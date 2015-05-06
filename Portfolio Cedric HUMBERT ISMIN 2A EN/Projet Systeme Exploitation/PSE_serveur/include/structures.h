/**********************************************************
*
*	File : structures.h
*	Author : Cédric HUMBERT & Kilian CONTAMAIN
*
*	Description :
*	Ce fichier contient les structures utilisées par
*   seveur du systeme TOMM
*
*   Projet : PSE ISMIN 2A
*
*	Date : 18/ 11/ 2014
*
*************************************************************/



#define TAILLE_NOM 20 // TAille des char court, nom TAILLE_NOM
#define TAILLE_POST 140 // Taille des char long TAILLE_POST
#define TAILLE_MES 200 // TAille des message à transferer : TAILLE_MES
#define TAILLE_PW 8 // Taille des mots de passe en octet
#define TAILLE_TAGS 20 // Nombre de Thread maximal par Tag
#define NOMBRE_TAGS 6 // Nombre total de Tags


// Fichiers Headers de structures :
typedef struct Date{
    int Jour;
    int Mois;
    int Annee;
    int Heure;
    int Minute;
    int Seconde;
}Date;

typedef struct Post{
    int Th_Id; // Identifiant du thread correspondant
    int Num_Pst; // Numero du post
    Date Date_Post; // Date du post, générée automatiquement
    char Auteur[TAILLE_NOM]; // Nom de l'auteur
    int Id_Auteur; // Identifiant de l'auteur
    char Text[TAILLE_POST]; // Contenu du post
    struct Post *next_P; // Element de chainage vers le post suivant
}Post;
// A noter que le passge de pointeur risque d'"être compliqué" par socket TCP entre 2 PC différents !!

typedef struct Tag{
    char Nom[TAILLE_NOM];
    int Related_Th[TAILLE_TAGS];
    struct Tag *next_Ta;
}Tag;

typedef struct Thread{
    int Th_Id; // Identifiant du Thread
    char Nom[TAILLE_NOM]; // Nom du thread
    Date Debut; // Date de Début généré automatiquement
    Date Fin; // date de Fin spécifiée par l'utilisateur
    int nbPost; // Nombre de poste dans ce thread
    Post *F_P; // Premier post contenu ds le Thread
    Post *L_P; // Dernier post contenu ds le Thread
    struct Thread *next_Th; // Element de chainage vers le Thread suivant
}Thread;


/*Structures d'envoi : */
typedef struct Message_TOMM{ // Idéalement c'est ce que l'on transmet par Internet mais bon si faut tout passer on passera tout
    char mes[TAILLE_MES]; // texte du message
    int descript; // descripteur du type de message
    int Nb_Th; // Numero du Thread concerné
    int ChkSum; // non implémenté
}Message_TOMM;


typedef struct
{
    char Buffer[TAILLE_MES];
    int finFich;
	int tfich;
}sFich;



typedef struct Utilisateur{ // Tous ces Utilisateurs sont Sauvegarder ds un fichier sur le  Serveur, encrypter ?
    int ID_Ut; // Identifiant de l'utilisateur
    char Nom_Ut[TAILLE_NOM]; // Nom de l'utilisateur tel qu'il apparait dans les post
    char PwU[TAILLE_PW]; // Mot de passe !!! Ce serait bien de ne pas l'afficher à la saisie
    int Related_Ta[NOMBRE_TAGS]; // Y sont inscrits les Tags auxquel l'utilisateur a souscrit
    int droit; // droit = 0 pour un client normal et droit = 1 pour un administrateur
}Utilisateur;


/* Structure d en-tete */
typedef struct En_tete{
	int nb_usr;												// Nombre d utilisateurs deja enregistres
	Date L_Modify;										// Date de derniere modification (struct tm est une structure de <time.h>)
} En_tete;





