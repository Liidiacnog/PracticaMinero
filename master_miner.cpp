// Lidia Casado
// FP2-DG05

#include "master_miner.h"

void master_miner(tJuego& juego, tPuntuaciones& marcador, int pos) {
    system("cls");
    cout << "\nM A S T E R  M I N E R   2\n\n";
   
    while (juego.numNivel <= NUM_TOTAL_MINAS && juego.estado != ABANDONO && juego.estado != FRACASO) {
        ifstream entrada, movimientos; string nombreArchivo, nombreFicheroMov;

        inicializar_juego(juego);

        //cargar el nombre de los archivos 1.txt, 2.txt, ... de la mina 
        stringstream ss;
        ss << juego.numNivel << ".txt";
        ss >> nombreArchivo;

        if (juego.opcMov == 2) { //si se introducen movimientos por fichero
            cout << "Introduce el nombre del archivo de texto que contiene los movimientos (no hace falta poner .txt): ";
            cin >> nombreFicheroMov;
            stringstream ssF;
            ssF << nombreFicheroMov << ".txt";
            ssF >> nombreFicheroMov;
            movimientos.open(nombreFicheroMov);
        }

        entrada.open(nombreArchivo); //abre los archivos de la mina
        if (entrada.is_open()) {
            jugar(juego, entrada, movimientos);

            system("cls");
            muestraJuego(juego);

            if (juego.estado == EXITO) {
                cout << "\nMina recorrida\n\n";
                actualizar_marcador(marcador, pos, juego.numNivel, juego.mina.plano.size(), juego.mina.plano[0].size(), juego.numGemas, juego.numTNT, juego.numMov);
                mostrar_Minas_Usuario(marcador, pos);
                menu_elige_mina(juego);
                system("cls");
            }
            else if (juego.estado == FRACASO) {
                cout << "\nLe alcanzo la dinamita\n\n";
                int opc = menu_reintentar();
                if (opc == 1) { 
                    //proseguir. Si opc == 0, no se cambia el estado porque es abandonar, y así termina el juego
                    juego.estado = EXPLORANDO;
                    system("cls");
                    mostrar_Minas_Usuario(marcador, pos);
                    menu_elige_mina(juego);
                }
                system("cls");
            }
            else{ //ABANDONO
                cout << "\nPide rescate\n\n";
                int opc = menu_reintentar();
                if (opc == 1) { 
                    //proseguir. Si opc == 0, no se cambia el estado porque es abandonar, y así termina el juego
                    juego.estado = EXPLORANDO;
                    system("cls");
                    mostrar_Minas_Usuario(marcador, pos);
                    menu_elige_mina(juego);
                }
                system("cls");
            }

            entrada.close(); movimientos.close();
        }
        else
            cout << "\nError al cargar el nivel\n";
    }
}

int menu_reintentar() {
    int opc;
    cout << "\n\n¿Quieres seguir jugando?, conservarás tus puntuaciones anteriores, pero esta mina contará como no recorrida.";
    do {
        cout << "\n\n1. Continuar\n0. Abandonar\n\nElige: ";
        cin >> opc;
    } while (opc < 0 || opc > 1);
    return opc;
}

void menu_elige_mina(tJuego& juego) {
    int mina = -1;
    cout << "¿Qué mina quieres explorar?\n";
    cout << "Puedes seleccionar cualquiera de las 5 minas, la hayas recorrido o no.\n";
    cout << "Si escoges una mina ya recorrida, conservarás la mejor de las puntuaciones.\n\n";

    do {
        cout << '\n' << "¿Qué mina quieres explorar?\nIntroduce un número entre 1 y 5 para explorar una mina, y 0 para salir: ";
        cin >> mina;
    } while (mina < 0 || mina > 5);
    if (mina == 0)
        juego.estado = ABANDONO;
    else
        juego.numNivel = mina;
}

void inicializar_juego(tJuego& juego) {
    juego.estado = EXPLORANDO;
    juego.numGemas = 0;
    juego.numMov = 0;
    juego.numTNT = 0;
}