#include<stdio.h>
#include<stdlib.h>
unsigned long fibonacci(unsigned long n);

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("BLAD WEJSCIA\n");
        return 0;
    }
    unsigned long argument1 = strtoul (argv[1], NULL, 10);
    
    printf("%lu", fibonacci(argument1));
}