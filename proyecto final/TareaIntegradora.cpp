//David Casanova
//A01282921
//Descripcion: Juego estilo damas chinas.

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

char cMatTablero[4][4];

const int longitud = 3;

//Llenar el tablero de manera aleatoria.
void llenaTablero(){

    int iR, iC, iCont;

    for (iR = 0; iR < 4; iR++)
        for (iC = 0; iC < 4; iC++)
        cMatTablero[iR][iC] = ' ';
    srand((int)time(0));
    for (iCont = 1; iCont <= 13; ){
        iR = rand() % 4; // esto genera un numero aleatorio
        iC = rand() % 4; // entre 0 y 3
        if (cMatTablero[iR][iC] == ' '){
            cMatTablero[iR][iC] = 'X';
            iCont++;
        }
    }
}

//Mostrar el tablero.
void MostrarTablero (){

    int cont = 1;

    for(int renglon = 0; renglon <= longitud; renglon++){
        for(int col = 0; col <= longitud; col++){
            if(cont < 9)
                cout<< cont << "[" << cMatTablero [renglon][col] << "]" << "   ";
            if((cont >= 9) && (cont <= 16))
                cout<< cont << "[" << cMatTablero [renglon][col] << "]" << "  ";
            cont++;
        }
        cout<< endl << endl;
    }

}

// Calcular las coordenadas de las casillas con el numero de columna (0 - 2).
void CalcularCasilla(int &col, int &ren, int casilla){
    col = ((casilla % 4) - 1);
    ren = (casilla / 4);
}

//Calcular las cordenadas de las casillas con el numero de columna 3.
void CalcularCol3 (int &col, int &ren, int casilla){
    col = 3;
    ren = ((casilla / 5));
}

//Contar las fichas que quedan en el tablero.
void ContarFichas(bool &unaficha, int &fichasRestantes){

    fichasRestantes = 0;

    for(int renglon = 0; renglon <= longitud; renglon++){
        for(int col = 0; col <= longitud; col++){
            if (cMatTablero[renglon][col] == 'X')
                fichasRestantes++;
        }
    }
    if(fichasRestantes == 1)
        unaficha = true;

}

//Pedir los datos al usuario.
void PedirDatos(int &casilla, char &direccion){

    do{
        cout<< "Casilla --> ";
        cin>> casilla;
    }while((casilla < 1) || (casilla > 16));

    do{
        cout<< "(a - izq; s - aba; w - arr; d - der) --> ";
        cin>> direccion;
        direccion = tolower(direccion);
    }while((direccion != 'a') && (direccion != 's') && (direccion != 'w') && (direccion != 'd'));

}
int main(){

    llenaTablero();

    int casilla, col, ren, fichasRestantes;
    bool unaficha = false, movCheck = false;
    char direccion, resp;

    do{
        do{
            MostrarTablero();
            PedirDatos(casilla, direccion);

            if((casilla % 4) == 0){
                CalcularCol3(col, ren, casilla);
            }
            else{
                CalcularCasilla(col, ren, casilla);
            }

            if(cMatTablero[ren][col] == 'X'){
                switch (direccion){
                    case 'w':
                        if(((ren-2) >= 0) && (cMatTablero[(ren-1)][col] == 'X') && (cMatTablero[(ren-2)][col] == ' ')){
                           cMatTablero[(ren-2)][col] = 'X';
                           cMatTablero[(ren-1)][col] = ' ';
                           cMatTablero [ren][col] = ' ';
                           movCheck = true;
                        }
                           break;
                    case 's':
                        if(((ren+2) <= 3) && (cMatTablero[(ren+1)][col] == 'X') && (cMatTablero[(ren+2)][col] == ' ')){
                            cMatTablero[(ren+2)][col] = 'X';
                            cMatTablero[(ren+1)][col] = ' ';
                            cMatTablero [ren][col] = ' ';
                            movCheck = true;
                        }
                            break;
                    case 'd':
                        if(((col+2) <= 3) && (cMatTablero[ren][(col+1)] == 'X') && (cMatTablero[ren][(col+2)] == ' ')){
                            cMatTablero[ren][(col+2)] = 'X';
                            cMatTablero[ren][(col+1)] = ' ';
                            cMatTablero [ren][col] = ' ';
                            movCheck = true;
                        }
                            break;
                    case 'a':
                        if (((col-2) >= 0) && (cMatTablero[ren][(col-1)] == 'X') && (cMatTablero[ren][(col-2)] == ' ')){
                            cMatTablero[ren][(col-2)] = 'X';
                            cMatTablero[ren][(col-1)] = ' ';
                            cMatTablero [ren][col] = ' ';
                            movCheck = true;
                        }
                            break;
                }
            }
        }while(movCheck == false);

        MostrarTablero();
        ContarFichas(unaficha, fichasRestantes);

        if (unaficha == true){
            cout<< endl << "GANASTE!" << endl;
            return 0;
        }

        do{
            cout<< "¿Quieres seguir jugando? --> ";
            cin>> resp;
            resp = tolower(resp);

        }while(resp != 's' && resp != 'n');

    }while(resp == 's');

    ContarFichas(unaficha, fichasRestantes);

    cout<< endl << "El juego no termino..." << endl;
    cout<< "Quedaron " << fichasRestantes << " fichas." << endl;

    return 0;
}
