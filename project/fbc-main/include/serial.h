#ifndef __SERIAL_H__
#define __SERIAL_H__

#ifndef NULL
#define NULL 0
#endif

#define NAMESIZE 16
#define CTLRSIZE 8

struct serial_device {
	char name[NAMESIZE];
	char ctlr[CTLRSIZE];

	int  (*init) (void);
	int  (*uninit) (void);
	void (*setbrg) (void);
	int (*getc) (void);
	int (*tstc) (void);
	void (*putc) (const char c);
	void (*puts) (const char *s);
};

extern struct serial_device * default_serial_console (void);

int serial_init (unsigned index);
int serial_tstc (void);
int serial_getc (void);
void serial_putc (const char c);
void serial_puts (const char *s);
struct serial_device * get_serial_device(int index);


#endif
