#include<bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]){ 
    int n = 511;//atoi(argv[2]);
    int q =200; 
    srand(atoi(argv[1]));
    printf("%d\n", n);
    for(int i = 0; i< n; i++) printf("%d ", i);

    printf("\n%d\n", q);
    for(int i = 0; i< q; i++){
        int v = rand()%n ;
        printf("%d ", v);
        
    }
    
}