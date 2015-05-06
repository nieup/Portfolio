/**********************************************************
*
*	File : head_Cli.h
*	Author : Cédric HUMBERT & Kilian CONTAMAIN
*
*	Description :
*	Ce fichier contient les code appels des headers du
*   client dans le systeme TOMM
*
*   Projet : PSE ISMIN 2A
*
*	Date : 18/ 11/ 2014
*
*************************************************************/


#define CMD   "client"

/* Fonctions de Net_Cli1.c : */

// Crée la socket à travers laquelle passe les fichiers
int Create_Sock();

// Connecte avec le serveur, par défault sur le localhost 20000
void Connection_TOMM(int sock, int argc, char *argv[]);

// A partir de la reponse du Serveur genere les parametres de l'utilisateur en Courant
void Authentification_Locale(Message_TOMM *Mes, Utilisateur *Cur_User);

// Genere le fichier "log" qui permet une authentification automatique sans tapper son Identifiant ou mot de passe
void Write_Auto_Log(Utilisateur *Cur_User);

// Utilise le fichier "log" présent dans le repertoire pour authentifier le client
Utilisateur *Auto_Log();

// Receptionne le fichier qui est envoyé dans "Nomfichier" à partir de la socket. Utilise la structure sFich
void RecevoirFich(int sock , char * Nomfichier);

// Envoi le fichier "Nomfichier" dans la socket. Utilise la structure sFich
void envoyerFichier(int sock,char * Nomfichier);

