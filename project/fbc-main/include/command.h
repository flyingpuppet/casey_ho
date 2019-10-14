#ifndef __COMMAND_H
#define __COMMAND_H

#include <string.h>

#ifdef IN_FBC_MAIN_CONFIG
#ifndef CONFIG_SYS_LONGHELP
#define CONFIG_SYS_LONGHELP
#endif
#endif

#ifndef NULL
#define NULL	0
#endif

struct cmd_tbl_s {
	char *name;		// Command Name
	int	maxargs;	// maximum number of arguments
	int	repeatable;	// autorepeat allowed?
					// Implementation function
	int	(*cmd)(struct cmd_tbl_s *, int, int, char * const []);
	char *usage;		// Usage message	(short)
#ifdef CONFIG_SYS_LONGHELP
	char *help;		// Help  message	(long)
#endif

#ifdef CONFIG_AUTO_COMPLETE
	int (*complete)(int argc, char * const argv[], char last_char, int maxv, char *cmdv[]);
#endif
};

typedef struct cmd_tbl_s	cmd_tbl_t;

// common/command.c
cmd_tbl_t *find_cmd(const char *cmd);
int run_command (char *cmd, int flag);
int ctrlc (void);
extern int cmd_usage(cmd_tbl_t *cmdtp);

#ifdef CONFIG_AUTO_COMPLETE
extern int var_complete(int argc, char * const argv[], char last_char, int maxv, char *cmdv[]);
extern int cmd_auto_complete(const char *const prompt, char *buf, int *np, int *colp);
#endif

/*
 * Command Flags:
 */
#define CMD_FLAG_REPEAT		0x0001	// repeat last command
#define CMD_FLAG_BOOTD		0x0002	// command is from bootd	

#define GET_CMD_ADDR_FROM_CNAME(name) &__fbc_boot_cmd_##name

#ifdef CONFIG_AUTO_COMPLETE
# define _CMD_COMPLETE(x) x,
#else
# define _CMD_COMPLETE(x)
#endif
#ifdef CONFIG_SYS_LONGHELP
# define _CMD_HELP(x) x,
#else
# define _CMD_HELP(x)
#endif

#define FBC_BOOT_CMD_MKENT_COMPLETE(name,maxargs,rep,cmd,usage,help,comp) \
	{#name, maxargs, rep, cmd, usage, _CMD_HELP(help) _CMD_COMPLETE(comp)}

#define FBC_BOOT_CMD_MKENT(name,maxargs,rep,cmd,usage,help) \
	FBC_BOOT_CMD_MKENT_COMPLETE(name,maxargs,rep,cmd,usage,help,NULL)

#define FBC_BOOT_CMD_COMPLETE(name,maxargs,rep,cmd,usage,help,comp) \
	cmd_tbl_t __fbc_boot_cmd_##name = \
		FBC_BOOT_CMD_MKENT_COMPLETE(name,maxargs,rep,cmd,usage,help,comp)

#define FBC_BOOT_CMD(name,maxargs,rep,cmd,usage,help) \
	FBC_BOOT_CMD_COMPLETE(name,maxargs,rep,cmd,usage,help,NULL)

#endif	// __COMMAND_H
