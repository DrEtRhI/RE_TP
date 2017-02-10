/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Fonctions.h"

#define TOTALCOLOR 8;

// Generation du tableau de couleur à trouver SANS possibilité de répétition de couleur.

char* tableauCouleur[] = {"bleu", "rouge", "blanc", "noir", "vert", "jaune", "orange", "violet"};

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

int verifierSaisie() {

}

void evaluationEssai(int *tabComputer, int *tabUser, int *bienPlace, int *malPlace, int difficulte) {
    // Copie du tableau-Computer pour remplacer les couleurs traitées par -1 par la suite. Cela évite un double traitement.
    int *copyTab;
    copyTab = (int*) malloc(difficulte * sizeof (int));
    for (int b = 0; b < difficulte; b++) {
        copyTab[b] = tabComputer[b];
    }
    // Evalutation en premier des couleurs bien placées.
    // ---> Si la couleur est bien placée, incrémentation de la variable bienPlace et remplacement dans copyTab par -1.
    for (int i = 0; i < difficulte; i++) {
        if (copyTab[i] == tabUser[i]) {
            (*bienPlace)++;
            copyTab[i] = -1;
        }
    }
    // Evalutation des couleurs mal placées.
    // ---> Si la couleur est mal placée, incrémentation de la variable malPlacee et remplacement dans copyTab par -1.
    for (int i = 0; i < difficulte; i++) {
        for (int z = 0; z < difficulte; z++) {
            if (copyTab[i] == tabUser[z]) { // Ici, pas besoin de vérifier i == z car ce cas est traité précédement. (remplacement par -1).
                (*malPlace)++;
                copyTab[i] = -1;
            }
        }
    }
    free(copyTab); // Libération du tableau CopyTab.
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
    char* temp = (char*) malloc (sizeof(char)*50);
    
    for (int i = 0; i <= essai; i++) {
        for (int y = 0; y < difficulte; y++) {
            if (y + 1 == difficulte) {
                //printf("|%d|", recap.tabEssais[i][y]);
                sprintf(temp, "|%d|", recap.tabEssais[i][y]);
                strcat(tampon, temp);
            } else {
                //printf("|%d", recap.tabEssais[i][y]);
                sprintf(temp, "|%d", recap.tabEssais[i][y]);
                strcat(tampon, temp); // BUG ICI
            }
        }
        //printf("  => Bien placé(s) : %d", recap.bienPlace[i]);
        sprintf(temp, "  => Bien placé(s) : %d", recap.bienPlace[i]);
        strcat(tampon, temp);
        //printf(", Mal placé(s) : %d\n", recap.malPlace[i]);
        sprintf(temp, ", Mal placé(s) : %d\n", recap.malPlace[i]);
        strcat(tampon, temp);

    }
    free(temp);
}

void choixCombinaison(int *userChoiceInt, int difficulte) {
    char choixCouleur[10];
    for (int z = 0; z < difficulte; z++) {
        int res = 1;
        int OK = 0;
        while (res != 0) {
            printf("Choissez vos couleurs parmis bleu, rouge, blanc, noir, vert, jaune, orange, violet :\n");
            scanf("%s", choixCouleur);
            for (int i = 0; i < strlen(*tableauCouleur); i++) {
                if ((res = strcmp(choixCouleur, tableauCouleur[i])) == 0) {
                    userChoiceInt[z] = res;
                    break;
                }
            }
        }
    }
}

/*
void ConvertionTableUser(char *userTableColor, int *userTableInt, int difficulte){
    char bleu[8], rouge[8], blanc[8], noir[8], vert[8], jaune[8], orange[8], violet[8];
    strcpy(bleu, "bleu");
    strcpy(rouge,"rouge");
    strcpy(blanc,"blanc");
    strcpy(noir,"noir");
    strcpy(vert,"vert");
    strcpy(jaune,"jaune");
    strcpy(orange,"orange");
    strcpy(violet,"violet");
    for (int i = 0; i < difficulte; i++){
        if(strcmp(bleu, userTableColor[i]) == 0){
            userTableInt[i] = 0;
        }else if (strcmp(rouge, userTableColor[i]) == 0){
            userTableInt[i] = 1;
        }else if (strcmp(blanc, userTableColor[i]) == 0){
            userTableInt[i] = 2;
        }else if (strcmp(noir, userTableColor[i]) == 0){
            userTableInt[i] = 3;
        }else if (strcmp(vert, userTableColor[i]) == 0){
            userTableInt[i] = 4;
        }else if (strcmp(jaune, userTableColor[i]) == 0){
            userTableInt[i] = 5;
        }else if (strcmp(orange, userTableColor[i]) == 0){
            userTableInt[i] = 6;
        }else if (strcmp(violet, userTableColor[i]) == 0){
            userTableInt[i] = 7;
        }
    }
}*/
