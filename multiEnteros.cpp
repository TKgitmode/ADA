#include <iostream>
#include <math.h>

using namespace std;

int desplaza_izq(int num, int posiciones) {
  return num * static_cast<int>(pow(10, posiciones));
}

int desplaza_der(int num, int posiciones) {
  return num / static_cast<int>(pow(10, posiciones));
}

int multiplicaDV(int X, int Y, int n) {
  int res;
  if (n == 1) {
    return X * Y;
  } else {
    int m = n / 2;
    int xi = desplaza_der(X, m);
    int xd = X % static_cast<int>(pow(10, m));
    int yi = desplaza_der(Y, m);
    int yd = Y % static_cast<int>(pow(10, m));

    int p = multiplicaDV(xi, yi, m);
    int q = multiplicaDV(xd, yd, m);
    int s1 = xi + xd;
    int s2 = yi + yd;
    int r = multiplicaDV(s1, s2, m);

    int aux = r - p - q;
    aux = desplaza_izq(aux, m);
    p = desplaza_izq(p, 2 * m);

    res = p + aux + q;
  }
  return res;
}

int main() {
  int X, Y;
  cout << "Ingrese el valor de X: "; cin >> X;
  cout << "Ingrese el valor de Y: "; cin >> Y;

  int n = max(to_string(X).length(), to_string(Y).length());

  int resultado = multiplicaDV(X, Y, n);

  cout << "Resultado de la multiplicación: " << resultado << endl;
}