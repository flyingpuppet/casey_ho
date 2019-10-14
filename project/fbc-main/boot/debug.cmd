MEMORY {
  CODE_MEM: ORIGIN = 0x00000000 LENGTH = 128K
  DATA_MEM: ORIGIN = 0xffffe000 LENGTH = 8K
  SRAM1: ORIGIN = 0x70020000 LENGTH = 64K
  SRAM2: ORIGIN = 0x80020000 LENGTH = 64K
}

SECTIONS {
  GROUP: {
    .text : {} 
    * (TEXT): {} 
    .rodata: { *(.rodata) }
  } > CODE_MEM
  GROUP: {
    .data: { *(.data) }
    .data1: { *(.data1) }
    .bss: { *(.bss) }
    .tls?: { *(.tls) }
  } > SRAM2
  GROUP: {
    .stack SIZE(4K): {}
  } > DATA_MEM
}
