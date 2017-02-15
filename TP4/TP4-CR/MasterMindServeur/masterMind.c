/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: laura
 *
 * Created on 5 février 2017, 09:30
 */
 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fon.h"
#include "masterMind.h"

#define NB_OCTETS 10000
#define NB_ESSAIS 20
#define TOTALCOLOR 8;

// Generation du tableau de couleur à trouver SANS possibilité de répétition de couleur.

char* tableauCouleur[] = {"bleu", "rouge", "blanc", "noir", "vert", "jaune", "orange", "violet"};

// ajout d'un tableau identique avec espace en plus afin d'afficher en console des cases de taille égale quelquesoit la couleur choisie.
char* tableauCouleurAffichage[] = {"bleu  ", "rouge ", "blanc ", "noir  ", "vert  ", "jaune ", "orange", "violet"};

//char *tampon = (char*) malloc (NB_OCTETS * sizeof(char));
char tampon[10000] = "";

/*
 * Pour la version serveur-client, transformer ce code en une fonction
 * la fonction devra prendre en paramètre le tampon définie dans serveur-client
 */
 
void generationGameTableNoRepet(int *tab, int difficulty) {
    srand(time(NULL));
    int z = 0;
    // allocation de la première case du tableau. 
    int randomColor;
    randomColor = rand() % TOTALCOLOR;
    tab[0] = randomColor;
    for (int i = 1; i < difficulty; i++) {
        randomColor = rand() % TOTALCOLOR;
        tab[i] = randomColor;
        while (z < i) {
            if (tab[i] != tab[z]) {
                z++;
            } else {
                tab[i] = rand() % TOTALCOLOR;
                z = 0;
            }
        }
        z = 0;
    }
}
// Generation du tableau de couleur à trouver AVEC possibilité de répétition de couleur.

void generationGameTableRepet(int *tab, int difficulty) {
    srand(time(NULL));
    for (int i = 0; i < difficulty; i++) {
        int randomColor;
        randomColor = rand() % TOTALCOLOR;
        tab[i] = randomColor;
    }
}


void evaluationEssai(int *tabComputer, int *tabUser, int *bienPlace, int *malPlace, int difficulte) {
    // Copie du tableau-Computer pour remplacer les couleurs traitées par -1 par la suite. Cela évite un double traitement.
    int *copyTabUser;
    int *copyTabComputer;
    copyTabUser = (int*) malloc(difficulte * sizeof (int));
    copyTabComputer = (int*) malloc(difficulte * sizeof (int));
    for (int b = 0; b < difficulte; b++) {
        copyTabComputer[b] = tabComputer[b];
        copyTabUser[b] = tabUser[b];
    }
    // Evalutation en premier des couleurs bien placées.
    // ---> Si la couleur est bien placée, incrémentation de la variable bienPlace et remplacement dans copyTab par -1.
    for (int i = 0; i < difficulte; i++) {
        if (copyTabComputer[i] == copyTabUser[i]) {
            (*bienPlace)++;
            copyTabComputer[i] = -1;
            copyTabUser[i] = -2;
        }
    }
    // Evalutation des couleurs mal placées.
    // --> Si la couleur est mal placée, incrémentation de la variable malPlacee et remplacement dans copyTab par -1.
    for (int i = 0; i < difficulte; i++) {
        for (int z = 0; z < difficulte; z++) {
            if (copyTabComputer[i] == copyTabUser[z]) { // Ici, pas besoin de vérifier i == z car ce cas est traité précédement. (remplacement par -1).
                (*malPlace)++;
                copyTabComputer[i] = -1;
                copyTabUser[z] = -2;
            }
        }
    }
    free(copyTabUser); // Libération du tableau CopyTab.
    free(copyTabComputer);
}

void affichageEssais(tabRecap recap, int difficulte, int essai) {
    for (int i = 0; i <= essai; i++) {
        for (int y = 0; y < difficulte; y++) {
            if (y + 1 == difficulte) {
                printf("|%d|", recap.tabEssais[i][y]);
            } else {
                printf("|%d", recap.tabEssais[i][y]);
            }
        }
        printf("  => Bien placé(s) : %d", recap.bienPlace[i]);
        printf(", Mal placé(s) : %d\n", recap.malPlace[i]);

    }
}
// Vide le buffer et le rempli avec une chaine de caractère contenant toutes les informations de l'essai

void EssaisToBuff(tabRecap recap, int difficulte, int essai, char* tampon) {
    strcpy(tampon, "");
    char* temp = (char*) malloc(sizeof (char)*50);

    for (int i = 0; i <= essai; i++) {
        for (int y = 0; y < difficulte; y++) {
            if (y + 1 == difficulte) {
                //printf("|%d|", recap.tabEssais[i][y]);
                sprintf(temp, "|%s|", tableauCouleurAffichage[recap.tabEssais[i][y]]);
                strcat(tampon, temp);
            } else {
                //printf("|%d", recap.tabEssais[i][y]);
                sprintf(temp, "|%s", tableauCouleurAffichage[recap.tabEssais[i][y]]);
                strcat(tampon, temp); 
            }
        }
        //printf("  => Bien placé(s) : %d", recap.bienPlace[i]);
        sprintf(temp, "  => Bien placé(s) : %d", recap.bienPlace[i]);
        strcat(tampon, temp);
        //printf(", Mal placé(s) : %d\n", recap.malPlace[i]);
        sprintf(temp, ", Mal placé(s) : %d", recap.malPlace[i]);
        strcat(tampon, temp);
        
        sprintf(temp,"    Essai numero : %d\n", i+1);
        strcat(tampon, temp);

    }
    strcat(tampon, "\nPour continuer, entrez n'importe quelle touche et validez\n");
    free(temp);
}

void choixCombinaison(int *userChoiceInt, int difficulte, int idSocket) {
    char choixCouleur[10];
    char* temp = (char*) malloc(sizeof (char)*50);
    int bonneReponse = 1;
    for (int z = 0; z < difficulte; z++) {
        int res = 1;
        int OK = 0;
        while (res != 0) {
            if (bonneReponse){
            strcpy(tampon,"\nChoissez vos couleurs parmis bleu, rouge, blanc, noir, vert, jaune, orange, violet :\n");
            }
            else{
            	strcpy(tampon,"Cette couleur n'est pas une couleur valide.\n\nChoissez vos couleurs parmis bleu, rouge, blanc, noir, vert, jaune, orange, violet :\n");
            }
            bonneReponse = 1;
            sprintf(temp,"Couleur numero %d : ", z + 1);
            strcat(tampon, temp);
            h_writes(idSocket, tampon, NB_OCTETS);
            h_reads(idSocket, tampon, NB_OCTETS);
            strcpy(choixCouleur,tampon);
            for (int i = 0; i < 8; i++) { 
                if ((res = strcmp(choixCouleur, tableauCouleur[i])) == 0) {
                    userChoiceInt[z] = i; 
                    break;
                }
            }
            if (res != 0) bonneReponse = 0; // message pour recommencer la saisie.
        }
    }
    free(temp);
}

// Fonction pour afficher le message de fin... a faire avec le tampon au lieu des printf.
void afficherPartiePerdue(int difficulty, int *computerChoice, char* tampon) {
    strcpy(tampon, "");
    char* temp = (char*) malloc(sizeof (char)*200);
    //printf("Désolé vous avez perdu !!\n");
    //printf("La bonne combinaison était : \n");
    sprintf(temp, "\n\n\nDésolé vous avez perdu !!\nLa bonne combinaison était : \n");
    strcat(tampon, temp);
    for (int i = 0; i < difficulty; i++) {
        if (i + 1 == difficulty) {
            //printf("|%s|", tableauCouleurAffichage[computerChoice[i]]);
            sprintf(temp, "|%s|", tableauCouleurAffichage[computerChoice[i]]);
            strcat(tampon, temp);
        } else {
            //printf("|%s", tableauCouleurAffichage[computerChoice[i]]);
            sprintf(temp, "|%s", tableauCouleurAffichage[computerChoice[i]]);
            strcat(tampon, temp);
        }
    }
    //printf("\n\n");
    sprintf(temp, "\n\n");
    strcat(tampon, temp);
    free(temp);
}

void masterMind(int idSocketAccept) {

    int *userChoiceInt;
    int *computerChoice;
    int difficulty = 0;
    int continuePartie = 1;
    tabRecap tabRecap;
    

    strcpy(tampon, "Bienvenue sur MASTERMIND !!\n\n\n");
    strcat(tampon, "Détailler les règles du jeu :\n\n");
    strcat(tampon, "Le but du MasterMind est de trouver une combinaison secrète de couleurs\n");
    strcat(tampon, "La combinaison secrète est réalisée à partir d'un panel de 8 couleurs :\n");
    strcat(tampon, "bleu, rouge, blanc, noir, vert, jaune, orange, violet\n");
    strcat(tampon, "Le joueur peu choisir une combinaison de 4 à 7 couleurs, tirée parmis les\n");
    strcat(tampon, "huit couleurs prédéfinies\n");
    strcat(tampon, "Le joueur à un maximum de 20 tentatives pour trouver la bonne combinason\n");
    strcat(tampon, "Bonne chance !!!\n\n\n\n");
    
    h_writes(idSocketAccept, tampon, NB_OCTETS);

    while (continuePartie) {

        while (!(difficulty >= 4 && difficulty <= 7)) {
            strcpy(tampon, "Choisissez la difficulté (4 à 7 couleurs) : ");
            h_writes(idSocketAccept, tampon, NB_OCTETS);
            
            h_reads(idSocketAccept, tampon, NB_OCTETS);
            if (strcmp(tampon, "4") == 0){
            	difficulty = 4;
            }else if (strcmp(tampon, "5") == 0){
            	difficulty = 5;
            }else if (strcmp(tampon, "6") == 0){
            	difficulty = 6;
            }else if (strcmp(tampon, "7") == 0){
            	difficulty = 7;
            }
        }
        // initialisation des tableaux utilisateur et ordinateur suivant la difficulté
        // choisie par l'utilisateur
        userChoiceInt = (int*) malloc(difficulty * sizeof (int));
        computerChoice = (int*) malloc(difficulty * sizeof (int));

        // pour la génération de nombre aléatoire
        generationGameTableRepet(computerChoice, difficulty);
    		
        int essai = 0;

        while (essai < NB_ESSAIS) {
            int bienPlace = 0;
            int malPlace = 0;

            choixCombinaison(userChoiceInt, difficulty, idSocketAccept);
            evaluationEssai(computerChoice, userChoiceInt, &bienPlace, &malPlace, difficulty);

            // recopie de l'essai dans le tableau récapitulatif :
            for (int i = 0; i < difficulty; i++) {
                tabRecap.tabEssais[essai][i] = userChoiceInt[i];
            }
            tabRecap.malPlace[essai] = malPlace;
            tabRecap.bienPlace[essai] = bienPlace;
            
            EssaisToBuff(tabRecap, difficulty, essai, tampon);
            h_writes(idSocketAccept, tampon, NB_OCTETS);
            h_reads(idSocketAccept, tampon, NB_OCTETS); // lecture du paquet inutil
            
            essai++;
            if (essai == NB_ESSAIS || bienPlace == difficulty) {
                if (essai == NB_ESSAIS) {
                    afficherPartiePerdue(difficulty, computerChoice, tampon);
                    strcat(tampon, "\nPour continuer, entrez n'importe quelle touche et validez\n");
                    h_writes(idSocketAccept, tampon, NB_OCTETS);
                    char* test = (char*) malloc (sizeof(char) * NB_OCTETS);
                    h_reads(idSocketAccept, test, NB_OCTETS);
                    free(test);
                } else {
                    strcpy(tampon, "\n\n FELICITATION, vous avez trouvé la bonne combinaison\n");
                    essai = NB_ESSAIS;

                }
                strcat(tampon, "\nSouhaitez-vous refaire une partie ?? (Non = 0, Oui = 1)\n");
                h_writes(idSocketAccept, tampon, NB_OCTETS);
                h_reads(idSocketAccept, tampon, NB_OCTETS);
                while((strcmp(tampon, "0") != 0) && (strcmp(tampon, "1") != 0)){
                	strcpy(tampon, "\nSouhaitez-vous refaire une partie ?? (Non = 0, Oui = 1)\n");
                h_writes(idSocketAccept, tampon, NB_OCTETS);
                h_reads(idSocketAccept, tampon, NB_OCTETS);
                }
                //sprintf(newParty, "%s", tampon);
                if (strcmp(tampon, "0") == 0){
             	  	strcpy(tampon, "fin");
               		h_writes(idSocketAccept, tampon, NB_OCTETS);
               		continuePartie = 0;
                }
            }
        }
    }
    
}
