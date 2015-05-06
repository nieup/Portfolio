/* 				Projet Robot Contrat 7 Caniche avec détection I/R 
 *		Juin 2014 : LANFRANCHI Arnaud & HUMBERT Cédric 
 *		
 *		headall.h V0
*/
// Ficier header pour ces fonctions ICI : 

// Les Fichiers Tableau de correspondance ICI : 
//const rom unsigned char ComPWM[20] = {51, 54, 56, 61, 66, 71, 79, 87, 94, 102, 102, 102, 102, 102, 102, 92, 82, 71, 61, 51};
const rom unsigned char ComPWM[20] = {13, 14, 14, 15, 17, 18, 20, 22, 24, 26, 26, 26, 26, 26, 26, 23, 21, 18, 15, 13}

// Variables ApwmL & ApwmR 1 les tableaux en mémoire :  
unsigned char Batterie[4] = {180, 180, 180, 180}; // Tableau des valeures Batterie initialisation au dessus du seuil 
unsigned char ScanR[4] = {0, 0, 0, 0}; // Tableau pour le capteur Droit initialisation Sur petite distance
unsigned char ScanL[4] = {0, 0, 0, 0}; // Tableau pour le capteur Gauche initialisation Sur petite distance
unsigned char Vbat; // Valeur de la tension Batterie 
unsigned char distR; // Valeur de la tension distance à Droite
unsigned char distL; // Valeur de la tension distance à Gauche  
unsigned char ApwmR; // Valeur de la commande PWM Droite
unsigned char ApwmL; // Valeur de la commande PWM Gauche
unsigned char MesBat; // Mesure de la tension batterie 

// Ici sont toutes les fonctions utilisée dans le fichier FonctionPrincipales.c 

// Fonction d'initialisation : 
void Initialisation(); 

// Positionnement du robot pour qu'il se mette en face de la plaque par modulation du rapport cyclique 
void Positionnement(); 

// Scan avec les IR de la distance entre le robot et la plaque lors du Positionnement, remplit les tableaux scanL et scanR en mémoire 
void ScanP(); 

// Scan avec les IR de la distance entre le robot et la plaque lors de la Marche, remplit les tableaux scanL et scanR 
void ScanAs(); 

// Commande le PWM pour les moteurs lors de la marche du moteur 
void Marche1();









