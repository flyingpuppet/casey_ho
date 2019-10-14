#include <stdarg.h>
#include <serial.h>

#ifdef IN_FBC_MAIN_CONFIG
#ifndef MAX_CONSOLE_BUF_SIZE
#define MAX_CONSOLE_BUF_SIZE	1024
#endif
#else
#ifndef MAX_CONSOLE_BUF_SIZE
#define MAX_CONSOLE_BUF_SIZE	256
#endif
#endif

#ifndef CONFIG_SYS_MAXARGS
#define CONFIG_SYS_MAXARGS		10
#endif

#define TAG_VPP "VPP"
#define TAG_HDMIRX "HDMIRX"
#define TAG_VBY "VBYONE"

int printf(const char *__fmt, ...);
int printf_pq(const char *__fmt, ...);

extern void delay_us(int  us );
int readline (struct serial_device *dev, const char *const prompt);
int readline_into_buffer (struct serial_device *dev, const char *const prompt, char * buffer, int *len);
int parse_line (char *line, char *argv[]);
int debug_console(struct serial_device *dev);

#ifndef EXTEND_BUF_ADDR
#define EXTEND_BUF_ADDR			0x80020000
#endif

#ifndef EXTEND_BUF_SIZE
#define EXTEND_BUF_SIZE			0x8000
#endif

#ifdef IN_FBC_MAIN_CONFIG
int put_pq_data(unsigned port, char *buf, unsigned len);
int console_enable(void);
int console_disable(void);
#endif
