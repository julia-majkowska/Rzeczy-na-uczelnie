#dyrektywy assemblera - dodatkowe dane poza kodem wykonywalnym w kodzie assemblerowym : definicja danych, przynależność do sekcji, dane do konsolidacji, informacje o symbolach, info dla debuggera
.text
.global foobar
.type foobar, @function
.size 
foobar: 
            ...
       ret 
.size .-foobar #kropka to aktualny adres i odejmujemy poczatek funkcji


####

.rodata # bo const
.local baz
.type @object
baz : #zera to padding
    .ascii "abc"
    .zero 1 #<- .align 4
    .long 42
    .quad -3
    .float 1.4142
    .zero 4 #
.size .-baz

###
#sekcja common
.comm array , 800, 8 # <- adres wyrównany do 8
#lub .comm swap na .bss