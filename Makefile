# Test commands.
#	make run
#	Ctrl-a x (Exit)


CROSS = aarch64-linux-gnu
CC = ${CROSS}-gcc
AS = ${CROSS}-as
LD = ${CROSS}-ld
OBJDUMP = ${CROSS}-objdump
CFLAGS =  -mcpu=cortex-a57 -Wall -Wextra
#	-mcpu=name
#		Specify the name of the target processor
#	-Wall
#		Turns on all optional warnings which are desirable for normal code
#	-Wextra
#		This enables some extra warning flags that are not enabled by -Wall
ASM_FLAGS = -mcpu=cortex-a57
OBJS = boot.o kernel.o


kernel.elf: ${OBJS}
	${LD} -Tlinker.ld $^ -o $@
	${OBJDUMP} -D kernel.elf > kernel.list

boot.o: boot.S
	${AS} ${ASM_FLAGS} -c $< -o $@

%.o : %.c
	$(CC) ${CFLAGS} -c $<

run:
	$(MAKE) kernel.elf
	# qemu-system-aarch64 -machine virt -cpu cortex-a57 -m 128 -serial stdio -nographic -nodefaults -kernel kernel.elf
	qemu-system-aarch64 -machine virt -cpu cortex-a57 -nographic -kernel kernel.elf

gen_tags:
	./gen_tags.sh

clean_tags:
	rm -rf tags cscope*

clean:
	rm -f *.o *.elf *.list

.PHONY: run gen_tags clean_tags clean
