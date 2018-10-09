extern int buf[];

int *bufp0 = &buf[0];//dodaje do data
static int *bufp1;

static void incr() {//dodaje do eh_frame
    static int count = 0;
    count++;//dodaje do data bo to jest static bo cout jest w bss
}

static void decr(){}
void swap() {//dodaje do eh_frame
    int temp;
    incr();// brak relokacji jak jest PIC a jest jeśli w dezasemblowanym kodzie sa adresy absolutne
    bufp1 = &buf[1];//+2
    temp = *bufp0;//+1
    *bufp0 = *bufp1;//+2
    *bufp1 = temp;//+1
}

/*
 * 
 * COLUMN ONE: the symbol's value

COLUMN TWO: a set of characters and spaces indicating the flag bits that are set on the symbol. There are seven groupings which are listed below:

group one: (l,g,,!) local, global, neither, both.

group two: (w,) weak or strong symbol.

group three: (C,) symbol denotes a constructor or an ordinary symbol.

group four: (W,) symbol is warning or normal symbol.

group five: (I,) indirect reference to another symbol or normal symbol.

group six: (d,D,) debugging symbol, dynamic symbol or normal symbol.

group seven: (F,f,O,) symbol is the name of function, file, object or normal symbol.

COLUMN THREE: the section in which the symbol lives, ABS means not associated with a certain section

COLUMN FOUR: the symbol's size or alignment.

COLUMN FIVE: the symbol's name.

 
 objdump --syms swap.o

swap.o:     file format elf64-x86-64

SYMBOL TABLE:  local/gloabal | debugging d | file f |function F | object 0
0000000000000000 l    df *ABS*	0000000000000000 swap.c
0000000000000000 l    d  .text	0000000000000000 .text
0000000000000000 l    d  .data	0000000000000000 .data
0000000000000000 l    d  .bss	0000000000000000 .bss
0000000000000000 l     O .bss	0000000000000008 bufp1
0000000000000000 l     F .text	0000000000000016 incr
0000000000000008 l     O .bss	0000000000000004 count.1835
0000000000000000 l    d  .note.GNU-stack	0000000000000000 .note.GNU-stack
0000000000000000 l    d  .eh_frame	0000000000000000 .eh_frame
0000000000000000 l    d  .comment	0000000000000000 .comment
0000000000000000 g     O .data	0000000000000008 bufp0
0000000000000000         *UND*	0000000000000000 buf
0000000000000016 g     F .text	000000000000004a swap
*/