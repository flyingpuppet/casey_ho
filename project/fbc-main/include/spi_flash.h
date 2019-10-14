/*
 * Interface to SPI flash
 *
 */
#ifndef __SPI_FLASH_H__
#define __SPI_FLASH_H__

#ifndef NULL
#define NULL	0
#endif

//#define __DEBUG_SPI_FLASH__

#define CONFIG_RANDOM_WRITE

#define FLASH_PP_SIZE	256

#define SPI_BLOCK_SIZE	4096

#define SPI_FLASH_SECTOR_SIZE	4096

#define SPI_FLASH_SECTOR_MASK	(!(SPI_FLASH_SECTOR_SIZE-1))

#define	SPI_FLASH_BASE_ADDR		0x40000000

#define SPI_FLASH_SIZE	(0x80*0x400*0x400)

#define CONFIG_SPI_CONTROL_CACHE_SIZE	0x20

#define GET_SECTOR_NO(offset1, offset2)	(((offset1)>>12) - ((offset2)>>12) + 1)

struct spi_flash {
	const char *name;
	const unsigned base_addr;
	const unsigned size;
	int (*read)(unsigned int offset, unsigned int len, void *buf);
	int (*write)(unsigned int offset, unsigned int len, const void *buf);
	int	(*erase)(unsigned int offset, unsigned int len);
};

void init_spi_flash();
struct spi_flash* get_spi_flash_device(int index);
int spi_flash_read(struct spi_flash *flash, unsigned int offset, unsigned int len, void *buf);
int spi_flash_write(struct spi_flash *flash, unsigned int offset, unsigned int len, const void *buf);
int spi_flash_erase(struct spi_flash *flash, unsigned int offset, unsigned int len);

#ifdef CONFIG_RANDOM_WRITE
int spi_flash_random_write(struct spi_flash *flash, unsigned int offset, unsigned int len, const void *buf);
#endif

#endif //__SPI_FLASH_H__