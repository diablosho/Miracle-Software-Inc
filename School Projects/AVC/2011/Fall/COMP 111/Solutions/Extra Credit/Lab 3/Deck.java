
public class Deck 
{
	private Card deck;
	private int nextCardOnDeck;
	
	public Deck ()
	{
		shuffle();
		while (nextCardOnDeck < 5)
		{
			nextCardOnDeck++;
		}
	}
	public void shuffle()
	{
	}
	public Card deal()
	{
		return deck;
	}
}
