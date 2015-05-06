/*
 * Fichier Gestion BDD
 *
 * fonctionGestionBDD.h
 *
 *  Created on: 7 déc. 2013
 *      Author: Cedric et Nicolas
 *
 */



void AfficherBDD(EN_TETE * CurrentTable ); // Lecture des données en mémoire
/*
Appel de afficheRecord() et afficheHead()
*/

void CreerTableBDD(char * NomFichier, EN_TETE *CurrentHeader); // Entre en mémoire la table crée, crée le fichier data
/*


*/

void SupprimerBDD(EN_TETE *CurrentTable); // Mise a jour de l'état dans le header et suppression du fichier data

int TesterPresenceTABLE (char NomTable[32]); //  Teste la présence d'une table dans le fichier header
/*
renvoi 1 si nom pris, 0 si nom n'est pas pris

*/


int CalculeLengthRecord (EN_TETE *TableCourante); // Calcule la longueur d'un record
/*
Somme la longueur en octet de chaque entrée dans les colonnes


*/

char ColoneType(char * CurTABName, char * CurCOLName); // Renvoi le type de colone de la colonne entré
/*
ATTENTION Fichiers non ouvert
Renvoi w en cas d'erreur
*/


void AfficherBDD(EN_TETE *CurrentTable )
{
	// Il fait demander le nom de la table à rechercher
	printf("Bienvenue dans l'Afficheur Gestion BDD \n ");
		int CMP = 0;

	EN_TETE Headlu;
	FILE *FreeSpaSGBD = NULL ;
	FreeSpaSGBD = fopen("FreeSpaSGBD.txt", "r");
	if (FreeSpaSGBD !=  NULL)
    {
        while(fread(&Headlu, sizeof(EN_TETE), 1, FreeSpaSGBD) != 0 && CMP == 0)
        {
				TurnToLower(Headlu.NomTable);
            if (strcmp((Headlu.NomTable),(CurrentTable->NomTable)) == 0 && Headlu.Etat == ' ')
            {
                AfficheHead(&Headlu);
                CMP = 1;
            }
        }
	fclose(FreeSpaSGBD);
	if (CMP == 0) {printf("Nous n'avons pas trouvé la table que vous cherchez \n"); }
    }
	 else {printf(" Could not open Header file \n"); }
	if ( CMP == 1 )
	{
	int i;
	char * fileName;// marche pas autrement :(
	fileName = Headlu.NomTable;
	strcat(fileName, ".txt");

	FILE * dataFile = NULL;
	dataFile = fopen(	fileName, "r");
	if (dataFile != NULL)
	{
	for ( i = 0 ; i <= (Headlu.NbRecord -1); i++)// En effet on est décalé de 1, soit on fait l'opération ici soit on la fait en passant l'index
	{
	if (Headlu.NbRecord == 0) {printf("Empty file \n"); return;}

	afficherRecord (dataFile, &Headlu, i);

	}
	fclose(dataFile);
	}
	else {printf(" ERROR 25 : Could not opend data file");}

	}
	// to wait for enter key
	ToWait();

}

/********************* * Générateur de Table * ******************/

void CreerTableBDD(char * NomFichier , EN_TETE * CurrentHeader)
{
	printf("Bienvenue dans le créateur de table Gestion BDD\n");
	FILE *FreeSpaSGBD = NULL ;
	FreeSpaSGBD = fopen("FreeSpaSGBD.txt", "a");
    // entré dans le fichier de Header
    if (FreeSpaSGBD != NULL)
    {
        fwrite(CurrentHeader, sizeof(EN_TETE), 1, FreeSpaSGBD);
        printf("Execution donne supposively correctly ! \n");

        fclose(FreeSpaSGBD);

    }
    else {printf("ERREUR 85 : On n'a pas pu ouvrir la banque de BDD \n"); }

    // Création du fichier de data
	FreeSpaSGBD = NULL;
	FreeSpaSGBD = fopen(NomFichier, "w");

    if (FreeSpaSGBD != NULL)
    {
        printf("La fichier de BDD a bien été créé \n");

        fclose(FreeSpaSGBD);

    }
    else {printf("ERREUR 65 : On n'a pas pu générer de BDD \n"); }
	ToWait();
}

/********************* * Suppression de BDD * *******************/

void SupprimerBDD (EN_TETE *CurrentTable )
{
	printf("Bienvenue dans la suppression de BDD Gestion BDD \n ");
	char buff[100];
	strcat(buff, "rm ");
	strcat(buff, CurrentTable->NomTable);
	strcat(buff,".txt");
	system(buff);
	 int CMP = 0;

	EN_TETE Headlu;
	FILE *FreeSpaSGBD = NULL ;
	FreeSpaSGBD = fopen("FreeSpaSGBD.txt", "r+");
	if (FreeSpaSGBD !=  NULL)
    {
        while(fread(&Headlu, sizeof(EN_TETE), 1, FreeSpaSGBD) != 0 && CMP == 0)
        {
				TurnToLower(Headlu.NomTable);
				TurnToLower(CurrentTable->NomTable);
            if (strcmp((Headlu.NomTable),(CurrentTable->NomTable)) == 0)
            {// Mise à jour du fichier
					Headlu.Etat = '*';
					fseek(FreeSpaSGBD, -sizeof(EN_TETE), SEEK_CUR);
					fwrite(&Headlu,sizeof(EN_TETE), 1, FreeSpaSGBD);
                CMP = 1;

            }
        }
	fclose(FreeSpaSGBD);
    }
	ToWait();


}

/******************** Comparateurs ***************/

int TesterPresenceTABLE (char NomTable[32])
{// 1 si nom pris, 0 si nom libre. lit dans le header

	int CMP ;
	CMP = 0;
	EN_TETE Headlu;
	FILE * FreeSpaSGBD = NULL ;
	FreeSpaSGBD = fopen("FreeSpaSGBD.txt", "r");
	if (FreeSpaSGBD !=  NULL)
    {

        while(fread(&Headlu, sizeof(EN_TETE), 1, FreeSpaSGBD) != 0 && CMP == 0)
        {
				TurnToLower(Headlu.NomTable);

            if (strcmp(Headlu.NomTable,NomTable) == 0 && Headlu.Etat != '*' )
            {
                CMP = 1;

				}
        }
	fclose(FreeSpaSGBD);
    }
	 else {printf(" Could not open the header file \n"); }

	if(CMP == 1) return 1;  //1 si le nom est déjà pris
	else return 0;  //0 si le nom est disponible
}


int TesterPresenceColonne (char NomColonne[32], char NomTable[32]) // Non validé
{
	int CMP, i; // Comaparateur et compteur
	CMP=0;
	EN_TETE Tablelu;
	FILE *FreeSpaSGBD = NULL ;
	FreeSpaSGBD = fopen("FreeSpaSGBD.txt", "rb");
	if (FreeSpaSGBD != 0 )
    {
        while(fread(&Tablelu, sizeof(Tablelu), 1, FreeSpaSGBD) != 0 && CMP == 0) // Faire gaff toutes les tables n'ont pas la meme taille
	{
	    if (strcmp((Tablelu.NomTable),(NomTable)) == 0)
	    	{
                for(i=0;i <= Tablelu.NbMaxCol;i++)
                {
		    		if(strcmp(Tablelu.TabCol[i].NomColonne,NomColonne)==0) CMP=1;
		    	}
            }
	}
	fclose(FreeSpaSGBD);
    }

	if(CMP) return 1; // la colonne existe déjà
	else return 0; // la colonne peut être créée
}


/********************** Ecriture de nouvelle colone dans la bdd ***************/

// Debug le 20 / 12
void AjoutDansTableDeColoneBDD(EN_TETE *CurrentTABLE, COL * Col) // Non validé
{// On cherche à recopier le fichier de data en ajoutant la colonne souhaitée dans chaque enregistrment

	int CMP = 0;
	EN_TETE Tetelue;
	FILE *FreeSpaSGBD = NULL ;
	FreeSpaSGBD = fopen("FreeSpaSGBD.txt", "r+b"); // tu ne vas pas chercher dans le bon fichier ! cest celui la le bon ! il faut ouvrir au début et looper jusqu'a celui qu'on cherche
	if (FreeSpaSGBD != NULL)
    { // On trouve la bonne EN_TETE dans le fichier ou se trouvent les Headers
        while (fread(&Tetelue, sizeof(EN_TETE), 1, FreeSpaSGBD) && CMP == 0 )
        {
            if (strcmp((CurrentTABLE->NomTable),(Tetelue.NomTable)) == 0)
            {

					 (Tetelue.NbMaxCol)++;
                Tetelue.TabCol[Tetelue.NbMaxCol] = *Col; // Marie sainte mère de dieux ... priez pour nous pauvres pêcheurs
					 Tetelue.LengthRecord = CalculeLengthRecord(&Tetelue);
					 AfficheHead(&Tetelue);
					 fseek(FreeSpaSGBD, -sizeof(EN_TETE), SEEK_CUR);// On remet à sa place le Curseur
                fwrite(&Tetelue, sizeof(EN_TETE), 1, FreeSpaSGBD); // On print dans le fichier
                CMP = 1; // On sort du while
                fclose(FreeSpaSGBD);
            }
            else {printf(" ERREUR 72 : Could not find the data base \n"); fclose(FreeSpaSGBD); }
        }


    }
    else {printf(" ERREUR 25 : Could not open the header file\n"); }
	int j = 1 ;
	int i = 0;
	char fileNameBuff[50];
	char fileNameBuff1[50];
	char fileName[50];
	// Recopie du fichier :

	char fileToBecopied[50];

	int EmptyInt=0;
	int EmptyBool=0;
	char EmptyChar[32];
	float EmptyFloat = 0;

	strcpy((fileName), "buffer"); // nom du fichier en mémoire où l'on va recopier la base de donnée
	strcpy(fileToBecopied, Tetelue.NomTable);
	strcat(fileToBecopied,".txt");

	// Pointeurs sur les fichiers
	FILE * dataBase1 = NULL;
	FILE * dataBase2 = NULL;


	dataBase1 = fopen(fileName, "w");
	dataBase2 = fopen(fileToBecopied, "r+");

	if (dataBase1 != NULL)
	{
	if (dataBase2 != NULL)
	{
	for ( j = 1 ; j <= Tetelue.NbRecord ; j++)
	{// j est le compteur de record
	// Fonction de recopie
		while( i < Tetelue.NbMaxCol )
		{

			i++; // Compteur de colonne

			if (i <= (Tetelue.NbMaxCol - 1 ))
			{
			switch(Tetelue.TabCol[i].TypeColonne)
			{// recopie du fichier source

			   case 'f' : if (i < Tetelue.NbMaxCol){
							  {fread(&EmptyFloat, sizeof(float), 1, dataBase2);
						     fwrite(&EmptyFloat, sizeof(float), 1, dataBase1);}
							  break;}

				case 'b' : if (i < Tetelue.NbMaxCol){
						{ fread(&EmptyBool, sizeof(int), 1, dataBase2);
						fwrite(&EmptyBool, sizeof(int), 1, dataBase1);}
						break;}

			   case 'e' : if (i < Tetelue.NbMaxCol){
						{fread(&EmptyInt, sizeof(int), 1, dataBase2);
						fwrite(&EmptyInt, sizeof(int), 1, dataBase1);}
						break;}

			   case 'c' : if (i < Tetelue.NbMaxCol){
						{fread(EmptyChar, sizeof(char)*32, 1, dataBase2);
						fwrite(EmptyChar, sizeof(char)*32, 1, dataBase1);}
						break;}
				default : printf("wrong type \n "); break;
				}
				}
				else
				{

							switch((Col->TypeColonne))
						{// Insertion de cases vierges
					   	case 'f' : {fwrite(&EmptyFloat, sizeof(float), 1, dataBase1); break;}
					   	case 'b' : {fwrite(&EmptyBool, sizeof(int), 1, dataBase1); break;}
					   	case 'e' : {fwrite(&EmptyInt, sizeof(int), 1, dataBase1); break;}
					   	case 'c' : {fwrite(EmptyChar, sizeof(char)*32, 1, dataBase1); break;}
							default : printf("wrong type sur colonne ajoutée \n "); break;
            		}
				}
				// Remise à zéro des variables
				EmptyInt=0;
				EmptyBool=0;
				strcpy(EmptyChar, "************************ ");
				EmptyFloat = 0;
       }// end while


	i = 0; // Remise à zéros compteur colonnes
	}// end for
	fclose(dataBase1);
	fclose(dataBase2);
	printf("La colonne a été ajoutée avec succès\n");
	}
	else {printf(" ERROR 87 : Did Not recopy the file 1 \n "); }
	}
	else {printf(" ERROR 87 : Did Not recopy the file 2 \n"); }

	//On ecrase le fichier transféré et on change le nom de buffer pour nomdelatable.txt
	strcpy(fileNameBuff, "rm ");
	strcat(fileNameBuff,  Tetelue.NomTable);
	strcat(fileNameBuff, ".txt");

	//system (fileNameBuff); // On efface l'ancien fichier !
	// je ne sais pas pourquoi mais le fichier a déjà disparu sans que j'ai à faire le rm sur ma machine

	strcpy(fileNameBuff1, "mv ") ;
	strcat(fileNameBuff1, "buffer " );
	strcat(fileNameBuff1, Tetelue.NomTable);
	strcat(fileNameBuff1, ".txt");
	// ecriture de la ligne de code commande
	system(fileNameBuff1);


   ToWait();

}




/************************** Entré dans les fichiers ****************/
int GetBack (EN_TETE *TableCourante, char * CurColName) // Renvoi le nombre en octet dont il faut se déplacer pour depuis la fin de l'enregistrement vierge enregistré
{// envoi un int correspondant au nombre d'octet dont il fauf se décaler pour aller sur la colone
	int i, Longueur;
	Longueur = 0;
    for(i = TableCourante->NbMaxCol ; i == 0 ; i--)
    {


        switch((TableCourante->TabCol[i].TypeColonne))
               {
                   case 'c': {Longueur=Longueur+sizeof(char) * 32; break;}
                   case 'e': {Longueur=Longueur+sizeof(int); break;}
                   case 'f': {Longueur=Longueur+sizeof(float); break;}
                   case 'b': {Longueur=Longueur+sizeof(int); break;}
                   default: break;
               }
			// On test, si on retrouve la colonne que l'on cherche on s'arrete
			if (strcmp(CurColName, TableCourante->TabCol[i].NomColonne)){return (TableCourante->LengthRecord - Longueur);}

    }
	return (TableCourante->LengthRecord - Longueur);
}

void FillEntryFloatBDD(EN_TETE CurTab, char * CurColName, float data, int ToTheEnd)
{ // Ecriture dans le fichier d'un float
   printf("FillEntryFloatBDD \n");
	int ToPosition;
	ToPosition = GetBack(&CurTab, CurColName);
	FILE * BDD;
	char FileName[50];
	strcpy(FileName, CurTab.NomTable);
	strcat(FileName, ".txt");

	BDD=fopen(FileName, "a+"); if(BDD==NULL) {printf("On n'a pas pu ouvrir le fichier !\n"); return;}

	fwrite(&data, sizeof(float), 1, BDD);


	fclose(BDD);
	ToWait();

}

void FillEntryIntBDD(EN_TETE CurTab, char * CurColName, int data, int ToTheEnd)
{// Ecriture dans le fichier d'un int
   printf("FillEntryIntBDD \n");
	int ToPosition = 0 ;
	ToPosition = GetBack(&CurTab, CurColName);
	FILE * BDD;
	char FileName[50];
	strcpy(FileName, CurTab.NomTable);
	strcat(FileName, ".txt");
	BDD=fopen(FileName, "a+"); if(BDD==NULL) {printf("On n'a pas pu ouvrir le fichier !\n"); return;}

	fseek(BDD, -ToPosition, SEEK_END);


	fwrite(&data, sizeof(int), 1, BDD);
	fclose(BDD);

}


void FillEntryBoolBDD(EN_TETE CurTab, char * CurColName, int data, int ToTheEnd)
{ // Ecriture dans le fichier d'un bool
   printf("FillEntryBoolBDD \n ");
	int ToPosition = 0;
	ToPosition = GetBack(&CurTab, CurColName);
	FILE * BDD;
	char FileName[50];
	strcpy(FileName, CurTab.NomTable);
	strcat(FileName, ".txt");
	BDD=fopen(FileName, "a+"); if(BDD==NULL) {printf("On n'a pas pu ouvrir le fichier !\n"); return;}
	fseek(BDD, -ToPosition, SEEK_END);
	fwrite(&data, sizeof(int), 1, BDD);
	fclose(BDD);
}
void FillEntryCharBDD(EN_TETE CurTab, char * CurColName, char data[32], int ToTheEnd)
{ // Ecriture dans le fichier d'un char
   printf("FillEntryCharBDD \n ");
	int ToPosition = 0;
	ToPosition = GetBack(&CurTab, CurColName);
	FILE * BDD;
	char FileName[50];
	strcpy(FileName, CurTab.NomTable);
	strcat(FileName, ".txt");
	BDD=fopen(FileName, "a+"); if(BDD==NULL) {printf("On n'a pas pu ouvrir le fichier !\n"); return;}
	fseek(BDD, -ToPosition, SEEK_END); // Inutile
	fwrite(data, sizeof(char) * 32, 1, BDD);

	fclose(BDD);
}

/*********** * Enregistrement * *********************/

void CreateEnregistrementVierge(EN_TETE *Header) // Mise à jour du fichier header
{
	char FileName[50];
	strcpy(FileName, Header->NomTable);
	strcat(FileName, ".txt");
	FILE * BDD=NULL;
	BDD=fopen(FileName, "a+");
	if(BDD == NULL) {printf("La Base de données demandée n'a pas pu être ouverte\n"); return;}
	int i=0;

	int CMP ;
	CMP = 0;
	EN_TETE Headlu;
	FILE * FreeSpaSGBD = NULL ;
	FreeSpaSGBD = fopen("FreeSpaSGBD.txt", "r");
	if (FreeSpaSGBD !=  NULL)
    {

        while(fread(&Headlu, sizeof(EN_TETE), 1, FreeSpaSGBD) != 0 && CMP == 0)
        {
				TurnToLower(Headlu.NomTable);

            if (strcmp(Headlu.NomTable,Header->NomTable) == 0 && Headlu.Etat != '*' )
            {
                CMP = 1;

				}
        }
	fclose(FreeSpaSGBD);
    }
	 else {printf(" Could not open the header file \n"); }

	Header->NbRecord = Headlu.NbRecord;
	(Header->NbRecord)++;
	// TEST Valide enregistrement ! TEST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for (i = 0 ; i <= Headlu.NbRecord -1 ; i++)
	{
		if (Headlu.NbRecord == 0 ) {printf("quitting\n"); return;}
		afficherRecord (BDD, &Headlu, i);

	}


	fclose(BDD);



}

/******************* * Suppression de donnée * *********************/

void DeleteEntryFloatBDD (EN_TETE * Head, int ToPosition )
{ // On Remplace par 0 la colonne correspondante

	float ToEnter = 0;
	char NomFichier[50];
	strcpy(NomFichier, Head->NomTable);
	strcat(NomFichier, ".txt");
	FILE *BDD=NULL;
	BDD=fopen(NomFichier, "r+");
	if(BDD==NULL) {printf("Le fichier n'a pas été ouvert correctement\n"); return;}
	int PositionDansEnregistrement= ToPosition * Head->LengthRecord;// Nombre d'octet avant l'enregistrement
   int i;
   int CMP=0;

    for(i = 1 ; i <= Head->NbMaxCol && CMP ==0 ; i++) // On regarde les premieres colonnes du header
    {
		  fseek(BDD, PositionDansEnregistrement, SEEK_SET);// On se place devant l'enregistrement


        switch(Head->TabCol[i].TypeColonne)
              {// on décale le stack au fur et a mesure que l'on avance dans les colonnes
                   case 'f' : {fwrite(&ToEnter, sizeof(float), 1, BDD);CMP=1; break;} // Si tu bouge tu perds ce que tu voulais lire, c'est balot :)
                   case 'b' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'e' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'c' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(char)*32;  break;}
              }
	}
	fclose(BDD);
	printf("Exécution terminée avec succes");
}

void DeleteEntryIntBDD (EN_TETE * Head, int ToPosition )
{

	int ToEnter = 0;
	char NomFichier[50];
	strcpy(NomFichier, Head->NomTable);
	strcat(NomFichier, ".txt");
	FILE *BDD=NULL;
	BDD=fopen(NomFichier, "r+");
	if(BDD==NULL) {printf("Le fichier n'a pas été ouvert correctement\n"); return;}
	int PositionDansEnregistrement= ToPosition * Head->LengthRecord;// Nombre d'octet avant l'enregistrement
   int i;
   int CMP=0;

    for(i = 1 ; i <= Head->NbMaxCol && CMP ==0 ; i++) // On regarde les premieres colonnes du header
    {
		  fseek(BDD, PositionDansEnregistrement, SEEK_SET);// On se place devant l'enregistrement


        switch(Head->TabCol[i].TypeColonne)
              {// on décale le stack au fur et a mesure que l'on avance dans les colonnes
                   case 'f' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'b' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'e' : {fwrite(&ToEnter, sizeof(int), 1, BDD);CMP=1; break;}
                   case 'c' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(char)*32;  break;}
              }
	}
	fclose(BDD);
	printf("Exécution terminée avec succes");

}

void DeleteEntryBoolBDD (EN_TETE * Head, int ToPosition )
{

	int ToEnter = 0;
	char NomFichier[50];
	strcpy(NomFichier, Head->NomTable);
	strcat(NomFichier, ".txt");
	FILE *BDD=NULL;
	BDD=fopen(NomFichier, "r+");
	if(BDD==NULL) {printf("Le fichier n'a pas été ouvert correctement\n"); return;}
	int PositionDansEnregistrement= ToPosition * Head->LengthRecord;// Nombre d'octet avant l'enregistrement
   int i;
   int CMP=0;

    for(i = 1 ; i <= Head->NbMaxCol && CMP ==0 ; i++) // On regarde les premieres colonnes du header
    {
		  fseek(BDD, PositionDansEnregistrement, SEEK_SET);// On se place devant l'enregistrement


        switch(Head->TabCol[i].TypeColonne)
              {// on décale le stack au fur et a mesure que l'on avance dans les colonnes
                   case 'f' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'b' : {fwrite(&ToEnter, sizeof(int), 1, BDD);CMP=1; break;}
                   case 'e' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'c' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(char)*32;  break;}
              }
	}
	fclose(BDD);
	printf("Exécution terminée avec succes");

}

void DeleteEntryCharBDD (EN_TETE * Head, int ToPosition )
{

	char ToEnter[32] = "Supprimé";
	char NomFichier[50];
	strcpy(NomFichier, Head->NomTable);
	strcat(NomFichier, ".txt");
	FILE *BDD=NULL;
	BDD=fopen(NomFichier, "r+");
	if(BDD==NULL) {printf("Le fichier n'a pas été ouvert correctement\n"); return;}
	int PositionDansEnregistrement= ToPosition * Head->LengthRecord;// Nombre d'octet avant l'enregistrement
   int i;
   int CMP=0;

    for(i = 1 ; i <= Head->NbMaxCol && CMP ==0 ; i++) // On regarde les premieres colonnes du header
    {
		  fseek(BDD, PositionDansEnregistrement, SEEK_SET);// On se place devant l'enregistrement


        switch(Head->TabCol[i].TypeColonne)
              {// on décale le stack au fur et a mesure que l'on avance dans les colonnes
                   case 'f' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'b' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'e' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'c' : {fwrite(ToEnter, sizeof(char)*32, 1, BDD);CMP=1; break;}
              }
	}
	fclose(BDD);
	printf("Exécution terminée avec succes");

}

/************ * Recherche * ********************/

int SearchEntryFloatBDD(EN_TETE *Header, char ColTy, float ToSearchFor)
{
	char NomFichier[50];
	float floatLu;
	strcpy(NomFichier, Header->NomTable);
	strcat(NomFichier, ".txt");
	FILE *BDD=NULL;
	BDD=fopen(NomFichier, "r");
	if(BDD==NULL) {printf("Le fichier n'a pas été ouvert correctement\n"); return (-1);}
	int PositionDansEnregistrement=0;
   int i,j;
   int CMP=0;
   fseek(BDD, 0, SEEK_SET);
    for(i = 1 ; i <= Header->NbMaxCol && CMP ==0 ; i++) // On regarde les colonnes du header
    {
        fseek(BDD, PositionDansEnregistrement, SEEK_SET); //Pour le cas ou nous aurions 2 colonnes du meme type
        switch(Header->TabCol[i].TypeColonne)
              {
                   case 'f' : {break;}
                   case 'b' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'e' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'c' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(char)*32;  break;}
              }
        if((Header->TabCol[i].TypeColonne) == ColTy) // On choisit celle qui est du type que l'on recherche
        {

            for(j=0 ; j <= Header->NbRecord && CMP == 0 ; j++)
            {


                fread(&floatLu, sizeof(float), 1, BDD);
					 if(floatLu == ToSearchFor)
                {
                     CMP=1;

                     fclose(BDD);
                     return (j ); // On prend le premier qui arrive, on ne sait pas si il y en a 2
                }
					fseek(BDD, ((Header->LengthRecord) - sizeof(float)), SEEK_CUR); // On avance d'un enregistrement moins la taille ce que l'on viens de lire

					if (j == 0)
					 {
						PositionDansEnregistrement = PositionDansEnregistrement + sizeof(float); // On prépare pour le cas ou nous aurions 2 colones du meme type
					}

            }
        }
    }


    if(CMP==0) {printf("Votre recherche n'a donné aucune réponse !\n");}

    fclose(BDD);
    return -1;
}


int SearchEntryIntBDD(EN_TETE *Header, char ColTy, int ToSearchFor)
{
    char NomFichier[50];
    int intLu;
    strcpy(NomFichier, Header->NomTable);
    strcat(NomFichier, ".txt");
    FILE *BDD=NULL;
    BDD=fopen(NomFichier, "r");
    if(BDD==NULL) {printf("Le fichier n'a pas été ouvert correctement\n"); return (-1);}
    int PositionDansEnregistrement=0;

   int i,j;
   int CMP=0;
   fseek(BDD, 0, SEEK_SET);
    for(i = 1 ; i <= Header->NbMaxCol && CMP ==0 ; i++) // On regarde les colonnes du header
    {

		  fseek(BDD, PositionDansEnregistrement, SEEK_SET); //Pour le cas ou nous aurions 2 colonnes du meme type
        switch(Header->TabCol[i].TypeColonne)
              {
                   case 'f' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(float); break;}
                   case 'b' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'e' : {break;}
                   case 'c' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(char)*32;  break;}
              }
        if((Header->TabCol[i].TypeColonne) == ColTy) // On choisit celle qui est du type que l'on recherche ?? pour les &
        {


            for(j=0 ; j <= Header->NbRecord && CMP == 0 ; j++)
            {


               fread(&intLu, sizeof(int), 1, BDD);


                if(intLu == ToSearchFor)
                {
                     CMP=1;
                     fclose(BDD);
                     return (j ); // On prend le premier qui arrive, on ne sait pas si il y en a 2
                }
					 fseek(BDD, ((Header->LengthRecord) - sizeof(int)), SEEK_CUR); // On avance d'un enregistrement moins la taille ce que l'on viens de lire

					if (j == 0)
					 {
						PositionDansEnregistrement = PositionDansEnregistrement + sizeof(int); // On prépare pour le cas ou nous aurions 2 colones du meme type
					}

            }
        }
    }


    if(CMP==0) {printf("Votre recherche n'a donné aucune réponse !\n");}

    fclose(BDD);
    return -1;
}


int SearchEntryBoolBDD(EN_TETE *Header, char ColTy, int ToSearchFor)
{
    char NomFichier[50];
    int intLu;
    strcpy(NomFichier, Header->NomTable);
    strcat(NomFichier, ".txt");
    FILE *BDD=NULL;
    BDD=fopen(NomFichier, "r");
    if(BDD==NULL) {printf("Le fichier n'a pas été ouvert correctement\n"); return (-1);}
    int PositionDansEnregistrement=0;

   int i,j;
   int CMP=0;
   fseek(BDD, 0, SEEK_SET);
    for(i = 1 ; i <= Header->NbMaxCol && CMP ==0 ; i++) // On regarde les colonnes du header
    {
		  fseek(BDD, PositionDansEnregistrement, SEEK_SET); //Pour le cas ou nous aurions 2 colonnes du meme type
        switch(Header->TabCol[i].TypeColonne)
              {
                   case 'f' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(float); break;}
                   case 'b' : {break;}
                   case 'e' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'c' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(char)*32;  break;}
              }
        if((Header->TabCol[i].TypeColonne) == ColTy) // On choisit celle qui est du type que l'on recherche
        {

            for(j=0 ; j <= Header->NbRecord && CMP == 0 ; j++)
            {

                fread(&intLu, sizeof(int), 1, BDD);
                if(intLu == ToSearchFor)
                {
                     CMP=1;
                     fclose(BDD);
                     return (j ); // On prend le premier qui arrive, on ne sait pas si il y en a 2
                }
               fseek(BDD, ((Header->LengthRecord) - sizeof(int)), SEEK_CUR); // On avance d'un enregistrement moins la taille ce que l'on viens de lire

					if (j == 0)
					 {
						PositionDansEnregistrement = PositionDansEnregistrement + sizeof(int); // On prépare pour le cas ou nous aurions 2 colones du meme type
					}

            }
        }
    }


    if(CMP==0) {printf("Votre recherche n'a donné aucune réponse !\n");}

    fclose(BDD);
    return -1;
}
int SearchEntryCharBDD(EN_TETE *Header, char ColTy, char * ToSearchFor)
{
    char NomFichier[50];
    char charLu[32];
    strcpy(NomFichier, Header->NomTable);
    strcat(NomFichier, ".txt");
    FILE *BDD=NULL;
    BDD=fopen(NomFichier, "r");
    if(BDD==NULL) {printf("Le fichier n'a pas été ouvert correctement\n"); return (-1);}
    int PositionDansEnregistrement=0;

	int i,j;
   int CMP=0;
   fseek(BDD, 0, SEEK_SET);
    for(i = 1 ; i <= Header->NbMaxCol && CMP == 0 ; i++) // On regarde les premieres colonnes du header
    {

		  fseek(BDD, PositionDansEnregistrement, SEEK_SET); //Pour le cas ou nous aurions 2 colonnes du meme type
        switch(Header->TabCol[i].TypeColonne)
              {
                   case 'f' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(float); break;}
                   case 'b' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'e' : {PositionDansEnregistrement=PositionDansEnregistrement+sizeof(int); break;}
                   case 'c' : {break;}
              }

        if((Header->TabCol[i].TypeColonne) == ColTy) // On choisit celle qui est du type que l'on recherche
        {


            for(j=0 ; j <= Header->NbRecord && CMP == 0 ; j++)
            {

                fread(charLu, sizeof(char)*32, 1, BDD);
					 TurnToLower(charLu);
					 TurnToLower(ToSearchFor);

                if(strcmp(charLu, ToSearchFor)==0)
                {
                     CMP=1;

                     fclose(BDD);
                     return (j ); // On prend le premier qui arrive, on ne sait pas si il y en a 2
                }
					 fseek(BDD, ((Header->LengthRecord) - sizeof(char)*32), SEEK_CUR); // On avance d'un enregistrement moins la taille ce que l'on viens de lire

					if (j == 0)
					 {
						PositionDansEnregistrement = PositionDansEnregistrement + sizeof(char)*32; // On prépare pour le cas ou nous aurions 2 colones du meme type
					}


            }
        }
    }


    if(CMP==0) {printf("Votre recherche n'a donné aucune réponse !\n");}

    fclose(BDD);
    return -1;
}






/*
Fin

fichier gestionBDD
*/




















