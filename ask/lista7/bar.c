/* bar.c */
#include <stdio.h>

char main;//błąd linkera

void p2() {
    //main = 1;//błąd segmentacji - sekcja tekst jest zabezpieczona przez zapisem
    printf("0x%x %x\n", main);//wskaznik na main?
}