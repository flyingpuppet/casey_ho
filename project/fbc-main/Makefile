ifeq ($(OS), Windows_NT)
    include makefile_windows_main
else
  ifeq ($(ARC_COMPILER), GNU)
    include makefile_gnu_main
  else
    ifeq ($(ARC_COMPILER), METAWARE)
      include makefile_metaware_main
    endif
  endif
endif

PRODUCT = fbc-boot
VERSION = v1.0
VERSION_FILE = version_autogenarated.h

ROM_PARAM_FILES = project/rom_audioparam project/rom_pqparam project/rom_sysparam

LD_LIB_PATH=$(ARC_TOOLCHAIN_PATH)/../lib/a6
CC_FLAGS+= -I./include/vpp/
CC_FLAGS+= -I./project/include/
ASM_FLAGS+= -I./include/vpp/
ASM_FLAGS+= -I./project/include/

CC_FLAGS += -DIN_FBC_MAIN_CONFIG
ASM_FLAGS += -DIN_FBC_MAIN_CONFIG

SSRCS	= driver/vtable.s

MAIN    = main.c
SRCS	= common/printf.c
SRCS	+= common/console.c
SRCS	+= common/command.c
SRCS	+= common/cmd_test.c
SRCS	+= common/cmd_suspend.c
SRCS	+= common/cmd_debug.c
SRCS	+= common/dbg_task.c
SRCS	+= common/cmd_reboot.c
SRCS	+= common/cmd_sf.c
SRCS    += common/cmd_parameters.c
SRCS	+= common/test_running_spi.c
SRCS	+= common/build_version.c

PRJ_SRCS    += project/user_setting.c
PRJ_SRCS	+= project/panel.c
PRJ_SRCS	+= project/ui.c
PRJ_SRCS    += project/customer_key_conf.c

LIB_SRCS	= driver/interrupt.c
LIB_SRCS	+= driver/sosd.c
LIB_SRCS	+= driver/pwm.c
LIB_SRCS	+= driver/input/remote.c
LIB_SRCS	+= driver/input/saradc.c
LIB_SRCS	+= driver/input/input.c
LIB_SRCS	+= driver/input/uart.c
LIB_SRCS	+= driver/input/cmd.c
LIB_SRCS	+= driver/uart.c
LIB_SRCS	+= driver/timer.c
LIB_SRCS	+= driver/vpp/clk_vpp.c
LIB_SRCS	+= driver/vpp/hdmirx.c
LIB_SRCS	+= driver/vpp/hdmirx_wrapper.c
LIB_SRCS	+= driver/vpp/srcif.c
LIB_SRCS	+= driver/vpp/vbyone.c
LIB_SRCS	+= driver/vpp/vpu_util.c
LIB_SRCS	+= driver/vpp/vpp.c
LIB_SRCS	+= common/task.c
LIB_SRCS	+= common/osd.c
LIB_SRCS	+= common/listop.c
LIB_SRCS	+= common/log.c
LIB_SRCS	+= common/crc32.c
LIB_SRCS	+= common/reboot.c
LIB_SRCS	+= driver/spi_flash.c
LIB_SRCS	+= driver/i2c.c
LIB_SRCS    += driver/clock.c
LIB_SRCS	+= driver/audio/aml_audio.c
LIB_SRCS	+= driver/audio/audio_control.c
LIB_SRCS	+= driver/audio/codecs/tas5707.c
LIB_SRCS	+= driver/audio/codecs/tas5711.c
LIB_SRCS	+= common/uart_communication_task.c

LIB_HEADERS  = include/cmd_config.h
LIB_HEADERS += include/cmd.h
LIB_HEADERS += include/command.h
LIB_HEADERS += include/common.h
LIB_HEADERS += include/config.h
LIB_HEADERS += include/input.h
LIB_HEADERS += include/inputdata.h
LIB_HEADERS += include/key_const.h
LIB_HEADERS += include/listop.h
LIB_HEADERS += include/log.h
LIB_HEADERS += include/osd.h
LIB_HEADERS += include/serial.h
LIB_HEADERS += include/spi_flash.h
LIB_HEADERS += include/task.h
LIB_HEADERS += include/timer.h
LIB_HEADERS += include/update.h
LIB_HEADERS += include/XYmemoryMapping.h
LIB_HEADERS += include/arc600.h
LIB_HEADERS += include/audio_param.h
LIB_HEADERS += include/crc.h
LIB_HEADERS += include/i2c.h
LIB_HEADERS += include/clock.h
LIB_HEADERS += include/version.h
LIB_HEADERS += include/reboot.h
LIB_HEADERS += include/gpio.h
LIB_HEADERS += include/interrupt.h
LIB_HEADERS += include/uart_api.h
LIB_HEADERS += include/remote.h
LIB_HEADERS += include/vpp/vpp_api.h
LIB_HEADERS += include/task_priority.h
LIB_HEADERS += include/spi_regional_division.h
LIB_HEADERS += include/pwm.h
LIB_HEADERS += include/panel.h
LIB_HEADERS += include/user_setting.h

LIB_PROJECT_HEADERS += project/include/project.h
LIB_PROJECT_HEADERS += project/include/fonts.h
LIB_PROJECT_HEADERS += project/include/customer_key_conf.h

SOBJ     = $(SSRCS:%.s=%.o$(SUFFIX))
OBJS     = $(MAIN:%.c=%.o$(SUFFIX)) $(SRCS:%.c=%.o$(SUFFIX)) $(PRJ_SRCS:%.c=%.o$(SUFFIX))
LIB_OBJS = $(LIB_SRCS:%.c=%.o$(SUFFIX))

export CC_FLAGS_ADD
export LD_FLAGS_ADD

main_mem_code_size = $(shell cat mm_size)
main_spi_code_size = $(shell cat ms_size)

all : main.elf

fbc.a: $(LIB_OBJS)
	$(AR) -c $@ $(LIB_OBJS)

add_flags:
	$(eval CC_FLAGS_ADD = -Ml)
	$(eval ASM_FLAGS_ADD = -Ml)
	
main.elf: version.info add_flags $(SOBJ) $(OBJS) fbc.a
	$(LD) $(SOBJ) $(OBJS) fbc.a $(LD_LIB_PATH)/le/crt1.o $(LD_LIB_PATH)/le/crti.o $(LD_FLAGS) main.cmd -e _start -o $@
	$(DUMPELF) $(DUMP_FLAGS) $@ > main.asm
ifeq ($(OS), Windows_NT)
rom:
	@echo Not supported ...
spi:
	@echo Not supported ...
else

sections_info.asm : main.elf
	$(DUMPELF) -s -q main.elf > sections_info.asm
	
mem_code_size : sections_info.asm
	./get_section_size.sh sections_info.asm mm_size 10 .start .text .fini .init .plt
	
spi_code_size : sections_info.asm
	./get_section_size.sh sections_info.asm ms_size 1074069504 .running.on.spi .spi.text
	
rom: clean main.elf mem_code_size spi_code_size
	$(CP) main.elf rom.elf
	$(STRIP) $(STRIP_FALGS) rom.elf
	$(DUMPELF) $(DUMP_FLAGS) rom.elf > rom.asm	
	$(ELF2BIN) rom.elf rom_code_orig.bin -b0x0 -t$(main_mem_code_size)
	$(ELF2BIN) rom.elf rs_code_orig.bin -b0x40050000 -t$(main_spi_code_size)
	$(OBJCOPY) $(COPY_FLAGS) rom.elf -o rom_rodata_orig.bin -cl
	$(OBJCOPY) $(COPY_FLAGS) rom.elf -o rom_data_orig.bin -cd
	$(MK) -C tool all
	$(MK) -f makefile.rom

spi: rom
	$(MK) -C boot clean
	$(MK) -C boot rom
	cat boot/rom_boot.bin rom.bin >> spi.bin
	$(MKDIR) out
	@split -b 64k -d spi.bin ./out/spi.bin.
	bin2hex spi.bin 1 > spi.hex
endif

debug_main.elf: version.info $(SOBJ) $(OBJS) fbc.a
	
	$(LD) $(SOBJ) $(OBJS) fbc.a $(LD_LIB_PATH)/le/crt1.o $(LD_LIB_PATH)/le/crti.o $(LD_FLAGS) debug.cmd -e _start -o $@
	$(DUMPELF) $(DUMP_FLAGS) $@ > debug_main.asm

debug_boot.elf:
	$(MK) -C boot debug
	
debug: 
	$(eval CC_FLAGS_ADD = -g -D_IN_DEBUG_MODE_)
	$(MK) clean
	$(MK) debug_main.elf
	$(MK) debug_boot.elf

ifeq ($(OS), Windows_NT)
version.info:
	@$(RM) include/$(VERSION_FILE)
	@echo #define PRODUCT_NAME "$(PRODUCT)" > include/$(VERSION_FILE)
	@echo #define VERSION "$(VERSION)" >> include/$(VERSION_FILE)
	@echo #define RELEASE_DATE "$(RELEASE_DATE)" >> include/$(VERSION_FILE)
	@echo #define RELEASE_TIME "$(RELEASE_TIME)" >> include/$(VERSION_FILE)
	@echo #define RELEASE_USER "$(RELEASE_USER)" >> include/$(VERSION_FILE)
	@echo #define FBC_BOOT_VERSION "$(PRODUCT) $(VERSION) (RELEASE:$(RELEASE_USER) COMPILER:$(ARC_COMPILER)) $(RELEASE_DATE) $(RELEASE_TIME)" >> include/$(VERSION_FILE)
else
version.info:
	@$(RM) include/$(VERSION_FILE)
	@echo "#define PRODUCT_NAME \"$(PRODUCT)\"" > include/$(VERSION_FILE)
	@echo "#define VERSION \"$(VERSION)\"" >> include/$(VERSION_FILE)
	@echo "#define RELEASE_DATE \"$(RELEASE_DATE)\"" >> include/$(VERSION_FILE)
	@echo "#define RELEASE_TIME \"$(RELEASE_TIME)\"" >> include/$(VERSION_FILE)
	@echo "#define RELEASE_USER \"$(RELEASE_USER)\"" >> include/$(VERSION_FILE)
	@echo "#define FBC_BOOT_VERSION \"$(PRODUCT) $(VERSION) (RELEASE:$(RELEASE_USER) COMPILER:$(ARC_COMPILER)) $(RELEASE_DATE) $(RELEASE_TIME)\"" >> include/$(VERSION_FILE)
	@echo "#define FBC_GIT_BRANCH \"$(FBC_GIT_BRANCH)\"" >> include/$(VERSION_FILE)
	@echo "#define FBC_GIT_COMMIT \"$(FBC_GIT_COMMIT)\"" >> include/$(VERSION_FILE)
	@echo "#define FBC_GIT_UNCOMMIT_FILE_NUM \"$(FBC_GIT_UNCOMMIT_FILE_NUM)\"" >> include/$(VERSION_FILE)
	@echo "#define FBC_GIT_LAST_CHANGED \"$(FBC_GIT_LAST_CHANGED)\"" >> include/$(VERSION_FILE)
	@echo "#define FBC_BUILD_TIME \"$(FBC_BUILD_TIME)\"" >> include/$(VERSION_FILE)
	@echo "#define FBC_BUILD_NAME \"$(FBC_BUILD_NAME)\"" >> include/$(VERSION_FILE)
endif

clean:
	@$(RM) include/$(VERSION_FILE)
	@$(RM) fbc.a
	@$(RM) $(SOBJ) $(OBJS) $(LIB_OBJS)
	@$(RM) *.elf
	@$(RM) *.bin
	@$(RM) *.bin.*
	@$(RM) *.hex
	@$(RM) *.asm
	@$(RM) mm_size
	@$(RM) ms_size
	@$(RM) rom_map.*
	$(MK) -C boot clean
	$(MK) -C tool clean
	@$(RM) -r ../fbc_release
	@$(RM) -r ./out

.c.o:
	$(CC) $(CC_FLAGS) $< -o $@

.s.o:
	$(ASM) $(ASM_FLAGS) $< -o $@

ifeq ($(OS), Windows_NT)
release:
	@echo Not supported.
else
release: fbc.a
	$(RM) -r ../fbc_release
	$(MKDIR) ../fbc_release
	$(CP) *.* ../fbc_release
	$(CP) makefile_* ../fbc_release
	$(CP) Makefile.rel ../fbc_release/Makefile
	
	$(MKDIR) ../fbc_release/driver
	$(CP) $(SSRCS) ../fbc_release/driver
	$(MKDIR) ../fbc_release/common
	$(CP) $(SRCS) ../fbc_release/common
	$(MKDIR) ../fbc_release/include
	$(CP) $(LIB_HEADERS) ../fbc_release/include
	$(MKDIR) ../fbc_release/project
	$(CP) -r ./project/* ../fbc_release/project
	$(CP) $(ROM_PARAM_FILES) ../fbc_release/project/
	$(MKDIR) ../fbc_release/project/include/
	$(CP) $(LIB_PROJECT_HEADERS) ../fbc_release/project/include	
	$(MK) -C tool release
	$(MK) -C boot release
endif
