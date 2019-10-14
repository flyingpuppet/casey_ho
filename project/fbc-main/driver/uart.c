#include <uart.h>
#include <serial.h>
#include <log.h>

unsigned char console_state = 1;	//0:disable, 1:enable
unsigned char ucEnablePrint = 1;	//0:disable, 1:enable
unsigned char cmd_state = 0;

int serial_set_pin_port(unsigned port_base)
{
	if(port_base == UART_PORT_0)
	{
	    Wr_reg_bits(PERIPHS_PIN_MUX_0, 1, 6, 1);
	    Wr_reg_bits(PERIPHS_PIN_MUX_0, 0, 28, 2);
	    Wr_reg_bits(PERIPHS_PIN_MUX_0, 1, 7, 1);
	}
    else if (port_base == UART_PORT_1)
    {
//    	Wr_reg_bits(PERIPHS_PIN_MUX_1, 0, 25, 2);
//		Wr_reg_bits(PERIPHS_PIN_MUX_0, 0, 22, 1);
	    Wr_reg_bits(PERIPHS_PIN_MUX_2, 1, 5, 1);
	    Wr_reg_bits(PERIPHS_PIN_MUX_2, 1, 6, 1);

    }
    else
    {
    	Wr_reg_bits(DEBUG_BUS_SEL_CTL, 0, 15, 1);
	    Wr_reg_bits(PERIPHS_PIN_MUX_4, 1, 8, 1);
	    Wr_reg_bits(PERIPHS_PIN_MUX_4, 1, 9, 1);
    }
	
	return 0;
}

static void serial_putc_port (unsigned port_base,const char c);

/*
 * Sets baudarate
 */
static void serial_setbrg_port (unsigned port_base)
{
        
    unsigned long baud_para;
    int uart_clk = clk_get_rate(UART_0_CLK_SRC);
    if(uart_clk < 0)
        return;
     
    
    /* baud rate */
	baud_para=uart_clk/(UART_0_DEFAULT_BAUD_RATE*4) - 1;

    baud_para &= UART_CNTL_MASK_BAUD_RATE;

    /* write to the register */ 
    writel((readl(P_UART_CONTROL(port_base)) & ~UART_CNTL_MASK_BAUD_RATE) | baud_para, P_UART_CONTROL(port_base));
}

/*
 * Sets stop bits
 * input[0]: stop_bits (1, 2)
 */
static void serial_set_stop_port (unsigned port_base,int stop_bits)
{   
    unsigned long uart_config;

    uart_config = readl(P_UART_CONTROL(port_base)) & ~UART_CNTL_MASK_STP_BITS;
    /* stop bits */
    switch(stop_bits)
    {
        case 2:
            uart_config |= UART_CNTL_MASK_STP_2BIT;
            break;
        case 1:
        default:
            uart_config |= UART_CNTL_MASK_STP_1BIT;
            break;      
    }
    
    /* write to the register */
    writel(uart_config, P_UART_CONTROL(port_base));
}

/*
 * Sets parity type
 * input[0]: 1 -- enable parity, 0 -- disable;
 * input[1]: 1 -- odd parity, 0 -- even parity;
 */
static void serial_set_parity_port(unsigned port_base,int type)
{
    unsigned long uart_config;
     

    uart_config = readl(P_UART_CONTROL(port_base)) & ~(UART_CNTL_MASK_PRTY_TYPE | UART_CNTL_MASK_PRTY_EN);
#if 0   //changed by Elvis --- disable parity
    uart_config |= UART_CNTL_MASK_PRTY_EN;
    /* parity bits */
    if(type&2)
        uart_config |= UART_CNTL_MASK_PRTY_EN;
    if(type&1)
        uart_config |= UART_CNTL_MASK_PRTY_ODD;
    else
        uart_config |= UART_CNTL_MASK_PRTY_EVEN;
 #endif   
    /* write to the register */
    writel(uart_config, P_UART_CONTROL(port_base));

}

/*
 * Sets data length
 * input[0]: Character length [5, 6, 7, 8]
 */
static void serial_set_dlen_port (unsigned port_base,int data_len)
{
    unsigned long uart_config;
     
    uart_config = readl(P_UART_CONTROL(port_base)) & ~UART_CNTL_MASK_CHAR_LEN;
    /* data bits */
    switch(data_len)
    {
        case 5:
            uart_config |= UART_CNTL_MASK_CHAR_5BIT;
            break;
        case 6:
            uart_config |= UART_CNTL_MASK_CHAR_6BIT;
            break;
        case 7:
            uart_config |= UART_CNTL_MASK_CHAR_7BIT;
            break;
        case 8:
        default:
            uart_config |= UART_CNTL_MASK_CHAR_8BIT;
            break;
    }   
    
    /* write to the register */
    writel(uart_config, P_UART_CONTROL(port_base));
}



/*
 * reset the uart state machine
 */
static void serial_reset_port(unsigned port_base) {
	
	/* write to the register */
	writel(readl(P_UART_CONTROL(port_base)) | UART_CNTL_MASK_RST_TX | UART_CNTL_MASK_RST_RX | UART_CNTL_MASK_CLR_ERR, P_UART_CONTROL(port_base));
	writel(readl(P_UART_CONTROL(port_base)) & ~(UART_CNTL_MASK_RST_TX | UART_CNTL_MASK_RST_RX | UART_CNTL_MASK_CLR_ERR), P_UART_CONTROL(port_base));
}

/*
 * Intialise the serial port with given baudrate
 */

static int serial_init_port (unsigned port_base)
{
	int ret;
    writel(0,P_UART_CONTROL(port_base));
    ret = serial_set_pin_port(port_base);
    if (ret < 0)
    	return -1;
    
    serial_setbrg_port(port_base);
#ifndef CONFIG_SERIAL_STP_BITS
#define CONFIG_SERIAL_STP_BITS 1
#endif    
    serial_set_stop_port(port_base,CONFIG_SERIAL_STP_BITS);
#ifndef CONFIG_SERIAL_PRTY_TYPE
#define CONFIG_SERIAL_PRTY_TYPE 0
#endif

    serial_set_parity_port(port_base,CONFIG_SERIAL_PRTY_TYPE);
#ifndef CONFIG_SERIAL_CHAR_LEN
#define CONFIG_SERIAL_CHAR_LEN 8
#endif
    serial_set_dlen_port(port_base,CONFIG_SERIAL_CHAR_LEN);
    writel(readl(P_UART_CONTROL(port_base)) | UART_CNTL_MASK_TX_EN | UART_CNTL_MASK_RX_EN | UART_CNTL_MASK_2WIRE, P_UART_CONTROL(port_base));
    while(!(readl(P_UART_STATUS(port_base)) & UART_STAT_MASK_TFIFO_EMPTY));
    serial_reset_port(port_base);
#ifdef CONFIG_M3
	while((readl(P_UART_STATUS(port_base)) & (UART_STAT_MASK_XMIT_BUSY)));
#endif    
    serial_putc_port(port_base,'\n');
    return 0;
}

/*
 * Output a single byte to the serial port.
 */

static void serial_putc_port (unsigned port_base,const char c)
{
	if(!ucEnablePrint && port_base == UART_PORT_0)
	{
		return;
	}
	if (1 == console_state && c == '\n' && port_base == UART_PORT_0)
	{
        serial_putc_port(port_base,'\r');
	}

	if (0 == cmd_state && c == '\n' && port_base == UART_PORT_1)
	{
        serial_putc_port(port_base,'\r');
	}
    
    /* Wait till dataTx register is not full */
    while ((readl(P_UART_STATUS(port_base)) & UART_STAT_MASK_TFIFO_FULL));
    writel(c, P_UART_WFIFO(port_base));
    /* Wait till dataTx register is empty */
#if !defined (CONFIG_VLSI_EMULATOR)
    while(!(readl(P_UART_STATUS(port_base)) & UART_STAT_MASK_TFIFO_EMPTY));
#endif //CONFIG_VLSI_EMULATOR

}

/*
 * Read a single byte from the serial port. Returns 1 on success, 0
 * otherwise 0.
 */
static int serial_tstc_port (unsigned port_base)
{
	
	int i;

	i=(readl(P_UART_STATUS(port_base)) & UART_STAT_MASK_RFIFO_CNT);
	return i;

}

/*
 * Read a single byte from the serial port. 
 */
static int serial_getc_port (unsigned port_base)
{
    unsigned char ch;   
    
    /* Wait till character is placed in fifo */
  	while((readl(P_UART_STATUS(port_base)) & UART_STAT_MASK_RFIFO_CNT)==0) ;
  	ch = readl(P_UART_RFIFO(port_base)) & 0x00ff;
    /* Also check for overflow errors */
    if (readl(P_UART_STATUS(port_base)) & (UART_STAT_MASK_PRTY_ERR | UART_STAT_MASK_FRAM_ERR))
    {
    	writel(readl(P_UART_CONTROL(port_base)) | UART_CNTL_MASK_CLR_ERR,P_UART_CONTROL(port_base));//clear errors
        writel(readl(P_UART_CONTROL(port_base)) & (~UART_CNTL_MASK_CLR_ERR),P_UART_CONTROL(port_base));

    }
    

    return ((int)ch);

}

static void serial_puts_port (unsigned port_base,const char *s)
{
    while (*s) {
        serial_putc_port(port_base,*s++);
    }
}

#include <serial.h>
#define DECLARE_UART_FUNCTIONS(port) \
    static int  uart_##port##_init (void) {\
	serial_init_port(port);	return(0);}\
    static void uart_##port##_setbrg (void) {\
	serial_setbrg_port(port);}\
    static int  uart_##port##_getc (void) {\
	return serial_getc_port(port);}\
    static int  uart_##port##_tstc (void) {\
	return serial_tstc_port(port);}\
    static void uart_##port##_putc (const char c) {\
	serial_putc_port(port, c);}\
    static void uart_##port##_puts (const char *s) {\
	serial_puts_port(port, s);}


#define INIT_UART_STRUCTURE(port,name,bus) static struct serial_device device_##port={\
	name,\
	bus,\
	uart_##port##_init,\
	NULL,\
	uart_##port##_setbrg,\
	uart_##port##_getc,\
	uart_##port##_tstc,\
	uart_##port##_putc,\
	uart_##port##_puts, }

DECLARE_UART_FUNCTIONS(UART_PORT_0);
INIT_UART_STRUCTURE(UART_PORT_0,"uart0","UART0");
DECLARE_UART_FUNCTIONS(UART_PORT_1);
INIT_UART_STRUCTURE(UART_PORT_1,"uart1","UART1");
DECLARE_UART_FUNCTIONS(UART_PORT_2);
INIT_UART_STRUCTURE(UART_PORT_2,"uart2","UART2");

struct serial_device * default_serial_console (void)
{
#if (UART_PORT_CONS==UART_PORT_0)
    return &device_UART_PORT_0;
#elif (UART_PORT_CONS==UART_PORT_1)
    return &device_UART_PORT_1;
#elif (UART_PORT_CONS==UART_PORT_2)
    return &device_UART_PORT_2;

#endif    
}

void enable_uart_interrupt(unsigned port_base, unsigned type, unsigned on, unsigned trigger_size)
{
	if(UART_RX_TYPE == type)
	{
		if(on)
		{
			if(trigger_size==0 || trigger_size>0x7f)
			{
				trigger_size = DEF_RECV_IRQ_CNT;
			}
			writel(readl(P_UART_MISC(port_base))&(~UART_MISC_MASK_RECV_IRQ_CNT)|(UART_MISC_MASK_RECV_IRQ_CNT&trigger_size), P_UART_MISC(port_base));
			writel(readl(P_UART_CONTROL(port_base))|UART_CNTL_MASK_RINT_EN, P_UART_CONTROL(port_base));
		}
		else
		{
			writel(readl(P_UART_CONTROL(port_base))&(~UART_CNTL_MASK_RINT_EN), P_UART_CONTROL(port_base));
		}
	}
	else if(UART_TX_TYPE == type) 
	{
		if(on)
		{
			if(trigger_size==0 || trigger_size>0x7f)
			{
				trigger_size = DEF_XMIT_IRQ_CNT;
			}
			writel(readl(P_UART_MISC(port_base))&(~UART_MISC_MASK_XMIT_IRQ_CNT)|(UART_MISC_MASK_XMIT_IRQ_CNT&trigger_size), P_UART_MISC(port_base));
			writel(readl(P_UART_CONTROL(port_base))|UART_CNTL_MASK_TINT_EN, P_UART_CONTROL(port_base));
		}
		else
		{
			writel(readl(P_UART_CONTROL(port_base))&(~UART_CNTL_MASK_TINT_EN), P_UART_CONTROL(port_base));
		}
	}
	
	return;
}

void reset_uart(unsigned port_base, unsigned type) {
	if(UART_RX_TYPE == type)
	{
		writel(readl(P_UART_CONTROL(port_base)) | UART_CNTL_MASK_RST_RX | UART_CNTL_MASK_CLR_ERR, P_UART_CONTROL(port_base));
		writel(readl(P_UART_CONTROL(port_base)) & ~(UART_CNTL_MASK_RST_RX | UART_CNTL_MASK_CLR_ERR), P_UART_CONTROL(port_base));
	}
	else if(UART_TX_TYPE == type)
	{
		writel(readl(P_UART_CONTROL(port_base)) | UART_CNTL_MASK_RST_TX | UART_CNTL_MASK_CLR_ERR, P_UART_CONTROL(port_base));
		writel(readl(P_UART_CONTROL(port_base)) & ~(UART_CNTL_MASK_RST_TX | UART_CNTL_MASK_CLR_ERR), P_UART_CONTROL(port_base));
	}
	return;
}

int serial_init (unsigned index)
{
	if(0 == index)
	{
		device_UART_PORT_0.init();
	}
	else if(1 == index)
	{
		device_UART_PORT_1.init();
	}
	else if(2 == index)
	{
		device_UART_PORT_2.init();
	}
	return 0;

}

int serial_getc (void)
{
//#ifdef IN_FBC_MAIN_CONFIG
		if(!console_state)	return 0;
//#endif
	struct serial_device *dev = default_serial_console ();
	return dev->getc ();
}

int serial_tstc (void)
{
//#ifdef IN_FBC_MAIN_CONFIG
		if(!console_state)	return 0;
//#endif
	struct serial_device *dev = default_serial_console ();
	return dev->tstc ();
}

void serial_putc (const char c)
{
//#ifdef IN_FBC_MAIN_CONFIG
		if(!console_state)	return;
//#endif
	struct serial_device *dev = default_serial_console ();
	dev->putc (c);

}

void serial_puts (const char *s)
{
//#ifdef IN_FBC_MAIN_CONFIG
	if(!console_state)	return;
//#endif
	struct serial_device *dev = default_serial_console ();
	dev->puts (s);		

}

struct serial_device * get_serial_device(int index)
{
	if(index == 0)
	{
		return &device_UART_PORT_0;
	}
	else if(index == 1)
	{
		return &device_UART_PORT_1;
	}
	else if(index == 2)
	{
		return &device_UART_PORT_2;
	}
	return NULL;
}

