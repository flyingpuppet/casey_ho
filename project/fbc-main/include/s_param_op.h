#ifndef __PARAM_OP_H__
#define __PARAM_OP_H__

#ifndef NULL
#define NULL	0
#endif

#define MAX_PARAM_NUM			0x80
#define MAX_PARAM_NAME			0xc
#define HASH_ARRAY_SIZE			0x20
#define SYS_PARAM_HEADER_SIZE	0x800

typedef struct {
	char name[MAX_PARAM_NAME];
	unsigned short offset;
	unsigned short length;
	
} sys_param_header_t;

typedef struct sys_param_desc {
	struct sys_param_desc *next;
	sys_param_header_t s_param_h;
	void *addr;
	unsigned s_flag;
	
} sys_param_desc_t;

typedef struct {
	sys_param_desc_t *hash_tab[HASH_ARRAY_SIZE];
	unsigned m_flag;
	
} sys_param_htab_t;

typedef enum {
	IN_SPI = 0,
	IN_MEM,
	IS_ADDED,
} sys_param_state_e;

int get_sys_param(char *name, void *value);
int set_sys_param(char *name, void *value);
int save_sys_param();
int default_sys_param();
int test_param(char *name);	//if there is no returns 0, otherwise it returns the length of it.
int init_sys_param();
#endif
