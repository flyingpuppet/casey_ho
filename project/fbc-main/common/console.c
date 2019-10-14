#include <common.h>
#include <string.h>
#include <uart_api.h>

static const char erase_seq[] = "\b \b";        /* erase sequence   */
static const char   tab_seq[] = "        ";     /* used to expand TABs  */

int console_buffer_len;
char new_line_flag = 1;
int ctrlc_flag = 0;
int cmd_completion_flag = 0;
extern unsigned char console_state;

#ifdef IN_FBC_MAIN_CONFIG
int pq_cmd_flag = 0;
int del_char_flag = 0;
int first_sep_index = -1;

#define GAMMA_CMD		"gamma"
#define GAMMA_CMD_NLEN	0x5
#define DEMURA_CMD		"demura"
#define DEMURA_CMD_NLEN	0x6

int put_pq_data(unsigned port, char *buf, unsigned len)
{
	int i;
	
	if(port > 2 || !buf || len == 0) return -1;

	struct serial_device *sd = get_serial_device(port);

	if(!sd) return -1;

	for(i = 0; i < len; i++)
	{
		sd->putc(buf[i]);
	}

	return len;
}

static int is_not_pq_cmd(char *cmd, int len)
{
	if(!cmd) return 1;

	switch(len)
	{
		case GAMMA_CMD_NLEN:
			return strncmp(GAMMA_CMD, cmd, len);
			
		case DEMURA_CMD_NLEN:
			return strncmp(DEMURA_CMD, cmd, len);
	}
	return 1;
}

#endif

char IRQ_MODE = 0;

char console_buffer[MAX_CONSOLE_BUF_SIZE];
char lastcommand[MAX_CONSOLE_BUF_SIZE] = { 0, };

/****************************************************************************/

static char * delete_char (struct serial_device *dev, char *buffer, char *p, int *colp, int *np, int plen)
{
    char *s;

    if (*np == 0) {
        return (p);
    }

    if (*(--p) == '\t') {           /* will retype the whole line   */
        while (*colp > plen) {
            dev->puts (erase_seq);
            (*colp)--;
        }
        for (s=buffer; s<p; ++s) {
            if (*s == '\t') {
                dev->puts (tab_seq+((*colp) & 07));
                *colp += 8 - ((*colp) & 07);
            } else {
                ++(*colp);
                dev->putc (*s);
            }
        }
    } else {
        dev->puts (erase_seq);
        (*colp)--;
    }
    (*np)--;
	
#ifdef IN_FBC_MAIN_CONFIG
	if(pq_cmd_flag)
		del_char_flag = 1;
#endif
    return (p);
}

/*
 * Prompt for input and read a line.
 * Return:      number of read characters
 *              -1 if break
 */
int readline (struct serial_device *dev, const char *const prompt)
{
	int rc;

	 /*
	   * If console_buffer isn't 0-length the user will be prompted to modify
	   * it instead of entering it from scratch as desired.
	   */
	if (new_line_flag){
		console_buffer[0] = '\0';
		console_buffer_len = 0;
	}

	rc = readline_into_buffer(dev, prompt, console_buffer, &console_buffer_len);
	if (rc == -1){
		console_buffer[0] = '\0';
		console_buffer_len = 0;
	}
#ifdef IN_FBC_MAIN_CONFIG
//	console_buffer[1023] = '\0';
//	printf("console_buffer: %s\n", console_buffer);
#endif
	return rc; 
}

int readline_into_buffer (struct serial_device *dev, const char *const prompt, char * buffer, int *len)
{
    char *p = buffer;
    char *p_buf = buffer;
    int n = *len;           /* buffer index     */
    int plen = 0;           /* prompt length    */

#ifdef IN_FBC_MAIN_CONFIG
	int first_space_flag = 0;
	if(pq_cmd_flag)
	{
		p = (char *)EXTEND_BUF_ADDR;
		p_buf = (char *)EXTEND_BUF_ADDR;
		first_space_flag = 1;
	}
#endif

    int col;                /* output column cnt    */
    char c;

    /* print prompt */
    if (prompt) {
        plen = strlen (prompt);
	    if (n == 0){
	        if (prompt && !IRQ_MODE) {
	            dev->puts (prompt);
	        }
	        col = plen;
	    }
	    else{
	        col = plen + n;
	        p += n;
	    }
  	}

    for (;;) {
#ifdef IN_FBC_MAIN_CONFIG
		if(IRQ_MODE && console_state && uart_ports_read(0, (unsigned char *)&c, 0x1)==0)	//for irq mode
		{
			*len = p - p_buf;
			return -2;
		}
#else		
        c = dev->getc();
#endif

        /*
         	* Special character handling
         	*/
        switch (c) {
        case '\r':              /* Enter        */
        case '\n':
            *p = '\0';
            dev->puts ("\r\n");
            *len = p - p_buf;
            return (p - p_buf);

        case '\0':              /* null          */
            continue;

        case 0x03:              /* ^C - break       */
            p_buf[0] = '\0';    /* discard input */
            *len = 0;
            return (-1);

        case 0x15:              /* ^U - erase line  */
            while (col > plen) {
                dev->puts (erase_seq);
                --col;
            }
            p = p_buf;
            n = 0;
            continue;

        case 0x17:              /* ^W - erase word  */
            p = delete_char(dev, p_buf, p, &col, &n, plen);
            while ((n > 0) && (*p != ' ')) {
                p = delete_char(dev, p_buf, p, &col, &n, plen);
            }
			
#ifdef IN_FBC_MAIN_CONFIG
			if(del_char_flag)
			{
				del_char_flag = 0;
				if(first_sep_index > n)
				{
					pq_cmd_flag = 0;
					first_sep_index = -1;
					first_space_flag = 0;
					char *tmp = p_buf;						
					p_buf = buffer;
					p = p_buf + n;
					strncpy(p_buf, tmp, n);
				}
			}
#endif
            continue;

        case 0x08:              /* ^H  - backspace  */
        case 0x7F:              /* DEL - backspace  */
            p = delete_char(dev, p_buf, p, &col, &n, plen);	
			
#ifdef IN_FBC_MAIN_CONFIG
			if(del_char_flag)
			{
				del_char_flag = 0;
				if(first_sep_index > n)
				{
					pq_cmd_flag = 0;
					first_sep_index = -1;
					first_space_flag = 0;
					char *tmp = p_buf;						
					p_buf = buffer;
					p = p_buf + n;
					strncpy(p_buf, tmp, n);
				}
			}
#endif
            continue;

        default:
            /*
             		* Must be a normal character then
             		*/
#ifdef IN_FBC_MAIN_CONFIG             		
            if (!pq_cmd_flag && n < MAX_CONSOLE_BUF_SIZE-2 || pq_cmd_flag && n < EXTEND_BUF_SIZE-2)
#else	
			if (n < MAX_CONSOLE_BUF_SIZE-2)
#endif		
			{

                if (c == '\t') {    /* expand TABs      */
                    dev->puts (tab_seq+(col&07));
                    col += 8 - (col&07);
                } else {
                    ++col;      /* echo input       */
                    dev->putc (c);
                }
                *p++ = c;
                ++n;
				
#ifdef IN_FBC_MAIN_CONFIG     
				if(!first_space_flag && (' ' == c || '\t' == c))
				{
					first_space_flag = 1;
					if(!is_not_pq_cmd(buffer, n-1))
					{
						pq_cmd_flag = 1;
						first_sep_index = n;
						char *tmp = p_buf;						
						p_buf = (char *)EXTEND_BUF_ADDR;
						p = p_buf + n;
						strncpy(p_buf, tmp, n);
					}
				}
#endif				
            }
			else
			{            /* Buffer full      */
                dev->putc ('\a');
            }
        }
    }
}

/****************************************************************************/

int parse_line (char *line, char *argv[])
{
    int nargs = 0;

    while (nargs < CONFIG_SYS_MAXARGS) {

        /* skip any white space */
        while ((*line == ' ') || (*line == '\t')) {
            ++line;
        }

        if (*line == '\0') {    /* end of line, no more args    */
            argv[nargs] = NULL;
            return (nargs);
        }

        argv[nargs++] = line;   /* begin of argument string */

        /* find end of string */
        while (*line && (*line != ' ') && (*line != '\t')) {
            ++line;
        }

        if (*line == '\0') {    /* end of line, no more args    */
            argv[nargs] = NULL;
            return (nargs);
        }

        *line++ = '\0';     /* terminate current arg     */
    }
    return (nargs);
}

int debug_console(struct serial_device *dev)
{
/*	int len;

	console_mode = 1;
	while (console_mode){
      len = readline(dev, ">");
      if (len == 0)
          break;
      
      if (len > 0){
              strcpy (lastcommand, console_buffer);
          rc = run_command (lastcommand, 1);
          if (rc <= 0) {
                  lastcommand[0] = 0;
          }
      }                        
      else if (len == -1)
              puts ("<INTERRUPT>\n");
	}*/
    return 1;
}




