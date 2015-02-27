/*
 * Name: Brian Jones Date: 3/23/2013 Course: CIS 113 Assignment: Create a GUI-based Card-Dealing application Extra
 * Credit: Create a GUI-based Card-Trick application Notes: I have created both into one application. You can access the
 * Card-Trick application via the main menu in the Card-Dealing application, and you can return to the Card-Dealing
 * application from the Card-Trick Application via the main menu as well. The instructions for the Card-Trick
 * application are pretty self-explanatory, but basically you just: 1. Pick a card in your head 2. Click on the panel
 * that contains your card. 3. Click on the "Card-Trick" Menu button, and then click on "Next..." to move along with the
 * trick. 4. After the 3rd time clicking "Next...", your card will be highlighted with a blue border around it. 5. From
 * this point, you may: 5a: click "Show Me Again!!!" from the "Card Trick" menu, 5b: go back to the Card-Dealing
 * application, or 5c: exit the program completely.
 */

package Framework;

public class MainThread
{
	static MainThread	mainThread	= null; // Pointer to our Main Thread,

	public static void main(String[] args) // Entry point to the program
	{
		mainThread = new MainThread(); // Instantiate the MainThread as an
										// independent program driver
	}

	// parent of the following threads:
	DeckApp		DeckApp		= null; // Pointer to our Card-Dealing

	// application
	TrickApp	TrickApp	= null; // Pointer to our Card-Trick
									// application

	public MainThread() // Constructor for our main program Instance
	{
		DeckApp = new DeckApp(this); // Instantiate the Card-Dealing program
										// called DeckApp
	}

	public void CardTrickFocus() // Method to switch over to our Card-Trick
									// application
	{
		DeckApp.TERMINATE(); // Terminate the main Card-Dealing application,
								// freeing up memory
		TrickApp = new TrickApp(this); // Instantiate and focus on our
										// Card-Trick application
	}

	public void MainProgramFocus() // Method to switch over to our Main
									// Card-Dealing application
	{
		TrickApp.TERMINATE(); // Terminate the Card-Trick application, freeing
								// up memory
		DeckApp = new DeckApp(this); // Instantiate and focus on our
										// Card-Dealing application
	}

	public void TERMINATE() // Method to terminate the main program instance
	{
		System.exit(0); // Exit the program, destroying objects and freeing up
						// the RAM that was used
	}
}