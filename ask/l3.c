#include<stdio.h>
#include<inttypes.h>
#include<limits.h>
#include <half.hpp>
#define HALF_ROUND_TIES_TO_EVEN 1
int main(){
    int x = INT_MAX;
    printf("%d", x== (int32_t)(double) x);
    printf("%d, %f", x == (int32_t)(float) x, (float)x);
    long long int l =  (long long) 1<<40;
    double d = (double) l - (double) 1.0;
    printf("%d", d == (double)(float) d);
    printf("%d", 1.0/2 == 1/2.0);
    d = 0.00000000001;
    float f = 10000000000;
    printf("%d", (f + d) - f == d);
    3.984375 · 10−1 + 3.4375 · 10−1 + 1.771 · 103 u
    float f1 = 0.3984375;
    float f2 = 0.34375;
    float f3 = 1771;
    
}