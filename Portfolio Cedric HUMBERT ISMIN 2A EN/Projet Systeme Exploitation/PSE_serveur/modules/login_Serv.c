/**********************************************************
*
*	File : login_Serv.c
*	Author : Cédric HUMBERT & Kilian CONTAMAIN
*
*	Description :
*   Ce fichier contient les fonctions relatives au
*   login des clients de TOMM
*
*   Projet : PSE ISMIN 2A
*
*	Date : 18/ 11/ 2014
*
*************************************************************/
#include "../include/pse.h"


/* Donnees partagees par les differents threads */
int comptes, pos, nbecrits, nblus;
time_t now;
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;



void Encrire_En_Tete_Comptes(En_tete *Cur_Te){
    //Cur_Te->L_Modify = *Obtenir_Date();
    pos = lseek(comptes, 0, SEEK_SET);
    if (pos == -1){erreur_IO("lseek");}
    nbecrits = write(comptes, Cur_Te, sizeof(En_tete));
    if(nbecrits != sizeof(En_tete)){erreur_IO("write");}
    //printf("En-tete cree\n");
}


void Create_Comptes(Utilisateur *New_Us){

    int mode, i;
    char NomFifCom[TAILLE_NOM] = "comptes.log";
    En_tete *Com_Head;
    mode =  O_RDWR;
    // comptes est une varible globale
    Com_Head = malloc(sizeof(En_tete));
    comptes = open(NomFifCom, mode, S_IRWXU);

    if (comptes == -1){erreur_IO("open comptes");}

	//printf("Ouverture de comptes.log\n");
    	/* Lecture de l en-tete */
	pos = lseek(comptes, 0, SEEK_SET);
	if (pos == -1){erreur_IO("lseek");}
	nblus = read(comptes, Com_Head, sizeof(En_tete));
	if(nblus != sizeof(En_tete)){
		if(nblus == 0){Com_Head->nb_usr = 0;}
		else{erreur_IO("read");}
	}
    New_Us->ID_Ut = Com_Head->nb_usr + 1;
    (Com_Head->nb_usr)++;
	/* Verrouillage mutex*/
	if(pthread_mutex_lock(&verrou) != 0){
		erreur("mutex_lock");
		return;}
	//printf("Verrouillage\n");


      //Cur_Te->L_Modify = *Obtenir_Date();
    pos = lseek(comptes, 0, SEEK_SET);
    if (pos == -1){erreur_IO("lseek");}
    nbecrits = write(comptes, Com_Head, sizeof(En_tete));
    if(nbecrits != sizeof(En_tete)){erreur_IO("write");}
    //printf("En-tete Mise à Jour \n");
    pos = lseek(comptes, sizeof(En_tete)+Com_Head->nb_usr*sizeof(Utilisateur), SEEK_SET);
    if (pos == -1){erreur_IO("lseek");}
    nbecrits = write(comptes, New_Us, sizeof(Utilisateur));
    if(nbecrits != sizeof(Utilisateur)){erreur_IO("write");}
    //printf("Nouvel Utilisateur %s Validé \n", New_Us->Nom_Ut);


	/* Deverrouillage mutex*/
	if(pthread_mutex_unlock(&verrou) != 0){
		erreur("mutex_unlock");
		return;}
	//printf("Deverrouillage\n");

    close(comptes);
	//printf("Nombre d'utilisateurs : %d\n", Com_Head->nb_usr);

}


int Validate_User(Utilisateur *New_Us){
    int mode, k;
    char NomFifCom[TAILLE_NOM] = "comptes.log";
    Utilisateur *Cur_Us;
    En_tete *Com_Head;
    mode = O_RDWR;
    Cur_Us = malloc(sizeof(Utilisateur));
    // comptes est une varible globale
    comptes = open(NomFifCom, mode, S_IRWXU);
    Com_Head = malloc(sizeof(En_tete));

    if (comptes == -1){erreur_IO("open comptes");}

	/* Lecture de l en-tete */
	pos = lseek(comptes, 0, SEEK_SET);
	if (pos == -1){erreur_IO("lseek");}
	nblus = read(comptes, Com_Head, sizeof(En_tete));
	if(nblus != sizeof(En_tete)){erreur_IO("read");}
	//printf("Nombre de comptes : %d \n", Com_Head->nb_usr);
	for(k = 0 ; k < Com_Head->nb_usr ; k++){
        pos = lseek(comptes, sizeof(En_tete) + k * sizeof(Utilisateur), SEEK_SET);
        if (pos == -1){erreur_IO("lseek");}
        nblus = read(comptes, Cur_Us, sizeof(Utilisateur));
        //printf("Compare : _%s_ VS. _%s_ \n", New_Us->Nom_Ut, Cur_Us->Nom_Ut);
        //printf("Compare : _%s_ VS._%s_ \n", New_Us->PwU, Cur_Us->PwU);
        if(nblus != sizeof(Utilisateur)){erreur_IO("read");}
        if(strcmp(Cur_Us->Nom_Ut, New_Us->Nom_Ut) == 0 && strcmp(Cur_Us->PwU, New_Us->PwU) == 0){
            pos = lseek(comptes, sizeof(En_tete) + k * sizeof(Utilisateur), SEEK_SET);
            if (pos == -1){erreur_IO("lseek");}
            nblus = read(comptes, New_Us, sizeof(Utilisateur));
            if(nblus != sizeof(Utilisateur)){erreur_IO("read");}
            return VRAI;
        }

    }
    // FAUX : utilisateur non authetifié
    return FAUX;
}



