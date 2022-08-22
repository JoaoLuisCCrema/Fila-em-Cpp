//João Luís Ciarelotto Crema

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono; 

typedef duration<long, ratio<1, 1000000000>>

    t;
  
void avg(t x[]) { //Isso aqui so serve pra formatar o tempo pra não ficar numeros enormes
  double s = 0, m;
  for (int i = 0; i < 50; i++) {
    s = s + duration_cast<microseconds>(x[i]).count();
  }
  m = s / 50;
  if (m >= 1000)
    cout << trunc(m / 1000) << " milissegundos" << endl;
  else
    cout << trunc(m) << " microssegundos" << endl;
}

int main() {
  queue<int> fila, aux;
  t temps1[50], temps2[50], temps3[50];
  double soma;
  
  for (int i = 0; i <= 50; i++) {
    auto start = steady_clock::now();
    for (int j = 0; j <= 1000000; j++) {
      fila.push(j);
    }
    auto finish = steady_clock::now();
    auto tempo = finish - start;
    temps1[i] = tempo;
  }
  for (int i = 0; i <= 50; i++) {
    auto start = steady_clock::now();
    while (!fila.empty()) {
      soma += fila.front();
      aux.push(fila.front());
      fila.pop();
    }
    auto finish = steady_clock::now();
    auto tempo = finish - start;
    temps2[i] = tempo;
    while (!aux.empty()) {
      fila.push(aux.front());
      aux.pop();
    }
  }
  for (int i = 0; i <= 50; i++) {
    int k = 0;
    srand(time(0));
    int r = 1 + rand() % 1000000;
    auto start = steady_clock::now();
    while (fila.front() != r) {
      aux.push(fila.front());
      fila.pop();
    }
    while (!aux.empty()) {
      fila.push(aux.front());
      aux.pop();
    }
    auto finish = steady_clock::now();
    auto tempo = finish - start;
    temps3[i] = tempo;
  }

  //PrintOut dos tempos
  cout << "tempo para o preenchimento da pilha: ";
  avg(temps1);
  cout << "tempo para a soma da pilha: ";
  avg(temps2);
  cout << "tempo para a verificacao de numero na pilha: ";
  avg(temps3);
}