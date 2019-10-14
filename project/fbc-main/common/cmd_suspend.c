#include <common.h>
#include <command.h>

int do_suspend(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	printf("enter suspend!\n");
	printf("argc = %d\n", argc);
	int i;
	for(i=0; i<argc; i++){
		printf("argv[%d] = %s\n", i, argv[i]);
	}
	return 1;
}