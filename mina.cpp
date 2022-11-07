// Lidia Casado
// FP2-DG05

#include "mina.h"
#include "Windows.h"

enum tColor {
    NEGRO, AZUL_OSC, VERDE_OSC, CIAN_OSC, ROJO_OSC, MAGENTA_OSC, AMARILLO_OSC, GRIS_CLARO, GRIS_OSC, 
    AZUL_CLARO, VERDE_CLARO, CIAN_CLARO, ROJO_CLARO, MAGENTA_CLARO, AMARILLO_CLARO, BLANCO
};

const int MAX_TAM = 3; //orden de la matriz que representa cada casilla en escala 3 a 1


tElemento char2elem(char c) {
    tElemento elem;
    switch (c) {
        case '-': {
            elem = LIBRE;
            break;
        }
        case 'G': {
            elem = GEMA;
            break;
        }
        case 'M': {
            elem = MURO;
            break;
        }
        case 'J': {
            elem = MINERO;
            break;
        }
        case 'T': {
            elem = TIERRA;
            break;
        }
        case 'S': {
            elem = SALIDA;
            break;
        }
        case 'D': {
            elem = DINAMITA;
            break;
        }
        case 'P': {
elem = PIEDRA;
        }
    }
    return elem;
}

ostream& operator<< (ostream& out, tElemento const& e) {
    switch (e) {
    case LIBRE: {
        out << '-';
        break;
    }
    case GEMA: {
        out << 'G';
        break;
    }
    case MURO: {
        out << 'X';
        break;
    }
    case MINERO: {
        out << 'M';
        break;
    }
    case TIERRA: {
        out << '.';
        break;
    }
    case SALIDA: {
        out << 'S';
        break;
    }
    case DINAMITA: {
        out << 'D';
        break;
    }
    case PIEDRA: {
        out << '@';
    }
    }
    return out;
}

void cargar_mina(istream& fichero, tMina& mina) {
    int numF, numC;
    char aux;

    fichero >> numF >> numC;

    tMatriz plano(numF);
    vector<tElemento> elem(numC);

    fichero.ignore();//salto linea
    for (int n = 0; n < numF; ++n) {
        for (int m = 0; m < numC; ++m) {
            fichero >> aux;
            elem[m] = char2elem(aux);
            if (char2elem(aux) == MINERO) {
                mina.posic.first = n;
                mina.posic.second = m;
            }
        }
        plano[n] = elem;
    }
    mina.plano = plano;
}

void dibujar1_1(tMina const& mina) {
    for (int n = 0; n < mina.plano.size(); ++n) {
        for (int m = 0; m < mina.plano[0].size(); ++m) {
            cout << mina.plano[n][m];
        }
        cout << '\n';
    }
}

void color(int colorFond, int colorText) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, colorText | (colorFond << 4));
}

void muestraColor(const tElemento elem, const int vez) {
    color(tColor(NEGRO), tColor(BLANCO));
    switch (elem) {
        case LIBRE: {
            //color fondo negro
            for (int j = 0; j < MAX_TAM; ++j)
                cout << setw(2) << ' ';
            break;
        }
        case GEMA: {
            color(tColor(VERDE_CLARO), tColor(BLANCO));
            if (vez == 2)
                cout << setw(2) << '*' << setw(2) << 'G' << setw(2) << '*';
            else 
                for (int j = 0; j < MAX_TAM; ++j) 
                   cout << setw(2) << '*';
            break;
        }
        case MURO: {
           color(tColor(GRIS_OSC), tColor(NEGRO));
           for (int j = 0; j < MAX_TAM; ++j)
               cout << setw(2) << 'X';
           break;
        }
        case MINERO: {
            color(tColor(AZUL_CLARO), tColor(BLANCO));
            if (vez == 2)
                cout << setw(2) << '|' << setw(2) << 'J' << setw(2) << '|';
            else //primera o última columna
                cout << setw(2) << '|' << setw(2) << '-' << setw(2) << '|';
            break;
        }
        case TIERRA: {
            color(tColor(NEGRO), tColor(BLANCO));
            for (int j = 0; j < MAX_TAM; ++j)
                cout << setw(2) << '.';
            break;
        }
        case SALIDA: {
            color(tColor(CIAN_OSC), tColor(BLANCO));
            cout << setw(2) << 'F' << setw(2) << 'I' << setw(2) << 'N';
            break;
        }
        case DINAMITA: {
            color(tColor(ROJO_CLARO), tColor(NEGRO));
            cout << setw(2) << 'T' << setw(2) << 'N' << setw(2) << 'T';
            break;
        }
        case PIEDRA: {
            color(tColor(GRIS_CLARO), tColor(NEGRO));
            if (vez == 1)
                cout << setw(2) << 'P' << setw(2) << 'I' << setw(2) << 'E';
            else if(vez == 2) 
                cout << setw(2) << ' ' << setw(2) << ' ' << setw(2) << ' ' ;
            else
                cout << setw(2) << 'D' << setw(2) << 'R' << setw(2) << 'A';
        }
    }
    color(tColor(NEGRO), tColor(BLANCO));
}

void dibujar3_1(tMina const& mina) { //con color
    for (int n = 0; n < mina.plano.size(); ++n) {
        for (int vez = 1; vez <= MAX_TAM; ++vez) {
            for (int m = 0; m < mina.plano[0].size(); ++m)
                muestraColor(mina.plano[n][m], vez);
            cout << '\n';
        }
    }
}



/*void dibujar3_1(tMina const& mina) { //sin color
    for (int n = 0; n < mina.plano.size(); ++n) {
        for (int veces2 = 0; veces2 < 3; ++veces2) {
            for (int m = 0; m < mina.plano[0].size(); ++m) {
                for (int veces1 = 0; veces1 < 3; ++veces1) {
                    cout << mina.plano[n][m];
                }
            }
            cout << '\n';
        }
    }
}*/