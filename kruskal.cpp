#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

priority_queue<int> pq;

class Arista;

class Nodo {
public:
  vector<Arista *> aristas;
  bool v;
};

class Arista {
public:
  Nodo *inicio;
  Nodo *fin;
  int peso;

  Arista(Nodo *ini, Nodo *fini, int p) {
    inicio = ini;
    fin = fini;
    peso = p;
  }
};

class Grafo {
public:
  vector<Nodo *> nodos;
  vector<Arista *> aristas;

  Grafo() {
    nodos.resize(9);
    addArista(nodos[0], nodos[1], 12);
    addArista(nodos[0], nodos[2], 7);
    addArista(nodos[0], nodos[3], 5);
    addArista(nodos[1], nodos[4], 5);
    addArista(nodos[1], nodos[5], 5);
    addArista(nodos[1], nodos[6], 11);
    addArista(nodos[2], nodos[4], 3);
    addArista(nodos[2], nodos[7], 8);
    addArista(nodos[3], nodos[2], 6);
    addArista(nodos[3], nodos[7], 4);
    addArista(nodos[3], nodos[1], 12);
    addArista(nodos[5], nodos[2], 4);
    addArista(nodos[5], nodos[6], 6);
    addArista(nodos[5], nodos[8], 7);
    addArista(nodos[6], nodos[8], 10);
    addArista(nodos[7], nodos[1], 12);
    addArista(nodos[7], nodos[8], 9);
  }

  void addArista(Nodo *i, Nodo *f, int p) {
    Arista *a = new Arista(i, f, p);
    aristas.push_back(a);
    i->aristas.push_back(a);
  }

  void merge(int izq, int medio, int der) {
    int n1 = medio - izq + 1;
    int n2 = der - medio;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
      L[i] = aristas[izq + i]->peso;
    for (int j = 0; j < n2; j++)
      R[j] = aristas[medio + 1 + j]->peso;

    int i = 0;
    int j = 0;
    int k = izq;

    while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
        aristas[k]->peso = L[i];
        i++;
      } else {
        aristas[k]->peso = R[j];
        j++;
      }
      k++;
    }

    while (i < n1) {
      aristas[k]->peso = L[i];
      i++;
      k++;
    }

    while (j < n2) {
      aristas[k]->peso = R[j];
      j++;
      k++;
    }
  }

  void mergeSort(int izq, int der) {
    if (izq < der) {
      int medio = izq + (der - izq) / 2;

      mergeSort(izq, medio);
      mergeSort(medio + 1, der);

      merge(izq, medio, der);
    }
  }

  int findSet(vector<int> &parent, int i) {
    if (parent[i] == -1)
      return i;
    return parent[i] = findSet(parent, parent[i]);
  }

  void unionSets(vector<int> &parent, int x, int y) {
    int xset = findSet(parent, x);
    int yset = findSet(parent, y);
    if (xset != yset)
      parent[xset] = yset;
  }

  bool hayCiclo() {
    vector<int> parent(nodos.size(), -1);

    for (Arista *a : aristas) {
      int u = distance(nodos.begin(), find(nodos.begin(), nodos.end(), a->inicio));
      int v = distance(nodos.begin(), find(nodos.begin(), nodos.end(), a->fin));

      int setU = findSet(parent, u);
      int setV = findSet(parent, v);

      if (setU == setV)
        return true;

      unionSets(parent, setU, setV);
    }
    return false;
  }

  void imprimir() {
    for (Arista *a : aristas) {
      cout << "Arista: " << a->inicio << " -> " << a->fin << " con peso "
           << a->peso << endl;
    }
  }
};

void kruskal(Grafo G, vector<Nodo *> &S) {
  G.mergeSort(0, G.aristas.size());

  auto it = G.aristas.begin();
  while (!G.aristas.empty() && S.size() != G.nodos.size() - 1) {
    G.aristas.erase(it); // O(1)

    if (G.hayCiclo()) {
      S.push_back((*it)->inicio);
      S.push_back((*it)->fin);
    }

    it++; // O(V) ???
  }

  if (S.size() != (G.nodos.size() - 1))
    cout << "No existe un solucion" << endl;
  else {
    G.imprimir();
  }
}

int main() {
  Grafo G;

  vector<Nodo *> res;

  kruskal(G, res);

  cout << "Hello World!\n";
}