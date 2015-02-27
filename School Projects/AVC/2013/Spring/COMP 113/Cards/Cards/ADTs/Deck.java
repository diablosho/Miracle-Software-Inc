package ADTs;

import java.util.Random;

import Stacks.ArrayListStack;

public class Deck extends Card
{
	private static final int	POPPED			= 2;			// Instead of
																// the abstract
																// '2', I will
																// type 'POPPED'
	private static final int	SHUFFLED		= 1;			// Instead of
																// the abstract
																// '1', I will
																// type
																// 'SHUFFLED'
	private static final int	UNSHUFFLED		= 0;			// Instead of
																// the abstract
																// '0', I will
																// type
																// 'UNSHUFFLED'
	int							DECKSIZE		= 52;
	public ArrayListStack<Card>	deckStack		= null;		// Create a
																// pointer to
																// the stack
	protected Random			rand			= new Random(); // Random number
																// generator,
																// used to
																// shuffle the
																// deck
	ArrayListStackContainer		stackContainer	= null;		// Container for
																// the
																// individual
																// card-stacks

	public Deck(int deckSize) // Algorithm to create the deck for GUI & Console
								// output;
	{
		deckStack = new ArrayListStack<Card>(); // Create a new stack to hold
												// our cards in a linear fashion
		DECKSIZE = deckSize; // Formally initialize our deck size

		for (int cardValue = 14; cardValue >= 2; cardValue--) // Loop through
																// deck's values
																// in decreasing
																// order
		{
			for (int cardSuit = 4; cardSuit >= 1; cardSuit--) // Loop through
																// deck's suits
																// in decreasing
																// order
			{
				Card card = new Card(cardValue, cardSuit); // Create a Card
															// based on the
															// Card's value and
															// suit
				deckStack.push(card); // Push the Card onto the stack
			}
		}
	}

	// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// //////////////////////////////////////////// SHUFFLE THE CARDS
	// ////////////////////////////////////////////////
	// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	public void ShuffleCards(ArrayListStack<Card> stack)
	{
		stackContainer = new ArrayListStackContainer(3); // Create a container
															// for each of our
															// deck stacks
		stackContainer.stack[UNSHUFFLED] = deckStack; // Point our
														// unshuffled-stack
														// towards our
														// pre-created deck

		int cardLocation = 0; // Start at zero-index
		int cardCount = deckStack.elementCount; // Record the size of our deck,
												// since it will be changing...

		for (int currentIndex = 0; currentIndex < DECKSIZE; currentIndex++) // While
																			// there
																			// are
																			// still
																			// cards
																			// in
																			// the
																			// deck...
		{
			cardLocation = rand.nextInt(cardCount); // Assign a random location
													// in the deck to pop a card
													// out of

			int sub_loopIndex = 0;
			while (sub_loopIndex < cardLocation) // While we haven't reached OUR
													// card yet...
			{
				stackContainer.stack[UNSHUFFLED].popInto( // Pop the cards into
															// the...
						stackContainer.stack[POPPED]); // ...popped-stack
				sub_loopIndex++;
			}
			stackContainer.stack[UNSHUFFLED].popInto( // Now pop OUR card
														// into...
					stackContainer.stack[SHUFFLED]); // ...our Shuffled-Stack
			stackContainer.stack[UNSHUFFLED].incorporate( // Now restore our
															// unshuffled stack
															// (minus our
															// card)...
					stackContainer.stack[POPPED]); // ...from our Popped-Stack
			cardCount--; // Decrease the counter of cards to randomly choose
							// from
		}
		deckStack = stackContainer.stack[SHUFFLED]; // Point our deckStack to
													// our Shuffled-Stack
	}
}