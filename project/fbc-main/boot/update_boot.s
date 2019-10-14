_vtable:
    j _start
    j arc_fail
    j arc_fail
    j arc_fail
    j arc_fail
    j arc_fail
    j arc_fail
    j arc_fail
    .rep 23
        j arc_fail
    .endr

arc_fail:
    j arc_fail

_start:
	nop
	nop
	
; --- Initialize stack pointer registers
	mov  sp, 0xfffff000  ; Put sp in DCCM
	bl	main
	nop
