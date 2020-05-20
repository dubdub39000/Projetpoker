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
char values[]={'a', 'k', 'q', 'j', 't','9', '8', '7', '6', '5', '4', '3', '2'};
score result;
/***************************************************Définitions***************************************************/

carte  generatecard ();
mainjoueur generatemain ();
void affichermain(mainjoueur);
bool is_same_figure(carte *, carte *);
bool is_same_valeur(carte *, carte *);
int  getrang(carte );
mainjoueur tri(mainjoueur);
score is_pair( mainjoueur );
score is_four_of_kind(mainjoueur);
/*************************************************Fonctions générations main***************************************/
carte  generatecard() {
    carte cartes;
    unsigned long seed = clock()+time(NULL)+getpid();
    srand(seed);
    sleep(1);                                                                                                           //timer qui permet de laisser le temps au rand de se réinit.
    char figures[]={'H', 'D', 'C', 'S'};
    int nbr1 = rand() % 13;
    int nbr2 = rand() % 4;
    cartes.valeur = values[nbr1];
    cartes.figure = figures[nbr2];
    //printf("carte aleatoire : %c%c\n", cartes.valeur, cartes.figure);                                                 //test de bon fonctionnement
    return cartes;
}
mainjoueur generatemain() {
    for (int i = 0; i < 5; ++i) {                                                                                       // i détermine le nombre de carte par joueur (ici 5).
        tirage.card[i] = generatecard();                                                                                // permet d'appeler la fonction et de récup le résultat. donc 'tirage' recoit 'cartes'.
        for (int j = 0; j < 10; ++j) {
            if (is_same_figure(&tirage.card[i], &tirage.card[i + 1]) &&
                is_same_valeur(&tirage.card[i], &tirage.card[i + 1]))
                i--;
        }
    }
    return tirage;}

void affichermain(mainjoueur tirage) {
    printf("\nla main du joueur :\n");
    for (int j = 0; j < 5; j++) {
        printf("%c%c ", tirage.card[j].valeur, tirage.card[j].figure);                                                     // affichage de la main du joueur
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
    int forces;
        for (int j = 0; j < 13; ++j) {
            if (cartes.valeur == values[j]) {
                forces = j;
            }
        }
    return forces;
}
mainjoueur tri(mainjoueur tirage) {
    carte temp1;
    for (int i = 0; i < 5; ++i) {
        for (int k = i+1; k < 5; ++k) {
        if (getrang(tirage.card[i]) < getrang(tirage.card[k])) {
            temp1 = tirage.card[k];
            tirage.card[k] = tirage.card[i];
            tirage.card[i] = temp1;
        }
        }
    }
    return tirage;
}

/***************************************************Fonction des figures poker**********************************/
score is_pair( mainjoueur tirage) {
    for (int i = 0; i < 4 ; ++i) {
            if (is_same_valeur(&tirage.card[i], &tirage.card[i + 1])) {
                strcpy(result.type, "PAIR");
                result.score = 20;
            }
            else
                break;

    }
    return result;
}

score is_four_of_kind(mainjoueur tirage) {
    for (int i = 0; i < 2 ; ++i) {
            if (tirage.card[i].valeur == tirage.card[i+1].valeur && tirage.card[i].valeur == tirage.card[i+2].valeur && tirage.card[i].valeur == tirage.card[i+3].valeur) {
                strcpy(result.type, "CARRE");
                result.score = 80;
            }
            else
                break;
    }
    return result;
}

/***************************************************déroulement du jeu*************************************************/
int main() {
    for (int i = 0; i < 10; ++i) {                                                                                     //générer plusieurs mains
    generatemain();
    affichermain(tri(tirage));
}
    return 0;
}
