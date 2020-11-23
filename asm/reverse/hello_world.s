	.file	"hello_world.c"
	.intel_syntax noprefix
	.section	.rodata
.LC0:
	.string	"hello world"
	.text
	.globl	main
	.type	main, @function
main:
	push	rbp
	mov	rbp, rsp
	mov	edi, OFFSET FLAT:.LC0
	call	puts
	mov	eax, 0
	pop	rbp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 6.4.1 20170727 (Red Hat 6.4.1-1)"
	.section	.note.GNU-stack,"",@progbits
