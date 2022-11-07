// Lidia Casado
// FP2-DG05

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#ifndef _PUNTUACIONES
#define _PUNTUACIONES

const int NUM_TOTAL_MINAS = 5; //num m�ximo minas/niveles del juego
const int A = 10; //cte para calcular ptos por gema
const int B = 2;//cte para calcular ptos por dinamita

struct tDatosMina {
	int idMina, numMovimientos;
	int numGemas, numDinamitas;
	int puntosMina;
};

struct tPuntuacionJugador {
	string nombre;
	int punt_total;
	int minasRecorridas;
	tDatosMina vMinasRecorridas[NUM_TOTAL_MINAS]; //est�tico, vector tipo C
};

struct tPuntuaciones {
	int capacidad;
	int num_jugadores;
	tPuntuacionJugador* array_clasificacion; //din�mico
};

/*para guardar nombres usuarios todos en min�scula y poder compararlos*/
string aMinusculas(const string& pal);

/*duplica el tama�o del array*/
void aumentar_Capacidad(tPuntuaciones& marcador);

/*Inicializa una variable de tipo tPuntuacionJugador*/
void inicializar_pj(tPuntuacionJugador& pj);

/*Introduce en el array din�mico los datos disponibles en el fichero Puntuaciones.txt*/
void cargar_Marcador(istream& entrada, tPuntuaciones& marcador);

/* Lista las minas recorridas por una persona, ordenadas por nivel, (pos es la posici�n de la persona en el array din�mico)*/
void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int pos);

/* Lista los jugadores y sus puntuaciones totales, ordenados por orden alfab�tico*/
void mostrar_Alfabetico(const tPuntuaciones& marcador);

/* Muestra los datos de todos los usuarios, (usuarios ordenados alfab�ticamente, e id de las minas ordenados crecientemente)*/
void mostrar_Datos_Usuario(const tPuntuaciones& marcador);

/* Inicializa el array din�mico */
void inicializar_Marcador(tPuntuaciones& marcador);

/* libera la memoria din�mica */
void destruir(tPuntuaciones& marcador);

/*Busca un nombre en el array din�mico y devuelve si se encuentra o no. 
Devuelve la posici�n en la cual se encuentra, y si no est� en el array devuelve la posici�n d�nde deber�a estar (manteniendo el orden alfab�tico) */
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos);

/*B�squeda binaria recursiva de los datos*/
bool busqueda_Recursiva(const string& nombre, const tPuntuaciones& marcador, int& pos, int ini, int fin);

/*Inserta ordenadamente en la posici�n pos, un nuevo jugador*/
void insertar(tPuntuaciones& marcador, string const& nombre, int pos);

/*Vuelca el contenido del array din�mico en el fichero salida: Puntuaciones.txt.*/
void guardar_Marcador(ostream& salida, const tPuntuaciones& marcador);

/*actualiza puntos, n�mero de nv, etc en el marcador; una vez recorrida una mina con �xito.
pos es el �ndice del jugador en el array din�mico*/
void actualizar_marcador(tPuntuaciones& marcador, const int pos, const int nivel, const int numF, const int numC, const int numGemas, const int numTNT, const int numMov);

/*Calcula : Puntuaci�n = Ancho del plano * alto del plano + A * n�mero de gemas recogidas 
							- n�mero de movimientos - B * n�mero de dinamitas utilizadas*/
int calcula_ptos(const int numF, const int numC, const int numGemas, const int numTNT, const int numMov, const tDatosMina& datos);

#endif