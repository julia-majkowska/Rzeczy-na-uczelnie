#include <stdio.h>
#include <stdlib.h>
void heapify(int *dst, int *src, int n) {
     int divisor = 2; 
    //int multiplier = 1;
    int i = 0; 
    n+=1;
    int addend = n/divisor * 2; 
    int cur_verse = n/divisor;
    while(divisor < n+2){
        addend = n/divisor * 2;
        cur_verse = n/divisor;
        while(cur_verse < n) {
            ///printf("%d ", n/divisor * multiplier-1);
            dst[i] = src[cur_verse-1]; 
            cur_verse += addend;
            i++;
        }
        //printf("\n");
        divisor<<=1;
    }
  /* XXX: Fill in this procedure! */
}


void transpose2(int *dst, int *src, int n) {
    int B = 8;//32B
    for(int i = 0; i<n; i+=B)
        for(int j = 0; j<n; j+=B) //wspolrzedna bloku
            for(int ii = 0; ii<B && ii + i < n; ii++)
                for(int jj = 0; jj<B && jj + j < n; jj++)
                    dst[(ii+ i)*n + jj + j] = src[(jj+j)*n + ii + i];
}


int main(){

    int tablica[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int* cel = malloc(15*sizeof(int));
    heapify(cel, tablica, 15);
    for(int i = 0; i< 15; i++) printf("%d ", cel[i]);
    
    int macierz[16] = {1, 2, 3, 4, 11, 12, 13, 14, 21, 22, 23, 24, 31, 32, 33, 34};
    for(int i = 0; i< 4; i++){
        for(int j = 0; j<4; j++) 
            printf("%d ", macierz[i*4 + j]);
        printf("\n");
    }
    int* celmac = malloc(16*sizeof(int));
    transpose2(celmac, macierz, 4);
    
    for(int i = 0; i< 4; i++){
        for(int j = 0; j<4; j++) 
            printf("%d ", celmac[i*4 + j]);
        printf("\n");
    }
    
}

