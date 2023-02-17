// BlackJackGame.cpp

#include <iostream>
#include <windows.h>

using namespace std;

//Variables in game
bool gameOver = false;
int numCarta;
int totalPoints = 0;
//Palos
int picas[13];
int diamantes[13];
int corazones[13];
int treboles[13];

//Player 1
string nameP1 = "Manolo";
int pointsP1 = 0;
bool surrenderP1 = false;
bool loserP1 = false;
bool winnerP1 = false;

//Player 2
string nameP2 = "Croupiere";
int pointsP2 = 0;
bool surrenderP2 = false;
bool loserP2 = false;
bool winnerP2 = false;


void inicializarPalos(int(&palo)[13]) {
    for (int i = 0; i < 13; i++) {
        palo[i] = 1;
    }
    }

void exceptions(int &points, string player) {
    if (player == nameP1) {
        int option;
        cout << "Te ha tocado un AS y tienes " << points << ", cuanto quieres que valga?" << endl;
        cout << "[1] - 1" << endl;
        cout << "[2] - 11" << endl;
        cin >> option;
        switch (option)
        {
        case 1:
            points += 1;
            break;
        case 2:
            points += 11;
            break;
        default:
            break;
        }
    }
    else {
        if (points <= 10){
            points += 11;
        }
        else {
            points += 1;
        }
    }
}

void chooseCards(int& totalPoints, string player) {
    bool selected = false;
    string Palo;
    int indicePalo = rand() % 4;
    numCarta = rand() % 13;
    while (!selected) {
        //Numero random de palo
        if (indicePalo == 0) {
            //comprueba picas
            if (picas[numCarta] == 1) {
                    picas[numCarta] == 0;
                    selected = true;
                    Palo = "copas";
                }
        }
        else if (indicePalo == 1) {
            //comprueba diamantes
            if (diamantes[numCarta] == 1) {
                    diamantes[numCarta] == 0;
                    selected = true;
                    Palo = "diamantes";
            }
        }
        else if (indicePalo == 2) {
            //comprueba corazones
            if (corazones[numCarta] == 1) {
                    corazones[numCarta] == 0;
                    selected = true;
                    Palo = "corazones";
            }
        }
        else {
            //comprueba treboles
            if (treboles[numCarta] == 1) {
                    treboles[numCarta] == 0;
                    selected = true;
                    Palo = "treboles";
            }
        }
    }

    //numero de carta random

    if (numCarta >= 10) {
        totalPoints += 10;
        if (numCarta == 11) {
            cout << "El jugador " << player << " ha sacado una J de " << Palo << " y tiene un total de " << totalPoints << endl;
        }
        else if (numCarta == 12) {
            cout << "El jugador " << player << " ha sacado una Q de " << Palo << " y tiene un total de " << totalPoints << endl;
        }
        else {
            cout << "El jugador " << player << " ha sacado un K de " << Palo << " y tiene un total de " << totalPoints << endl;
        }

    }
    else if (numCarta == 0) {
        if (player == nameP1) {
            exceptions(totalPoints, player);
        }
        else {
            exceptions(totalPoints, player);
            cout << "El jugador " << player << " ha sacado un AS de " << Palo << " y tiene un total de " << totalPoints << endl;
        }
    }
    else {
        totalPoints += numCarta + 1;
        cout << "El jugador " << player << " ha sacado un " << numCarta +1 << " de " << Palo << " y tiene un total de " << totalPoints << endl;
    }

   
}

bool checkPoints(int& points, bool& winner, bool& loser) {
    if (points == 21) {
        winner = true;
        return true;
    }
    else if (points > 21) {
        loser = true;
        return true;
    }
    return false;
}

bool checkWhoWins(int points1, int points2, bool& winner2) {
    if (points2 >= points1) {
        winner2 = true;
        return true;
    }
    else {
        return false;
    }
}

int main()
{
    srand(time(NULL));
    inicializarPalos(picas);
    inicializarPalos(diamantes);
    inicializarPalos(corazones);
    inicializarPalos(treboles);
    chooseCards(pointsP1, nameP1);
    Sleep(1500);
    chooseCards(pointsP1, nameP1);
    Sleep(1500);
    surrenderP1 = checkPoints(pointsP1, winnerP1, loserP1);

    chooseCards(pointsP2, nameP2);

    while (!surrenderP1) {
        int choice = 0;
        //Juega el jugador 1
        Sleep(1500);
        while (choice != 1 && choice != 2) {
            cout << "Tienes " << pointsP1 << " puntos. Quieres pedir carta?" << endl;
            cout << "[1] - Sí" << endl;
            cout << "[2] - No" << endl;
            cin >> choice;
            //Eleccion erronea
            if (choice != 1 && choice != 2) {
                cout << "Elije una opción válida." << endl;
            }
        }
        if (choice == 1) {
            //Da carta y comprueba si te pasas o no
            chooseCards(pointsP1, nameP1);
            surrenderP1 = checkPoints(pointsP1, winnerP1, loserP1);
            Sleep(1500);
        }
        else {
            //No quieres mas cartas
            surrenderP1 = true;
        }
    }
    //Comprueba si el jugador 1 gana o pierde, o le toca jugar a la banca
    if (loserP1) {
        cout << "El jugador " << nameP1 << " pierde y la banca gana" << endl;
    }
    else if (pointsP1 == pointsP2) {
        cout << "Has empatado.";
    }
    else if (!loserP1 || pointsP1 <= pointsP2){
        cout << "El jugador " << nameP1 << " tiene "<< pointsP1 <<" por lo que la banca juega" << endl;
        //Juega la banca
        while (!surrenderP2) {
            //Reparte carta
            chooseCards(pointsP2, nameP2);
            Sleep(1500);
            //Comprueba el resultado
            surrenderP2 = checkPoints(pointsP2, winnerP2, loserP2);
            if (!surrenderP2) {
                //Comprueba si la banca gana
                surrenderP2 = checkWhoWins(pointsP1, pointsP2, winnerP2);
            }
        }
        Sleep(1500);
        //Muestra quien gana
        if (winnerP2 && pointsP1 != pointsP2) {
            cout << "La banca gana y el jugador " << nameP1 << " pierde" << endl;
        }
        else if (loserP2) {
            cout << "La banca pierde y el jugador " << nameP1 << " gana" << endl;
        }
        else if (winnerP2 && pointsP1 == pointsP2){
            cout << "Has empatado";
        }
    
    }
}