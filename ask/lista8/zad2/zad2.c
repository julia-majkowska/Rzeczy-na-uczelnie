#include<stdio.h>
#include<stdlib.h>
typedef struct {
    unsigned long lcm, gcd;
} result_t;
result_t lcm_gcd(unsigned long, unsigned long);

int main(int argc, char* argv[]){
    if (argc < 3){
        printf("BLAD WEJSCIA\n");
        return 0;
    }
    
    unsigned long argument1 = strtoul (argv[1], NULL, 10);
    unsigned long argument2 = strtoul (argv[2], NULL, 10);
    result_t r = lcm_gcd(argument1, argument2);
    printf("%lu %lu\n", r.lcm, r.gcd);
}