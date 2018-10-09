/*
 * callmaxofthree.c
 *
 * A small program that illustrates how to call the maxofthree function we wrote in
 * assembly language.
 */

#include <stdio.h>
#include <inttypes.h>

int64_t puzzle3(int64_t, int64_t);

int main() {
   
    for(int i  = 0 ; i< 10; i++) 
        for(int j = 0; j<10 ; j++)
            printf("%d %d %lu\n", i, j, puzzle3(i, j)); 
}