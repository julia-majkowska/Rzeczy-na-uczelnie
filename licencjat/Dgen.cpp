#include<bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]){
    int q =1000000; 
    char syms[] = {'L', 'I', 'D', 'U'};
    srand(atoi(argv[1]));
    printf("%d\n", q);
    for(int i = 0; i< q; i++){
        int ind = rand()%4, v = rand()%200 - 100 ;
        printf("%c %d\n", syms[ind], v);
        
    }
    
}