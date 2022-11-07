// Lidia Casado
// FP2-DG05

#include "puntuaciones.h"


struct CompString {
	bool operator()(const string& a, const string& b) {
		return aMinusculas(a) < aMinusculas(b);
	}
};

string aMinusculas(const string & pal) { //Para ordenar alfabéticamente nombre sin tener en cuenta mayúsculas o minúsculas
	string palabra = pal;
	for (int i = 0; i < palabra.length(); ++i)
		if ('A' <= palabra[i] && palabra[i] <= 'Z')
			palabra[i] = 'a' + (palabra[i] - 'A');
	return palabra;
}

void inicializar_pj(tPuntuacionJugador& pj) {
	pj.minasRecorridas = 0;
	pj.punt_total = 0;
	for (int i = 0; i < NUM_TOTAL_MINAS; ++i) {//Inicializa vminasrecorridas[]
		pj.vMinasRecorridas[i].idMina = -1; //convenio, si no la ha recorrido vale -1
		pj.vMinasRecorridas[i].numDinamitas = 0;
		pj.vMinasRecorridas[i].numGemas = 0;
		pj.vMinasRecorridas[i].numMovimientos = 0;
		pj.vMinasRecorridas[i].puntosMina = 0;
	}
}

void cargar_Marcador(istream& entrada, tPuntuaciones& marcador) {
	int i = 0; //i es el número de jugadores que se van leyendo del fichero
	string nombre; int mina;
	entrada >> nombre;
	while (nombre != "000") {
		if (i >= marcador.capacidad)//aumentar capac
			aumentar_Capacidad(marcador);
		//lo añade:
		inicializar_pj(marcador.array_clasificacion[i]); 
		//la llamo para que rellene parámetros como ptos de minas sin recorrer, para que no valgan cosas raras
		//además, la llamo para que ponga su idMina a -1, que es el convenio que estamos usando si no la ha recorrido
		marcador.array_clasificacion[i].nombre = nombre;
		entrada >> marcador.array_clasificacion[i].punt_total >> marcador.array_clasificacion[i].minasRecorridas;
		for (int j = 0; j < marcador.array_clasificacion[i].minasRecorridas; ++j) {
			entrada >> mina; //coge idMina de la mina a leer
			marcador.array_clasificacion[i].vMinasRecorridas[mina - 1].idMina = mina;
			entrada >> marcador.array_clasificacion[i].vMinasRecorridas[mina - 1].numMovimientos;
			entrada >> marcador.array_clasificacion[i].vMinasRecorridas[mina - 1].numGemas;
			entrada >> marcador.array_clasificacion[i].vMinasRecorridas[mina - 1].numDinamitas;
			entrada >> marcador.array_clasificacion[i].vMinasRecorridas[mina - 1].puntosMina;
		}
		++marcador.num_jugadores;
		++i;
		entrada >> nombre;
	}
}

void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int pos) {
	cout << setw(6) << marcador.array_clasificacion[pos].nombre << setw(8) << " " << "Movimientos" << setw(8) << " " << "Gemas"
		<< setw(8) << " " << "Dinamitas" << setw(8) << " " << "Puntos" << setw(8) << " " << "Puntos en total" << '\n';
	if (marcador.array_clasificacion[pos].minasRecorridas > 0) {
		int i = 0;
		while (marcador.array_clasificacion[pos].vMinasRecorridas[i].idMina == -1)//no infinito porque ha recorrido al menos 1
			++i;
		cout << "Mina " << (i + 1) << setw(17) << " " << marcador.array_clasificacion[pos].vMinasRecorridas[i].numMovimientos
			<< setw(12) << " " << marcador.array_clasificacion[pos].vMinasRecorridas[i].numGemas << setw(16) << " "
			<< marcador.array_clasificacion[pos].vMinasRecorridas[i].numDinamitas << setw(10) << " "
			<< marcador.array_clasificacion[pos].vMinasRecorridas[i].puntosMina << setw(21) << " "
			<< marcador.array_clasificacion[pos].punt_total << '\n';
		++i;
		while (i < NUM_TOTAL_MINAS) {
			if (marcador.array_clasificacion[pos].vMinasRecorridas[i].idMina != -1) {
				cout << "Mina " << (i + 1) << setw(17) << " " << marcador.array_clasificacion[pos].vMinasRecorridas[i].numMovimientos
					<< setw(12) << " " << marcador.array_clasificacion[pos].vMinasRecorridas[i].numGemas << setw(16) << " "
					<< marcador.array_clasificacion[pos].vMinasRecorridas[i].numDinamitas << setw(10) << " "
					<< marcador.array_clasificacion[pos].vMinasRecorridas[i].puntosMina << '\n';
			}
			++i;
		}
	}
	cout << "\n\n";
}

void mostrar_Alfabetico(const tPuntuaciones& marcador) {
	cout << "\n\n ------------- LISTA DE JUGADORES ------------- \n" << '\n';
	for (int i = 0; i < marcador.num_jugadores; ++i) {
		cout << setw(15) << " " << marcador.array_clasificacion[i].nombre << setw(5) << " " << marcador.array_clasificacion[i].punt_total << '\n';
	}
	cout << "\n";
	system("pause");
	cout << "\n\n";
}

void mostrar_Datos_Usuario(const tPuntuaciones& marcador) {
	cout << setw(8) << ' ' << " ---------------------- JUGADORES ORDENADOS POR NOMBRE ----------------------" << "\n\n";
	for (int i = 0; i < marcador.num_jugadores; ++i) {
		mostrar_Minas_Usuario(marcador, i);
		cout << '\n';
	}
	cout << "\n";
	system("pause");
	cout << "\n\n";
}


//DINÁMICO:

void aumentar_Capacidad(tPuntuaciones& marcador) {
	tPuntuacionJugador* aux = marcador.array_clasificacion;
	marcador.array_clasificacion = new tPuntuacionJugador[marcador.capacidad * 2];
	for (int i = 0; i < marcador.num_jugadores; ++i)
		marcador.array_clasificacion[i] = aux[i];
	delete[] aux;
	marcador.capacidad = marcador.capacidad * 2;
}

void inicializar_Marcador(tPuntuaciones& marcador) {
	marcador.capacidad = 2;
	marcador.num_jugadores = 0;
	marcador.array_clasificacion = new tPuntuacionJugador[marcador.capacidad]; //array dinámico
}

void destruir(tPuntuaciones& marcador) {
	marcador.capacidad = 0;
	marcador.num_jugadores = 0;
	delete[] marcador.array_clasificacion;
	marcador.array_clasificacion = nullptr;
}

bool busqueda_Recursiva(const string& nombre, const tPuntuaciones& marcador, int& pos, int ini, int fin) {
	//fin apunta a marcador.num_jugadores, es decir no es una posic váida del array
	int mitad = (ini + fin) / 2;
	if (marcador.num_jugadores <= 0 || ini == fin) {
		pos = ini; //la posic donde debería estar, porque aún no existe
		return false;
	}
	else {
		if (marcador.array_clasificacion[mitad].nombre == nombre) {
			pos = mitad;
			return true;
		}
		else if (CompString()(marcador.array_clasificacion[mitad].nombre, nombre)) { //hay que mirar a la dcha
			return busqueda_Recursiva(nombre, marcador, pos, mitad + 1, fin);
		}
		else {
			return busqueda_Recursiva(nombre, marcador, pos, ini, mitad);
		}
	}
}

bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos) {
	return busqueda_Recursiva(nombre, marcador, pos, 0, marcador.num_jugadores);
}

void insertar(tPuntuaciones& marcador, string const& nombre, int pos) {
	if (marcador.capacidad <= marcador.num_jugadores) { // < no debería pasar nunca
		aumentar_Capacidad(marcador);
	}
	int i = marcador.num_jugadores - 1;
	while (i >= pos) {//desplaza elem a la derecha para insertar en pos el nuevo jug
		marcador.array_clasificacion[i + 1] = marcador.array_clasificacion[i];
		--i;
	}
	marcador.array_clasificacion[pos].nombre = nombre;
	inicializar_pj(marcador.array_clasificacion[pos]);
	++marcador.num_jugadores;
}

void guardar_Marcador(ostream& salida, const tPuntuaciones& marcador) {
	for (int i = 0; i < marcador.num_jugadores; ++i) {
		salida << marcador.array_clasificacion[i].nombre << '\n' << marcador.array_clasificacion[i].punt_total << '\n' <<
			marcador.array_clasificacion[i].minasRecorridas << '\n';
		if (marcador.array_clasificacion[i].minasRecorridas > 0) {
			int j = 0;
			while (marcador.array_clasificacion[i].vMinasRecorridas[j].idMina == -1)//no infinito porque ha recorrido al menos 1
				++j;
			while (j < NUM_TOTAL_MINAS) {
				if (marcador.array_clasificacion[i].vMinasRecorridas[j].idMina != -1) {
					salida << marcador.array_clasificacion[i].vMinasRecorridas[j].idMina << ' ' <<
						marcador.array_clasificacion[i].vMinasRecorridas[j].numMovimientos << ' ' <<
						marcador.array_clasificacion[i].vMinasRecorridas[j].numGemas << ' ' <<
						marcador.array_clasificacion[i].vMinasRecorridas[j].numDinamitas << ' ' <<
						marcador.array_clasificacion[i].vMinasRecorridas[j].puntosMina << '\n';
				}
				++j;
			}
		}
	}
	salida << "000";
}

void actualizar_marcador(tPuntuaciones& marcador, const int pos, const int nivel, const int numF, const int numC, const int numGemas, const int numTNT, const int numMov) {
	if (marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].idMina == -1) {//1a vez que la recorre
		marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].numDinamitas = numTNT;
		marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].numGemas = numGemas;
		marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].numMovimientos = numMov;
		++marcador.array_clasificacion[pos].minasRecorridas;
		marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].idMina = nivel;
		marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].puntosMina = calcula_ptos(numF, numC, numGemas, numTNT, numMov, marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1]);
		marcador.array_clasificacion[pos].punt_total += marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].puntosMina;
	}
	else {
		int nuevosPtos = calcula_ptos(numF, numC, numGemas, numTNT, numMov, marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1]);
		if (marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].puntosMina < nuevosPtos) { //puntuacion mejorada
			marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].numDinamitas = numTNT;
			marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].numGemas = numGemas;
			marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].numMovimientos = numMov;
			marcador.array_clasificacion[pos].punt_total -= marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].puntosMina;
			marcador.array_clasificacion[pos].vMinasRecorridas[nivel - 1].puntosMina = nuevosPtos;
			marcador.array_clasificacion[pos].punt_total += nuevosPtos;
		}
	}
}

int calcula_ptos(const int numF, const int numC, const int numGemas, const int numTNT, const int numMov, const tDatosMina& datos) {
	return numF * numC + A * numGemas - numMov - B * numTNT;
}

