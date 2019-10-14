#include <common.h>
#include <command.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUF_SIZE_	0x10000

struct load_type {
	unsigned received_cnt;
	unsigned total;
	unsigned char *buf;
};

static int data_stream_read(struct load_type *type)
{
	unsigned i = 0;
	char c;
	
	if(!type) return -1;

	printf("total: %d, buf: 0x%x\n", type->total, type->buf);
	do
	{
		c = serial_getc();
		
		if(i < MAX_BUF_SIZE_)
		{
			printf("-->i = %d\n", i);
			type->buf[i] = c;
		}
		
		type->received_cnt++;
		if(i%256 == 0)
		{

			serial_putc('.');
			printf("i = %d\n", i);

		}
		
		if(MAX_BUF_SIZE_ - 1 == i || type->received_cnt == type->total)
		{
			serial_putc('\n');
			break;
		}		
				
		i++;
	}
	while(1);
	
	return type->received_cnt;
}
int do_test(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	printf("enter test!\n");
	printf("argc = %d\n", argc);
	unsigned addr;
	unsigned size;
	char *endp;
	struct load_type type;
	if(argc < 3) return -1;
	
	addr = strtoul(argv[1], &endp, 16);
	size = strtoul(argv[2], &endp, 16);
	
	type.buf = (unsigned char *)0x80020000;
	type.total = size;
	type.received_cnt = 0;
	
	printf("addr: 0x%x, size: 0x%x\n", addr, size);

	data_stream_read(&type);
	memcpy((void *)addr, type.buf, size);
	printf("over test!\n");
	return 0;
}
