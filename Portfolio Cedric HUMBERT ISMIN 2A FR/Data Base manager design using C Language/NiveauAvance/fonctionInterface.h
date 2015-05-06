/*
 * fonctionInterface.h
 *
 *  Created on: 7 d�c. 2013
 *      Author: Cedric et Nicolas
 *
 */
#ifndef FONCTIONINTERFACE_H_
#define FONCTIONINTERFACE_H_


void MenuTables(int * Continue); // Affiche le menu

// Pour lancer les valeurs dans le fichier de Gestion

void AfficherBDDInt(); // Lance les modalit�s d'affichage d'une bdd
/*
Lance : AfficherBDD( &CurrentEN_TETE);
*/

void CreerTableInt(); // Lance les modalit�s de cr�ation de table
/*
Lance : CreerTableBDD( &CurrentEN_TETE, &CurrentEN_TETE);
*/

void SupprimerBDDInt(); // Lance les modalit�s de Suppression de table
/*
Lance : SupprimerBDD(&CurrentEN_TETE);
Qui doit supprimer la base de donn�
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
Qui sont les foncions de saisie et d'appel des fonctions qui vont elle entrer dans la base de donn�e
*/

void FillEntryFloat(EN_TETE CurTab, char * CurColName); // Envoi � la fonction FillEntryFloatBDD() un float en plus de ce quelle a d�j� et l'index sur lequel �crire , 0 si � la suite
void FillEntryBool(EN_TETE CurTab, char * CurColName); // Envoi � la fonction FillEntryBoolBDD() un bool en plus de ce quelle a d�j� et l'index sur lequel �crire , 0 si � la suite
void FillEntryInt(EN_TETE CurTab, char * CurColName); // Envoi � la fonction FillEntryIntBDD() un int en plus de ce quelle a d�j� et l'index sur lequel �crire , 0 si � la suite
void FillEntryChar(EN_TETE CurTab, char * CurColName); // Envoi � la fonction FillEntrycharBDD() un char * en plus de ce quelle a d�j� et l'index sur lequel �crire , 0 si � la suite






void SelectRecherche (); // Demande � l'utilisateur ce qu'il souhaite rechercher
/*
Appel les SearchEntry
*/
void SearchEntryFloat(EN_TETE * Head, char ColTy);// Envoi � la fonction FillEntryFloatBDD()
void SearchEntryBool(EN_TETE * Head, char ColTy);// Envoi � la fonction FillEntryBoolBDD()
void SearchEntryInt(EN_TETE * Head, char ColTy);// Envoi � la fonction FillEntryIntBDD()
void SearchEntryChar(EN_TETE * Head, char ColTy);// Envoi � la fonction FillEntrycharBDD()






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


// Fichier contenant les fonctions relatives � la gestion des BDD
#include "fonctionGestionBDD.h"



/****************** * MENU * ***********************/

void MenuTables(int * Choisit) // Affiche le menu, lance les fonctions
{
// Boucle
do
{
	system("clear");

	printf("[1] Visualiser une base de donn�es\n");
	printf("[2] Ajouter une base de donn�es\n");
	printf("[3] Supprimer une base de donn�es\n");
	printf("[4] Modifier une Base de Donn�es\n");
	printf("[5] Ajouter des enregistrements\n");
	printf("[6] Selectionner Recherche\n");
	printf("[7] Afficher toute les bases de donn�e\n");
	printf("[8] Supprimer dans une table \n");
	printf("[9] Quitter le programme\n");
	scanf(" %d", Choisit);

	switch(*Choisit)
	{
		case 1 : {AfficherBDDInt(); break;} //va afficher la base de donn�es � afficher // on ne fais pas que d'afficher ! on peut aussi la tripoter !
		case 2 : {CreerTableInt(); break;} //va cr�er puis ajouter une table
		case 3 : {SupprimerBDDInt(); break;} // Supprime le fichier de donn� et passe un * � l'�tat dans le Header
		case 4 : {AjoutDansTableDeColone (); break;} // Va proposer d'ajouter un table, � quelle bdd et entrer table
		case 5 : {ModificationDansTable (); break;} // Demande la table � modifier et la colone, passe ce qui est � entrer dedans
		case 6 : {SelectRecherche (); break;} // Envoi une table et une colone � chercher
		case 7 : {AfficherTouteLaBDD(); break;}; // Affiche toute la base de donn�e
		case 8 : {SuppressionDansUneTable(); break;} // Supprime dans une base de donn� l'enregistrement ou la colone
		case 9 : break;
		default: {printf("Mauvaise entr�"); ToWait(); break;} // La selection reste sur ce qui avait �t� choisit avant c'est pratique
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
    // On passe le nom de la Table � rechercher
    AfficherBDD( &CurrentHEAD);


}

/***************** * Interface cr�ation de Table * *************/

void CreerTableInt()
{
    // Permet d'entrer une Table et une entete, g�n�re les donn�e � mettre automatiquement
    // On a la strucutre de table qui est obsolette du coup :(
	EN_TETE CurrentEN_TETE;
	COL CurrentCOL;
	char NomFichier[32];
	int j = 1;// Compteur pour les colones

    printf("Bienvenue dans le cr�ateur de table Int\n");
    printf("Entrez le nom de la Table que vous souhaitez cr�er : ");
	 // Ne marche toujours pas ...
	 //fflush(stdin);
    //gets(CurrentEN_TETE.NomTable); // Faire attention aux espaces !
	scanf(" %s", CurrentEN_TETE.NomTable);
	if (TesterPresenceTABLE(CurrentEN_TETE.NomTable) == 0) // test l'existance de la table en m�moire
    {
        strcpy(NomFichier, CurrentEN_TETE.NomTable);
        strcat(NomFichier, ".txt"); // Nom du fichier et nom de repertoire g�n�r�
		  // Mise � jour de l'heure
        time_t seconde;
        struct tm instant;
   	  time(&seconde);
   	  instant = *localtime(&seconde);

   	  CurrentEN_TETE.DD = instant.tm_mday;
   	  CurrentEN_TETE.MM = instant.tm_mon + 1;
        CurrentEN_TETE.YY = instant.tm_year + 1900;


    printf("Vous avez entr� : %s \n",NomFichier);

    // On remplit l'EN_TETE:


    printf("Entrez le nombre de colone que vous souhaitez dans votre Table : ");
    scanf(" %d", &(CurrentEN_TETE.NbMaxCol));
    CurrentEN_TETE.NbMaxCol = ChoixDeNb(MaxCol, CurrentEN_TETE.NbMaxCol); // V�rifie que le le nombre de colonnes entr� est bien inf�rieur au nombre max
	 printf("Vous avez choisit : %d \n", CurrentEN_TETE.NbMaxCol); // Information utilisateur
    // Remplissage des tetes de colone
    for ( j = 1; j <= (CurrentEN_TETE.NbMaxCol); j++ )
    {
        printf("Entrez le Nom de la colone %d: ", j); // On utilise une colonne de buffer
		  scanf(" %s", CurrentCOL.NomColonne);
        CurrentCOL.TypeColonne = TypeDeCol(); // test du type de la colonne
        (CurrentCOL.TailleColonne) = sizeof(COL);
        CurrentEN_TETE.TabCol[j] = CurrentCOL; // On remet dans l'entete la colonne cr�e
    }
    CurrentEN_TETE.NbRecord = 0; // Initialisation des records

    CurrentEN_TETE.LengthRecord = CalculeLengthRecord( &CurrentEN_TETE); // fonctions qui fait la somme de toutes les parties d'un enregistrement
    CurrentEN_TETE.LengthHeader = sizeof(CurrentEN_TETE); // Il faut bien prendre en compte les colones

	 CurrentEN_TETE.Etat = ' ';

    // rentrer tout ca dans le gestionnaire de BDD
    CreerTableBDD( NomFichier, &CurrentEN_TETE); // ATTENTION on n'a plus de Table
    }
    else {printf("Cette Table existe d�j� ! \n"); ToWait();}


}

/****************** * Supression de BDD * **********************/

void SupprimerBDDInt()
{
    EN_TETE CurrentEN_TETE; // Attention passer � une EN_TETE
	 char answer;
    printf("Bienvenue dans le supprimeur de table Int\n");
    printf("Entrez le Nom de la table que vous souhaitez supprimer : ");

	scanf(" %s", CurrentEN_TETE.NomTable);
	//TurnToLower(CurrentEN_TETE.NomTable);
	if (TesterPresenceTABLE(CurrentEN_TETE.NomTable) == 1)
	{
    // On passe le nom de la Table � rechercher en lowercase !
    printf("Etes vous bien sur de vouloir �ffacer la table %s ? ", CurrentEN_TETE.NomTable);

	 scanf(" %c", &answer);
    if (answer == 'y')
    {
        SupprimerBDD(&CurrentEN_TETE); // Attention passage table il faut passer une entete
        printf("La table a bien �t� supprim�e \n");
    }
		else {printf("La table n'a pas �t� supprim�e\n");}
	}
	else {printf("La table n'�xiste pas \n");}

    ToWait();
}


/******************* * Modification des tables * *********************/

void AjoutDansTableDeColone () // M�ga Crash ! Tout le code a �t� plac� en commentaire
 {
     EN_TETE CurrentEN_TETE; // Pas une Table
    printf("Bienvenue dans le cr�ateur de table Int\n");
    printf("Entrez le nom de la Table que vous souhaitez modifier : ");
    scanf(" %s",CurrentEN_TETE.NomTable);
    if (TesterPresenceTABLE(CurrentEN_TETE.NomTable) == 1)
    {
        COL CurrentCOL;
        printf("Entrez le Nom de la Nouvelle colone : ");
        scanf(" %s",CurrentCOL.NomColonne);
        CurrentCOL.TypeColonne = TypeDeCol();
        AjoutDansTableDeColoneBDD(&CurrentEN_TETE, &CurrentCOL); // Cette fonction CRASH
        printf("La Colonne a bien �t� ajout�e \n");
        ToWait();
    }
    else {printf("Cette table n'�xiste pas \n"); ToWait();}
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

    if (i != 0) // test l'existance de la table en m�moire
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
                Headlu.NbRecord = CurrentTABLE.NbRecord; // On incr�mente le nombre de record
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



	 }// Fin de boucle entr� de l'enregistrement



    printf("Votre donn�e a bien �t� chang�e !\n");
    ToWait();

    }
	 else {printf(" Could not open header file ! \n"); }

	}
	else {printf("Cette table n'�xiste pas \n"); ToWait();}
}

void FillEntryFloat(EN_TETE CurTab, char * CurColName) // On �crit � la suite dans la collone sp�cifi� si 'ToTheEnd' = 0 sur sa valeur si non enfin on essai
{
    float data;
    int ToTheEnd = 0;
	 /* Cette fonctionnalit� n'est pas op�rationnelle, on �crit toujours sur la derni�re ligne, on ne peut pas remplacer des valeurs
    printf("Dans quelle enregistrement souhaitez vous l'�crire (0 � la suite)?\n");
    printf("Entrez l'index de l'enregistrement que vous souhaitez modifier :\n");
    scanf(" %d", &ToTheEnd);
	 */
    printf("Entrez la donn� � enregistrer : ");
    scanf(" %f", &data);
    FillEntryFloatBDD(CurTab, CurColName, data, ToTheEnd);

}

void FillEntryBool(EN_TETE CurTab, char * CurColName)
{
    int data;
    int ToTheEnd = 0;
	 /* Cette fonctionnalit� n'est pas op�rationnelle, on �crit toujours sur la derni�re ligne, on ne peut pas remplacer des valeurs
    printf("Dans quelle enregistrement souhaitez vous l'�crire (0 � la suite)?\n");
    printf("Entrez l'index de l'enregistrement que vous souhaitez modifier :\n");
    scanf(" %d", &ToTheEnd);
	 */
    printf("Entrez la donn� � enregistrer : ");
    scanf(" %d", &data);
    FillEntryBoolBDD(CurTab, CurColName, data, ToTheEnd);
}

void FillEntryInt(EN_TETE CurTab, char * CurColName)
{
    int data;
    int ToTheEnd = 0;
	 /* Cette fonctionnalit� n'est pas op�rationnelle, on �crit toujours sur la derni�re ligne, on ne peut pas remplacer des valeurs
    printf("Dans quelle enregistrement souhaitez vous l'�crire (0 � la suite)?\n");
    printf("Entrez l'index de l'enregistrement que vous souhaitez modifier :\n");
    scanf(" %d", &ToTheEnd);
	 */
    printf("Entrez la donn� � enregistrer : ");
    scanf(" %d", &data);
    FillEntryIntBDD(CurTab, CurColName, data, ToTheEnd);

}

void FillEntryChar(EN_TETE CurTab, char * CurColName)
{
    char data[32];
    int ToTheEnd = 0;
	 /* Cette fonctionnalit� n'est pas op�rationnelle, on �crit toujours sur la derni�re ligne, on ne peut pas remplacer des valeurs
    printf("Dans quelle enregistrement souhaitez vous l'�crire (0 � la suite)?\n");
    printf("Entrez l'index de l'enregistrement que vous souhaitez modifier :\n");
    scanf(" %d", &ToTheEnd);
    */
	 printf("Entrez la donn� � enregistrer : ");
    scanf(" %s", data);
    FillEntryCharBDD(CurTab, CurColName, data, ToTheEnd);

}



/************* * Affiche toute la BDD * ****************/

void AfficherTouteLaBDD() // Affiche la totalit� du fichier de headers
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
				if (Head.Etat !='*') // On v�rifie l'�tat de la bd !
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
{// Avec un mot cl� que l'on recherche � coups de fread() ( faire attention � la taille et en lancer plusieurs


    EN_TETE CurrentTABLE, Headlu;
	 int CMP = 0;
    printf("Bienvenue dans le gestionnaire de colone Int \n");
    printf("Entrez le nom de la Table dans laquelle vous souhaitez rechercher : ");
    scanf(" %s", CurrentTABLE.NomTable); // Le nom de la table est le nom du repertoire Faire attention aux espaces !
    if (TesterPresenceTABLE(CurrentTABLE.NomTable) == 1) // test l'existance de la table en m�moire
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
    else {printf("Cette table n'�xiste pas \n"); ToWait();}
}

void SearchEntryFloat(EN_TETE * Head, char ColTy)
{
    float ToSearchFor;
    int ToPosition;
    printf("Entrez le r�el que vous souhaitez rechercher : ");
    scanf(" %f", &ToSearchFor);
    // Doit renvoyer la position dans le fichier de la donn� recherch�e
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
	else {printf(" Cette entr� n'existe pas dans la table \n"); }
	ToWait();
}

void SearchEntryBool(EN_TETE * Head, char ColTy)
{
    int ToSearchFor;
    int ToPosition;
    printf("Entrez le Bool�en que vous souhaitez rechercher : ");
    scanf(" %d", &ToSearchFor);
    // Doit renvoyer la position dans le fichier de la donn� recherch�e
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
	else {printf(" Cette entr� n'existe pas dans la table \n"); }
	ToWait();
}

void SearchEntryInt(EN_TETE * Head, char ColTy)
{
	 int ToSearchFor;
    int ToPosition;
    printf("Entrez l'entier que vous souhaitez rechercher : ");
    scanf(" %d", &ToSearchFor);
    // Doit renvoyer la position dans le fichier de la donn� recherch�e
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
	else {printf(" Cette entr� n'existe pas dans la table \n"); }
	ToWait();
}

void SearchEntryChar(EN_TETE * Head, char ColTy)
{
    char ToSearchFor[32];
	 TurnToLower(ToSearchFor);
    int ToPosition;
    printf("Entrez l'entier que vous souhaitez rechercher : ");
    scanf(" %s", ToSearchFor);
    // Doit renvoyer la position dans le fichier de la donn� recherch�e
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
	else {printf(" Cette entr� n'existe pas dans la table \n"); }
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
    if (TesterPresenceTABLE(CurrentTABLE.NomTable) == 1) // test l'existance de la table en m�moire
    {
		  // On charge la bonne EN_TETE en m�moire
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
    else {printf("Cette table n'�xiste pas \n"); }

	ToWait();
}

void DeleteEntryFloat( EN_TETE * Head, char ColTy )
{
    float ToSearchFor;
	 int ToPosition;
    printf("Entrez le r�el que vous souhaitez supprimer : ");
    scanf(" %f", &ToSearchFor);

    ToPosition = SearchEntryFloatBDD(Head, ColTy, ToSearchFor);
    if (ToPosition != -1)
	 {
		DeleteEntryFloatBDD(Head, ToPosition );
	 }
	 else {printf("Nous n'avons pas trouv� la donn� que vous souhaitez changer"); }

    ToWait();

}

void DeleteEntryBool ( EN_TETE * Head, char ColTy )
{
    int ToSearchFor;
	 int ToPosition;
    printf("Entrez le bool�en que vous souhaitez supprimer : ");
    scanf(" %d", &ToSearchFor);

	 ToPosition = SearchEntryBoolBDD(Head, ColTy, ToSearchFor);
    if (ToPosition != -1)
	 {
		DeleteEntryBoolBDD(Head, ToPosition);
	 }
	 else {printf("Nous n'avons pas trouv� la donn� que vous souhaitez changer"); }
}

void DeleteEntryInt ( EN_TETE * Head, char ColTy )
{
    int ToSearchFor;
	 int ToPosition;
    printf("Entrez le r�el que vous souhaitez supprimer : ");
    scanf(" %d", &ToSearchFor);
    ToPosition = SearchEntryIntBDD(Head, ColTy, ToSearchFor);
    if (ToPosition != -1)
	 {
		DeleteEntryIntBDD(Head, ToPosition);
	 }
	 else {printf("Nous n'avons pas trouv� la donn� que vous souhaitez changer"); }
}

void DeleteEntryChar ( EN_TETE * Head, char ColTy )
{
    char ToSearchFor[32];
	 int ToPosition;
    printf("Entrez les caract�res que vous souhaitez supprimer : ");
    scanf(" %s", ToSearchFor);
    TurnToLower(ToSearchFor); // pass� en lower case !
    ToPosition = SearchEntryCharBDD(Head, ColTy, ToSearchFor);
    if (ToPosition != -1)
	 {
		DeleteEntryCharBDD(Head, ToPosition);
	 }
	 else {printf("Nous n'avons pas trouv� la donn� que vous souhaitez changer"); }


}





#endif /* FONCTIONINTERFACE_H_ */



