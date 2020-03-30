#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/***************************************************projet poker**************************************************
 * ***************************************************************************************************************
 * ***************************************************************************************************************
 ****************************************************************************************************************/

/****************************************************structure***************************************************/
typedef struct carte {
    char valeur;
    char figure;
}carte;

typedef struct main {
    carte cartes[5];
}mainjoueur;

typedef struct score {
    char type[255];
    int score;
}score;

typedef struct joueur {
    int numero;
score scorejoueur;
mainjoueur main;
bool gagnant;
}joueur;

typedef struct joueurs {
    joueur joueur[2];
}joueurs;

carte card;
/***************************************************Définitions***************************************************/

carte* generatecard ();
void generatemain (carte *tirage);

/*************************************************Fonctions*****************************************************/
carte* generatecard() {
    char values[]={'a', 'k', 'q', 'j', 't','9', '8', '7', '6', '5', '4', '3', '2'};
    char figures[]={'H', 'D', 'C', 'S'};
    srand(time(NULL));

        int nbr1 = rand() % 13;
        int nbr2 = rand() % 4;
        card.valeur = values[nbr1];
        card.figure = figures[nbr2];
        printf("%s%s", card.valeur, card.figure);
    return &card;
}
void generatemain(carte *tirage) {
    mainjoueur tiragejoueur1;
    for (int i = 0; i < 5; ++i) {
        generatecard();
        tiragejoueur1.cartes[i] = *tirage;
    }
}

/***************************************************code********************************************************/
int main() {
generatecard();
    return 0;
}
