ifeq ($(OS), Windows_NT)
    include ../makefile_windows
else
  ifeq ($(ARC_COMPILER), GNU)
    include ../makefile_gnu
  else
    ifeq ($(ARC_COMPILER), METAWARE)
      include ../makefile_metaware
    endif
  endif
endif

LD_LIB_PATH=$(ARC_TOOLCHAIN_PATH)/../lib/a6
CC_FLAGS+= -I./../include/vpp/
CC_FLAGS+= -I./../project/include/
ASM_FLAGS+= -I./../include/vpp/
ASM_FLAGS+= -I./../project/include/

BOOT_LIB = fbc_boot.a
SUSPEND_LIB = fbc_suspend.a
UPDATE_LIB = fbc_update.a

SRCS     = boot.c
ifeq ($(wildcard ../rom_map.c),)
else
SRCS     += ../rom_map.c
CC_FLAGS_ADD += -DHAS_ROM_MAP
endif
SRCS += ../common/build_version.c
SSRCS	 = boot_rom.s
DRVSRCS = ../driver/uart.c
DRVSRCS += ../driver/clock.c
DRVSRCS += ../driver/spi_flash.c
DRVSRCS += ../driver/input/remote.c
DRVSRCS += ../driver/input/saradc.c
DRVSRCS += ../common/reboot.c

COMSRCS = ../common/printf.c
COMSRCS += ../common/console.c
COMSRCS += ../common/command.c
COMSRCS += ../common/check.c
COMSRCS += ../common/crc32.c
COMSRCS += ../common/cmd_reboot.c
COMSRCS += ../common/cmd_update.c
COMSRCS += ../common/cmd_suspend.c
COMSRCS += ../common/cmd_boot.c
COMSRCS += ../common/cmd_test.c
COMSRCS += ../common/cmd_debug.c

PRJ_SRCS    = ../project/customer_key_conf.c

SOBJS    = $(SSRCS:%.s=%.o$(SUFFIX)) 
OBJS     = $(SRCS:%.c=%.o$(SUFFIX)) $(PRJ_SRCS:%.c=%.o$(SUFFIX))
LIB_OBJS = $(DRVSRCS:%.c=%.o$(SUFFIX)) $(COMSRCS:%.c=%.o$(SUFFIX)) $(PRJ_SRCS:%.c=%.o$(SUFFIX))

SUS_SSRCS	= boot_rom.s
SUS_SRCS    = suspend.c
SUS_SRCS    += ../project/customer_key_conf.c
SUS_DRVSRCS = ../driver/uart.c
SUS_DRVSRCS += ../driver/clock.c
SUS_DRVSRCS += ../driver/input/remote.c
SUS_DRVSRCS += ../driver/input/saradc.c
SUS_COMSRCS += ../common/reboot.c

SUS_SOBJS    = $(SUS_SSRCS:%.s=%.o$(SUFFIX)) 
SUS_OBJS     = $(SUS_SRCS:%.c=%.o$(SUFFIX))
SUS_LIB_OBJS = $(SUS_DRVSRCS:%.c=%.o$(SUFFIX)) $(SUS_COMSRCS:%.c=%.o$(SUFFIX))

UDRVSRCS = ../driver/uart.c
UDRVSRCS += ../driver/clock.c
UDRVSRCS += ../driver/spi_flash.c
UDRVSRCS += ../driver/sosd.c
UDRVSRCS += ../driver/timer.c
UDRVSRCS += ../driver/interrupt.c
UDRVSRCS += ../driver/input/uart.c
UDRVSRCS += ../driver/vpp/hdmirx.c
UDRVSRCS += ../driver/vpp/clk_vpp.c
UDRVSRCS += ../driver/vpp/srcif.c
UDRVSRCS += ../driver/vpp/vpp.c
UDRVSRCS += ../driver/vpp/vpu_util.c
UDRVSRCS += ../driver/vpp/vbyone.c
UDRVSRCS += ../driver/pwm.c

UCOMSRCS +=../common/printf.c
UCOMSRCS = ../common/console.c
UCOMSRCS += ../common/reboot.c
UCOMSRCS += ../common/osd.c
UCOMSRCS += ../common/check.c
UCOMSRCS += ../common/crc32.c

UPROJSRCS = ../project/panel.c

LIB_UDRVOBJS = $(UDRVSRCS:%.c=%.o$(SUFFIX)) $(UCOMSRCS:%.c=%.o$(SUFFIX)) $(UPROJSRCS:%.c=%.o$(SUFFIX))

USRCS = update_main.c
USRCS += update.c
USSRCS = ../driver/vtable.s
UOBJS = $(USSRCS:%.s=%.o$(SUFFIX)) $(USRCS:%.c=%.o$(SUFFIX))


export CC_FLAGS_ADD
export ASM_FLAGS_ADD
export LD_FLAGS_ADD

all : clean rom_boot.elf rom_suspend.elf rom_update.elf

fbc_boot.a: $(LIB_OBJS)
	$(AR) -c $@ $(LIB_OBJS)

fbc_suspend.a: $(SUS_LIB_OBJS)
	$(AR) -c $@ $(SUS_LIB_OBJS)
	
fbc_update.a: $(LIB_UDRVOBJS)
	$(AR) -c $@ $(LIB_UDRVOBJS)

rom_boot.elf: $(SOBJS) $(OBJS) $(BOOT_LIB)
	$(LD) $(SOBJS) $(OBJS) $(BOOT_LIB) $(LD_FLAGS) boot.cmd -o boot.elf
	$(DUMPELF) $(DUMP_FLAGS) boot.elf > boot.asm
	$(CP) boot.elf rom_boot.elf
	$(STRIP) $(STRIP_FALGS) rom_boot.elf
	$(OBJCOPY) $(COPY_FLAGS) $@ -o rom_boot_code.bin -ctl
	$(OBJCOPY) $(COPY_FLAGS) $@ -o rom_boot_data.bin -cd
	$(DUMPELF) $(DUMP_FLAGS) $@ > rom_boot.asm

rom_suspend.elf: $(SUS_SOBJS) $(SUS_OBJS) $(SUSPEND_LIB)
	$(LD) $(SUS_SOBJS) $(SUS_OBJS) $(SUSPEND_LIB) $(LD_FLAGS) suspend.cmd -o suspend.elf
	$(DUMPELF) $(DUMP_FLAGS) suspend.elf > suspend.asm
	$(CP) suspend.elf rom_suspend.elf
	$(STRIP) $(STRIP_FALGS) suspend.elf
	$(OBJCOPY) $(COPY_FLAGS) $@ -o rom_suspend_code.bin -ctl
	$(OBJCOPY) $(COPY_FLAGS) $@ -o rom_suspend_data.bin -cd
	$(DUMPELF) $(DUMP_FLAGS) $@ > rom_suspend.asm
	
rom_update.elf: $(UOBJS) $(UPDATE_LIB)
	$(LD) $(UOBJS) $(UPDATE_LIB) $(LD_LIB_PATH)/le/crt1.o $(LD_LIB_PATH)/le/crti.o $(LD_FLAGS) update.cmd -lhlt -e _start -o update.elf
	$(DUMPELF) $(DUMP_FLAGS) update.elf > rom_update.asm
	cp update.elf rom_update.elf
	$(STRIP) $(STRIP_FALGS) rom_update.elf
	$(OBJCOPY) $(COPY_FLAGS) $@ -o rom_update_code.bin -ctl
	$(OBJCOPY) $(COPY_FLAGS) $@ -o rom_update_data.bin -cd
	$(DUMPELF) $(DUMP_FLAGS) $@ > rom_update.asm
	
rom: clean rom_boot.elf rom_suspend.elf rom_update.elf
	$(MK) -f makefile.rom

debug_boot.elf: clean $(OBJS) $(LIB_OBJS)
	$(LD) $(OBJS) $(LIB_OBJS) $(LD_LIB_PATH)/le/crt1.o $(LD_LIB_PATH)/le/crti.o $(LD_FLAGS) debug.cmd -o $@
	$(DUMPELF) $(DUMP_FLAGS) $@ > debug_boot.asm

debug: clean debug_boot.elf

clean:
	@$(RM) $(BOOT_LIB)
	@$(RM) $(UPDATE_LIB)
	@$(RM) $(SUSPEND_LIB)
	@$(RM) $(SOBJS) $(OBJS) $(LIB_OBJS) $(UOBJS) $(LIB_UDRVOBJS) $(SUS_SOBJS) $(SUS_OBJS) $(SUS_LIB_OBJS)
	@$(RM) *.asm
	@$(RM) *.bin
	@$(RM) *.elf
	@$(RM) rom_boot*.hex
	@$(RM) rom_update*.hex
	@$(RM) rom_suspend*.hex
	@$(RM) -r ../../fbc_release/boot

.c.o:  
	$(CC) $(CC_FLAGS) $< -o $@

.s.o:  
	$(ASM) $(ASM_FLAGS) $< -o $@

release: clean fbc_boot.a fbc_suspend.a fbc_update.a
	$(RM) -r ../../fbc_release/boot
	$(MKDIR) ../../fbc_release/boot
	$(CP) ../boot ../../fbc_release/
	$(CP) ../boot/Makefile.rel ../../fbc_release/boot/Makefile
	$(MKDIR) ../../fbc_release/common

