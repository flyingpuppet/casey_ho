#include <common.h>
#include <log.h>
#include <inputdata.h>
#include <task.h>
#include <timer.h>
#include <malloc.h>
#include <string.h>
#include <cmd.h>
#include <crc.h>
#include <uart.h>
#include <uart_api.h>
#include <task_priority.h>


#define LEADINGBYTES        0x5a5a
#define READ_LEADING_FIELD  0x01
#define READ_LENGTH_FIELD   0x02
#define READ_DATA_FIELD     0x03
#define READ_PACKAGE_DONE   0x04

#define LEADING_FIELD_SIZE              0x2
#define LENGTH_FIELD_SIZE               0x2
#define TYPE_AND_ID_FIELD_SIZE          0x2
#define ID_FIELD_SIZE                   0x1
#define TYPE_FIELD_SIZE                 0x1
#define RESPONSE_CONTENT_FIELD_SIZE     0x2
#define CRC_FIELD_SIZE                  0x4

#define LEADING_FIELD_INDEX     (0x0)
#define LENGTH_FIELD_INDEX      (LEADING_FIELD_INDEX + LEADING_FIELD_SIZE)
#define TYPE_FIELD_INDEX        (LENGTH_FIELD_INDEX + LENGTH_FIELD_SIZE)
#define ID_FIELD_INDEX          (TYPE_FIELD_INDEX + TYPE_FIELD_SIZE)
#define DATA_FIELD_INDEX        (ID_FIELD_INDEX + ID_FIELD_SIZE)
#define RESPONSE_FIELD_INDEX    (DATA_FIELD_INDEX)

#define RESPONSE_FIELD_FLAG         0x80
#define RESPONSE_PACKAGE_LENGTH     (LEADING_FIELD_SIZE + LENGTH_FIELD_SIZE + TYPE_AND_ID_FIELD_SIZE + RESPONSE_CONTENT_FIELD_SIZE + CRC_FIELD_SIZE)
#define CMD_RESPONSE_CRC_OK         0x7ffe
#define CMD_RESPONSE_CRC_ERROR      0x8001

typedef struct {
    unsigned char flag;
    unsigned char timeout_flag;
    unsigned short rhead_field_count;
    unsigned short rlength_field_count;
    unsigned short rdata_field_count;   //contains crc field
    unsigned short length;
    unsigned short pos;
    unsigned int crc;
    unsigned char head[4];
    unsigned char *package;
} UART_RX_CMD_PACKAGE_T;

typedef struct {
    unsigned char re_send_cnt;
    unsigned char timeout_cnt;
    unsigned short length;
    unsigned char *package;
} UART_TX_CMD_PACKAGE_T;

static UART_RX_CMD_PACKAGE_T rx_cmd_package;
static UART_TX_CMD_PACKAGE_T tx_cmd_package;
static int uart_communication_task_id = -1;
static int timer_id;
static int interval = 5;

extern unsigned char cmd_state;


//#define __UART_COMMUNICATION_DEBUG__
#ifdef __UART_COMMUNICATION_DEBUG__
static void print(int type, void *m)
{
    if(!m) return;

    if(type == 0) {
        UART_RX_CMD_PACKAGE_T *rc = (UART_RX_CMD_PACKAGE_T *)m;
        printf("flag: 0x%x, length: %d\n", rc->flag, rc->length);
        int i;
        printf("head:\n");
        for(i=0; i<4; i++) {
            printf("%x ", rc->head[i]);
        }

        printf("\nreceive package:\n");

        for(i=0; i<rc->length; i++) {
            printf("%x ", rc->package[i]);
        }

        printf("\n");
    } else {
        UART_TX_CMD_PACKAGE_T *tc = (UART_TX_CMD_PACKAGE_T *)m;

        printf("re_send_cnt: 0x%x, length: %d\n", tc->re_send_cnt, tc->length);
        int i;
        printf("\ntransceive package:\n");

        for(i=0; i<tc->length; i++) {
            printf("%x ", tc->package[i]);
        }

        printf("\n");
    }
}
#endif

static int get_field(int type, int start, unsigned char *buf, void *ret)
{
    unsigned char *p, *q;
    int i;

    if(!buf || !ret) return -1;

    p = (unsigned char *)((unsigned)buf+start);
    q = (unsigned char *)ret;

    for(i=0; i<type; i++,p++,q++) {
        *q = *p;
    }

    return 0;
}

static int set_field(int type, int start, void *val, unsigned char *buf)
{
    unsigned char *p, *q;
    int i;

    if(!buf || !val) return -1;

    p = (unsigned char *)((unsigned)buf+start);
    q = (unsigned char *)val;

    for(i=0; i<type; i++,p++,q++) {
        *p = *q;
    }

    return 0;
}

static int uart_channel_send_data(unsigned char *s, unsigned short len)
{
    if(tx_cmd_package.package != NULL) {
        serial_puts("last cmd package not tx done!\n");
        return -2;
    }

    tx_cmd_package.length = LEADING_FIELD_SIZE + LENGTH_FIELD_SIZE + TYPE_FIELD_SIZE + len + CRC_FIELD_SIZE;
    tx_cmd_package.package = (unsigned char *)malloc(tx_cmd_package.length);

    if(tx_cmd_package.package == NULL) {
        serial_puts("no memory!\n");
        return -1;
    }

    unsigned short leading = LEADINGBYTES;
    unsigned char type = 0;
    unsigned crc;

    set_field(LEADING_FIELD_SIZE, LEADING_FIELD_INDEX, &leading, tx_cmd_package.package);
    set_field(LENGTH_FIELD_SIZE, LENGTH_FIELD_INDEX, &(tx_cmd_package.length), tx_cmd_package.package);
//  set_field(ID_FIELD_SIZE, ID_FIELD_INDEX, s, tx_cmd_package.package);
    set_field(TYPE_FIELD_SIZE, TYPE_FIELD_INDEX, &type, tx_cmd_package.package);
    set_field(len, ID_FIELD_INDEX, s, tx_cmd_package.package);

    crc = crc32(0, tx_cmd_package.package, tx_cmd_package.length - CRC_FIELD_SIZE);
    set_field(CRC_FIELD_SIZE, tx_cmd_package.length - CRC_FIELD_SIZE, &crc, tx_cmd_package.package);

    cmd_state = 1;
    uart_ports_write(DEVICE_UART_PORT_1, tx_cmd_package.package, tx_cmd_package.length);
    cmd_state = 0;

    tx_cmd_package.re_send_cnt++;

#ifdef __UART_COMMUNICATION_DEBUG__
    printf("uart_channel_send_data:\n");
    print(1, &tx_cmd_package);
#endif

    return 0;
}

static int uart_receive_cmd_package(UART_RX_CMD_PACKAGE_T *rx_package)
{
    int ret;
    unsigned char *p;

    if(!rx_package) return -1;

    if(rx_package->pos != 0 && rx_package->timeout_flag > 2) return -2; //receive timeout

    if(rx_package->package == NULL) {
        p = rx_package->head + rx_package->pos;
    } else {
        p = rx_package->package + rx_package->pos;
    }

    if(rx_package->flag == READ_LEADING_FIELD) {
        ret = uart_ports_read(DEVICE_UART_PORT_1, p, rx_package->rhead_field_count);
        rx_package->rhead_field_count -= ret;
        rx_package->pos += ret;

        if(0 == rx_package->rhead_field_count) {
            unsigned short leading;
            get_field(LEADING_FIELD_SIZE, LEADING_FIELD_INDEX, rx_package->head, &leading);

            if(LEADINGBYTES == leading) {
                rx_package->flag = READ_LENGTH_FIELD;
            } else {
                //serial_puts("leading bytes is not 0x5a5a.\n");
                return -1;
            }
        }
        p = rx_package->head + rx_package->pos;

    }

    if(rx_package->flag == READ_LENGTH_FIELD) {
        ret = uart_ports_read(DEVICE_UART_PORT_1, p, rx_package->rlength_field_count);
        rx_package->rlength_field_count -= ret;
        rx_package->pos += ret;

        if(0 == rx_package->rlength_field_count) {
            get_field(LENGTH_FIELD_SIZE, LENGTH_FIELD_INDEX, rx_package->head, &(rx_package->length));
            rx_package->rdata_field_count = rx_package->length - LEADING_FIELD_SIZE - LENGTH_FIELD_SIZE;
            rx_package->flag = READ_DATA_FIELD;
            rx_package->package = (unsigned char *)malloc(rx_package->length);
            if(rx_package->package == NULL) {
                serial_puts("in uart_receive_cmd_package malloc rx_package->package failed.\n");
                return -1;
            }
            memcpy(rx_package->package, rx_package->head, sizeof(rx_package->head));
        }

        if(rx_package->package == NULL) {
            p = rx_package->head + rx_package->pos;
        } else {
            p = rx_package->package + rx_package->pos;
        }
    }

    if(rx_package->flag == READ_DATA_FIELD) {
        ret = uart_ports_read(DEVICE_UART_PORT_1, p, rx_package->rdata_field_count);
        rx_package->rdata_field_count -= ret;
        rx_package->pos += ret;

        if(0 == rx_package->rdata_field_count) {
            rx_package->flag = READ_PACKAGE_DONE;
        }
        p = rx_package->package + rx_package->pos;
    }

    if(rx_package->pos != 0) rx_package->timeout_flag++;

    return 0;
}

static void reset_tx_cmd_package(UART_TX_CMD_PACKAGE_T *tx_package)
{
    if(!tx_package) return;

    if(tx_package->package != NULL) {
        free(tx_package->package);
        tx_package->package = NULL;
    }

    memset(tx_package, 0, sizeof(UART_TX_CMD_PACKAGE_T));
}

static void reset_rx_cmd_package(UART_RX_CMD_PACKAGE_T *rx_package)
{
    if(!rx_package) return;

    if(rx_package->package != NULL) {
        free(rx_package->package);
        rx_package->package = NULL;
    }

    memset(rx_package, 0, sizeof(UART_RX_CMD_PACKAGE_T));

    rx_package->flag = READ_LEADING_FIELD;
    rx_package->rhead_field_count = LEADING_FIELD_SIZE;
    rx_package->rlength_field_count = LENGTH_FIELD_SIZE;
}

static int resend_cmd_package(UART_TX_CMD_PACKAGE_T *tx_package)
{
    if(!tx_package) return -1;

    tx_package->re_send_cnt += 1;
    cmd_state = 1;
    uart_ports_write(DEVICE_UART_PORT_1, tx_package->package, tx_package->length);
    cmd_state = 0;

    if(tx_package->re_send_cnt >= 3) {
        reset_tx_cmd_package(tx_package);
    }

    return 0;
}

static int is_response_package(unsigned char *package)
{
    unsigned char flag;

    if(!package) return 0;

    get_field(TYPE_FIELD_SIZE, TYPE_FIELD_INDEX, package, &flag);

#ifdef __UART_COMMUNICATION_DEBUG__
    printf("is_response_package flag: 0x%x\n", flag);
#endif

    if(flag & (1<<7)) {
        return 1;
    }

    return 0;
}

static int handle_response_package(UART_RX_CMD_PACKAGE_T *rx_package)
{
    if(!rx_package) return -1;

    if(rx_package->package) {
        unsigned short response_value;
        get_field(RESPONSE_CONTENT_FIELD_SIZE, RESPONSE_FIELD_INDEX, rx_package->package, &response_value);

#ifdef __UART_COMMUNICATION_DEBUG__
        printf("handle_response_package response_value: 0x%x\n", response_value);
#endif

        if(CMD_RESPONSE_CRC_OK == response_value) {
            reset_tx_cmd_package(&tx_cmd_package);
        } else {
            resend_cmd_package(&tx_cmd_package);
        }
    }

    reset_rx_cmd_package(rx_package);

    return 0;
}

static int generate_send_response_package(unsigned char id, unsigned short content)
{
#ifdef __UART_COMMUNICATION_DEBUG__
    printf("response_package id: 0x%x, type: 0x%x\n", id, content);
#endif

    unsigned char package[RESPONSE_PACKAGE_LENGTH];
    UART_TX_CMD_PACKAGE_T tx_package;
    tx_package.length = RESPONSE_PACKAGE_LENGTH;
    tx_package.package = package;
    unsigned short leading = LEADINGBYTES;
    unsigned char respose_flag = RESPONSE_FIELD_FLAG;

    set_field(LEADING_FIELD_SIZE, LEADING_FIELD_INDEX, &leading, tx_package.package);
    set_field(LENGTH_FIELD_SIZE, LENGTH_FIELD_INDEX, &(tx_package.length), tx_package.package);
    set_field(TYPE_FIELD_SIZE, TYPE_FIELD_INDEX, &respose_flag, tx_package.package);
    set_field(ID_FIELD_SIZE, ID_FIELD_INDEX, &id, tx_package.package);
    set_field(sizeof(content), DATA_FIELD_INDEX, &content, tx_package.package);

    int crc = crc32(0, tx_package.package, tx_package.length - CRC_FIELD_SIZE);
    set_field(CRC_FIELD_SIZE, tx_package.length-CRC_FIELD_SIZE, &crc, tx_package.package);

    cmd_state = 1;
    uart_ports_write(DEVICE_UART_PORT_1, tx_package.package, tx_package.length);
    cmd_state = 0;

#ifdef __UART_COMMUNICATION_DEBUG__
    printf("line: %d -- re_send_cnt: 0x%x, length: %d\n", __LINE__, tx_package.re_send_cnt, tx_package.length);
    int i;
    printf("\npackage:\n");

    for(i=0; i<tx_package.length; i++) {
        printf("%x ", tx_package.package[i]);
    }
    printf("\n");
#endif

    return 0;
}

static int handle_cmd_package(UART_RX_CMD_PACKAGE_T *rx_package)
{
    if(!rx_package) return -1;

    unsigned cmd_len = rx_package->length - LEADING_FIELD_SIZE - LENGTH_FIELD_SIZE - CRC_FIELD_SIZE - 1;

    unsigned char *cmd = (unsigned char *)malloc(cmd_len);

    if(NULL == cmd) {
        serial_puts("In handle_cmd_package malloc cmd failed!\n");
        return -1;
    }

    get_field(ID_FIELD_SIZE, ID_FIELD_INDEX, rx_package->package, &cmd[0]);
    get_field(cmd_len-1, DATA_FIELD_INDEX, rx_package->package, &cmd[1]);

#ifdef __UART_COMMUNICATION_DEBUG__
    printf("handle_cmd_package cmd lenth: %d\ncmd:\n", cmd_len);
    int i;
    for(i=0; i<cmd_len; i++)
        printf("%x ", cmd[i]);
    printf("\n");
#endif

    CmdChannelAddData(INPUT_UART_HOST, cmd);

    unsigned char id = 0x0;
    get_field(ID_FIELD_SIZE, ID_FIELD_INDEX, rx_package->package, &id);
    generate_send_response_package(id, CMD_RESPONSE_CRC_OK);

    reset_rx_cmd_package(rx_package);
    return 0;
}

static int UartCommunicationHandler(int task_id, void *param)
{
    if(tx_cmd_package.package != NULL) {
        tx_cmd_package.timeout_cnt += interval * 10;
        if(200 == tx_cmd_package.timeout_cnt || 400 == tx_cmd_package.timeout_cnt)
            resend_cmd_package(&tx_cmd_package);

    }

    int ret = uart_receive_cmd_package(&rx_cmd_package);
    if(ret != 0) {
        if(ret == -2) serial_puts("receive cmd timeout!\n");

        reset_rx_cmd_package(&rx_cmd_package);
    }

    if(READ_PACKAGE_DONE == rx_cmd_package.flag) {
        rx_cmd_package.crc = crc32(0, rx_cmd_package.package, rx_cmd_package.length - CRC_FIELD_SIZE);

        unsigned crc = 0;
        int start = rx_cmd_package.length - CRC_FIELD_SIZE;
        get_field(CRC_FIELD_SIZE, start, rx_cmd_package.package, &crc);

#ifdef __UART_COMMUNICATION_DEBUG__
        print(0, &rx_cmd_package);
        printf("rx_cmd_package.crc: 0x%x, crc: 0x%x\n", rx_cmd_package.crc, crc);
#endif

        if(crc == rx_cmd_package.crc) {
            if(is_response_package(rx_cmd_package.package)) {
                handle_response_package(&rx_cmd_package);
            } else {
                if(tx_cmd_package.package == NULL)
                    handle_cmd_package(&rx_cmd_package);
            }
        } else {
            serial_puts("crc check error!\n");
            unsigned char id = 0x0;
            get_field(ID_FIELD_SIZE, ID_FIELD_INDEX, rx_cmd_package.package, &id);
            generate_send_response_package(id, CMD_RESPONSE_CRC_ERROR);
            reset_rx_cmd_package(&rx_cmd_package);
            return -1;
        }
    }
    return 0;
}

void uart_communication_task_init()
{
    reset_rx_cmd_package(&rx_cmd_package);
    reset_tx_cmd_package(&tx_cmd_package);
    uart_ports_open(DEVICE_UART_PORT_1);
    RegisterChannel(INPUT_UART_HOST, uart_channel_send_data);
    uart_communication_task_id = RegisterTask(UartCommunicationHandler, NULL, 0, TASK_PRIORITY_UART_COMMUNICATION);
    timer_id = request_timer(uart_communication_task_id, interval);
    return;
}

