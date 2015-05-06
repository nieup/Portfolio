/**********************************************************
*
*	File : head_Serv.h
*	Author : Cédric HUMBERT & Kilian CONTAMAIN
*
*	Description :
*	Ce fichier contient les code appels des headers du
*   seveur dans le systeme TOMM
*
*   Projet : PSE ISMIN 2A
*
*	Date : 18/ 11/ 2014
*
*************************************************************/


//#include "structures.h"
#define    CMD      "serveur"

#define    NTHREADS       8
#define    MILLISECONDES  1000
#define    ATTENTE        2000*MILLISECONDES
#define    QUEUE_SOCK     10

//#include "login_Serv.h"
//#include "TOMM_Serv.h"

// Variable globale :
Thread *Root_Th; // Acces à la racine de la base de donnée :

/* Fonctions dans le fichier Net_Serv.c */

// Dialogue client mono Utilisateur
void Mono_TOMM(int argc, char *argv[]);

// Gestion des fichiers de dialogue, ecriture, supression...
void Serveur_TOMM(int sock, char *texte);

// Interprete est oriente la reponse du serveur en fontion du message envoyé
void Interpret_Request(Message_TOMM *Mes, Utilisateur *Cur_Us);

// Appelé par une Requete de type See 1 prépare et ecrit le fichier reponse
void See_Cli(Message_TOMM *Mes, char *NomFichier);

// Appelé par une Requete de type Edit 2 prépare et ecrit le fichier reponse
void Edit_Cli(Message_TOMM *Mes);

// Appelé par une Requete de type New 3 prépare et ecrit le fichier reponse
void New_Cli(Message_TOMM *Mes);

// Supprime un post NON IMPLEMENTE renvoi FAIL
void Delete_Cli(Message_TOMM *Mes);

// Souscrire à un Tag NON IMPLEMENTE renvoi FAIL
void Subscribe_Cli(Message_TOMM *Mes);

// Receptionne le fichier qui est envoyé dans "Nomfichier" à partir de la socket. Utilise la structure sFich
void RecevoirFich(int sock , char * Nomfichier);

// Envoi le fichier "Nomfichier" dans la socket. Utilise la structure sFich
void envoyerFichier(int sock,char * Nomfichier);

/* Cest 2 fonctions ne sont pas utilisées dans le programme compilé,
 * J'ai cependant essayer de les faires fonctionner mais le debug c'est
 * avéré compliqué sans CDB ni printf
 */
// Dialogue Client MultiUtilisateur, Probleme de concurence
void Start_up_TOMM(int argc, char *argv[]);

// Gestion de Thread :
void *traiterRequete(void *arg);




