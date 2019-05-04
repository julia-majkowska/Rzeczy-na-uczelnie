#include<bits.stdc++.h>

using namespace std;


int main(int argc, char* argv[]){ 
    int q =argv[2]; 
    char syms[] = { 'I', 'D','L', 'U'};
    default_random_engine generator(atoi(argv[1]));
    srand(atoi(argv[1]));
    normal_distribution<double> distribution (0.0, 1e9)
    
    printf("%d\n", q);
    for(int i = 0; i< q; i++){
        int ind = rand()%4, v = distribution(generator) ;
        printf("%c %d\n", syms[ind], v);
        
    }
    
}