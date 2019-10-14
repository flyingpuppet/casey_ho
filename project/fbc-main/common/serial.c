/*
 *
 */
#include <serial.h>
#include <string.h>

extern void serial_aml_register(void);

static struct serial_device *serial_devices = NULL;
static struct serial_device *serial_current = NULL;

int serial_register (struct serial_device *dev)
{
	dev->next = serial_devices;
	serial_devices = dev;

	return 0;
}

void serial_initialize (void)
{
	serial_aml_register();
	serial_current = default_serial_console();
//	serial_assign (serial_current->name);
	serial_current->init();
}

void serial_stdio_init (void)
{
/*	struct stdio_dev dev;
	struct serial_device *s = serial_devices;

	while (s) {
		memset (&dev, 0, sizeof (dev));

		strcpy (dev.name, s->name);
		dev.flags = 0x00000002 | 0x00000001;

		dev.start = s->init;
		dev.stop = s->uninit;
		dev.putc = s->putc;
		dev.puts = s->puts;
		dev.getc = s->getc;
		dev.tstc = s->tstc;

		stdio_register (&dev);

		s = s->next;
	}*/
}

int serial_assign (char *name)
{
	struct serial_device *s;

	for (s = serial_devices; s; s = s->next) {
		if (strcmp (s->name, name) == 0) {
			serial_current = s;
			return 0;
		}
	}

	return 1;
}

void serial_reinit_all (void)
{
	struct serial_device *s;

	for (s = serial_devices; s; s = s->next) {
		s->init ();
	}
}

int serial_init (void)
{
	struct serial_device *dev = default_serial_console ();
	if (dev!=NULL) {
		return dev->init ();
		
	}

	return serial_current->init ();
}

void serial_setbrg (void)
{
	struct serial_device *dev = default_serial_console ();
	if (dev!=NULL) {
		dev->setbrg ();
		return;
	}

	serial_current->setbrg ();
}

int serial_getc (void)
{
	struct serial_device *dev = default_serial_console ();
	if (dev!=NULL) {
		return dev->getc ();
	}

	return serial_current->getc ();
}

int serial_tstc (void)
{
	struct serial_device *dev = default_serial_console ();
	if (dev!=NULL) {
		return dev->tstc ();
	}

	return serial_current->tstc ();
}

void serial_putc (const char c)
{
	struct serial_device *dev = default_serial_console ();
	if (dev!=NULL) {
		dev->putc (c);
		return;
	}

	serial_current->putc (c);
}

void serial_puts (const char *s)
{
	struct serial_device *dev = default_serial_console ();
	if (dev!=NULL) {
		dev->puts (s);
		return;
	}

	serial_current->puts (s);
}
