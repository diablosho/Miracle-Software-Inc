#include <stdio.h>

void main()
{
	int numShiftChars=0, loopCounter;
	char stringToEncrypt[80];
	char stringEncrypted[80];
	
	for (loopCounter=0; loopCounter<80; loopCounter++)
		stringEncrypted[loopCounter]=0x00;
	loopCounter=0;
	printf("Enter message to be encrypted:  ");
	gets(stringToEncrypt);
	printf("Enter shift amount (1-25):  ");
	scanf("%d", &numShiftChars);
	printf("Encrypted message:  ");

	for (loopCounter=0; loopCounter < sizeof(stringToEncrypt)-1; loopCounter++)
	{
		stringEncrypted[loopCounter] = stringToEncrypt[loopCounter] + numShiftChars;
		if ((stringToEncrypt[loopCounter] >= 0x41 && stringToEncrypt[loopCounter] <= 0x5A) && stringEncrypted[loopCounter] > 0x5A)
			stringEncrypted[loopCounter] = (stringEncrypted[loopCounter] - 0x5A) + 0x41;
		else if ((stringToEncrypt[loopCounter] >= 0x61 && stringToEncrypt[loopCounter] <= 0x7A) && stringEncrypted[loopCounter] > 0x7A)
			stringEncrypted[loopCounter] = (stringEncrypted[loopCounter] - 0x7A) + 0x61;
		putchar(stringEncrypted[loopCounter]);
	}
	scanf("%d", &numShiftChars);
}