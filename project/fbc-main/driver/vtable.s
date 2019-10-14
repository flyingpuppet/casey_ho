/*-------------------------------------------------------------- 
 * Save caller saved registers (scratch registers) ( r0 - r12 )
 * Registers are pushed / popped in the order defined in struct ptregs
 * in asm/ptrace.h
 *-------------------------------------------------------------*/
.macro  SAVE_CALLER_SAVED
    st.a    r0, [sp, -4]
    st.a    r1, [sp, -4]
    st.a    r2, [sp, -4]
    st.a    r3, [sp, -4]
    st.a    r4, [sp, -4]
    st.a    r5, [sp, -4]
    st.a    r6, [sp, -4]
    st.a    r7, [sp, -4]
    st.a    r8, [sp, -4]
    st.a    r9, [sp, -4]
    st.a    r10, [sp, -4]
    st.a    r11, [sp, -4]
    st.a    r12, [sp, -4]
    st.a    blink, [sp, -4]
    st.a    ilink2, [sp, -4]
    lr      r0, [lp_start]
    st.a    r0, [sp, -4]
    lr      r0, [lp_end]
    st.a    r0, [sp, -4]
    mov     r0, lp_count
    st.a    r0, [sp, -4]
.endm

/*-------------------------------------------------------------- 
 * Restore caller saved registers (scratch registers)
 *-------------------------------------------------------------*/
.macro RESTORE_CALLER_SAVED
    ld.ab   r0, [sp, 4]
    mov     lp_count,r0
    ld.ab   r0, [sp, 4]
    sr      r0, [lp_end]
    ld.ab   r0, [sp, 4]
    sr      r0, [lp_start]
    ld.ab   ilink2, [sp, 4]
    ld.ab   blink, [sp, 4]
    ld.ab   r12, [sp, 4]
    ld.ab   r11, [sp, 4]
    ld.ab   r10, [sp, 4]
    ld.ab   r9, [sp, 4]
    ld.ab   r8, [sp, 4]
    ld.ab   r7, [sp, 4]
    ld.ab   r6, [sp, 4]
    ld.ab   r5, [sp, 4]
    ld.ab   r4, [sp, 4]
    ld.ab   r3, [sp, 4]
    ld.ab   r2, [sp, 4]
    ld.ab   r1, [sp, 4]
    ld.ab   r0, [sp, 4]
.endm

    .extern Process_Irq
    .extern Process_Fiq
    .extern enable_interrupts

_vtable:
    j _start
    j inst_fail
    j mem_fail
    j proc_irq
    j proc_irq
    j proc_irq
    j proc_fiq
    j proc_fiq
    .rep 23
        j arc_fail
    .endr

arc_fail:
    j other_fail

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

	mov r0, 0x00000000
	SR  r0, [0x25] 

	mov 	r10,	0x201	; hardware interrupt register
	mov 	r15,	0x200	; priority register
	mov 	r12,	0x43	; sticky interrupt status register

	SR		0x00000040, [r15]	; set interrupt priority levels
	SR		0x00000003, [r12]	; clear LV12 register

	FLAG	0x6 				; enable level 1 and level 2 interrupts
	NOP

; --- Initialize stack pointer registers
	mov  sp, 0xfffff000  ; Put sp in DCCM
	bl	main
	nop

enable_interrupts:
SAVE_CALLER_SAVED
    mov     r10,    0x201   ; hardware interrupt register
    mov     r15,    0x200   ; priority register
    mov     r12,    0x43    ; sticky interrupt status register

    SR      0x00000040, [r15]   ; set interrupt priority levels
    SR      0x00000003, [r12]   ; clear LV12 register
;    SR      0x00000005, [r10]   ; Write interrupt number (HINT)
;    SR      0         , [r10]   ; Clear HINT
    FLAG    0x6                 ; enable level 1 and level 2 interrupts
    NOP
    NOP
RESTORE_CALLER_SAVED
    j_s     [%blink]
    nop_s

proc_irq:
SAVE_CALLER_SAVED
	NOP
	BL       read_int_ack
  	MOV      r10, r0
	NOP
	bl Process_Irq      ; irq5
	NOP
	MOV      r0, r10
	NOP
RESTORE_CALLER_SAVED
	jal.f [ilink1];
	
inst_fail:
    MOV     r0, 0xfffffffc
    ST      ilink1, [r0]
    MOV     r0, 0xfffffff8
    ST      ilink2, [r0]
    j       inst_fail

mem_fail:
    MOV     r0, 0xfffffffc
    ST      ilink1, [r0]
    MOV     r0, 0xfffffff8
    ST      ilink2, [r0]
    j       inst_fail
    
other_fail:
    MOV     r0, 0xfffffffc
    ST      ilink1, [r0]
    MOV     r0, 0xfffffff8
    ST      ilink2, [r0]
    j       inst_fail

proc_fiq:
SAVE_CALLER_SAVED
	NOP
	bl       read_int_ack
  	MOV      r10, r0
	NOP
	bl Process_Fiq      ; irq6
	NOP
	MOV      r0, r10
	NOP
RESTORE_CALLER_SAVED
	jal.f [ilink2];
