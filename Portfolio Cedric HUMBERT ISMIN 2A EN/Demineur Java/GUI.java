/**
 * 
 */
package fr.ismin.demineur.Cedric;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

/*
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
*/
//...
import javax.swing.*; 

/**
 * @author eleves
 *
 */
public class GUI extends JPanel implements ActionListener{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JButton butQuit = new JButton ("Quit"); 
	private JButton butInit = new JButton (":-)");
	private JLabel timerLabel = new JLabel("Timer HERE !");
	private JPanel panelMines = new JPanel(); 
	private JMenuItem itemNew;
	private JMenuItem itemQuit;  
	private JMenuItem itemAbout;
	public Demineur1 aplli; 
	private Case[][] tabCase; 
	// TIMER : 
	public boolean launchTimer; 
	public Timer timer;
	private int time = 0; 
	//timer.setInitialDelay(0);
	
	public GUI(Demineur1 appli){
		super(new BorderLayout()); 
		//setLayout(new BorderLayout()); // Meme chose en moins joli
		
		this.aplli = appli; 
		
		creerMenu(); 
		launchTimer = false; 
		timer = new Timer(1500, this); 
		
		// North 
		JPanel panelActionN = new JPanel(); 
		panelActionN.add(timerLabel);
		add(panelActionN, BorderLayout.NORTH); 
		
		
		// Center 
		// Grillle
		panelMines.setLayout(new GridLayout(appli.GetGrilleDimX(),appli.GetGrilleDimY()));
		
		// Generation du Tableau 
		createTabCase(); 
		
		// Remplissage de la grille : 
		for (int i = 0 ; i < appli.GetGrilleDimX() ; i++){
			for(int j = 0 ; j < appli.GetGrilleDimY() ; j++){
				Case Case = tabCase[i][j]; 
				panelMines.add(Case); 
			}
		}
		
		add(panelMines, BorderLayout.CENTER); 
		
		// South : 
		butQuit.addActionListener(this); 
		butInit.addActionListener(this);
		
		JPanel panelActionS = new JPanel(); 
		add(panelActionS, BorderLayout.SOUTH); 
		panelActionS.add (butInit); 
		panelActionS.add(butQuit); 

	}
	
	
	@Override 
	public void actionPerformed(ActionEvent e){
		// eventuellement remetre une icone ?? 
		if(e.getSource() == itemQuit){
			int reponse = JOptionPane.showConfirmDialog(null, "Are you Sure ??","Confirme",  JOptionPane.YES_NO_OPTION); 
			if (reponse == JOptionPane.YES_OPTION){
				System.out.println("Bye !");
				System.exit(0);
			}
		}
		else if (e.getSource() == butQuit){
			System.out.println("Bye item Quit !");
			System.exit(0);
		}
		else if(e.getSource() == butInit) {
			aplli.resetGame(false); 
		}
		
		// Identification EMPTY !!!!!!!!
		else if(e.getSource() == itemAbout){
			String reponse = JOptionPane.showInputDialog("What is your ID ??"); 
			System.out.println(reponse);		
		}
		// Nouveau Jeux 
		else if (e.getSource() == itemNew){
			aplli.resetGame(false);
		}
		// Timer
		else if (e.getSource() == timer) {
		time++; 
		timerLabel.setText( String.valueOf(time)); 
	    timerLabel.repaint();
		timer.restart(); 
		}
		else {
			System.out.println("Non Reconnu "); 
		}
	}
	
	public void createTabCase(){
		tabCase = new Case[aplli.GetGrilleDimX()][aplli.GetGrilleDimY()]; 
		for (int i = 0 ; i < aplli.GetGrilleDimX() ; i++){
			for(int j = 0 ; j < aplli.GetGrilleDimY() ; j++){
				tabCase[i][j] = new Case(aplli.getNbMines(i, j), i, j, this );
			}
		}
	}
		
	
	
	/**
	 * Création des menus en haut dans la barre de menu 
	 * TO DO 
	 * Ajouter un menu pour changer de niveau
	 * 
	 */
	
	void creerMenu(){
		// Barre de menu 
		JMenuBar menuBar = new JMenuBar(); 
		JMenu menuF = new JMenu("Fichier"); 
		menuBar.add(menuF); 
		JMenu menuA = new JMenu("About"); 
		menuBar.add(menuA); 
		
		
		// Fichier 
		// New 
		itemNew = new JMenuItem("New", KeyEvent.VK_N);
		itemNew.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, ActionEvent.ALT_MASK)); 
		// Affiche un message après 2 secondes sur le bouton 
		itemNew.setToolTipText("New"); 
		menuF.add(itemNew);
		itemNew.addActionListener(this);
		
		// Quit 
		itemQuit = new JMenuItem("Quit", KeyEvent.VK_Q);
		itemQuit.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Q, ActionEvent.ALT_MASK)); 
		// Affiche un message après 2 secondes sur le bouton 
		itemQuit.setToolTipText("Quit"); 
		menuF.add(itemQuit);
		aplli.setJMenuBar(menuBar); 
		itemQuit.addActionListener(this);
		
		// About 
		itemAbout = new JMenuItem("Ident", KeyEvent.VK_B);
		itemAbout.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_B, ActionEvent.ALT_MASK)); 
		menuA.add(itemAbout); 
		itemAbout.setToolTipText("Ajoutez vos Identifiants"); 
		aplli.setJMenuBar(menuBar); 
		itemAbout.addActionListener(this);
		
	}
	
	public void propagateUpDate(int posX, int posY){
		if(posX < this.tabCase.length && posX >= 0){
			if (posY < this.tabCase[0].length && posY >= 0){
				if (!this.tabCase[posX][posY].getThere()){
					if (this.tabCase[posX][posY].isMine() < 50){ // La case est un zéro elle est changée
						this.tabCase[posX][posY].changeMine(); 
						this.tabCase[posX][posY].setBeenThere(); 
						propagateUpDate(posX + 1, posY);
						propagateUpDate(posX - 1, posY);
						propagateUpDate(posX, posY + 1);
						propagateUpDate(posX, posY - 1);
					}
					else if (this.tabCase[posX][posY].isMine() == 50){
						this.tabCase[posX][posY].changeMine(); 
						this.tabCase[posX][posY].setBeenThere(); 
					}
				}
			}
		}
	}
	
	public void refreshAllThere(){
		for (int i = 0 ; i < this.tabCase.length ; i++){
			for (int j = 0 ; j < this.tabCase[0].length ; j++){
				this.tabCase[i][j].refreshThere(); 
			}
		}
	}
	
	public void checkResultGui(){
		boolean win = true;
		for (int i = 0 ; i < this.tabCase.length ; i++){
			for (int j = 0 ; j < this.tabCase[0].length ; j++){
				if (this.tabCase[i][j].isMine() == 100){ 
					if (!(this.tabCase[i][j].val == "Y")){win = false;}// Pas encore Gagné
				}
				else { // Pas une mine 
					if (this.tabCase[i][j].val == "Y"){win = false;}// Pas encore Gagné
				}
			}
		}
		if (win == true){
			// System.out.println("VOUS AVEZ GAGNE !!!!!!!! ");
			timer.stop(); 
			aplli.resetGame(true);
		}
	}

}
















