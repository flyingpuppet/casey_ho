MEMORY {
  ROM: ORIGIN = 0x40000000 LENGTH = 256K
  CODE_MEM: ORIGIN = 0x00000000 LENGTH = 128K
  DATA_MEM: ORIGIN = 0xffff0000 LENGTH = 64K
  SRAM1: ORIGIN = 0x70020000 LENGTH = 64K
  SRAM2: ORIGIN = 0x80020000 LENGTH = 64K
}

SECTIONS {
  GROUP: {
    .start : { vtable.o (.text) }
    _TEXT_START = .;
    .text : {} 
    * (TEXT): {} 
    _TEXT_END = .;
  } > CODE_MEM
  GROUP: {
    .rodata : {}
  } > CODE_MEM
  GROUP: {
    .data: { *(.data) }
    .data1: { *(.data1) }
    .tls: { *(.tls) }
    .bss: { *(.bss) }
    .heap : { _fheap = . ;  *(.heap) ; _eheap = 0xffffdffc ; }
  } > DATA_MEM
  GROUP: {
    .stack ADDR(0xffffe000) SIZE(8K-16): {}
  } > DATA_MEM
}
