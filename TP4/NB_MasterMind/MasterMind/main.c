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

#include <stdio.h>
#include <stdlib.h>
#include "Fonctions.h"
#define NB_OCTETS 1000
#define NB_ESSAIS 20

/*
 * 
 */
int main(int argc, char** argv) {

    typedef enum {
        BLEU, ROUGE, BLANC, NOIR, VERT, JAUNE, ORANGE, VIOLET
    } Color;
    int *userChoiceInt;
    int *computerChoice;
    int difficulty = 0;
    int newParty = 0;
    tabRecap tabRecap;
    char *tampon = (char*) malloc (NB_OCTETS * sizeof(char));
    

    printf("Bienvenue sur MASTERMIND !!\n\n\n");
    printf("Détailler les règles du jeu :\n\n");
    printf("Le but du MasterMind est de trouver une combinaison secrète de couleurs\n");
    printf("La combinaison secrète est réalisée à partir d'un panel de 8 couleurs :\n");
    printf("bleu, rouge, blanc, noir, vert, jaune, orange, violet\n");
    printf("Le joueur peu choisir une combinaison de 4 à 7 couleurs, tirée parmis les\n");
    printf("huit couleurs prédéfinies\n");
    printf("Le joueur à un maximum de 20 tentatives pour trouver la bonne combinason\n");
    printf("Bonne chance !!!\n\n\n\n");

    while (newParty == 0) {

        while (!(difficulty >= 4 && difficulty <= 7)) {
            printf("Choisissez la difficulté (4 à 7 couleurs) : ");
            scanf("%d", &difficulty);
        }
        // initialisation des tableaux utilisateur et ordinateur suivant la difficulté
        // choisie par l'utilisateur
        userChoiceInt = (int*) malloc(difficulty * sizeof (int));
        computerChoice = (int*) malloc(difficulty * sizeof (int));

        // pour la génération de nombre aléatoire
        generationGameTableRepet(computerChoice, difficulty);

        // ********** Pour le TEST, affichage du computerTab au début de la partie. **********
        for (int i = 0; i < difficulty; i++) {
            if (i + 1 == difficulty) {
                printf("|%d|\n", computerChoice[i]);
            } else {
                printf("|%d", computerChoice[i]);
            }
        }

        printf("\n\nVous avez %d essai maximum pour trouver la bonne combinaison\n", NB_ESSAIS);

        int essai = 0;

        while (essai < NB_ESSAIS) {
            int bienPlace = 0;
            int malPlace = 0;

/*
            printf("Choissez vos couleurs parmis bleu, rouge, blanc, noir, vert, jaune, orange, violet :\n");

            for (int i = 0; i < difficulty; i++) {
                printf("Entrez la couleur %d : ", i + 1);
                scanf("%d", &userChoiceInt[i]);
            }
*/
            choixCombinaison(userChoiceInt, difficulty);
            evaluationEssai(computerChoice, userChoiceInt, &bienPlace, &malPlace, difficulty);

            // recopie de l'essai dans le tableau récapitulatif :
            for (int i = 0; i < difficulty; i++) {
                tabRecap.tabEssais[essai][i] = userChoiceInt[i];
            }
            tabRecap.malPlace[essai] = malPlace;
            tabRecap.bienPlace[essai] = bienPlace;
            
            EssaisToBuff(tabRecap, difficulty, essai, tampon);
            printf("%s", tampon); // Cette fonction sera remplacée par un write dans la version reseau.
            
            essai++;
            if (essai == NB_ESSAIS || bienPlace == difficulty) {
                if (essai == NB_ESSAIS) {
                    afficherPartiePerdue(difficulty, computerChoice);
                } else {
                    printf("\n\n FELICITATION, vous avez trouvé la bonne combinaison\n");
                    essai = NB_ESSAIS;

                }
                printf("Souhaitez-vous refaire une partie ?? (Non = 1, Oui = 0)\n");
                scanf("%d", &newParty);
            }
        }
        free(computerChoice); // Pas sur que ce soit obligatoire...
        free(userChoiceInt);
    }
    return (EXIT_SUCCESS);
}
