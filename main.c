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
bool doublons(carte *);
mainjoueur tri(mainjoueur);
score is_pair( mainjoueur );
score is_three_of_kind(mainjoueur);
score is_four_of_kind(mainjoueur);
score is_double_pair(mainjoueur);
score is_flush(mainjoueur);
score is_straight(mainjoueur );
score is_full (mainjoueur);
score is_straight_flush(mainjoueur);
void jeu();
joueur ordinateur();
joueur humain();
score calculresultat(mainjoueur);
void afficheresultat (joueurs *);
joueur bot;
joueur vous;
/*************************************************Fonctions générations main***************************************/
carte  generatecard() {
    carte cartes;
    char figures[]={'H', 'D', 'C', 'S'};
    int nbr1 = rand() % 13;
    int nbr2 = rand() % 4;
    cartes.valeur = values[nbr1];
    cartes.figure = figures[nbr2];
    //printf("carte aleatoire : %c%c\n", cartes.valeur, cartes.figure);                                                 //test de bon fonctionnement
    return cartes;
}
mainjoueur generatemain() {
    for (int i = 0; i < 5;) {                                                                                       // i détermine le nombre de carte par joueur (ici 5).
        tirage.card[i] = generatecard();
            if (doublons(&tirage.card[i])) {
                i--;
            }
            else {
                i++;
            }
    }
    return tirage;
}
/****************************************************affichage**************************************************/
void affichermain(mainjoueur tirage) {
    printf("\nla main du joueur\n" );
    for (int j = 0; j < 5; j++) {
        printf("%c%c ", tirage.card[j].valeur, tirage.card[j].figure);                                                     // affichage de la main du joueur
    }
}

void afficheresultat (joueurs *partie){
    int temp = 0;
    if(partie->joueur->)
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
bool doublons(carte *carte) {
    int compt=0;
        for (int k = 0; k < 5; ++k) {
            if (is_same_figure(carte, &tirage.card[k]) &&
                is_same_valeur(carte, &tirage.card[k]))
                compt++;
            if (compt==2)
                return true;

    }
    return false;
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
                strcpy(result.type, "UNE PAIR");
                result.score = 20;
            }
            else
                break;

    }
    return result;
}
score is_double_pair(mainjoueur tirage) {
    for (int i = 0; i < 4 ; ++i) {
        if (is_same_valeur(&tirage.card[i], &tirage.card[i + 1])) {
            strcpy(result.type, " UNE DOUBLE PAIR");
            result.score = 30;
        }
        else
            break;  }
    return result;
}
score is_three_of_kind(mainjoueur tirage) {
    for (int i = 0; i < 2; ++i) {
        if (tirage.card[i].valeur == tirage.card[i + 1].valeur && tirage.card[i].valeur == tirage.card[i + 2].valeur) {
            strcpy(result.type, " UN BRELAN");
            result.score = 40;
        } else
            break;
        return result;
    }
}

score is_straight(mainjoueur tirage) {
    for (int i = 0; i < 4 ; ++i) {
        if (getrang(tirage.card[i]) == 1+getrang(tirage.card[i+1]) && getrang(tirage.card[i+1]) == 1+getrang(tirage.card[i+2]) && getrang(tirage.card[i+2]) == 1+getrang(tirage.card[i+3]) && getrang(tirage.card[i+3]) == 1+getrang(tirage.card[i+4])){
            strcpy(result.type, "UNE SUITE");
            result.score = 50;
        }
        else
            break;
    }
    return result;
}

score is_flush(mainjoueur tirage) {
    for (int i = 0; i < 2 ; ++i) {
        if (tirage.card[i].figure == tirage.card[i+1].figure && tirage.card[i].figure == tirage.card[i+2].figure && tirage.card[i].figure == tirage.card[i+3].figure && tirage.card[i].figure == tirage.card[i+4].figure){
            strcpy(result.type, "UNE COULEUR");
            result.score = 60;
        }
        else
            break;
    }
    return result;
}
score is_full(mainjoueur tirage) {
    is_pair(tri(tirage));
    if (result.score = 20)
        is_three_of_kind(tri(tirage));
    if (result.score=40){
        strcpy(result.type, "UN FULL");
        result.score = 70;

    }
    return result;
}



score is_four_of_kind(mainjoueur tirage) {
    for (int i = 0; i < 2 ; ++i) {
            if (tirage.card[i].valeur == tirage.card[i+1].valeur && tirage.card[i].valeur == tirage.card[i+2].valeur && tirage.card[i].valeur == tirage.card[i+3].valeur) {
                strcpy(result.type, "UN CARRE");
                result.score = 80;
            }
            else
                break;
    }
    return result;
}

score is_straight_flush(mainjoueur tirage) {
    for (int i = 0; i < 4 ; ++i) {
        if (getrang(tirage.card[i]) == 1+getrang(tirage.card[i+1]) && getrang(tirage.card[i+1]) == 1+getrang(tirage.card[i+2]) && getrang(tirage.card[i+2]) == 1+getrang(tirage.card[i+3]) && getrang(tirage.card[i+3]) == 1+getrang(tirage.card[i+4])
            && (tirage.card[i].figure == tirage.card[i+1].figure && tirage.card[i].figure == tirage.card[i+2].figure && tirage.card[i].figure == tirage.card[i+3].figure && tirage.card[i].figure == tirage.card[i+4].figure)){

            strcpy(result.type, "UNE QUINTE FLUSH");
            result.score = 90;
        }
        else
            break;
    }
    return result;
}
/***************************************************Verification du résultat*******************************************/
score calculresultat(mainjoueur tirage) {
    is_pair(tri(tirage));
    /*****************si presence pair*************/
    if (result.score = 20)
    {
        is_double_pair(tri(tirage));
    is_three_of_kind(tri(tirage));
    if (result.score=40 ) {
        is_full(tri(tirage));
    }   else {
    is_four_of_kind(tri(tirage));
    }
    }
    /******************si non presence pair*********/
    else {
        is_straight(tri(tirage));
        is_flush(tri(tirage));
        if (result.score = 60) {
            is_straight_flush(tri(tirage));
        }
    }
    return result;
}


/***************************************************déroulement du jeu*************************************************/
void jeu() {
    joueurs partie;
        partie.joueur[0]=ordinateur(bot);
        partie.joueur[1]=humain(vous);
}

joueur ordinateur() {
    bot.numero=1;
    bot.main=generatemain();
    affichermain(tri(tirage));
    calculresultat(tirage);
    bot.scorejoueur=result;
    return bot;
}

joueur humain() {
    vous.numero=2;
    vous.main=generatemain();
    affichermain(tri(tirage));
    calculresultat(tirage);
    vous.scorejoueur=result;
    return vous;
}

/*****************************************************main()***********************************************************/
int main() {
    unsigned long seed = clock()+time(NULL)+getpid();
    srand(seed);
    jeu();
    //do {                                                                                    //générer plusieurs mains
    //    jeu();
    //}
    //while (result.score!=40);
    return 0;
}
