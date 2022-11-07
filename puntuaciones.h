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

const int NUM_TOTAL_MINAS = 5; //num máximo minas/niveles del juego
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
	tDatosMina vMinasRecorridas[NUM_TOTAL_MINAS]; //estático, vector tipo C
};

struct tPuntuaciones {
	int capacidad;
	int num_jugadores;
	tPuntuacionJugador* array_clasificacion; //dinámico
};

/*para guardar nombres usuarios todos en minúscula y poder compararlos*/
string aMinusculas(const string& pal);

/*duplica el tamaño del array*/
void aumentar_Capacidad(tPuntuaciones& marcador);

/*Inicializa una variable de tipo tPuntuacionJugador*/
void inicializar_pj(tPuntuacionJugador& pj);

/*Introduce en el array dinámico los datos disponibles en el fichero Puntuaciones.txt*/
void cargar_Marcador(istream& entrada, tPuntuaciones& marcador);

/* Lista las minas recorridas por una persona, ordenadas por nivel, (pos es la posición de la persona en el array dinámico)*/
void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int pos);

/* Lista los jugadores y sus puntuaciones totales, ordenados por orden alfabético*/
void mostrar_Alfabetico(const tPuntuaciones& marcador);

/* Muestra los datos de todos los usuarios, (usuarios ordenados alfabéticamente, e id de las minas ordenados crecientemente)*/
void mostrar_Datos_Usuario(const tPuntuaciones& marcador);

/* Inicializa el array dinámico */
void inicializar_Marcador(tPuntuaciones& marcador);

/* libera la memoria dinámica */
void destruir(tPuntuaciones& marcador);

/*Busca un nombre en el array dinámico y devuelve si se encuentra o no. 
Devuelve la posición en la cual se encuentra, y si no está en el array devuelve la posición dónde debería estar (manteniendo el orden alfabético) */
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos);

/*Búsqueda binaria recursiva de los datos*/
bool busqueda_Recursiva(const string& nombre, const tPuntuaciones& marcador, int& pos, int ini, int fin);

/*Inserta ordenadamente en la posición pos, un nuevo jugador*/
void insertar(tPuntuaciones& marcador, string const& nombre, int pos);

/*Vuelca el contenido del array dinámico en el fichero salida: Puntuaciones.txt.*/
void guardar_Marcador(ostream& salida, const tPuntuaciones& marcador);

/*actualiza puntos, número de nv, etc en el marcador; una vez recorrida una mina con éxito.
pos es el índice del jugador en el array dinámico*/
void actualizar_marcador(tPuntuaciones& marcador, const int pos, const int nivel, const int numF, const int numC, const int numGemas, const int numTNT, const int numMov);

/*Calcula : Puntuación = Ancho del plano * alto del plano + A * número de gemas recogidas 
							- número de movimientos - B * número de dinamitas utilizadas*/
int calcula_ptos(const int numF, const int numC, const int numGemas, const int numTNT, const int numMov, const tDatosMina& datos);

#endif