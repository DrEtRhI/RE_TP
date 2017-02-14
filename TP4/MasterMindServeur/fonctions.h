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

    /**
     * Définition d'une structure permettant de stocker les essais réalisés
     * tabEssais : tableau contenant les combinaisons déjà jouées par le joueur
     * bienPlace : tableau contenant le nombre de couleurs bien placées pour chaque essai
     * malPlace : tableau contenant le nombre de couleurs mal placées pour chaque essai
     */
    typedef struct tabRecap {
        int tabEssais[20][8];
        int bienPlace[20];
        int malPlace[20];
    } tabRecap;

    /**
     * Fonction permettant de générer de façon aléatoire la combinaison de couleur
     * à découvrir sans répétition de couleur dans la combinaison
     * @param tab tableau dans lequel seront ajoutées les couleurs
     * @param difficulty nombre de couleurs à deviner
     */
    void generationGameTableNoRepet(int *tab, int difficulty);
    
    /**
     * Fonction permettant de générer de façon aléatoire la combinaison de couleur
     * à découvrir avec répétition de couleur possible
     * @param tab tableau dans lequel seront ajoutées les couleurs
     * @param difficulty nombre de couleurs à deviner
     */
    void generationGameTableRepet(int *tab, int difficulty);
    
    /**
     * Fonction permettant d'évaluer l'essai du joueur vis à vis de la combinaison cachée
     * @param tabComputer : tableau contenant la combinaison cachée
     * @param tabUser : tableua contenant l'essai du joueur
     * @param bienPlace : entier représentant les couleurs bien placées
     * @param malPlace : entier représentant les couleurs mal placées
     * @param difficulte : entier représentant le nombre de couleurs choisies 
     * par le joueur en début de partie
     */
    void evaluationEssai(int *tabComputer, int *tabUser, int *bienPlace, int *malPlace, int difficulte);
    
    /**
     * Fonction permettant de stocker l'essai du joueur dans un tableau. De plus la fonction
     * permet de vérifier que la couleur entrée par l'utilisateur est correcte et fait
     * correspondre la couleur à l'entier correspondant pour la fonction evalutationEssai()
     * @param userChoiceInt : tableau contenant l'essai de joueur convertie en entier
     * @param difficulte : entier représentant le nombre de couleurs choisies
     * par le joueur en début de partie
     */    
    void choixCombinaison(int *userChoiceInt, int difficulte);
    
    /**
     * La fonction permet d'afficher l'essai en cours et l'historique des essais
     * précédents dans le tampon.
     * @param recap : structure contenant l'historique des essais précédents
     * @param difficulte : entier représentant le nombre de couleurs choisies
     * par le joueur en début de partie
     * @param essai : entier représentant l'essai en cours
     * @param tampon : tableau de caractères contenant les informations de l'essais 
     * en cours et des précédents
     */
    void EssaisToBuff(tabRecap recap, int difficulte, int essai, char* tampon);
    
    /**
     * Fonction affichant le résultat d'une partie perdue dans le tampon
     * @param difficulty : entier représentant le nombre de couleurs choisies
     * par le joueur en début de partie
     * @param computerChoice : tableau contenant la combinaisoin cachée
     * @param tampon : tableau contenant la chaine de caractère du message de défaite
     */
    void afficherPartiePerdue(int difficulty, int *computerChoice, char* tampon);
