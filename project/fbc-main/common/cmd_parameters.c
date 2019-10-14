#include <cmd.h>

const cmd_def_t cmd_def[MAX_CMD] = {
	//Index start 0x00
	{0x13, 0x08, 0xFAA5, 1, 0, 0},// Index offset 0x0
	{5, 1, 3, 0, 0, 0},// Index offset 0x1
	{1, 0, 0, 0, 0, 0},// Index offset 0x2
	{0, 0, 0, 0, 0, 0},// Index offset 0x3
	{1, 0, 0, 0x401, 0x400, 0},// Index offset 0x4
	{2, 1, 1, 0, 0, 0},// Index offset 0x5
	{2, 1, 1, 0, 0, 0},// Index offset 0x6
	{0, 0, 0, 0, 0, 0},// Index offset 0x7
	{1, 0, 0, 0, 0, 0},// Index offset 0x8
	{3, 2, 5, 0, 0, 0},// Index offset 0x9
	{0, 0, 0, 0, 0, 0},// Index offset 0xa
	{2, 1, 1, 0, 0, 0},// Index offset 0xb
	{2, 1, 1, 0, 0, 0},// Index offset 0xc
	{2, 1, 1, 0, 0, 0},// Index offset 0xd
	{2, 1, 1, 0, 0, 0},// Index offset 0xe
	{2, 1, 1, 0, 0, 0},// Index offset 0xf

	//Index start 0x10
	{33, 8, 0xFFFF, 0, 0, 0},// Index offset 0x0
	{1, 0, 0, 49, 48, 0xFFFF},// Index offset 0x1
	{0, 0, 0, 0, 0, 0},// Index offset 0x2
	{0, 0, 0, 0, 0, 0},// Index offset 0x3
	{2, 1, 1, 0, 0, 0},// Index offset 0x4
	{0, 0, 0, 0, 0, 0},// Index offset 0x5
	{2, 1, 1, 3, 2, 0x11},// Index offset 0x6
	{2, 0, 0, 1, 1, 1},// Index offset 0x7
	{5, 1, 0x3, 5, 1, 0x3},// Index offset 0x8
	{5, 1, 0x3, 5, 1, 0x3},// Index offset 0x9
	{9, 2, 0xf, 33, 8, 0xffff},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{0, 0, 0, 0, 0, 0},// Index offset 0xc
	{2, 1, 0x0001, 1, 0, 0},// Index offset 0xd
	{2, 1, 0x0001, 1, 0, 0},// Index offset 0xe
	{2, 0, 0, 321, 320, 0xFFFF},// Index offset 0xf

	//Index start 0x20
	{2, 1, 1, 0, 0, 0},// Index offset 0x0
	{2, 1, 1, 0, 0, 0},// Index offset 0x1
	{2, 1, 1, 0, 0, 0},// Index offset 0x2
	{2, 1, 1, 0, 0, 0},// Index offset 0x3
	{2, 1, 1, 0, 0, 0},// Index offset 0x4
	{0, 0, 0, 0, 0, 0},// Index offset 0x5
	{2, 1, 1, 0, 0, 0},// Index offset 0x6
	{2, 1, 1, 0, 0, 0},// Index offset 0x7
	{2, 1, 1, 0, 0, 0},// Index offset 0x8
	{2, 1, 1, 0, 0, 0},// Index offset 0x9
	{2, 1, 1, 0, 0, 0},// Index offset 0xa
	{2, 1, 1, 0, 0, 0},// Index offset 0xb
	{0, 0, 0, 0, 0, 0},// Index offset 0xc
	{0, 0, 0, 0, 0, 0},// Index offset 0xd
	{0, 0, 0, 0, 0, 0},// Index offset 0xe
	{2, 1, 1, 0, 0, 0},// Index offset 0xf

	//Index start 0x30
	{0, 0, 0, 0, 0, 0},// Index offset 0x0
	{2, 1, 1, 0, 0, 0},// Index offset 0x1
	{2, 1, 1, 0, 0, 0},// Index offset 0x2
	{2, 1, 1, 0, 0, 0},// Index offset 0x3
	{2, 1, 1, 0, 0, 0},// Index offset 0x4
	{2, 1, 1, 0, 0, 0},// Index offset 0x5
	{2, 1, 1, 0, 0, 0},// Index offset 0x6
	{0, 0, 0, 0, 0, 0},// Index offset 0x7
	{2, 1, 1, 0, 0, 0},// Index offset 0x8
	{1, 0, 0, 0, 0, 0},// Index offset 0x9
	{2, 1, 1, 0, 0, 0},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{0, 0, 0, 0, 0, 0},// Index offset 0xc
	{0, 0, 0, 0, 0, 0},// Index offset 0xd
	{1, 0, 0, 0, 0, 0},// Index offset 0xe
	{3, 2, 5, 0, 0, 0},// Index offset 0xf

	//Index start 0x40
	{2, 1, 1, 0, 0, 0},// Index offset 0x0
	{2, 1, 1, 0, 0, 0},// Index offset 0x1
	{2, 1, 1, 0, 0, 0},// Index offset 0x2
	{2, 1, 1, 0, 0, 0},// Index offset 0x3
	{2, 1, 1, 0, 0, 0},// Index offset 0x4
	{2, 1, 1, 0, 0, 0},// Index offset 0x5
	{2, 1, 1, 0, 0, 0},// Index offset 0x6
	{2, 1, 1, 0, 0, 0},// Index offset 0x7
	{2, 1, 1, 0, 0, 0},// Index offset 0x8
	{0, 0, 0, 0, 0, 0},// Index offset 0x9
	{2, 1, 1, 0, 0, 0},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{8, 7, 0x1555, 0, 0, 0},// Index offset 0xc
	{4, 3, 0x15, 0, 0, 0},// Index offset 0xd
	{2, 1, 1, 0, 0, 0},// Index offset 0xe
	{0, 0, 0, 0, 0, 0},// Index offset 0xf

	//Index start 0x50
	{2, 1, 1, 0, 0, 0},// Index offset 0x0
	{2, 1, 1, 0, 0, 0},// Index offset 0x1
	{3, 2, 1, 0, 0, 0},// Index offset 0x2
	{2, 1, 1, 0, 0, 0},// Index offset 0x3
	{2, 1, 1, 0, 0, 0},// Index offset 0x4
	{3, 2, 1, 0, 0, 0},// Index offset 0x5
	{2, 1, 1, 0, 0, 0},// Index offset 0x6
	{2, 1, 1, 0, 0, 0},// Index offset 0x7
	{2, 1, 1, 0, 0, 0},// Index offset 0x8
	{2, 1, 1, 0, 0, 0},// Index offset 0x9
	{1, 0, 0, 2, 1, 1},// Index offset 0xa
	{1, 0, 0, 2, 1, 1},// Index offset 0xb
	{1, 0, 0, 3, 2, 5},// Index offset 0xc
	{1, 0, 0, 2, 1, 1},// Index offset 0xd
	{1, 0, 0, 2, 1, 1},// Index offset 0xe
	{1, 0, 0, 3, 2, 5},// Index offset 0xf

	//Index start 0x60
	{1, 0, 0, 2, 1, 1},// Index offset 0x0
	{1, 0, 0, 2, 1, 1},// Index offset 0x1
	{1, 0, 0, 2, 1, 1},// Index offset 0x2
	{1, 0, 0, 2, 1, 1},// Index offset 0x3
	{2, 1, 1, 0, 0, 0},// Index offset 0x4
	{0, 0, 0, 0, 0, 0},// Index offset 0x5
	{33, 8, 0xFFFF, 0, 0, 0},// Index offset 0x6
	{1, 0, 0, 49, 48, 0xFFFF},// Index offset 0x7
	{0, 0, 0, 0, 0, 0},// Index offset 0x8
	{0, 0, 0, 0, 0, 0},// Index offset 0x9
	{0, 0, 0, 0, 0, 0},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{0, 0, 0, 0, 0, 0},// Index offset 0xc
	{0, 0, 0, 0, 0, 0},// Index offset 0xd
	{0, 0, 0, 0, 0, 0},// Index offset 0xe
	{0, 0, 0, 0, 0, 0},// Index offset 0xf

	//Index start 0x70
	{0, 0, 0, 0, 0, 0},// Index offset 0x0
	{0, 0, 0, 0, 0, 0},// Index offset 0x1
	{0, 0, 0, 0, 0, 0},// Index offset 0x2
	{0, 0, 0, 0, 0, 0},// Index offset 0x3
	{0, 0, 0, 0, 0, 0},// Index offset 0x4
	{0, 0, 0, 0, 0, 0},// Index offset 0x5
	{0, 0, 0, 0, 0, 0},// Index offset 0x6
	{0, 0, 0, 0, 0, 0},// Index offset 0x7
	{0, 0, 0, 0, 0, 0},// Index offset 0x8
	{0, 0, 0, 0, 0, 0},// Index offset 0x9
	{0, 0, 0, 0, 0, 0},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{0, 0, 0, 0, 0, 0},// Index offset 0xc
	{0, 0, 0, 0, 0, 0},// Index offset 0xd
	{0, 0, 0, 0, 0, 0},// Index offset 0xe
	{0, 0, 0, 0, 0, 0},// Index offset 0xf

	//Index start 0x80
	{0, 0, 0, 0, 0, 0},// Index offset 0x0
	{0, 0, 0, 0, 0, 0},// Index offset 0x1
	{0, 0, 0, 0, 0, 0},// Index offset 0x2
	{0, 0, 0, 0, 0, 0},// Index offset 0x3
	{0, 0, 0, 0, 0, 0},// Index offset 0x4
	{0, 0, 0, 0, 0, 0},// Index offset 0x5
	{0, 0, 0, 0, 0, 0},// Index offset 0x6
	{0, 0, 0, 0, 0, 0},// Index offset 0x7
	{0, 0, 0, 0, 0, 0},// Index offset 0x8
	{0, 0, 0, 0, 0, 0},// Index offset 0x9
	{0, 0, 0, 0, 0, 0},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{0, 0, 0, 0, 0, 0},// Index offset 0xc
	{0, 0, 0, 0, 0, 0},// Index offset 0xd
	{0, 0, 0, 0, 0, 0},// Index offset 0xe
	{0, 0, 0, 0, 0, 0},// Index offset 0xf

	//Index start 0x90
	{0, 0, 0, 0, 0, 0},// Index offset 0x0
	{0, 0, 0, 0, 0, 0},// Index offset 0x1
	{0, 0, 0, 0, 0, 0},// Index offset 0x2
	{0, 0, 0, 0, 0, 0},// Index offset 0x3
	{0, 0, 0, 0, 0, 0},// Index offset 0x4
	{0, 0, 0, 0, 0, 0},// Index offset 0x5
	{0, 0, 0, 0, 0, 0},// Index offset 0x6
	{0, 0, 0, 0, 0, 0},// Index offset 0x7
	{0, 0, 0, 0, 0, 0},// Index offset 0x8
	{0, 0, 0, 0, 0, 0},// Index offset 0x9
	{0, 0, 0, 0, 0, 0},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{0, 0, 0, 0, 0, 0},// Index offset 0xc
	{0, 0, 0, 0, 0, 0},// Index offset 0xd
	{0, 0, 0, 0, 0, 0},// Index offset 0xe
	{0, 0, 0, 0, 0, 0},// Index offset 0xf

	//Index start 0xA0
	{0, 0, 0, 0, 0, 0},// Index offset 0x0
	{0, 0, 0, 0, 0, 0},// Index offset 0x1
	{1, 0, 0, 2, 1, 1},// Index offset 0x2
	{1, 0, 0, 2, 1, 1},// Index offset 0x3
	{1, 0, 0, 2, 1, 1},// Index offset 0x4
	{0, 0, 0, 0, 0, 0},// Index offset 0x5
	{1, 0, 0, 2, 1, 1},// Index offset 0x6
	{0, 0, 0, 0, 0, 0},// Index offset 0x7
	{1, 0, 0, 2, 1, 1},// Index offset 0x8
	{1, 0, 0, 2, 1, 1},// Index offset 0x9
	{1, 0, 0, 2, 1, 1},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{0, 0, 0, 0, 0, 0},// Index offset 0xc
	{0, 0, 0, 0, 0, 0},// Index offset 0xd
	{0, 0, 0, 0, 0, 0},// Index offset 0xe
	{0, 0, 0, 0, 0, 0},// Index offset 0xf

	//Index start 0xB0
	{0, 0, 0, 0, 0, 0},// Index offset 0x0
	{1, 0, 0, 2, 1, 1},// Index offset 0x1
	{1, 0, 0, 2, 1, 1},// Index offset 0x2
	{1, 0, 0, 2, 1, 1},// Index offset 0x3
	{1, 0, 0, 2, 1, 1},// Index offset 0x4
	{1, 0, 0, 2, 1, 1},// Index offset 0x5
	{1, 0, 0, 2, 1, 1},// Index offset 0x6
	{0, 0, 0, 0, 0, 0},// Index offset 0x7
	{0, 0, 0, 0, 0, 0},// Index offset 0x8
	{0, 0, 0, 0, 0, 0},// Index offset 0x9
	{0, 0, 0, 0, 0, 0},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{0, 0, 0, 0, 0, 0},// Index offset 0xc
	{0, 0, 0, 0, 0, 0},// Index offset 0xd
	{0, 0, 0, 0, 0, 0},// Index offset 0xe
	{0, 0, 0, 0, 0, 0},// Index offset 0xf

	//Index start 0xC0
	{1, 0, 0, 2, 1, 1},// Index offset 0x0
	{1, 0, 0, 2, 1, 1},// Index offset 0x1
	{1, 0, 0, 2, 1, 1},// Index offset 0x2
	{1, 0, 0, 2, 1, 1},// Index offset 0x3
	{1, 0, 0, 2, 1, 1},// Index offset 0x4
	{1, 0, 0, 2, 1, 1},// Index offset 0x5
	{1, 0, 0, 2, 1, 1},// Index offset 0x6
	{1, 0, 0, 2, 1, 1},// Index offset 0x7
	{1, 0, 0, 2, 1, 1},// Index offset 0x8
	{0, 0, 0, 0, 0, 0},// Index offset 0x9
	{1, 0, 0, 2, 1, 1},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{2, 1, 1, 8, 7, 0x1555},// Index offset 0xc
	{0, 0, 0, 0, 0, 0},// Index offset 0xd
	{0, 0, 0, 0, 0, 0},// Index offset 0xe
	{0, 0, 0, 0, 0, 0},// Index offset 0xf

	//Index start 0xD0
	{0, 0, 0, 0, 0, 0},// Index offset 0x0
	{0, 0, 0, 0, 0, 0},// Index offset 0x1
	{0, 0, 0, 0, 0, 0},// Index offset 0x2
	{0, 0, 0, 0, 0, 0},// Index offset 0x3
	{0, 0, 0, 0, 0, 0},// Index offset 0x4
	{0, 0, 0, 0, 0, 0},// Index offset 0x5
	{0, 0, 0, 0, 0, 0},// Index offset 0x6
	{0, 0, 0, 0, 0, 0},// Index offset 0x7
	{0, 0, 0, 0, 0, 0},// Index offset 0x8
	{0, 0, 0, 0, 0, 0},// Index offset 0x9
	{0, 0, 0, 0, 0, 0},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{0, 0, 0, 0, 0, 0},// Index offset 0xc
	{0, 0, 0, 0, 0, 0},// Index offset 0xd
	{0, 0, 0, 0, 0, 0},// Index offset 0xe
	{0, 0, 0, 0, 0, 0},// Index offset 0xf

	//Index start 0xE0
	{0, 0, 0, 0, 0, 0},// Index offset 0x0
	{0, 0, 0, 0, 0, 0},// Index offset 0x1
	{0, 0, 0, 0, 0, 0},// Index offset 0x2
	{0, 0, 0, 0, 0, 0},// Index offset 0x3
	{0, 0, 0, 0, 0, 0},// Index offset 0x4
	{0, 0, 0, 0, 0, 0},// Index offset 0x5
	{0, 0, 0, 0, 0, 0},// Index offset 0x6
	{0, 0, 0, 0, 0, 0},// Index offset 0x7
	{0, 0, 0, 0, 0, 0},// Index offset 0x8
	{0, 0, 0, 0, 0, 0},// Index offset 0x9
	{0, 0, 0, 0, 0, 0},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{0, 0, 0, 0, 0, 0},// Index offset 0xc
	{0, 0, 0, 0, 0, 0},// Index offset 0xd
	{0, 0, 0, 0, 0, 0},// Index offset 0xe
	{0, 0, 0, 0, 0, 0},// Index offset 0xf

	//Index start 0xF0
	{0, 0, 0, 0, 0, 0},// Index offset 0x0
	{0, 0, 0, 0, 0, 0},// Index offset 0x1
	{0, 0, 0, 0, 0, 0},// Index offset 0x2
	{0, 0, 0, 0, 0, 0},// Index offset 0x3
	{0, 0, 0, 0, 0, 0},// Index offset 0x4
	{0, 0, 0, 0, 0, 0},// Index offset 0x5
	{0, 0, 0, 0, 0, 0},// Index offset 0x6
	{0, 0, 0, 0, 0, 0},// Index offset 0x7
	{0, 0, 0, 0, 0, 0},// Index offset 0x8
	{0, 0, 0, 0, 0, 0},// Index offset 0x9
	{0, 0, 0, 0, 0, 0},// Index offset 0xa
	{0, 0, 0, 0, 0, 0},// Index offset 0xb
	{0, 0, 0, 0, 0, 0},// Index offset 0xc
	{0, 0, 0, 0, 0, 0},// Index offset 0xd
	{0, 0, 0, 0, 0, 0},// Index offset 0xe
	{0, 0, 0, 0, 0, 0},// Index offset 0xf

};

