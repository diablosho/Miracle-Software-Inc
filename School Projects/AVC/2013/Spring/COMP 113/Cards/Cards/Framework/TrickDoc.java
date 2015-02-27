package Framework;

import ADTs.ArrayListStackContainer;
import ADTs.Card;
import ADTs.Deck;
import Stacks.ArrayListStack;

public class TrickDoc
{
	Deck					deck			= null; // Create a new deck object
	final int				DECKSIZE		= 21;	// Initialize the size of
													// the trick-deck to 21
	ArrayListStack<Card>	deckStack		= null; // Create a stack for our
													// deck in a linear fashion
	int						newStep			= 0;	// newStep tells us how many
													// times we've dealt the
													// cards
	ArrayListStackContainer	stackContainer	= null; // Create a container for
													// our ArrayListStacks
	TrickView				thisView		= null; // Create a pointer to our
													// View object

	public TrickDoc(TrickApp app, TrickView view)
	{
		thisView = view; // Point thisView to our View object
		stackContainer = new ArrayListStackContainer(3); // Instantiate our
															// stackContainer,
															// to hold 3 stacks
		freshDeal(); // Begin dealing
	}

	public void ConstructPanelsFromDeck() // We need to create 3 panels for
											// display purposes,
	{ // while retaining the original deck
		ArrayListStack<Card> tempStack = new ArrayListStack<Card>();

		int cardLoc = 0;
		while (cardLoc < DECKSIZE) // While there are still cards in the deck...
		{
			for (int stackNumber = 0; stackNumber < 3; stackNumber++, cardLoc++)
			{
				stackContainer.stack[stackNumber].push(deckStack.top()); // Pop
																			// the
																			// top
																			// of
																			// our
																			// linear
																			// Seck-Stack
				deckStack.popInto(tempStack); // into it's respective panel
			}
		}
		deckStack.incorporate(tempStack); // Put our linear Deck-Stack back
											// together
	}

	public void CreateDeckFromPanels()
	{
		// Panels have been moved, and now we must re-create the deck to reflect
		// that fact
		// We will do so by pushing all elements of stack 0, then all from stack
		// 1, then all from stack 2

		deckStack.EmptyStack();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				stackContainer.stack[i].popInto(deckStack); // Copy each
															// complete panel at
															// a time into the
															// Deck-Stack
			}
		}
	}

	public void deal()
	{
		ConstructPanelsFromDeck(); // Convert our linear deck-stack to 3
									// different panels
		displayPanels(); // Output those panels to the window
	}

	public void displayPanels() // Display the Panels
	{
		for (int stackNumber = 0; stackNumber < 3; stackNumber++)
		{
			for (int row = 0; row < (DECKSIZE / 3); row++)
			{
				thisView.DisplayImage(stackContainer.stack[stackNumber].top(), stackNumber);
				stackContainer.stack[stackNumber].pop();
			}
		}
	}

	public void freshDeal() // Called whenever we need a new deck of cards
	{
		deck = new Deck(DECKSIZE); // Create a new deck
		deck.ShuffleCards(deck.deckStack); // Shuffle the cards
		deckStack = deck.deckStack; // Create an alias for the deck's stack, to
									// make things easier
		newStep = 0; // Make this step 0 (since no card has been chosen yet)
		deal(); // Deal the cards
	}

	public void next(int panelToMove) // Called whenever we need to deal again
	{
		newStep++; // One step closer to finished
		ConstructPanelsFromDeck(); // Convert our linear deck-stack to 3
									// different panels
		stackContainer.SwapElements(panelToMove, 1); // Place the selected stack
														// into the middle of
														// the deck
		CreateDeckFromPanels(); // Now recreate the linear deck-steck from the 3
								// panels
		deal(); // Deal again
		if (newStep == 3) // If we are on step 3, then we are finished!!!
		{
			thisView.HighlightCard(1, 3); // Highlight the card
			thisView.Menu[1].getItem(0).setEnabled(false); // Disable the
															// "Next..." button
															// in the menu
			thisView.Menu[1].getItem(1).setEnabled(true); // Enable the
															// "Show me Again"
															// button in the
															// menu
		}
	}
}