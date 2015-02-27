package Framework;

import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ScrollPaneConstants;
import javax.swing.UIManager;
import javax.swing.border.TitledBorder;

import ADTs.Card;

public class DeckView
{
	JFrame			mainWindow		= null;				// Pointer to the
															// mainWindow
	JScrollPane[]	scrollPanes		= new JScrollPane[2];	// Pointer to the
															// scrollPanes

	JPanel[]		ShuffledPanels	= new JPanel[2];		// Pointer to the
															// ShuffledPanels,
															// which hold the
															// cards
	DeckApp			thisApp			= null;				// Pointer to the
															// main Card-Dealing
															// Application
															// Thread
	final int		WINDOW_HEIGHT	= 850;					// Window Height
	final int		WINDOW_WIDTH	= 1050;				// Window Width

	public DeckView(DeckApp app) // Constructor for the View object
	{
		thisApp = app; // Point thisApp to the main Application object
		mainWindow = CreateMainWindow(); // Create the main Window, with a
											// mainWindow Handle
	}

	public void CheckUIInterface() // Make sure we are drawing our GUI in the
									// Operating System's native style
	{
		try
		{
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (Exception e)
		{
		}
	}

	public void clearPanels() // Clear the panels when we are re-dealing
	{
		ShuffledPanels[0].removeAll(); // Remove all components from our
										// panels[0]; ([0] = UnShuffled Panel)
		ShuffledPanels[1].removeAll(); // Remove all components from our
										// panels[1]; ([1] = Shuffled Panel)
		mainWindow.validate(); // Redraw the main Window
	}

	public void CreateMainframeMenus() // Create the menus for the Mainframe
										// Window
	{
		JMenuBar menuMain = new JMenuBar(); // Pointer to the main menu-bar
		JMenu Menu[] = new JMenu[2]; // Pointer to the parent menus

		JMenuItem dealButton = new JMenuItem("Deal Cards"); // Pointer to the
															// sub-menu
															// "Deal Cards", to
															// deal the deck
		JMenuItem trickButton = new JMenuItem("Card Trick"); // Pointer to the
																// sub-menu
																// "Card Trick"
																// button
		JMenuItem exitButton = new JMenuItem("Exit"); // Pointer to the sub-menu
														// "Exit" button
		dealButton.addActionListener(thisApp); // Add an action-listener to the
												// "Deal Cards" sub-menu
		trickButton.addActionListener(thisApp); // Add an action-listener to the
												// "Card Trick" sub-menu
		exitButton.addActionListener(thisApp); // Add an action-listener to exit
												// the program

		Menu[0] = new JMenu("File"); // Pointer to the parent-menu "File"
		Menu[0].add(dealButton); // Add the "Deal Cards" sub-menu to the
									// parent-menu "File"
		Menu[0].add(trickButton); // Add the "Card Trick" sub-menu to the
									// parent-menu "File"
		Menu[0].add(exitButton);

		menuMain.add(Menu[0]); // Add the parent-menu "File" to the main
								// menu-bar
		mainWindow.setJMenuBar(menuMain); // Add the populated menu-bar into the
											// Mainframe Window
	}

	public void CreateMainframePanels() // Create the panels, to which images
										// will be placed
	{
		String[] deckType =
		{ "Unshuffled Deck", "Shuffled Deck" };

		for (int i = 0; i < 2; i++)
		{
			ShuffledPanels[i] = new JPanel(); // Create a new panel to hold our
												// cards
			ShuffledPanels[i].setBorder(new TitledBorder(deckType[i])); // Give
																		// it a
																		// border
			ShuffledPanels[i].setLayout(new GridLayout(13, 4, 5, 5)); // Set the
																		// layout
																		// of
																		// each
																		// panel
																		// to a
																		// grid-layout
			scrollPanes[i] = new JScrollPane(ShuffledPanels[i], // Create
																// JScrollPanes,
																// which include
																// each panel
					ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED, // : Use a
																		// vertical-scrollbar
																		// when
																		// it is
																		// needed
					ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED); // :
																			// Use
																			// a
																			// horizontal-scrollbar
																			// when
																			// it
																			// is
																			// needed
			mainWindow.add(scrollPanes[i]); // Add the scrollPanes to the
											// Mainframe window
		}
	}

	public JFrame CreateMainWindow() // Method to create the main Window
	{
		CheckUIInterface(); // Check that we are using the native UI
		mainWindow = new JFrame("Brian Jones' Cards project"); // Create a new
																// Mainframe
																// Window
		mainWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Set Window
																	// to close
																	// after
																	// clicking
																	// the
																	// Window's
																	// 'X'
		mainWindow.setLayout(new GridLayout(1, 1, 5, 5)); // Set the Window
															// Layout to a
															// grid-layout
		mainWindow.setSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Initialize the
															// Window's size
		CreateMainframeMenus(); // Add menus to the Mainframe Window
		CreateMainframePanels(); // Add ScrollPane Panels to the Mainframe
									// Window
		mainWindow.setVisible(true); // Set the main Window to be visible
		return mainWindow; // Return a handle to the main Window
	}

	public void DisplayImage(Card card, int panelNum) // Method to display our
														// card
	{
		JLabel cardToAdd = new JLabel(card.imgCard); // Create a Pointer to a
														// JLabel containing a
														// card's image
		ShuffledPanels[panelNum].add(cardToAdd); // Add our card's JLabel to our
													// main Window's panels
		cardToAdd.addMouseListener(thisApp); // Add a Mouse-Listener to our
												// card's JLabel
		mainWindow.validate(); // Redraw the window
	}
}