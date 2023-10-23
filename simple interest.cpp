#include<stdio.h>include 
#include<math.h>

int main()

{
	float p,r,t,si;
	printf("enter principal amount:");
	scanf("%f",&p);
	printf("enter rate\n");
	scanf("%f",&r);
	printf("enter time(in years):");
	scanf("%f",&t);
	si=(p*r*t)/100;
	printf("%f",si);

return 0;
}
	
	
	

