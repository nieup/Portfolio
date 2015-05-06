/**********************************************************
*
*	File : TOMM_Serv.c
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
    // FAIRE UNE GESTION DES ERREURS avec i
        int i;
        fseek(new_File, 0, SEEK_SET);
        i = fread(Mes_Lu, sizeof(Message_TOMM), 1, new_File);
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
        fseek(new_File, 0, SEEK_SET);
        fwrite(Cur_Th, sizeof(Thread), 1, new_File);
        for (Cur_Po = Cur_Th->F_P ; Cur_Po != NULL ; Cur_Po = Cur_Po->next_P){
            fwrite(Cur_Po, sizeof(Post), 1, new_File);
        }
        fclose(new_File);
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


void Affiche_Date(Date *Cur_Date){
    printf("Le %d/%d/%d à ", Cur_Date->Annee, Cur_Date->Mois, Cur_Date->Jour);
    printf("%d:%d:%d \n", Cur_Date->Heure, Cur_Date->Minute, Cur_Date->Seconde);
    printf("   AAAA/MM/JJ   HH:MM:SS \n");

}


Utilisateur *New_Utilisateur(char *Nom, char *Pw){

    Utilisateur *New_Us;
    int i;
    New_Us = malloc(sizeof(Utilisateur));
    New_Us->ID_Ut = 1; // A initialiser
    strcpy(New_Us->Nom_Ut, Nom);
    strcpy(New_Us->PwU,Pw);
    for (i = 1; i < NOMBRE_TAGS; i++){New_Us->Related_Ta[i] = 0;}
    return New_Us;
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
        for(Cur_Th = Root_Th->next_Th; Cur_Th->next_Th != NULL; Cur_Th = Cur_Th->next_Th){}
        Cur_Th->next_Th = New_Th;
        New_Th->Th_Id = Cur_Th->Th_Id + 1;
    }
}


void Ajout_Thread_BDD(Thread *New_Th, Thread *Root_Th){
    if (New_Th->Th_Id == 1){
        Root_Th->next_Th = New_Th;
    }
    else{
        int i;
        Thread *Cur_Th;
        Cur_Th = Root_Th->next_Th;
        for(i = 1; i < New_Th->Th_Id -1; i++ ){Cur_Th = Cur_Th->next_Th;}
        Cur_Th->next_Th = New_Th;
    }
}


Thread *Rech_Thread(Thread *Root, char *txt){
    Thread *Cur_Th;
    for (Cur_Th = Root ; Cur_Th != NULL ; Cur_Th = Cur_Th->next_Th){
        //printf(" string : %s VS. N_Th %s\n", txt, Cur_Th->Nom);
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


void Save_Data(Thread *Root_Th){

    Thread *Cur_Th;
    Post *Cur_Po;
    FILE* new_File = NULL;
    FILE* Index_file = NULL;
    char NomSavFichier[TAILLE_MES];
    char CommandeFichier[TAILLE_MES];
    char NomIndexSav[TAILLE_MES];

    strcpy(NomIndexSav, "data/index");

    Index_file = fopen(NomIndexSav, "w");
    if(Index_file != NULL){
        fseek(Index_file, 0, SEEK_SET);
        printf("Saving All Data in /data \n");
        for (Cur_Th = Root_Th ; Cur_Th != NULL; Cur_Th = Cur_Th->next_Th){

            fwrite(Cur_Th, sizeof(Thread), 1, Index_file);

            strcpy(NomSavFichier, "");
            strcat(NomSavFichier, "data/");
            strcat(NomSavFichier, Cur_Th->Nom);
                // Fichier :
            new_File = fopen(NomSavFichier, "w");

            if (new_File != NULL)
            {
                fseek(new_File, 0, SEEK_SET);
                fwrite(Cur_Th, sizeof(Thread), 1, new_File);
                for (Cur_Po = Cur_Th->F_P ; Cur_Po != NULL ; Cur_Po = Cur_Po->next_P){
                    fwrite(Cur_Po, sizeof(Post), 1, new_File);}
                fclose(new_File);
            }
            else {printf("Error Opening File \n");}
        }
    }
    else {printf("Error Opening File \n");}
}


Thread *Lire_Thread_BDD(Thread *Cur_Th){

    int i;
    Thread *New_Th;
    Post *Cur_Po, *New_Po;
    New_Th = malloc(sizeof(Thread));
    char file_name[TAILLE_NOM];
    // Fichier :
    strcpy(file_name, "");
    strcpy(file_name, "data/");
    strcat(file_name, Cur_Th->Nom);

    FILE* new_File = NULL;
    new_File = fopen(file_name, "r");
    if (new_File != NULL)
    {
        fseek(new_File, 0, SEEK_SET);
        fread(New_Th, sizeof(Thread), 1, new_File);
        New_Th->F_P = NULL;
        for(i = 1; i <= New_Th->nbPost; i++){
            New_Po = malloc(sizeof(Post));
            fread(New_Po, sizeof(Post), 1, new_File);
            Ajout_Post_BDD(New_Po, New_Th);
        }
        fclose(new_File);
        return New_Th;
    }
    else {printf("Error Opening File \n");}
}


void Lire_BDD(Thread *Root_Th){

    int arret = VRAI;
    Thread *Cur_Th, *New_Th;
    FILE* Index_file = NULL;
    char NomIndexSav[TAILLE_MES];

    Cur_Th = malloc(sizeof(Thread));


    strcpy(NomIndexSav, "data/index");

    Index_file = fopen(NomIndexSav, "r");
    if(Index_file != NULL){
        fseek(Index_file, 0, SEEK_SET);
        fread(Root_Th, sizeof(Thread), 1, Index_file);
        Root_Th->next_Th = NULL;
        while(arret){
            New_Th = malloc(sizeof(Thread));
            fread(New_Th, sizeof(Thread), 1, Index_file);
            New_Th = Lire_Thread_BDD(New_Th);
            if(New_Th->next_Th == NULL){arret = FAUX;}
            New_Th->next_Th = NULL;
            Ajout_Thread_BDD(New_Th, Root_Th);
        }
        fclose(Index_file);
        printf("La base de donnée a été Chargée ! \n");
    }
    else {printf("Error Opening File \n");}

}


void Generate_Data(Thread *Root_Th){
    //REMPLISSAGE BDD :
    Thread *Cur_Th;
    Post *Cur_Po;
    Utilisateur *Cur_Us1;
    Utilisateur *Cur_Us2;
    Cur_Us1 = New_Utilisateur("Fake1", "Pw");
    Cur_Us2 = New_Utilisateur("Fake2", "Pw");
    // Nouveau Thread :
    Cur_Th = New_Thread(Obtenir_Date(), "Voiture_Paris");
    Ajout_Thread(Cur_Th, Root_Th);
    Cur_Po = Remplir_Post("Bonjour,Je voudrais aller a Paris ce Week-end", Cur_Us1, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);
    Cur_Po = Remplir_Post("Salut Fake, je vais justement à Paris en R5 vendredi", Cur_Us2, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);
    Cur_Po = Remplir_Post("Merci Fake, On pars apres ls cours ?", Cur_Us1, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);
    Cur_Po = Remplir_Post("Ca marche !", Cur_Us2, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);

    // Nouveau Thread :
    Cur_Th = New_Thread(Obtenir_Date(), "Sport_Rugdy");
    Ajout_Thread(Cur_Th, Root_Th);
    Cur_Po = Remplir_Post("Bonjour, qui veux aller jouer au RuGeby ce Jeudi ?", Cur_Us1, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);
    Cur_Po = Remplir_Post("Salut Fake, on a prévu d'y aller en R5 demain", Cur_Us2, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);
    Cur_Po = Remplir_Post("Merci Fake, vous me prennez chez moi vers 8h ?", Cur_Us1, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);
    Cur_Po = Remplir_Post("Ca marche !", Cur_Us2, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);

    // Nouveau Thread :
    Cur_Th = New_Thread(Obtenir_Date(), "Ecole_PSE");
    Ajout_Thread(Cur_Th, Root_Th);
    Cur_Po = Remplir_Post("Bonjour, j'ai un soucis avec la date du rendu c'est bien a 8h 19 ?", Cur_Us1, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);
    Cur_Po = Remplir_Post("Salut Fake, oui oui on va encore passer une de ces nuits...", Cur_Us2, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);
    Cur_Po = Remplir_Post("Merci Fake, quoi vous vous couchez à 8h ?", Cur_Us1, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);
    Cur_Po = Remplir_Post("Toujours !", Cur_Us2, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);

    // Nouveau Thread :
    Cur_Th = New_Thread(Obtenir_Date(), "Assos_CA_FEI");
    Ajout_Thread(Cur_Th, Root_Th);
    Cur_Po = Remplir_Post("Bonjour, il y aura un CA du FEI ce vendredi a 12h 30 ?", Cur_Us1, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);
    Cur_Po = Remplir_Post("Salut Fake, on peut venir manger aussi ?", Cur_Us2, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);
    Cur_Po = Remplir_Post("Merci Fake pour ton humour mais non c'est serieux ce coup la", Cur_Us1, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);
    Cur_Po = Remplir_Post("Ca marche !", Cur_Us2, Cur_Th);
    Ajout_Post(Cur_Po, Cur_Th);

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
                if (text[i+1] == '\n' || text[i+1] == ' ')
                    {j = 2;}
                k++;
                break;
                }
        }
        i++;
    }
    New_Us = New_Utilisateur(logi, pw);

    return New_Us;

}


void Get_Param(Message_TOMM *Mes, char *arg1, char *arg2){
    Utilisateur *New_Us;
    char text[TAILLE_MES];
    int i, j, k;
    // Initialisation :
    memset(text, 0, sizeof(text));
    memset(arg1, 0, sizeof(arg1));
    memset(arg2, 0, sizeof(arg2));
    i = 0;
    j = 0;
    k = 0;
    strcpy(text, Mes->mes);
    while(text[i] != '\n' && i != TAILLE_MES){
        switch(j){
            case 0:{
                arg1[k] = text[i];
                k++;
                if (text[i+1] == '\t'){
                    j = 1;
                    k = 0;
                    i++;}
                break;
            }
            case 1:{
                //printf("Ecriture dans arg2\n");
                arg2[k] = text[i];
                k++;
                if (text[i+1] == '\n'){j = 2;}
                break;
                }
        }
        i++;
    }
}


Post *Get_Post(Message_TOMM *Mes, Utilisateur *Cur_Us){
    Thread *Cur_Th;
    Post *New_Po;
    char  text[TAILLE_MES], Th_N[TAILLE_NOM], Po_txt[TAILLE_MES];
    int i, j, k;
    // Initialisation :
    memset(text, 0, sizeof(text));
    memset(Th_N, 0, sizeof(Th_N));
    memset(Po_txt, 0, sizeof(Po_txt));
    i = 0;
    j = 0;
    k = 0;
    strcpy(text, Mes->mes);
    while(text[i] != '\n' && i != TAILLE_MES){
        switch(j){
            case 0:{
                Th_N[k] =  text[i];
                k++;
                if (text[i+1] == '\t'){
                    j = 1;
                    k = 0;
                    i++;}
                break;
            }
            case 1:{
                Po_txt[k] = text[i];
                k++;
                break;
                }
        }
        i++;
    }
    Cur_Th = Rech_Thread(Root_Th, Th_N);
    New_Po = Remplir_Post(text, Cur_Us, Cur_Th);

    return New_Po;
}


void Write_Success(Message_TOMM *Mes){
    Mes->descript = 15;
    strcpy(Mes->mes, "Success\0");
}


void Write_Fail(Message_TOMM *Mes){
    Mes->descript = 15;
    strcpy(Mes->mes, "Fail\0");
}


void rm_File(char *NonFichier){

    char ComRM_Fichier[TAILLE_NOM];
    strcpy(ComRM_Fichier, "rm ");
    strcat(ComRM_Fichier, NonFichier);
    system(ComRM_Fichier);
}


