        .global clz
        .type clz,@function

        .text

LONG_MAX = 0xFFFFFFFFFFFFFFFF
BIT_COUNT = 64
a = %rdi
p = %eax
k = %edx
m = %r8d
tmp = %ecx
maska = %rsi
        
clz:
    movl $0, p #poczatek w eax
    movl $65, k  #koniec w edi
C1: movl k, tmp # tmp = k-1
    decl tmp
    subl p, tmp
    jbe  C2 # jezeli k - p >= 1 ret
    movl p, m
    addl k, m
    sarl m # m = p + q /2
    xorl tmp, tmp
    movq $1, maska#maska
    movb $64, %cl
    subb %r8b, %cl
    salq %cl, maska
    decq maska
    notq maska
    andq a, maska #arg &= maska
    cmpq $0, maska
    jne  K
P:  movl m, p # p = m    
    jmp  C1
K:  movl m, k # k = m
    jmp  C1
C2: ret
    .size clz, .-clz
