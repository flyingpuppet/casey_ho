#include <common.h>
#include <log.h>
#include <malloc.h>
#include <string.h>
#include <uart.h>
#include <spi_regional_division.h>
#include <spi_flash.h>
#include <s_param_op.h>

static sys_param_htab_t s_param_entry;

static unsigned get_hash_code(char *key)
{
	unsigned hval;
	char *c;
	
	if(NULL == key || strlen(key) >= MAX_PARAM_NAME) return MAX_PARAM_NAME;

	for(hval = 0, c = key; *c != '\0'; c++)
	{
		hval += *c; 
	}
	
	hval %= HASH_ARRAY_SIZE;
	
	return hval;
}

static int add_to_hash_list(sys_param_desc_t *s_param_d)
{
	if(s_param_d == NULL || test_param(s_param_d->s_param_h.name)) return -1;
	
	unsigned hval = get_hash_code(s_param_d->s_param_h.name);

	sys_param_desc_t **s_tmp = NULL;
	for(s_tmp = &(s_param_entry.hash_tab[hval]); *s_tmp != NULL; s_tmp = &((*s_tmp)->next))
	{
	}

	*s_tmp = s_param_d;
	
	return 0;
}

static void destory_sys_param_node(sys_param_desc_t * param)
{
	if(param == NULL) return;

	if(param->addr != NULL)
	{
		free(param->addr);
		param->addr = NULL;
	}

	free(param);
}

static void destory_hash_list()
{
	unsigned i;
	for(i=0; i<HASH_ARRAY_SIZE; i++)
	{
		if(s_param_entry.hash_tab[i] == NULL) continue;
		
		sys_param_desc_t *s_param_d = NULL;
		sys_param_desc_t *s_tmp = NULL;
		for(s_param_d=s_param_entry.hash_tab[i]; s_param_d!=NULL; )
		{
			s_tmp = s_param_d;
			s_param_d = s_param_d->next;
			destory_sys_param_node(s_tmp);
		}
		s_param_entry.hash_tab[i] = NULL;
	}
	return;
}

static int do_default_sys_param()
{
	char buf[RESERVED_PARAM_AREA_SIZE];
	memset(buf, 0, RESERVED_PARAM_AREA_SIZE);
	spi_flash_erase(get_spi_flash_device(0), SYSTEM_PARAM_AREA_BASE_OFFSET, RESERVED_PARAM_AREA_SIZE);
	spi_flash_read(get_spi_flash_device(0), PARAM_AREA_BACKUP_BASE_OFFSET + AUDIO_PARAM_AREA_SIZE + PQ_PARAM_AREA_SIZE, RESERVED_PARAM_AREA_SIZE, buf);
	spi_flash_write(get_spi_flash_device(0), SYSTEM_PARAM_AREA_BASE_OFFSET, RESERVED_PARAM_AREA_SIZE, buf);
	return 0;
}

int test_param(char *name)
{
	if(name == NULL) return 0;

	unsigned hval = get_hash_code(name);
	sys_param_desc_t *s_param_d = NULL;
	for(s_param_d = s_param_entry.hash_tab[hval]; s_param_d != NULL; s_param_d = s_param_d->next)
	{
		if(!strcmp(name, s_param_d->s_param_h.name))
		{
			return s_param_d->s_param_h.length;
		}
	}
	
	return 0;
}

int set_sys_param(char *name, void *value)
{
	if(name==NULL || value==NULL) return -1;

	unsigned hval = get_hash_code(name);
	
	sys_param_desc_t *s_param_d = NULL;
	
	for(s_param_d = s_param_entry.hash_tab[hval]; s_param_d != NULL; s_param_d = s_param_d->next)
	{
		if(!strcmp(s_param_d->s_param_h.name, name))
		{
			if(s_param_d->s_flag)
			{
				memcpy((char *)(s_param_d->addr), (char *)value, s_param_d->s_param_h.length);
			}
			else
			{
				char *val = (char *)malloc(s_param_d->s_param_h.length);
				
				if(val == NULL) return -1;

				memcpy(val, (char *)value, s_param_d->s_param_h.length);
				s_param_d->addr = val;
				s_param_d->s_flag = IN_MEM;
			}

			s_param_entry.m_flag |= (1<<hval);
			
			return s_param_d->s_param_h.length;
		}
	}

	return 0;
	
}

int get_sys_param(char *name, void *value)
{
	if(name==NULL || value==NULL) return -1;

	unsigned hval = get_hash_code(name);
	sys_param_desc_t *s_param_d = NULL;
	for(s_param_d = s_param_entry.hash_tab[hval]; s_param_d != NULL; s_param_d = s_param_d->next)
	{
		if(!strcmp(s_param_d->s_param_h.name, name))
		{
			if(s_param_d->s_flag)
			{
				memcpy((char *)value, (char *)(s_param_d->addr), s_param_d->s_param_h.length);
			}
			else
			{
				if(spi_flash_read(get_spi_flash_device(0), s_param_d->s_param_h.offset, s_param_d->s_param_h.length, value) != 0)
				{
					serial_puts("in get_sys_param read sys param error!\n");
					return -1;
				}
			}

			return s_param_d->s_param_h.length;
		}
	}

	return 0;
}

int save_sys_param()
{
	char buf[RESERVED_PARAM_AREA_SIZE];
	if(spi_flash_read(get_spi_flash_device(0), SYSTEM_PARAM_AREA_BASE_OFFSET, RESERVED_PARAM_AREA_SIZE, buf) != 0)
	{
		serial_puts("in save_sys_param read sys param error!\n");
		return -1;
	}

	unsigned con, i;
	for(i=0; i<HASH_ARRAY_SIZE; i++)
	{
		con = s_param_entry.m_flag & (1<<i);
		if(!con) continue;
		
		sys_param_desc_t *s_param_d = NULL;
		for(s_param_d=s_param_entry.hash_tab[i]; s_param_d!=NULL; s_param_d=s_param_d->next)
		{
			if(s_param_d->s_flag == IN_MEM)
			{
				memcpy(buf+s_param_d->s_param_h.offset, s_param_d->addr, s_param_d->s_param_h.length);
				free(s_param_d->addr);
				s_param_d->addr = NULL;
				s_param_d->s_flag = IN_SPI;
			}
		}
	}

	s_param_entry.m_flag = 0;
	if(spi_flash_erase(get_spi_flash_device(0), SYSTEM_PARAM_AREA_BASE_OFFSET, RESERVED_PARAM_AREA_SIZE))
	{
		serial_puts("in save_sys_param erase failed!\n");
		return -1;
	}
	
	if(spi_flash_write(get_spi_flash_device(0), SYSTEM_PARAM_AREA_BASE_OFFSET, RESERVED_PARAM_AREA_SIZE, buf))
	{
		serial_puts("in save_sys_param write failed!\n");
		return -1;
	}
	
	return 0;
}

int default_sys_param()
{
	destory_hash_list();
	do_default_sys_param();
	init_sys_param();
	return 0;
}

int init_sys_param()
{
	
	char buf[SYS_PARAM_HEADER_SIZE];
	
	memset(&s_param_entry, 0, sizeof(sys_param_htab_t));
	memset(buf, 0, sizeof(buf));
	
	if(spi_flash_read(get_spi_flash_device(0), SYSTEM_PARAM_AREA_BASE_OFFSET, SYS_PARAM_HEADER_SIZE, buf) != 0)
	{
		serial_puts("in init_sys_param read sys param header error!\n");
		return -1;
	}
	
	sys_param_desc_t *s_param_d = NULL;
	sys_param_header_t *s_param_h = NULL;
	
	for(s_param_h = (sys_param_header_t *)(unsigned)buf; s_param_h->length > 0; s_param_h++)
	{
		s_param_d = (sys_param_desc_t *)malloc(sizeof(sys_param_desc_t));
		if(NULL == s_param_d)
		{
			serial_puts("alloc sys_param_desc_t failed!\n");
			return -1;
		}
		
		memset(s_param_d, 0, sizeof(sys_param_desc_t));

		s_param_d->s_param_h.length = s_param_h->length;
		s_param_d->s_param_h.offset = s_param_h->offset;
		memcpy(s_param_d->s_param_h.name, s_param_h->name, MAX_PARAM_NAME);
		
		if(add_to_hash_list(s_param_d))
		{
			destory_sys_param_node(s_param_d);
		}
		
		s_param_d = NULL;
	}

	return 0;
}

