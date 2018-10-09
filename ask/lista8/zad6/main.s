# -----------------------------------------------------------------------------
# A 64-bit command line application to compute x^y.
#
# Syntax: power x y
# x and y are integers
# -----------------------------------------------------------------------------

        .global main
        .type main, @function

argv = %rbx
argc = %r13
stack_padding = %r12
stack_pointer = %rsp
i = %r14
max = %rax
min = %rbx

        .text
main:
        push    %rbx
        push    %r12                    # save callee-save registers
        push    %r13
        push    %r14
        # By pushing 3 registers our stack is already aligned for calls
        mov     %rdi, argc
        mov     %rsi, argv
        dec     argc
        cmp     $1, argc                # sprawdzanie liczby argumentow
        jl      error1
        
        mov     argc, stack_padding
        shl     $3, stack_padding
        sub     stack_padding, stack_pointer #zaalokowania tablica na stosie trzeba bedzie ja dorownac
        
        mov     stack_pointer, i
        shr     $3, i
        test    $1, i
        je      C0
        sub     $8, stack_pointer
        add     $8, stack_padding #wyrownanie stosu do 16 bajtow

C0:     mov $0, i
        
PUT:    cmp     i, argc
        jle     FIND
        mov     8(argv, i, 8), %rdi    #argv[i+1]
        call    atol                   
        mov     %rax, (stack_pointer, i, 8) 
        inc     i
        jmp     PUT
        
FIND:   mov     $1, i
        mov     (stack_pointer), min
        mov     (stack_pointer), max
        
FOR:    cmp     i, argc
        jle     done
        cmp     (stack_pointer, i, 8), min
        jl      C1
        mov     (stack_pointer, i, 8), min
C1:     cmp     (stack_pointer, i, 8), max
        jg      C2
        mov     (stack_pointer, i, 8), max
C2:     inc i
        jmp FOR
        
done:   
        mov     $format, %rdi
        mov     max, %rsi
        xor     %rax, %rax
        call    printf
        
        mov     $format, %rdi
        mov     min, %rsi
        xor     %rax, %rax
        call    printf
        
        # restore saved registers
        add     stack_padding, stack_pointer
        
return: pop     %r14
        pop     %r13
        pop     %r12
        pop     %rbx
        ret
        
error1:             # print error message
        mov     $badArgumentCount, %edi
        call    puts
        jmp     return
        
        .size main, .-main

format:
        .asciz  "%ld\n"
badArgumentCount:
        .asciz  "BLAD WEJSCIA\n"
