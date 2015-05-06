/*
 * main.c
 *
 *  Created on: 7 d�c. 2013
 *      Author: C�dric & Nicolas
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MaxCol 16

/*************************************/
/*STRUCTURES*/
/*************************************/


typedef struct COL /*Structure de la base de donn�es*/
{
    char NomColonne[32] ; // nom de la colonne dans la table
    char TypeColonne; // type de la colonne 'C' = char, 'E'=entier, 'F' = r�el, 'B' = bool�en
    int TailleColonne; // taille en octet

}COL;

typedef struct EN_TETE /* Structure de Header */
{

    char NomTable[32];  // nom de la table
    short YY, MM,DD; // date de modification ann�e, mois , jour
    int NbRecord ; // nombre d' enregistrements de la table
    int LengthHeader; // taille enoctets de l' en-t�te (� calculer)
    int LengthRecord ; // taille en octetsde l' enregistrement ( � calculer)
    COL TabCol[MaxCol] ; // description des colonnes de la table
    int NbMaxCol; // Nombre effectif de colonnes dans la table
    char Etat; // relatif aux fonctions de suppression

}EN_TETE;


/*************************************/
/*PROTOTYPES*/
/*************************************/


void ToContinue(char * Continue); // attent un y pour continuer la boucle du main
void ToWait(); // Attent qu l'on presse entrer pour continuer
int ChoixDeNb( int MaxNb, int i); // Permet de rentrer le bon nombre de colonnes, mois que 16 ici mais utile surtout lors de la phase de test
void TurnToLower(char * chaine); // renvoi la chaine entr�e en lower case
char TypeDeCol(); // Renvoi le type de colonne que l'utilisateur souhaite, gestion des mauvaises entr�s
void AfficheHead( EN_TETE *Head); // Affiche le header de la table qui lui est donn�
void afficherRecord (FILE * FileToread, EN_TETE * CurHead, int IndexOfRecordToRead); // Affiche un record en appelant les fonctions plus bas
void AfficheEntryFloat(FILE * FileToread);
void AfficheEntryInt(FILE * FileToread);
void AfficheEntryBool(FILE * FileToread);
void AfficheEntryChar(FILE * FileToread);
int CalculeLengthRecord (EN_TETE *TableCourante); //Renvoit en octets la longueur d'un enregistrement
char ColoneType(char * CurTABName, char * CurCOLName); // Renvoi le type de colone de la colonne entr� !! Fichier non ouvert


// Fichier incluant les fonction d'interface et appellant les fonctions de gestion de la BDD
#include "fonctionInterface.h"


/*********** Main ****************/



int main(void)
{ // Le main lance les fonctions

	// Impl�mentation des variables :

	int Choisit;
	char Continue;
	Choisit = 0;
	Continue = 'y';

	// Algorithme d'�x�cution g�n�ral

	while( Continue == 'y')
	{

		MenuTables(&Choisit);
		ToContinue(&Continue);
	}

	return 0;
}

/*********** Fonctions utilitaires **************/


void ToContinue(char * Continue)
{

	* Continue = 'n';
	printf("Entrez y pour continuer : ");

	scanf(" %c", Continue);
	*Continue = tolower(*Continue);

}

void ToWait ()
{// attent un Entrer pour passer � la suite
// Remarque : malheureusement fflush et getc ne marche bien qu'avec Windows

	int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
	getchar();
}

int ChoixDeNb( int MaxNb, int i)
{// Compare le nombre entr� avec le nombre max qui lui est entr� renvoi le plus petit des 2
    if (i >= MaxNb)
        return MaxNb;
	else return i;
}

void TurnToLower(char * chaine)
{// Change la chainne en une chaine en lowercase

	int i = 0; // Compteur
	while (chaine[i] != '\0')
	{
		chaine[i] = tolower(chaine[i]);
		i++;
	}
}

char TypeDeCol()
{//renvoi le type de colone souhait� par l'utilisateur

    char Ty ;
    short RightCol = 0;
    while ( RightCol != 1)
    {
        printf("Quel type de colonne souhaitez vous ? \n");
        printf(" entrez 'C' pour char, 'E' pour entier, 'F' pour r�el, 'B' pour bool�en\n");
        scanf(" %c", &Ty);
        Ty = tolower(Ty);
        switch (Ty)
        {
            case 'c' : RightCol = 1; break;
            case 'e' : RightCol = 1; break;
            case 'f' : RightCol = 1; break;
            case 'b' : RightCol = 1; break;
            default : {printf("ERREUR 20 : Mauvaise entr� Type de Colone \n "); break;} // gestion des mauvaises saisies
        }

    }
    return Ty ;
}

void AfficheHead(EN_TETE * Head) // Valid� pour l'affichage, reste � voir le nombre d'"*"
{
    int k = 1; // compteur pour les Colones

    printf(" ************************************************************\n ");


    printf("* Nom de la Table : %3s || Modifi� de le %d / %d / %d *\n", Head->NomTable, Head->DD, Head->MM, Head->YY);
    for (k = 1 ; k <= Head->NbMaxCol ; k++)
    {//(HeadNbMaxCol)
        printf(" * [%d]  %s ", k, (Head->TabCol[k].NomColonne));
    }
    printf("\n **********************************************************\n ");

}

/************** * Affiche Record * ********************/

void afficherRecord (FILE * FileToread, EN_TETE * CurHead, int IndexOfRecordToRead)
{ // Il faut bien commencer � 0 IndexOfRecordToRead pour avoir le d�but
    int i ; // Compteur

    // Pr�paration du nombre d'octets � sauter
    int PositionInFile = (CurHead->LengthRecord)*IndexOfRecordToRead; // Suppos� etre un long int
    fseek(FileToread, PositionInFile, SEEK_SET); // Ce replace devant l'enregistrement � lire ! ( a partir du d�but du fichier)
    printf("*************************************************************************\n");
    for (i = 0 ; i  <= CurHead->NbMaxCol ; i++)
    {

        fseek(FileToread, PositionInFile, SEEK_SET); // Ce replace devant l'enregistrement � lire ! ( a partir du d�but du fichier)

        switch (CurHead->TabCol[i].TypeColonne)
        {
            case 'f' : {AfficheEntryFloat(FileToread); PositionInFile = PositionInFile + sizeof(float);  break;}
            case 'b' : {AfficheEntryBool(FileToread); PositionInFile = PositionInFile + sizeof(int);  break;}
            case 'e' : {AfficheEntryInt(FileToread); PositionInFile = PositionInFile + sizeof(int); break;}
            case 'c' : {AfficheEntryChar(FileToread); PositionInFile = (PositionInFile + sizeof(char) * 32) ; break;}

        }
    }
    printf("*\n");
    printf("************************************************************************* \n");


}

void AfficheEntryFloat(FILE * FileToread)
{
    float data;
    fread(&data, sizeof(float), 1, FileToread);
    printf("* %4f", data);
}
void AfficheEntryBool(FILE * FileToread)
{
    int data;
    fread(&data, sizeof(int), 1, FileToread);
    printf("* %4d", data);

}
void AfficheEntryInt(FILE * FileToread)
{
    int data;
    fread(&data, sizeof(int), 1, FileToread);
    printf("* %4d", data);
}
void AfficheEntryChar(FILE * FileToread)
{
    char data[32];
    fread(data, sizeof(char) * 32, 1, FileToread);
    printf("* %4s", data);
}

/*************** Calcul de longueur *************************/

int CalculeLengthRecord (EN_TETE *TableCourante) //Renvoit en octets la longueur d'un enregistrement
{
    int i, Longueur=0;
    for(i=0;i <= TableCourante->NbMaxCol;i++)
    {
        switch((TableCourante->TabCol[i].TypeColonne))
               {
                   case 'c': {Longueur=Longueur+sizeof(char)*32; break;}
                   case 'e': {Longueur=Longueur+sizeof(int); break;}
                   case 'f': {Longueur=Longueur+sizeof(float); break;}
                   case 'b': {Longueur=Longueur+sizeof(int); break;}
                   default: break;
               }
    }
    return Longueur;
}
/*********************** * Type de colonne ******************/

char ColoneType(char * CurTABName, char * CurCOLName) // Renvoi le type de colone de la colonne entr� !! Fichier non ouvert
{
   int CMP, i; // Comaparateur et compteur
	CMP=0;
	EN_TETE Tablelu;
	FILE *FreeSpaSGBD = NULL ;
	FreeSpaSGBD = fopen("FreeSpaSGBD.txt", "rb");
	if (FreeSpaSGBD != 0 )
    {
        while(fread(&Tablelu, sizeof(Tablelu), 1, FreeSpaSGBD) != 0 && CMP == 0)
	{
	    if (strcmp((Tablelu.NomTable),(CurTABName)) == 0)
	    	{
                for(i=0;i<Tablelu.NbMaxCol;i++)
                {
		    		if(strcmp(Tablelu.TabCol[i].NomColonne,CurCOLName)==0)
                    {
                        CMP = 1;
                        fclose(FreeSpaSGBD);
                        return Tablelu.TabCol[i].TypeColonne;
                    }
		    	}
            }
	}
	fclose(FreeSpaSGBD);
    }
	else {printf("ERREUR 85 : Could not open header file ! (yes again) \n");}
    return 'w'; // En cas d'erreur renvoi un w
}












