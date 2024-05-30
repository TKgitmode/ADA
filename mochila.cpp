#include <iostream>
#include <vector>

using namespace std;

int seleccionarMejor(vector<int>& b, vector<int>& p) {
    int indiceMejorProporcion = 0;
    double mejorProporcion = 0.0;

    for (int i = 0; i < b.size(); i++) {
        if (p[i] != 0) { 
            double proporcion = static_cast<double>(b[i]) / p[i];
            if (proporcion > mejorProporcion) {
                mejorProporcion = proporcion;
                indiceMejorProporcion = i;
            }
        }
    }
    return indiceMejorProporcion;
}

void Mochila(int M, int n, vector<int>& b, vector<int>& p, vector<double>& X) {
    X.resize(n, 0);

    int pesoAct = 0;
    while (pesoAct < M) {
        int i = seleccionarMejor(b, p);

        if (pesoAct + p[i] <= M) {
            X[i] = 1;
            pesoAct += p[i];
        } else {
            X[i] = static_cast<double>(M - pesoAct) / p[i];
            pesoAct = M;
        }
        //para ya no considerarlo en la siguiente iteración
        b[i] = 0;     
        p[i] = 1000;
    }
}
         

int main() {
    int M = 55; 
    int n = 3; 
    vector<int> beneficios = {60, 100, 120}; 
    vector<int> pesos = {10, 20, 30}; 
    vector<double> X; 

    Mochila(M, n, beneficios, pesos, X);

    cout << "Solución de la mochila:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Objeto " << i + 1 << ": " << X[i] << endl;
    }

    return 0;
}
