#include <common.h>
#include <command.h>
#include <ctype.h>
#include <stdlib.h>
#include <serial.h>
#include <crc.h>

#define SPI_ADDR_START	0x40000000
#define SPI_ADDR_SIZE	0x8000000

static unsigned	dp_last_addr, dp_last_size;
static unsigned	dp_last_addr, dp_last_size;
static unsigned	dp_last_length = 0x40;

static unsigned base_address = 0;

int cmd_get_data_size(char* arg, int default_size)
{
	/* Check for a size specification .b, .w or .l.
	 */
	int len = strlen(arg);
	if (len > 2 && arg[len-2] == '.') {
		switch(arg[len-1]) {
		case 'b':
			return 1;
		case 'w':
			return 2;
		case 'l':
			return 4;
		case 's':
			return -2;
		default:
			return -1;
		}
	}
	return default_size;
}
void cmd_reg_bits_read(char* arg_addr,char* arg_bit, char* arg_width)
{
	unsigned int addr,bit,width,val;
	addr = strtoul(arg_addr, NULL, 16);
	bit = strtoul(arg_bit, NULL, 10);
	width = strtoul(arg_width, NULL, 10);
	val = *(volatile unsigned *)addr;
	val = (val>>bit)&((1L << width) - 1);
	printf("0x%08lx[%d,%d]:0x%x\n",addr,bit,width,val);
}
void cmd_reg_bits_write(char* arg_addr,char* arg_bit, char* arg_width,char* arg_val)
{
	unsigned int addr,bit,width,val,val_orig;
	addr = strtoul(arg_addr, NULL, 16);
	bit = strtoul(arg_bit, NULL, 10);
	width = strtoul(arg_width, NULL, 10);
	val = strtoul(arg_val, NULL, 16);
	val_orig = *(volatile unsigned *)addr;
	val = ((val_orig & ~(((1L<<width)-1)<<(bit))) | (val << bit));
	*(volatile unsigned *)addr = val;
}

#define MAX_LINE_LENGTH_BYTES (64)
#define DEFAULT_LINE_LENGTH_BYTES (16)
int print_buffer (unsigned addr, void* data, unsigned width, unsigned count, unsigned linelen)
{
	/* linebuf as a union causes proper alignment */
	union linebuf {
		unsigned ui[MAX_LINE_LENGTH_BYTES/sizeof(unsigned) + 1];
		unsigned short us[MAX_LINE_LENGTH_BYTES/sizeof(unsigned short) + 1];
		unsigned char uc[MAX_LINE_LENGTH_BYTES/sizeof(unsigned char) + 1];
	} lb;
	int i;

	if (linelen*width > MAX_LINE_LENGTH_BYTES)
		linelen = MAX_LINE_LENGTH_BYTES / width;
	if (linelen < 1)
		linelen = DEFAULT_LINE_LENGTH_BYTES / width;

	while (count) {
		printf("%08lx:", addr);

		/* check for overflow condition */
		if (count < linelen)
			linelen = count;

		/* Copy from memory into linebuf and print hex values */
		for (i = 0; i < linelen; i++) {
			unsigned x;
			if (width == 4)
				x = lb.ui[i] = *(volatile unsigned *)data;
			else if (width == 2)
				x = lb.us[i] = *(volatile unsigned short *)data;
			else
				x = lb.uc[i] = *(volatile unsigned char *)data;
			printf(" %0*x", width * 2, x);
			data =(char*)data + width;
		}

		/* Print data in ASCII characters */
		for (i = 0; i < linelen * width; i++) {
			if (!isprint(lb.uc[i]) || lb.uc[i] >= 0x80)
				lb.uc[i] = '.';
		}
		lb.uc[i] = '\0';
		printf("    %s\n", lb.uc);

		/* update references */
		addr += linelen * width;
		count -= linelen;

		if (ctrlc())
			return -1;
	}

	return 0;
}

/* Memory Display
 *
 * Syntax:
 *	md {addr} {len}
 */
#define DISP_LINE_LEN	16
int do_mem_md ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned addr, length;
	int	size;
	int rc = 0;

	/* We use the last specified parameters, unless new ones are
	 * entered.
	 */
	addr = dp_last_addr;
	size = dp_last_size;
	length = dp_last_length;

	if (argc < 2)
		return cmd_usage(cmdtp);

	if ((flag & CMD_FLAG_REPEAT) == 0) {
		/* New command specified.  Check for a size specification.
		 * Defaults to long if no or incorrect specification.
		 */
		if ((size = cmd_get_data_size(argv[0], 4)) < 0)
			return 1;
		/*add for bit read*/
		if(argv[1][0] == 's'){
			cmd_reg_bits_read(argv[2],argv[3],argv[4]);
			return rc;
		}
		/* Address is specified since argc > 1
		*/
		addr = strtoul(argv[1], NULL, 16);
		addr += base_address;

		/* If another parameter, it is the length to display.
		 * Length is the number of objects, not number of bytes.
		 */
		if (argc > 2)
			length = strtoul(argv[2], NULL, 16);
	}

	/* Print the lines. */
	print_buffer(addr, (void*)addr, size, length, DISP_LINE_LEN/size);
	addr += size*length;

	dp_last_addr = addr;
	dp_last_length = length;
	dp_last_size = size;
	return (rc);
}

int do_mem_mw ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned addr, writeval, count;
	int	size;

	if (argc < 3)
		return cmd_usage(cmdtp);

	/* Check for size specification.
	*/
	if ((size = cmd_get_data_size(argv[0], 4)) < 1)
		return 1;
	/*add for bit write*/
	if(argv[1][0] == 's'){
		cmd_reg_bits_write(argv[2],argv[3],argv[4],argv[5]);
		return 0;
	}

	/* Address is specified since argc > 1
	*/
	addr = strtoul(argv[1], NULL, 16);
	addr += base_address;

	/* Get the value to write.
	*/
	writeval = strtoul(argv[2], NULL, 16);

	/* Count ? */
	if (argc == 4) {
		count = strtoul(argv[3], NULL, 16);
	} else {
		count = 1;
	}

	while (count-- > 0) {
		if (size == 4)
			*((unsigned *)addr) = (unsigned)writeval;
		else if (size == 2)
			*((unsigned short *)addr) = (unsigned short)writeval;
		else
			*((unsigned char *)addr) = (unsigned char)writeval;
		addr += size;
	}
	return 0;
}

#ifdef IN_FBC_MAIN_CONFIG
static int addr_dataflash(unsigned addr)
{
	if(addr>=SPI_ADDR_START && addr<SPI_ADDR_START+SPI_ADDR_SIZE)
	{
		return 0;
	}

	return 1;
}

static int flash_write (char *src, unsigned addr, unsigned cnt)
{
	return 1;
}

int do_mem_cp ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned addr, dest, count;
	int	size;

	if (argc != 4)
		return cmd_usage(cmdtp);

	// Check for size specification.
	if ((size = cmd_get_data_size(argv[0], 4)) < 0)
		return 1;

	addr = strtoul(argv[1], NULL, 16);
	addr += base_address;

	dest = strtoul(argv[2], NULL, 16);
	dest += base_address;

	count = strtoul(argv[3], NULL, 16);

	if (count == 0) {
		serial_puts ("Zero length ???\n");
		return 1;
	}

	// check if we are copying to Flash
	if (!addr_dataflash(dest))
	{
		int rc;

		serial_puts ("Copy to Flash... ");

		rc = flash_write ((char *)addr, dest, count*size);
		if (rc != 0)
		{
//			flash_perror (rc);
			serial_puts ("Copy to Flash error! ");
			return (1);
		}
		serial_puts ("done\n");
		return 0;
	}

	while (count-- > 0) {
		if (size == 4)
			*((unsigned *)dest) = *((unsigned *)addr);
		else if (size == 2)
			*((unsigned short *)dest) = *((unsigned short *)addr);
		else
			*((unsigned char *)dest) = *((unsigned char *)addr);
		addr += size;
		dest += size;

		// reset watchdog from time to time
//		if ((count % (64 << 10)) == 0)
//			WATCHDOG_RESET();
	}
	return 0;
}

int do_mem_crc (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned addr, length;
	unsigned crc;
	unsigned *ptr;

	if (argc < 3)
		return cmd_usage(cmdtp);

	addr = strtoul(argv[1], NULL, 16);
	addr += base_address;

	length = strtoul(argv[2], NULL, 16);

	crc = crc32(0, (const unsigned char *) addr, length);

	printf ("CRC32 for %08lx ... %08lx ==> %08lx\n",
			addr, addr + length - 1, crc);

	if (argc > 3) {
		ptr = (unsigned *)strtoul(argv[3], NULL, 16);
		*ptr = crc;
	}

	return 0;
}

#endif
