/*
	This tool is used to generate system control parameters' config file,  that is stored on spi.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARAM_NAME				0xc

#define DEFAULT_IN_CONFIG_FILE		"sys_config"
#define DEFAULT_OUT_CONFIG_FILE		"sys_param"
#define MAX_LINE_BUF_SIZE			0x800

#define SYS_PARAM_HEADER_BASE_OFFSET	0x0
#define SYS_PARAM_HEADER_SIZE			0x800
#define SYS_PARAM_ENTITY_BASE_OFFSET	(SYS_PARAM_HEADER_BASE_OFFSET + SYS_PARAM_HEADER_SIZE)
#define SYS_PARAM_ENTITY_SIZE			0x1800
#define SYS_PARAM_AREA_SIZE				(SYS_PARAM_HEADER_SIZE + SYS_PARAM_ENTITY_SIZE)

typedef struct {
	char name[MAX_PARAM_NAME];
	unsigned short offset;
	unsigned short length;
	
} sys_param_header_t;


char param_buf[SYS_PARAM_AREA_SIZE];

static int fill_param_buffer(sys_param_header_t *s_param_h, unsigned h_offset, char *buf)
{
	if(!s_param_h || !buf)
	{
		printf("%s param error!\n", __func__);
		return -1;
	}
	
	char *p = param_buf + h_offset;
	
	memcpy(p, s_param_h, sizeof(sys_param_header_t));

	p = param_buf + s_param_h->offset;
	memcpy(p, buf, s_param_h->length);

	if(h_offset + sizeof(sys_param_header_t) >= SYS_PARAM_HEADER_SIZE)
	{
		printf("system parameter head structure exceeds the maximum size: %dKB!\n", SYS_PARAM_HEADER_SIZE);
		return -1;
	}
	
	return h_offset + sizeof(sys_param_header_t);
}

int main(int argc, char **argv){

	FILE *out = NULL;
	FILE *in = NULL;
	
	int len;
	int wr_next_hoffset;
	
	char name[MAX_PARAM_NAME] = {0,};
	char value[MAX_LINE_BUF_SIZE] = {0,};	
	char buf[MAX_LINE_BUF_SIZE] = {0,};
	
	sys_param_header_t s_param_h;
	
	if(argc < 2)
	{
		in = fopen(DEFAULT_IN_CONFIG_FILE, "r");
	}
	else
	{
		in = fopen(argv[1], "r");
	}

	if(NULL == in)
	{
		printf("open %s failed!\n", DEFAULT_IN_CONFIG_FILE);
		goto EXT_0;
	}
	
	out = fopen(DEFAULT_OUT_CONFIG_FILE, "wb");
	if(NULL == out)
	{
		printf("open %s failed!\n", DEFAULT_OUT_CONFIG_FILE);
		goto EXT_1;
	}

	s_param_h.offset = SYS_PARAM_ENTITY_BASE_OFFSET;
	
	wr_next_hoffset = SYS_PARAM_HEADER_BASE_OFFSET;

	memset(param_buf, 0, sizeof(param_buf));
	
	while(fgets(buf, MAX_LINE_BUF_SIZE, in))
	{
  		if(buf[0] == '#') 
		{
			memset(buf, 0, MAX_LINE_BUF_SIZE);
			continue;
		}

		int i, sep_count;
		for(i=0, sep_count=0; i<MAX_LINE_BUF_SIZE && buf[i]!='\0'; i++)
		{
			if(buf[i] == '\n')
			{
				buf[i] = '\0';
				break;
			}
			else if(sep_count < 2 && buf[i] == ',')
			{
				buf[i] = ' ';
				sep_count++;
			}
		}
		
		printf("buf: %s\n", buf);

		sscanf(buf, "%s %d %s", name, &len, value);
		printf("name: %s len: %d, value: %s\n", name, len, value);

		memcpy(s_param_h.name, name, MAX_PARAM_NAME);
		s_param_h.length = len;		
		wr_next_hoffset = fill_param_buffer(&s_param_h, wr_next_hoffset, value);
		
		if(wr_next_hoffset < 0) goto EXT_2;
		
		s_param_h.offset += s_param_h.length;
		
		memset(buf, 0, MAX_LINE_BUF_SIZE);
	}

	fwrite(param_buf, sizeof(param_buf), 1, out);
	fflush(out);

EXT_2:
	fclose(out);
EXT_1:
	fclose(in);
EXT_0:
	return 0;
}	

