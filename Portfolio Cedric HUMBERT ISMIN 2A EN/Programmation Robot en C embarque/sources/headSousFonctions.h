/* 				Projet Robot Contrat 7 Caniche avec détection I/R 
 *		Juin 2014 : LANFRANCHI Arnaud & HUMBERT Cédric 
 *		
 *		headSousFonctions.h V0
*/
// Ficier header pour ces fonctions ICI : 


// Ici sont toutes les fonctions présentes dans le fichier SousFonctions.c

// Arret du robot suite à une erreur de déplacement  
void errordir1();

// Sort la tenstion de la batterie 
void OutBat();

// Transforme la valeure retrouvé par les IR en une valeur exploitable via le tableau de conversion  
char trad(unsigned char Mes);

// Fait une nouvelle moyenne dans le tableau avec la nouvelle valeur
unsigned char moyenne(unsigned char Val, unsigned char* Tab); 


