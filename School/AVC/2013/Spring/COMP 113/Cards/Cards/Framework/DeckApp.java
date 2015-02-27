package Framework;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import ADTs.Deck;

public class DeckApp implements WindowListener, MouseListener, ActionListener, ComponentListener
{
	Deck		deck		= null; // Handle to our deck of cards
	MainThread	mainThread	= null; // Handle to the Main Thread and Container
									// for DeckApp and TrickApp
	DeckDoc		thisDoc		= null; // Handle to the Document class (where all
									// the card handling is performed)
	DeckView	thisView	= null; // Handle to the View class (where all the
									// visual stuff is performed)

	public DeckApp(MainThread thread) // Constructor for our Card-Dealing
										// application
	{
		mainThread = thread; // Point 'mainThread' to our Main Thread
		thisView = new DeckView(this); // Instantiate our View object, and
										// assign it to our 'thisView' Handle
		thisDoc = new DeckDoc(this, thisView); // Instantiate our Document
												// object, and assign it to our
												// 'thisDoc' Handle
	}

	@Override
	public void actionPerformed(ActionEvent e) // Implement to respond to menu
												// item selections
	{
		switch (e.getActionCommand())
		// e.getActionCommand() determines which menu item was clicked
		{
		case "Deal Cards": // If the user clicked on "Deal Cards", then:
		{
			thisView.clearPanels(); // Clear the shuffled panel
			thisDoc.DealCards(); // Deal a new set of cards
			break;
		}
		case "Card Trick": // If the user clicked on "Card Trick", then:
		{
			mainThread.CardTrickFocus(); // Tell the Main Thread to focus on the
											// Card-Trick application
			break;
		}
		case "Exit": // If the user clicked on "Exit", then:
		{
			mainThread.TERMINATE(); // Tell the Main Thread to Terminate the
									// Entire Application
		}
		}
	}

	// ////////////////////////////////////////////////////////////////////////////////////////////////////
	// //// EVENT-HANDLERS BELOW; NO IMPORTANT HOMEWORK IMPLEMENTATION OCCURS
	// BELOW THIS POINT //////
	// ////////////////////////////////////////////////////////////////////////////////////////////////////

	@Override
	public void componentHidden(ComponentEvent arg0)
	{
	} // Needed to implement the ComponentListener interface

	@Override
	public void componentMoved(ComponentEvent arg0)
	{
	} // Needed to implement the ComponentListener interface

	@Override
	public void componentResized(ComponentEvent e)
	{
	} // Only needed to implement the MouseListener interface

	@Override
	public void componentShown(ComponentEvent arg0)
	{
	} // Needed to implement the ComponentListener interface

	@Override
	public void mouseClicked(MouseEvent e)
	{
	} // Only needed to implement the MouseListener interface

	@Override
	public void mouseEntered(MouseEvent arg0)
	{
	} // Only needed to implement the MouseListener interface

	@Override
	public void mouseExited(MouseEvent arg0)
	{
	} // Only needed to implement the MouseListener interface

	@Override
	public void mousePressed(MouseEvent e)
	{
	} // Only needed to implement the MouseListener interface

	@Override
	public void mouseReleased(MouseEvent e)
	{
	} // Only needed to implement the MouseListener interface

	public void TERMINATE() // If the parent thread calls TERMINATE(), then
	{ // 'thisView' closes the Window and free's up RAM (via
		thisView.mainWindow.dispose(); // Garbage Collection) for the MainThread
										// to re-use
	}

	@Override
	public void windowActivated(WindowEvent e)
	{
	} // Only needed to implement the WindowListener interface

	@Override
	public void windowClosed(WindowEvent e)
	{
	} // Only needed to implement the WindowListener interface

	@Override
	public void windowClosing(WindowEvent ev)
	{
	} // Only needed to implement the WindowListener interface

	@Override
	public void windowDeactivated(WindowEvent e)
	{
	} // Only needed to implement the WindowListener interface

	@Override
	public void windowDeiconified(WindowEvent e)
	{
	} // Only needed to implement the WindowListener interface

	@Override
	public void windowIconified(WindowEvent e)
	{
	} // Only needed to implement the WindowListener interface

	@Override
	public void windowOpened(WindowEvent e)
	{
	} // Only needed to implement the WindowListener interface
}