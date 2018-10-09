#include<stdio.h>
#include<inttypes.h>
struct A {
    void *b;
    int16_t d;
    int8_t a;
    int8_t c;
       
};

struct B {
    uint16_t a;
    void *c;
    double b;
    
};

int main(){
    struct A a;
    struct B b;
    printf("%lu %p %p %p %p %p\n", sizeof(struct A), &a, &(a.a), &a.b, &a.c, &a.d);
    printf("%lu %p %p %p %p\n", sizeof(struct B),&b,  &(b.a), &b.b, &b.c);
    
}