/**********************************************************
*
*	File : TOMM_Serv.h
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



/* Fonctions contenues dans le fichier TOMM_Serv.c */

//La fonction lit le message qui est dans le fichier rentré en paramètre.
void read_Message_TOMM(Message_TOMM *Mes_Lu, char *Nomfichier);

//créer un fichier échange.txt puis écrit le message dans le fichier
void write_Message_TOMM(Message_TOMM *Mes_Ec,char *Nomfichier);

//On créer un fichier nommée en fonction du nom de l'utilisateur pour ensuite écrire tous le thread avec tous les postes dans le fichier.
void Ecrire_Thread_Envoi(Thread *Cur_Th, Utilisateur *Cur_User);

//La fonction consiste à lire un thread reçu dans un fichier qui dépend du nom de l’utilisateur.
Thread *Lire_Thread_Reception(Utilisateur *Cur_User);

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

//La fonction rajoute le thread en entrée à la suite de la liste chainée.
void Ajout_Thread_BDD(Thread *New_Th, Thread *Root_Th);

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

//La fonction permet d’enregistrer les threads et les postes correspondant dans un fichier.
void Save_Data(Thread *Root_Th);

//La fonction permet de lire les threads du fichier.
Thread *Lire_Thread_BDD(Thread *Cur_Th);

//La fonction permet de récuperer tous les thread du fichier après les avoir lu avec la fonction Lire_Thread_BDD.
void Lire_BDD(Thread *Root_Th);

//Permet de générer une base de données dès le lancement.
void Generate_Data(Thread *Root_Th);

//	Renvoi l'utilisateur que se trouve dans le Message.
Utilisateur *Get_User(Message_TOMM *Mes);

//	Cette fonction permet de récupérer les paramètres.
void Get_Param(Message_TOMM *Mes, char *arg1, char *arg2);

//	Cette fonction récupère le poste selon le contenu du message et de l’utilisateur.
Post *Get_Post(Message_TOMM *Mes, Utilisateur *Cur_Us);

// Genere un message pour le success de la requette
void Write_Success(Message_TOMM *Mes);

// Genere un message pour le non success de la requette
void Write_Fail(Message_TOMM *Mes);

// Supprime le fichier passé en argument
void rm_File(char *NonFichier);

