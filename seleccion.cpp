#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

// donde ordenarInsercion es una versión del algoritmo de ordenación por
// inserción más general que el que vimos en el Capítulo 3, ya que podemos
// indicar el trozo del vector que deseamos ordenar.

void ordenarInsercion(vector<int> &v, int inicio, int fin) {
  for (int i = inicio + 1; i <= fin; i++) {
    int temp = v[i];
    int j = i - 1;
    while (j >= inicio && v[j] > temp) {
      v[j + 1] = v[j];
      j--;
    }
    v[j + 1] = temp;
  }
}

void particion2(vector<int> v, int a, int b, int pivote, int &p, int &q) {
  int k;
  int aux;
  p = a;
  k = a;
  q = b;

  while (k <= q) {
    if (v[k] == pivote)
      k++;
    else if (v[k] < pivote) {
      aux = v[p];
      v[p] = v[k];
      v[k] = aux;
      p = p + 1;
      k = k + 1;
    } else {
      aux = v[q];
      v[q] = v[k];
      v[k] = aux;
      q = q - 1;
    }
  }
}

int seleccion2(vector<int> v, int a, int b, int k) {
  int l, p, q, s, pm, t;
  int aux, mm;
  t = b - a + 1;
  if (t <= 12) {
    ordenarInsercion(v, a, b);
    return v[k];
  } else {
    s = t / 5;
    for (l = 1; l <= s; l++) {
      ordenarInsercion(v, a + 5 * (l - 1), a + 5 * l - 1);
      pm = a + 5 * (l - 1) + (5 / 2);
      aux = v[a + l - 1];
      v[a + l - 1] = v[pm];
      v[pm] = aux;
    }
    mm = seleccion2(v, a, a + s - 1, a + (s - 1) / 2);
    particion2(v, a, b, mm, p, q);
    if ((k >= p) && (k <= q)) {
      return mm;
    } else if (k < p) {
      return seleccion2(v, a, p - 1, k);
    } else {
      return seleccion2(v, q + 1, b, k);
    }
  }
}

int main() {
  vector<int> lista;
  int tam, n;
  cin >> tam;

  while (tam > 0) {
    cin >> n;
    lista.push_back(n);
    tam--;
  } 
  clock_t inicio = clock();

  int pivote = seleccion2(lista, 0, lista.size() - 1, lista.size() / 2);
  cout << "Pivote: " << pivote << endl;

  clock_t fin = clock();

  double tiempo_transcurrido = double(fin - inicio) / CLOCKS_PER_SEC;

  cout << "Tiempo transcurrido: " << tiempo_transcurrido << " segundos" << endl;
}