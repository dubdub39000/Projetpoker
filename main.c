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
carte cartes;
char values[]={'a', 'k', 'q', 'j', 't','9', '8', '7', '6', '5', '4', '3', '2'};
/***************************************************Définitions***************************************************/

carte  generatecard ();
mainjoueur generatemain ();
void affichermain(mainjoueur);
bool is_same_figure(carte *, carte *);
bool is_same_valeur(carte *, carte *);
int  getrang(carte );
/*************************************************Fonctions générations main***************************************/
carte  generatecard() {
    unsigned long seed = clock()+time(NULL)+getpid();
    srand(seed);
    sleep(1);                                                                                                           //timer qui permet de laisser le temps au rand de se réinit.
    char figures[]={'H', 'D', 'C', 'S'};
    int nbr1 = rand() % 13;
    int nbr2 = rand() % 4;
    cartes.valeur = values[nbr1];
    cartes.figure = figures[nbr2];
    printf("carte aleatoire : %c%c\n", cartes.valeur, cartes.figure);                                                 //test de bon fonctionnement
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
    //if (is_same_figure) {                                                                                               //test de fonctionnement des bools
    //    printf("Présence de carte de meme figure\n");
    //}
    //if (is_same_valeur) {
    //    printf("Présence de carte de même valeur\n");
    //}
    return tirage;}

void affichermain(mainjoueur tirage) {
    printf("\nla main du joueur :\n");
    for (int j = 0; j < 5; j++) {
        printf("%c%c\n", tirage.card[j].valeur, tirage.card[j].figure);                                                     // affichage de la main du joueur
    }
}

/*******************************************les bools***********************************************************/
bool is_same_figure(carte * carte1, carte * carte2) {
    if (carte1->figure == carte2->figure)
        return true;
    else
        return false;
}

bool is_same_valeur(carte * carte1, carte * carte2) {                                                                   //manière plus simple et condensé d'écrire un bool il return par défaut TRUE
    return carte1->valeur == carte2->valeur;
}

/*************************************************fonction force et tri de la main******************************/
int getrang(carte  cartes) {
    int a;
    for (int i = 0; i < 13; ++i) {
        if (cartes.valeur==values[i])
        a=i;
    }
    return a;
}

/***************************************************code********************************************************/
int main() {
    //for (int i = 0; i < 5; ++i) {}                                                                                     //boucle test pour tester les doublons
        //generatemain();
        //affichermain(tirage);
        generatecard();
getrang(cartes);

    return 0;
}
