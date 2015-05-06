/*
 * fonctionInterface.h
 *
 *  Created on: 7 déc. 2013
 *      Author: Cedric et Nicolas
 *
 */
#ifndef FONCTIONINTERFACE_H_
#define FONCTIONINTERFACE_H_


void MenuTables(int * Continue); // Affiche le menu

// Pour lancer les valeurs dans le fichier de Gestion

void AfficherBDDInt(); // Lance les modalités d'affichage d'une bdd
/*
Lance : AfficherBDD( &CurrentEN_TETE);
*/

void CreerTableInt(); // Lance les modalités de création de table
/*
Lance : CreerTableBDD( &CurrentEN_TETE, &CurrentEN_TETE);
*/

void SupprimerBDDInt(); // Lance les modalités de Suppression de table
/*
Lance : SupprimerBDD(&CurrentEN_TETE);
Qui doit supprimer la base de donné
*/


int GenerateLengthRecord( EN_TETE * CurHead); // Fonction qui renvoi la longueur des records en fonction du nombre de colone et de leur type
/*
Renvoi le nombre correspondant, ce devrait etre un long int pour la fonction fseek mais un int nous est suffiant
*/



void AjoutDansTableDeColone (); // Ajoute dans une table une colonne NON FONCTIONEL
/*
Ne Marche pas
*/

void ModificationDansTable (); // Ajoute un enregistrement au bout du fichier data
/*
Appel les FillEntry...
Qui sont les foncions de saisie et d'appel des fonctions qui vont elle entrer dans la base de donnée
*/

void FillEntryFloat(EN_TETE CurTab, char * CurColName); // Envoi à la fonction FillEntryFloatBDD() un float en plus de ce quelle a déjà et l'index sur lequel écrire , 0 si à la suite
void FillEntryBool(EN_TETE CurTab, char * CurColName); // Envoi à la fonction FillEntryBoolBDD() un bool en plus de ce quelle a déjà et l'index sur lequel écrire , 0 si à la suite
void FillEntryInt(EN_TETE CurTab, char * CurColName); // Envoi à la fonction FillEntryIntBDD() un int en plus de ce quelle a déjà et l'index sur lequel écrire , 0 si à la suite
void FillEntryChar(EN_TETE CurTab, char * CurColName); // Envoi à la fonction FillEntrycharBDD() un char * en plus de ce quelle a déjà et l'index sur lequel écrire , 0 si à la suite






void SelectRecherche (); // Demande à l'utilisateur ce qu'il souhaite rechercher
/*
Appel les SearchEntry
*/
void SearchEntryFloat(EN_TETE * Head, char ColTy);// Envoi à la fonction FillEntryFloatBDD()
void SearchEntryBool(EN_TETE * Head, char ColTy);// Envoi à la fonction FillEntryBoolBDD()
void SearchEntryInt(EN_TETE * Head, char ColTy);// Envoi à la fonction FillEntryIntBDD()
void SearchEntryChar(EN_TETE * Head, char ColTy);// Envoi à la fonction FillEntrycharBDD()






void AfficherTouteLaBDD();
/*
Affiche tout ce qui est dans le fichier de Header
*/


void SuppressionDansUneTable ();
/*
Supprime un enregistrement dans la table
*/
void DeleteEntryFloat( EN_TETE * Head, char ColTy );
void DeleteEntryBool ( EN_TETE * Head, char ColTy );
void DeleteEntryInt ( EN_TETE * Head, char ColTy );
void DeleteEntryChar ( EN_TETE * Head, char ColTy );


// Fichier contenant les fonctions relatives à la gestion des BDD
#include "fonctionGestionBDD.h"



/****************** * MENU * ***********************/

void MenuTables(int * Choisit) // Affiche le menu, lance les fonctions
{
// Boucle
do
{
	system("clear");

	printf("[1] Visualiser une base de données\n");
	printf("[2] Ajouter une base de données\n");
	printf("[3] Supprimer une base de données\n");
	printf("[4] Modifier une Base de Données\n");
	printf("[5] Ajouter des enregistrements\n");
	printf("[6] Selectionner Recherche\n");
	printf("[7] Afficher toute les bases de donnée\n");
	printf("[8] Supprimer dans une table \n");
	printf("[9] Quitter le programme\n");
	scanf(" %d", Choisit);

	switch(*Choisit)
	{
		case 1 : {AfficherBDDInt(); break;} //va afficher la base de données à afficher // on ne fais pas que d'afficher ! on peut aussi la tripoter !
		case 2 : {CreerTableInt(); break;} //va créer puis ajouter une table
		case 3 : {SupprimerBDDInt(); break;} // Supprime le fichier de donné et passe un * à l'état dans le Header
		case 4 : {AjoutDansTableDeColone (); break;} // Va proposer d'ajouter un table, à quelle bdd et entrer table
		case 5 : {ModificationDansTable (); break;} // Demande la table à modifier et la colone, passe ce qui est à entrer dedans
		case 6 : {SelectRecherche (); break;} // Envoi une table et une colone à chercher
		case 7 : {AfficherTouteLaBDD(); break;}; // Affiche toute la base de donnée
		case 8 : {SuppressionDansUneTable(); break;} // Supprime dans une base de donné l'enregistrement ou la colone
		case 9 : break;
		default: {printf("Mauvaise entré"); ToWait(); break;} // La selection reste sur ce qui avait été choisit avant c'est pratique
     }

}
while( *Choisit != 9);
}

/****************** * AFFICHEUR * ********************/

void AfficherBDDInt()
{
	EN_TETE CurrentHEAD;
    printf("Bienvenue dans l'afficheur de table Int\n");
    printf("Entrez le nom de la table que vous souhaitez afficher : ");
    scanf(" %s", CurrentHEAD.NomTable);
    TurnToLower(CurrentHEAD.NomTable);
    // On passe le nom de la Table à rechercher
    AfficherBDD( &CurrentHEAD);


}

/***************** * Interface création de Table * *************/

void CreerTableInt()
{
    // Permet d'entrer une Table et une entete, génére les donnée à mettre automatiquement
    // On a la strucutre de table qui est obsolette du coup :(
	EN_TETE CurrentEN_TETE;
	COL CurrentCOL;
	char NomFichier[32];
	int j = 1;// Compteur pour les colones

    printf("Bienvenue dans le créateur de table Int\n");
    printf("Entrez le nom de la Table que vous souhaitez créer : ");
	 // Ne marche toujours pas ...
	 //fflush(stdin);
    //gets(CurrentEN_TETE.NomTable); // Faire attention aux espaces !
	scanf(" %s", CurrentEN_TETE.NomTable);
	if (TesterPresenceTABLE(CurrentEN_TETE.NomTable) == 0) // test l'existance de la table en mémoire
    {
        strcpy(NomFichier, CurrentEN_TETE.NomTable);
        strcat(NomFichier, ".txt"); // Nom du fichier et nom de repertoire généré
		  // Mise à jour de l'heure
        time_t seconde;
        struct tm instant;
   	  time(&seconde);
   	  instant = *localtime(&seconde);

   	  CurrentEN_TETE.DD = instant.tm_mday;
   	  CurrentEN_TETE.MM = instant.tm_mon + 1;
        CurrentEN_TETE.YY = instant.tm_year + 1900;


    printf("Vous avez entré : %s \n",NomFichier);

    // On remplit l'EN_TETE:


    printf("Entrez le nombre de colone que vous souhaitez dans votre Table : ");
    scanf(" %d", &(CurrentEN_TETE.NbMaxCol));
    CurrentEN_TETE.NbMaxCol = ChoixDeNb(MaxCol, CurrentEN_TETE.NbMaxCol); // Vérifie que le le nombre de colonnes entré est bien inférieur au nombre max
	 printf("Vous avez choisit : %d \n", CurrentEN_TETE.NbMaxCol); // Information utilisateur
    // Remplissage des tetes de colone
    for ( j = 1; j <= (CurrentEN_TETE.NbMaxCol); j++ )
    {
        printf("Entrez le Nom de la colone %d: ", j); // On utilise une colonne de buffer
		  scanf(" %s", CurrentCOL.NomColonne);
        CurrentCOL.TypeColonne = TypeDeCol(); // test du type de la colonne
        (CurrentCOL.TailleColonne) = sizeof(COL);
        CurrentEN_TETE.TabCol[j] = CurrentCOL; // On remet dans l'entete la colonne crée
    }
    CurrentEN_TETE.NbRecord = 0; // Initialisation des records

    CurrentEN_TETE.LengthRecord = CalculeLengthRecord( &CurrentEN_TETE); // fonctions qui fait la somme de toutes les parties d'un enregistrement
    CurrentEN_TETE.LengthHeader = sizeof(CurrentEN_TETE); // Il faut bien prendre en compte les colones

	 CurrentEN_TETE.Etat = ' ';

    // rentrer tout ca dans le gestionnaire de BDD
    CreerTableBDD( NomFichier, &CurrentEN_TETE); // ATTENTION on n'a plus de Table
    }
    else {printf("Cette Table existe déjà ! \n"); ToWait();}


}

/****************** * Supression de BDD * **********************/

void SupprimerBDDInt()
{
    EN_TETE CurrentEN_TETE; // Attention passer à une EN_TETE
	 char answer;
    printf("Bienvenue dans le supprimeur de table Int\n");
    printf("Entrez le Nom de la table que vous souhaitez supprimer : ");

	scanf(" %s", CurrentEN_TETE.NomTable);
	//TurnToLower(CurrentEN_TETE.NomTable);
	if (TesterPresenceTABLE(CurrentEN_TETE.NomTable) == 1)
	{
    // On passe le nom de la Table à rechercher en lowercase !
    printf("Etes vous bien sur de vouloir éffacer la table %s ? ", CurrentEN_TETE.NomTable);

	 scanf(" %c", &answer);
    if (answer == 'y')
    {
        SupprimerBDD(&CurrentEN_TETE); // Attention passage table il faut passer une entete
        printf("La table a bien été supprimée \n");
    }
		else {printf("La table n'a pas été supprimée\n");}
	}
	else {printf("La table n'éxiste pas \n");}

    ToWait();
}


/******************* * Modification des tables * *********************/

void AjoutDansTableDeColone () // Méga Crash ! Tout le code a été placé en commentaire
 {
     EN_TETE CurrentEN_TETE; // Pas une Table
    printf("Bienvenue dans le créateur de table Int\n");
    printf("Entrez le nom de la Table que vous souhaitez modifier : ");
    scanf(" %s",CurrentEN_TETE.NomTable);
    if (TesterPresenceTABLE(CurrentEN_TETE.NomTable) == 1)
    {
        COL CurrentCOL;
        printf("Entrez le Nom de la Nouvelle colone : ");
        scanf(" %s",CurrentCOL.NomColonne);
        CurrentCOL.TypeColonne = TypeDeCol();
        AjoutDansTableDeColoneBDD(&CurrentEN_TETE, &CurrentCOL); // Cette fonction CRASH
        printf("La Colonne a bien été ajoutée \n");
        ToWait();
    }
    else {printf("Cette table n'éxiste pas \n"); ToWait();}
 }

/******************* * Modification dans les tables * ***************/

void ModificationDansTable () // Ajout de nouvel enregistrement
{
    EN_TETE CurrentTABLE, Headlu;

	int i ; // compteur pour les colonnes
	int CMP = 0;

    printf("Bienvenue dans le gestionnaire de colone Int : \n");
    printf("Entrez le nom de la Table que vous souhaitez modifier : \n");

	scanf(" %s", CurrentTABLE.NomTable);
    i = TesterPresenceTABLE(CurrentTABLE.NomTable); // Pour etre sur

    if (i != 0) // test l'existance de la table en mémoire
    {
        // Mise en jour de l'enregistrement dans le fichier de HEADER
		CreateEnregistrementVierge(&CurrentTABLE);

		FILE * FreeSpaSGBD = NULL ;
		FreeSpaSGBD = fopen("FreeSpaSGBD.txt", "r+");
		if (FreeSpaSGBD !=  NULL)
    	{
        while(fread(&Headlu, sizeof(EN_TETE), 1, FreeSpaSGBD) != 0 && CMP == 0)
        {
				TurnToLower(Headlu.NomTable);

            if ( strcmp(Headlu.NomTable,CurrentTABLE.NomTable) == 0 && Headlu.Etat != '*' )
            {
					 CMP = 1;
                Headlu.NbRecord = CurrentTABLE.NbRecord; // On incrémente le nombre de record
					 fseek(FreeSpaSGBD, -sizeof(EN_TETE), SEEK_CUR);
					 fwrite(&Headlu, sizeof(EN_TETE), 1, FreeSpaSGBD);

				}
        }
	fclose(FreeSpaSGBD);

		for (i = 1 ; i <= Headlu.NbMaxCol ; i++)
	{

		printf("Vous allez modifier la colonne %s entrez votre element. \n", Headlu.TabCol[i].NomColonne);

        switch (Headlu.TabCol[i].TypeColonne)
    {
       case 'f' : {FillEntryFloat(Headlu, Headlu.TabCol[i].NomColonne); break;}
       case 'b' : {FillEntryBool(Headlu, Headlu.TabCol[i].NomColonne); break;}
       case 'e' : {FillEntryInt(Headlu, Headlu.TabCol[i].NomColonne) ; break;}
       case 'c' : {FillEntryChar(Headlu, Headlu.TabCol[i].NomColonne); break;}
    }



	 }// Fin de boucle entré de l'enregistrement



    printf("Votre donnée a bien été changée !\n");
    ToWait();

    }
	 else {printf(" Could not open header file ! \n"); }

	}
	else {printf("Cette table n'éxiste pas \n"); ToWait();}
}

void FillEntryFloat(EN_TETE CurTab, char * CurColName) // On écrit à la suite dans la collone spécifié si 'ToTheEnd' = 0 sur sa valeur si non enfin on essai
{
    float data;
    int ToTheEnd = 0;
	 /* Cette fonctionnalité n'est pas opérationnelle, on écrit toujours sur la dernière ligne, on ne peut pas remplacer des valeurs
    printf("Dans quelle enregistrement souhaitez vous l'écrire (0 à la suite)?\n");
    printf("Entrez l'index de l'enregistrement que vous souhaitez modifier :\n");
    scanf(" %d", &ToTheEnd);
	 */
    printf("Entrez la donné à enregistrer : ");
    scanf(" %f", &data);
    FillEntryFloatBDD(CurTab, CurColName, data, ToTheEnd);

}

void FillEntryBool(EN_TETE CurTab, char * CurColName)
{
    int data;
    int ToTheEnd = 0;
	 /* Cette fonctionnalité n'est pas opérationnelle, on écrit toujours sur la dernière ligne, on ne peut pas remplacer des valeurs
    printf("Dans quelle enregistrement souhaitez vous l'écrire (0 à la suite)?\n");
    printf("Entrez l'index de l'enregistrement que vous souhaitez modifier :\n");
    scanf(" %d", &ToTheEnd);
	 */
    printf("Entrez la donné à enregistrer : ");
    scanf(" %d", &data);
    FillEntryBoolBDD(CurTab, CurColName, data, ToTheEnd);
}

void FillEntryInt(EN_TETE CurTab, char * CurColName)
{
    int data;
    int ToTheEnd = 0;
	 /* Cette fonctionnalité n'est pas opérationnelle, on écrit toujours sur la dernière ligne, on ne peut pas remplacer des valeurs
    printf("Dans quelle enregistrement souhaitez vous l'écrire (0 à la suite)?\n");
    printf("Entrez l'index de l'enregistrement que vous souhaitez modifier :\n");
    scanf(" %d", &ToTheEnd);
	 */
    printf("Entrez la donné à enregistrer : ");
    scanf(" %d", &data);
    FillEntryIntBDD(CurTab, CurColName, data, ToTheEnd);

}

void FillEntryChar(EN_TETE CurTab, char * CurColName)
{
    char data[32];
    int ToTheEnd = 0;
	 /* Cette fonctionnalité n'est pas opérationnelle, on écrit toujours sur la dernière ligne, on ne peut pas remplacer des valeurs
    printf("Dans quelle enregistrement souhaitez vous l'écrire (0 à la suite)?\n");
    printf("Entrez l'index de l'enregistrement que vous souhaitez modifier :\n");
    scanf(" %d", &ToTheEnd);
    */
	 printf("Entrez la donné à enregistrer : ");
    scanf(" %s", data);
    FillEntryCharBDD(CurTab, CurColName, data, ToTheEnd);

}



/************* * Affiche toute la BDD * ****************/

void AfficherTouteLaBDD() // Affiche la totalité du fichier de headers
{
    printf("Bienvenue dans AfficherTouteLaBDD \n ");
    FILE * FreeSpaSGBD = NULL ;
    int CurcerPosition = 0 ;
    EN_TETE Head;
	 FreeSpaSGBD = fopen("FreeSpaSGBD.txt", "r");
	 if (FreeSpaSGBD != NULL)
    {

        fseek(FreeSpaSGBD, CurcerPosition, SEEK_SET);

			while(fread(&Head, sizeof(EN_TETE), 1, FreeSpaSGBD) != 0 ) // Je sais pas trop il fait un size of Head qu'il est en train de lire ou de celle d'avant mais c'est in bonne question
        {
				if (Head.Etat !='*') // On vérifie l'état de la bd !
				{
            AfficheHead(&Head);
            printf("\n");
            CurcerPosition = CurcerPosition + sizeof(EN_TETE);
            fseek(FreeSpaSGBD, CurcerPosition, SEEK_SET);
				}
        }
		fclose(FreeSpaSGBD);
     }
     else {printf("ERREUR 85 : Could not open the header file, too bad ! \n");}

     ToWait();
}

/*************** * Recherche * *******************************/

void SelectRecherche () // Demande une recherche dans la Table
{// Avec un mot clé que l'on recherche à coups de fread() ( faire attention à la taille et en lancer plusieurs


    EN_TETE CurrentTABLE, Headlu;
	 int CMP = 0;
    printf("Bienvenue dans le gestionnaire de colone Int \n");
    printf("Entrez le nom de la Table dans laquelle vous souhaitez rechercher : ");
    scanf(" %s", CurrentTABLE.NomTable); // Le nom de la table est le nom du repertoire Faire attention aux espaces !
    if (TesterPresenceTABLE(CurrentTABLE.NomTable) == 1) // test l'existance de la table en mémoire
    {
		// On cherche la table dans le fichier de header
		FILE * FreeSpaSGBD = NULL ;
		FreeSpaSGBD = fopen("FreeSpaSGBD.txt", "r+");
		if (FreeSpaSGBD !=  NULL)
    	{
        while(fread(&Headlu, sizeof(EN_TETE), 1, FreeSpaSGBD) != 0 && CMP == 0)
        {
				TurnToLower(CurrentTABLE.NomTable);

            if ( strcmp(Headlu.NomTable,CurrentTABLE.NomTable) == 0 && Headlu.Etat != '*' )
            {
					 CMP = 1;

				}
        }
	     fclose(FreeSpaSGBD);
        char ColTy;
        ColTy = TypeDeCol();
        switch (ColTy)
    {
       case 'f' : {SearchEntryFloat(&Headlu, ColTy); break;}
       case 'b' : {SearchEntryBool(&Headlu, ColTy); break;}
       case 'e' : {SearchEntryInt(&Headlu, ColTy) ; break;}
       case 'c' : {SearchEntryChar(&Headlu, ColTy); break;}

    }
    }
	 }
    else {printf("Cette table n'éxiste pas \n"); ToWait();}
}

void SearchEntryFloat(EN_TETE * Head, char ColTy)
{
    float ToSearchFor;
    int ToPosition;
    printf("Entrez le réel que vous souhaitez rechercher : ");
    scanf(" %f", &ToSearchFor);
    // Doit renvoyer la position dans le fichier de la donné recherchée
    ToPosition = SearchEntryFloatBDD(Head, ColTy, ToSearchFor);

    if (ToPosition != -1)
	{
	FILE * FileToread = NULL;

	// On recherche la table

	char FileName[36];
	strcpy(FileName, 	Head->NomTable);
	strcat(FileName, ".txt");
	printf("%s \n", FileName);
	FileToread = fopen(FileName, "r");
	if (FileToread != 0)
	{
		afficherRecord (FileToread, Head, ToPosition);
		fclose(FileToread);
	}
	else {printf(" ERROR 35 : Could not open data file \n"); }
	}
	else {printf(" Cette entré n'existe pas dans la table \n"); }
	ToWait();
}

void SearchEntryBool(EN_TETE * Head, char ColTy)
{
    int ToSearchFor;
    int ToPosition;
    printf("Entrez le Booléen que vous souhaitez rechercher : ");
    scanf(" %d", &ToSearchFor);
    // Doit renvoyer la position dans le fichier de la donné recherchée
    ToPosition = SearchEntryBoolBDD(Head, ColTy, ToSearchFor);

    if (ToPosition != -1)
	{
	FILE * FileToread = NULL;

	// On recherche la table

	char FileName[36];
	strcpy(FileName, 	Head->NomTable);
	strcat(FileName, ".txt");
	printf("%s \n", FileName);
	FileToread = fopen(FileName, "r");
	if (FileToread != 0)
	{
		afficherRecord (FileToread, Head, ToPosition);
		fclose(FileToread);
	}
	else {printf(" ERROR 35 : Could not open data file \n"); }
	}
	else {printf(" Cette entré n'existe pas dans la table \n"); }
	ToWait();
}

void SearchEntryInt(EN_TETE * Head, char ColTy)
{
	 int ToSearchFor;
    int ToPosition;
    printf("Entrez l'entier que vous souhaitez rechercher : ");
    scanf(" %d", &ToSearchFor);
    // Doit renvoyer la position dans le fichier de la donné recherchée
    ToPosition = SearchEntryIntBDD(Head, ColTy, ToSearchFor);

    if (ToPosition != -1)
	{
	FILE * FileToread = NULL;

	// On recherche la table

	char FileName[36];
	strcpy(FileName, 	Head->NomTable);
	strcat(FileName, ".txt");
	printf("%s \n", FileName);
	FileToread = fopen(FileName, "r");
	if (FileToread != 0)
	{
		afficherRecord (FileToread, Head, ToPosition);
		fclose(FileToread);
	}
	else {printf(" ERROR 35 : Could not open data file \n"); }
	}
	else {printf(" Cette entré n'existe pas dans la table \n"); }
	ToWait();
}

void SearchEntryChar(EN_TETE * Head, char ColTy)
{
    char ToSearchFor[32];
	 TurnToLower(ToSearchFor);
    int ToPosition;
    printf("Entrez l'entier que vous souhaitez rechercher : ");
    scanf(" %s", ToSearchFor);
    // Doit renvoyer la position dans le fichier de la donné recherchée
    ToPosition = SearchEntryCharBDD(Head, ColTy, ToSearchFor);

    if (ToPosition != -1)
	{
	FILE * FileToread = NULL;

	// On recherche la table

	char FileName[36];
	strcpy(FileName, 	Head->NomTable);
	strcat(FileName, ".txt");
	printf("%s \n", FileName);
	FileToread = fopen(FileName, "r");
	if (FileToread != 0)
	{
		afficherRecord (FileToread, Head, ToPosition);
		fclose(FileToread);
	}
	else {printf(" ERROR 35 : Could not open data file \n"); }
	}
	else {printf(" Cette entré n'existe pas dans la table \n"); }
	ToWait();
}

/******************** * SUPPRESSION DANS UNE TABLE * **********************/

void SuppressionDansUneTable()
{

	 EN_TETE CurrentTABLE, Headlu;
	 int CMP = 0;
    printf("Bienvenue dans le gestionnaire de suppression dans une table  : \n");
    printf("Entrez le nom de la Table dans laquelle vous souhaitez supprimer : ");
    scanf(" %s", CurrentTABLE.NomTable); // Le nom de la table est le nom du repertoire Faire attention aux espaces !
    if (TesterPresenceTABLE(CurrentTABLE.NomTable) == 1) // test l'existance de la table en mémoire
    {
		  // On charge la bonne EN_TETE en mémoire
		  FILE * FreeSpaSGBD = NULL ;
		  FreeSpaSGBD = fopen("FreeSpaSGBD.txt", "r+");
		  while(fread(&Headlu, sizeof(EN_TETE), 1, FreeSpaSGBD) != 0 && CMP == 0)
        {
				TurnToLower(CurrentTABLE.NomTable);

            if ( strcmp(Headlu.NomTable,CurrentTABLE.NomTable) == 0 && Headlu.Etat != '*' )
            {
					 CMP = 1;

				}
        }
	     fclose(FreeSpaSGBD);
        char ColTy;
        ColTy = TypeDeCol();
        switch (ColTy)
    {
       case 'f' : {DeleteEntryFloat(&Headlu, ColTy); break;}
       case 'b' : {DeleteEntryBool(&Headlu, ColTy); break;}
       case 'e' : {DeleteEntryInt(&Headlu, ColTy) ; break;}
       case 'c' : {DeleteEntryChar(&Headlu, ColTy); break;}

    }

    }
    else {printf("Cette table n'éxiste pas \n"); }

	ToWait();
}

void DeleteEntryFloat( EN_TETE * Head, char ColTy )
{
    float ToSearchFor;
	 int ToPosition;
    printf("Entrez le réel que vous souhaitez supprimer : ");
    scanf(" %f", &ToSearchFor);

    ToPosition = SearchEntryFloatBDD(Head, ColTy, ToSearchFor);
    if (ToPosition != -1)
	 {
		DeleteEntryFloatBDD(Head, ToPosition );
	 }
	 else {printf("Nous n'avons pas trouvé la donné que vous souhaitez changer"); }

    ToWait();

}

void DeleteEntryBool ( EN_TETE * Head, char ColTy )
{
    int ToSearchFor;
	 int ToPosition;
    printf("Entrez le booléen que vous souhaitez supprimer : ");
    scanf(" %d", &ToSearchFor);

	 ToPosition = SearchEntryBoolBDD(Head, ColTy, ToSearchFor);
    if (ToPosition != -1)
	 {
		DeleteEntryBoolBDD(Head, ToPosition);
	 }
	 else {printf("Nous n'avons pas trouvé la donné que vous souhaitez changer"); }
}

void DeleteEntryInt ( EN_TETE * Head, char ColTy )
{
    int ToSearchFor;
	 int ToPosition;
    printf("Entrez le réel que vous souhaitez supprimer : ");
    scanf(" %d", &ToSearchFor);
    ToPosition = SearchEntryIntBDD(Head, ColTy, ToSearchFor);
    if (ToPosition != -1)
	 {
		DeleteEntryIntBDD(Head, ToPosition);
	 }
	 else {printf("Nous n'avons pas trouvé la donné que vous souhaitez changer"); }
}

void DeleteEntryChar ( EN_TETE * Head, char ColTy )
{
    char ToSearchFor[32];
	 int ToPosition;
    printf("Entrez les caractères que vous souhaitez supprimer : ");
    scanf(" %s", ToSearchFor);
    TurnToLower(ToSearchFor); // passé en lower case !
    ToPosition = SearchEntryCharBDD(Head, ColTy, ToSearchFor);
    if (ToPosition != -1)
	 {
		DeleteEntryCharBDD(Head, ToPosition);
	 }
	 else {printf("Nous n'avons pas trouvé la donné que vous souhaitez changer"); }


}





#endif /* FONCTIONINTERFACE_H_ */



