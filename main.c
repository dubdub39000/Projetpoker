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
    carte card[5];
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
carte *ptrcard = &card; //obligé de mettre en variable global car sinon le code n'éxecutait que deux boucles dans le generatemain.
/***************************************************Définitions***************************************************/

void generatecard ();
void generatemain ();

/*************************************************Fonctions*****************************************************/
void generatecard() {
    char values[]={'a', 'k', 'q', 'j', 't','9', '8', '7', '6', '5', '4', '3', '2'};
    char figures[]={'H', 'D', 'C', 'S'};
        int nbr1 = rand() % 13;
        int nbr2 = rand() % 4;
        ptrcard->valeur = values[nbr1];
        ptrcard->figure = figures[nbr2];
        printf("carte aleatoire : %c%c\n", ptrcard->valeur, ptrcard->figure); //test de bon fonctionnement
}
void generatemain() {
    mainjoueur tiragejoueur1;
    for (int i = 0; i < 4; ++i) { // i détermine le nombre de carte par joueur.
        generatecard();
        tiragejoueur1.card[i] =*ptrcard;
    }
    for (int j = 0; j < 4; ++j) {


    printf("%c\n", tiragejoueur1.card[j]);
}}

/***************************************************code********************************************************/
int main() {
    srand(time(NULL)); //obligé de le placer là sinon les variable nbr1 et nbr2 ne se réinit pas.
generatemain();
    return 0;
}
