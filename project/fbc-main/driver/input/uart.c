#include <register.h>
#include <inputdata.h>
#include <interrupt.h>
#include <serial.h>
#include <uart.h>
#include <malloc.h>
#include <string.h>

#ifdef IN_FBC_MAIN_CONFIG
#include <log.h>
#include <task_priority.h>
#include <input.h>
#include <task.h>
#include <timer.h>
#include <common.h>
#include <command.h>

#define CONFIG_SYS_PROMPT	"fbc-main#"

static int ConsoleTaskID = -1;
static int Uart_0_TaskID = -1;
static int Uart_1_TaskID = -1;
static int ConsoleTimerID = -1;

extern int pq_cmd_flag;
extern int first_sep_index;
extern int LogcatRunFlag;
extern int ctrlc_flag;
extern int console_buffer_len;
extern char new_line_flag;
extern char IRQ_MODE;
extern char console_buffer[MAX_CONSOLE_BUF_SIZE];
extern char lastcommand[MAX_CONSOLE_BUF_SIZE];
#endif

extern unsigned char console_state;
extern unsigned char ucEnablePrint;
extern unsigned char cmd_state;

static char TAG[]= "uart" ;

#define UART_RX_IRQ_TRIGGER_SIZE	1
#define UART_TX_IRQ_TRIGGER_SIZE	16

#define UART_BUF_SIZE	1024

static struct serial_device *uart_port_0_ctl_device= NULL;
static struct serial_device *uart_port_1_ctl_device= NULL;
UART_CTRL_T uart_port_0_ctl = {0, 0, 0, 0, NULL, NULL, NULL};
UART_CTRL_T uart_port_1_ctl = {0, 0, 0, 0, NULL, NULL, NULL};

extern void enable_uart_interrupt(unsigned port_base, unsigned type, unsigned on, unsigned trigger_size);
extern void reset_uart(unsigned port_base, unsigned type);

#ifdef IN_FBC_MAIN_CONFIG
static int ConsoleHandler(int task_id, void *param)
{
	int len;
	int rc = 2;
	len = readline (default_serial_console(), CONFIG_SYS_PROMPT);
	
	if(LogcatRunFlag && len != -1)
	{
		return 0;
	}
	
	if (len > 0)
	{
		if(!pq_cmd_flag)
			strcpy (lastcommand, console_buffer);
	}

	if (len == -1)
	{
		serial_puts ("<INTERRUPT>\n");
		if(LogcatRunFlag)
		{
			ctrlc_flag = 1;
			LogcatRunFlag = 0;
		}
	}
	else if(len == -2)
	{
		new_line_flag = 0;
	}
	else
	{
		if(pq_cmd_flag)
		{
			rc = run_command ((char *)EXTEND_BUF_ADDR, 0);
		}
		else
		{
			rc = run_command (lastcommand, 0);
		}
	}

	if (rc <= 0 || (len<0 && len!=-2))
	{
		new_line_flag = 1;
		pq_cmd_flag = 0;
		first_sep_index = -1;
		lastcommand[0] = 0;
		serial_puts(CONFIG_SYS_PROMPT);
	}
	else if(rc == 1)
	{
		serial_puts(CONFIG_SYS_PROMPT);
	}
	return 0;
}

static void UART0_IRQ_FUNC(void)
{
	//do nothing
	;
}

void uart_console_hd_enable(unsigned char ucValue)
{
	if(ucValue)
	{
		if(ConsoleTaskID < 0)
		{
			ConsoleTaskID = RegisterTask(ConsoleHandler, NULL, 1<<INT_UART0, TASK_PRIORITY_CONSOLE);
			if(ConsoleTaskID > 0)
			{
				ConsoleTimerID = request_timer(ConsoleTaskID, 8);
			}
		}
	}
	else 
	{
		if(ConsoleTimerID >= 0)
		{
			release_timer(ConsoleTimerID);
			ConsoleTimerID = -1;
		}
		if(ConsoleTaskID > 0)
		{
			UnregisterTask(ConsoleTaskID);
			ConsoleTaskID = -1;
		}
	}
}

void uart_print_enable(unsigned char ucValue)
{
    ucEnablePrint = ucValue;
}

int console_enable(void)
{
	LOGI(TAG,"Enter uart_port_0_open\n");
	int i;
	console_state = 1;

	uart_ports_open(DEVICE_UART_PORT_0);
	uart_console_hd_enable(1);
	IRQ_MODE = 1;
	
	i=RegisterInterrupt(INT_UART0, INT_TYPE_IRQ, UART0_IRQ_FUNC);
	if(i==0)
	{
		SetInterruptEnable(INT_UART0, 1);
	}
	
	return i;
}

int console_disable(void)
{
	console_state = 0;
	UnregisterInterrupt(INT_UART0, UART0_IRQ_FUNC);
	uart_console_hd_enable(0);
	SetInterruptEnable(INT_UART0, 0);
	uart_ports_cloe(DEVICE_UART_PORT_0);
	return 0;
}
#endif

/*init uart1 for G9 and FBC communicate*/

static unsigned long rx_get_data_len(unsigned uart_port_num){
		unsigned long rx_read_ptr, rx_write_ptr;
		unsigned int rx_wrap_flag;
	  UART_CTRL_T *uart_ports_ctl= NULL;
	  switch (uart_port_num)	{
	  		case DEVICE_UART_PORT_0:
	  				uart_ports_ctl= &uart_port_0_ctl;
	  				break;
	  		case DEVICE_UART_PORT_1:
	  				uart_ports_ctl= &uart_port_1_ctl;
	  				break;
	  		default:
	  			  break;
	  }		
		rx_wrap_flag = uart_ports_ctl->rx_wrap_flag;
		rx_read_ptr = (unsigned long)uart_ports_ctl->rx_read_ptr;
		rx_write_ptr = (unsigned long)uart_ports_ctl->rx_write_ptr;
  	
		if(rx_wrap_flag)
		{
			return (UART_BUF_SIZE - (rx_read_ptr - rx_write_ptr));
		}
		else
		{
			return (rx_write_ptr - rx_read_ptr);
		}
}

static void rx_inc_read_ptr(unsigned uart_port_num) {
	  UART_CTRL_T *uart_ports_ctl= NULL;
	  switch (uart_port_num)	{
	  		case DEVICE_UART_PORT_0:
	  				uart_ports_ctl= &uart_port_0_ctl;
	  				break;
	  		case DEVICE_UART_PORT_1:
	  				uart_ports_ctl= &uart_port_1_ctl;
	  				break;
	  		default:
	  			  break;
	  }
		uart_ports_ctl->arc_busy_flag = 1;
		uart_ports_ctl->rx_read_ptr++;
		if(uart_ports_ctl->rx_read_ptr >= (uart_ports_ctl->rx_buf + UART_BUF_SIZE))
		{
			uart_ports_ctl->rx_read_ptr = uart_ports_ctl->rx_buf;
			if(uart_ports_ctl->rx_wrap_flag)
				uart_ports_ctl->rx_wrap_flag = 0;
		}
		
		uart_ports_ctl->arc_busy_flag = 0;
}

static void rx_inc_write_ptr(unsigned uart_port_num)	{
	  UART_CTRL_T *uart_ports_ctl= NULL;
	  switch (uart_port_num)	{
	  		case DEVICE_UART_PORT_0:
	  				uart_ports_ctl= &uart_port_0_ctl;
	  				break;
	  		case DEVICE_UART_PORT_1:
	  				uart_ports_ctl= &uart_port_1_ctl;
	  				break;
	  		default:
	  			  break;
	  }	  		
		uart_ports_ctl->rx_write_ptr++;
		if(uart_ports_ctl->rx_write_ptr >= (uart_ports_ctl->rx_buf + UART_BUF_SIZE))
		{
			uart_ports_ctl->rx_write_ptr = uart_ports_ctl->rx_buf;
			uart_ports_ctl->rx_wrap_flag = 1;
		}
}


static void checkUART(unsigned uart_port_num) {
    struct serial_device *uart_ports_ctl_device= NULL;
	  UART_CTRL_T *uart_ports_ctl= NULL;
	  switch (uart_port_num)	{
	  		case DEVICE_UART_PORT_0:
	  			  uart_ports_ctl_device= uart_port_0_ctl_device;
	  				uart_ports_ctl= &uart_port_0_ctl;
	  				break;
	  		case DEVICE_UART_PORT_1:
	  			  uart_ports_ctl_device= uart_port_1_ctl_device;
	  				uart_ports_ctl= &uart_port_1_ctl;
	  				break;
	  		default:
	  			  break;
	  }    

		if(uart_ports_ctl_device) {
				while(uart_ports_ctl_device->tstc()) {
						*uart_ports_ctl->rx_write_ptr = uart_ports_ctl_device->getc();
						rx_inc_write_ptr(uart_port_num);
				}
	  }
}

static void UART0_IRQ_Handle(void)
{
	return checkUART(DEVICE_UART_PORT_0);
}

static void UART1_IRQ_Handle(void)
{
	return checkUART(DEVICE_UART_PORT_1);
}

static void uart_buf_init(UART_CTRL_T *uart_ctl)
{
    uart_ctl->rx_read_ptr = uart_ctl->rx_buf;
    uart_ctl->rx_write_ptr = uart_ctl->rx_buf;
    uart_ctl->rx_wrap_flag = 0;
    uart_ctl->arc_busy_flag = 0;
    uart_ctl->rx_read_cnt =0;
    uart_ctl->tx_write_cnt =0;
    memset(uart_ctl->rx_buf, 0, UART_BUF_SIZE);
}


int uart_ports_open(unsigned uart_port_num) {
		int i=-2;
		switch (uart_port_num)	{
				case DEVICE_UART_PORT_0:
						{
#ifdef IN_FBC_MAIN_CONFIG
								LOGI(TAG,"Enter uart_port_0_open\n");
//								console_disable();
//		            Uart_0_TaskID = RegisterTask(UART0_IRQ_Handle, NULL, 1<<INT_UART0, TASK_PRIORITY_UART1);
#endif
		            uart_port_0_ctl.rx_buf = (unsigned char*)malloc(UART_BUF_SIZE);
					printf("uart_port_0_ctl.rx_buf : 0x%x\n", uart_port_0_ctl.rx_buf);
		            if(uart_port_0_ctl.rx_buf)	{
		            		uart_buf_init(&uart_port_0_ctl);
							
						  i= RegisterInterrupt(INT_UART0, INT_TYPE_IRQ, UART0_IRQ_Handle);
		            	  if(i==0) {
		            	  		serial_init(DEVICE_UART_PORT_0);
		            			  enable_uart_interrupt(UART_PORT_0, UART_RX_TYPE, UART_IRQ_ON, UART_RX_IRQ_TRIGGER_SIZE);
		            	  		uart_port_0_ctl_device= (struct serial_device *)get_serial_device(DEVICE_UART_PORT_0);
		            	  		SetInterruptEnable(INT_UART0, 1);
		            	  }
		            }
		       }
		       break;
				case DEVICE_UART_PORT_1:
						{
#ifdef IN_FBC_MAIN_CONFIG
								LOGI(TAG,"Enter uart_port_1_open\n");
//		            Uart_1_TaskID = RegisterTask(UART1_IRQ_Handle, NULL, 1<<INT_UART1, TASK_PRIORITY_UART1);
#endif		            
		            uart_port_1_ctl.rx_buf = (unsigned char*)malloc(UART_BUF_SIZE);
		            if(uart_port_1_ctl.rx_buf)	{
		            		uart_buf_init(&uart_port_1_ctl);
							
            	  i= RegisterInterrupt(INT_UART1, INT_TYPE_IRQ, UART1_IRQ_Handle);
		            	  if(i==0) {
		            	  		serial_init(DEVICE_UART_PORT_1);
		            			  enable_uart_interrupt(UART_PORT_1, UART_RX_TYPE, UART_IRQ_ON, UART_RX_IRQ_TRIGGER_SIZE);
		            	  		uart_port_1_ctl_device= (struct serial_device *)get_serial_device(DEVICE_UART_PORT_1);
		            	  		SetInterruptEnable(INT_UART1, 1);
		            	  }
		            }
		       }
		       break;
		   default:
		   	   break;
		}
		    
		return i;
}

int uart_ports_cloe(unsigned uart_port_num) {
		int i=0;
		switch (uart_port_num)	{
				case DEVICE_UART_PORT_0:
						if(uart_port_0_ctl.rx_buf) {
								free(uart_port_0_ctl.rx_buf);
					  }
					  SetInterruptEnable(INT_UART0, 0);
					  UnregisterInterrupt(INT_UART0, UART0_IRQ_Handle);
					  break;
				case DEVICE_UART_PORT_1:
						if(uart_port_1_ctl.rx_buf) {
								free(uart_port_1_ctl.rx_buf);
					  }
					  SetInterruptEnable(INT_UART1, 0);
					  UnregisterInterrupt(INT_UART1, UART1_IRQ_Handle);
					  break;
				default:
					  break;
		}
		return i;
}

unsigned  uart_ports_read(unsigned uart_port_num, unsigned char *read_buf, unsigned length) {
		unsigned char *read_data_index;
    unsigned ready_bytes, i;        
    read_data_index = read_buf;
	  UART_CTRL_T *uart_ports_ctl= NULL;
	  switch (uart_port_num)	{
	  		case DEVICE_UART_PORT_0:
	  				uart_ports_ctl= &uart_port_0_ctl;
	  				break;
	  		case DEVICE_UART_PORT_1:
	  				uart_ports_ctl= &uart_port_1_ctl;
	  				break;
	  		default:
	  			  break;
	  }
    uart_ports_ctl->rx_read_cnt = 0;

    ready_bytes = rx_get_data_len(uart_port_num);

	  ready_bytes = (ready_bytes > (length - uart_ports_ctl->rx_read_cnt)) ? (length - uart_ports_ctl->rx_read_cnt) : ready_bytes;
	  	
	  for(i=0; i<ready_bytes; i++) {
	  		*read_data_index++ = *uart_ports_ctl->rx_read_ptr;
		 		rx_inc_read_ptr(uart_port_num);
		    uart_ports_ctl->rx_read_cnt++;
		}
  
    return ready_bytes;
}

void uart_ports_write(unsigned uart_port_num, unsigned char *write_buf, unsigned length) {

    unsigned char *write_data_index;
    unsigned length_to_write;
    struct serial_device *uart_ports_ctl_device= NULL;
	  UART_CTRL_T *uart_ports_ctl= NULL;
	  switch (uart_port_num)	{
	  		case DEVICE_UART_PORT_0:
	  			  uart_ports_ctl_device= uart_port_0_ctl_device;
	  				uart_ports_ctl= &uart_port_0_ctl;
	  				break;
	  		case DEVICE_UART_PORT_1:
	  			  uart_ports_ctl_device= uart_port_1_ctl_device;
	  				uart_ports_ctl= &uart_port_1_ctl;
	  				break;
	  		default:
	  			  break;
	  }    
    
    write_data_index = write_buf;
    length_to_write = length;
	  uart_ports_ctl->tx_write_cnt = 0;
	  while(uart_ports_ctl->tx_write_cnt < length_to_write)	{
	  		if(uart_ports_ctl_device) {
	  			  uart_ports_ctl->tx_write_cnt++;
	  				uart_ports_ctl_device->putc(*(write_data_index++));
	      }
	  }
    return; 
}

#ifdef IN_FBC_MAIN_CONFIG
void UartDebugEnable(unsigned char ucVal)
{
	if(ucVal)
	{
		uart_ports_cloe(DEVICE_UART_PORT_0);
		console_enable();
	}
	else 
	{
		console_disable();
		uart_ports_open(DEVICE_UART_PORT_0);
	}
}

unsigned char GetUartDebugStatus(void)	
{
	return console_state ;
}
#endif

void Set_0a_to_0d0a_enable(unsigned char ucVal) //add for customer 0 disable; 1 enable

{
	console_state = ucVal;
	if(0 == ucVal)
		cmd_state = 1; // cmd_state = 1 : disable \r for uart1
	else
		cmd_state = 0; // cmd_state = 0 : enable \r for uart1
}

