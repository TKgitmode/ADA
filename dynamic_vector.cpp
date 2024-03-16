#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <vector>
using namespace std;

int *gpVect = NULL;
int gnCount = 0;
int gnMax = 0;
int i;
int rsCount = 0;

void Resize(){
	const int delta = 10;

	int *ptemp;
	ptemp = new int[gnMax+delta];
	for(i=0; i<gnMax; i++)
		ptemp[i] = gpVect[i];
	delete [] gpVect;

	gpVect = ptemp;
	gnMax += delta;
	rsCount++;
}

void Insert(int element){
	if (gnCount == gnMax) 
		Resize();
	gpVect[gnCount++] = element;
	cout<<"Elemento agregado: "<<element<<"\n";
}

int main(){
 
	for(i=0; i<20; i++)
		Insert(i+1);
	cout<<rsCount<<" Resize's done.";
	return 0;
}

