// Lidia Casado
// FP2-DG05

#include "juego.h"
#include "puntuaciones.h"

//master_miner.h sustituye al main de la parte 1, e incluye algún menú nuevo

#ifndef _JUGAR
#define _JUGAR

/*main en la parte 1 de la práctica, se encarga de gestionar el juego como tal: mensajes de éxito,... ; y funciones para jugar.
En pos le pasas el índice del jugador*/
void master_miner(tJuego& juego, tPuntuaciones& marcador, int pos);

/*muestra el menú para seleccionar a siguiente mina a recorrer*/
void menu_elige_mina(tJuego& juego);

//inicializa parámetros numGemas, movimientos etc; al recorrer una nueva mina
void inicializar_juego(tJuego& juego);

//devuelve 0 si el jugador quiere salir, y 1 si quiere proseguir
int menu_reintentar();

#endif