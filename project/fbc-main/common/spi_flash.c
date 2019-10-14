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
extern int register_arc_spi_flash();

static struct spi_flash *current_spi_flash = NULL;

int register_spi_flash(struct spi_flash *spi)
{
	current_spi_flash = spi;
	return 0;
}

int spi_flash_read(struct spi_flash *flash, unsigned int offset, unsigned int len, void *buf)
{
	return flash->read(flash, offset, len, buf);
}

int spi_flash_write(struct spi_flash *flash, unsigned int offset, unsigned int len, const void *buf)
{
	return flash->write(flash, offset, len, buf);
}

int spi_flash_erase(struct spi_flash *flash, unsigned int offset, unsigned int len)
{
	return flash->erase(flash, offset, len);
}

struct spi_flash *spi_flash_probe(unsigned int bus, unsigned int cs, unsigned int max_hz, unsigned int spi_mode)
{
	register_arc_spi_flash();
	return current_spi_flash;
}
