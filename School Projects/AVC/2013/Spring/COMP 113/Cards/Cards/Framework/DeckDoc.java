package Framework;

import ADTs.ArrayListStackContainer;
import ADTs.Card;
import ADTs.Deck;
import Stacks.ArrayListStack;

public class DeckDoc
{
	Deck					deck		= null; // Create a pointer to our Deck
												// object
	final int				DECKSIZE	= 52;	// Initialize the deck size to
												// 52
	ArrayListStack<Card>	deckStack	= null; // Create an object to hold our
												// Deck's stack
	ArrayListStackContainer	stackContainer;	// Container for ArrayListStacks
	DeckView				thisView	= null; // Create a pointer to our View
												// object

	public DeckDoc(DeckApp app, DeckView view)
	{
		thisView = view; // Point thisView to our View object
		DealCards(); // Deal our cards
	}

	public void ConstructPanelsFromDeck(int panelToConstruct) // We need to
																// create 3
																// panels for
																// display
																// purposes,...
	{ // ...while retaining the original deck
		ArrayListStack<Card> tempStack = new ArrayListStack<Card>();
		ArrayListStack<Card> panelStack = // Create an alias to our container's
		stackContainer.stack[panelToConstruct]; // panel to construct

		int cardLocation = 0; // Set our location in the deck to 0
		while (cardLocation < DECKSIZE) // While there are still cards in the
										// deck...
		{
			tempStack.push(deckStack.popInto(panelStack)); // Push our Deck's
															// stack into our
															// panel,...
															// while saving a
															// copy in tempStack
															// for later
			cardLocation++; // Move to the next card in the deck
		}
		deckStack.incorporate(tempStack); // Rebuild our Deck's stack using
											// tempStack
	}

	public void DealCards()
	{
		deck = new Deck(DECKSIZE); // Create a new deck of cards
		stackContainer = new ArrayListStackContainer(2); // Create a container
															// to hold our Card
															// stacks

		for (int panelToDisplayTo = 0; panelToDisplayTo < 2; panelToDisplayTo++)
		{
			deckStack = deck.deckStack; // Point our Deck Stack object to the
										// Deck's current stack
			deckStack.reversed(); // Reverse our Deck-pointer's stack
			ConstructPanelsFromDeck(panelToDisplayTo); // Create our Deck Panels
														// from our linear
														// Deck-Stack
			deck.ShuffleCards(deckStack); // Shuffle our Deck
		}
		displayPanels(); // Display our Card Panels on our Window
	}

	public void displayPanels() // Output our panel stacks that we just created
	{
		ArrayListStack<Card> currentStack = null;
		Card cardToDisplay;
		int panelQty = stackContainer.elementCount; // Record the number of
													// panels in our
		int stackNumber = 0; // ...Stack-Container, and start looping at
		int cardLoc = 0; // ...Panel #0

		while (stackNumber < panelQty) // While there are still stacks to
										// display
		{
			cardLoc = 0;
			while (cardLoc < DECKSIZE) // ...and while there cards left to
										// display
			{
				currentStack = stackContainer.stack[stackNumber]; // Assign the
																	// stack
																	// holding
																	// our card
				cardToDisplay = (currentStack.top()); // Assign our card to that
														// stack's top card
				thisView.DisplayImage(cardToDisplay, stackNumber); // Display
																	// our card
				currentStack.pop(); // Pop the card from our Panel Container...
				cardLoc++; // ...and move on to the next card
			}
			stackNumber++; // Then move on to the next Panel to output...
		}
	}
}