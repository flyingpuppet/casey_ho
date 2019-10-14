#include <common.h>
#include <command.h>
#include <cmd_config.h>

#define CONFIG_SYS_CBSIZE		512
#define CONFIG_SYS_MAXARGS		10
#define CONFIG_SYS_HELP_CMD_WIDTH	8

#ifdef IN_FBC_MAIN_CONFIG
extern int pq_cmd_flag;
#endif

/***************************************************************************
 * find command table entry for a command
 */
cmd_tbl_t *find_cmd (const char *cmd)
{
	int len;
	int i;
	int n_found = 0;
	char *p;
	cmd_tbl_t *cmdtp_temp = NULL;
	cmd_tbl_t *cmdtp;
	
	if(!cmd)
	{
		return NULL;
	}
	len = ((p = strchr(cmd, '.')) == NULL) ? strlen (cmd) : (p - cmd);
		
	for(i=0; i<sizeof(default_cmd)/sizeof(cmd_tbl_t *); i++)
	{
		cmdtp = default_cmd[i];
		if(cmdtp!=NULL && cmdtp->name!=NULL && strncmp(cmd, cmdtp->name, len) == 0)
		{
			if(strlen(cmdtp->name) == len)
			{
				return cmdtp;
			}
			cmdtp_temp = cmdtp;
			n_found++;
		}
	}

	if(n_found == 1)
	{
		return cmdtp_temp;
	}
	return NULL;
}

int ctrlc (void)
{
	if (default_serial_console()->tstc()) {
		switch (default_serial_console()->getc ()) {
		case 0x03:		// ^C - Control C 
			return 1;
		default:
			break;
		}
	}
	return 0;
}

int run_command (char *cmd, int flag)
{
	cmd_tbl_t *cmdtp;
	char cmdbuf[CONFIG_SYS_CBSIZE];	// working copy of cmd
	char cmdline[CONFIG_SYS_CBSIZE];	// put a cmd
	char *token;			// start of token in cmdbuf
	char *sep;			// end of token (separator) in cmdbuf
	
	char *str = cmdbuf;
	char *argv[CONFIG_SYS_MAXARGS + 1];	// NULL terminated
	int argc = 0, inquotes;
	int repeatable = 1;
	int rc = 0;
	
//	serial_puts("Enter run_command!\n");

	if (!cmd || !*cmd) {
		return -1;	// empty command
	}

#ifdef IN_FBC_MAIN_CONFIG
	if ((!pq_cmd_flag && strlen(cmd) >= CONFIG_SYS_CBSIZE) || (pq_cmd_flag && strlen(cmd) >= EXTEND_BUF_SIZE)) {
		serial_puts ("Command too long!\n");
		return -1;
	}

	if(!pq_cmd_flag)
		strcpy (cmdbuf, cmd);
	else
		str = cmd;
#else
	if (strlen(cmd) >= CONFIG_SYS_CBSIZE) {
		serial_puts ("Command too long!\n");
		return -1;
	}

	strcpy (cmdbuf, cmd);
#endif

	while (*str) 
	{
		for (inquotes = 0, sep = str; *sep; sep++) 
		{
			if ((*sep=='\'') && (*(sep-1) != '\\'))
				inquotes=!inquotes;

			if (!inquotes && (*sep == ';') && ( sep != str) && (*(sep-1) != '\\'))
				break;
		}

		token = str;
		if (*sep) 
		{
			str = sep + 1;	// start of command for next pass
			*sep = '\0';
		}
		else
		{
			str = sep;	// no more commands for next pass
		}
		
#ifdef IN_FBC_MAIN_CONFIG		
		if(!pq_cmd_flag)
			strcpy(cmdline, token);
#else
		strcpy(cmdline, token);
#endif

		// Extract arguments
#ifdef IN_FBC_MAIN_CONFIG		
		if (!pq_cmd_flag && ((argc = parse_line (cmdline, argv)) == 0) || pq_cmd_flag && ((argc = parse_line (token, argv)) == 0)) 
#else
		if ((argc = parse_line (cmdline, argv)) == 0) 
#endif		
		{
			rc = -1;	// no command at all
			continue;
		}

		// Look up command in command table
		if ((cmdtp = find_cmd(argv[0])) == NULL) 
		{
			serial_puts ("Unknown command!\n");
			rc = -1;	// give up after bad command
			continue;
		}

		// found - check max args
		if (argc > cmdtp->maxargs) 
		{
			cmd_usage(cmdtp);
			rc = -1;
			continue;
		}
	
		// OK - call function to do the command
		rc = (cmdtp->cmd) (cmdtp, flag, argc, argv);
	}
	return rc;
}

int cmd_usage(cmd_tbl_t *cmdtp)
{
#ifdef	CONFIG_SYS_LONGHELP
	serial_puts ("Usage:\n");
	serial_puts (cmdtp->name);

	if (!cmdtp->help) {
		serial_puts ("- No additional help available.\n");
		return 1;
	}

	serial_puts (cmdtp->help);
	serial_putc ('\n');
#endif	// CONFIG_SYS_LONGHELP
	return 0;
}

#ifdef IN_FBC_MAIN_CONFIG
int do_help(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{

	int i;
	int rcode = 0;
	const int cmd_items = sizeof(default_cmd)/sizeof(cmd_tbl_t *);

	if (argc == 1) {	//show list of commands 
		cmd_tbl_t *cmd_array[cmd_items];
		int i, j, swaps;
		
		cmdtp = default_cmd[0];
		for (i = 0; i < cmd_items; i++) {
			cmd_array[i] = cmdtp++;
		}

		// Sort command list 
		for (i = cmd_items - 1; i > 0; --i) {
			swaps = 0;
			for (j = 0; j < i; ++j) {
				if (strcmp (cmd_array[j]->name,
						cmd_array[j + 1]->name) > 0) {
					cmd_tbl_t *tmp;
					tmp = cmd_array[j];
					cmd_array[j] = cmd_array[j + 1];
					cmd_array[j + 1] = tmp;
					++swaps;
				}
			}
			if (!swaps)
				break;
		}

		// print short help (usage) 
		for (i = 0; i < cmd_items; i++) {
			const char *usage = cmd_array[i]->usage;

			// allow user abort
			if (ctrlc ())
				return 1;
			if (usage == NULL)
				continue;
			printf("%-*s- %s\n", CONFIG_SYS_HELP_CMD_WIDTH,
				   cmd_array[i]->name, usage);
		}
		return 0;
	}
	
	// command help (long version)
	for (i = 1; i < argc; ++i) {
		if ((cmdtp = find_cmd(argv[i])) != NULL) {
			rcode |= cmd_usage(cmdtp);
		} else {
			printf ("Unknown command '%s' - try 'help'"
				" without arguments for list of all"
				" known commands\n\n", argv[i]
					);
			rcode = 1;
		}
	}
	return rcode;

}
#endif
