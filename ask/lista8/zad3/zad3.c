#include<stdio.h>
#include<stdlib.h>
void insert_sort(long *first, long *last);

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("BLAD WEJSCIA\n");
        return 0;
    }
    long tab[argc-1];
    for(int i = 1; i<argc; i++){
        tab[i-1] = atol(argv[i]);
    }
    
    insert_sort(tab, tab + argc-2);
    
    for(int i = 0; i<argc-1; i++){
        printf("%ld ", tab[i]);
    }
    
}