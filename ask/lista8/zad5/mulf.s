        .global mulf
        .type mulf,@function

       
        
mantysa = 0x7fffff
jedynka = 0x800000
znak = 0x80000000
cecha = 0x7F800000
bias = 127   

a = %rdi
b = %rsi
res = %rcx
tempa = %rdx
adend = %r8
#last_bit = %r9
#deleted_bit = %r10
        .text

mulf:
        xor res, res
        mov a, tempa
        xor b, tempa
        and $znak, %edx
        or  tempa, res # znak wstawiony
        
        mov a, tempa
        and $mantysa, tempa
        or  $jedynka, tempa #dodajemy jedynki na poczatku mantysy
        mov b, %rax
        and $mantysa, %rax
        or  $jedynka, %rax
        mul tempa
        shr $23, %rax
        
        #mov $1, deleted_bit
        #and %rax, deleted_bit
        
        #shr %rax
        
        
        mov %rax, adend
        shr $24, adend
        
        cmp $0, adend
        je MANT
        shr %rax
        
MANT:   #and %rax, deleted_bit #czy przeniesienie ma generowac zaokroglanie
        #add deleted_bit, %rax
        and $mantysa, %rax
        or %rax, res
        
        
        mov a, tempa
        and $cecha, tempa
        shr $23, tempa
        
        mov b, %rax
        and $cecha, %rax
        shr $23, %rax
        add tempa, %rax
        add adend, %rax
        sub $bias, %rax #odejmujemy bias
        shl $23, %rax
        and $cecha, %rax
        
        or res, %rax
        ret
        