        .global fibonacci
        .type fibonacci,@function

        .text
        
n = %rdi
n1 = %r13
res = %r12
frame = %rbp
stack = %rsp

fibonacci:
        push    frame
        mov     stack, frame
        
        cmp     $0, n
        je      END1
        cmp     $1, n
        je      END1
        
        push    n1
        push    res
        mov     n, n1
        
        xor     res, res
        mov     n, n1
        
        decq    n #odejmujemy od n
        call    fibonacci
        
        add     %rax, res #dodajemy do res
          
        mov     n1, n
        sub     $2, n #odejmujemy od n
        call    fibonacci
        
        add     res, %rax
RES:    pop     res
        pop     n1
        pop     frame
        ret
        
END1:   
        movq    n, %rax
        pop     frame
        ret
        
.size fibonacci, .-fibonacci
