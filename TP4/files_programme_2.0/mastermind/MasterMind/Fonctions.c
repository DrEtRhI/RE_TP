/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Constante.h"

#define TOTALCOLOR 8;

void GenerationGameTableNoRepet(int *tab, int difficulty) {
    srand(time(NULL));
    int z = 0;
    // allocation de la première case du tableau. 
    int randomColor;
    randomColor = rand() % TOTALCOLOR;
    tab[0] = randomColor;
    for (int i = 1; i < difficulty; i++){
        randomColor = rand() % difficulty;
        tab[i] = randomColor;
        while (z < i){
            if (tab[i] != tab[z]){
                z++;
            }else{
                tab[i] = rand() % difficulty;
                z = 0;
            }
        }
        z = 0;
    }
}

void GenerationGameTableRepet(int *tab, int difficulty) {
    srand(time(NULL));
    for (int i = 0; i < difficulty; i++) {
        int randomColor;
        randomColor = rand() % difficulty;
        tab[i] = randomColor;
    }
}

void EvaluationEssai(int *tabComputer, int *tabUser, int *bienPlace, int *malPlace, int difficulte){
    for (int i = 0; i < difficulte; i++){
        for (int z = 0; z < difficulte; z++){
            if (tabComputer[i] == tabUser[z] && i == z){
                *bienPlace = *bienPlace + 1;
            }else if (tabComputer[i] == tabUser[z] && i != z){
                *malPlace = *malPlace + 1;
            }
        }
    }
}

void AffichageEssai(int *userTab, int bienPlace, int malPlace, int difficulte){
    for (int i = 0; i < difficulte; i++){
        if (i + 1 == difficulte){
            printf("|%d|", userTab[i]);
        }else{
            printf("|%d", userTab[i]);
        }
    }
    printf("  => Bien placé(s) : %d", bienPlace);
    printf(", Mal placé(s) : %d\n", malPlace);
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