#include<bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]){ 
    int n = 20;
    int q =20; 
    srand(atoi(argv[1]));
    printf("%d\n", n);
    for(int i = 0; i< n; i++) printf("%d ", rand()%100 - 50);

    printf("\n%d\n", q);
    for(int i = 0; i< q; i++){
        int v = rand()%100 - 50 ;
        printf("%d ", v);
        
    }
    
}