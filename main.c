#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

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

mainjoueur tirage;

/***************************************************Définitions***************************************************/

carte  generatecard ();
mainjoueur generatemain ();
void affichermain(mainjoueur);
/*************************************************Fonctions générations main***************************************/
carte  generatecard() {
    unsigned long seed = clock()+time(NULL)+getpid();
    srand(seed);
    sleep(1);                                                                                                           //timer qui permet de laisser le temps au rand de se réinit.
    char values[]={'a', 'k', 'q', 'j', 't','9', '8', '7', '6', '5', '4', '3', '2'};
    char figures[]={'H', 'D', 'C', 'S'};
    carte cartes;
    int nbr1 = rand() % 13;
    int nbr2 = rand() % 4;
    cartes.valeur = values[nbr1];
    cartes.figure = figures[nbr2];
    //printf("carte aleatoire : %c%c\n", cartes.valeur, cartes.figure);                                             //test de bon fonctionnement
    return cartes;
}
mainjoueur generatemain() {
    carte tabverif[10];
    int i;
    for (i =0 ; i < 5; i++) {                                                                                           // i détermine le nombre de carte par joueur (ici 5).
        carte card=generatecard();                                                                                      // permet d'appeler la fonction et de récup le résultat. donc 'card' recoit 'cartes'.
        for (int j = 0; j < 10; ++j) {
            if (card.valeur == tabverif[j].valeur && card.figure == tabverif[j].figure)
                i--;
        }
        tabverif[i].valeur=card.valeur;
        tabverif[i].figure=card.figure;
        tirage.card[i] = card;
        //printf("%c %c", card.valeur, card.figure);
    }
    return tirage;}

void affichermain(mainjoueur tirage) {
    printf("\nla main du joueur :\n");
    for (int j = 0; j < 5; j++) {
        printf("%c%c\n", tirage.card[j].valeur, tirage.card[j].figure);                                                     // affichage de la main du joueur
    }
}

/*******************************************fonction main et score**********************************************/


/***************************************************code********************************************************/
int main() {
    //for (int i = 0; i < 5; ++i) {}                                                                                     //boucle test pour tester les doublons
        generatemain();
        affichermain(tirage);

    return 0;
}
