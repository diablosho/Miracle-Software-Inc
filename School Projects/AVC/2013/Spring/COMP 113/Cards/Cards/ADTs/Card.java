package ADTs;

import javax.swing.ImageIcon;

public class Card
{
	protected 	String		cardSuit	=	"None";	// cardSuit is the numerical value of our card's suit
	protected 	int			cardValue	=	1;		// cardValue is the numerical value of our card's value
	public 		ImageIcon	imgCard		=	null;		// imgCard will contain our card's image

	public Card()								// Default Constructor for Inheritance-purposes
	{
	} 

	public Card(int cardValue, int cardSuit)
	{
		this.cardValue = cardValue;		// Equate cardValue with the cardValue parameter

		switch (cardSuit)				// Switch, based on the card's suit, to assign a string value to the Card
		{
		case 1:	this.cardSuit = "Hearts";	break;	// if cardSuit = 1, then Card's cardSuit = "Hearts" 
		case 2:	this.cardSuit = "Diamonds";	break;	// if cardSuit = 2, then Card's cardSuit = "Diamonds" 
		case 3:	this.cardSuit = "Spades";	break;	// if cardSuit = 3, then Card's cardSuit = "Spades" 
		case 4:	this.cardSuit = "Clubs";	break; 	// if cardSuit = 4, then Card's cardSuit = "Clubs"
		default:this.cardSuit = "NONE";		return;	// if cardSuit != those, then there was an Error 
		}

		imgCard = GetCardImage(cardValue, cardSuit); 	// imgCard = ImageIcon, based on GetCardImage's return
	}

	public ImageIcon GetCardImage(int cardValue, int cardSuit)
	{											// Get the Card's Image based on the cardValue and cardSuit
		switch (cardSuit)
		{
		case 1: // Hearts
		{
			switch (cardValue)	// Return an ImageIcon, pointing to the card's image, labeled with the card's string
			{
			case 2:	return (new ImageIcon(getClass().getResource("/Resources/2h.jpg"), "Two of Hearts"));
			case 3:	return (new ImageIcon(getClass().getResource("/Resources/3h.jpg"), "Three of Hearts"));
			case 4:	return (new ImageIcon(getClass().getResource("/Resources/4h.jpg"), "Four of Hearts"));
			case 5:	return (new ImageIcon(getClass().getResource("/Resources/5h.jpg"), "Five of Hearts"));
			case 6:	return (new ImageIcon(getClass().getResource("/Resources/6h.jpg"), "Six of Hearts"));
			case 7:	return (new ImageIcon(getClass().getResource("/Resources/7h.jpg"), "Seven of Hearts"));
			case 8:	return (new ImageIcon(getClass().getResource("/Resources/8h.jpg"), "Eight of Hearts"));
			case 9:	return (new ImageIcon(getClass().getResource("/Resources/9h.jpg"), "Nine of Hearts"));
			case 10:return (new ImageIcon(getClass().getResource("/Resources/10h.jpg"), "Ten of Hearts"));
			case 11:return (new ImageIcon(getClass().getResource("/Resources/jh.jpg"), "Jack of Hearts"));
			case 12:return (new ImageIcon(getClass().getResource("/Resources/qh.jpg"), "Queen of Hearts"));
			case 13:return (new ImageIcon(getClass().getResource("/Resources/kh.jpg"), "King of Hearts"));
			case 14:return (new ImageIcon(getClass().getResource("/Resources/ah.jpg"), "Ace of Hearts"));
			}
		}
		case 2: // Diamonds
		{
			switch (cardValue)
			{
			case 2:	return (new ImageIcon(getClass().getResource("/Resources/2d.jpg"), "Two of Diamonds"));
			case 3:	return (new ImageIcon(getClass().getResource("/Resources/3d.jpg"), "Three of Diamonds"));
			case 4:	return (new ImageIcon(getClass().getResource("/Resources/4d.jpg"), "Four of Diamonds"));
			case 5:	return (new ImageIcon(getClass().getResource("/Resources/5d.jpg"), "Five of Diamonds"));
			case 6:	return (new ImageIcon(getClass().getResource("/Resources/6d.jpg"), "Six of Diamonds"));
			case 7:	return (new ImageIcon(getClass().getResource("/Resources/7d.jpg"), "Seven of Diamonds"));
			case 8:	return (new ImageIcon(getClass().getResource("/Resources/8d.jpg"), "Eight of Diamonds"));
			case 9:	return (new ImageIcon(getClass().getResource("/Resources/9d.jpg"), "Nine of Diamonds"));
			case 10:return (new ImageIcon(getClass().getResource("/Resources/10d.jpg"), "Ten of Diamonds"));
			case 11:return (new ImageIcon(getClass().getResource("/Resources/jd.jpg"), "Jack of Diamonds"));
			case 12:return (new ImageIcon(getClass().getResource("/Resources/qd.jpg"), "Queen of Diamonds"));
			case 13:return (new ImageIcon(getClass().getResource("/Resources/kd.jpg"), "King of Diamonds"));
			case 14:return (new ImageIcon(getClass().getResource("/Resources/ad.jpg"), "Ace of Diamonds"));
			}
		}
		case 3: // Spades
		{
			switch (cardValue)
			{
			case 2:	return (new ImageIcon(getClass().getResource("/Resources/2s.jpg"), "Two of Spades"));
			case 3:	return (new ImageIcon(getClass().getResource("/Resources/3s.jpg"), "Three of Spades"));
			case 4:	return (new ImageIcon(getClass().getResource("/Resources/4s.jpg"), "Four of Spades"));
			case 5:	return (new ImageIcon(getClass().getResource("/Resources/5s.jpg"), "Five of Spades"));
			case 6:	return (new ImageIcon(getClass().getResource("/Resources/6s.jpg"), "Six of Spades"));
			case 7:	return (new ImageIcon(getClass().getResource("/Resources/7s.jpg"), "Seven of Spades"));
			case 8:	return (new ImageIcon(getClass().getResource("/Resources/8s.jpg"), "Eight of Spades"));
			case 9:	return (new ImageIcon(getClass().getResource("/Resources/9s.jpg"), "Nine of Spades"));
			case 10:return (new ImageIcon(getClass().getResource("/Resources/10s.jpg"), "Ten of Spades"));
			case 11:return (new ImageIcon(getClass().getResource("/Resources/js.jpg"), "Jack of Spades"));
			case 12:return (new ImageIcon(getClass().getResource("/Resources/qs.jpg"), "Queen of Spades"));
			case 13:return (new ImageIcon(getClass().getResource("/Resources/ks.jpg"), "King of Spades"));
			case 14:return (new ImageIcon(getClass().getResource("/Resources/as.jpg"), "Ace of Spades"));
			}
		}
		case 4: // Clubs
		{
			switch (cardValue)
			{
			case 2:	return (new ImageIcon(getClass().getResource("/Resources/2c.jpg"), "Two of Clubs"));
			case 3:	return (new ImageIcon(getClass().getResource("/Resources/3c.jpg"), "Three of Clubs"));
			case 4:	return (new ImageIcon(getClass().getResource("/Resources/4c.jpg"), "Four of Clubs"));
			case 5:	return (new ImageIcon(getClass().getResource("/Resources/5c.jpg"), "Five of Clubs"));
			case 6:	return (new ImageIcon(getClass().getResource("/Resources/6c.jpg"), "Six of Clubs"));
			case 7:	return (new ImageIcon(getClass().getResource("/Resources/7c.jpg"), "Seven of Clubs"));
			case 8:	return (new ImageIcon(getClass().getResource("/Resources/8c.jpg"), "Eight of Clubs"));
			case 9:	return (new ImageIcon(getClass().getResource("/Resources/9c.jpg"), "Nine of Clubs"));
			case 10:return (new ImageIcon(getClass().getResource("/Resources/10c.jpg"), "Ten of Clubs"));
			case 11:return (new ImageIcon(getClass().getResource("/Resources/jc.jpg"), "Jack of Clubs"));
			case 12:return (new ImageIcon(getClass().getResource("/Resources/qc.jpg"), "Queen of Clubs"));
			case 13:return (new ImageIcon(getClass().getResource("/Resources/kc.jpg"), "King of Clubs"));
			case 14:return (new ImageIcon(getClass().getResource("/Resources/ac.jpg"), "Ace of Clubs"));
			}
		}
		}
		return null;
	}

	@Override
	public String toString() // Convert the card's numerical card value, and card suit, to a String Card description
	{
		String card = null;

		switch (this.cardValue)
		// Switch based on the card's value, and assign a string to the Card
		{
		case 2:	card = "Two of " + cardSuit;	break;
		case 3:	card = "Three of " + cardSuit;	break;
		case 4:	card = "Four of " + cardSuit;	break;
		case 5:	card = "Five of " + cardSuit;	break;
		case 6:	card = "Six of " + cardSuit;	break;
		case 7:	card = "Seven of " + cardSuit;	break;
		case 8:	card = "Eight of " + cardSuit;	break;
		case 9:	card = "Nine of " + cardSuit;	break;
		case 10:card = "Ten of " + cardSuit;	break;
		case 11:card = "Jack of " + cardSuit;	break;
		case 12:card = "Queen of " + cardSuit;	break;
		case 13:card = "King of " + cardSuit;	break;
		case 14:card = "Ace of " + cardSuit;	break;
		default: 			/* Error */			return ("Card Value Error");
		}
		return card;
	}
}
