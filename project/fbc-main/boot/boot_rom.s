    .equ SRAM_BASE, 0    
    .text    
	.global	_start
	.global jump_0

_start:
	nop
	nop
	mov r0, 0x00000000
	mov r1, 0x00000000
	mov r2, 0x00000000
	mov r3, 0x00000000
	mov r4, 0x00000000
	mov r5, 0x00000000
	mov r6, 0x00000000
	mov r7, 0x00000000
	mov r8, 0x00000000
	mov r9, 0x00000000
	mov r10, 0x00000000
	mov r11, 0x00000000
	mov r12, 0x00000000
	mov r13, 0x00000000
	mov r14, 0x00000000
	mov r15, 0x00000000
	mov r16, 0x00000000
	mov r17, 0x00000000
	mov r18, 0x00000000
	mov r19, 0x00000000
	mov r20, 0x00000000
	mov r21, 0x00000000
	mov r22, 0x00000000
	mov r23, 0x00000000
	mov r24, 0x00000000
	mov r25, 0x00000000
	mov r26, 0x00000000
	mov r27, 0x00000000
	mov r28, 0x00000000

; --- Initialize stack pointer registers

	mov  sp, 0xfffff000  ; Put sp in DCCM
	bl	main
	nop
	nop
	mov	r0, SRAM_BASE
	nop
	nop
	j	[%r0]	
	nop
	nop
	nop

jump_0:
	mov	r0, 0x0
	nop
	nop
	j	[%r0]

