#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef	unsigned char BYTE;
const	char*	SPECIAL_CHARACTERS[]	=	{	"NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", 
												"EM", "SUB", "ESC", "FS", "GS", "RS", "US", "DEL"	};

BYTE	inputBuffer[7],
		outputASCII[4],
		outputParity[5],
		outputTransmissionError[6],
		outputNumerical;
int		pFile;

void CheckParity()	//	Assuming even parity;  *******DOES NOT WORK PROPERLY YET...*********
{
	int	countOnes = 0,
		curBinaryDigit = 0,
		bitParity = outputNumerical & 0x80,
		i = 0;

	outputNumerical = (BYTE)strtol(inputBuffer, NULL, 2);
	
	for (i = 0, curBinaryDigit = 1; i < 8; i++, curBinaryDigit *= 2)
	{
		if ((outputNumerical & curBinaryDigit) == curBinaryDigit)
			countOnes++;
	}

	if (bitParity == 0x80)		//	Parity Bit = 1, so Even Parity is being used
	{
		if ((countOnes % 2) == 0)	//	Even number of ones...
		{
			strncpy(outputParity, "EVEN\0", 5);
			strncpy(outputTransmissionError, "FALSE\0", 6);
		}
		else
		{
			strncpy(outputParity, "ODD\0", 4);
			strncpy(outputTransmissionError, "TRUE\0", 5);
		}
	}
	else	//	Parity Bit = 0, so Odd Parity is being used
	{
		if ((countOnes % 2) == 0)	//	Even number of ones...
		{
			strncpy(outputParity, "EVEN\0", 5);
			strncpy(outputTransmissionError, "TRUE\0", 5);
		}
		else
		{
			strncpy(outputParity, "ODD\0", 4);
			strncpy(outputTransmissionError, "FALSE\0", 6);
		}
	}
}

void GetAscii()
{
	int i = 0;
	for (i = 0; i < 3; i++)
		outputASCII[i] = NULL;

	outputNumerical = (BYTE)(strtol(inputBuffer, NULL, 2) & 0x7F);
	if (outputParity == "EVEN" && inputBuffer[0] == '1')
		outputNumerical++;

	if ((outputNumerical > 0x1F) && (outputNumerical != 0x7F))
		outputASCII[0] = outputNumerical;
	else if (outputNumerical == 0x7F)
		strncpy(outputASCII, SPECIAL_CHARACTERS[20], sizeof(SPECIAL_CHARACTERS[20]));
	else
		strncpy(outputASCII, SPECIAL_CHARACTERS[outputNumerical], sizeof(SPECIAL_CHARACTERS[outputNumerical]));
}

void ProcessChar()
{
	CheckParity();
	GetAscii();
	printf("%8s\t%5s\t\t%5d\t\t%5s\t\t%5s\n", inputBuffer, outputASCII, outputNumerical, outputParity, outputTransmissionError);
}

void ParseInput()
{
	int		charPos = 0,
			bytesRead = 0;
	BYTE	tempBuffer[1] = { NULL };
	do
	{
		bytesRead = read(pFile, tempBuffer, 1);
		inputBuffer[charPos] = tempBuffer[0];
		
		if (inputBuffer[charPos] == '1' || inputBuffer[charPos] == '0')
		{
			if (charPos == 7)
			{
				charPos = -1;
				ProcessChar();
			}
			charPos += bytesRead;
		}		
	} while (bytesRead != 0);
	
	if ((charPos > 0) && (charPos < 8))	//	Add padding
	{
		for (; charPos < 8; charPos++)
			inputBuffer[charPos] = '0';
				
		ProcessChar();
	}

	close(pFile);
}

int	main(int argc, char** argv)
{
	int i = 0;

	printf("Original\t  ASCII  \tDecimal\t\t Parity\t\tT.Error\n");
	printf("--------\t--------\t--------\t--------\t--------\n");
	
	if (argc == 1)	//	No arguments were passed via the Command-Line, so they must be coming via stdin...
	{
		pFile = stdin;
		ParseInput();
	}
	else
	{
		for (i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-") == 0)		//	Argument meaning that input is coming in from stdin...
			{
				pFile = stdin;
				ParseInput();
			}
			else
			{
				if (access(argv[i], 0) != -1)			//	file exists
				{
					pFile = open(argv[i], 0);
					ParseInput();
				}
			}
		}
	}
	return 0;
}
