package fr.ismin.demineur.Cedric;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.*;

public class Case extends JPanel implements MouseListener {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private static final int MARGE = 4; 
	private static final int SIZE_CASE = 50; 
	private int nbMinesCase; 
	private int posX, posY; 
	private GUI gui; 
	private boolean beenThere; 
	
	public String val = "X";
	
	/**
	 * Constructeur de case avec taille prédéfinie 
	 */
	Case(int nbMines, int posX, int posY, GUI gui){
		
		setPreferredSize(new Dimension(SIZE_CASE, SIZE_CASE)); 
		addMouseListener(this); // il faut implementer mouse Listener 
		nbMinesCase = nbMines; 
		this.gui = gui; 
		this.posX = posX;
		this.posY = posY; 
		this.beenThere = false; 
	}
	
	/**
	 * Dessin de la Case 
	 * 
	 */
	public void paintComponent(Graphics gc){ 
		
		super.paintComponents(gc); 
		gc.setColor(Color.white);
		gc.fillRect(MARGE, MARGE, SIZE_CASE, SIZE_CASE); 
		gc.setColor(Color.black);
		gc.fillRect(2*MARGE, 2*MARGE, SIZE_CASE/2, SIZE_CASE/2); 
		gc.setColor(Color.cyan);
		gc.drawString(val, SIZE_CASE/2, SIZE_CASE/2); 
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		// TODO Auto-generated method stub
		//System.out.println("Mouse clicked");
		if (!gui.launchTimer){
			gui.launchTimer = true; 
			// Lance le timer 
			gui.timer.start();
		}
		
		if (SwingUtilities.isRightMouseButton(arg0)) {
			if (val == "Y"){val = "X";}  // Pour annuler 
			else {val = "Y"; }
			repaint();  
		}
		if (SwingUtilities.isLeftMouseButton(arg0)){
			gui.refreshAllThere(); 
			int change = changeMine(); 
			if (change == 0){ // Un zéro est cliqué 
				gui.propagateUpDate(this.posX, this.posY);			
			}
			else if (change == 50 ){ // Une case qui touche une bombe ! 
				//System.out.println("ATTENTION !!!!!");
			}
			else if (change == 100){ // Bombe ! 
				System.out.println("Perdu !!!!!!! ");
				// Terminer le JEUX ICI !!!!
				gui.aplli.resetGame(false); 
			}	
		}
		gui.checkResultGui(); 
	}
	
	public int changeMine(){
		int retVal; 
		if (nbMinesCase == 0){ 
			val = String.valueOf(nbMinesCase);
			retVal = 0; 
		}
		else if (nbMinesCase != 100){
			val = String.valueOf(nbMinesCase); 
			retVal = 50; 
		}
		else {// Il y a une bombe dans la case 
			val = "B"; 
			retVal = 100; 
		}
		repaint(); 
		return retVal; 
	}
	
	public int isMine(){
		if (this.nbMinesCase == 100){
			return 100; 
		}
		else if(this.nbMinesCase > 0){return 50;} 
		else {return 0; }
	}
	
	public void refreshThere(){
		beenThere = false; 
	}
	
	public void setBeenThere(){
		beenThere = true; 
	}
	public boolean getThere(){
		return beenThere; 
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
