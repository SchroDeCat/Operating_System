nasm -f elf32 -o foo.o foo.asm
gcc -c -m32 -o bar.o bar.c
ld  -m elf_i386 -s -o foobar foo.o bar.o
