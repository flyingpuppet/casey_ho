/*
*	This tool is used to generate audio control parameters' config file,  that is stored on spi.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define MAX_NAME_LEN				0x10
#define MAX_BUF_SIZE				300*0x400
#define CHECK_INFO_SIZE				0x20

#define COMPLETE_SPI_MAGIC			0x12345678
#define BOOT_SPI_MAGIC				0x11111111
#define MAIN_CODE_SPI_MAGIC			0x22222222
#define MAIN_DATA_SPI_MAGIC			0x33333333
#define MAIN_RODATA_SPI_MAGIC		0x44444444
#define MAIN_PARAM_SPI_MAGIC		0x55555555
#define MAIN_RSCODE_SPI_MAGIC		0x66666666

typedef struct {
	char name[MAX_NAME_LEN];
	unsigned int magic;
	unsigned int crc;
	unsigned int size;
	
} check_info_t;

typedef struct {
	char *type;
	unsigned magic;
} magic_t;

static magic_t w_magic[6] = {
	{"COMPLETE_BIN", COMPLETE_SPI_MAGIC},
	{"BOOT_BIN", BOOT_SPI_MAGIC},
	{"MAIN_CODE_BIN", MAIN_CODE_SPI_MAGIC},
	{"MAIN_DATA_BIN", MAIN_DATA_SPI_MAGIC},
	{"MAIN_RODATA_BIN", MAIN_RODATA_SPI_MAGIC},
	{"MAIN_PARAM_BIN", MAIN_PARAM_SPI_MAGIC},
	{"MAIN_RSCODE_BIN", MAIN_RSCODE_SPI_MAGIC},
};

static struct option long_options[] = {
	{"input", 1, NULL, 'i'},
	{"type", 1, NULL, 't'},
	{"output", 1, NULL, 'o'},
};
static char *optstring ="i:t:o:";

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
static unsigned int crc32(unsigned int crc, const unsigned char *ptr, unsigned int buf_len)
{
	static const unsigned int s_crc32[16] = { 
		0, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
  		0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
  		0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
  		0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c 
	};
	
  	unsigned int crcu32 = crc;
  
	if (!ptr) return 0;

	crcu32 = ~crcu32;
	while (buf_len--)
	{
	  	unsigned char b = *ptr++;
		crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b & 0xF)];
		crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b >> 4)];
	}
	
	return ~crcu32;
}

static void usage()
{
	return;
}

static unsigned get_magic(char *type)
{
	int i;

	if(!type) return COMPLETE_SPI_MAGIC;

	for(i = 0; i<sizeof(w_magic)/sizeof(magic_t); i++)
	{
		if(!strcasecmp(w_magic[i].type, type))
		{
			return w_magic[i].magic;
		}
	}

	return 0;
}

static void get_file_name(char *path, char *name)
{
	if(!path || !name) return;

	int len = strlen(path);
	int i = len -1;
	for(; i >= 0; i--)
	{
		if(path[i] == '/')
		{
			i++;
			break;
		}
	}

	strcpy(name, path+i);
	
	return;
}

int main(int argc, char **argv){

	int i, flag, val, magic;
	unsigned if_size = 0;
	unsigned of_size = 0;
	unsigned real_rc = 0;
	
	char *if_name = NULL;
	char *of_name = NULL;
	char *type = NULL;

	char bin_buf[MAX_BUF_SIZE];
	char ci_buf[CHECK_INFO_SIZE];
	
	FILE *out = NULL;
	FILE *in = NULL;

	check_info_t check_info;

	flag = 0;
	
	if(argc < 7)
	{
		flag = 1;
		goto EXT_1;
	}

	while((val = getopt_long(argc, argv, optstring, long_options, NULL)) != -1)
	{
		switch(val)
		{
			case 'i':
				if_name = optarg;
				break;
				
			case 't':
				type = optarg;
				break;
				
			case 'o':
				of_name = optarg;
				break;
		}
	}

	magic = get_magic(type);
//	printf("magic: 0x%x\n", magic);
	
//	printf("if_name: %s\n", if_name);
	in = fopen(if_name, "r");
	if(NULL == in)
	{
		printf("open %s failed!\n", if_name);
		goto EXT_0;
	}
	clearerr(in);
//	printf("of_name: %s\n", of_name);
	out = fopen(of_name, "wb");
	if(NULL == in)
	{
		printf("open %s failed!\n", of_name);
		goto EXT_2;
	}

	memset(bin_buf, 0, sizeof(bin_buf));
	memset(ci_buf, 0, sizeof(ci_buf));

	if(magic == COMPLETE_SPI_MAGIC)
	{
		real_rc = fread(bin_buf + CHECK_INFO_SIZE, MAX_BUF_SIZE - CHECK_INFO_SIZE, 1, in);
	}
	else
	{
		real_rc = fread(bin_buf, MAX_BUF_SIZE, 1, in);
	}
	
	if(real_rc < 1)
	{
		if(ferror(in))
		{
			printf("fread %s error.\n", if_name);
			goto EXT_3;
		}

		if_size = ftell(in);
		
	}
	
//	printf("if_size: %d\n", if_size);
	
	check_info.size = if_size;
	check_info.magic = magic;
//	get_file_name(of_name, check_info.name);

	if(check_info.magic != COMPLETE_SPI_MAGIC)
	{
		check_info.crc = crc32(0, bin_buf, if_size - CHECK_INFO_SIZE);
		of_size = if_size;
		memcpy(ci_buf, &check_info, sizeof(check_info_t));
		memcpy(bin_buf + if_size - CHECK_INFO_SIZE, ci_buf, sizeof(ci_buf));
		
	}
	else
	{
		check_info.crc = crc32(0, bin_buf + CHECK_INFO_SIZE, if_size);
		of_size = if_size + CHECK_INFO_SIZE;
		memcpy(ci_buf, &check_info, sizeof(check_info_t));
		memcpy(bin_buf, ci_buf, sizeof(ci_buf));
	}
	
	fwrite(bin_buf, of_size, 1, out);
	fflush(out);
		
EXT_3:
	fclose(out);
EXT_2:
	fclose(in);
EXT_1:
	if(flag) usage();
EXT_0:
	return 0;
}	

