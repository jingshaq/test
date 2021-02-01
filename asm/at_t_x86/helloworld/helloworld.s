    .section .data
message:
    .ascii "hello world!\n"
    length = . - message

    .section .text
    .global _start      # must be declared for linker
_start:
    movq $1, %rax      # 'write' syscall number
    movq $1, %rdi      # file descriptor, stdout
    lea message(%rip), %rsi # relative addressing string message 
    movq $length, %rdx
    syscall

    movq $60, %rax     # 'exit' syscall number
    xor %rdi, %rdi      # set rdi to zero
    syscall
