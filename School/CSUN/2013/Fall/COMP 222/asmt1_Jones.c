/*
Name:	Brian Jones
Date:	9/18/2013
Course:	CIS 222
Assignment #1:	Performance Assessment
*/
#include <stdio.h>
#include <stdlib.h>

int		numClasses			=	0,		//	input:	quantity of Classes
		machineFreq			=	0,		//	input:	frequency of machine (MHz)
		qtyInstructions		=	0;		//	calculated total number of instructions
float 	avgCPI				=	0,		//	calculated average Cycles per Instruction
		totalCPUTime		=	0,		//	calculated total time for CPU to execute instructions
		totalMIPS			=	0;		//	calculated Millions Instructions per Second
int*	classCPI			=	{0};	//	Array to hold each class' CPI
int*	classInstCount		=	{0};	//	Array to hold each class' Instruction Count
/******************************************************************************************************************************/
void EnterParams()	//	Procedure for Data Entry
{
	int i = 0;		//	Counter variable

	printf("Enter the number of instruction classes:  ");
	scanf("%i", &numClasses);
	printf("Enter the frequency of the machine (MHz):  ");
	scanf("%i", &machineFreq);

	classCPI = (int *)malloc(numClasses * sizeof(int));			//	Re-Allocate classCPI
	classInstCount = (int *)malloc(numClasses * sizeof(int));	//	Re-Allocate classInstCount
	
	for (i = 0; i < numClasses; i++)							//	Loop through all numClasses that were entered
	{
		printf("Enter CPI of class %1i:  ", 1+i);							//	Ask for all class' CPIs
		scanf("%i", &classCPI[i]);
		printf("Enter instruction count of class %1i (millions):  ", 1+i);	//	Ask for all class' Instruction Counts
		scanf("%i", &classInstCount[i]);
		qtyInstructions += classInstCount[i];								//	Keep track of Total Instructions
	}
	printf("\n");
	return;
}

/******************************************************************************************************************************/
void CalculateAvgCPI()			//	Procedure to calculate the Average Cycles per Instruction
{
	int i = 0;		//	Counter variable
	
	for (i = 0; i < numClasses; i++)							//	Loop through all classes that were entered...
		avgCPI += (float)(classInstCount[i] * classCPI[i]);		//...adding each class' total Cycles...
	avgCPI /= (float)qtyInstructions;							//...then average with total Instruction Count

	printf("The average CPI of the sequence is:  %.2f\n\n", avgCPI);
	return;
}

/******************************************************************************************************************************/
void CalculateTotalExecutionTime()		//	Procedure to calculate the Total Execution Time
{
	int i = 0;		//	Counter variable
	
	totalCPUTime = (qtyInstructions)*(avgCPI)*(1000.0/machineFreq);		//	Calculate total execution time 
	
	printf("The total CPU time of the sequence is:  %.2f msec\n\n", totalCPUTime);
	return;
}

/******************************************************************************************************************************/
void CalculateMIPS()		//	Procedure to calculate the Millions of Instructions executed Per Second
{
	totalMIPS = (qtyInstructions / (totalCPUTime));		//	Total MIPS = (Total Instructions / time per Instruction)
		
	printf("The total MIPS of the sequence is:  %.2f\n\n", totalMIPS);		/*	Print out result	*/
	return;
}

/******************************************************************************************************************************/
int main()
{
	int sel_Menu = 0;		//	Initialize menu selection

	do
	{
		printf("Performance assessment:\n"
				"-----------------------\n"
				"1)  Enter parameters\n"
				"2)  Calculate average CPI of a sequence of instructions\n"
				"3)  Calculate total execution time of a sequence of instructions\n"
				"4)  Calculate MIPS of a sequence of instructions\n"
				"5)  Quit\n\n"
				"Enter selection:  ");
	
		scanf("%1i", &sel_Menu);							//	Input menu selection

		switch (sel_Menu)
		{
		case 1:		EnterParams();					break;	//	Enter Parameters
		case 2:		CalculateAvgCPI();				break;	//	Calculate Average CPI of a Sequence of Instructions
		case 3:		CalculateTotalExecutionTime();	break;	//	Calculate total execution time of a sequence of instructions
		case 4:		CalculateMIPS();				break;	//	Calculate MIPS of a sequence of instructions
		case 5:		return 1;						break;	//	Quit
		default:									break;	//	Invalid Selection (either <1 or >6)
		}
	}	while (sel_Menu != 5);

	return 1;
}