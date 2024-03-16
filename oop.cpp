#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class CVector{
	private:
		int *m_pVector,
			 m_nCount,
			 m_nMax,
			 m_nDelta;
		void Resize(){
			int *ptemp;
			ptemp = new int[m_nMax+m_nDelta];
			for(int i=0; i<m_nMax; i++)
				ptemp[i] = m_pVector[i];
			delete [] m_pVector;

			m_pVector = ptemp;
			m_nMax += m_nDelta;
			m_rsCount++;
		}
	public:
		int m_rsCount;
		void ini(){
			m_pVector = NULL;
			m_nDelta = 10;
			m_nCount = 0;
			m_nMax = 0;
		}
		void Insert(int element){
			if (m_nCount == m_nMax) 
				Resize();
			m_pVector[m_nCount++] = element;
			cout<<"Elemento agregado: "<<element<<", ";
		}
};

int main(){
 
	CVector vec;
	vec.ini();
	CVector vec2;

	for(int i=0; i<50; i++)
		vec.Insert(i+1);
	cout<<vec.m_rsCount<<" Resize's done.";
	return 0;
}

