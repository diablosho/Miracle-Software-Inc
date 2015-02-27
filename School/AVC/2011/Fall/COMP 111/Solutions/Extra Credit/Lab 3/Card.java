
public class Card
{
	public String[] cardValueAndSuit = new String[2];
	final String[][] cardValues = 
	{
		{"Hearts", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"}, 
		{"Diamonds", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"}, 
		{"Spades", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"}, 
		{"Clubs", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"}
	};
	
	public Card (int Suit, int Value)
	{
		toString(Suit);
		toString(null, Value);
	}
	public String toString(int Suit)
	{
			return cardValues[Suit][0];
	}
	public String toString(<null>, int Suit)
	{
			return cardValues[0][Values];
	}
}
