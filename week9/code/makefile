
NASM=nasm
GCC=gcc
CFLAGS=-c -m16
LD=ld
LDFLAGS= -static -nostdlib -m elf_i386 -T kernel.lds
RM=rm -f


all: boot apps
	@dd if=/dev/zero of=os.img bs=512 count=2880
	@dd if=boot.bin of=os.img bs=512 conv=notrunc
	@dd if=kernel.bin of=os.img seek=1 bs=512 conv=notrunc
	@echo "Gen floppy image."


boot:
	@$(NASM) -o boot.bin boot.asm
	@echo "Gen boot.img."

apps:
	@$(NASM) -f elf32 -o entry.o entry.asm
	@$(NASM) -f elf32 -o utils.o utils.asm
	@$(GCC) $(CFLAGS) -o main.o main.c
	@$(LD) $(LDFLAGS) -o kernel.bin entry.o utils.o main.o

clean:
	@$(RM) *.o *.bin *.img
	@echo "Clean objs."

.PHONY: all boot clean
