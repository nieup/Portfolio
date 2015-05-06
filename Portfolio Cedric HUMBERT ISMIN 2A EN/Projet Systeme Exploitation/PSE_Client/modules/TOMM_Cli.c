/**********************************************************
*
*	File : TOMM_Cli.c
*	Author : Cédric HUMBERT & Kilian CONTAMAIN
*
*	Description :
*   Ce fichier contient les fonctions relatives à
*   l'éxectution de TOMM
*
*   Projet : PSE ISMIN 2A
*
*	Date : 18/ 11/ 2014
*
*************************************************************/
#include "../include/pse.h"



void read_Message_TOMM(Message_TOMM *Mes_Lu, char *Nomfichier){

    char ComRM_Fichier[TAILLE_NOM];
    FILE* new_File = NULL;
    new_File = fopen(Nomfichier, "r");
    //printf("Debut Lire Message \n");
    if (new_File != NULL)
    {
        fseek(new_File, 0, SEEK_SET);
        fread(Mes_Lu, sizeof(Message_TOMM), 1, new_File);
        fclose(new_File);
        strcpy(ComRM_Fichier, "rm ");
        strcat(ComRM_Fichier, Nomfichier);
        system(ComRM_Fichier);
        //printf("FIN Lire Message, fichier supprime \n");
    }
    else {printf("Error Opening File \n");}
}

void write_Message_TOMM(Message_TOMM *Mes_Ec, char *Nomfichier){

    FILE* new_File = NULL;
    new_File = fopen(Nomfichier, "w");
    //printf("DEBUT Ecrire Message \n");
    if (new_File != NULL)
    {
    // FAIRE UNE GESTION DES ERREURS
        fseek(new_File, 0, SEEK_SET);
        fwrite(Mes_Ec, sizeof(Message_TOMM), 1, new_File);
        fclose(new_File);
        //printf("FIN Ecrire Message \n");
    }
    else {printf("Error Opening File \n");}
}

void Ecrire_Thread_Envoi(Thread *Cur_Th, Utilisateur *Cur_User){
    Post *Cur_Po;
    char file_name[TAILLE_NOM];
    // Fichier a envoyer :  "Nom_Ut_answer"
    strcat(file_name, Cur_User->Nom_Ut);
    strcat(file_name, "_answer");
    // Fichier :
    FILE* new_File = NULL;
    new_File = fopen(file_name, "ab");

    if (new_File != NULL)
    {
    // FAIRE UNE GESTION DES ERREURS
        fseek(new_File, 0, SEEK_END);
        fwrite(Cur_Th, sizeof(Thread), 1, new_File);
        for (Cur_Po = Cur_Th->F_P ; Cur_Po != NULL ; Cur_Po = Cur_Po->next_P){
            fwrite(Cur_Po, sizeof(Post), 1, new_File);
        }
        fclose(new_File);
    }
    else {printf("Error Opening File \n");}
}

Thread *Lire_Thread_Reception(Utilisateur *Cur_User){
    Thread *New_Th;
    Post *New_Po;
    New_Th = malloc(sizeof(Thread));
    New_Po = malloc(sizeof(Post));
    char file_name[TAILLE_NOM];
    char com_rm_file[TAILLE_NOM];
    // Fichier a envoyer :  "Nom_Ut_answer"
    strcat(file_name, Cur_User->Nom_Ut);
    strcat(file_name, "_answer");
    // Fichier :
    FILE* new_File = NULL;
    new_File = fopen(file_name, "ab");

    if (new_File != NULL)
    {
        // Les dates ne devraient pas marcher, il va faloir les passer en dur dans la structure
        fseek(new_File, 0, SEEK_END);
        fread(New_Th, sizeof(Thread), 1, new_File);
        New_Th->next_Th = NULL;
        for(New_Po = New_Th->F_P ; New_Po != NULL ; New_Po = New_Po->next_P){
            // L'itéarion du for marche car on test sur le pointeur NULL qui est NULL pour le serveur et aussi le client...
            fread(New_Po, sizeof(Post), 1, new_File);
            Ajout_Post(New_Po, New_Th);
        }
        fclose(new_File);
        strcat(com_rm_file, "rm ");
        strcat(com_rm_file, file_name);
        system(com_rm_file);
    }
    else {printf("Error Opening File \n");}
}

Date *Obtenir_Date(){ // Renvoi la date actuelle du serveur
    // Suffit de trouver comment on fait :)
    Date *Nouvelle_Date;
    Nouvelle_Date = malloc(sizeof(Date));
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    Nouvelle_Date->Annee = tm.tm_year + 1900;
    Nouvelle_Date->Mois =  tm.tm_mon + 1;
    Nouvelle_Date->Jour =  tm.tm_mday;
    Nouvelle_Date->Heure = tm.tm_hour;
    Nouvelle_Date->Minute = tm.tm_min;
    Nouvelle_Date->Seconde = tm.tm_sec;

    return Nouvelle_Date;
}

Date *Saisir_Date(){
    // Definition des Variables
    Date *Nouvelle_Date;
    Date *Cur_Date = Obtenir_Date();

    Nouvelle_Date = malloc(sizeof(Date));
    // Interface Utilisateur :
    printf("************* VOUS ALLEZ SAISIR UNE DATE : ****************\n");
    printf("(entrez des chiffres) Cette date se trouvera dans le mois courrant\n");
    printf("Le jour : ");
    scanf("%d", &Nouvelle_Date->Jour);
    printf("L'heure : ");
    scanf("%d", &Nouvelle_Date->Heure);
    // Traitement de la requete

    Nouvelle_Date->Annee = Cur_Date->Annee;
    Nouvelle_Date->Mois = Cur_Date->Mois;
    Nouvelle_Date->Minute = Cur_Date->Minute;
    Nouvelle_Date->Seconde = 0;

    if (Nouvelle_Date->Jour < Cur_Date->Jour || Nouvelle_Date->Heure < Cur_Date->Heure){
        printf("Erreur lors de la saisie, les parametres par défault ont été appliqués \n");
        Nouvelle_Date->Jour = Cur_Date->Jour;
        Nouvelle_Date->Heure = Cur_Date->Heure + 1;
    }
    return Nouvelle_Date;
}

void Affiche_Date(Date *Cur_Date){
    printf("Le %d/%d/%d à ", Cur_Date->Annee, Cur_Date->Mois, Cur_Date->Jour);
    printf("%d:%d:%d \n", Cur_Date->Heure, Cur_Date->Minute, Cur_Date->Seconde);
    printf("   AAAA/MM/JJ   HH:MM:SS \n");

}



Utilisateur *New_Utilisateur(char *Nom, char *Pw){

    Utilisateur *New_User;
    int i;
    New_User = malloc(sizeof(Utilisateur));
    New_User->ID_Ut = 1; // A initialiser
    New_User->droit = 0;
    strcpy(New_User->Nom_Ut, Nom);
    strcpy(New_User->PwU,Pw);
    for (i = 1; i < NOMBRE_TAGS; i++){New_User->Related_Ta[i] = 0;}
    return New_User;
}

void Affiche_Utilisateur(Utilisateur *Cur_Us){
    int i;
    printf("************* Utilisateur %d *************\n", Cur_Us->ID_Ut);
    printf("Nom : %s \n", Cur_Us->Nom_Ut);
    printf("Pw : %s \n", Cur_Us->PwU);
    printf("Tags Souscrits");
    for (i = 1; i < NOMBRE_TAGS; i++){
        //if (Cur_Us->Related_Ta[i] != 0){printf(", %d ",Cur_Us->Related_Ta[i]);}
    }
    printf("\n");
}




Thread *New_Thread(Date *End_Date, char *Titre){
    // Le thread est crée avec un Identifiant, une date de création qui correspond à l'appel de cette fonction
    // Une date de fin qui est spécifiée par l'utilisateur
    Thread *Cur_Th;
    Cur_Th = malloc(sizeof(Thread));
    Cur_Th->F_P = NULL;
    Cur_Th->L_P = NULL;
    Cur_Th->Debut = *Obtenir_Date();
    Cur_Th->Fin = *End_Date;
    Cur_Th->nbPost = 0;
    strcpy(Cur_Th->Nom, Titre);
    Cur_Th->Th_Id = 0; // A implementer
    Cur_Th->next_Th = NULL;
    return Cur_Th;

}

void Affiche_Thread(Thread *Cur_Th){
    printf("---------------------------------------------------------\n");
    printf("---------------------------------------------------------\n");
    printf("Titre : %s \n", Cur_Th->Nom);
    printf("Indentifiant : %d et nombre de Posts : %d \n", Cur_Th->Th_Id, Cur_Th->nbPost);
    printf("Date de début : \n");
    Affiche_Date(&Cur_Th->Debut);
    printf("Date de fin : \n");
    Affiche_Date(&Cur_Th->Fin);
}

void Affiche_Th_Po(Thread *Cur_Th){
    Affiche_Thread(Cur_Th);
    Post *New_Po;
    for (New_Po = Cur_Th->F_P; New_Po != NULL; New_Po = New_Po->next_P){
        Affiche_Post(New_Po);
    }
}

void Affiche_Al_Th(Thread *Root_Th){
    Thread *New_Th;

    for(New_Th = Root_Th; New_Th != NULL ; New_Th = New_Th->next_Th){
        Affiche_Thread(New_Th);
    }

}

void Ajout_Thread(Thread *New_Th, Thread *Root_Th){
    if (Root_Th->next_Th == NULL){
        Root_Th->next_Th = New_Th;
        New_Th->Th_Id = 1;
    }
    else{
        Thread *Cur_Th;
        for(Cur_Th = Root_Th->next_Th; Cur_Th->next_Th != NULL; Cur_Th = Cur_Th->next_Th){
        }
        Cur_Th->next_Th = New_Th;
        New_Th->Th_Id = Cur_Th->Th_Id + 1;
    }
}

Thread *Rech_Thread(Thread *Root, char *txt){
    Thread *Cur_Th;
    for (Cur_Th = Root ; Cur_Th != NULL ; Cur_Th = Cur_Th->next_Th){
        if (strcmp(txt, Cur_Th->Nom) == 0){
            return Cur_Th;
        }
    }
    Cur_Th = New_Thread(Obtenir_Date(), "NON TROUVE");
    return Cur_Th;
}

Thread *Match_Th_Ta(int i, Thread *Root_Th, Tag *Root_Ta){
    Thread *Cur_Th;
    Tag *Cur_Ta;
    for(Cur_Ta = Root_Ta; Cur_Ta->next_Ta != NULL ; Cur_Ta = Cur_Ta->next_Ta){

        for(Cur_Th = Root_Th; Cur_Th->next_Th != NULL ; Cur_Th = Cur_Th->next_Th){
            if (strcmp(Cur_Th->Nom, Cur_Ta->Nom) <= 0){
                printf("Cur_Ta %d \n", Cur_Ta);
                //return Cur_Th;
            }
        }
    }
    printf("Root_Th : %d \n", Root_Th->next_Th);
    return Root_Th;
}





Post *Remplir_Post(char *txt, Utilisateur *User, Thread *Cur_Th){ // Fonction serveur remplit le nouveau un nouveau post
    // Remplir l'auteur qui doit etre identifié
    // Mettre à jour le Thread avant : nombre de posts & Contenu
    Post *Nouveau_Post;
    Nouveau_Post = malloc(sizeof(Post));
    Nouveau_Post->Id_Auteur = User->ID_Ut;
    strcpy(Nouveau_Post->Auteur,User->Nom_Ut);
    Nouveau_Post->Date_Post = *Obtenir_Date(); // date du post
    Nouveau_Post->Th_Id = Cur_Th->Th_Id;  // Remplir le thread
    Nouveau_Post->Num_Pst = Cur_Th->nbPost + 1;   // Nombre de post dans le thread + 1, mettre a jour le nombre de post ds le thread
    strcpy(Nouveau_Post->Text, txt); // Lire ce qui est envoyé dans par le client
    Nouveau_Post->next_P = NULL;
    return Nouveau_Post;

}

void Affiche_Post(Post *Cur_Po){

    printf("____________________________________________ \n");
    printf("Post n° %d dans le Thread n° %d :\n", Cur_Po->Num_Pst, Cur_Po->Th_Id);
    printf("Posté par : %s \n", Cur_Po->Auteur);
    Affiche_Date(&Cur_Po->Date_Post);
    printf("'%s' \n", Cur_Po->Text);

}

void Ajout_Post(Post *New_Post, Thread *Cur_Thread){
    //Ajoute un post dans le thread Correspondant
    if (Cur_Thread->F_P == NULL){
        Cur_Thread->F_P = New_Post;
        Cur_Thread->nbPost++;
    }
    else{
        Cur_Thread->L_P->next_P = New_Post;
        Cur_Thread->nbPost++;
    }
    Cur_Thread->L_P = New_Post;

}

void Ajout_Post_BDD(Post *New_Post, Thread *Cur_Thread){
    //Ajoute un post dans le thread Correspondant
    if (Cur_Thread->F_P == NULL){
        Cur_Thread->F_P = New_Post;
    }
    else{
        Cur_Thread->L_P->next_P = New_Post;
    }
    Cur_Thread->L_P = New_Post;
}



// Géstion des Tags :
Tag *Generate_Tags(){
    Tag *New_Ta, *Cur_Tag, *F_Ta;

    int i;
    char Tab_Ta_Nom[NOMBRE_TAGS][TAILLE_NOM] = {"ROOT","Voiture", "Courses", "Sport", "Ecole", "Assos"};
    printf("%s \n", &*Tab_Ta_Nom[0]);
    for ( i = 0; i < NOMBRE_TAGS ; i++){

        New_Ta = malloc(sizeof(Tag));
        strcpy(New_Ta->Nom, &*Tab_Ta_Nom[i]);
        New_Ta->Related_Th[1] = 0;
        if (i != 0){
            Cur_Tag->next_Ta = New_Ta;
        }
        else
        {F_Ta = New_Ta;}
        Cur_Tag = New_Ta;
    }
    return F_Ta;
}

void Souscrire_Th(Utilisateur *Cur_User, Tag *Root_Ta, char Tab_Sub[NOMBRE_TAGS][TAILLE_NOM]){
    // Mise en place avec des indices il serait peut etre bon de passer avec des chaines de caractere
    int i, j, k;
    j = 1;
    Tag *Cur_Ta = Root_Ta; // Envisager de passer au Next
    for(i = 0 ; i < NOMBRE_TAGS ; i++){
        for(k = 0; k < NOMBRE_TAGS ; k++){
            if (strcmp(Tab_Sub[k], Cur_Ta->Nom) == 0){
                Cur_User->Related_Ta[j] = i;
                j++;
            }
        }

    Cur_Ta = Cur_Ta->next_Ta;
    }
}


void Help_Menu(){

    printf("\t**********AIDE TOMM ***********\n");
    printf("\t see Nom_du_Thread \n");
    printf("\t \t Affiche le Thread en question\n\n");
    printf("\t edit Nom_du_Thread Votre_Post\n");
    printf("\t \t Ecrit un post dans le Thread en question\n\n");
    printf("\t new Nom_du_Thread \n");
    printf("\t \t Crée le Thread en question\n\n");
    printf("\t delete Nom_du_Thread -Votre_Post\n");
    printf("\t \t Supprime un post ou le Thread donne en question\n");
    printf("\t \t Vous devez etre admininstrateur pour suprimer un Thread\n\n");
    printf("\t subscribe Nom_du_Tag \n");
    printf("\t \t Souscrit a un Tag et donc aux threads correspondant\n\n");
    printf("\t end \n");
    printf("\t \t Termine la session client\n\n");
    printf("\t login -Votre_Nom_Utilisateur Votre_Mot_de_Passe\n");
    printf("\t \t Authentification sur le serveur\n\n");
    printf("\t create -Votre_Nom_Utilisateur Votre_Mot_de_Passe\n");
    printf("\t \t pour creer un compte \n\n");
    printf("\t help \n");
    printf("\t \t Affiche l'aide\n");

}



Message_TOMM *Interpret_Cli(){

    char text[TAILLE_MES];
    char com[TAILLE_NOM], arg1[TAILLE_NOM], arg2[TAILLE_MES];
    int i, j, k;
    Message_TOMM *Mes;
    Mes = malloc(sizeof(Message_TOMM));
    // Initialisation :
    memset(com, 0, sizeof(com));
    memset(arg1, 0, sizeof(arg1));
    memset(arg2, 0, sizeof(arg2));
    j = 0;
    k = 0;

    // Saisie de la commande :
    printf("TOMM / ");
    fflush(stdout);
    fgets(text, sizeof(text), stdin);
    i = 0;
    while(text[i] != '\n'){
        switch(j){
            case 0:{
                com[k] =  text[i];
                k++;
                if (text[i+1] == ' '){j = 1;
                    k = 0;
                    i++;}
                break;
            }
            case 1:{
                arg1[k] =  text[i];
                k++;
                if(text[i+1] == ' '){j = 2;k = 0; i++;}
                break;
            }
            case 2:{
                arg2[k] = text[i];
                k++;
                break;
            }

        }
    i++;
    }


    /* Les codes :
	1 - see
	2 - edit
	3 - new
	4 - delete
	5 - help
	6 - subscribe
	7 - end
	10 - login Auto
    11 - login
    12 - create login
    */

    if(strcmp(com, "see") == 0){ // see
    Mes->descript = 1;
    strcpy(Mes->mes, arg1);
    strcat(Mes->mes, "\t \n");
    }
    else if(strcmp(com, "edit") == 0 ){// edit
    Mes->descript = 2;
    strcpy(Mes->mes, arg1);
    strcat(Mes->mes, "\t");
    strcat(Mes->mes, arg2);
    strcat(Mes->mes, "\n");
    }
    else if(strcmp(com, "new") == 0 ){// new
    Mes->descript = 3;
    strcpy(Mes->mes, arg1);
    strcat(Mes->mes, "\n");
    }
    else if(strcmp(com, "delete") == 0 ){// delete
    Mes->descript = 4;
    strcpy(Mes->mes, arg1);
    strcat(Mes->mes, "\n");
    }
    else if(strcmp(com, "help") == 0 ){//help
    Mes->descript = 5;
    Help_Menu();
    }
    else if(strcmp(com, "subscribe") == 0 ){// subscribe
    Mes->descript = 6;
    strcpy(Mes->mes, arg1);
    strcat(Mes->mes, "\n");
    }
    else if(strcmp(com, "end") == 0 ){// end
    Mes->descript = 7;
    }

    else if(strcmp(com, "login") == 0 ){//
        if(strlen(arg1) <= 1){
            Mes->descript = 10;
        }
        else
            {
            Mes->descript = 11;
            strcpy(Mes->mes, arg1);
            strcat(Mes->mes, "\t");
            strcat(Mes->mes, arg2);
            strcat(Mes->mes, "\n");
        }
    }
    else if(strcmp(com, "create") == 0 ){//
        Mes->descript = 12;
        strcpy(Mes->mes, arg1);
        strcat(Mes->mes, "\t");
        strcat(Mes->mes, arg2);
        strcat(Mes->mes, "\n");
    }
    /*
	printf("com : %s__\n", com);
	printf("arg1 : %s__\n", arg1);
	printf("arg2 : %s__\n", arg2);
    */
    return Mes;

}

Utilisateur *Get_User(Message_TOMM *Mes){
    Utilisateur *New_Us;
    char logi[TAILLE_NOM], pw[TAILLE_NOM], text[TAILLE_MES];
    int i, j, k;
    // Initialisation :
    memset(text, 0, sizeof(text));
    memset(logi, 0, sizeof(logi));
    memset(pw, 0, sizeof(pw));
    i = 0;
    j = 0;
    k = 0;
    strcpy(text, Mes->mes);
    while(text[i] != '\n' && i != TAILLE_MES){
        switch(j){
            case 0:{
                logi[k] =  text[i];
                k++;
                if (text[i+1] == '\t'){
                    j = 1;
                    k = 0;
                    i++;}
                break;
            }
            case 1:{
                pw[k] = text[i];
                k++;
                break;
                }
        }
        i++;
    }
    New_Us = New_Utilisateur(logi, pw);

    return New_Us;

}

void Write_Success(Message_TOMM *Mes){
    Mes->descript = 15;
    strcpy(Mes->mes, "Success");
}

void Write_Fail(Message_TOMM *Mes){
    Mes->descript = 15;
    strcpy(Mes->mes, "Fail");

}

void Lire_See(FILE *new_File, Message_TOMM *Mes_Lu){
    Thread *New_Th;
    Post *New_Po;
    int i;
    New_Th = malloc(sizeof(Thread));
    fseek(new_File, 0, SEEK_SET);
    fread(Mes_Lu, sizeof(Message_TOMM), 1, new_File);
    fread(New_Th, sizeof(Thread), 1, new_File);
    New_Th->F_P = NULL;
    for(i = 1; i <= New_Th->nbPost; i++){
        New_Po = malloc(sizeof(Post));
        fread(New_Po, sizeof(Post), 1, new_File);
        Ajout_Post_BDD(New_Po, New_Th);
    }
    Affiche_Th_Po(New_Th);
}


void Traitement_Answer(char *Nomfichier){

    char ComRM_Fichier[TAILLE_NOM];
    FILE* new_File = NULL;
    Message_TOMM *Mes_Lu;
    Mes_Lu = malloc(sizeof(Message_TOMM));
    new_File = fopen(Nomfichier, "r");
    //printf("Debut Traitement du Fichier \n");
    if (new_File != NULL)
    {
        fseek(new_File, 0, SEEK_SET);
        fread(Mes_Lu, sizeof(Message_TOMM), 1, new_File);
        //printf("\n\nRecut : %d\n\n", Mes_Lu->descript);
        switch(Mes_Lu->descript){
            case 1: { // See
                printf("Commande See demandee\n");
                Lire_See(new_File, Mes_Lu);
                break;
            }
            case 2: { // Edit
                printf("Commande Edit demandee\n");
                break;
            }
            case 3: { // New
                printf("Commande New demandee\n");
                break;
            }
            case 4: { // Delete
                printf("Commande Delete demandee\n");
                printf("Désolé cette commande n'est pas implémentée \n");
                break;
            }
            case 5: { // help
                printf("Commande Help demandee\n");
                break;
            }
            case 6:{ // souscrire
                printf("Commande Souscrire demandee\n");
                break;
            }
            case 7:{ // end
                printf("Commande End demandee\n");
                printf("Le client TOMM va s'arreter...\n");
            }
            case 15:{ // Success Retourne
                printf("Etat de votre requete : %s.\n", Mes_Lu->mes);
            }/*
            case 8:{ // Error
                printf("Commande Error demandee\n");
                break;
            }*/
    }
    fclose(new_File);
    strcpy(ComRM_Fichier, "rm ");
    strcat(ComRM_Fichier, Nomfichier);
    system(ComRM_Fichier);
    printf("FIN Traitement du Fichier, fichier supprime \n");
    }
    else {printf("Error Opening File \n");}
}

void rm_File(char *NonFichier){
    char ComRM_Fichier[TAILLE_NOM];
    strcpy(ComRM_Fichier, "rm ");
    strcat(ComRM_Fichier, NonFichier);
    system(ComRM_Fichier);
}
