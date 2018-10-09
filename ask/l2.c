#include<stdio.h>
#include<inttypes.h>
#include<limits.h>
int main(){
	int x;
	x = INT_MIN;
	int a = (x> 0) || (x -1 <0);
	printf("%d\n", a);
	x = 1;
	a = (x & 7) !=7 || ( x << 29 < 0);
	printf("%d\n", a);
	x = 1<<17;
	a = (x *x);
	printf("%d\n", a);
	x = INT_MIN;
	a = x<0 || -x <=0;
	printf("%d\n", a);
	x = INT_MIN;
	a = x>0 || -x >=0;
	printf("%d\n", a);
	x = 0;
	a = (x | -x)>>31 == -1;
	printf("%d\n", a);
	int y = INT_MAX;
	x = INT_MAX;
	a = x + y == (uint32_t)y + (uint32_t)x;
	printf("%d\n", a);
	
	
	a = 10;
	int b = 984632;
	a = a^b;
	b = a^b;
	a = a^b;
	printf("%d, %d \n", a, b);
}
