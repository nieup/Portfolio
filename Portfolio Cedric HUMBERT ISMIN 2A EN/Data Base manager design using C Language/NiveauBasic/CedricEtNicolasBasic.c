/*
 * ProjCmainBasic.c
 *
 *  Created on: 4 d�c. 2013
 *      Author: C�dric & Nicolas
 *
 *     Watch out : Il faut desfois entrer un caract�re puis Valider pour passer � la suite (bug am�lior� dans la version  payante du logiciel )
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


/* On cherche � creer une base de donn�e pour la SPA

Elle contient les noms, identifiants, et autres caract�ristiques des annimaux 'enferm�s dans les cages'
On cherche � orienter cette premiere version du projet vers une gestion simple des bases de donn�es, recherche et impl�mentation de fichiers

*/



#define SiHis 100 // Size of the Historic

// Structures invent�es pour l'occasion !!

// On g�n�re un id�ntifiant sigulier � chaque annimal avec les 2 permiere lettres de l'esp�ce ( en minuscule ) et un entier
// qui lui est propre, grandit avec le nombre d'annimaux du centre ( cf void NextId ())

typedef struct{

    char Identc[2];
    int Identi;


}Ident;

// A chaque annimal correspond une structure de la forme suivante :

typedef struct {

    char Etat; // ' ' si il est en vie '*' si il est supprim� ou mort par d�fault il sera donc en vie
    Ident ID;
    char Name[30];
    char Species[20];
    int CellNb;
    int JJ, MM, AA; // Date d'entr�, elle n'est pas modifiable
    char Historique[SiHis]; // On propose � l'utilisateur de renter un description courte de l'animal qui est entr�


}ANIM;

// On g�n�re une en tete qui permet de rentrer un titre et une description. Elle tiens aussi � jours le fichier, date, taille...

typedef struct {

	char Titre[20] ;
	char Descriptif[50] ;
	int LenghtOfEntries ;
	int NumberOfEntries ; // Nombre d'entr� dans la BDD du centre
	int NumberOfEntriesNA ; // Les animaux archiv�s
	int JJe; // Date
	int MMe;
	int AAe;

}EN_TE;


#define TETE sizeof(EN_TE);


void Menu(); // affiche le menu
void NouveauClient(); // Permet d'entrer un nouvel animal dans la base de donn�
void AfficheLaFiche(); // Affiche la fiche d'un animal
void Entrer(ANIM * Animal); // permet de rentrer un nouvel ANIM
void AfficheStruct(ANIM * Current); // Affiche la fiche de l'animal
void RechercherAnimal(); // recherche un animal dans le fichier structure
int NextId(FILE *REPl); // Lit le fichier et renvoi l'identifiant suivant
void AfficheSpa(); // Affiche tout le repertoire
void TurnToLower(char * chaine); // passe une chaine en une chaine de muniscules Nota : utile au niveau avanc� et pas avant
void ModifierClient(); // Permet de modifier un client dans les fichiers
void DeadOrAlive(); // Permet d'archiver (l'Etat) des animaux. Dans la mesure ou ils ne revinnent pas en vie, on ne peut pas les d�sarchiver
int TestDeadOrAlive(ANIM *Current); // permet de tester si l'animal est mort 1 ou en vie 0
void FillHeader(FILE *ToHeader); // Cette fonction est destin�e � remplir le header � la premiere utilistion
void UpDate(FILE *ToHeader); // Cette fonction est destin�e � mettre � jours le Header et le ficher Utilisateur en fin de programme.
void JumpHeader(FILE *ToHeader); // Cette fonction permet lors de l'ouverture d'un fichier de sauter le stack au dessus du header



int main()
{
    // Le main permet d'afficher le menu et de lancer les fonctions propos�es dans le menu
    // Il permet aussi de remplir le Hearder � la premiere utilisation et de le mettre � jour apr�s chaque utilisation ceci est automatique !
    // Il continue en recevant, 'y'

	FILE *ToHeader = NULL;
	ToHeader = fopen("repertoire Structure.txt", "r");

	if (ToHeader == NULL) // Premiere utilisattion, pas encore de base de donn�e
		 FillHeader(ToHeader); // On la cr�e


    char num;
    char Cont = 'y';
    while (Cont == 'y')
    {
        // On ouvre le fichier dans le main
        num = '0';
        do
        {
            Menu();
            scanf(" %c", &num);
            switch (num)
            {
                case '1' : NouveauClient(); break;
                case '2' : RechercherAnimal(); break;
                case '3' : AfficheLaFiche(); AfficheSpa();  break;
                case '4' : ModifierClient(); break;
				case '5' : DeadOrAlive(); break;
				case '6' : break;
                default  : num = '0';  break; // Gestion des mauvaises entr�es
            }

        }while (num != '6' );
        // Interface utilisateur, demande de retour on non :
		  UpDate(ToHeader); // Mise � jour
		  printf("Les fichiers sont � jour\n");
        printf("\n \n \n \n Souhaitez vous continuer dans le menu ? \n");
        printf("Entrez 'y' pour continue\n");
        scanf(" %c", &Cont);
    }


   return 0;
}

void Menu()
{
    // Affiche simplement un Menu
    system("clear");
    printf(" \t \t Bienvenue dans le Menu \n ");
    printf(" \t Entrez le numero correspondant � la ligne souhait�e  \n \n");
    printf("    [1] Entrez un nouveau client \n");
    printf("    [2] Rechercher un client \n");
    printf("    [3] Afficher le contenu des fichiers client \n");
    printf("%7s Modifier un client \n", "[4]"); // 2 types de pr�sentation !
    printf("%7s Archiver un client \n", "[5]");
    printf("%7s Exit & Mise � jour \n", "[6]");

}


void NouveauClient()
{
    // Permet � l'utilisateur de rentrer un nouveau client

    system("clear");  // rafraichissement de la console
    printf("Bienvenue dans la fonction Nouveau client \n");
    ANIM Nouveau;
    char Answer = 'n';
    FILE * REP = NULL; // Le REPertoire est le fichier dans lequel on rentre tous les animaux (mani�e 'GUI')

    FILE * REPstr = NULL; // Le REPstr est le fichier dans lequel on rentre tous les animaux (avec des fwrite())

    REP = fopen("repertoire Utilisateur.txt", "a");
    REPstr = fopen("repertoire Structure.txt", "r+"); // Il est logique d'ouvrire en r, on l'a d�j� test� et initialis�

    if (REP != NULL)
    {
	 if (REPstr != NULL)
        {
        while ( Answer == 'n' && Answer != 'y')// Pour permettre de reboucler et valider le choix de nom
        {
            printf("Vous allez rentrer un nouvel Animal dans le centre.\n Vous allez devoir entrer son nom \n");
            Entrer(&Nouveau); // gestion de la saisit par une sous fonction


				Nouveau.ID.Identc[0] = tolower(Nouveau.Species[0]);
   			Nouveau.ID.Identc[1] = tolower(Nouveau.Species[1]);
   			Nouveau.ID.Identi = NextId(REPstr);
   			if (Nouveau.ID.Identi == 0) printf("l'identifiant g�n�r� est 0 \n ");

            // G�n�ration de la date courante

   			time_t seconde;
   			struct tm instant;
   			time(&seconde);
   			instant = *localtime(&seconde);

   			Nouveau.JJ = instant.tm_mday;
   			Nouveau.MM = instant.tm_mon +1;
   			Nouveau.AA = instant.tm_year + 1900;
   			Nouveau.Etat = ' '; // par d�faut l'annimal est vivant

            // V�rification avec l'utilisateur

            printf("Vous venez d'entrer l'animal suivant, etes vous satifait ? \n");
            printf("Nom : %s \n", Nouveau.Name);
            printf("Ident : %c%c.%d \n", Nouveau.ID.Identc[0],Nouveau.ID.Identc[1],Nouveau.ID.Identi);
            printf("Esp�ce : %s \n", Nouveau.Species);
            printf("Num�ro de cellule : %d \n", Nouveau.CellNb);
            printf("Historique : %s \n", Nouveau.Historique);
            printf("Entrez 'n' pour recommencer, 'y' pour valider \n");
            scanf(" %c",&Answer);
        }

        // Ecriture de l'annimal en m�moire

        fprintf(REP, "***************************** \n ");
        fprintf(REP, "Nom : %s \n", Nouveau.Name);
        fprintf(REP, "Ident : %c%c.%d \n", Nouveau.ID.Identc[0],Nouveau.ID.Identc[1], Nouveau.ID.Identi); // Bug sur cette ligne print ')' entre %s et .
        fprintf(REP, "Espece : %s \n", Nouveau.Species);
        fprintf(REP, "Cage : %d \n", Nouveau.CellNb);
        fprintf(REP, "Historique : %s \n", Nouveau.Historique);
        fprintf(REP, "Date d'entr� : Le %d / %d / %d \n ", Nouveau.JJ, Nouveau.MM, Nouveau.AA);
        fclose(REP);

        // On va enoyer dans le repertoire de structure

            fseek(REPstr, 0,SEEK_END);
            fwrite(&Nouveau,sizeof(Nouveau),1, REPstr); // envoi en fwrite les structures entieres d�j� �crites � la fin du fichier
            fclose(REPstr);
        }
        else
            printf("D�sol� le fichier repertoire str n'a pas pu etre ouvert");


    }
    else
        printf("Le fichier repertoire utilisateur n'a pas pu etre ouvert \n");



}

void Entrer(ANIM *Nouveau) //
{
    char  buffer[SiHis];
    char TamponViST = 'u';
    /* Cette fonction permet de rentrer un nouvel animal dans une structure */
    printf("Entrez le nom de l'animal : \n");
    scanf(" %s", (Nouveau->Name));
    printf("Entrez l'esp�ce de l'animal \n");
    scanf(" %s", (Nouveau->Species));
    printf("Entrez le num�ro de la cage \n");
    scanf(" %d", &(Nouveau->CellNb));
    printf("Entrez l'historique de l'animal : \n ");

    // vide le buffer du stdin car il reste un retour chariot end of EOF
    while(((TamponViST=getchar()) != '\n') && TamponViST != EOF);
    fgets(buffer, SiHis, stdin); // Saisie s�curis�e !

    strcpy((Nouveau->Historique), buffer); // recopie dans le buffer

}


void AfficheLaFiche()
{
    // Cette fonction affiche les annimaux du fichier repertoire Utilisateur.txt
    system("clear");
    printf("Bienvenue dans la fonction AfficheLaFiche \n");
    FILE * REPl = NULL;
    char buffer[300];
    REPl = fopen("repertoire Utilisateur.txt", "r+");
    if (REPl != NULL)
    {
        while (fgets(buffer, 300, REPl) != NULL)
        {
            printf("%s \n", buffer);

        }

        fclose(REPl);
    }
    else
        printf("On n'a pas pu ouvrir le fichier \n");

}

void AfficheStruct(ANIM *Current)
{
	// Affiche la scrtucture qui lui est pass�e

	printf("****************************************************************\n");
	printf("*%30s * %20s * %5d *\n", Current->Name, Current->Species, Current->CellNb);
	printf("* Entr� le %4d / %d / %d   *\n", Current->JJ, Current->MM, Current->AA);
	printf("* Identifiant : %4c%c.%d %36s \n", Current->ID.Identc[0], Current->ID.Identc[1], Current->ID.Identi, "*");
	printf("* %5s *\n", Current->Historique);

	printf("****************************************************************\n");



}

void AfficheSpa()
{	// Rmk : Lit tout le fichier
	char end;
	FILE * REPl;
	ANIM ANIMCourant;
	EN_TE head1;
	REPl = fopen("repertoire Structure.txt", "r+");
	if (REPl != NULL)
	{
	// On affiche le Header aussi :
	fread(&head1, sizeof(EN_TE), 1, REPl);
	printf("Centre %s, le %d / %d / %d \n", head1.Titre, head1.JJe, head1.MMe, head1.AAe);
	printf("Descriptif du centre : %s \n", head1.Descriptif);
	printf("Vous avez %d animaux dans vos locaux \n", head1.NumberOfEntriesNA);
	printf("Vous avez %d animaux qui sont pass�s par votre centre \n", head1.NumberOfEntries);

	// Les fiches sont print�es :
	while(fread(&ANIMCourant, sizeof(ANIM), 1, REPl) !=0)

        {
			if (TestDeadOrAlive(&ANIMCourant) == 0)
				AfficheStruct(&ANIMCourant);
        }
	fclose(REPl);
	}
	else printf("On n'a pas pu ouvrir le fichier \n ");


	scanf(" %c",&end );

}

void RechercherAnimal()
{
	system("clear");
    printf("Bienvenue dans la fonction RechercherAnimal \n");

    // Interface utilisateur :

    FILE * REPl;
    ANIM ANIMCourant;
    int j = 0 ; //interrupteur (trouv� ou pas)
    char NomLu[30]; // Nom Trouv� dans le fichier
    char end;
    REPl = fopen("repertoire Structure.txt", "r");
    if(REPl == NULL) {printf("Echec de la recherche\n"); return;};
    	printf("Entrez le nom de l'animal que vous recherchez :\n");
    	scanf("%s", NomLu);

		JumpHeader(REPl);
    	printf("R�sultats de la recherche : \n");
    	while(fread(&ANIMCourant, sizeof(ANIM), 1, REPl)!=0)
        {
            if(strcmp(NomLu,ANIMCourant.Name)==0)
            {
            j=1;
            printf("Nom : %s\n", ANIMCourant.Name);
            if (TestDeadOrAlive(&ANIMCourant) == 1)
            	printf("Attention cet animal est archiv� \n");
            AfficheStruct(&ANIMCourant);


            }
        }
    if(j!=1)
    	{
    		printf("Votre recherche n'a donn� aucun r�sultat\n");
     	}
    fclose(REPl);
    scanf(" %c", &end);

}

int NextId(FILE *REPl)
{
    // G�n�rateur d'indentifiant

	long int position=0; long int compteur=0;

	fseek(REPl, 0, SEEK_SET); // on se positionne avant le header ce que JumpHeader fait d�ja mais on n'est jamais assez sur
	// passer le header
	JumpHeader(REPl);
	ANIM ANIMCourant;

		while(fread(&ANIMCourant, sizeof(ANIMCourant), 1, REPl)!=0)
        {
            compteur++;

        }

		position=compteur*sizeof(ANIM) + sizeof(EN_TE);
		fseek(REPl, position, SEEK_SET); //On se place juste devant la derni�re structure
		fread(&ANIMCourant, sizeof(ANIM), 1, REPl); //on lit le fichier
		return (ANIMCourant.ID.Identi + 1);



}

void TurnToLower(char * chaine) // totalement fonctionnelle et inutile dans ce programme
{
	printf("vous etes entr� dans la fonction to turn to lower \n ");
	int i = 0;
	while (chaine[i] != '\0')
	{
		chaine[i] = tolower(chaine[i]);
		i++;
	}

}

void ModifierClient()
{
	printf("On va d'abord rechercher le client \n ");
	FILE * REPl;
	    ANIM ANIMCourant;
	    int j = 0 ; //interrupteur (trouv� ou pas)
	    char NomLu[30]; // Nom Trouv� dans le fichier
	    char end;
	    REPl = fopen("repertoire Structure.txt", "r+");
	    if(REPl == NULL) {printf("Echec de la recherche\n"); return;};
	    	printf("Entrez le nom de l'animal que vous recherchez :\n");
	    	scanf("%s", NomLu);

			JumpHeader(REPl);
	    	printf("R�sultats de la recherche : \n");
	    	while(fread(&ANIMCourant, sizeof(ANIM), 1, REPl)!=0)
	        {
	            if(strcmp(NomLu,ANIMCourant.Name)==0)
	            {
	            j=1;
	            printf("Nom : %s\n", ANIMCourant.Name);
	            AfficheStruct(&ANIMCourant);
	            Entrer(&ANIMCourant);
					//JumpHeader(REPl);
	            fseek(REPl, -sizeof(ANIM), SEEK_CUR);
	            fwrite(&ANIMCourant,sizeof(ANIMCourant),1, REPl);
	            fclose(REPl);

	            }
	        }
	    if(j!=1)
	    	{
	    		printf("Votre recherche n'a donn� aucun r�sultat.\n");
	    		printf("Vous ne pourrez donc pas modifier le client\n");
	    		printf("V�rifiez le nom que vous avez entr� \n ");
	    	}

	    printf("Tout c'est bien d�roul� \n ");
	   scanf(" %c", &end); // On attend un caract�re

}

void DeadOrAlive()// (oui c'est une r�f�rence musicale)
{
	printf("On va d'abord rechercher le client \n ");
	FILE * REPl;
	ANIM ANIMCourant;
	int j = 0 ; //interrupteur (trouv� ou pas)
	char NomLu[30]; // Nom Trouv� dans le fichier
	char end, ans;
	REPl = fopen("repertoire Structure.txt", "r+");
	if(REPl == NULL) {printf("Echec de la recherche\n"); return;};
	printf("Entrez le nom de l'animal que vous recherchez :\n");
	scanf("%s", NomLu);

	JumpHeader (REPl);
	printf("R�sultats de la recherche : \n");
	while(fread(&ANIMCourant, sizeof(ANIM), 1, REPl)!=0)
	{
	    if(strcmp(NomLu,ANIMCourant.Name)==0)
	    {
	    	j=1;
	    	printf("Nom : %s\n", ANIMCourant.Name);
		    AfficheStruct(&ANIMCourant);
		    printf("Ceci est l'annimal que vous voulez tuer ? \n entrez 'y' pour oui \n ");
		    scanf(" %c", &ans);
		    if (ans == 'y')
		    {
		       	ANIMCourant.Etat = '*';
		      	fseek(REPl, -sizeof(ANIM), SEEK_CUR);
		       	fwrite(&ANIMCourant,sizeof(ANIMCourant),1, REPl);
		     }
		     else printf("L'animal n'a pas �t� archiv� \n ");

		     fclose(REPl);

		 }
	}
	if(j!=1)
	{
		printf("Votre recherche n'a donn� aucun r�sultat.\n");
		printf("Vous ne pourrez donc pas modifier le client\n");
		printf("V�rifiez le nom que vous avez entr� \n ");
	}

	printf("Tout c'est bien d�roul� \n ");
	scanf(" %c", &end);


}


int TestDeadOrAlive(ANIM *Current)// returns 0 if the animal is not archved, 1 if he is
{
	int i = 0;
	if ((Current->Etat) == '*') i = 1;
	return i;

}

void FillHeader(FILE *ToHeader)
{
	ToHeader = fopen("repertoire Structure.txt", "w");
	if (ToHeader != NULL)
	{
	EN_TE head1;

	printf("Entrez le nom de votre centre :\n");
	fflush(stdin);

	fgets(head1.Titre, 20, stdin);
	printf("Entrez la description de votre table : \n");
	//Here too
	fflush(stdin);
	fgets(head1.Descriptif, 50, stdin);
	head1.LenghtOfEntries = sizeof(ANIM);
	fwrite(&head1, sizeof(EN_TE), 1, ToHeader);

	// On initialise le compteur d'identit� � 1
	ANIM Toto;
	Toto.ID.Identi = 0;
	Toto.Etat = '*';// On initialise le premier comme mort de sorte � ce qu'il ne soit pas affich�
	fwrite(&Toto, sizeof(ANIM), 1, ToHeader);


	fclose(ToHeader);


	}

}

void UpDate(FILE * ToHeader)
{
	ToHeader = fopen("repertoire Structure.txt", "r+");
	EN_TE head1;
	if (&ToHeader != NULL)
	{
	fread(&head1, sizeof(EN_TE), 1, ToHeader);
	time_t seconde;
   struct tm instant;
   time(&seconde);
   instant = *localtime(&seconde);

   head1.JJe = instant.tm_mday;
   head1.MMe = instant.tm_mon + 1;
   head1.AAe = instant.tm_year + 1900;

	//D�termination du nombre d'entr� en soustrayant les animaux archiv�s
	ANIM ANIMCourant;
	int compteur = 0;

	while(fread(&ANIMCourant, sizeof(ANIMCourant), 1, ToHeader)!=0)
   {
		if(TestDeadOrAlive(&ANIMCourant) == 0)
		compteur++;

   }
	head1.NumberOfEntriesNA = compteur;

	head1.NumberOfEntries = NextId(ToHeader) - 1;
	fseek(ToHeader, 0, SEEK_SET);
	fwrite(&head1, sizeof(EN_TE),1, ToHeader);
	printf("EN_TE Structure mise � jour !! \n");
	fclose(ToHeader);
	}
	else printf("pas r�ussi a ouvrir le fichier structure pour mise � jour de l'EN_TE \n");

	ToHeader = fopen("repertoire Utilisateur.txt", "a");
	if (ToHeader != NULL)
	{
	fprintf(ToHeader,"Centre %s \nLe %d / %d / %d \n", head1.Titre, head1.JJe, head1.MMe, head1.AAe);
	fprintf(ToHeader,"Descriptif du centre : %s \n", head1.Descriptif);
	fprintf(ToHeader,"Vous avez %d animaux dans vos locaux \n", head1.NumberOfEntriesNA);
	fclose(ToHeader);
	printf("Le Fichier Utilisateur a �t� mis � jours \n");
	}
	else printf("Il est impossible d'ouvrir le fichier Utilisateur afin de faire la mise � jour");

}


void JumpHeader(FILE *ToHeader)
{
	fseek(ToHeader, 0, SEEK_SET);
	fseek(ToHeader, sizeof(EN_TE), SEEK_SET);

}


