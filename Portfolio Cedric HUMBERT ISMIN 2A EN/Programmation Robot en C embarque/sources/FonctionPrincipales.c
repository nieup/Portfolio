/* 				Projet Robot Contrat 7 Caniche avec dÃ©tection I/R 
 *		Juin 2014 : LANFRANCHI Arnaud & HUMBERT CÃ©dric 
 *		
 *		Le Programme correspond Ã  l'algorigrame	
 *		FonctionPrincipales.c V0
*/

// ETAT : A tester + Ajouter Code Initialisation + Acquisition des mesures  

// Header des sous fonctions :


//extern void errordir();
/*
#include "headall.h"
#include <p18f2520.h>
*/

// Fonction d'initialisation : 
void Initialisation(){ //Description de la fonction Initialisation, qui ne revoit rien.
/*Cette fonction initialise :
 * le convertisseur chargé de traité la tension issue de la battérie,
 * le timer0,
 * l'I²C,
 * les capteurs infrarouges,
 * les signaux PWM,
 * les 8 LEDs,
 * L'RS232
 *  */

/*Inilisation du Conversisseur Analogique Numérique (CAN)*/
     //Configuration entrée/sortie de la broche 2 du port A
    TRISAbits.RA2 = 1 ; // Broche 2 du port A en entrée
    TRISBbits.RB5 = 1 ; //Broche de la LED test

    ADCON0bits.CHS0 = 0 ; // Sélection broche en analogique
    ADCON0bits.CHS1 = 1 ; // Broche 2 du port A (AN2) en analogique
    ADCON0bits.CHS2 = 0 ;
    ADCON0bits.CHS3 = 0 ;



    ADCON0bits.ADON = 1 ; // Active le module de version analogique/numérique

    // Configuration analogique/numérique de la broche 2 du port A
    ADCON1bits.PCFG0 = 0 ;
    ADCON1bits.PCFG1 = 0 ; // Indique que le broche 2 du port A
    ADCON1bits.PCFG2 = 1 ; // est une grandeure analogique
    ADCON1bits.PCFG3 = 1 ; // Sélection de AN0 à AN2, les autres broches sont en numériques

    //Sélection des tensions de référence
    ADCON1bits.VCFG0 = 0 ; // On n'utilise pas de tension de référence
    ADCON1bits.VCFG1 = 0 ; //(ni Vref+, ni Vref-)

    //Configuration de la fréquence de fonctionnement du CAN et du temps de conversion
    ADCON2bits.ADCS0 = 0 ;
    ADCON2bits.ADCS1 = 0 ; // Il faut que Tad (temps de conversion) soit le plus faible possible met supérieur à 0,7 µs
    ADCON2bits.ADCS2 = 1 ; // Tad = 1 /(Fosc/Préscaler) Fosc = 8MHz, donc il faut un préscaler de 8. Tad = 1µs > Tadmin = 0,7 µs

    //Configuration du temps d'acquisition Tacq = Tamp + Tc + Tcoff
    ADCON2bits.ACQT0 = 0 ; // Tamp = 2µs, c'est la temps de mise en place, Tc = 1,05µs(dans le pire des cas), c'est le temps de chargement
    ADCON2bits.ACQT1 = 0 ; // Tcoff =  1,2µs(dans le pire des cas), c'est temps supplémentaire dépendant de la température
    ADCON2bits.ACQT2 = 1 ; // Tacq = 2 + 1 + 1,2 > 4,2 µs, ici Tacq = 8.Tad = 8 µs > 4,2µs

    // Résultat de la conversion droite justifié ou gauche justifié
    ADCON2bits.ADFM = 0 ; //Gauche justifié (on prend les 8 bits de poids forts,le plus significatifs)

/*Initialisation du Timer0*/
    T0CONbits.TMR0ON = 1 ; // Activation de timer0
    T0CONbits.T08BIT = 0 ; // Configuration du timer0 en  16 bits
    T0CONbits.T0CS = 0 ; // Utilisation de l'horloge interne pour le timer0
    T0CONbits.T0CS = 0 ; // Incrémentation sur front montant de l'horloge
    T0CONbits.PSA = 1 ; // Utilisation d'un préscaler
    T0CONbits.T0PS2 = 0 ; // Valeur du prescaler :
    T0CONbits.T0PS1 = 1 ; // On veut avoir la moyenne de la tension de la battérie toute les 100ms (on fait 4 mesures)
    T0CONbits.T0PS0 = 1 ;
    // Prescaler = 16 => Ftimer0 = Fosc/Préscaler = 0,5MHz => t1mesure = N/fr = 0.032ms
    // => tmesuremoy = 4.t1mesure = 128ms


/*Initialisation des  capteurs infrarouges*/
    TRISAbits.RA0 = 1 ; // Broche 0 du port A en entrée (tension de sortie du capteur droit)
    TRISAbits.RA1 = 1 ; // Broche 1 du port A en entrée (tension de sortie du capteur gauche)
    TRISBbits.RB1 = 0 ; // Broche 1 du port B en sortie
    // Broche configuré en numérique plus haut

/*Initialisation des signaux PWM*/
   TRISCbits.RC1 = 0 ; //Broche 1 du port C en sortie (PWMD)
   TRISCbits.RC2 = 0 ; //Broche 1 du port C en sortie (PWMG)

   T2CONbits.T2CKPS1 =  1 ; // prescaler de 16 car il faut que PR2<255
   PR2=124; // PR2 = fosc/(4.fpwm.prescaler)-1 avec fpwm=1000hz


//pour générer les signaux PWM mode CCPi
    CCP2CONbits.CCP2M3 = 1 ; // Mode CCP2 pour la broche 12
    CCP2CONbits.CCP2M2 = 1 ;
    CCP1CONbits.CCP1M3 = 1 ; // Mode CCP1 pour la broche 13
    CCP1CONbits.CCP1M2 = 1 ;
    CCP1CONbits.CCP1M1 = 0 ; // Broche 12(PWMD) et 14(PWMG)en simple sortie.
    CCP1CONbits.CCP1M0 = 0 ;

/*Initialisation de l'RS232*/
        TXSTAbits.SYNC = 0 ;// Liaison asynchrone
        BAUDCONbits.BRG16 = 0 ; // Transmission du 8bits
        TXSTAbits.BRGH = 0 ;
        SPBRG = 12 ;// BaudRate = Fosc/[64](SPBRG+1]
        // SPRBG = Fosc/[64.BaudRate] -1 = 8M/[64.9,6k] -1 = 12

        RCSTAbits.FERR = 0 ; // Pas d'erreur de cadrage
        RCSTAbits.OERR = 0 ; // Pas d'erreur de dépassement
        RCSTAbits.CREN = 1 ; // Activer la réception

	TRISCbits.RC6 = 1 ; //Broche 6 du port C TX en entrée
        TRISCbits.RC7 = 1 ; //Broche 7 du port C RX en sortie
        RCSTAbits.SPEN = 1 ; //Validation de la broche TX et RX
        TXSTAbits.TXEN = 1 ; //Validation de la transmission
        SSPCON2bits.RCEN = 1 ; //Validation de la translission

        PIR1bits.TXIF = 1 ; //Effacement de l'intérruption TX
        PIE1bits.TXIE = 1 ; //Valider l'intérrruption  TX
        PIR1bits.RCIF = 1 ; //Effacement de l'intérruption RX
        PIE1bits.RCIE = 1 ; //Valider l'intérrruption  RX


/*Initialisation de l'I²C*/
   TRISCbits.RC3 = 1 ; //Broche 3 du port C en entrée (SCL)
   TRISCbits.RC4 = 1 ; //Broche 4 du port C en entrée (SDA)
   SSPCON1bits.SSPEN = 1 ; // Broche 14(SCL) et (SDA) en mode I²C

   SSPCON1bits.SSPM3 = 1 ;
   SSPCON1bits.SSPM2 = 0 ; // Utilisation de mode master
   SSPCON1bits.SSPM1 = 0 ;
   SSPCON1bits.SSPM0 = 0 ;
   SSPSTATbits.SMP = 1 ; //Echange standart sur front montant
   SSPADD = 39 ; // Pour une fréquence 50kHz pour l'I2C :
   //SSPADD=Fosc/(4.CLK)-1=(8.?10?^6)/(4.50.?10?^3 )-1=39

   SSPCON2bits.SEN =  1 ; // Bit Start, début de la transmission

	while (! PIR1bits.SSPIF) ; //Tant que la transmission n'est pas finie
	PIR1bits.SSPIF = 0; // On dit que la transmission est en cour

	SSPBUF = 0x40 ; // Adresse de l'esclave

	while (! PIR1bits.SSPIF ) ; //Test la transmission n'est pas finie
	PIR1bits.SSPIF = 0 ; // On continue la transmission

	while ( SSPCON2bits.ACKSTAT ) ; // Test que le bit d'acknowledge est à '1 (le récepteur est prêt à reçevoir)
	SSPBUF = 0x7F ; //On allume toutes les LEDs
// Les données arrives à la cathode de chaque LED, donc avec un '0' <=> GND
//on crée une différence de potentiel aux bornes des LEDs, donc allumés

	//while (! PIR1bits.SSPIF ) ; // Tant que la transmission n'est pas finie
	PIR1bits.SSPIF = 0; // On continue la transmission

	//while ( SSPCON2bits.ACKSTAT ) ; // Test de la réception des données
	SSPCON2bits.PEN = 1 ; // Bit Stop, fin de la transmission


        RCONbits.IPEN = 0 ; // Pas de niveau d'intérruptions
        INTCONbits.GIE = 1 ; // Autoriser les intérrruptions
        INTCONbits.PEIE = 1 ; // Valider les périphériques d'intérruptions
}

// Positionnement du robot pour qu'il se mette en face de la plaque par modulation du rapport cyclique 
void Positionnement() {
	if (distR <= distL){
	ApwmL = ComPWM[0];// IncrÃ©mentation ApwmL
	ApwmR = 0; // DÃ©crÃ©mentation ApwmR
	}
	else {
	ApwmR = ComPWM[0];// IncrÃ©mentation ApwmR
	ApwmL = 0;// DÃ©crÃ©mentation ApwmL
	}

}

// Scan avec les IR de la distance entre le robot et la plaque lors du Positionnement, remplit les tableaux scanL et scanR en mÃ©moire 
void ScanP(){
    unsigned char R, L;
	// Aquisition L & R via les capteurs  
	trad(R); // Transforme la valeure retrouvÃ© par les IR en une valeur exploitable via le tableau de conversion 
        trad(L); 
        moyenne(R, ScanR); // Fait une nouvelle moyenne dans le tableau avec la nouvelle valeur
	moyenne(L, ScanL); // Fait une nouvelle moyenne dans le tableau avec la nouvelle valeur
}

// Scan avec les IR de la distance entre le robot et la plaque lors de la Marche, remplit les tableaux scanL et scanR 
void ScanAs(){
	unsigned char MesR; // Variables pour la mesure droite  
	unsigned char MesL; // Variables pour la mesure gauche 
	// Aquisition de L & R via les capteurs
	
	
	// Transforme la valeure retrouvÃ© par les IR en une valeur exploitable via le tableau de conversion
	distR = moyenne(trad(MesR),ScanR); // Fait une nouvelle moyenne dans le tableau avec la nouvelle valeur  
	distL = moyenne(trad(MesL), ScanL); // Fait une nouvelle moyenne dans le tableau avec la nouvelle valeur 
	
	// Test en cas d'erreur sur une dÃ©viation de chemin
	if ( distR != distL ) {
            errordir1();

	}
}

// Commande le PWM pour les moteurs lors de la marche du moteur

void Marche1(){
	// Regarder dans la table 2 ( conrrespondance distance / vitesse ) via distL et distR
	// Set ApwmL & ApwmR
	ApwmL = ComPWM[distL]; 
	ApwmR = ComPWM[distR];

}
