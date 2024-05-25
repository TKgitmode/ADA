#include <iostream>
#include <vector>

using namespace std;

vector<int> cambioMonedas(int cambio, vector<int> monedas) {
  int act = 0;
  vector<int> res;
  int j = monedas.size() - 1;

  for (int i = 0; i < monedas.size(); i++) {
    res.push_back(0);
  }

  while (act != cambio) {
    while (monedas[j] > (cambio - act) && j >= 0) {
      j--;
    }
    if (j == -1) {
      return res;
    }
    res[j] = (cambio - act) / monedas[j];
    act = act + (res[j] * monedas[j]);
  }
  return res;
}

int main() {
  int cambio = 384;
  vector<int> monedas = {2, 5, 10, 20, 50, 100, 200};
  vector<int> res = cambioMonedas(cambio, monedas);

  for(int i=0; i<res.size(); i++){
    cout << res[i] << " ";
  }
}