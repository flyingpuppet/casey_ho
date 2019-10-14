//---------------------------------------------------------------------------

#ifndef program_header_checkH
#define program_header_checkH


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elf_header.h"

extern _Endian endian;
extern int program_header_check(Elf32_Phdr& p_elf_hdr, int flag);
//---------------------------------------------------------------------------
#endif
