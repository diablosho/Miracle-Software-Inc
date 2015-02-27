/*
Name:        Brian Jones
Assignment:  Chapter 3-Exercise 2
		  	 This program will input a compression load, and compute the diameter of a steel, aluminum, and copper rod (in centimeters)
			 necessary to withstand a particular compression load.  
			 
			 Allowable compression stress:
				Steel:		25,000 lbs/m^2
				Aluminum:	15,000 lbs/m^2
				Copper:		20,000 lbs/m^2
			 Area of rod = Compression Load/Allowable Compression Stress
			 Area = (Pi)*(r^2), Diameter = 2r
*/
#include <stdio.h>	// Library for c++ standard input/output functions
#include <math.h>

int main()
{
	const float PI = 3.141593;
	int counter;									// Counter-variable for repetition loop
	float compressionLoad=0.0;
	float steelRodArea, steelRodDiameter, aluminumRodArea, aluminumRodDiameter, copperRodArea, copperRodDiameter;

	for (counter=0; counter<3; counter++)			// Repetition loop (3 reps)
	{
		printf("Enter the compression load:  ");
		scanf("%f", &compressionLoad);
	
		steelRodDiameter = sqrt((compressionLoad/25000)/PI)*2;		// steelRodArea=(compressionLoad/25000);
		aluminumRodDiameter = sqrt((compressionLoad/15000)/PI)*2;	// aluminumRodArea=(compressionLoad/15000);
		copperRodDiameter = sqrt((compressionLoad/20000)/PI)*2;		// copperRodArea=(compressionLoad/20000);

		printf("Steel:\nCompression Load:  %f\nAllowable Stress:  25,000 lbs/sq. meter\nMinimum Diameter:  %f\n\n", compressionLoad, steelRodDiameter);
		printf("Aluminum:\nCompression Load:  %f\nAllowable Stress:  15,000 lbs/sq. meter\nMinimum Diameter:  %f\n\n", compressionLoad, aluminumRodDiameter);
		printf("Copper:\nCompression Load:  %f\nAllowable Stress:  20,000 lbs/sq. meter\nMinimum Diameter:  %f\n\n", compressionLoad, copperRodDiameter);
	}
	scanf("%f", &compressionLoad);
	return 0;
}