#include <log.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <command.h>
#include <common.h>
#include <task.h>
#include <timer.h>
#include <task_priority.h>


#ifndef __DEBUG__
//#define __DEBUG__
#endif

static struct filter myfilter;
static const char *options[2] = {"-c", "-s"};
int LogcatTaskID = -1;
int LogcatRunFlag = 0;
static LOG_BUF_CTRL_T log_buf_ctl;

extern int ctrlc_flag;
extern int vsprintf(char *buf, const char *fmt, va_list args);

#ifdef __DEBUG__
static int debug(int max)
{
	int i;
	for(i=0; i<max; i++)
	{
		switch(i%5)
		{
			case 0:
				LOGI("TAG", "in case 0 i = %d", i);
				break;
			case 1:
				LOGW("TAG", "in case 0 i = %d", i);
				break;
			case 2:
				LOGD("TAG", "in case 0 i = %d", i);
				break;
			case 3:
				LOGV("TAG", "in case 0 i = %d", i);
				break;
			case 4:
				LOGE("TAG", "in case 0 i = %d", i);
				break;
		} 
	}
}

static void print_log_buf_info()
{
	printf("======> log_buf info <======\n");
	printf("log_buf.read_index = %d\n", log_buf_ctl.read_index);
	printf("log_buf.read_index = %d\n", log_buf_ctl.write_index);
	printf("log_buf.wrap_cnt = %d\n", log_buf_ctl.wrap_cnt);
	printf("============================\n\n");
}

static void print_filter_info()
{
	int i;
	printf("======> myfilter info <======\n");
	for(i=0; i<myfilter.count; i++)
	{
		printf("tags[%d] ---- level = %d, tag:%s\n", i, myfilter.tags[i].level, myfilter.tags[i].tag);
	}
	printf("=============================\n\n");
}

static void test()
{
	int max = 15;
	print_log_buf_info();
	debug(max);
	int i;
	char buf[64];
	print_log_buf_info();
	
	for(i=0; read_log_buf(buf) != -1; i++)
	{
		printf(buf);
	}
	printf("----------------> i = %d <----------------\n", i);
	print_log_buf_info();
}
#endif

static int buf_is_empty()
{
	if((log_buf_ctl.write_index==log_buf_ctl.read_index)&&(log_buf_ctl.wrap_cnt==0))
	{
		return 1;
	}
	return 0;
}

static int read_log_buf(char *buf)
{
	int i;
	if(!buf || buf_is_empty())
	{
		return -1;
	}

	for(i=0; !buf_is_empty(); i++)
	{
		buf[i] = log_buf_ctl.log_buf[log_buf_ctl.read_index++];

		if(log_buf_ctl.read_index == MAX_LOG_BUF_SIZE)
		{
			log_buf_ctl.read_index = log_buf_ctl.read_index % MAX_LOG_BUF_SIZE;
			log_buf_ctl.wrap_cnt -= 1;
		}
		if(buf[i]=='\n')
		{
#ifdef __DEBUG__
			printf("In read_log_buf  i = %d\n", i);
#endif
			break;
		}
	}
	buf[i+1] = 0;

#ifdef __DEBUG__
	printf("In read_log_buf buf: %s", buf);
	printf("In read_log_buf log_buf_ctl.read_index = %d\n", log_buf_ctl.read_index);
#endif

	log_buf_ctl.read_cnt += i;
	return i;
}

static int write_log_buf(const char *buf)
{
	int len, i;
	if(!buf)
	{
		return -1;
	}

	len = strlen(buf);
	
#ifdef __DEBUG__
	printf("In write_log_buf buf:%s", buf);
	printf("In write_log_buf len:%d\n", len);
#endif

	for(i=0; i<len; i++)
	{
		log_buf_ctl.write_cnt += len;
		log_buf_ctl.log_buf[log_buf_ctl.write_index++] = buf[i];
		if(log_buf_ctl.write_index == MAX_LOG_BUF_SIZE)
		{
			log_buf_ctl.write_index = log_buf_ctl.write_index % MAX_LOG_BUF_SIZE;
			log_buf_ctl.wrap_cnt += 1;
		}
		
	}

	if(log_buf_ctl.wrap_cnt>0 && log_buf_ctl.write_index>log_buf_ctl.start_read_position)
	{
		log_buf_ctl.start_read_position = log_buf_ctl.write_index;
		if(log_buf_ctl.start_read_position > log_buf_ctl.read_index)
		{
			log_buf_ctl.read_index = log_buf_ctl.start_read_position;
		}
	}
	return len;
}

static int get_log_level(char s)
{
	if(s == 'E')
	{
		return LOG_LEVEL_E;
	}
	else if(s == 'W')
	{
		return LOG_LEVEL_W;
	}
	else if(s == 'I')
	{
		return LOG_LEVEL_I;
	}
	else if(s == 'D')
	{
		return LOG_LEVEL_D;
	}
	else
	{
		return LOG_LEVEL_V;
	}
}

static int filter(const char *str)
{
	int i, lev;
	lev = get_log_level(str[0]);
	
#ifdef __DEBUG__
	print_filter_info();
	printf("In filter lev = %d\n", lev);
	printf("In filter str:%s", str);
#endif

	char *p = strstr(str, SEPARATOR);
	char obj_tag[TAG_SIZE];

	if(p == str+2)
	{
#ifdef __DEBUG__
		printf("In filter p:%s", p);
#endif

		for(i=0; i<myfilter.count; i++)
		{
			if(lev<=myfilter.tags[i].level)
			{
				return 0;
			}
		}
		return -1;
	}
	
	for(i=0; str+2+i<p; i++)
	{
		obj_tag[i] = str[i+2];
	}
	obj_tag[i] = '\0';
	
#ifdef __DEBUG__
	printf("In filter obj_tag:%s<-\n", obj_tag);
#endif

	for(i=0; i<myfilter.count; i++)
	{
		if(!strcmp(myfilter.tags[i].tag, WILDCARD) && lev<=myfilter.tags[i].level)
		{
			return 0;
		}
		
		if(!strcmp(obj_tag, myfilter.tags[i].tag) && lev<=myfilter.tags[i].level)
		{
			return 0;
		}
	}
	
	return -2;
}

int print_log_buffer()
{
	char tmp[LINE_SIZE];
	for(;!ctrlc_flag && read_log_buf(tmp)!=-1;)
	{
		int ret;
		ret = filter(tmp);
#ifdef __DEBUG__
		printf("In print_log_buffer ret = %d\n", ret);
		printf(">%s\n", tmp);
		printf("filter(tmp) = %d\n", filter(tmp));
#endif
		
		if(!ret)
		{
			serial_puts(tmp);
		}
	}
	
	return 0;
}

int do_log_out ( cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{	
	int i;
	if(argc == 1)
	{
		myfilter.count = 1;
		myfilter.tags[0].level = LOG_LEVEL_V;
		strcpy(myfilter.tags[0].tag, WILDCARD);
		
	} else {
		for(i=1; i<argc; i++)
		{
			if(i==1 && !strcmp(argv[i],options[0]))	//process -c option
			{
				myfilter.count = 0;
				log_buf_ctl.read_index = 0;
				log_buf_ctl.write_index = 0;
				log_buf_ctl.start_read_position = 0;
				break;
			}

			if(i==1 && !strcmp(argv[i],options[1]))	//process -s option
			{
				int j,n;
				char *p;
				myfilter.count = 0;
				for(n=0,j=i+1; j<argc && n<FILTER_SIZE; j++,n++)
				{
					myfilter.count++;
					p = strchr(argv[j], ':');
					if(p == NULL)
					{
						myfilter.tags[n].level = LOG_LEVEL_V;
						
						if(argv[j][0] != 0)
						{
							strcpy(myfilter.tags[n].tag, argv[j]);
						} 
						else 
						{
							strcpy(myfilter.tags[n].tag, WILDCARD);
						}
						
					} else {
						if(p-argv[j]+1 < strlen(argv[j]))
						{
							myfilter.tags[n].level = get_log_level(*(p+1));
						}
						else
						{
							myfilter.tags[n].level  = LOG_LEVEL_V;
						}

						if(argv[j][0] != ':')
						{
							*p = 0;
							strcpy(myfilter.tags[n].tag, argv[j]);
						} 
						else 
						{
							strcpy(myfilter.tags[n].tag, WILDCARD);
						}
					}
				}				
			}
		}
	}

#ifdef __DEBUG__
	print_filter_info();
#endif

	if(myfilter.count)
	{
		LogcatRunFlag = 1;
		log_buf_ctl.read_index = log_buf_ctl.start_read_position;
		if (LogcatTaskID>0) 
			WakeupTaskByID(LogcatTaskID);
	}
	else
	{
		LogcatRunFlag = 0;
	}
		
	return 0;
}

static int LogcatHandler(int task_id, void *param)
{
#ifdef __DEBUG__
	printf("Enter LogcatHandler LogcatRunFlag = %d, ctrlc_flag = %d\n", LogcatRunFlag, ctrlc_flag);
#endif __DEBUG__

	if(LogcatRunFlag)
	{
		print_log_buffer();
	}
	if(ctrlc_flag)
	{
		ctrlc_flag = 0;
	}
	return 0;
}

int log_print_to_buffer(int level, int flag, const char *tag, const char * __fmt, ...)
{
	va_list args;
	unsigned int i, len = 0;
	char s;

	if(level == LOG_LEVEL_E)
	{
		s = 'E';
	}
	else if(level == LOG_LEVEL_W)
	{
		s = 'W';
	}
	else if(level == LOG_LEVEL_D)
	{
		s = 'D';
	}
	else if(level == LOG_LEVEL_I)
	{
		s = 'I';
	}
	else
	{
		s = 'V';
	}
	
	char printbuffer[128];
	printbuffer[len++] = s;
	printbuffer[len++] = '/';
	if(tag != NULL && tag[0]!=0)
	{
		strcpy(printbuffer+len, tag);
		len = strlen(printbuffer);
	}
	strcpy(printbuffer+len, SEPARATOR);
	len = strlen(printbuffer);
	
	_itoa(OSTimeGet(), printbuffer+len, 10);
	len = strlen(printbuffer);
	printbuffer[len++] = ' ';

	va_start(args, __fmt);
	vsprintf(printbuffer+len, __fmt, args);
	va_end(args);

	for(i=0; printbuffer[i]!=0; i++);
	if ((i>0)&&(printbuffer[i-1]!='\n'))
		printbuffer[i++] = '\n';
	printbuffer[i] = 0;

	write_log_buf(printbuffer);
	if ((LogcatTaskID>0)&&(flag&LOG_FLAG_WAKEUP))
		WakeupTaskByID(LogcatTaskID);
	return 0;
}

int init_log(vold)
{
	printf("Enter init_log\n");
	
#ifdef __DEBUG__
	debug(15);
#endif

	LogcatTaskID = RegisterTask(LogcatHandler, NULL, 0, TASK_PRIORITY_LOG);
	return LogcatTaskID;
//	return request_timer(LogcatTaskID, 2);//10ms interrupt
}

