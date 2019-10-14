#include <spi_regional_division.h>
#include <crc.h>

static int query_check_info(unsigned s_addr, check_info_t **info)
{
//	unsigned s_addr;
	unsigned ret;
	
	if(!info) return -1;

//	s_addr = s_offs + SPI_BASE;
	
	switch(s_addr)
	{
		case BOOT_CODE_BASE:
			*info = (check_info_t *)(BOOT_CODE_BASE + BOOT_AREA_SIZE - CHECK_INFO_SIZE);
			ret = MAIN_CODE_BASE;
			break;

		case MAIN_CODE_BASE:
			*info = (check_info_t *)(MAIN_CODE_BASE + MAIN_CODE_SIZE - CHECK_INFO_SIZE);
			ret = MAIN_DATA_BASE;
			break;
			
		case MAIN_DATA_BASE:
			*info = (check_info_t *)(MAIN_DATA_BASE + MAIN_DATA_SIZE - CHECK_INFO_SIZE);
			ret = MAIN_RODATA_BASE;
			break;
			
		case MAIN_RODATA_BASE:
			*info = (check_info_t *)(MAIN_RODATA_BASE + MAIN_RODATA_SIZE - CHECK_INFO_SIZE);
			ret = PARAM_AREA_BASE;
			break;
			
		case PARAM_AREA_BASE:
			*info = (check_info_t *)(PARAM_AREA_BASE + PARAM_SIZE - CHECK_INFO_SIZE);
			ret = PARAM_AREA_BASE + PARAM_SIZE;
			break;
			
		case ICCM_BASE:
			*info = (check_info_t *)(ICCM_BASE + ICCM_SIZE - CHECK_INFO_SIZE);
			ret = ICCM_BASE + ICCM_SIZE;
			break;
			
		case DCCM_BASE:
			*info = (check_info_t *)(DCCM_BASE + DCCM_SIZE - CHECK_INFO_SIZE);
			ret = DCCM_BASE + DCCM_SIZE;
			break;
			
	}

	return ret;
}

int check_image(unsigned s_addr, int size)
{
	unsigned t_addr, t_ret, crc;
	
	check_info_t *info;

	t_addr = s_addr;
	
	do {
		t_ret = query_check_info(t_addr, &info);
		
		if(t_ret == -1) return 0;

		crc = crc32(0, (const unsigned char *)t_addr, (unsigned)info - t_addr);
		if(crc != info->crc)
		{
//			printf("check_image: t_addr = 0x%x, t_ret = 0x%x, crc = 0x%x, info->crc = 0x%x\n", t_addr, t_ret, crc, info->crc);
			return 0;
		}
		
		t_addr = t_ret;
		
	} while(t_addr < (s_addr + size));
	
	return 1;
}