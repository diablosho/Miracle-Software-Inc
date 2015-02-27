#include <stdio.h>
void populateDeck(), shuffleDeck(), dealDeck(int indexNextCard);
int deck[52][2];

int main()
{
	int hand[5][4];
	int indexNextCard=0;
	populateDeck();
	//shuffleDeck();
	dealDeck(0);			// 0 is the index of the top card in the shuffled deck to begin dealing the cards to the hand for play.
	scanf("%c");
	return 0;
}

void populateDeck()
{
/*	This function is essential.
	First, populate deck[card (0-12)][suit (0-3)]
	For instance:  deck[5][2] = (cardCounter*4) + suitCounter = 22, or, "8 of Hearts"
*/
	int card, suit;

	for (card = 0; card < 52; card++)
		for (suit=0; suit<4; suit++)
		{
			deck[card][0] = card
		}
}

void shuffleDeck()
{

}

void dealDeck(int indexNextCard)
{
/*	Deal 5 cards to hand
	int lastCardToDeal = indexNextCard+5;
	while (indexNextCard < lastCardToDeal)
	{
		printf("%d\n", deck[indexNextCard]);
		indexNextCard++;
	}*/
	int i;
	for (i=0; i<52; i++)
	{
		printf("%i\n", deck[i]);
	}
}
