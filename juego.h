// Lidia Casado
// FP2-DG05

#include <sstream>
#include "mina.h"
using namespace std;

#ifndef _JUEGO
#define _JUEGO

enum tTecla {ARRIBA, ABAJO, IZDA, DCHA, SALIR, TNT, NADA};

enum tEstado {EXPLORANDO, EXITO, ABANDONO, FRACASO};

struct tJuego {
	tMina mina;
	tEstado estado;
	int numGemas, numMov, numTNT, escala, opcMov, numNivel;
};


/*lee, del flujo de entrada de movimientos, un movimiento; y devuelve el valor del tipo enumerado correspondiente*/
istream& operator>> (std::istream& movimientos, tTecla& tecla);

/*comprueba si una posicion esta dentro del plano*/
bool dentroPlano(tMina const& mina, int x, int y);

/*manda dibujar el plano de la mina a la escala que tiene guardada en las opciones del juego*/
void dibujar(tJuego const& juego);


/*Muestra el menu para preguntar la forma de introducir datos (teclado o fichero)*/
int menuTeclado();

/*Muestra el menu para preguntar la escala*/
int menuEscala();

//muestra num movimientos, gemas, tnt, etc y muestra el plano durante el juego
void muestraJuego(const tJuego& juego);


/*no es necesario en la parte 2
//pregunta al usuario si quiere pasar al siguiente nivel o abandonar el juego
int menuSigNv();
*/


/*carga los datos de la mina, va leyendo los movimientos, y para cada uno modifica la mina de acuerdo con el
movimiento. Los movimientos no los almacena, los trata segun los va leyendo*/
void jugar(tJuego& juego, std::istream& entrada, std::istream& movimientos);

/*lee un movimiento del fichero, con la sobrecarga del operador. Si el minero selecciona el movimiento
SALIR, pone el estado del minero en ABANDONO.*/
void leerMovimiento(tJuego& juego, tTecla& tecla, std::istream& movimientos);

/*realiza el movimiento indicado en el parametro mov, modificando el plano de la mina y la posicion del minero en la mina.*/
void realizarMovimiento(tJuego& juego, const tTecla mov);

//coloca al MINERO en su nueva posic, y deja la anterior libre
void mineroAvanza(tJuego& juego, const int nuevaFila, const int nuevaCol);

/*se encarga de que la dinamita caiga hasta el fondo del pozo, explote, liberando todas las casillas adyacentes
a ella, y luego comprueba si la explosion ha dejado piedras sueltas (en caso afirmativo las hace caer).*/
void lanzarTNT(tJuego& juego);

/*comprueba si hay derrumbamientos en la direcc (de tdirs8) que le envies en el string direcc, tras usar dinamita
Y si los hay los realiza*/
void derrumbamientosTrasUsarTNT(tJuego& juego, const int filaTNT, const int colTNT, const int numDirecc);


//FUNCIONES ENCARGADAS CAIDA:

/*permite realizar la caida de las piedras o gemas en cascada. Le pasas la posic del MINERO o la 
piedra que vaya a caer, y en direcc le dices si hay un desprendimiento (en ese caso tiene que mirar si en 
direcc == ARRIBA, está libre para la caída), o si es una caida por un pozo (direcc == ABAJO)*/
void caeCascada(tJuego& juego, const int fila, const int col, const tTecla direcc);

/*gestiona la caida de un solo tElemento mientras el espacio que tiene debajo esta LIBRE*/
void caeUna(tJuego& juego, const int fila, const int col, const tElemento elemQueCae);

//le pasas la posic anterior del minero y comprueba si ha dejado de sujetar (al moverse, o sea detras suyo), piedras o gemas
bool desprendimiento(const tJuego& juego, const int fila, const int col);

//devuelve true si debajo de un objeto hay espacio libre. Le pasas la posic del objeto
bool hayPozo(const tJuego& juego, const int fila, const int col);


#endif