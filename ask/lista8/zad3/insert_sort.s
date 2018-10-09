        .global insert_sort
        .type insert_sort,@function

        .text

pocz = %rdi
kon = %rsi
akt_pocz = %rdx
wskaznik = %rax
wart_akt_pot = %r8
wart_wsk = %r9
        

insert_sort:
       
        cmp pocz, kon 
        je KONIEC
        movq pocz, akt_pocz
        addq $8, akt_pocz
WHILE1: cmp akt_pocz, kon
        jl KONIEC
        movq akt_pocz, wskaznik
        movq (akt_pocz), wart_akt_pot
        subq $8, wskaznik
WHILE2: cmp wskaznik, pocz
        jg OUT2
        movq (wskaznik), wart_wsk
        cmp wart_akt_pot, wart_wsk
        jle OUT2
        movq wart_wsk, 8(wskaznik)
        leaq -8(wskaznik), wskaznik
        jmp WHILE2
OUT2:   movq wart_akt_pot, 8(wskaznik)
        addq $8, akt_pocz
        jmp WHILE1
KONIEC: ret

.size insert_sort, .-insert_sort
