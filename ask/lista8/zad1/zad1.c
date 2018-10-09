#include<stdio.h>
#include <stdlib.h> 
int clz(long long arg);

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("BŁEDNE WEJSCIE\n");
        return 0;
    }
    
    long long argument = atoll(argv[1]);
   
   // printf("%lld", argument);
    printf("%d", clz(argument));
    
}