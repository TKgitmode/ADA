#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Función auxiliar para multiplicar dos matrices
vector<vector<double>> multiply(vector<vector<double>> &A,
                                vector<vector<double>> &B) {
  int n = A.size();
  vector<vector<double>> C(n, vector<double>(n, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  return C;
}

// Función auxiliar para sumar dos matrices
vector<vector<double>> add(vector<vector<double>> &A,
                           vector<vector<double>> &B) {
  int n = A.size();
  vector<vector<double>> C(n, vector<double>(n, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      C[i][j] = A[i][j] + B[i][j];
    }
  }

  return C;
}

// Función auxiliar para restar dos matrices
vector<vector<double>> subtract(vector<vector<double>> &A,
                                vector<vector<double>> &B) {
  int n = A.size();
  vector<vector<double>> C(n, vector<double>(n, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      C[i][j] = A[i][j] - B[i][j];
    }
  }

  return C;
}

// Función para multiplicar dos matrices utilizando el algoritmo de
// Coppersmith-Winograd
vector<vector<double>> coppersmith_winograd(vector<vector<double>> &A,
                                            vector<vector<double>> &B) {
  int n = A.size();

  if (n <= 60) {
    // Para matrices pequeñas, usar la multiplicación clásica
    return multiply(A, B);
  }

  int m = n / 2;

  // Dividir las matrices en bloques
  vector<vector<double>> A11(m, vector<double>(m, 0));
  vector<vector<double>> A12(m, vector<double>(m, 0));
  vector<vector<double>> A21(m, vector<double>(m, 0));
  vector<vector<double>> A22(m, vector<double>(m, 0));

  // Inicializar las matrices de bloques A_blocks
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      A11[i][j] = A[i][j];
      A12[i][j] = A[i][j + m];
      A21[i][j] = A[i + m][j];
      A22[i][j] = A[i + m][j + m];
    }
  }

  vector<vector<double>> B11(m, vector<double>(m, 0));
  vector<vector<double>> B12(m, vector<double>(m, 0));
  vector<vector<double>> B21(m, vector<double>(m, 0));
  vector<vector<double>> B22(m, vector<double>(m, 0));

  // Inicializar las matrices de bloques B_blocks
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      B11[i][j] = B[i][j];
      B12[i][j] = B[i][j + m];
      B21[i][j] = B[i + m][j];
      B22[i][j] = B[i + m][j + m];
    }
  }

  // Calcular las matrices producto utilizando la recursión
  vector<vector<double>> B_temp = subtract(B22, B21);
  vector<vector<double>> P1 = coppersmith_winograd(A11, B_temp);
  vector<vector<double>> A_temp = add(A11, A12);
  vector<vector<double>> P2 = coppersmith_winograd(A_temp, B22);
  A_temp = add(A21, A22);
  vector<vector<double>> P3 = coppersmith_winograd(A_temp, B11);
  B_temp = subtract(B12, B11);
  vector<vector<double>> P4 = coppersmith_winograd(A22, B_temp);
  A_temp = add(A11, A22);
  B_temp = add(A11, A12);
  vector<vector<double>> P5 = coppersmith_winograd(A_temp, B_temp);
  A_temp = subtract(A12, A22);
  B_temp = add(B21, B22);
  vector<vector<double>> P6 = coppersmith_winograd(A_temp, B_temp);
  A_temp = subtract(A11, A21);
  B_temp = add(B11, B12);
  vector<vector<double>> P7 = coppersmith_winograd(A_temp, B_temp);

  // Combinar los resultados
  vector<vector<double>> C(n, vector<double>(n, 0));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      C[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
      C[i][j + m] = P1[i][j] + P2[i][j];
      C[i + m][j] = P3[i][j] + P4[i][j];
      C[i + m][j + m] = P5[i][j] - P3[i][j] - P1[i][j] + P7[i][j];
    }
  }

  return C;
}

int main() {
  int n;
  cout << "Ingrese el tamaño de las matrices cuadradas: ";
  cin >> n;

  vector<vector<double>> A(n, vector<double>(n, 0));
  vector<vector<double>> B(n, vector<double>(n, 0));

  cout << "Ingrese los elementos de la matriz A:" << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
    }
  }

  cout << "Ingrese los elementos de la matriz B:" << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> B[i][j];
    }
  }

  vector<vector<double>> C = coppersmith_winograd(A, B);

  cout << "El resultado de la multiplicación de matrices es:" << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << C[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}