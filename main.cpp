// Lidia Casado
// FP2-DG05

#include "master_miner.h"
//master_miner.h sustituye al main de la parte 1


int main() {
	system("chcp 1252");
	system("cls");

	ifstream entrada1;

	entrada1.open("Puntuaciones.txt");
	if (!entrada1.is_open()) {
		cout << "Error al leer Puntuaciones.txt.";
		system("pause");
	}
	else {
		tPuntuaciones marcador;
		inicializar_Marcador(marcador);
		cargar_Marcador(entrada1, marcador);

		cout << "M A S T E R  M I N E R  2\n\n";

		tJuego juego;

		juego.escala = menuEscala();
		if (juego.escala != 0) {
			juego.opcMov = menuTeclado();	
		}
		if (juego.escala == 0 || juego.opcMov == 0)
			juego.estado = ABANDONO;

		system("cls");

		if (juego.estado != ABANDONO) {
			string nombre; int pos = -1; //pos es el índice del jugador en el array dinámico

			cout << "M A S T E R  M I N E R  2\n\n";
			cout << "Introduce tu nombre de jugador/a: ";
			cin >> nombre;

			if (buscar(nombre, marcador, pos)) { //jugador ya registrado
				cout << "\n\nYa estás registrado/a.";
				cout << "\n\nEstas son las minas que has recorrido, ordenadas por nivel:\n\n";
				mostrar_Minas_Usuario(marcador, pos);
			}
			else { //nuevo jugador
				cout << "\n\nSe te ha creado un nuevo usuario.";
				cout << "\n\nEstas son las puntuaciones de tus adversarios, ordenadas por nivel:";
				mostrar_Alfabetico(marcador);
				insertar(marcador, nombre, pos);
			}

			inicializar_juego(juego);
			menu_elige_mina(juego);

			//empieza a jugar
			master_miner(juego, marcador, pos);
			mostrar_Datos_Usuario(marcador);

			ofstream salida;
			salida.open("Puntuaciones.txt");
			if (salida.is_open())
				guardar_Marcador(salida, marcador); 
			else cout << "\nNo se ha guardado la partida correctamente.";

			//Devuelvo la memoria al heap
			destruir(marcador);
		}
	}
	
	return 0;
}
