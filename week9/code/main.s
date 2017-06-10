	.file	"main.c"
	.code16gcc
	.section	.rodata
.LC0:
	.string	"Success\r\n"
	.text
	.globl	print_str
	.type	print_str, @function
print_str:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$12, %esp
	pushl	$.LC0
	call	print_string
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	print_str, .-print_str
	.globl	showInfo
	.type	showInfo, @function
showInfo:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$12, %esp
	pushl	8(%ebp)
	call	print_string
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	showInfo, .-showInfo
	.section	.rodata
.LC1:
	.string	"will quit.\r\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$20, %esp
	subl	$12, %esp
	pushl	$111
	call	print_char
	addl	$16, %esp
	subl	$12, %esp
	pushl	$115
	call	print_char
	addl	$16, %esp
.L6:
	call	key_detect_simple
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
	cmpl	$113, -12(%ebp)
	je	.L4
	movl	-12(%ebp), %eax
	movsbl	%al, %eax
	subl	$12, %esp
	pushl	%eax
	call	print_char
	addl	$16, %esp
	jmp	.L6
.L4:
	subl	$12, %esp
	pushl	$.LC1
	call	print_string
	addl	$16, %esp
	jmp	.L6
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
