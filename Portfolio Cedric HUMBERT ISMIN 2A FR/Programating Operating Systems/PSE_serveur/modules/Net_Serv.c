/**********************************************************
*
*	File : Net_Serv.c
*	Author : Cédric HUMBERT & Kilian CONTAMAIN
*
*	Description :
*   Ce fichier contient les fonctions relatives à
*   l'éxectution des transports de fichiers Network
*
*   Projet : PSE ISMIN 2A
*
*	Date : 18/ 11/ 2014
*
*************************************************************/

#include "../include/pse.h"

/* donnees globales partagees par tous les threads */
DataSpec cohorte[NTHREADS];
sem_t sem_libres;
int journal;

/* Notament pour la version Multithread mais n'est pas utilisé ici.
Message_TOMM *Mes;
Utilisateur *Cur_Us;
*/



void Mono_TOMM(int argc, char *argv[]){
    int ecoute, canal, ret, mode, ilibre, i, log, arret;
    struct sockaddr_in adrEcoute, reception;
    socklen_t receptionlen = sizeof(reception);
    char texte[LIGNE_MAX];
    short port;
    if (argc != 2) {erreur("usage: %s port\n", argv[0]);}

    if (argc != 2) {erreur("usage: %s port\n", argv[0]);}
    // Prise des paramètres de la connextion
    port = (short) atoi(argv[1]);

    //printf("%s: creating a socket\n", CMD);
    ecoute = socket (AF_INET, SOCK_STREAM, 0);
    if (ecoute < 0) {erreur_IO("socket");}

    adrEcoute.sin_family = AF_INET;
    adrEcoute.sin_addr.s_addr = INADDR_ANY;
    adrEcoute.sin_port = htons(port);
    //printf("%s: binding to INADDR_ANY address on port %d\n", CMD, port);
    ret = bind (ecoute,  (struct sockaddr *) &adrEcoute, sizeof(adrEcoute));
    if (ret < 0) {erreur_IO("bind");}

    //printf("%s: listening to socket\n", CMD);
    ret = listen (ecoute, 5);
    if (ret < 0) {erreur_IO("listen");}
    // Fin du parametrage, écoute

    // parametrage se l'écoute :
    receptionlen = sizeof(reception);
    //printf("%s: accepting a connection\n", CMD);
    canal = accept(ecoute, (struct sockaddr *) &reception, &receptionlen);
    if (canal < 0) {erreur_IO("accept");}
    printf("%s: adr %s, port %hu\n", CMD,
        stringIP(ntohl(reception.sin_addr.s_addr)),
        ntohs(reception.sin_port));


    /// Boucle d'écoute : */
    arret = FAUX;
    while(arret == FAUX){
       if (lireLigne(canal, texte) == 6){
            // Interaction avec le serveur tout va bien !
            Serveur_TOMM(canal, texte);
        }
        else {
            printf("Fin de client \n");
            arret = VRAI;
        }
    }

    if (close(canal) == -1) {erreur_IO("close canal");}
    if (close(ecoute) == -1) {erreur_IO("close ecoute");}
}


void Serveur_TOMM(int sock, char *texte){

    Utilisateur *Cur_Us;
    Message_TOMM *Mes;
    Cur_Us =(Utilisateur*) malloc(sizeof(Utilisateur));
    Mes = malloc(sizeof(Message_TOMM));

    //printf("La ligne recue est : %s__ \n", texte);

    if(strcmp(texte, "ENVOI")==0){ // Le client Lance un diaogue avec le serveur
        RecevoirFich(sock,"Temp/Requete"); // Reception du fichier
        read_Message_TOMM(Mes, "Temp/Requete"); // Ecriture de la requete dans un message

        Interpret_Request(Mes, Cur_Us); // Ecrit dans message les reponses
        //printf("Nouveau message descript : %d et mes : _%s__ \n", Mes->descript, Mes->mes);
        envoyerFichier(sock,"Temp/Answer"); // On peut donner le nom du worker au fichier
        rm_File("Temp/Answer");
    }
    // Cas de test :
    else if(strcmp(texte, "RECPT")==0){envoyerFichier(sock,"test.txt");} // Pour les tests, non utilisé
    else {
        RecevoirFich(sock,"Temp/Requete"); // Reception du fichier
        rm_File("Temp/Requete");
        printf("Mauvaise Requette \n");
        Write_Fail(Mes);
        envoyerFichier(sock, "Temp\Answer");
    }
    free(Cur_Us);
    free(Mes);
}


void Interpret_Request(Message_TOMM *Mes, Utilisateur *Cur_Us){

    //printf("Interpreteur de Message Serveur : %d \n", Mes->descript);
    switch(Mes->descript){
        case 1:{ // see
            See_Cli(Mes, "Temp/Answer");
            break;
        }
        case 2:{ // edit
            Edit_Cli(Mes);
            break;
        }
        case 3:{ // new
            New_Cli(Mes);
            break;
        }
        case 4:{ // delete
            Delete_Cli(Mes);
            break;
        }
        case 5:{ // help
            Write_Success(Mes);
            write_Message_TOMM(Mes, "Temp/Answer");
            break;
        }
        case 6:{ // subscribe
            Subscribe_Cli(Mes);
            break;
        }
        case 7:{ // end
            Write_Success(Mes);
            break;
        }
        case 10:{
            Cur_Us = Get_User(Mes);
            //Affiche_Utilisateur(Cur_Us);
            if (Validate_User(Cur_Us) == 1){// Utilisateur VALIDE
                printf("Validé !! \n");
                Write_Success(Mes);
                write_Message_TOMM(Mes, "Temp/Answer");
            }
            else { // Utilisateur Non valide
                printf("Non Validé !\n");
                Write_Fail(Mes);
                write_Message_TOMM(Mes, "Temp/Answer");
            }
            break;
        }
        case 11:{
            Cur_Us = Get_User(Mes);
            Affiche_Utilisateur(Cur_Us);
            if (Validate_User(Cur_Us) == 1){// Utilisateur VALIDE
                printf("Validé !! \n");
                Write_Success(Mes);
                write_Message_TOMM(Mes, "Temp/Answer");
            }
            else { // Utilisateur Non valide
                printf("Non Validé !\n");
                Write_Fail(Mes);
                write_Message_TOMM(Mes, "Temp/Answer");
            }
            break;
        }
        case 12:{
            Cur_Us = Get_User(Mes);
            Affiche_Utilisateur(Cur_Us);
            if (Validate_User(Cur_Us) != 1){// Utilisateur Non deja utilisé
                printf("Validé !! \n");
                Write_Success(Mes);
                write_Message_TOMM(Mes, "Temp/Answer");
            }
            else { // Utilisateur Non valide
                printf("Non Validé !\n");
                Write_Fail(Mes);
                write_Message_TOMM(Mes, "Temp/Answer");
            }
            break;
        }
        case 0:{
            printf("Erreur retournée Requete non reconnue\n");
            Write_Fail(Mes);
            write_Message_TOMM(Mes, "Temp/Answer");
            break;
        }
    }
}


void See_Cli(Message_TOMM *Mes, char *NomFichier){
    Mes->descript = 1;
    int new_File;
    Thread *Cur_Th;
    Post *Cur_Po;
    char arg1[TAILLE_NOM], arg2[TAILLE_MES];
    Get_Param(Mes, arg1, arg2);
    memset(Mes->mes, '\0', sizeof(Mes->mes));
    //printf("arg1 : _%s_ et arg2 : _%s_ \n", arg1, arg2);

    Cur_Th = Rech_Thread(Root_Th, arg1);

    Affiche_Thread(Cur_Th);

    new_File = fopen(NomFichier, "w");

    if (new_File != NULL)
    {
        fseek(new_File, 0, SEEK_SET);
        fwrite(Mes, sizeof(Message_TOMM), 1, new_File);
        fseek(new_File,sizeof(Message_TOMM), SEEK_SET);
        fwrite(Cur_Th, sizeof(Thread), 1, new_File);
        for (Cur_Po = Cur_Th->F_P ; Cur_Po != NULL ; Cur_Po = Cur_Po->next_P){
            fwrite(Cur_Po, sizeof(Post), 1, new_File);
            Affiche_Post(Cur_Po);
        }
        fclose(new_File);
    }
    else {printf("Error Opening File \n");}

}


void Edit_Cli(Message_TOMM *Mes){

    Mes->descript = 2;
    Thread *Cur_Th;
    Post *New_Po;
    Utilisateur *Cur_Us;
    Cur_Us = New_Utilisateur("foo", "pow");
    char arg1[TAILLE_NOM], arg2[TAILLE_MES];

    // Lire le message
    Get_Param(Mes, arg1, arg2);
    memset(Mes->mes, '\0', sizeof(Mes->mes));
    //printf("arg1 : %s et arg2 : %s \n", arg1, arg2);

    // Trouver le Thread
    Cur_Th = Rech_Thread(Root_Th, arg1);
    Affiche_Thread(Cur_Th);

    // Ajouter le post
    New_Po = Remplir_Post(arg2, Cur_Us, Cur_Th);
    Ajout_Post(New_Po, Cur_Th);

    // Si tt se passe bien renvoyer success
    write_Message_TOMM(Mes, "Temp/Answer");
    Write_Success(Mes);
}


void New_Cli(Message_TOMM *Mes){

    Mes->descript = 3;
    Thread *Cur_Th;
    char arg1[TAILLE_NOM], arg2[TAILLE_MES];

    // Lire le message
    Get_Param(Mes, arg1, arg2);
    memset(Mes->mes, '\0', sizeof(Mes->mes));
    //printf("arg1 : %s et arg2 : %s \n", arg1, arg2);

    // Ajouter le Thread
    Cur_Th = New_Thread(Obtenir_Date(), arg1);
    Ajout_Thread(Cur_Th, Root_Th);

    // Si tt se passe bien renvoyer success
    Write_Success(Mes);
    write_Message_TOMM(Mes, "Temp/Answer");
}


void Delete_Cli(Message_TOMM *Mes){

    // Lire le message

    // Supprimer le Thread

    // non Implementé : Fail
    Write_Fail(Mes);
    write_Message_TOMM(Mes, "Temp/Answer");
}


void Subscribe_Cli(Message_TOMM *Mes){

    // Lire le message

    // Supprimer le Thread

    // Si tt se passe bien renvoyer success si non Fail
    Write_Fail(Mes);
    write_Message_TOMM(Mes, "Temp/Answer");
}


void RecevoirFich(int sock , char *FichierDestination){
    printf("reception fichier : %s\n",FichierDestination);
    sFich *buff, *Tamp;
    Tamp = malloc(sizeof(sFich));
    buff = malloc(sizeof(sFich));
    int arret, i;
    char AsserRecpt[TAILLE_NOM];
    strcpy(AsserRecpt, "RECU");
    arret = VRAI;
    strcpy(Tamp->Buffer, "init");
    FILE * Fich = fopen(FichierDestination,"wb");
    if(Fich != NULL )
    {
        while(arret){
            buff = malloc(sizeof(sFich));
            i = recv(sock, buff->Buffer, TAILLE_MES, 0);
            /*
            printf("Recut : %s___\n" ,buff->Buffer);
            printf("Tampon : %s_\n", Tamp->Buffer);
            printf("Recv = %d\n", i);
            printf("Fin de fichier : %d \n", buff->finFich);
            */
            if(strcmp("Terminate", buff->Buffer) == 0  || i != TAILLE_MES){
                printf("Vu end of file \n");
                arret = FAUX;
            }
            else{
                //printf("taillse de buffer : %d\n", strlen(buff->Buffer));
                ecrireLigne(sock, AsserRecpt);
                fwrite(buff->Buffer ,sizeof(char) , TAILLE_MES, Fich);
                //printf("Ecrit : %s\n" ,buff->Buffer);
                strcpy(Tamp->Buffer, buff->Buffer);
            }
            free(buff);
            //printf("Attente reception\n");
        }
        fclose(Fich);
    }
    printf("Fin reception\n");
}


void envoyerFichier(int sock,char * NomFichier){
    sFich *buffer;
    int arret = FAUX;
    char chaine[TAILLE_NOM];
    //buffer = malloc(sizeof(sFich));
    //buffer->finFich = 0;
    FILE* fichier =fopen(NomFichier , "rb");
    int i;

    if ( fichier != NULL) // ce test échoue si le fichier n'est pas ouvert
    {
        while (!arret )
        {
            buffer = malloc(sizeof(sFich));
            i = fread( buffer->Buffer , 1 , TAILLE_MES , fichier );
            if(i != TAILLE_MES){
                buffer->finFich = 1;
                arret = VRAI;
                //send(sock, "EOF", sizeof(sFich), 0);
            }
            //send(sock, buffer, sizeof(sFich), 0);
            send(sock, buffer->Buffer, TAILLE_MES, 0);
            //printf("fin fichier ?? -> %d \n %s__\n i = %d size : %d \n" ,buffer->finFich, buffer->Buffer,i, sizeof(sFich) );
            // Verification de reception
            lireLigne(sock, chaine);
            //printf("Ce qui reste dans le canal : %s_\n",chaine);
            free(buffer);
            //memset(buffer->Buffer,'\0',TAILLE_MES);
        }

        //printf("envoi %s fini \n", NomFichier);
        fclose(fichier);
        strcpy(chaine, "Terminate");
        ecrireLigne(sock, chaine);
    }
    else
        printf("erreur ouverture fichier\n");
return;
}





void Start_up_TOMM(int argc, char *argv[]){ // Validé Testé
  int ecoute, canal, ret, mode, ilibre, i;
  struct sockaddr_in adrEcoute, reception;
  socklen_t receptionlen = sizeof(reception);
  short port;
  if (argc != 2) {erreur("usage: %s port\n", argv[0]);}

  mode = O_WRONLY|O_APPEND|O_CREAT;
  journal = open("journal.log", mode, 0660);
  if (journal == -1) {erreur_IO("open journal");}

  if (sem_init(&sem_libres, 0, NTHREADS) == -1) {erreur_IO("sem_init libres");}

  /* initialisation cohorte */
  for (i=0; i<NTHREADS; i++) {
    cohorte[i].tid = i;
    cohorte[i].libre = VRAI;
    /* une valeur -1 indique pas de requete a traiter */
    cohorte[i].canal = -1;
    if (sem_init(&cohorte[i].sem, 0, 0) == -1) {erreur_IO("sem_init");}
    ret = pthread_create(&cohorte[i].id, NULL, traiterRequete, &cohorte[i]);
    if (ret != 0) {erreur_IO("pthread_create");}
  }

  port = (short) atoi(argv[1]);

  printf("server: creating a socket\n");
  ecoute = socket (AF_INET, SOCK_STREAM, 0);
  if (ecoute < 0) {erreur_IO("socket");}

  adrEcoute.sin_family = AF_INET;
  adrEcoute.sin_addr.s_addr = INADDR_ANY;
  adrEcoute.sin_port = htons(port);
  printf("server: binding to INADDR_ANY address on port %d\n", port);
  ret = bind (ecoute,  (struct sockaddr *) &adrEcoute, sizeof(adrEcoute));
  if (ret < 0) {erreur_IO("bind");}

  printf("server: listening to socket\n");
  ret = listen (ecoute, 20);
  if (ret < 0) {erreur_IO("listen");}

  while (VRAI) {

    printf("server: waiting to a connection\n");
    canal = accept(ecoute, (struct sockaddr *) &reception, &receptionlen);
    if (canal < 0) {erreur_IO("accept");}

    printf("server: adr %s, port %hu\n",
	   stringIP(ntohl(reception.sin_addr.s_addr)),
	   ntohs(reception.sin_port));

    if (sem_wait(&sem_libres) == -1) {erreur_IO("sem_post");}
    for (ilibre=0; ilibre<NTHREADS; ilibre++)
      if (cohorte[ilibre].libre) break;
    printf("serveur: %d\n", ilibre);

    cohorte[ilibre].canal = canal;
    if (sem_post(&cohorte[ilibre].sem) == -1) {erreur_IO("sem_post");}
    printf("server: worker %d choisi\n", ilibre);

  }

  exit(EXIT_SUCCESS);

}


/* traitement des requetes par les threads */
void *traiterRequete(void *arg) {
  DataSpec * data = (DataSpec *) arg;
  int arret = FAUX, nblus, mode;
  char texte[LIGNE_MAX];
  printf("Dans le traitement de Requette ! \n");
  Utilisateur *Cur_Us;
  Cur_Us = New_Utilisateur("Admin", "0000");
  Affiche_Utilisateur(Cur_Us);
  mode = O_WRONLY | O_APPEND | O_CREAT | O_TRUNC;

  while (VRAI) {
    printf("worker %d: attente canal.\n", data->tid);
    /* attente canal */
    if (sem_wait(&data->sem) != 0) {erreur_pthread_IO("sem_wait");}
    data->libre = FAUX;
    printf("worker %d: lecture canal %d.\n", data->tid, data->canal);

    arret = FAUX;

    /// BOUCLE DU THREAD :

    while (arret == FAUX){

        if (lireLigne(data->canal, texte) == 5){
            // Interaction avec le serveur tout va bien !
            Serveur_TOMM(data->canal, texte);
        }
        else {
            erreur_pthread_IO("Mauvaise requette");
            printf("Fin de client \n");
            arret = VRAI;
        }

    }

    if (close(data->canal) == -1) {erreur_IO("close");}
    data->canal = -1;
    data->libre = VRAI;
    if (sem_post(&sem_libres) != 0) {erreur_pthread_IO("sem_post");}
  }

  pthread_exit(NULL);
}










