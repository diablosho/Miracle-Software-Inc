/*
Name:	Brian Jones
Date:	2012-03-10
Assignment:	Chapter 4 Part 1, #3

	This program will input two dates from the user, and then determine which date
		comes first (in numerical order).  It will then output which of the two dates
		came first (chronologically).  If the two dates are equal to each other, then
		the program will output that "You entered the same date twice" and prompt you
		to enter a new set of dates.
*/
#include <stdio.h>	// Used for scanf/printf functions

void main()
{
	int month1=0, month2=0, day1=0, day2=0, year1=0, year2=0;

	do
	{
		printf("Enter first date (mm/dd/yyyy):  ");							// Prompt user for date1
		scanf("%2d/%2d/%4d", &month1, &day1, &year1);	
		printf("Enter second date (mm/dd/yyyy):  ");						// Prompt user for date2
		scanf("%2d/%2d/%4d", &month2, &day2, &year2);
		
		if ((year1 == year2)	&& (month1 == month2) && (day1 == day2))	// if date1 = date2
			printf("You entered the same date twice\n");					// Print error message
	}	while ((year1 == year2)	&& (month1 == month2) && (day1 == day2));	// repeat for two diff. inputs

	if	(((year1 == year2)	&& (month1 == month2) && (day1 < day2))	||		// day1 < day2 OR
		 ((year1 == year2)	&& (month1 < month2))					||		// ..month1 < month2 OR
		  (year1 < year2))													// ..year1 < year2
		printf("%d/%d/%d is earlier than %d/%d/%d", month1, day1, year1,	// date1 < date2
													month2, day2, year2);

	else if (((year1 == year2)	&& (month1 == month2) && (day1 > day2))	||	// day2 > day1 OR
		 ((year1 == year2)	&& (month1 > month2))						||	// ..month2 > month1 OR
		  (year1 > year2))													// ..year2 > year1
		printf("%d/%d/%d is earlier than %d/%d/%d", month2, day2, year2,	// date2 < date1
													month1, day1, year1);

	scanf("%d", &month1);													// Pause console
}