#include<bits/stdc++.h>

using namespace std;

int main(){
    
    vector<int> elems;
    int n; 
    scanf("%d", &n);
    printf("%d\n", n>>4);
    int n1 = n;
    int a; 
    n>>=4;
    for(int i = 0; i<n1; i++) scanf("%d", &a);
    for(int i = 1; i<= n; i++){
        printf("%d ", i);
    }
    
    int q;
    scanf("%d", &q);
    printf("\n%d\n ", q);
    while(q--){
        int val;
        scanf("%d", &val);
        printf("%d ", val>>4);
    }

}