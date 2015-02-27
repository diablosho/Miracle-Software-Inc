#include "StdAfx.h"
#include "HexOps.h"


CHexOps::CHexOps()
{
}


CHexOps::~CHexOps()
{
}


CString CHexOps::HexToBinaryString(CString Instruction)
{
	int i=1;
	while (i>=0)
	{
		if (Instruction.GetAt(i)=='0')	Instruction=ReplaceValue(Instruction, i, CString("0000"));
		if (Instruction.GetAt(i)=='1')	Instruction=ReplaceValue(Instruction, i, CString("0001"));
		if (Instruction.GetAt(i)=='2')	Instruction=ReplaceValue(Instruction, i, CString("0010"));
		if (Instruction.GetAt(i)=='3')	Instruction=ReplaceValue(Instruction, i, CString("0011"));
		if (Instruction.GetAt(i)=='4')	Instruction=ReplaceValue(Instruction, i, CString("0100"));
		if (Instruction.GetAt(i)=='5')	Instruction=ReplaceValue(Instruction, i, CString("0101"));
		if (Instruction.GetAt(i)=='6')	Instruction=ReplaceValue(Instruction, i, CString("0110"));
		if (Instruction.GetAt(i)=='7')	Instruction=ReplaceValue(Instruction, i, CString("0111"));
		if (Instruction.GetAt(i)=='8')	Instruction=ReplaceValue(Instruction, i, CString("1000"));
		if (Instruction.GetAt(i)=='9')	Instruction=ReplaceValue(Instruction, i, CString("1001"));
		if (Instruction.GetAt(i)=='A')	Instruction=ReplaceValue(Instruction, i, CString("1010"));
		if (Instruction.GetAt(i)=='B')	Instruction=ReplaceValue(Instruction, i, CString("1011"));
		if (Instruction.GetAt(i)=='C')	Instruction=ReplaceValue(Instruction, i, CString("1100"));
		if (Instruction.GetAt(i)=='D')	Instruction=ReplaceValue(Instruction, i, CString("1101"));
		if (Instruction.GetAt(i)=='E')	Instruction=ReplaceValue(Instruction, i, CString("1110"));
		if (Instruction.GetAt(i)=='F')	Instruction=ReplaceValue(Instruction, i, CString("1111"));
		i--;
	}
	return Instruction;
}


CString CHexOps::ReplaceValue(CString Instruction, int Position, CString ReplacementString)
{
	Instruction.Delete(Position, 1);
	Instruction.Insert(Position, ReplacementString);
	return Instruction;
}


CString CHexOps::BinaryToHex(long charArray)
{
	CString hexString, charToAppend;
	int index=0;
	char nibble[8];

	nibble[0] = (charArray << 0) >> 28;
	nibble[1] = (charArray << 4) >> 28;
	nibble[2] = (charArray << 8) >> 28;
	nibble[3] = (charArray << 12) >> 28;
	nibble[4] = (charArray << 16) >> 28;
	nibble[5] = (charArray << 20) >> 28;
	nibble[6] = (charArray << 24) >> 28;
	nibble[7] = (charArray << 28) >> 28;
	
	do
	{
		for (int nibbleNum = 0; nibbleNum < 8; nibbleNum++)
		{
			if (nibble[nibbleNum] == '\x00') charToAppend = "0";
			if (nibble[nibbleNum] == '\x01') charToAppend = "1";
			if (nibble[nibbleNum] == '\x02') charToAppend = "2";
			if (nibble[nibbleNum] == '\x03') charToAppend = "3";
			if (nibble[nibbleNum] == '\x04') charToAppend = "4";
			if (nibble[nibbleNum] == '\x05') charToAppend = "5";
			if (nibble[nibbleNum] == '\x06') charToAppend = "6";
			if (nibble[nibbleNum] == '\x07') charToAppend = "7";
			if (nibble[nibbleNum] == '\x08') charToAppend = "8";
			if (nibble[nibbleNum] == '\x09') charToAppend = "9";
			if (nibble[nibbleNum] == '\x0A') charToAppend = "A";
			if (nibble[nibbleNum] == '\x0B') charToAppend = "B";
			if (nibble[nibbleNum] == '\x0C') charToAppend = "C";
			if (nibble[nibbleNum] == '\x0D') charToAppend = "D";
			if (nibble[nibbleNum] == '\x0E') charToAppend = "E";
			if (nibble[nibbleNum] == '\x0F') charToAppend = "F";
			hexString.Append(charToAppend);
		}
		index+=4;
	}	while (index < sizeof(charArray));

	return hexString;
}
