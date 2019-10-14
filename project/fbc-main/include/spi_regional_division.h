#ifndef SPI_REGIONAL_DIVISION_H
#define SPI_REGIONAL_DIVISION_H

#define MAX_NAME_LEN				0x10
#define CHECK_INFO_SIZE				0x20

#define COMPLETE_SPI_MAGIC			0x12345678
#define BOOT_SPI_MAGIC				0x11111111
#define MAIN_CODE_SPI_MAGIC			0x22222222
#define MAIN_DATA_SPI_MAGIC			0x33333333
#define MAIN_RODATA_SPI_MAGIC		0x44444444
#define MAIN_PARAM_SPI_MAGIC		0x55555555

#define ICCM_BASE	0x00000000
#define ICCM_SIZE	0x20000
#define DCCM_BASE	0xffff0000
#define DCCM_SIZE	0x10000
#define SRAM1_BASE	0x70020000
#define SRAM2_BASE	0x80020000
#define SRAM_SIZE	0x10000

typedef struct {
	char name[MAX_NAME_LEN];
	unsigned int magic;
	unsigned int crc;
	unsigned int size;
	
} check_info_t;

int check_image(unsigned s_offs, int size);

/*	fbc-boot (spi offset range: 0~0x1ffff, size:128K)
* 		use 20K(0K~20K) in SPI for boot code/rodata
* 		use 6K(24K~30K) in SPI for suspend code/rodata
*		use 72K(32K~104K) in SPI for update code/rodata
*		use 4K(20K~24K) in SPI for boot data -> copy -> 	SRAM2 4K(0x80020000~0x80021000) for data and bss
*		use 2K(30K~32K) in SPI for suspend data -> copy -> 	SRAM2 2K(0x80020000~0x80020800) for data and bss
*		use 24K(104K~128K) in SPI for update data -> copy -> 	SRAM2 24K(0x80020000~0x80026000) for data and bss
*				DCCM(ffffe000~0xffffefff) 4K stack(* overlap with main code stack)
*/
#define SPI_BASE							0x40000000

#define BOOT_CODE_SIZE						0x5000
#define BOOT_DATA_SIZE						0x1000

#define SUSPEND_CODE_SIZE					0x1800
#define SUSPEND_DATA_SIZE					0x800

#define UPDATE_CODE_SIZE					0x12000
#define UPDATE_DATA_SIZE					0x6000

#define BOOT_CODE_BASE						SPI_BASE
#define BOOT_DATA_BASE						(SPI_BASE + BOOT_CODE_SIZE)

#define SUSPEND_CODE_BASE					(BOOT_DATA_BASE + BOOT_DATA_SIZE)
#define SUSPEND_DATA_BASE					(SUSPEND_CODE_BASE + SUSPEND_CODE_SIZE)

#define UPDATE_CODE_BASE					(SUSPEND_DATA_BASE + SUSPEND_DATA_SIZE)

#define UPDATE_DATA_BASE					(UPDATE_CODE_BASE + UPDATE_CODE_SIZE)

#define BOOT_AREA_SIZE						(BOOT_CODE_SIZE + BOOT_DATA_SIZE + SUSPEND_CODE_SIZE + SUSPEND_DATA_SIZE + UPDATE_CODE_SIZE + UPDATE_DATA_SIZE)

#define FBC_BOOT_BASE_OFFSET				0x0

/*	fbc-main (spi offset range: 0x10000~0x7ffff, size:448K)
* 		use 128K(0k~127k) in SPI for code -> copy ->	ICCM(00000000~0x0000ffff) 64K code and readonly
*		use 64K(128K~191K) in SPI for data -> copy ->	DCCM(ffff0000~0xffffdfff) 56K data and bss(initialize to zero) total
*		use 64K(192K~255K) in SPI for data
*		use 180K(256K~435K) in SPI for rodata
*		use 76K(436K~511K) in SPI for param
*				DCCM(ffffe000~0xffffffff) 8K stack
*				SRAM1(0x70020000~0x7002ffff) 64K reserved for hw buffer
*				SRAM2(0x80024000~0x8002ffff) 48K reserved for hw buffer
*/
#define MAIN_CODE_BASE						(UPDATE_DATA_BASE + UPDATE_DATA_SIZE)
#define MAIN_CODE_SIZE						0x20000

#define MAIN_DATA_BASE						(MAIN_CODE_BASE + MAIN_CODE_SIZE)
#define MAIN_DATA_SIZE						0x10000

#define MAIN_SPI_CODE_BASE					(MAIN_DATA_BASE + MAIN_DATA_SIZE)
#define MAIN_SPI_CODE_SIZE					0x10000

#define MAIN_RODATA_BASE					(MAIN_SPI_CODE_BASE + MAIN_SPI_CODE_SIZE)
#define MAIN_RODATA_SIZE					0x2D000

#define FBC_MAIN_BASE_OFFSET				(MAIN_CODE_BASE - SPI_BASE)

//#ifdef IN_FBC_MAIN_CONFIG
/*	param (size:76K)
*		use 8k  for audio
*		use 44k  for PQ
*		the rest 24K for other
*/
#define PARAM_SIZE							0x10000
#define AUDIO_PARAM_AREA_SIZE				0x2000
#define PQ_PARAM_AREA_SIZE					0xB000
#define RESERVED_PARAM_AREA_SIZE			0x6000

#define PARAM_AREA_BASE						(MAIN_RODATA_BASE + MAIN_RODATA_SIZE)
#define PARAM_AREA_BASE_OFFSET				(MAIN_RODATA_BASE + MAIN_RODATA_SIZE - SPI_BASE)
#define AUDIO_PARAM_AREA_BASE_OFFSET		(PARAM_AREA_BASE_OFFSET)
#define PQ_PARAM_AREA_BASE_OFFSET			(AUDIO_PARAM_AREA_BASE_OFFSET + AUDIO_PARAM_AREA_SIZE)
#define SYSTEM_PARAM_AREA_BASE_OFFSET		(PQ_PARAM_AREA_BASE_OFFSET + PQ_PARAM_AREA_SIZE)

/*
*	backup base offset
*/
#define BACKUP_BASE_OFFSET		(SYSTEM_PARAM_AREA_BASE_OFFSET + RESERVED_PARAM_AREA_SIZE)
#define PARAM_AREA_BACKUP_BASE_OFFSET		(BASE_OFFSET + MAIN_CODE_SIZE + MAIN_DATA_SIZE + MAIN_RODATA_SIZE)

//#endif
#endif
