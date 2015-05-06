/* 				Projet Robot Contrat 7 Caniche avec détection I/R 
 *		Juin 2014 : LANFRANCHI Arnaud & HUMBERT Cédric 
 *		
 *		Le Programme correspond à l'algorigrame
 *		SousFonctions.c V0
*/
// ETAT : trad & moyenne à tester FAIRE les Errordir & OutBat 
/*
#include "headSousFonctions.h"
#include "headall.h"
*/
const rom unsigned char dist[20] = { 11, 11, 12, 14, 15, 16, 18, 20, 22, 24, 27, 31, 35, 40, 46, 55, 66, 83 ,110, 135};
// Arret du robot suite à une erreur de déplacement  
void errordir1(){
	// Afficher Erreur Marche Led 
	
	// Terminaison du programme car erreur: 
	while(1); 
}

// Sort la tenstion de la batterie 
void OutBat(){
	// Afficher Erreur Batterie Led
	// Entrer en Mode Sleep 
}

// Transforme la valeure retrouvé par les IR en une valeur exploitable via le tableau de conversion  
char trad(unsigned char Mes){
	char Trans = 0; // Variable de parcours du tableau qui est retournée 
	// Comparaison de la valeur mesurée avec un tableau de conversion dans un header 
	while (Mes <= dist[Trans]){
	Trans++; 
	} 
	return Trans; // retourner la distance 

}

// Fait une nouvelle moyenne dans le tableau avec la nouvelle valeur
unsigned char moyenne(unsigned char Val, unsigned char* Tab){
	// Boucle de parcour du tableau : 
	char i ; // Variable de parcours du tableau
	unsigned char Moy = Val;  
	for (i = 0 ; i <= 2 ; i++ ){
	Tab[i+1] = Tab[i]; // Passer la valeur i du tableau dans la valeur i + 1 
	Moy = Tab[i] + Moy; // Somme pour la moyenne
	}
	Tab[0] = Val; // Donner à la valeur 0 du tableau la valeur de la mesure 
	Moy = Moy>>2; // Division par 4 en décalant à droite 2 fois 
	return Moy; // Retourne la moyenne du tableau
}













