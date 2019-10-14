//---------------------------------------------------------------------------

#ifndef elf_headerH
#define elf_headerH



#define EI_NIDENT 16

#define BIT_I	0
#define BIT_S   1
#define BIT_L   2

#define INFO(a) 	((a >> BIT_I) & 0x1)
#define SCRIPT(a) ((a >> BIT_S) & 0x1)
#define LOG(a) 		((a >> BIT_L) & 0x1)

#define SWAP_LONG(a)	((a >> 24) & 0xff) | ((a >> 16) & 0xff00) | ((a << 24) & 0xff0000) | ((a << 16) & 0xff000000)
#define SWAP_SHORT(a)	((a >> 8) & 0xff) | ((a << 8) & 0xff00)

typedef unsigned int   Elf32_Addr;
typedef unsigned short Elf32_Half;
typedef unsigned int   Elf32_Off;
typedef signed int     Elf32_Sword;
typedef unsigned int   Elf32_Word;

typedef struct{
	unsigned char e_ident[EI_NIDENT];
	Elf32_Half    e_type;
	Elf32_Half    e_machine;
	Elf32_Word    e_version;
	Elf32_Addr    e_entry;
	Elf32_Off     e_phoff;
	Elf32_Off     e_shoff;
	Elf32_Word    e_flags;
	Elf32_Half    e_ehsize;
	Elf32_Half    e_phentsize;
	Elf32_Half    e_phnum;
	Elf32_Half    e_shentsize;
	Elf32_Half    e_shnum;
	Elf32_Half    e_shstrndx;
} Elf32_Ehdr;



typedef struct{
	Elf32_Word    p_type;
	Elf32_Off     p_offset;
	Elf32_Addr    p_vaddr;
	Elf32_Addr    p_paddr;
	Elf32_Word    p_filesz;
	Elf32_Word    p_memsz;
	Elf32_Word    p_flags;
	Elf32_Word    p_align;
} Elf32_Phdr;


typedef struct{
	Elf32_Word    sh_name;
	Elf32_Word    sh_type;
	Elf32_Word    sh_flags;
	Elf32_Addr    sh_addr;
	Elf32_Off     sh_offset;
	Elf32_Word    sh_size;
	Elf32_Word    sh_link;
	Elf32_Word    sh_info;
	Elf32_Word    sh_addralign;
	Elf32_Word    sh_entsize;
} Elf32_Shdr;



typedef enum {big = 0, little} _Endian;


//---------------------------------------------------------------------------
#endif


