// Lidia Casado
// FP2-DG05

#include "juego.h"
#include "conio.h"

const int NUM_PUNTOS_CARDINALES = 4;
const int NUM_DIRECCIONES = 8;
const std::pair <int, int> dirs4[NUM_PUNTOS_CARDINALES] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; //ARRIBA, ABAJO, IZDA, DCHA
const std::pair <int, int> dirs8[NUM_DIRECCIONES] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1} };
//ARRIBA, ABAJO, IZDA, DCHA, DiagSupIzq, DiagInfIzq, DiagSupDcha, DiagInfDcha;
//  0,      1,     2,    3,      4,          5,           6,           7;

bool dentroPlano(tMina const& mina, int fila, int columna) {
	return fila >= 0 && fila < mina.plano.size() && columna >= 0 && columna < mina.plano[0].size();
}

istream& operator>> (std::istream& movimientos, tTecla& tecla) {
	char mov;
	movimientos >> mov;
	switch (mov) {
	case 'A': { //arriba
		tecla = ARRIBA;
		break;
	}
	case 'Z': { //abajo
		tecla = ABAJO;
		break;
	}
	case 'M': { //derecha
		tecla = DCHA;
		break;
	}
	case 'N': { //izquierda
		tecla = IZDA;
		break;
	}
	case 'S': { //abandona
		tecla = SALIR;
		break;
	}
	case 'D': {//dinamita
		tecla = TNT;
		break;
	}
	default: tecla = NADA;
	}
	return movimientos;
}

void dibujar(tJuego const& juego) {
	if (juego.escala == 1)
		dibujar1_1(juego.mina);
	else if (juego.escala == 2)
		dibujar3_1(juego.mina);
}


void jugar(tJuego& juego, std::istream& entrada, std::istream& movimientos) {
	tTecla tecla;

	cargar_mina(entrada, juego.mina);

	while (juego.estado == EXPLORANDO) {
		muestraJuego(juego);
		/*if (juego.opcMov == 2) //fichero
			system("pause");*/ 
		//descomentar para que, al introducir movimientos por fichero, haya que dar a algún boton para que muestre el siguiente mov
		leerMovimiento(juego, tecla, movimientos);
		if (juego.estado != ABANDONO) {
			realizarMovimiento(juego, tecla);
			system("cls"); 			
		}
	}
}

void leerMovimiento(tJuego& juego, tTecla& tecla, std::istream& movimientos) {
	int movim;
	if (juego.opcMov == 2) { //fichero
		movimientos >> tecla;
		if (tecla == NADA) //Si hay errores en el fichero, o este se acaba y no se ha salido de la mina, se considera abandono
			juego.estado = ABANDONO;
	}
	else if (juego.opcMov == 1) { //teclado
		do {
			cout << "Introduce tu movimiento (usa las flechas para moverte y la tecla 'Esc' para abandonar el juego; ";
			cout << "si quieres soltar dinamita pulsa 'd' o 'D'): \n\n";
			cin.sync();
			movim = _getch();
			if (movim == 0xe0) 
				movim = _getch();
			switch (movim) {
			case (72): {//Flecha arriba
				tecla = ARRIBA;
				break;
			}
			case (75): { //Flecha izquierda  
				tecla = IZDA;
				break;
			}
			case (77): { //Flecha derecha
				tecla = DCHA;
				break;
			}
			case (80): { //Flecha abajo
				tecla = ABAJO;
				break;
			}
			case (27): { //Salir
				tecla = SALIR;
				break;
			}
			case 'D': { //TNT
				tecla = TNT;
				break;
			}
			case 'd': { //TNT
				tecla = TNT;
				break;
			}
			default:
				tecla = NADA;
			}
		} while (tecla == NADA);
	}
	if (tecla == SALIR)
		juego.estado = ABANDONO;
}

void realizarMovimiento(tJuego& juego, const tTecla mov) {
	if (mov == TNT) {
		++juego.numTNT;
		lanzarTNT(juego);
	}
	else {
		int nuevaFila = juego.mina.posic.first + dirs4[mov].first,
			nuevaCol = juego.mina.posic.second + dirs4[mov].second,
			nuevaFPiedra, nuevaCPiedra;
		tElemento elem;
		if (dentroPlano(juego.mina, nuevaFila, nuevaCol)) {
			elem = juego.mina.plano[nuevaFila][nuevaCol];
			switch (elem) {
				case (TIERRA): { //avanza sin problema
					mineroAvanza(juego, nuevaFila, nuevaCol);
					break;
				}
				case (LIBRE): { //avanza sin problema
					mineroAvanza(juego, nuevaFila, nuevaCol);
					break;
				}
				case (PIEDRA): {
					if ((mov == DCHA) || (mov == IZDA)) {
						nuevaFPiedra = nuevaFila + dirs4[mov].first, nuevaCPiedra = nuevaCol + dirs4[mov].second;
						if (dentroPlano(juego.mina, nuevaFPiedra, nuevaCPiedra) && juego.mina.plano[nuevaFPiedra][nuevaCPiedra] == LIBRE) {
							juego.mina.plano[nuevaFPiedra][nuevaCPiedra] = PIEDRA;//nueva posic PIEDRA
							mineroAvanza(juego, nuevaFila, nuevaCol);//la nueva posic MINERO es la anterior de la PIEDRA
							if (hayPozo(juego, nuevaFPiedra, nuevaCPiedra))
								//ahora le pasas a caeCascada la posic de la piedra, para que vea si puede caer
								caeCascada(juego, nuevaFPiedra, nuevaCPiedra, ABAJO);
						}
					}
					break;
				}
				case (GEMA): {
					++juego.numGemas;
					mineroAvanza(juego, nuevaFila, nuevaCol);//la nueva posic MINERO es la anterior de la GEMA
					break;
				}
				case (SALIDA): {
					juego.estado = EXITO;
					mineroAvanza(juego, nuevaFila, nuevaCol);//la nueva posic MINERO es la anterior de la SALIDA
				}
			}//fin switch(mov)
		}
	}
	++juego.numMov;
}

void mineroAvanza(tJuego& juego, const int nuevaFila, const int nuevaCol) {
	int filaAnteriorMinero = juego.mina.posic.first, colAnteriorMinero = juego.mina.posic.second;
	juego.mina.plano[juego.mina.posic.first][juego.mina.posic.second] = LIBRE; //libera la posic actual del MINERO
	juego.mina.plano[nuevaFila][nuevaCol] = MINERO; //nueva posic MINERO 
	juego.mina.posic.first = nuevaFila;
	juego.mina.posic.second = nuevaCol;
	if (desprendimiento(juego, filaAnteriorMinero, colAnteriorMinero))
		caeCascada(juego, filaAnteriorMinero, colAnteriorMinero, ARRIBA);
}

void lanzarTNT(tJuego& juego) {
	int filaTNT = juego.mina.posic.first, colTNT = juego.mina.posic.second, //el MINERO la lanza desde su posic actual
		filaExplota, colExplota;
	while (hayPozo(juego, filaTNT, colTNT)) {
		filaTNT += dirs4[ABAJO].first, colTNT += dirs4[ABAJO].second; //va bajando la TNT
	}
	filaExplota = filaTNT, colExplota = colTNT;
	if (filaExplota == juego.mina.posic.first && colExplota == juego.mina.posic.second) //donde estaba antes el minero
		juego.estado = FRACASO;
	if (juego.mina.plano[filaExplota][colExplota] == SALIDA)
		juego.estado = ABANDONO;
	juego.mina.plano[filaExplota][colExplota] = DINAMITA;
	system("cls");
	muestraJuego(juego);
	system("pause");
	system("cls");
	juego.mina.plano[filaExplota][colExplota] = LIBRE;
	for (int numDirs = 0; numDirs < NUM_DIRECCIONES; ++numDirs) {
		filaExplota += dirs8[numDirs].first, colExplota += dirs8[numDirs].second;
		if (dentroPlano(juego.mina, filaExplota, colExplota) && (juego.mina.plano[filaExplota][colExplota] != LIBRE)) {
			if (juego.mina.plano[filaExplota][colExplota] == MINERO)
				juego.estado = FRACASO;
			if (juego.mina.plano[filaExplota][colExplota] == SALIDA)
					juego.estado = ABANDONO;
			juego.mina.plano[filaExplota][colExplota] = LIBRE;
		}
		filaExplota = filaTNT, colExplota = colTNT;
	}
	derrumbamientosTrasUsarTNT(juego, filaTNT, colTNT, 0); // direcc == ARRIBA
	derrumbamientosTrasUsarTNT(juego, filaTNT, colTNT, 4); //direcc == DiagSupIzq
	derrumbamientosTrasUsarTNT(juego, filaTNT, colTNT, 6); //direcc == DiagSupDcha
}

void derrumbamientosTrasUsarTNT(tJuego& juego, const int filaTNT, const int colTNT, const int numDirecc) {
	if (desprendimiento(juego, filaTNT + dirs8[numDirecc].first, colTNT + dirs8[numDirecc].second))
		caeCascada(juego, filaTNT + dirs8[numDirecc].first, colTNT + dirs8[numDirecc].second, ARRIBA);
}


//FUNCIONES ENCARGADAS CAIDA:

void caeCascada(tJuego& juego, const int fila, const int col, const tTecla direcc) {
	int direccX, direccY, nuevaFila, nuevaCol;
	if (direcc == ARRIBA) { //para desprendimientos
		direccX = dirs4[ARRIBA].first, direccY = dirs4[ARRIBA].second;
		nuevaFila = fila + dirs4[ARRIBA].first, nuevaCol = col + dirs4[ARRIBA].second;
	}
	else if (direcc == ABAJO) {//para caidas por pozos
		direccX = dirs4[ABAJO].first, direccY = dirs4[ABAJO].second;
		nuevaFila = fila, nuevaCol = col;
	}
	//nuevaFila y nuevaCol apuntan a encima del MINERO, o a encima del pozo, donde se mira si cae una PIEDRA

	tElemento elem = juego.mina.plano[nuevaFila][nuevaCol]; //cojo objeto encima de la posic inicial

	while (dentroPlano(juego.mina, nuevaFila, nuevaCol) && (elem == PIEDRA || elem == GEMA || elem == LIBRE)) {
		if ((elem == GEMA) || (elem == PIEDRA))
			caeUna(juego, nuevaFila, nuevaCol, elem);
		nuevaFila += direccX;
		nuevaCol += direccY;
		if (dentroPlano(juego.mina, nuevaFila, nuevaCol))
			elem = juego.mina.plano[nuevaFila][nuevaCol];
	}
}

void caeUna(tJuego& juego, const int fila, const int col, const tElemento elemQueCae) {
	//fila y col son las coord del elem en sí
	int fAbajo = fila + dirs4[ABAJO].first, cAbajo = col + dirs4[ABAJO].second; //coges coord de debajo del elem
	while ((dentroPlano(juego.mina, fAbajo, cAbajo)) && (juego.mina.plano[fAbajo][cAbajo] == LIBRE)) {
		juego.mina.plano[fAbajo][cAbajo] = elemQueCae;
		juego.mina.plano[fAbajo - dirs4[ABAJO].first][cAbajo - dirs4[ABAJO].second] = LIBRE;
		fAbajo += dirs4[ABAJO].first;
		cAbajo += dirs4[ABAJO].second;
	}
}

bool desprendimiento(const tJuego& juego, const int fila, const int col) {
	int nuevaF = fila + dirs4[ARRIBA].first, nuevaC = col + dirs4[ARRIBA].second; //mira encima de la posic anterior del MINERO
	if (dentroPlano(juego.mina, nuevaF, nuevaC))
		return (juego.mina.plano[nuevaF][nuevaC] == PIEDRA) || (juego.mina.plano[nuevaF][nuevaC] == GEMA);
	else return false;
}

bool hayPozo(const tJuego& juego, const int fila, const int col) {
	int nuevaF = fila + dirs4[ABAJO].first, nuevaC = col + dirs4[ABAJO].second;
	if (dentroPlano(juego.mina, nuevaF, nuevaC))
		return (juego.mina.plano[nuevaF][nuevaC] == LIBRE);
	else return false;
}



// MENUS

void muestraJuego(const tJuego& juego) {
	cout << "NIVEL " << juego.numNivel << "\n\n";
	dibujar(juego);
	cout << "\nMovimientos: " << juego.numMov << '\n' << "Gemas: " << juego.numGemas << '\n' << "Dinamitas: " << juego.numTNT << "\n\n";
}

int menuEscala() {
	int escala; 
	cout << "1. Jugar partida a escala 1:1.\n" << "2. Jugar partida a escala 1:3.\n" << "0. Salir.\n";
	cout << "Escoge: ";
	cin >> escala;
	cout << "\n\n";
	
	while (escala < 0 || escala > 2) {
		cin.ignore();
		cout << "Opción no válida, escoge de nuevo\n";
		system("pause");
		system("cls");
		cout << "1. Jugar partida a escala 1:1.\n" << "2. Jugar partida a escala 1:3.\n" << "0. Salir.\n";
		cout << "Escoge: ";
		cin >> escala;
		cout << "\n\n";
	}

	return escala;
}

//no es necesario en la parte 2
/*int menuSigNv() {
	int opc;
	cout << "\n¡Nivel completado!, enhorabuena, el minero puede pasar al siguiente plano de la mina.\n\n";
	cout << "¿Quieres jugar el siguiente nivel o abandonar el juego?\n\n";
	cout << "1. Continuar la aventura.\n" << "0. Abandonar al minero a su suerte y salir.\n" << "Elige: ";
	cin >> opc;
	cout << "\n\n";
	while (opc != 0 && opc != 1) {
		cout << "Opción no válida, escoge de nuevo\n";
		system("pause");
		system("cls");
		cout << "\n¡Nivel completado!, enhorabuena, el minero puede pasar al siguiente plano de la mina.\n\n";
		cout << "¿Quieres jugar el siguiente nivel o abandonar el juego?\n\n";
		cout << "1. Continuar la aventura.\n" << "0. Abandonar al minero a su suerte y salir.\n" << "Elige: ";
		cin >> opc;
		cout << "\n\n";
	}
	system("cls");
	return opc;
}*/

int menuTeclado() {
	int teclado;

	cout << "1. Introducir movimientos por teclado.\n" << "2. Introducir movimientos por fichero.\n" << "0. Salir.\n";
	cout << "Escoge: ";
	cin >> teclado;
	cout << "\n\n";
	while (teclado < 0 || teclado > 2) {
		cout << "Opción no válida, escoge de nuevo\n";
		system("pause");
		system("cls");
		cin.sync();
		cout << "1. Introducir movimientos por teclado.\n" << "2. Introducir movimientos por fichero.\n" << "0. Salir.\n";
		cout << "Escoge: ";
		cin >> teclado;
		cout << "\n\n";
	}
		
	return teclado;
}