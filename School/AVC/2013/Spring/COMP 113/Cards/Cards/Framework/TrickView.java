package Framework;

import java.awt.Color;
import java.awt.GridLayout;

import javax.swing.BorderFactory;
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

public class TrickView
{
	boolean[]	isPanelSelected	= new boolean[3];	// Flags for easily
													// determining if a panel is
													// selected
	JFrame		mainWindow		= null;			// Pointer to the main
													// Card-Trick Window
	JMenu[]		Menu			= new JMenu[2];	// Container for the main
													// Window's menu
	int			panelSelected	= 1;				// Tells specifically which
													// panel is selected
	JPanel[]	subPanel		= new JPanel[3];	// Container for each
													// card-stack's cards (and
													// images)
	TrickApp	thisApp			= null;			// Pointer to the
													// Card-Trick's Parent
	final int	WINDOW_HEIGHT	= 850;				// Window Height
	final int	WINDOW_WIDTH	= 500;				// Window Width

	public TrickView(TrickApp app) // Card-Trick's View object constructor
	{
		thisApp = app; // Point 'thisApp' to the Parent thread
		isPanelSelected[0] = false; // Initialize all panels to "not selected"
		isPanelSelected[1] = false; // Initialize all panels to "not selected"
		isPanelSelected[2] = false; // Initialize all panels to "not selected"
		mainWindow = CreateMainWindow(); // Create the main Window
	}

	public void CheckUIInterface() // Make sure we draw our GUI in the Operating
									// System's native style
	{
		try
		{
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (Exception e)
		{
		}
	}

	public void CreateMainframeMenus() // Create the menus for the Mainframe
										// Window
	{
		JMenuBar menuMain = new JMenuBar(); // Pointer to the main menu-bar
		Menu = new JMenu[2]; // Pointer to the parent menus

		JMenuItem returnButton = new JMenuItem("Return to main...");// Pointer
																	// to return
																	// to the
																	// main
																	// program
		JMenuItem tryAgainButton = new JMenuItem("Show Me Again!!!"); // Pointer
																		// to
																		// try
																		// the
																		// trick
																		// again
																		// after
																		// re-dealing
		JMenuItem exitButton = new JMenuItem("Exit"); // Pointer to the sub-menu
														// "Exit" button
		returnButton.addActionListener(thisApp); // Add an action-listener to
													// the "Deal Cards" sub-menu
		tryAgainButton.addActionListener(thisApp); // Add an action-listener to
													// the "Card Trick" sub-menu
		exitButton.addActionListener(thisApp); // Add an action-listener to exit
												// the program

		Menu[0] = new JMenu("File"); // Pointer to the parent-menu "File"
		Menu[0].add(returnButton); // Add the "Deal Cards" sub-menu to the
									// parent-menu "File"
		Menu[0].add(exitButton); // Add the "Exit" sub-menu to the parent-menu
									// "File"

		JMenuItem nextButton = new JMenuItem("Next..."); // Create the "Next..."
															// Menu Item
		nextButton.setEnabled(false); // Initialize the nextButton to disabled
		nextButton.addActionListener(thisApp); // Add a Listener to the
												// nextButton, for
												// event-handling

		Menu[1] = new JMenu("Card Trick:"); // Add the parent-menu "Card-Trick"
											// to the main Window
		Menu[1].add(nextButton); // Add the "Next..." button to the "Card-Trick"
									// menu
		Menu[1].add(tryAgainButton); // Add the "Show Me Again" button

		menuMain.add(Menu[0]); // Add the parent-menu "File" to the main
								// menu-bar
		menuMain.add(Menu[1]); // Add the parent-menu "Card-Trick" to the main
								// menu-bar
		mainWindow.setJMenuBar(menuMain); // Add the populated menu-bar into the
											// Mainframe Window
	}

	public void CreateMainframePanels() // Create the panels for the Main
										// Window, where images will be
										// displayed
	{
		JPanel mainPanel = new JPanel(); // Create a new Panel for the main
											// Window
		mainPanel.setBorder(new TitledBorder(
				"Pick a card in your head, click on it's panel and then click Card-Trick\\\"Next...\""));
		mainPanel.setLayout(new GridLayout(1, 3, 0, 0)); // Set the layout of
															// each panel to a
															// grid-layout

		for (int i = 0; i < 3; i++) // Add 3 panels to the main Window
		{
			subPanel[i] = new JPanel(); // Create a panel
			subPanel[i].setBorder(new TitledBorder("Stack " + (i + 1))); // Give
																			// it
																			// a
																			// border
			subPanel[i].setLayout(new GridLayout(7, 1, 5, 5)); // Give it a
																// GridLayout
			subPanel[i].setName("Stack " + i); // Give it a name
			subPanel[i].addMouseListener(thisApp); // Add an Event-Listener
			mainPanel.add(subPanel[i]); // Add the panel to the main Container
										// Panel
		}

		JScrollPane mainScrollPane = new JScrollPane(mainPanel, // Create
																// JScrollPanes,
																// which include
																// each panel
				ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED, // : Use a
																	// vertical-scrollbar
																	// when it
																	// is needed
				ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED); // : Use a
																		// horizontal-scrollbar
																		// when
																		// it is
																		// needed

		mainWindow.add(mainScrollPane); // Add the scrollPanes to the Mainframe
										// window
	}

	public JFrame CreateMainWindow()
	{
		CheckUIInterface(); // Make sure the GUI matches the Operating System's
		mainWindow = new JFrame("Brian Jones' Card Trick project"); // Create a
																	// new
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
		mainWindow.setVisible(true); // Set the Window to be visible
		return mainWindow; // Return a handle to the window
	}

	public void DisplayImage(Card card, int panelNumber) // Method to display
															// images to the
															// panels in the
															// Window
	{
		JLabel cardToAdd = new JLabel(card.imgCard); // Create a Pointer to a
														// JLabel containing a
														// card's image
		cardToAdd.setName("Stack " + (panelNumber + 1)); // Give it a name
		cardToAdd.addMouseListener(thisApp); // Add a Mouse-Listener to our
												// card's JLabel, implemented in
												// TrickThread
		subPanel[panelNumber].add(cardToAdd); // Add our card's JLabel to our
												// Mainframe's panels
	}

	public void EmptyPanels() // Empty the Panels
	{
		for (int i = 0; i < 3; i++)
		{
			subPanel[i].removeAll(); // Remove all components from the current
										// panel
			subPanel[i].setBorder(new TitledBorder("Stack " + (i + 1))); // Set
																			// the
																			// panel's
																			// border
																			// back
																			// to
																			// normal
			isPanelSelected[i] = false; // De-Select the panel
		}
		Menu[1].getItem(0).setEnabled(false); // Disable the "Next..." Menu item
		mainWindow.validate(); // Redraw the window
	}

	public void HighlightCard(int panel, int row) // Highlight the final card
	{
		((JLabel) (subPanel[panel].getComponent(row))).setBorder(BorderFactory.createLineBorder(Color.blue));
	}
}