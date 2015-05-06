/**********************************************************
*
*	File : TOMM_Cli.h
*	Author : Cédric HUMBERT & Kilian CONTAMAIN
*
*	Description :
*   Ce fichier contient les prototypes des fonctions relatives à
*   l'éxectution de TOMM
*
*   Projet : PSE ISMIN 2A
*
*	Date : 18/ 11/ 2014
*
*************************************************************/

#define CMD   "client"

/* Fonctions contenues dans le fichier TOMM_Cli.c */

// Interface de commande avec l'utilisateur entre dans le message les spécifications de la commande
Message_TOMM *Interpret_Cli();

// Charge le contenu du fichier dans un message
void read_Message_TOMM(Message_TOMM *Mes_Lu, char *Nomfichier);

// Charge le contenu du message dans le fichier
void write_Message_TOMM(Message_TOMM *Mes_Ec, char *Nomfichier);

// Renvoi la date actuelle
Date *Obtenir_Date();

// Fonction d'affiche de la date
void Affiche_Date(Date *Cur_Date);

// Genere un nouvel utilisateur
Utilisateur *New_Utilisateur(char *Nom, char *Pw);

// Affiche un utilisateur
void Affiche_Utilisateur(Utilisateur *Cur_Us);

// Cree un nouveau Thread
Thread *New_Thread(Date *End_Date, char *Titre);

// Affiche Un thread
void Affiche_Thread(Thread *Cur_Th);

// Affiche tous les posts contenus dans un Thread
void Affiche_Th_Po(Thread *Cur_Th);

// Affiche tous les Threads qui suivent celui passé en argument
void Affiche_Al_Th(Thread *Root_Th);

// Ajoute un Thread à la suite
void Ajout_Thread(Thread *New_Th, Thread *Root_Th);

// Renvoi un Thread à partir de son nom
Thread *Rech_Thread(Thread *Root, char *txt);

// Renvoi le thread correspondant au Tag passé en argument
Thread *Match_Th_Ta(int i, Thread *Root_Th, Tag *Root_Ta);

// Fonction serveur remplit le nouveau un nouveau post, Necessite l'appel à Ajout_Post par la suite
Post *Remplir_Post(char *txt, Utilisateur *User, Thread *Cur_Th);

// Affiche le post
void Affiche_Post(Post *Cur_Po);

//Ajoute un post dans le thread Correspondant
void Ajout_Post(Post *New_Post, Thread *Cur_Thread);

//Ajoute un post dans le thread Correspondant sans mettre à jour le nombre de post qui est déjà remplit.
void Ajout_Post_BDD(Post *New_Post, Thread *Cur_Thread);

// Genere les Tags :
Tag *Generate_Tags();

// Ajoute des tags aux Utilisateurs en inscrivant l'identifiant du Thread dans leur description
void Souscrire_Th(Utilisateur *Cur_User, Tag *Root_Ta, char Tab_Sub[NOMBRE_TAGS][TAILLE_NOM]);

// Affichage du menu d'aide
void Help_Menu();

// Renvoi l'utilisateur que se trouve dans le Message
Utilisateur *Get_User(Message_TOMM *Mes);

// Genere un message pour le success de la requette
void Write_Success(Message_TOMM *Mes);

// Genere un message pour le non success de la requette
void Write_Fail(Message_TOMM *Mes);

// Lit le reste du fichier qui a ete envoyé pour la commande see
void Lire_See(FILE *new_File, Message_TOMM *Mes_Lu);

// Traite la reception des réponses, supprime le fichier de réponse.
void Traitement_Answer(char *Nomfichier);

// Supprime le fichier passé en argument
void rm_File(char *NonFichier);


