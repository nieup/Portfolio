/**********************************************************
*
*	File : login_Serv.h
*	Author : Cédric HUMBERT & Kilian CONTAMAIN
*
*	Description :
*   Ce fichier contient les headers des fonctions relatives au
*   login des clients de TOMM
*
*   Projet : PSE ISMIN 2A
*
*	Date : 18/ 11/ 2014
*
*************************************************************/

/* Fonctions de login_Serv.c : */

// Ecrit l'entete en haut de comptes.log
void Encrire_En_Tete_Comptes(En_tete *Cur_Te);

// Crée un compte dans comptes.log
void Create_Comptes(Utilisateur *New_Us);

// Test la présence d'un utilisateur dans le fichier comptes.log 1 si VRAI 0 si FAUX
int Validate_User(Utilisateur *New_Us);


