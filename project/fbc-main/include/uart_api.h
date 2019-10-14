int uart_ports_open(unsigned uart_port_num);
int uart_ports_cloe(unsigned uart_port_num);
unsigned  uart_ports_read(unsigned uart_port_num, unsigned char *read_buf, unsigned length) ;
void uart_ports_write(unsigned uart_port_num, unsigned char *write_buf, unsigned length) ;
//0 disable;1 enable
void UartDebugEnable(unsigned char ucVal);
unsigned char GetUartDebugStatus(void);
//0 disable;1 enable
void Set_0a_to_0d0a_enable(unsigned char ucVal); 
//0 disable;1 enable
void uart_print_enable(unsigned char ucValue);
//0 disable;1 enable
void uart_console_hd_enable(unsigned char ucValue);
