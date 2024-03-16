#include <vector>
#include <list>
#include <iostream>

using namespace std;

float Addition(float a, float b){ return a+b; }

float Substraction(float a, float b){ return a-b; }

float Multiplication(float a, float b){ return a*b; }

float Division(float a, float b){ 

	if(!b)return -1;
	return a/b; 

}

typedef float (*lpfnOperation)(float,float) ;
lpfnOperation vpf[4] = {&::Addition, &::Substraction,
								&::Multiplication, &::Division};


int main(int argc, char* argv[]){
	float a,b,c; int opt;
	cin>> a >> b;

	cin>> opt;

	c = (*vpf[opt])(a,b);

	if(opt==3 && b==0) cout<<"Division entre 0";
	else cout<<"El resultado es: "<<c;
	return 0;
}
