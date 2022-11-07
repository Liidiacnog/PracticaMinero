// Lidia Casado
// FP2-DG05

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#ifndef _MINA
#define _MINA

//para definir los elementos que pueden encontrarse en la mina.
enum tElemento { TIERRA, PIEDRA, MURO, GEMA, SALIDA, LIBRE, MINERO, DINAMITA};

using tMatriz = vector<vector<tElemento>>;

struct tMina {
	tMatriz plano;
	pair<int, int> posic;
};

//transforma un caracter en un valor del tipo enumerado tElemento
tElemento char2elem(char c);

//sobrecarga del operador <<, para escribir los valores del tipo enumerado
ostream& operator<< (std::ostream& out, tElemento const& e);

//la matriz se muestra con las funciones siguientes:

//lee el plano de la mina del fichero y lo guarda en memoria. Actualiza la posicion del minero en la mina.
void cargar_mina(std::istream& fichero, tMina& mina);

//muestra por pantalla el plano en escala 1:1
void dibujar1_1(tMina const& mina);

//muestra por pantalla el plano en escala 1:3
void dibujar3_1(tMina const& mina);

void color(int colorFond, int colorText);//para manejar cambio colores caracteres

void muestraColor(const tElemento elem, const int vez); //muestra cada casilla en escala 3 a 1

#endif