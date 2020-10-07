.text
.globl _start

# Linux kernel calls _start by default
_start:

    mov %rsp, %rbp    
    mov 0(%rbp), %rdi 
    lea 8(%rbp), %rsi 
    call main         

    mov %rax, %rdi    
    movl $1, %eax     
    movl $0, %ebx     
    int $0x80        
                      
                      