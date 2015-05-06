/**********************************************************
*
*	File : client1_main.c
*	Author : Cédric HUMBERT & Kilian CONTAMAIN
*
*	Description :
*	Ce fichier contient le code du programe principal coté
*   Client du systeme TOMM
*
*   Projet : PSE ISMIN 2A
*
*	Date : 19/ 11/ 2014
*
*************************************************************/

#include "../include/pse.h"


int main(int argc, char *argv[]){

    // Déclaration des variables :
    int sock, arret = VRAI;
    char init_EN[TAILLE_NOM], init_REC[TAILLE_NOM];
    Utilisateur *Cur_User = NULL;
    //Cur_User = (Utilisateur *) malloc(sizeof(Utilisateur));
    Message_TOMM *Mes; // Outils pour decrire les fichiers envoyés

    // Initialisation :
    //MesL = malloc(sizeof(Message_TOMM));
    strcpy(init_EN, "ENVOI");
    strcpy(init_REC, "RECPT");

    // création de la socket
    sock = Create_Sock(argc, argv);

    // Connection au serveur
    Connection_TOMM(sock, argc, argv);

    while(arret){
        // Authetification :
        Mes = Interpret_Cli();

        // Demande au Seveur :
        ecrireLigne(sock, init_EN); // On se place en Envoi
        write_Message_TOMM(Mes, "Temp/echange"); // Ecrit le message dans le fichier
        envoyerFichier(sock, "Temp/echange"); // Envoi le fichier au serveur
        rm_File("Temp/echange");

        // Confirmation Je sais pas si il faudra encore ecrire une ligne pour qu'il nous envoi sa reponse
        RecevoirFich(sock, "Temp/conf"); // Reception de l'authetifiction
        read_Message_TOMM(Mes, "Temp/conf"); // Lecture du fichier recut


        // Renvoi l'utilisateur qui a été envoyé par le serveur
        //if (Mes->)
        Authentification_Locale(Mes, Cur_User);
        //Affiche_Utilisateur(Cur_User);

        while(!(Mes->descript == 7) /*&& !(Mes->descript == 15)*/){ // Test Authentification reussi si MesL != 15
            Mes = Interpret_Cli();
            printf("Mes->descript = %d\n", Mes->descript);
            if (Mes->descript != 7){

                // Envoi de Requete
                write_Message_TOMM(Mes, "Temp/Requete"); // Ecriture du fichier correspondant au Message
                ecrireLigne(sock, init_EN); // On se place en Envoi
                envoyerFichier(sock, "Temp/Requete"); // Envoi le fichier au serveur
                rm_File("Temp/Requete");

                // Reception
                RecevoirFich(sock, "Temp/Answer"); // Recoit le fichier envoyé par le serveur
                Traitement_Answer("Temp/Answer"); // Traitement Affichage et rm fichier
            }
        }
        if(Mes->descript == 7){ // Cas de fin
            printf("Commande End demandee\n");
            printf("Le client TOMM va s'arreter...\n");
            arret = FAUX;}
        if(Mes->descript == 15){ // Cas d'erreur authetification
            printf("Vous n'etes pas authentifié \n");
        }
    }


  if (close(sock) == -1) {erreur_IO("close canal");}
  exit(EXIT_SUCCESS);
}
