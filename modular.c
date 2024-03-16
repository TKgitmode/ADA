#include <stdio.h>
#include <stdlib.h>

int *gpVect = NULL;
int i;

typedef struct Vector Vector ;
struct Vector{
	int *m_pVector,
		 m_nCount,
		 m_nMax,
		 m_nDelta,
		 m_rsCount;
};

void initVector(Vector *v){
	v->m_nCount = 0;
	v->m_nMax = 0;
	v->m_nDelta = 0;
	v->m_rsCount = 0;
}

void Resize(Vector *pThis){
	pThis->m_pVector = realloc(gpVect,sizeof(int) * (pThis->m_nMax + pThis->m_nDelta));
	pThis->m_nMax += pThis->m_nDelta;
	pThis->m_rsCount++;
}

void Insert(Vector *pThis, int element){
	if(pThis->m_nCount == pThis->m_nMax)
		Resize(pThis);
	pThis->m_pVector[pThis->m_nCount++] = element;
	printf("%d", element);
	printf("\n");
}

int main(){
 
	Vector vec;
	initVector(&vec);	

	Vector vec2;
	initVector(&vec2);	

	
	for(i=0; i<100; i++)
		Insert(&vec, i+1);
	printf("\n");
	printf("%d", vec.m_rsCount);
	printf(" Resize's done.");


	for(i=0; i<20; i++)
		Insert(&vec2, i+1);
	return 0;
}

