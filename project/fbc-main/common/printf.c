#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>
#include <common.h>

#define CONFIG_SYS_PBSIZE 256

//#define USING_LIBC_VSPRINTF_FOR_PRINTF

#ifndef USING_LIBC_VSPRINTF_FOR_PRINTF

#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SMALL	32		/* Must be 32 == 0x20 */
#define SPECIAL	64		/* 0x */

#define NUM_TYPE long long

#define is_digit(c)	((c) >= '0' && (c) <= '9')

static unsigned int __div64_32(unsigned long long *n, unsigned int base)
{
	unsigned long long rem = *n;
	unsigned long long b = base;
	unsigned long long res, d = 1;
	unsigned long long high = rem >> 32;

	/* Reduce the thing a bit first */
	res = 0;
	if (high >= base) {
		high /= base;
		res = (unsigned long long) high << 32;
		rem -= (unsigned long long) (high*base) << 32;
	}

	while ((long long)b > 0 && b < rem) {
		b = b+b;
		d = d+d;
	}

	do {
		if (rem >= b) {
			rem -= b;
			res += d;
		}
		b >>= 1;
		d >>= 1;
	} while (d);

	*n = res;
	return rem;
}

#define do_div(n,base) ({				\
	unsigned int __base = (base);			\
	unsigned int __rem;					\
	(void)(((typeof((n)) *)0) == ((unsigned long long *)0));	\
	if (((n) >> 32) == 0) {			\
		__rem = (unsigned int)(n) % __base;		\
		(n) = (unsigned int)(n) / __base;		\
	} else						\
		__rem = __div64_32(&(n), __base);	\
	__rem;						\
 })

static char* put_dec_trunc(char *buf, unsigned q)
{
	unsigned d3, d2, d1, d0;
	d1 = (q>>4) & 0xf;
	d2 = (q>>8) & 0xf;
	d3 = (q>>12);

	d0 = 6*(d3 + d2 + d1) + (q & 0xf);
	q = (d0 * 0xcd) >> 11;
	d0 = d0 - 10*q;
	*buf++ = d0 + '0'; /* least significant digit */
	d1 = q + 9*d3 + 5*d2 + d1;
	if (d1 != 0) {
		q = (d1 * 0xcd) >> 11;
		d1 = d1 - 10*q;
		*buf++ = d1 + '0'; /* next digit */
		d2 = q + 2*d2;
		if ((d2 != 0) || (d3 != 0)) {
			q = (d2 * 0xd) >> 7;
			d2 = d2 - 10*q;
			*buf++ = d2 + '0'; /* next digit */

			d3 = q + 4*d3;
			if (d3 != 0) {
				q = (d3 * 0xcd) >> 11;
				d3 = d3 - 10*q;
				*buf++ = d3 + '0';  /* next digit */
				if (q != 0)
					*buf++ = q + '0';  /* most sign. digit */
			}
		}
	}
	return buf;
}

/* Same with if's removed. Always emits five digits */
static char* put_dec_full(char *buf, unsigned q)
{
	/* BTW, if q is in [0,9999], 8-bit ints will be enough, */
	/* but anyway, gcc produces better code with full-sized ints */
	unsigned d3, d2, d1, d0;
	d1 = (q>>4) & 0xf;
	d2 = (q>>8) & 0xf;
	d3 = (q>>12);

	/*
	 * Possible ways to approx. divide by 10
	 * gcc -O2 replaces multiply with shifts and adds
	 * (x * 0xcd) >> 11: 11001101 - shorter code than * 0x67 (on i386)
	 * (x * 0x67) >> 10:  1100111
	 * (x * 0x34) >> 9:    110100 - same
	 * (x * 0x1a) >> 8:     11010 - same
	 * (x * 0x0d) >> 7:      1101 - same, shortest code (on i386)
	 */

	d0 = 6*(d3 + d2 + d1) + (q & 0xf);
	q = (d0 * 0xcd) >> 11;
	d0 = d0 - 10*q;
	*buf++ = d0 + '0';
	d1 = q + 9*d3 + 5*d2 + d1;
	q = (d1 * 0xcd) >> 11;
	d1 = d1 - 10*q;
	*buf++ = d1 + '0';

	d2 = q + 2*d2;
	q = (d2 * 0xd) >> 7;
	d2 = d2 - 10*q;
	*buf++ = d2 + '0';

	d3 = q + 4*d3;
	q = (d3 * 0xcd) >> 11; /* - shorter code */
	/* q = (d3 * 0x67) >> 10; - would also work */
	d3 = d3 - 10*q;
	*buf++ = d3 + '0';
	*buf++ = q + '0';
	return buf;
}

static char* put_dec(char *buf, unsigned NUM_TYPE num)
{
	while (1) {
		unsigned rem;
		if (num < 100000)
			return put_dec_trunc(buf, (unsigned)num);
		rem = do_div(num, 100000);
		buf = put_dec_full(buf, rem);
	}
}

static char *number(char *buf, unsigned NUM_TYPE num, int base, int size, int precision, int type)
{
	/* we are called with base 8, 10 or 16, only, thus don't need "G..."  */
	static const char digits[16] = "0123456789ABCDEF"; /* "GHIJKLMNOPQRSTUVWXYZ"; */

	char tmp[66];
	char sign;
	char locase;
	int need_pfx = ((type & SPECIAL) && base != 10);
	int i;

	/* locase = 0 or 0x20. ORing digits or letters with 'locase'
	 * produces same digits or (maybe lowercased) letters */
	locase = (type & SMALL);
	if (type & LEFT)
		type &= ~ZEROPAD;
	sign = 0;
	if (type & SIGN) {
		if ((signed NUM_TYPE) num < 0) {
			sign = '-';
			num = - (signed NUM_TYPE) num;
			size--;
		} else if (type & PLUS) {
			sign = '+';
			size--;
		} else if (type & SPACE) {
			sign = ' ';
			size--;
		}
	}
	if (need_pfx) {
		size--;
		if (base == 16)
			size--;
	}

	/* generate full string in tmp[], in reverse order */
	i = 0;
	if (num == 0) {
		tmp[i++] = '0';
	} else if (base != 10) { /* 8 or 16 */
		int mask = base - 1;
		int shift = 3;
		if (base == 16) shift = 4;
		do {
			tmp[i++] = (digits[((unsigned char)num) & mask] | locase);
			num >>= shift;
		} while (num);
	} else { /* base 10 */
		i = put_dec(tmp, num) - tmp;
	}
	/* printing 100 using %2d gives "100", not "00" */
	if (i > precision)
		precision = i;
	/* leading space padding */
	size -= precision;
	if (!(type & (ZEROPAD+LEFT)))
		while(--size >= 0)
			*buf++ = ' ';
	/* sign */
	if (sign)
		*buf++ = sign;
	/* "0x" / "0" prefix */
	if (need_pfx) {
		*buf++ = '0';
		if (base == 16)
			*buf++ = ('X' | locase);
	}
	/* zero or space padding */
	if (!(type & LEFT)) {
		char c = (type & ZEROPAD) ? '0' : ' ';
		while (--size >= 0)
			*buf++ = c;
	}
	/* hmm even more zero padding? */
	while (i <= --precision)
		*buf++ = '0';
	/* actual digits of result */
	while (--i >= 0)
		*buf++ = tmp[i];
	/* trailing space padding */
	while (--size >= 0)
		*buf++ = ' ';
	return buf;
}

static int skip_atoi(const char **s)
{
	int i=0;

	while (is_digit(**s))
		i = i*10 + *((*s)++) - '0';
	return i;
}

static unsigned int strnlen(const char * s, unsigned int count)
{
	const char *sc;

	for (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

static char *string(char *buf, char *s, int field_width, int precision, int flags)
{
	int len, i;

	if (s == 0)
		s = "<NULL>";

	len = strnlen(s, precision);

	if (!(flags & LEFT))
		while (len < field_width--)
			*buf++ = ' ';
	for (i = 0; i < len; ++i)
		*buf++ = *s++;
	while (len < field_width--)
		*buf++ = ' ';
	return buf;
}

static char *pointer(const char *fmt, char *buf, void *ptr, int field_width, int precision, int flags)
{
	if (!ptr)
		return string(buf, "(null)", field_width, precision, flags);

	flags |= SMALL;
	if (field_width == -1) {
		field_width = 2*sizeof(void *);
		flags |= ZEROPAD;
	}
	return number(buf, (unsigned NUM_TYPE) ptr, 16, field_width, precision, flags);
}

extern "C" int vsprintf(char *buf, const char *fmt, va_list args)
{
	unsigned NUM_TYPE num;
	int base;
	char *str;

	int flags;		/* flags to number() */

	int field_width;	/* width of output field */
	int precision;		/* min. # of digits for integers; max
				   number of chars for from string */
	int qualifier;		/* 'h', 'l', or 'L' for integer fields */
				/* 'z' support added 23/7/1999 S.H.    */
				/* 'z' changed to 'Z' --davidm 1/25/99 */
				/* 't' added for ptrdiff_t */

	str = buf;
	for (; *fmt ; ++fmt) {
		if (*fmt != '%') {
			*str++ = *fmt;
			continue;
		}

		/* process flags */
		flags = 0;
		repeat:
			++fmt;		/* this also skips first '%' */
			switch (*fmt) {
				case '-': flags |= LEFT; goto repeat;
				case '+': flags |= PLUS; goto repeat;
				case ' ': flags |= SPACE; goto repeat;
				case '#': flags |= SPECIAL; goto repeat;
				case '0': flags |= ZEROPAD; goto repeat;
			}

		/* get field width */
		field_width = -1;
		if (is_digit(*fmt))
			field_width = skip_atoi(&fmt);
		else if (*fmt == '*') {
			++fmt;
			/* it's the next argument */
			field_width = va_arg(args, int);
			if (field_width < 0) {
				field_width = -field_width;
				flags |= LEFT;
			}
		}

		/* get the precision */
		precision = -1;
		if (*fmt == '.') {
			++fmt;
			if (is_digit(*fmt))
				precision = skip_atoi(&fmt);
			else if (*fmt == '*') {
				++fmt;
				/* it's the next argument */
				precision = va_arg(args, int);
			}
			if (precision < 0)
				precision = 0;
		}

		/* get the conversion qualifier */
		qualifier = -1;
		if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L' ||
		    *fmt == 'Z' || *fmt == 'z' || *fmt == 't') {
			qualifier = *fmt;
			++fmt;
			if (qualifier == 'l' && *fmt == 'l') {
				qualifier = 'L';
				++fmt;
			}
		}

		/* default base */
		base = 10;
		switch (*fmt) {
		case 'c':
			if (!(flags & LEFT))
				while (--field_width > 0)
					*str++ = ' ';
			*str++ = (unsigned char) va_arg(args, int);
			while (--field_width > 0)
				*str++ = ' ';
			continue;

		case 's':
			str = string(str, va_arg(args, char *), field_width, precision, flags);
			continue;

		case 'p':
			str = pointer(fmt+1, str,
					va_arg(args, void *),
					field_width, precision, flags);
			/* Skip all alphanumeric pointer suffixes */
			while (isalnum(fmt[1]))
				fmt++;
			continue;

		case 'n':
			if (qualifier == 'l') {
				long * ip = va_arg(args, long *);
				*ip = (str - buf);
			} else {
				int * ip = va_arg(args, int *);
				*ip = (str - buf);
			}
			continue;

		case '%':
			*str++ = '%';
			continue;

		/* integer number formats - set up the flags and "break" */
		case 'o':
			base = 8;
			break;

		case 'x':
			flags |= SMALL;
		case 'X':
			base = 16;
			break;

		case 'd':
		case 'i':
			flags |= SIGN;
		case 'u':
			break;

		default:
			*str++ = '%';
			if (*fmt)
				*str++ = *fmt;
			else
				--fmt;
			continue;
		}
		if (qualifier == 'L')  /* "quad" for 64 bit variables */
			num = va_arg(args, unsigned long long);
		else if (qualifier == 'l') {
			num = va_arg(args, unsigned long);
			if (flags & SIGN)
				num = (signed long) num;
		} else if (qualifier == 'Z' || qualifier == 'z') {
			num = va_arg(args, unsigned int);
		} else if (qualifier == 't') {
			num = va_arg(args, unsigned long);
		} else if (qualifier == 'h') {
			num = (unsigned short) va_arg(args, int);
			if (flags & SIGN)
				num = (signed short) num;
		} else {
			num = va_arg(args, unsigned int);
			if (flags & SIGN){
				num = (signed int) num;
			}
		}
		str = number(str, num, base, field_width, precision, flags);
	}
	*str = '\0';
	return str-buf;

}
#endif // USING_LIBC_VSPRINTF_FOR_PRINTF

#ifndef	_IN_DEBUG_MODE_
extern "C" int printf(const char *__fmt, ...)
{
	va_list args;
	unsigned int i;
	char printbuffer[CONFIG_SYS_PBSIZE];
	va_start(args, __fmt);
	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf(printbuffer, __fmt, args);
	va_end(args);
	/* Print the string */
	serial_puts(printbuffer);
	return i;
}

extern "C" int sprintf(char * buffer, const char *__fmt, ...)
{
	va_list args;
	unsigned int i;
	va_start(args, __fmt);
	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf(buffer, __fmt, args);
	va_end(args);
	/* Print the string */
	//serial_puts(printbuffer);
	return i;
}

extern "C" int printf_pq(const char *__fmt, ...)
{
	va_list args;
	unsigned int i;
	char *printbuffer = (char *)EXTEND_BUF_ADDR;
	va_start(args, __fmt);
	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf(printbuffer, __fmt, args);
	va_end(args);
	/* Print the string */
	serial_puts(printbuffer);
	return i;
}
struct serial_device *s_dev;
extern "C" int printf2(const char *__fmt, ...)
{
	va_list args;
	unsigned int i;
	char printbuffer[CONFIG_SYS_PBSIZE];
	va_start(args, __fmt);
	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf(printbuffer, __fmt, args);
	va_end(args);
	/* Print the string */
	s_dev->puts(printbuffer);
	return i;
}

extern "C" int puts(const char *__s)
{
    return printf("%s\n", __s);
}
#endif