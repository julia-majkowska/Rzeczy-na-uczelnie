#include<stdio.h>
#include<stdlib.h>

unsigned mulf(unsigned ,unsigned );

int main(int argc, char* argv[]){
    if (argc < 3){
        printf("BLAD WEJSCIA\n");
        return 0;
    }
    
    float argument1 = atof (argv[1]);
    float argument2 = atof (argv[2]);
    //printf("%f %f\n", argument1, argument2);
    unsigned int rep1 = *(unsigned int*)&argument1;  
    unsigned int rep2 = *(unsigned int*)&argument2;  
    unsigned int result = mulf(rep1, rep2);
    float res = *(float *)&result;
    argument2*=argument1;
    //unsigned int real_res = *(unsigned int*)&argument2; 
    printf("%f\n", res);
}