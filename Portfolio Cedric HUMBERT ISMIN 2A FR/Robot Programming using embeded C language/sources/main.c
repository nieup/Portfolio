/* 				Projet Robot Contrat 7 Caniche avec détection I/R 
 *		Juin 2014 : LANFRANCHI Arnaud & HUMBERT Cédric 
 *		
 *		Le Programme correspond à l'algorigrame 
 *		main.c V0
*/

// ETAT : Début du Main ?? LIB ?? 

#include <stdio.h>
#include <p18f2520.h>
#include "headall.h"
#include "headSousFonctions.h"
#include "FonctionPrincipales.c"
#include "SousFonctions.c"
//#include "hFonctionsPrincipales.h"
// extern void Marche(); 

#pragma config OSC = INTIO7
#pragma config PBADEN = OFF, WDT = OFF, LVP = OFF, DEBUG = ON

// Intéruptions ICI 
// Pour la Batterie Appel toutes les 100 ms 
/* 
if( // Flag ) {
//Flag Off
// Mesurer sur le Can de la tension Batterie
PORTBbits.RB1 = 1; 
MesBat = read Can de batterie 
}
*/  

void main (void)
{        //Configuration de l"horloge
         OSCCONbits.IRCF0 = 1 ; // On utilise l'oscillateur interne du microcontroleur
         OSCCONbits.IRCF1 = 1 ; // Qui est de 8MHz
         OSCCONbits.IRCF2 = 1 ;
	// Initialisation des Interruptions
	// Affichage des Leds -> Pret
	while (1) {
	// Sleep mode // Attente de commande par la télécommande
	// Déclaration des Variables 
	Initialisation(); // Appel de la fonction d'initialisation
	PORTBbits.RB5 = 1 ;
	//Positionnement & Détection de l'obstacle
	while (distL == 0 && distR == 0 ){ // test sur la distance, à plus de 150 cm +/- 7 cm 
		ScanP(); // détection de la plaque à distance 
		Positionnement(); // Mise en Position du robot avec des commandes de PWM 
		}
	
	while (distL <= 18 && distR <= 18){ // Test sur la distance ici avec le model : à 24 cm  
		// if( interruption ) { // Cadencement à 100 ms 
			moyenne(MesBat, Batterie); // Faire la moyenne dans le tableau
			// test de valeur Bon : rien Mauvais : OutBat(); 
			if (Vbat <= 159 ) { // valeur correspondant sur la simulation ISIS 
				OutBat(); 
			}
		}
		ScanAs(); // Détection de la distance 
		Marche1(); // Controle des PWM pour la vitesse de déplacement
		CCP1CONbits.CCPR1L = ApwmL // Commande moteur Gauche 
		CCP2CONbits.CCPR2L = ApwmR // Commande moteur Droit
		}
	// Fin -> Economie d'énergie 
	}
}