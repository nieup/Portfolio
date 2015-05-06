/** 
 * Class pincipale du demineur 
 * 
 */


package fr.ismin.demineur.Cedric;

import javax.swing.JFrame;
import javax.swing.JOptionPane;


import fr.ismin.demineur.Cedric.Grille.LEVEL;


/**
 * @author Cedric
 *
 */
public class Demineur1 extends JFrame{
	

	/** Varibles 
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private GUI gui;
	private Grille tableau;
	
	/**
	 * @param args 
	 * 
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new Demineur1(); 
	}
	
	
	/**
	 * 
	 * @param lvl
	 */
	Demineur1(LEVEL lvl){
		// Nom de la fenetre 
		super("Démineur !!");
				
		// Generation d'un tableau 
		tableau = new Grille(lvl);
		tableau.modifierTaille(tableau.GetDimX(), tableau.GetDimY()); 
		// Place les mines dans le tableau  
		tableau.placeMines(tableau.nbMinesDefault()); 
				
		/** TEST :  
		 * Affichage du tableau sur la console : 
		 * System.out.println(tableau); 
		 * Test du nombre de mines dans la case 5 et 4 
		 * System.out.println(tableau.getNbMines(5, 4));
		 */
		gui = new GUI(this); 
		setContentPane(gui); // Pannel principale de la JPanel 
		pack();
		// Resize de la fenetre
		// this.setResizable(false);  
		setDefaultCloseOperation(EXIT_ON_CLOSE); 
		setVisible(true); 
	}
	
	/**
	 * Constructeur : 
	 * 		Création de Grille et IHM
	 */
	Demineur1(){
		new Demineur1(LEVEL.EASY); 
		
	}




	public int GetGrilleDimX(){return this.tableau.GetDimX();}
	
	public int GetGrilleDimY(){return this.tableau.GetDimY();}
	
	public int getNbMines(int PosX, int PosY){return this.tableau.getNbMines(PosX, PosY);}
	
	public void resetGame(boolean state){
		setVisible(false); 
		if (state){
			int reponseS = JOptionPane.showConfirmDialog(null, "Gagné \nSouhaitez vous recomencer","New Game",  JOptionPane.YES_NO_OPTION); 
			if (reponseS == JOptionPane.YES_OPTION){
				String reponseL = JOptionPane.showInputDialog("Quel Niveau ??");
				switch (reponseL){
					case "easy":{new Demineur1(LEVEL.EASY); }
					case "medium":{new Demineur1(LEVEL.MEDIUM); }
					case "hard":{ new Demineur1(LEVEL.HARD); }
					case "custom":{	new Demineur1(LEVEL.CUSTOM); }
					default : {	new Demineur1();}
				}		
			}
			else {
				System.out.println("Bye do not restart!");
				System.exit(0);
			}
		}
		else {
			int reponseS = JOptionPane.showConfirmDialog(null, "Perdu \nSouhaitez vous recomencer","New Game",  JOptionPane.YES_NO_OPTION); 
			if (reponseS == JOptionPane.YES_OPTION){
				String reponseL = JOptionPane.showInputDialog("Quel Niveau ??");
				switch (reponseL){
					case "easy" :{new Demineur1(LEVEL.EASY); break; }
					case "medium" :{new Demineur1(LEVEL.MEDIUM); break; }
					case "hard" :{ new Demineur1(LEVEL.HARD); break; }
					case "custom" :{new Demineur1(LEVEL.CUSTOM); break; }
					default : {new Demineur1(LEVEL.EASY); break; }
				}		
			}
			else {
				System.out.println("Bye do not restart!");
				System.exit(0);
			}
		}
		
		
	}

}

























