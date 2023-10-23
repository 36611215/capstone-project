#include <iostream>
#include <math.h>
using namespace std;
int main(int argc, char** argv)
{
	float p,r,t,ci;
	cout<<"\nEnter Principal Amount:";
	cin>>p;
	cout<<"\nEnter Interest Rate:";
	cin>>r;
	cout<<"\nEnter time period in years:";
	cin>>t;
	ci=p*pow((1+r/100),t)-p;
	cout<<"\n\nCompound interest after"<<t<<"years is :"<< ci;
	return 0;
}