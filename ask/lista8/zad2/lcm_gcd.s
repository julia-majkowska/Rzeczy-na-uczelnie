        .global lcm_gcd
        .type lcm_gcd,@function

        .text

a0 = %rdi
b0 = %rsi
a = %r8
b = %r9
c = %rcx
reszta = %rdx
        

lcm_gcd:
        movq a0, a
        movq b0, b
gcd:    cmp $0, b
        jbe  NEXT #skok jesli mniejsze lub rowne
        movq a, c
        xorq %rdx, %rdx
        movq a, %rax
        divq b
        movq b, a
        movq reszta, b
        jmp gcd
NEXT:   xorq %rdx, %rdx
        movq a0, %rax
        divq a # a to gcd
        mulq b0 # lcm zwracam raxem
        movq a, %rdx
        ret
.size lcm_gcd, .-lcm_gcd
        