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
carte *ptrcard = &card;
/***************************************************Définitions***************************************************/

void generatecard ();
void generatemain ();

/*************************************************Fonctions*****************************************************/
void generatecard() {
    memset(ptrcard, '\0', sizeof(card));
    char values[]={'a', 'k', 'q', 'j', 't','9', '8', '7', '6', '5', '4', '3', '2'};
    char figures[]={'H', 'D', 'C', 'S'};
    srand(time(NULL));
        int nbr1 = rand() % 13;
        int nbr2 = rand() % 4;
        ptrcard->valeur = values[nbr1];
        ptrcard->figure = figures[nbr2];
        printf("carte aleatoire : %c%c\n", ptrcard->valeur, ptrcard->figure); //test de bon fonctionnement
}
void generatemain() {
    mainjoueur tiragejoueur1;
    for (int i = 0; i < 4; ++i) {
        generatecard();
        tiragejoueur1.cartes[i] =*ptrcard;
    }
    for (int j = 0; j < 4; ++j) {                     //affiche la main du joueur 1
        printf("%c", tiragejoueur1.cartes[j]);
    }
}

/***************************************************code********************************************************/
int main() {
generatemain();
    return 0;
}
