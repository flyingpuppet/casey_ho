GCC = gcc

OBJ_TOOLS = audio_param
OBJ_TOOLS += bin_wrapper
OBJ_TOOLS += config2bin

TOOLS_SRCS = audio_param.c
TOOLS_SRCS += bin_wrapper.c

audio_param: audio_param.o
	$(GCC) $^ -o $@

bin_wrapper: bin_wrapper.o
	$(GCC) $^ -o $@

config2bin: config2bin.o
	$(GCC) $^ -o $@
	
all: clean $(OBJ_TOOLS)

release: all
	@mkdir ./../../fbc_release/tool
	@cp $(TOOLS_SRCS) ./../../fbc_release/tool
	@cp Makefile.rel ./../../fbc_release/tool/Makefile
	@rm -f *.o
	@rm -f $(OBJ_TOOLS)
	
clean:
	@$(RM) *.o
	@$(RM) rom_audioparam
	@$(RM) $(OBJ_TOOLS)
	
.c.o:
	$(GCC) -c $<