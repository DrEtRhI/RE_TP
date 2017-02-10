/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ComputerFonction.h
 * Author: laura
 *
 * Created on 5 février 2017, 09:40
 */

#ifndef COMPUTERFONCTION_H
#define COMPUTERFONCTION_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct tabRecap {
        int tabEssais[20][8];
        int bienPlace[20];
        int malPlace[20];
    } tabRecap;

    /**
     * Fonction permettant de générer de façon aléatoire la combinaison de couleur
     * à découvrir
     * @param tab tableau dans lequel seront ajoutées les couleurs
     * @param difficulty nombre de couleur à choisir
     */
    void generationGameTableNoRepet(int *tab, int difficulty);
    void generationGameTableRepet(int *tab, int difficulty);
    void evaluationEssai(int *tabComputer, int *tabUser, int *bienPlace, int *malPlace, int difficulte);
    void affichageEssais(tabRecap, int, int);
    void choixCombinaison(int *userChoiceInt, int difficulte);
    void EssaisToBuff(tabRecap, int, int, char*);


#ifdef __cplusplus
}
#endif

#endif /* COMPUTERFONCTION_H */