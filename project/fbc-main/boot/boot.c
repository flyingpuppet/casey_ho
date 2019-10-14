#include <serial.h>
#include <command.h>
#include <common.h>
#include <reboot.h>
#include <inputdata.h>
#include <spi_regional_division.h>

#define CONFIG_SYS_PROMPT       "fbc-boot#"
#define SF_UPGRADE_CMD    "ug"
#define RF_UPGRADE_RES    "ok"
#define RF_NOUPGRADE_RES  "ng"
#define CONFIG_UPDATE_KEY	16

#define _xxxx_
#define _ADCKEY_TEST_

extern void clock_init(void);
extern void sar_adc_init(void);
extern int detect_adc_key(int chanel, INPUTDATA *inputdata);
extern int set_redetect_flag();
extern int adc2key(int chan, INPUTDATA *data);

struct serial_device *current_serial_device = 0;

#ifdef HAS_ROM_MAP
extern unsigned __SECTION_SIZE[];
#endif
extern char console_buffer[MAX_CONSOLE_BUF_SIZE];
extern char lastcommand[MAX_CONSOLE_BUF_SIZE];

extern void print_build_version_info(void);

int check_main_code(void)
{
    printf("start check main code...\n");

    if(check_image(ICCM_BASE, ICCM_SIZE)) return 0;

    return -1;
}

int check_main_data(void)
{
    printf("enter check main data...\n");

    if(check_image(DCCM_BASE, DCCM_SIZE)) return 0;

    return -1;
}

// boot code running in SPI, not need to copy, except when need to upgrade boot code
void copy_data_from_spi_to_sram2(int start_addr, int length)
{
    int *des=(int *)SRAM2_BASE;
    int *src =(int *)start_addr;
    int i=0;
    for(i=0; i<length; i++) {
        *(des++) = *(src++);
    }
}

void copy_code_from_spi_to_ICCM(int start_addr, int length)
{
    int *des=(int *)ICCM_BASE;
    int *src =(int *)start_addr;
    int i=0;
    for(i=0; i<length; i++) {
        if(i%256 == 0) serial_putc('.');
        *(des++) = *(src++);
    }
    serial_putc('\n');
}


void copy_data_from_spi_to_DCCM(int start_addr, int length)
{
    int *des=(int *)DCCM_BASE ;
    int *src =(int *)start_addr;
    int i=0;
    for(i=0; i<length; i++) {
        if(i%256 == 0) serial_putc('.');
        *(des++) = *(src++);
    }
    serial_putc('\n');
}

static void do_wait_cmd()
{
    int len;
    int rc = 1;
    int flag;
    for (;;) {
        len = readline (current_serial_device, CONFIG_SYS_PROMPT);
        flag = 0;   // assume no special flags for now
        if (len > 0)
            strcpy (lastcommand, console_buffer);
        else if (len == 0)
            flag |= CMD_FLAG_REPEAT;

        if (len == -1)
            serial_puts ("<INTERRUPT>\n");
        else
            rc = run_command (lastcommand, flag);

        if (rc <= 0 || len < 0) {
            // invalid command or not repeatable, forget it
            lastcommand[0] = 0;
        }
    }
}

static void udelay(int us)
{
    register int n= us*105;
    while(n--);
}

unsigned int bootdelay = 100;

static int abortboot(int bootdelay)
{
    int abort = 0;
    char key;
    serial_puts("Hit enter key to stop autoboot\n");
    if (bootdelay >= 0) {
        if (serial_tstc()) {
            switch (serial_getc()) {
            case 0x03:      /* ^C - Ctrl+C */
                abort = 1;
                break;
            case 0x0d:      /* Enter */
                abort = 1;
                break;
            case 0x20:      /* Space */
                abort = 1;
                break;
            default:
                break;
            }
        }
    }

    if (abort == 1) {
        //Disable Watchdog
    }

    while ((bootdelay > 0) && (!abort)) {
        int i;
        --bootdelay;
        /* delay 100 * 10ms */
        for (i=0; !abort && i<100; ++i) {
            /* we got a key press   */
            if (serial_tstc()) {
                serial_puts("tstc enter\n");
                key = serial_getc();
                if(13 == key) { //only "enter" key can triger abort
                    abort  = 1; /* don't auto boot  */
                    bootdelay = 0;  /* no more delay    */
                    break;
                }
            }
            udelay(200);
        }
    }
    return abort;
}

int main()
{
    unsigned int boot_flag = 0; //0:normal boot, 1:do recovery, 2:do suspend
    clock_init();
    copy_data_from_spi_to_sram2(BOOT_DATA_BASE, BOOT_DATA_SIZE>>2);

    serial_init(0);
    current_serial_device = default_serial_console();
    serial_puts("serial init success!\n\n");

	sar_adc_init();

	boot_flag = get_boot_flag();
	
#ifdef _ADCKEY_TEST_
	int i, j;
	INPUTDATA inputdata;
	set_redetect_flag();
	for(i=0; i<3; i++)
	{
		if(!detect_adc_key(1, &inputdata))
		{
			printf("data: 0x%x, type: %d\n", inputdata.input_data, inputdata.input_type);
			if(inputdata.input_type == 0 && adc2key(1, &inputdata) == CONFIG_UPDATE_KEY)
			{
				char rec[10] = {0, };
				int n;
				
				serial_init(1);
				struct serial_device *sdev1 = get_serial_device(1);
				while(1)
				{
					sdev1->puts(SF_UPGRADE_CMD);
					if(sdev1->tstc() >= 2)
					{
						for(n=0; n<2; n++)
						{
							rec[n] = sdev1->getc();
						}

						rec[n] = 0;
						
						if(!strcmp(RF_UPGRADE_RES, rec))
						{
							boot_flag = 0x88888888;
							break;
						}else if(!strcmp(RF_NOUPGRADE_RES, rec))
						{
							boot_flag = 0x87654321;
							break;
						}
					}
					
				}

				break;
				
			}
		}

		for(j=100*1000; j>0; j--);

	}
	
#endif

    printf("fbc boot code version:\n");
    print_build_version_info();

    if(0x12345678 == boot_flag) {
        serial_puts("enter suspend!\n");
        copy_code_from_spi_to_ICCM(SUSPEND_CODE_BASE, SUSPEND_CODE_SIZE>>2);
        copy_data_from_spi_to_DCCM(SUSPEND_DATA_BASE, SUSPEND_DATA_SIZE>>2);
        return 0;

    }

    if(0x88888888 == boot_flag || 0x80808080 == boot_flag) {
        serial_puts("enter upgrade!\n");
        copy_code_from_spi_to_ICCM(UPDATE_CODE_BASE, UPDATE_CODE_SIZE>>2);
        serial_puts("copy upgrade code done!\n");
        copy_data_from_spi_to_DCCM(UPDATE_DATA_BASE, UPDATE_DATA_SIZE>>2);
        serial_puts("copy upgrade data done!\n");
        return 0;

    } else {
        if(bootdelay>0 && abortboot(bootdelay)) {
            serial_puts("enter the cmdline.\n");
            do_wait_cmd();
        } else {
#ifdef HAS_ROM_MAP
            printf("start copy main code, size %d bytes.\n", MAIN_CODE_SIZE);
            copy_code_from_spi_to_ICCM(MAIN_CODE_BASE, MAIN_CODE_SIZE>>2);

            printf("start copy main data, size %d bytes.\n", MAIN_DATA_SIZE);
            memset((int *)MAIN_DATA_BASE, 0, 0x10000);
            copy_data_from_spi_to_DCCM(MAIN_DATA_BASE, MAIN_DATA_SIZE>>2);
#else
            printf("start copy main code, size %d.\n", __SECTION_SIZE[0]);
            copy_code_from_spi_to_ICCM(MAIN_CODE_BASE, __SECTION_SIZE[0]>>2);
            printf("start copy main data. size %d\n", __SECTION_SIZE[1]);
            memset((int *)MAIN_DATA_BASE, 0, 0x10000);
            copy_data_from_spi_to_DCCM(MAIN_DATA_BASE, __SECTION_SIZE[1]>>2);
#endif
            printf("finish copy main code and run main code.\n");
            return 0; // return to boot.s and jump to 0(ICCM) to main code
        }

    }
}
