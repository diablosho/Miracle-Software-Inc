package Framework;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.BorderFactory;
import javax.swing.JComponent;
import javax.swing.border.TitledBorder;

public class TrickApp implements WindowListener, MouseListener, ActionListener, ComponentListener
{
	MainThread	mainThread	= null; // Pointer to our parent Thread, used to
									// switch program focus
	TrickDoc	thisDoc		= null; // Pointer to our Card-Trick Document
									// object, where cards are handled
	TrickView	thisView	= null; // Pointer to our Card-Trick View object,
									// where cards are displayed

	public TrickApp(MainThread thread) // Constructor for our Card-Trick
										// Application
	{
		mainThread = thread; // Point mainThread to our parent thread
		thisView = new TrickView(this); // Instantiate our View object, with
										// 'thisView' as its' Handle
		thisDoc = new TrickDoc(this, thisView); // Instantiate our Document
												// object, with 'thisDoc' as
												// its' Handle
	}

	@Override
	public void actionPerformed(ActionEvent e) // Implement to respond to menu
												// item selections
	{
		switch (e.getActionCommand())
		// e.getActionCommand() determines which menu item was clicked
		{
		case "Return to main...": // If the user clicked on "Return to main...",
									// then:
		{
			mainThread.MainProgramFocus(); // Tell the MainThread to send
											// program focus back to
			break; // the Card-Dealing Thread
		}
		case "Exit": // If the user clicked on "Exit", then:
		{
			mainThread.TERMINATE(); // Tell the Main Thread to Terminate the
									// program
			break;
		}

		case "Next...": // If the user clicked on "Next", then we need to
						// continue the trick...
		{
			thisView.EmptyPanels(); // Clear the panels, in preparation for the
									// next set of visuals
			thisDoc.next(thisView.panelSelected); // Tell the Document class to
													// continue on to the next
													// step of...
			break; // ...the trick
		}
		case "Show Me Again!!!": // If the user clicked on "Show Me Again!!!"
									// (because it was so cool!!!):
		{
			thisView.EmptyPanels(); // Clear the panels, in preparation for the
									// next set of visuals
			thisDoc.freshDeal(); // Tell the Document to Start the trick all
									// over again,
			thisView.mainWindow.validate(); // re-initializing all necessary
											// variables with a new deck.
			break;
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
	} // Needed to implement the ComponentListener interface

	@Override
	public void componentShown(ComponentEvent arg0)
	{
	} // Needed to implement the ComponentListener interface

	public void highlightStack(int panelNumber) // Put a border around the
												// selected panel
	{
		for (int i = 0; i < 3; i++) // Check if already highlighted, and see if
									// it was clicked
		{
			if (thisView.isPanelSelected[i]) // We are de-selecting the panel...
			{
				thisView.subPanel[i].setBorder(new TitledBorder("Stack " + (panelNumber + 1)));
				thisView.isPanelSelected[i] = false;
				thisView.Menu[1].getItem(0).setEnabled(false);
			}
			else if (i == panelNumber) // We are selecting the panel...
			{
				thisView.subPanel[panelNumber].setBorder(BorderFactory.createLineBorder(Color.blue));
				thisView.isPanelSelected[panelNumber] = true;
				thisView.panelSelected = i; // Flag for our Document Object to
											// know which panel...
				thisView.Menu[1].getItem(0).setEnabled(true); // ...was selected
			}
		}
	}

	@Override
	public void mouseClicked(MouseEvent e) // mouseClicked is called when a
											// Component is clicked
	{
		JComponent componentSelected = (JComponent) e.getSource(); // Grab a
																	// handle to
																	// the
																	// clicked
																	// component

		switch (componentSelected.getName())
		// Switch based on the name of the Component
		{
		case "Stack 1":
			highlightStack(0);
			break; // If the name was "Stack 1", then highlight stack 0
		case "Stack 2":
			highlightStack(1);
			break; // If the name was "Stack 2", then highlight stack 1
		case "Stack 3":
			highlightStack(2);
			break; // If the name was "Stack 3", then highlight stack 2
		}
	}

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