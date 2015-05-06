/**********************************************************
*
*	File : serveur_main.c
*	Author : Cédric HUMBERT & Kilian CONTAMAIN
*
*	Description :
*	Ce fichier contient le code du programe principal coté
*   seveur du systeme TOMM
*
*   Projet : PSE ISMIN 2A
*
*	Date : 18/ 11/ 2014
*
*************************************************************/


#include "../include/pse.h"

int main(int argc, char *argv[]) {

    /// Generer des threads, demonstration et sauvegarde :
    // Initialisation de la racine :
    Root_Th = New_Thread(Obtenir_Date(),"ROOT_Thread");
    // Lecture des données
    Lire_BDD(Root_Th);

    ///Affichage des données
    //Affiche_Al_Th(Root_Th);

    //Lancement du serveur et management :
    // Multithread :
    //Start_up_TOMM(argc, argv); // Malheureusement il y a une erreur que je n'arrive pas à réparer dans cette fonction la
    // Mono user : Fonctionne
    Mono_TOMM(argc, argv);

    // Enregistrement des données :
    Save_Data(Root_Th);
    printf("La base de donnée a été sauvegardée\n");

    exit(EXIT_SUCCESS);
}

