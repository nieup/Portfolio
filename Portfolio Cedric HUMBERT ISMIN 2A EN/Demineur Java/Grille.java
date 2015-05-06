/**
 * Grille du demineur 
 * avec les 0 et les 1 qui 
 * correspondent à la presence de bombe 
 * ou non dans le demineur
 * 
 */
package fr.ismin.demineur.Cedric;

import java.util.Random;

/**
 * @author Cedric HUMBERT 
 *
 */

public class Grille {
	
	enum LEVEL {EASY, MEDIUM, HARD, CUSTOM};
	private static final int COEFF_EASY = 5; // % de mines dans le tableau 
	private static final int COEFF_MEDIUM = 15;
	private static final int COEFF_CUSTOM = 13;
	private static final int COEFF_HARD = 20;
	private static final int DIM_DEF = 7;
	private static final int DIM_EASY = 7;
	private static final int DIM_MEDIUM = 10;
	private static final int DIM_HARD = 20;
	private int nbMinesDef; // nombre de mines du tableau
	private boolean[][] tabMines; 
	
	private LEVEL level; // niveau courant 
	
	/**
	 * Constructeur par defaulf de grille
	 * 
	 */
	public Grille(){this(LEVEL.EASY, 0, 0);}
	
	/**
	 * Second Constructeur par defaulf de grille
	 * 
	 */
	public Grille(LEVEL level){this(level, 0, 0);}
	
	/**
	 * Constructeur avec definition de niveau 
	 * @param niveau souhaité 
	 */
	public Grille(LEVEL level, int dimX, int dimY){
		this.level = level;
		if (level == LEVEL.CUSTOM){tabMines = new boolean [dimX][dimY];}
		else if (level == LEVEL.EASY){tabMines = new boolean [DIM_EASY][DIM_EASY];}
		else if (level == LEVEL.MEDIUM){tabMines = new boolean [DIM_MEDIUM][DIM_MEDIUM];}
		else if (level == LEVEL.HARD){tabMines = new boolean [DIM_HARD][DIM_HARD];}
		// En cas de probleme ou défault on donne la dimension Custom. 
		else {level = LEVEL.CUSTOM; tabMines = new boolean [DIM_DEF][DIM_DEF];}
	}
	
	
	
	/**
	 * Placement de mines aléatoire 
	 * @param nbMines nombre de mines à placer dans le tableau 
	 * 
	 */
	void placeMines(int nbMines){
		this.nbMinesDef = nbMinesDefault(); // this est une reference, un "super pointeur" 
		int nbMinesPlacees = 0; 
		Random geneRand = new Random(); 
		
		while( nbMinesPlacees != nbMines){
			int x = geneRand.nextInt(tabMines.length); 
			int y = geneRand.nextInt(tabMines[0].length); 
			if (!tabMines[x][y]){
				tabMines[x][y] = true; 
				nbMinesPlacees++; 
			}
		}
	}
	
	/**
	 * 
	 * @return le nombre de bombe en fonction du level 
	 */
	
	public int nbMinesDefault(){
		int coeff; 
		if(level == LEVEL.EASY){
			coeff = COEFF_EASY; 
		}else if (level == LEVEL.MEDIUM){
			coeff = COEFF_MEDIUM;
		}else if (level == LEVEL.HARD){
			coeff = COEFF_HARD;
		}else if (level == LEVEL.CUSTOM){
			coeff = COEFF_CUSTOM;
		}
		else{
			coeff = COEFF_EASY;
		}
		/** Test : nombre de mines et coefficient 
		 *		System.out.println(coeff) ; 
		 *		System.out.println(tabMines.length * tabMines[0].length * coeff / 100); 
		 */
		return tabMines.length * tabMines[0].length * coeff / 100 ;  
	}
	
	/**
	 * Modifier la taille de la tabMines
	 * 
	 * @param newX largeur 
	 * @param newY hauteur 
	 * 
	 */
	void modifierTaille(int newX, int newY){
		tabMines = new boolean [newX][newY];
		placeMines(nbMinesDefault()); 	
	}
	
	
	/**
	 * 
	 * retourne une chaine de characteres 
	 * 
	 */
	public String toString(){
		StringBuffer buff = new StringBuffer(); 
		for(int i = 0 ; i < tabMines.length ; i++){
			for(int j = 0 ; j < tabMines[0].length ; j++){
				if (tabMines[i][j] == true){
					buff.append("x ");
				}else {
					buff.append("0 ");
				}
			}
			buff.append("\n"); 
		}
		return buff.toString(); 
	}
	
	/**
	 * 
	 * affiche la grille sur la console 
	 * 
	 */
	void affGrille(){
		for(int i = 0 ; i < tabMines.length ; i++){
			for(int j = 0 ; j < tabMines[0].length ; j++){
				if (tabMines[i][j] == true){System.out.print("x ");}
				else {	System.out.print("0 ");}
			}
			System.out.println();
		}
	}
	/*
	 * Retourne le nombre de mines autour de la case PosX, PosY 
	 * Du tableau de Mines. 
	 * 
	 * Ne doit pas etre appellée sur une  case Mine si non renvoi 
	 * une mine de trop !!
	 * 
	 */
	public int getNbMines(int PosX, int PosY){
		int count = 0;
		if (this.tabMines[PosX][PosY] == true){
			return 100; // code de retour si on est sur une mine
		}
		for(int i = PosX - 1 ; i <= PosX + 1; i++){// Parcours des cases alentours 
			for(int j = PosY - 1 ; j <= PosY + 1 ; j++){
				if(i >= 0 && j >= 0 && i < this.tabMines.length && j < tabMines[0].length){
					// On est bien dans une case define 
					if (!(i == PosX && j == PosY)){// on n'est pas sur une mine 
						if(this.tabMines[i][j] == true){count++;} // Il y a une mine											
					}
				}
			}
		}
		return count; 
	}
	
	public int GetDimX(){return this.tabMines.length;}
	
	public int GetDimY(){return this.tabMines[0].length;}
	
}






