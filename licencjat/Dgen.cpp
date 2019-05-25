#include<bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]){ 
    int q = 20000; 
    char syms[] = { 'I', 'D','L', 'U'};
    srand(atoi(argv[1]));
    printf("%d\n", q);
    for(int i = 0; i< q; i++){
        int ind = rand()%2, v = rand()%200 - 100 ;
        printf("%c %d\n", syms[ind], v);
        
    }
    
}