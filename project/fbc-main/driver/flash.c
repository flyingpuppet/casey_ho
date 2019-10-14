#include <spi_flash.h>
#include <c_arc_pointer_reg.h>

#define SPI_BASE 0x40000000
#define SPI_SIZE 0x8000000	//128M

int read_from_spi(struct spi_flash *flash, unsigned int offset, unsigned int len, void *buf)
{
	return 0;
}

int write_to_spi(struct spi_flash *flash, unsigned int offset, unsigned int len, const void *buf)
{
	return 0;
}

int	erase_spi(struct spi_flash *flash, unsigned int offset, unsigned int len)
{
	return 0;
}

int SPI_sector_erase(unsigned addr )
{
   unsigned temp;
   *P_SPI_FLASH_CTRL = (*P_SPI_FLASH_CTRL) & (~(1 << SPI_ENABLE_AHB )) ; 
   *P_SPI_FLASH_ADDR = addr & 0xffffff;
   *P_SPI_FLASH_CMD  =  1 << SPI_FLASH_WREN;
   while ( (*P_SPI_FLASH_CMD ) !=0 );
   // sector erase  64Kbytes erase is block erase.
   *P_SPI_FLASH_CMD = 1 << SPI_FLASH_BE;
   while ( (*P_SPI_FLASH_CMD ) !=0 );
   // check erase is finished.
  temp = 1;
  while ( (temp & 1) == 1 ) { 
     *P_SPI_FLASH_CMD = 1 << SPI_FLASH_RDSR;
     while ((*P_SPI_FLASH_CMD ) != 0 );
     temp = *P_SPI_FLASH_STATUS ;
  }
  *(P_SPI_FLASH_CTRL) = (*P_SPI_FLASH_CTRL) | (1 << SPI_ENABLE_AHB ) ; 
  return 0;
}

int SPI_page_program(unsigned * addr_source, unsigned spi_addr, int byte_length)
{
   unsigned temp;
   unsigned temp_addr;
   int temp_bl;
   *P_SPI_FLASH_CTRL = (*P_SPI_FLASH_CTRL) & (~(1 << SPI_ENABLE_AHB )) ; 
   temp_addr = spi_addr;
   temp_bl = byte_length;
   while (temp_bl > 0 ) {
     if ( temp_bl >= 32 ) {
        *P_SPI_FLASH_ADDR = (temp_addr & 0xffffff) | 
                          ( 32 << SPI_FLASH_BYTES_LEN );
        *P_SPI_FLASH_C0 = *addr_source++;
        *P_SPI_FLASH_C1 = *addr_source++;
        *P_SPI_FLASH_C2 = *addr_source++;
        *P_SPI_FLASH_C3 = *addr_source++;
        *P_SPI_FLASH_C4 = *addr_source++;
        *P_SPI_FLASH_C5 = *addr_source++;
        *P_SPI_FLASH_C6 = *addr_source++;
        *P_SPI_FLASH_C7 = *addr_source++;
        temp_bl = temp_bl - 32;
        temp_addr = temp_addr + 32;
     } else {
        *P_SPI_FLASH_ADDR = (temp_addr & 0xffffff) | 
                          (temp_bl << SPI_FLASH_BYTES_LEN );
        if ( temp_bl > 0 ) {
          *P_SPI_FLASH_C0 = *addr_source++;
          temp_bl = temp_bl - 4;
        }
        if ( temp_bl > 0 ) {
          *P_SPI_FLASH_C1 = *addr_source++;
          temp_bl = temp_bl - 4;
        }
        if ( temp_bl > 0 ) {
          *P_SPI_FLASH_C2 = *addr_source++;
          temp_bl = temp_bl - 4;
        }
        if ( temp_bl > 0 ) {
          *P_SPI_FLASH_C3 = *addr_source++;
          temp_bl = temp_bl - 4;
        }
        if ( temp_bl > 0 ) {
          *P_SPI_FLASH_C4 = *addr_source++;
          temp_bl = temp_bl - 4;
        }
        if ( temp_bl > 0 ) {
          *P_SPI_FLASH_C5 = *addr_source++;
          temp_bl = temp_bl - 4;
        }
        if ( temp_bl > 0 ) {
          *P_SPI_FLASH_C6 = *addr_source++;
          temp_bl = temp_bl - 4;
        }
        if ( temp_bl > 0 ) {
          *P_SPI_FLASH_C7 = *addr_source++;
          temp_bl = temp_bl - 4;
        }
     }
   
     *P_SPI_FLASH_CMD  =  1 << SPI_FLASH_WREN;
     while ( (*P_SPI_FLASH_CMD ) !=0 ); 
     *P_SPI_FLASH_CMD = 1 << SPI_FLASH_PP;
     while ( (*P_SPI_FLASH_CMD ) !=0 );
     temp = 1;
     while ( (temp & 1) == 1 ) { 
        *P_SPI_FLASH_CMD = 1 << SPI_FLASH_RDSR;
        while ((*P_SPI_FLASH_CMD ) != 0 ); 
        temp = *P_SPI_FLASH_STATUS ;
     }
  } 
  *(P_SPI_FLASH_CTRL) = (*P_SPI_FLASH_CTRL) | (1 << SPI_ENABLE_AHB ) ; 
  return 0;
}

struct spi_flash flash = {
	NULL, \
	"fbc_spi_flash", \
	SPI_SIZE, \
	read_from_spi, \
	write_to_spi, \
	erase_spi,
	
};

int register_arc_spi_flash()
{	
	register_spi_flash(&flash);
	return 0;
}

