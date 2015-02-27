/*
Name:  Brian Jones
Date:  2012-04-23
Assignment:	Chapter 7, Assignment #3

	This program will input the first word from the user.  It will then find each actual letter and convert
	them to upper-case.  Once standardized to upper-case, the program will then loop through all elements 
	in the word, subtracting 41h (65d) from each character, thus making each element in the charArray array
	equivalent to an ASCII character: ('A' - 41h = 0, thus charArray[0] = 'A').  Finally, the program will 
	increment each value in charArray for each occurence of every letter in the first word, thus creating a 
	log of every letter and how many of them are present.

	Next, this program will input a second word from the user.  It will then find each actual letter and 
	convert them to upper-case.  Once standardized to upper-case, the program will then loop through all 
	elements in the word, subtracting 41h (65d) from each character, thus making each element in the 
	charArray array equivalent to an ASCII character: ('A' - 41h = 0, thus charArray[0] = 'A').  Finally, 
	the program will decrement each value in charArray for each occurence of every letter in the first word, 
	thus cancelling each character that is used in BOTH words.
	
	Once both words are processed, the program will loop through each element in charArray, looking for any 
	non-zero number, indicating extra letters in either of the words (positive num. = extra in first word, 
	negative num. = extra in second word).  If all elements equal zero, then we know that all letters used 
	in the first word are also present in the same quantity in the second word, indicating that both words 
	are, in fact, anagrams.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void main()
{
	int charArray[26]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int index=0;
	char firstWord[100], secondWord[100];	// first and second word must be less than 100 characters
	char result[7] = "is";	//
	int loopCounter=0;											// counter for each character-counting loop
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	///  Input first word into firstWord variable, and loop through all elements in firstWord,			///
	///  determining if each element is an actual letter, and if isalpha() = true, then convert each	///
	///  uppercase character into a zero-based index (by subtracting 65d) to increment the proper		///
	///  charArray element.																				///
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	
	printf("Please enter first word:  ");
	scanf("%99s", firstWord);
	for (loopCounter=0; loopCounter<strlen(firstWord)+1; loopCounter++)
	{
		if (isalpha(firstWord[loopCounter]))
			charArray[(toupper(firstWord[loopCounter]))-65]++;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	///  Input second word into secondWord variable, and loop through all elements in secondWord,		///
	///  determining if each element is an actual letter, and if isalpha() = true, then convert each	///
	///  uppercase character into a zero-based index (by subtracting 65d) to increment the proper		///
	///  charArray element.																				///
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	
	printf("\nPlease enter second word:  ");
	scanf("%99s", secondWord);
	index=0;
	for (loopCounter=0; loopCounter<strlen(secondWord)+1; loopCounter++)
	{
		if (isalpha(secondWord[loopCounter]))
			charArray[(toupper(secondWord[loopCounter]))-65]--;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Loop through all charArray elements, and test if each equal zero.  If not, then there must be an ///
	/// extra letter in one of the words, thus the words are NOT anagrams.  Otherwise, if all elements	 ///
	/// equal zero, then we must have an anagram.                                                        ///
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	while (loopCounter > 0)
	{
		if (charArray[loopCounter] != 0)
			strcpy(result, "is NOT");
		loopCounter--;
	}
	
	printf("%s %s an anagram with %s", firstWord, result, secondWord);	// Print result of anagram test
	scanf("%s", secondWord);											// To pause console termination
}