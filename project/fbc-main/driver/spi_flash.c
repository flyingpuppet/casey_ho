/*
 * Amlogic SPI flash interface
 *
 * Copyright (C) 2011 Amlogic Corporation
 *
 * Licensed under the GPL-2 or later.
 * 
 *
 * Dedicated for Amlogic SPI controller use
 */

#include <spi_flash.h>
#include <register.h>
#include <serial.h>
#include <common.h>
#include <string.h>
#include <interrupt.h>
#include <c_arc_pointer_reg.h>

#ifdef CONFIG_RANDOM_WRITE
#include <malloc.h>
#endif

#define SPI_FLASH_NAME	"FBC_SPI_FLASH"

#define SPI_XFER_BEGIN      0x0001		/* Assert CS before transfer */
#define SPI_XFER_END        0x0002		/* Deassert CS after transfer */
#define SPI_XFER_ADR        0x0004		/* Set SPI address for read/write */
#define SPI_XFER_CMD        0x0008		/* Trigger SPI command */    
#define SPI_XFER_STATUS		0x0010		/* Read SPI status register from device */
#define SPI_XFER_ID	    	0x0020		/* Read SPI device ID */
#define SPI_XFER_READCACHE	0x0080		/* SPI controller data operation: from cache to host */
#define SPI_XFER_WRITECACHE	0x0100		/* SPI controller data operation: from host to cache*/

#define writel(data, addr)	*(volatile unsigned long *)(addr)=(data)
#define readl(addr)			*(volatile unsigned long *)(addr)

extern int _spi_flash_write(unsigned int offset, unsigned int len, const void *buf);
extern int _spi_flash_read(unsigned int offset, unsigned int len, void *buf);
extern int _spi_flash_erase(unsigned int offset, unsigned int len);


struct spi_flash *current_spi_flash;

struct spi_flash f_spi_flash = {
	SPI_FLASH_NAME, \
	SPI_FLASH_BASE_ADDR, \
	SPI_FLASH_SIZE, \
	_spi_flash_read, \
	_spi_flash_write, \
	_spi_flash_erase,
	
};

/*
static int spi_xfer(unsigned int bitlen, const void *dout, void *din, unsigned long flags)
{
	unsigned len;
	unsigned temp_len;
	unsigned char temp_data[4];
	unsigned char *buf = temp_data;
	int	ret = 0;
	const unsigned char *txp = (unsigned char *)dout;
	unsigned char *rxp = (unsigned char *)din;
	unsigned value;
	int i,j;
	
	ret = 0;

	if (bitlen == 0) goto out;    

	if (bitlen % 8)
	{
		flags |= SPI_XFER_END;
		goto out;
	}

	len = bitlen / 8; //convert to BYTE counter
	
	//Set Address register of SPI controller
	if(flags & SPI_XFER_ADR)
	{
		writel(*((unsigned *)(unsigned)txp), P_SPI_FLASH_ADDR);
		goto out;	
	}
	
	//Send command to device through SPI FLASH command register
	if(flags & SPI_XFER_CMD)
	{

		//only for RDID, clear the cache for a fresh load
		if(*((unsigned *)dout) == (1<<SPI_FLASH_RDID))
		{
			writel(0, P_SPI_FLASH_C0);			
		}
    	writel(*((unsigned *)(unsigned)txp), P_SPI_FLASH_CMD);
		while(readl(P_SPI_FLASH_CMD)!=0);
		goto out;
	}

	//Write data to SPI data cache for transfer
	//Then SPI controller will transfer them to SPI device with WREN(Writer enable) & PP(Page program)
	if((txp) && (flags & SPI_XFER_WRITECACHE)){
		for( j=0;j<len;j+=4)
		{
			writel(*(unsigned *)(unsigned)(txp + j), P_SPI_FLASH_C0 + j);
		}		
		goto out;
	}	

	//for input to host
	//following code will use rxp
	if(!rxp) goto out;

	//Read status register
	if(flags & SPI_XFER_STATUS)
	{
		value=readl(P_SPI_FLASH_STATUS) & 0xffff;
		*rxp = value & 0xff;
		*(rxp + 1) = (value >> 8) & 0xff;
		goto out;
	}

	//Read vender & chip ID 
	if(flags & SPI_XFER_ID)
	{
		value = readl(P_SPI_FLASH_C0) & 0xffffff;
		*rxp = value & 0xff;
		*(rxp + 1) = (value >> 8) & 0xff;
		*(rxp + 2) = (value >> 16) & 0xff;
		goto out;
	}		
	
	//Load from SPI controller data cache
	if(flags & SPI_XFER_READCACHE)
	{
		temp_len = len/4;
		for(i=0; i < temp_len*4; i += 4)
		{		
			*(unsigned *)(unsigned)(rxp+i)=readl(P_SPI_FLASH_C0 + i);
		}
		
		if(len % 4)
		{
			temp_len = len % 4;
			*(unsigned *)(unsigned)buf = readl(P_SPI_FLASH_C0 + i);
			for(j=0; j<temp_len; j++)
			{
				*(unsigned char *)(rxp + i + j) = *(buf + j);
			}
		}
		goto out;
	}	
		
out:
	writel(readl(SPI_FLASH_CTRL) | 1<<SPI_ENABLE_AHB, SPI_FLASH_CTRL); //for AHB data bus request
	return 0;
}

int spi_flash_cmd(unsigned cmd, void *response, int len)
{
	unsigned long flags = SPI_XFER_BEGIN;
	int ret;
	unsigned var = cmd;	

	if (len == 0) flags |= SPI_XFER_END;
	
	flags |= SPI_XFER_CMD;

	ret = spi_xfer(4*8, (unsigned char *)(unsigned)&var, NULL, flags);				

	if (ret)
	{
		serial_puts("sf: failed to send command.\n");
		return ret;
	}

	if (len)
	{
		if((1 << SPI_FLASH_RDID) == cmd)
		{
			flags=SPI_XFER_ID;			
		}
		else
		{
			if((1 << SPI_FLASH_RDSR) == cmd)
			{
				flags=SPI_XFER_STATUS;				
			}
		}

		ret = spi_xfer(len * 8, NULL, response, flags | SPI_XFER_END);

		if (ret)
		{
			serial_puts("sf: failed to read response.\n");			
		}
	}
	
	return ret;
}

static int spi_flash_addr_write(unsigned addr){

	unsigned flags = SPI_XFER_END;
	unsigned nAddress = addr;
	int ret;

	flags |= SPI_XFER_ADR;
	
	ret = spi_xfer(4*8, &nAddress, NULL, flags);
	
	if(ret)
	{	
		serial_puts("sf: faild to send addr.\n");
	}
	return ret;
}

int spi_program(const unsigned * addr_source, unsigned spi_addr)
{
	int status = 1;
		
	*P_SPI_FLASH_ADDR = (spi_addr & 0xffffff) | (CONFIG_SPI_CONTROL_CACHE_SIZE << SPI_FLASH_BYTES_LEN);
			
    *P_SPI_FLASH_C0 = *addr_source++;
    *P_SPI_FLASH_C1 = *addr_source++;
    *P_SPI_FLASH_C2 = *addr_source++;
    *P_SPI_FLASH_C3 = *addr_source++;
    *P_SPI_FLASH_C4 = *addr_source++;
    *P_SPI_FLASH_C5 = *addr_source++;
    *P_SPI_FLASH_C6 = *addr_source++;
    *P_SPI_FLASH_C7 = *addr_source++;
	
	*P_SPI_FLASH_CMD  =  1 << SPI_FLASH_WREN;
	 
	while ((*P_SPI_FLASH_CMD ) != 0); 
	 
	*P_SPI_FLASH_CMD = 1 << SPI_FLASH_PP;
	 
	while ((*P_SPI_FLASH_CMD ) != 0);
	 
	while ((status & 1) == 1)
	{ 
		*P_SPI_FLASH_CMD = 1 << SPI_FLASH_RDSR;
		
		while ((*P_SPI_FLASH_CMD ) != 0);
		
		status = *P_SPI_FLASH_STATUS ;
	}
	
	*(P_SPI_FLASH_CTRL) = (*P_SPI_FLASH_CTRL) | (1 << SPI_ENABLE_AHB); 
	
	return 0;
}
*/

static int spi_page_program(const void *buf, unsigned offs, int length)
{

	const unsigned char *p = (const unsigned char *)buf;
	unsigned char *c_buf = (unsigned char *)(unsigned)P_SPI_FLASH_C0;

	int t_len = length;
	int w_len = 0;
	unsigned w_offs = offs;
	unsigned w_addr;
	unsigned status = 0x1;
	unsigned f_num = 0;
	unsigned char *f_buf[32];

#ifdef __DEBUG_SPI_FLASH__	
	unsigned f_status = 0, i = 0;

	printf("spi_page_program: buf: 0x%x, offs: 0x%x, length: 0x%x\n", buf, offs, length);
#endif

	if(!buf || !length) return -1;

	DisableAllInterrupt();

	//close AHB bus before any APB bus operation
	Wr_reg_bits(SPI_FLASH_CTRL, 0, SPI_ENABLE_AHB, 1);
	
	while(t_len > 0)
	{
		f_num = 0;
		
		if(t_len > CONFIG_SPI_CONTROL_CACHE_SIZE)
			w_len = CONFIG_SPI_CONTROL_CACHE_SIZE;
		else
			w_len = t_len;

		if(w_len % 4 != 0)
		{
			f_num = 4 - w_len % 4;
		}
		
		memset(f_buf, 0xff, 32);
			
		w_addr = ((w_offs/FLASH_PP_SIZE) << 0x8) | ((w_offs % FLASH_PP_SIZE) << 0x0);
		
		Wr(SPI_FLASH_ADDR, ((w_addr & 0xffffff) | ((w_len + f_num) << SPI_FLASH_BYTES_LEN )));
		
		memcpy(f_buf, p, w_len);
		memcpy(c_buf, f_buf, (w_len + f_num));
		_ASM("sync");

		Wr(SPI_FLASH_CMD, (1<<SPI_FLASH_WREN));
		while (Rd(SPI_FLASH_CMD) !=0);
		
		
		Wr(SPI_FLASH_CMD, (1<<SPI_FLASH_PP));
		while (Rd(SPI_FLASH_CMD) !=0);

		status = 0x1;
		while ((status & 0x1) == 1)
		{
			Wr(SPI_FLASH_CMD, (1 << SPI_FLASH_RDSR));
			
			while (Rd(SPI_FLASH_CMD) !=0);

			status = Rd(SPI_FLASH_STATUS);
			
#ifdef __DEBUG_SPI_FLASH__
			if(i == 0) f_status = status;
			i++;
#endif
		}
		
		w_offs += w_len;
		p += w_len;
		t_len -= w_len;
		
	}
	
	Wr_reg_bits(SPI_FLASH_CTRL, 1, SPI_ENABLE_AHB, 1);

#ifdef __DEBUG_SPI_FLASH__	
	printf("status: 0x%x, f_status: 0x%x, i = %d, f_num = %d\n", status, f_status, i, f_num);
#endif

	EnableAllInterrupt();
	
	return length;
}

static int _spi_flash_write(unsigned int offset, unsigned int len, const void *buf)
{
	int ret = 0;
	unsigned p_offs = offset % FLASH_PP_SIZE;
	
	if(!len || !buf)
		return -1;

#ifdef __DEBUG_SPI_FLASH__
	printf("_spi_flash_write: p_offs: 0x%x\n", p_offs);
#endif

	if(p_offs + len <= FLASH_PP_SIZE)
	{	
		return spi_page_program(buf, offset, len);
	}
	else
	{
		int f_len = FLASH_PP_SIZE - p_offs;

		ret += spi_page_program(buf, offset, f_len);
		
		int t_offs = offset + f_len;
		int e_offs = offset + len;
		unsigned t_len = FLASH_PP_SIZE;
		const void *p_buf = (const void *)((unsigned)buf + f_len);
		
#ifdef __DEBUG_SPI_FLASH__		
		printf("_spi_flash_write: t_offs: 0x%x, e_offs: 0x%x, t_len: 0x%x, p_buf: 0x%x\n", t_offs, e_offs, t_len, p_buf);
#endif

		while(t_offs < e_offs)
		{
			if(e_offs - t_offs > FLASH_PP_SIZE)
				t_len = FLASH_PP_SIZE;
			else
				t_len = e_offs - t_offs;

#ifdef __DEBUG_SPI_FLASH__				
			printf("t_len: 0x%x\n", t_len);
#endif

			ret += spi_page_program(p_buf, t_offs, t_len);
			
			t_offs += t_len;
			p_buf = (const void *)((unsigned)p_buf + t_len);
			
#ifdef __DEBUG_SPI_FLASH__			
			printf("_spi_flash_write: t_offs: 0x%x, e_offs: 0x%x, p_buf: 0x%x\n", t_offs, e_offs, p_buf);
#endif
		}
		
		return ret;
	}

}

static int _spi_flash_read(unsigned int offset, unsigned int len, void *buf)
{
	char * source_addr = (char*)(SPI_FLASH_BASE_ADDR + offset);

	if(!len || !buf)
		return -1;
	
	memcpy(buf, source_addr, len);
	
	return len;
}

int spi_flash_sector_erase(unsigned int offset)
{
	unsigned status;
	
	DisableAllInterrupt();

	*P_SPI_FLASH_CTRL = (*P_SPI_FLASH_CTRL) & (~(1 << SPI_ENABLE_AHB ));
	*P_SPI_FLASH_ADDR = offset & 0xffffff;
	*P_SPI_FLASH_CMD  =  1 << SPI_FLASH_WREN;
	
	while ((*P_SPI_FLASH_CMD ) != 0);
	
	// sector erase  4Kbytes erase is sector erase.
	*P_SPI_FLASH_CMD = 1 << SPI_FLASH_SE;
	
	while ((*P_SPI_FLASH_CMD ) != 0);
	
	// check erase is finished.
	status = 1;
	
	while ((status & 1) == 1)
	{      
		*P_SPI_FLASH_CMD = 1 << SPI_FLASH_RDSR;
		
		while ((*P_SPI_FLASH_CMD ) != 0);
		
		status = *P_SPI_FLASH_STATUS ;
	}
	
	*(P_SPI_FLASH_CTRL) = (*P_SPI_FLASH_CTRL) | (1 << SPI_ENABLE_AHB); 

	EnableAllInterrupt();

	return 0;
	
}

static int _spi_flash_erase(unsigned int offset, unsigned int len)
{
	unsigned actual;
	
	if((len%SPI_FLASH_SECTOR_SIZE)!=0 || (offset%SPI_FLASH_SECTOR_SIZE)!=0)
	{
		return -1;
	}

	for (actual = 0; actual < len; actual+=SPI_FLASH_SECTOR_SIZE)
	{
		if(spi_flash_sector_erase(offset+actual) != 0)
		{
			return -1;
		}
	}
	
	return 0;
}

struct spi_flash* get_spi_flash_device(int index)
{
	if(0 == index)
	{
		return &f_spi_flash;
	}
	
	return NULL;
}

void init_spi_flash()
{
	*(P_SPI_FLASH_CTRL) = 0xea313;    // system clock / 4.     
	*(P_SPI_FLASH_CTRL1) = 0x501f0080;
//	*(P_SPI_FLASH_USER) = *(P_SPI_FLASH_USER) | (1<<7);
}

int spi_flash_read(struct spi_flash *flash, unsigned int offset, unsigned int len, void *buf)
{
	return flash->read(offset, len, buf);
}

int spi_flash_write(struct spi_flash *flash, unsigned int offset, unsigned int len, const void *buf)
{
	return flash->write(offset, len, buf);
}

int spi_flash_erase(struct spi_flash *flash, unsigned int offset, unsigned int len)
{
	return flash->erase(offset, len);
}


#ifdef CONFIG_RANDOM_WRITE

int spi_flash_random_write(struct spi_flash *flash, unsigned int offset, unsigned int len, const void *buf)
{
	unsigned w_len = 0;
	unsigned t_len = len;
	unsigned sector_no;
	unsigned p_offs, s_offs, e_offs;
	const unsigned char *p = (const unsigned char *)buf;
	unsigned char t_buf[SPI_FLASH_SECTOR_SIZE];

	if(!buf || !len) return -1;

	p_offs = offset % SPI_FLASH_SECTOR_SIZE;
	s_offs = (offset / SPI_FLASH_SECTOR_SIZE) * SPI_FLASH_SECTOR_SIZE;
	e_offs = s_offs + len;

	for(; s_offs < e_offs; s_offs += SPI_FLASH_SECTOR_SIZE)
	{
		if(p_offs + t_len > SPI_FLASH_SECTOR_SIZE)
			w_len = SPI_FLASH_SECTOR_SIZE - p_offs;
		else
			w_len = t_len;
		
		spi_flash_read(flash, s_offs, SPI_FLASH_SECTOR_SIZE, t_buf);
		memcpy(t_buf + p_offs, p, w_len);
		spi_flash_erase(flash, s_offs, SPI_FLASH_SECTOR_SIZE);
		spi_flash_write(flash, s_offs, SPI_FLASH_SECTOR_SIZE, t_buf);
		
		p_offs = 0;
		p += w_len;
		t_len -= w_len;
		
	}

	return len;

}

#endif
