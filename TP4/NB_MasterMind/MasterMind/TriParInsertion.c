/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TriParInsertion.c
 * Author: EtRhI_PC
 *
 * Created on 20 février 2017, 12:02
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {

    int tab[] = {5,8,96,10,100,8,13,25,2,47};
    int tmp, j;
    for (int i = 1; i < 10; i++){
        j = 0;
        while (j < i && tab[j <= tab[i]]){
            j++;
        }
        if (j < i){
            tmp = tab[i];
            for (int k = i; i < j+1; k++){
                tab[k] = tab[k-1];
                tab[j] = tmp;
            }
        }
    }
    
    for (int i = 0; i < 10; i++){
        printf("%d  ", tab[i]);
    }
    
    return (0);
}

