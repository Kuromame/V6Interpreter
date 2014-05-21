CC = gcc
CFLAGS = -Wall -g 

disasm_program = disasm_v00
intrp_program = disasm_v00_intrp
srcs = disasm_v00.c disasm_fo_lib.c disasm_analyzer_lib.c disasm_print_lib.c
objs = $(srcs:%.c=%.o)
deps = $(srcs:%.c=%.d)

#.SUFFIXES: .o .c

all: $(disasm_program) $(intrp_program)

#$(disasm_program):$(objs)
#	$(CC) $(CFLAGS) -o $@ $(objs)

#$(intrp_program):$(objs)
#	$(CC) $(CFLAGS) -o $@ -D "INTRP_MODE" $(objs)

$(disasm_program):$(srcs)
	$(CC) $(CFLAGS) -o $@ $(srcs)

$(intrp_program):$(srcs)
	$(CC) $(CFLAGS) -o $@ -D "INTRP_MODE" $(srcs)

#.c.o:
#	$(CC) -c -MMD -MP $(CFLAGS) $<

-include $(deps)

.PHONY: clean
#clean:
#	$(RM) $(objs) $(deps)

clean_$(disasm_program):
	$(RM) $(objs) $(disasm_program).exe

clean_$(intrp_program):
	$(RM) $(objs) $(intrp_program).exe

clean_both:
	$(RM) $(objs) $(disasm_program).exe $(intrp_program).exe


