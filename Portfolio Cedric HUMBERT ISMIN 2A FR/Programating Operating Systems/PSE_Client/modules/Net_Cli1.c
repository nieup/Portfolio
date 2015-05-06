/**********************************************************
*
*	File : Net_Cli.c
*	Author : Cédric HUMBERT & Kilian CONTAMAIN
*
*	Description :
*   Ce fichier contient les fonctions relatives à
*   l'éxectution de la partie Network client de TOMM
*
*   Projet : PSE ISMIN 2A
*
*	Date : 19/ 11/ 2014
*
*************************************************************/
//#include "include/pse.h"
#include "../include/pse.h"

int Create_Sock(){
    int sock;
    //printf("%s: creating a socket\n", CMD);
    sock = socket (AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {erreur_IO("socket");}
    return sock;
}

void Connection_TOMM(int sock, int argc, char *argv[]){
    int ret;
    struct sockaddr_in *sa;
    char To_Local[2][10] = {"localhost", "20000"};
    if (argc != 3) {
        // Fait une connection sur le loopback par défaut port 20000
        //printf("%s: DNS resolving for %s, port %s\n", CMD, To_Local[0], To_Local[1]);
        sa = resolv(To_Local[0], To_Local[1]);
        if (sa == NULL) {
            erreur("adresses %s et port %s inconnus\n", argv[0], To_Local[0]);
        }
        //erreur("usage: %s machine port\n", argv[0]);
    }
    else{
        //printf("%s: DNS resolving for %s, port %s\n", CMD, argv[1], argv[2]);
        sa = resolv(argv[1], argv[2]);
        if (sa == NULL) {
            erreur("adresses %s et port %s inconnus\n", argv[0], argv[1]);
        }
    }

    /*printf("%s: adr %s, port %hu\n", CMD,
	stringIP(ntohl(sa->sin_addr.s_addr)),
        ntohs(sa->sin_port));*/

    /* connexion sur site distant */
    //printf("%s: connecting the socket\n", CMD);
    ret = connect(sock, (struct sockaddr *) sa, sizeof(struct sockaddr_in));
    if (ret < 0) {
        erreur_IO("Connect");
    }
    freeResolv(); // libere les resources allouées à resolv (cf recherche dns)
}

void Authentification_Locale(Message_TOMM *Mes, Utilisateur *Cur_User){
        // Test de login :
        if(Mes->descript == 11){ // Log
            //printf("Descript -> %d\n", Mes->descript);
            Cur_User = Get_User(Mes);
            // Affichage du login :
            printf("Vous etes authentifié sous le nom : \n");
            Affiche_Utilisateur(Cur_User);
        }
        else if(Mes->descript == 10){ // Auto log
            //printf("Descript -> %d\n", Mes->descript);
            //printf(" Auto log \n");
            Cur_User = Auto_Log();
            Affiche_Utilisateur(Cur_User);
        }
        else if(Mes->descript == 12){ // create auto log
            //printf("Descript -> %d\n", Mes->descript);
            //printf("Create Log : \n");
            Cur_User = Get_User(Mes);
            Affiche_Utilisateur(Cur_User);
            //printf("User Crée \n");
            Write_Auto_Log(Cur_User);
            //printf("Auto Log ecrit \n");
            Utilisateur *Created_User;
            Created_User = Auto_Log();
            Affiche_Utilisateur(Created_User);
        }
        else {
            printf("Vous devez d'abord vous authentifier \n");
            //printf("Descript -> %d\n", Mes->descript);
        }
}

Utilisateur *Auto_Log(){
    Utilisateur *Cur_User;
    Cur_User = malloc(sizeof(Utilisateur));
    FILE* new_File = NULL;
    new_File = fopen("log", "r");
    if (new_File != NULL)
    {
        fseek(new_File, 0, SEEK_SET);
        fread(Cur_User, sizeof(Utilisateur), 1, new_File);
        fclose(new_File);
        return Cur_User;
    }
    else {printf("Error Opening File \n");}
}

void Write_Auto_Log(Utilisateur *Cur_User){
    FILE* new_File = NULL;

    new_File = fopen("log", "w");

    if (new_File != NULL){
        fseek(new_File, 0, SEEK_END);
        fwrite(Cur_User, sizeof(Utilisateur), 1, new_File);
        fclose(new_File);
    }
    else {printf("Error Opening File \n");}
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

void RecevoirFich(int sock , char *FichierDestination){
    //printf("reception fichier : %s\n",FichierDestination);
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
                //printf("Vu end of file \n");
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
    //printf("Fin reception\n");
}

