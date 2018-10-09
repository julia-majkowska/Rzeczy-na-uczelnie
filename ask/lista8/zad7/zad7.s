        .global _start
        .type _start, @function

write = 1
read = 0
exit  = 60
male_a = 97
duze_a = 65
duze_z = 90
male_z = 122
tmp = %rcx


        .section .text
_start:
readsec:  
        mov     $read,%rax
        mov     $0,%rdi
        mov     $bufor,%rsi
        mov     $1,%rdx
        syscall
        
        cmp $0, %rax
        je end
        
        mov (bufor), tmp
        cmp $male_z, tmp
        jge writesec
        cmp $duze_a, tmp
        jl  writesec
        cmp $duze_z, tmp
        jl  large
        cmp $male_a, tmp
        jge small
writesec:  
        mov     tmp, bufor
        mov     $write,%rax
        mov     $1,%rdi
        mov     $bufor,%rsi
        mov     $1,%rdx
        syscall
        jmp readsec
        
small:
        sub $male_a, tmp
        add $duze_a, tmp
        jmp writesec
        
large:
        sub $duze_a, tmp
        add $male_a, tmp
        jmp writesec

# exit(int status)
end:    mov     $exit,%rax
        mov     $1,%rdi
        syscall
        .size _start, .- _start
        
        .section .bss
    .comm bufor, 1 
    .size bufor, 1

# vim: ft=gas ts=8 sw=8 et
