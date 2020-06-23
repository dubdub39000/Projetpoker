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

/***************************************************Définitions***************************************************/
carte  generatecard ();
mainjoueur generatemain ();
void affichermain(mainjoueur, joueur);
bool is_same_figure(carte *, carte *);
bool is_same_valeur(carte *, carte *);
int  getrang(carte );
bool doublons(carte *);
mainjoueur tri(mainjoueur);
score is_high_card (mainjoueur);
score is_pair( mainjoueur );
score is_three_of_kind(mainjoueur);
score is_four_of_kind(mainjoueur);
score is_double_pair(mainjoueur);
score is_flush(mainjoueur);
score is_straight(mainjoueur );
score is_full (mainjoueur);
score is_straight_flush(mainjoueur);
void jeu();
score calculresultat(mainjoueur);
void afficheresultat (joueurs *, int);
void comparemains(joueurs []);
void matrice_CH();
joueur deroulement(int );
/******************************************************variable global*********************************************/
int forces;
mainjoueur tirage;
char values[]={'2', '3', '4', '5', '6','7', '8', '9', 't', 'v', 'q', 'k', 'a'};
score result;
char matrice[13][255];
/*************************************************Fonctions générations main***************************************/
carte  generatecard() {
    carte cartes;
    char figures[]={'H', 'D', 'C', 'S'};
    int nbr1 = rand() % 13;
    int nbr2 = rand() % 4;
    cartes.valeur = values[nbr1];
    cartes.figure = figures[nbr2];
    //printf("carte aleatoire : %c%c\n", cartes.valeur, cartes.figure);         TBF                                        //test de bon fonctionnement
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
void affichermain(mainjoueur tirage, joueur participant) {
    if (participant.numero==0) {
        printf("\n== MAIN DU JOUEUR 1 ==\n");
    }
    else {
        printf("\n== MAIN DU JOUEUR 2 ==\n");
    }
    for (int j = 0; j < 5; j++) {
        printf("%c%c - ", tirage.card[j].valeur, tirage.card[j].figure);                                                     // affichage de la main du joueur
    }
}

void afficheresultat (joueurs *partie, int choix){
    switch (choix){
        case 1:
            printf("\n%s plus fort que %s, joueur 1 gagne !\n", partie->joueur[0].scorejoueur.type, partie->joueur[1].scorejoueur.type );
            break;
        case 2:
            printf("\n%s aussi fort que %s, égalité !\n", partie->joueur[0].scorejoueur.type, partie->joueur[1].scorejoueur.type );
            break;
        case 3:
            printf("\n%s plus fort que %s, joueur 2 gagne !\n", partie->joueur[1].scorejoueur.type, partie->joueur[0].scorejoueur.type );
            break;
    }
}


/*******************************************MATRICE CARTE HAUTE****************************/

void matrice_CH() {

    strcpy(matrice[0],"UN DEUX");
    strcpy(matrice[1],"UN TROIS");
    strcpy(matrice[2],"UN QUATRE");
    strcpy(matrice[3],"UN CINQ");
    strcpy(matrice[4],"UN SIX");
    strcpy(matrice[5],"UN SEPT");
    strcpy(matrice[6],"UN HUIT");
    strcpy(matrice[7],"UN NEUF");
    strcpy(matrice[8],"UN DIX");
    strcpy(matrice[9],"UN VALET");
    strcpy(matrice[10],"UNE DAME");
    strcpy(matrice[11],"UN ROI");
    strcpy(matrice[12],"UN AS");
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
            if (getrang(tirage.card[i]) > getrang(tirage.card[k])) {
                temp1 = tirage.card[k];
                tirage.card[k] = tirage.card[i];
                tirage.card[i] = temp1;
            }
        }
    }
    return tirage;
}

/***************************************************Fonction des figures poker**********************************/
score is_high_card (mainjoueur tirage){
    getrang(tirage.card[4]);
    matrice_CH();
    strcpy(result.type, matrice[forces]);
    result.score=forces;
    return result;
}

score is_pair( mainjoueur tirage) {
    for (int i = 0; i < 4 ; ++i) {
        if (is_same_valeur(&tirage.card[i], &tirage.card[i + 1]) || is_same_valeur(&tirage.card[i+1], &tirage.card[i + 2]) || is_same_valeur(&tirage.card[i+2], &tirage.card[i + 3]) || is_same_valeur(&tirage.card[i+3], &tirage.card[i + 4])){
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
        if (is_same_valeur(&tirage.card[i], &tirage.card[i + 1]) && is_same_valeur(&tirage.card[i+3], &tirage.card[i + 4])) {
            strcpy(result.type, "UNE DOUBLE PAIR");
            result.score = 30;
        }
        else
            break;  }
    return result;
}

score is_three_of_kind(mainjoueur tirage) {
    for (int i = 0; i < 2; ++i) {
        if (tirage.card[i].valeur == tirage.card[i + 1].valeur && tirage.card[i].valeur == tirage.card[i + 2].valeur) {
            strcpy(result.type, "UN BRELAN");
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
    result.score = 0;
    is_double_pair(tri(tirage));
    if (result.score == 30){
        is_three_of_kind(tri(tirage));
        if (result.score == 40) {
            strcpy(result.type, "UN FULL");
            result.score = 70;
        }
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
    result = is_straight_flush(tri(tirage));
    if (result.score==0) {
        result = is_four_of_kind(tri(tirage));
        if (result.score == 0)
            result = is_full(tri(tirage));
                if (result.score == 0) {
                    result = is_flush(tri(tirage));
                    if (result.score == 0) {
                        result = is_straight(tri(tirage));
                        if (result.score == 0) {
                            result = is_three_of_kind(tri(tirage));
                            if (result.score == 0) {
                                result = is_double_pair(tri(tirage));
                                if (result.score == 0) {
                                    result = is_pair(tri(tirage));
                                if (result.score == 0) {
                                    result = is_high_card(tri(tirage));
                            }
                        }
                    }
                }
            }
        }
    }
    //printf("\nresult en sortie de calcul :%i\n", result.score);   TBF
    return result;
}
/*******************************comparaison des scores****************************************/
void comparemains(joueurs partie[2]){
    int choix=0;
    if (partie->joueur[0].scorejoueur.score > partie->joueur[1].scorejoueur.score)
        choix=1;
    if (partie->joueur[0].scorejoueur.score == partie->joueur[1].scorejoueur.score)
        choix=2;
    if (partie->joueur[0].scorejoueur.score < partie->joueur[1].scorejoueur.score)
        choix=3;
    //printf("\nvaleur de la variable choix :%i", choix);   TBF
    afficheresultat(partie, choix);
}


/***************************************************déroulement du jeu*************************************************/
void jeu() {
    int cptr=0;
    joueurs partie[2];
    for (int i = 0; i < 2; ++i) {                          //i est le nombre de participant
        partie->joueur[i]=deroulement(cptr);
        cptr++;
    }
    comparemains(partie);
}


joueur deroulement(int cptr) {
    joueur participant;
    result.score=0;
    strcpy(result.type, " ");
        participant.numero=cptr;
        participant.main=generatemain();
        affichermain(tri(tirage), participant);
        calculresultat(tri(tirage));
        participant.scorejoueur=result;
    return participant;
}
/*****************************************************main()***********************************************************/
int main() {
    unsigned long seed = clock()+time(NULL)+getpid();
    srand(seed);
    jeu();
    return 0;
}