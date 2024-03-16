#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

template <typename Type> class CVector{
	private:
		Type *m_pVector; 
		int m_nCount,
			 m_nMax,
			 m_nDelta;
		void Resize(){
			Type *ptemp;
			ptemp = new Type[m_nMax+m_nDelta];
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
		void Insert(Type element){
			if (m_nCount == m_nMax) 
				Resize();
			m_pVector[m_nCount++] = element;
			cout<<"Elemento agregado: "<<element<<", ";
		}
};

int main(){
 
	CVector<int> vec;
	vec.ini();
	CVector<float> vec2;
	vec2.ini();

	for(int i=0; i<50; i++)
		vec2.Insert(i+0.6);

	cout<<vec.m_rsCount<<" Resize's done.";
	return 0;
}

