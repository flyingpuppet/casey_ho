#ifndef	__LOG__
#define __LOG__

#ifdef IN_FBC_MAIN_CONFIG

#ifndef NULL
#define NULL	0
#endif

#ifndef HAS_LOGCAT_FUNCTION
#define HAS_LOGCAT_FUNCTION		1
#endif

#define LOG_LEVEL_E		0x0
#define LOG_LEVEL_W		0x1
#define LOG_LEVEL_D		0x2
#define LOG_LEVEL_I		0x3
#define LOG_LEVEL_V		0x5
#define MAX_LOG_BUF_SIZE 4096
#define LINE_SIZE	128
#define TAG_SIZE	16
#define FILTER_SIZE	4
#define LOG_KEY		"logcat"
#define WILDCARD	"*"
#define SEPARATOR	" :  "

#define LOG_FLAG_WAKEUP	1

struct log_tag {
	int level;
	char tag[TAG_SIZE];
};

struct filter {
	unsigned count;
	struct log_tag tags[FILTER_SIZE];
};

typedef struct {
	unsigned int start_read_position;
	
	unsigned long read_cnt;
	unsigned long write_cnt;
	
	unsigned int wrap_cnt;
	unsigned int busy_flag;	
	
	unsigned read_index;
	unsigned write_index;
	
	char log_buf[MAX_LOG_BUF_SIZE];
}LOG_BUF_CTRL_T;

int log_print_to_buffer(int level, int flag, const char *tag, const char * __fmt, ...);

#define LOGI(TAG, ...)	log_print_to_buffer(LOG_LEVEL_I, LOG_FLAG_WAKEUP, TAG, __VA_ARGS__)
#define LOGD(TAG, ...)	log_print_to_buffer(LOG_LEVEL_D, LOG_FLAG_WAKEUP, TAG, __VA_ARGS__)
#define LOGW(TAG, ...)	log_print_to_buffer(LOG_LEVEL_W, LOG_FLAG_WAKEUP, TAG, __VA_ARGS__)
#define LOGE(TAG, ...)	log_print_to_buffer(LOG_LEVEL_E, LOG_FLAG_WAKEUP, TAG, __VA_ARGS__)
#define LOGV(TAG, ...)	log_print_to_buffer(LOG_LEVEL_V, LOG_FLAG_WAKEUP, TAG, __VA_ARGS__)

#define LOGI_NO_WAKEUP(TAG, ...)	log_print_to_buffer(LOG_LEVEL_I, 0, TAG, __VA_ARGS__)
#define LOGD_NO_WAKEUP(TAG, ...)	log_print_to_buffer(LOG_LEVEL_D, 0, TAG, __VA_ARGS__)
#define LOGW_NO_WAKEUP(TAG, ...)	log_print_to_buffer(LOG_LEVEL_W, 0, TAG, __VA_ARGS__)
#define LOGE_NO_WAKEUP(TAG, ...)	log_print_to_buffer(LOG_LEVEL_E, 0, TAG, __VA_ARGS__)
#define LOGV_NO_WAKEUP(TAG, ...)	log_print_to_buffer(LOG_LEVEL_V, 0, TAG, __VA_ARGS__)

#else

#define LOGI(TAG, ...)	((void)0)
#define LOGD(TAG, ...)	((void)0)
#define LOGW(TAG, ...)	((void)0)
#define LOGE(TAG, ...)	((void)0)
#define LOGV(TAG, ...)	((void)0)

#define LOGI_NO_WAKEUP(TAG, ...)	((void)0)
#define LOGD_NO_WAKEUP(TAG, ...)	((void)0)
#define LOGW_NO_WAKEUP(TAG, ...)	((void)0)
#define LOGE_NO_WAKEUP(TAG, ...)	((void)0)
#define LOGV_NO_WAKEUP(TAG, ...)	((void)0)

//#define printf(...) ((void)0)

#endif IN_FBC_MAIN_CONFIG
#endif __LOG__
