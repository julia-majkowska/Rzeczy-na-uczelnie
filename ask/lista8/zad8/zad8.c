#include<stdio.h>
#include<stdlib.h>
double approx_sqrt(double x, double epsilon);

int main(int argc, char* argv[]){
    if (argc < 3){
        printf("BLAD WEJSCIA\n");
        return 0;
    }
    
    double x = atof(argv[1]);
    double eps = atof(argv[2]);
    
    printf("%lf\n", approx_sqrt(x, eps));
    
}