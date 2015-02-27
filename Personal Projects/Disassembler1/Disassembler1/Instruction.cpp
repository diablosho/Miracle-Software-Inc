#include "StdAfx.h"
#include "Instruction.h"

CInstruction::CInstruction(byte* bytesRead, int Size)
	: data(new byte[Size])
	, InstructionPointer(0)
	, InstructionOffset(0)
	, EndOfInstructions(false)
	, dataSize(Size)
	, CurrentAddressingWordSize(32)
{
	data = bytesRead;
	ProcessInstruction();
}


CInstruction::~CInstruction(void)
{
}


void CInstruction::ParsePrefixes()
{
	int count=0;
	for (count = 0; count < 4; count++)
	{
		if (InstructionPointer < dataSize)
		{
			switch (data[InstructionPointer])
			{
				case 0xF3:{	Prefixes[0]=true;	IncrementCounters(1);	break;}
				case 0xF2:{	Prefixes[0]=true;	IncrementCounters(1);	break;}
				case 0xF0:{	Prefixes[0]=true;	IncrementCounters(1);	break;}
				case 0x67:{	Prefixes[1]=true;	IncrementCounters(1);	break;}	// Address-Size Prefix
				case 0x66:{	Prefixes[2]=true;	IncrementCounters(1);	break;}	// Operand-Size Prefix
				case 0x26:{	Prefixes[3]=true;	IncrementCounters(1);	break;}
				case 0x2E:{	Prefixes[3]=true;	IncrementCounters(1);	break;}
				case 0x36:{	Prefixes[3]=true;	IncrementCounters(1);	break;}
				case 0x3E:{	Prefixes[3]=true;	IncrementCounters(1);	break;}
				case 0x64:{	Prefixes[3]=true;	IncrementCounters(1);	break;}
				case 0x65:{	Prefixes[3]=true;	IncrementCounters(1);	break;}
				default:						count=4;
			}
		}
	}
	if		(CurrentAddressingWordSize==32 && (Prefixes[1] || Prefixes[2]))	CurrentAddressingWordSize=16;
	else if (CurrentAddressingWordSize==16 && (Prefixes[1] || Prefixes[2]))	CurrentAddressingWordSize=32;
}


void CInstruction::ParseOpcode()
{
	if (InstructionPointer < dataSize)
	{
		Opcode[0]=data[InstructionPointer];
		IncrementCounters(1);
		if (((Opcode[0]<<6)>>7) & 0x01)	SpecialBits[0]=true;	// D-Bit
		if (((Opcode[0]<<7)>>7) & 0x01)	SpecialBits[1]=true;	// W-Bit
		if (((Opcode[0]<<6)>>7) & 0x01)	SpecialBits[2]=true;	// S-Bit
		
		if (Opcode[0]==0x0f)					// Two-Byte Opcodes
		{
			if (InstructionPointer < dataSize)
			{
				Opcode[1]=data[InstructionPointer];
				IncrementCounters(1);

				if (((Opcode[1]<<6)>>7) & 0x01)	SpecialBits[0]=true;	// D-Bit
				if (((Opcode[1]<<7)>>7) & 0x01)	SpecialBits[1]=true;	// W-Bit
				if (((Opcode[1]<<6)>>7) & 0x01)	SpecialBits[2]=true;	// S-Bit
			}
			else
				EndOfInstructions=true;
		}
		DetermineGenInstructionAndOperandTypes();
	}
	else
		EndOfInstructions=true;
}


void CInstruction::ProcessInstruction()
{
	for (int index = 0; index < dataSize; index++)
	{
		InitializeVariables(true);
		ParsePrefixes();								// Parse Prefixes
		ParseOpcode();									// Parse Opcodes
		DetermineOperand();
	
		if (!EndOfInstructions)
		{
			if (Operands[0] != "")	Instruction += CString(" ") + Operands[0];
			if (Operands[1] != "")	Instruction += CString(", ") + Operands[1];
			if (Operands[2] != "")	Instruction += CString(", ") + Operands[2];
			FinalInstruction.Add(Instruction);
		}
	}
}

void CInstruction::DetermineGenInstructionAndOperandTypes()
{
	switch (Opcode[0])
	{
		case 0x00:{	Instruction += CString(" ADD ");	OperandType[0]='E';OperandSize[0]='b';	OperandType[1]='G';OperandSize[1]='b';	break;}
		case 0x01:{	Instruction += CString(" ADD ");	OperandType[0]='E';OperandSize[0]='w';	OperandType[1]='G';OperandSize[1]='w';	break;}
		case 0x02:{	Instruction += CString(" ADD ");	OperandType[0]='G';OperandSize[0]='b';	OperandType[1]='E';OperandSize[1]='b';	break;}
		case 0x03:{	Instruction += CString(" ADD ");	OperandType[0]='G';OperandSize[0]='w';	OperandType[1]='E';OperandSize[1]='w';	break;}
		case 0x04:{	Instruction += CString(" ADD AL ");	OperandType[0]='I';OperandSize[0]='b';											break;}
		case 0x05:{	Instruction += CString(" ADD EAX ");OperandType[0]='I';OperandSize[0]='w';											break;}
		case 0x06:{	Instruction += CString(" PUSH ES ");																				break;}
		case 0x07:{	Instruction += CString(" POP ES ");																					break;}
		case 0x08:{	Instruction += CString(" OR ");		OperandType[0]='E';OperandSize[0]='b';	OperandType[1]='G';OperandSize[1]='b';	break;}
		case 0x09:{	Instruction += CString(" OR ");		OperandType[0]='E';OperandSize[0]='w';	OperandType[1]='G';OperandSize[1]='w';	break;}
		case 0x0A:{	Instruction += CString(" OR ");		OperandType[0]='G';OperandSize[0]='b';	OperandType[1]='E';OperandSize[1]='b';	break;}
		case 0x0B:{	Instruction += CString(" OR ");		OperandType[0]='G';OperandSize[0]='w';	OperandType[1]='E';OperandSize[1]='w';	break;}
		case 0x0C:{	Instruction += CString(" OR AL ");	OperandType[0]='I';OperandSize[0]='b';											break;}
		case 0x0D:{	Instruction += CString(" OR EAX ");	OperandType[0]='I';OperandSize[0]='w';											break;}
		case 0x0E:{	Instruction += CString(" PUSH CS ");																				break;}
		case 0x0F:{													DetermineTwoByteOpcodes();											break;}
		case 0x10:{	Instruction += CString(" ADC ");	OperandType[0]='E';OperandSize[0]='b';	OperandType[1]='G';OperandSize[1]='b';	break;}
		case 0x11:{	Instruction += CString(" ADC ");	OperandType[0]='E';OperandSize[0]='w';	OperandType[1]='G';OperandSize[1]='w';	break;}
		case 0x12:{	Instruction += CString(" ADC ");	OperandType[0]='G';OperandSize[0]='b';	OperandType[1]='E';OperandSize[1]='b';	break;}
		case 0x13:{	Instruction += CString(" ADC ");	OperandType[0]='G';OperandSize[0]='w';	OperandType[1]='E';OperandSize[1]='w';	break;}
		case 0x14:{	Instruction += CString(" ADC AL ");	OperandType[0]='I';OperandSize[0]='b';											break;}
		case 0x15:{	Instruction += CString(" ADC EAX");	OperandType[0]='I';OperandSize[0]='w';											break;}
		case 0x16:{	Instruction += CString(" PUSH SS");																					break;}
		case 0x17:{	Instruction += CString(" POP SS");																					break;}
		case 0x18:{	Instruction += CString(" SBB ");	OperandType[0]='E';OperandSize[0]='b';	OperandType[1]='G';OperandSize[1]='b';	break;}
		case 0x19:{	Instruction += CString(" SBB ");	OperandType[0]='E';OperandSize[0]='w';	OperandType[1]='G';OperandSize[1]='w';	break;}
		case 0x1A:{	Instruction += CString(" SBB ");	OperandType[0]='G';OperandSize[0]='b';	OperandType[1]='E';OperandSize[1]='b';	break;}
		case 0x1B:{	Instruction += CString(" SBB ");	OperandType[0]='G';OperandSize[0]='w';	OperandType[1]='E';OperandSize[1]='w';	break;}
		case 0x1C:{	Instruction += CString(" SBB AL ");	OperandType[0]='I';OperandSize[0]='b';											break;}
		case 0x1D:{	Instruction += CString(" SBB EAX ");OperandType[0]='I';OperandSize[0]='w';											break;}
		case 0x1E:{	Instruction += CString(" PUSH DS ");																				break;}
		case 0x1F:{	Instruction += CString(" POP DS ");																					break;}
		case 0x20:{	Instruction += CString(" AND ");	OperandType[0]='E';OperandSize[0]='b';	OperandType[1]='G';OperandSize[1]='b';	break;}
		case 0x21:{	Instruction += CString(" AND ");	OperandType[0]='E';OperandSize[0]='w';	OperandType[1]='G';OperandSize[1]='w';	break;}
		case 0x22:{	Instruction += CString(" AND ");	OperandType[0]='G';OperandSize[0]='b';	OperandType[1]='E';OperandSize[1]='b';	break;}
		case 0x23:{	Instruction += CString(" AND ");	OperandType[0]='G';OperandSize[0]='w';	OperandType[1]='E';OperandSize[1]='w';	break;}
		case 0x24:{	Instruction += CString(" AND AL ");	OperandType[0]='I';OperandSize[0]='b';											break;}
		case 0x25:{	Instruction += CString(" AND EAX ");OperandType[0]='I';OperandSize[0]='w';											break;}
		case 0x26:{	Instruction += CString(" SEG ES ");																					break;}
		case 0x27:{	Instruction += CString(" DAA ES ");																					break;}
		case 0x28:{	Instruction += CString(" SUB ");	OperandType[0]='E';OperandSize[0]='b';	OperandType[1]='G';OperandSize[1]='b';	break;}
		case 0x29:{	Instruction += CString(" SUB ");	OperandType[0]='E';OperandSize[0]='w';	OperandType[1]='G';OperandSize[1]='w';	break;}
		case 0x2A:{	Instruction += CString(" SUB ");	OperandType[0]='G';OperandSize[0]='b';	OperandType[1]='E';OperandSize[1]='b';	break;}
		case 0x2B:{	Instruction += CString(" SUB ");	OperandType[0]='G';OperandSize[0]='w';	OperandType[1]='E';OperandSize[1]='w';	break;}
		case 0x2C:{	Instruction += CString(" SUB AL ");	OperandType[0]='I';OperandSize[0]='b';											break;}
		case 0x2D:{	Instruction += CString(" SUB EAX ");OperandType[0]='I';OperandSize[0]='w';											break;}
		case 0x2E:{	Instruction += CString(" SEG CS ");																					break;}
		case 0x2F:{	Instruction += CString(" DAS ");																					break;}
		case 0x30:{	Instruction += CString(" XOR ");	OperandType[0]='E';OperandSize[0]='b';	OperandType[1]='G';OperandSize[1]='b';	break;}
		case 0x31:{	Instruction += CString(" XOR ");	OperandType[0]='E';OperandSize[0]='w';	OperandType[1]='G';OperandSize[1]='w';	break;}
		case 0x32:{	Instruction += CString(" XOR ");	OperandType[0]='G';OperandSize[0]='b';	OperandType[1]='E';OperandSize[1]='b';	break;}
		case 0x33:{	Instruction += CString(" XOR ");	OperandType[0]='G';OperandSize[0]='w';	OperandType[1]='E';OperandSize[1]='w';	break;}
		case 0x34:{	Instruction += CString(" XOR AL ");	OperandType[0]='I';OperandSize[0]='b';											break;}
		case 0x35:{	Instruction += CString(" XOR EAX ");OperandType[0]='I';OperandSize[0]='w';											break;}
		case 0x36:{	Instruction += CString(" SEG SS ");																					break;}
		case 0x37:{	Instruction += CString(" AAA ");																					break;}
		case 0x38:{	Instruction += CString(" CMP ");	OperandType[0]='E';OperandSize[0]='b';	OperandType[1]='G';OperandSize[1]='b';	break;}
		case 0x39:{	Instruction += CString(" CMP ");	OperandType[0]='E';OperandSize[0]='w';	OperandType[1]='G';OperandSize[1]='w';	break;}
		case 0x3A:{	Instruction += CString(" CMP ");	OperandType[0]='G';OperandSize[0]='b';	OperandType[1]='E';OperandSize[1]='b';	break;}
		case 0x3B:{	Instruction += CString(" CMP ");	OperandType[0]='G';OperandSize[0]='w';	OperandType[1]='E';OperandSize[1]='w';	break;}
		case 0x3C:{	Instruction += CString(" CMP AL");	OperandType[0]='I';OperandSize[0]='b';											break;}
		case 0x3D:{	Instruction += CString(" CMP EAX");	OperandType[0]='I';OperandSize[0]='w';											break;}
		case 0x3E:{	Instruction += CString(" SEG DS");												break;}
		case 0x3F:{	Instruction += CString(" AAS ");												break;}
		case 0x40:{	Instruction += CString(" INC EAX ");											break;}
		case 0x41:{	Instruction += CString(" INC ECX ");											break;}
		case 0x42:{	Instruction += CString(" INC EDX ");											break;}
		case 0x43:{	Instruction += CString(" INC EBX ");											break;}
		case 0x44:{	Instruction += CString(" INC ESP ");											break;}
		case 0x45:{	Instruction += CString(" INC EBP ");											break;}
		case 0x46:{	Instruction += CString(" INC ESI ");											break;}
		case 0x47:{	Instruction += CString(" INC EDI ");											break;}
		case 0x48:{	Instruction += CString(" DEC EAX ");											break;}
		case 0x49:{	Instruction += CString(" DEC ECX ");											break;}
		case 0x4A:{	Instruction += CString(" DEC EDX ");											break;}
		case 0x4B:{	Instruction += CString(" DEC EBX ");											break;}
		case 0x4C:{	Instruction += CString(" DEC ESP ");											break;}
		case 0x4D:{	Instruction += CString(" DEC EBP ");											break;}
		case 0x4E:{	Instruction += CString(" DEC ESI ");											break;}
		case 0x4F:{	Instruction += CString(" DEC EDI ");											break;}
		case 0x50:{	Instruction += CString(" PUSH EAX ");											break;}
		case 0x51:{	Instruction += CString(" PUSH ECX ");											break;}
		case 0x52:{	Instruction += CString(" PUSH EDX ");											break;}
		case 0x53:{	Instruction += CString(" PUSH EBX ");											break;}
		case 0x54:{	Instruction += CString(" PUSH ESP ");											break;}
		case 0x55:{	Instruction += CString(" PUSH EBP ");											break;}
		case 0x56:{	Instruction += CString(" PUSH ESI ");											break;}
		case 0x57:{	Instruction += CString(" PUSH EDI ");											break;}
		case 0x58:{	Instruction += CString(" POP EAX ");											break;}
		case 0x59:{	Instruction += CString(" POP ECX ");											break;}
		case 0x5A:{	Instruction += CString(" POP EDX ");											break;}
		case 0x5B:{	Instruction += CString(" POP EBX ");											break;}
		case 0x5C:{	Instruction += CString(" POP ESP ");											break;}
		case 0x5D:{	Instruction += CString(" POP EBP ");											break;}
		case 0x5E:{	Instruction += CString(" POP ESI ");											break;}
		case 0x5F:{	Instruction += CString(" POP EDI ");											break;}
		case 0x60:{	Instruction += CString(" PUSHA/PUSHAD ");										break;}
		case 0x61:{	Instruction += CString(" POPA/POPAD ");											break;}
		case 0x62:{	Instruction += CString(" BOUND ");	OperandType[0]='G';OperandSize[0]='w';	Operands[1]="Ma";		break;}
		case 0x63:{	Instruction += CString(" ARPL ");	OperandType[0]='E';OperandSize[0]='v';	OperandType[1]='G';OperandSize[1]='v';		break;}
		case 0x64:{	Instruction += CString(" SEG FS ");												break;}
		case 0x65:{	Instruction += CString(" SEG GS ");												break;}
		case 0x66:{	Instruction += CString(" SWITCH OPERAND-SIZE ");								break;}
		case 0x67:{	Instruction += CString(" SWITCH ADDRESS-SIZE ");								break;}
		case 0x68:{	Instruction += CString(" PUSH ");	OperandType[0]='I';OperandSize[0]='w';	SpecialBits[2]=SpecialBits[0];		break;}
		case 0x69:{	Instruction += CString(" IMUL ");	OperandType[0]='G';OperandSize[0]='w';	Operands[1]="Ev ";				Operands[2]="Iv";	SpecialBits[2]=SpecialBits[0];	break;}
		case 0x6A:{	Instruction += CString(" PUSH ");	OperandType[0]='I';OperandSize[0]='b';	SpecialBits[2]=SpecialBits[0];		break;}
		case 0x6B:{	Instruction += CString(" IMUL ");	OperandType[0]='G';OperandSize[0]='w';	Operands[1]="Ev ";				Operands[2]="Ib";	SpecialBits[2]=SpecialBits[0];	break;}
		case 0x6C:{	Instruction += CString(" INSB ");	OperandType[0]='Y';OperandSize[0]='b';	Operands[1]="DX";		break;}
		case 0x6D:{	Instruction += CString(" INSW/D ");	OperandType[0]='Y';OperandSize[0]='w';	Operands[1]="DX";		break;}
		case 0x6E:{	Instruction += CString(" OUTSB DX ");OperandType[0]='X';OperandSize[0]='b';							break;}
		case 0x6F:{	Instruction += CString(" OUTSW DX ");OperandType[0]='X';OperandSize[0]='w';							break;}
		case 0x70:{	Instruction += CString(" JO ");													break;}
		case 0x71:{	Instruction += CString(" JNO ");												break;}
		case 0x72:{	Instruction += CString(" JC ");													break;}
		case 0x73:{	Instruction += CString(" JNC ");												break;}
		case 0x74:{	Instruction += CString(" JZ ");													break;}
		case 0x75:{	Instruction += CString(" JNZ ");												break;}
		case 0x76:{	Instruction += CString(" JBE ");												break;}
		case 0x77:{	Instruction += CString(" JA ");													break;}
		case 0x78:{	Instruction += CString(" JS ");													break;}
		case 0x79:{	Instruction += CString(" JNS ");												break;}
		case 0x7A:{	Instruction += CString(" JP ");													break;}
		case 0x7B:{	Instruction += CString(" JNP ");												break;}
		case 0x7C:{	Instruction += CString(" JL ");													break;}
		case 0x7D:{	Instruction += CString(" JGE ");												break;}
		case 0x7E:{	Instruction += CString(" JLE ");												break;}
		case 0x7F:{	Instruction += CString(" JG ");													break;}
		case 0x80:
		{
			OperandType[0]='E';OperandSize[0]='b';OperandType[1]='I';OperandSize[1]='b';
			SpecialBits[2]=SpecialBits[0];
			ParseModRM();	
			ProcessOpcodeGroups(1);
			break;
		}
		case 0x81:	
		{
			OperandType[0]='E';OperandSize[0]='w';OperandType[1]='I';OperandSize[1]='w';
			SpecialBits[2]=SpecialBits[0];
			ParseModRM();	
			ProcessOpcodeGroups(1);
			break;
		}
		case 0x82:	
		{
			OperandType[0]='E';OperandSize[0]='b';OperandType[1]='I';OperandSize[1]='b';
			SpecialBits[2]=SpecialBits[0];
			ParseModRM();	
			ProcessOpcodeGroups(1);
			break;
		}
		case 0x83:	
		{
			OperandType[0]='E';OperandSize[0]='w';OperandType[1]='I';OperandSize[1]='b';
			SpecialBits[2]=SpecialBits[0];
			ParseModRM();	
			ProcessOpcodeGroups(1);
			break;
		}
		case 0x84:{	Instruction += CString(" TEST ");	OperandType[0]='G';OperandSize[0]='b';	OperandType[1]='E';OperandSize[1]='b';	break;}
		case 0x85:{	Instruction += CString(" TEST ");	OperandType[0]='G';OperandSize[0]='w';	OperandType[1]='E';OperandSize[1]='w';	break;}
		case 0x86:{	Instruction += CString(" XCHG ");	OperandType[0]='G';OperandSize[0]='b';	OperandType[1]='E';OperandSize[1]='b';	break;}
		case 0x87:{	Instruction += CString(" XCHG ");	OperandType[0]='G';OperandSize[0]='w';	OperandType[1]='E';OperandSize[1]='w';	break;}
		case 0x88:{	Instruction += CString(" MOV ");	OperandType[0]='E';OperandSize[0]='b';	OperandType[1]='G';OperandSize[1]='b';	break;}
		case 0x89:{	Instruction += CString(" MOV ");	OperandType[0]='E';OperandSize[0]='w';	OperandType[1]='G';OperandSize[1]='w';	break;}
		case 0x8A:{	Instruction += CString(" MOV ");	OperandType[0]='G';OperandSize[0]='b';	OperandType[1]='E';OperandSize[1]='b';	break;}
		case 0x8B:{	Instruction += CString(" MOV ");	OperandType[0]='G';OperandSize[0]='w';	OperandType[1]='E';OperandSize[1]='w';	break;}
		case 0x8C:{	Instruction += CString(" MOV ");	OperandType[0]='E';OperandSize[0]='v';	OperandType[1]='S';OperandSize[1]='v';	break;}
		case 0x8D:{	Instruction += CString(" LEA ");	OperandType[0]='G';OperandSize[0]='w';	OperandType[1]='M';						break;}
		case 0x8E:{	Instruction += CString(" MOV ");	OperandType[0]='S';OperandSize[0]='v';	OperandType[1]='E';OperandSize[1]='v';	break;}
		case 0x8F:
		{
			ParseModRM();
			if (ModRMSIB[1]=='E')
			{
				Instruction += CString(" POP ");OperandType[0]='E';OperandSize[0]='w';
			}
			break;
		}
		case 0x90:{	Instruction += CString(" NOP ");																break;}
		case 0x91:{	Instruction += CString(" XCHG ECX ");															break;}
		case 0x92:{	Instruction += CString(" XCHG EDX ");															break;}
		case 0x93:{	Instruction += CString(" XCHG EBX ");															break;}
		case 0x94:{	Instruction += CString(" XCHG ESP ");															break;}
		case 0x95:{	Instruction += CString(" XCHG EBP ");															break;}
		case 0x96:{	Instruction += CString(" XCHG ESI ");															break;}
		case 0x97:{	Instruction += CString(" XCHG EDI ");															break;}
		case 0x98:{	Instruction += CString(" CBW ");																break;}
		case 0x99:{	Instruction += CString(" CWD/CDQ ");															break;}
		case 0x9A:{	Instruction += CString(" CALL ");	OperandType[0]='A';OperandSize[0]='w';						break;}
		case 0x9B:{	Instruction += CString(" WAIT ");																break;}
		case 0x9C:{	Instruction += CString(" PUSHF ");	OperandType[0]='F';OperandSize[0]='w';						break;}
		case 0x9D:{	Instruction += CString(" POPF ");	OperandType[0]='F';OperandSize[0]='w';						break;}
		case 0x9E:{	Instruction += CString(" SAHF ");																break;}
		case 0x9F:{	Instruction += CString(" LAHF ");																break;}
		case 0xA0:{	Instruction += CString(" MOV AL ");	OperandType[0]='O';OperandSize[0]='b';						break;}
		case 0xA1:{	Instruction += CString(" MOV EAX ");OperandType[0]='O';OperandSize[0]='w';						break;}
		case 0xA2:{	Instruction += CString(" MOV ");	OperandType[0]='O';OperandSize[0]='b';	Operands[1]="AL";	break;}
		case 0xA3:{	Instruction += CString(" MOV ");	OperandType[0]='O';OperandSize[0]='w';	Operands[1]="eAX";	break;}
		case 0xA4:{	Instruction += CString(" MOVSB ");	OperandType[0]='Y';OperandSize[0]='b';	OperandType[1]='X';OperandSize[1]='b';	break;}
		case 0xA5:{	Instruction += CString(" MOVSW ");	OperandType[0]='Y';OperandSize[0]='w';	Operands[1]="Xv";	break;}
		case 0xA6:{	Instruction += CString(" CMPSB ");	OperandType[0]='X';OperandSize[0]='b';	OperandType[1]='Y';OperandSize[1]='b';	break;}
		case 0xA7:{	Instruction += CString(" CMPSW ");	OperandType[0]='X';OperandSize[0]='w';	Operands[1]="Yv";	break;}
		case 0xA8:{	Instruction += CString(" TEST AL ");OperandType[0]='I';OperandSize[0]='b';						break;}
		case 0xA9:{	Instruction += CString(" TEST EAX ");OperandType[0]='I';OperandSize[0]='w';						break;}
		case 0xAA:{	Instruction += CString(" STOSB ");	OperandType[0]='Y';OperandSize[0]='b';	Operands[1]="AL";	break;}
		case 0xAB:{	Instruction += CString(" STOSW ");	OperandType[0]='Y';OperandSize[0]='w';	Operands[1]="eAX";	break;}
		case 0xAC:{	Instruction += CString(" LODSB AL ");OperandType[0]='X';OperandSize[0]='b';						break;}
		case 0xAD:{	Instruction += CString(" LODSW EAX ");OperandType[0]='X';OperandSize[0]='w';					break;}
		case 0xAE:{	Instruction += CString(" SCASB AL ");OperandType[0]='Y';OperandSize[0]='b';						break;}
		case 0xAF:{	Instruction += CString(" SCASW EAX ");OperandType[0]='Y';OperandSize[0]='w';					break;}
		case 0xB0:{	Instruction += CString(" MOV AL ");	OperandType[0]='I';OperandSize[0]='b';						break;}
		case 0xB1:{	Instruction += CString(" MOV CL ");	OperandType[0]='I';OperandSize[0]='b';						break;}
		case 0xB2:{	Instruction += CString(" MOV DL ");	OperandType[0]='I';OperandSize[0]='b';						break;}
		case 0xB3:{	Instruction += CString(" MOV BL ");	OperandType[0]='I';OperandSize[0]='b';						break;}
		case 0xB4:{	Instruction += CString(" MOV AH ");	OperandType[0]='I';OperandSize[0]='b';						break;}
		case 0xB5:{	Instruction += CString(" MOV CH ");	OperandType[0]='I';OperandSize[0]='b';						break;}
		case 0xB6:{	Instruction += CString(" MOV DH ");	OperandType[0]='I';OperandSize[0]='b';						break;}
		case 0xB7:{	Instruction += CString(" MOV BH ");	OperandType[0]='I';OperandSize[0]='b';						break;}
		case 0xB8:{	Instruction += CString(" MOV EAX ");OperandType[0]='I';OperandSize[0]='v';						break;}
		case 0xB9:{	Instruction += CString(" MOV ECX ");OperandType[0]='I';OperandSize[0]='v';						break;}
		case 0xBA:{	Instruction += CString(" MOV EDX ");OperandType[0]='I';OperandSize[0]='v';						break;}
		case 0xBB:{	Instruction += CString(" MOV EBX ");OperandType[0]='I';OperandSize[0]='v';						break;}
		case 0xBC:{	Instruction += CString(" MOV ESP ");OperandType[0]='I';OperandSize[0]='v';						break;}
		case 0xBD:{	Instruction += CString(" MOV EBP ");OperandType[0]='I';OperandSize[0]='v';						break;}
		case 0xBE:{	Instruction += CString(" MOV ESI ");OperandType[0]='I';OperandSize[0]='v';						break;}
		case 0xBF:{	Instruction += CString(" MOV EDI ");OperandType[0]='I';OperandSize[0]='v';						break;}
		case 0xC0:{						OperandType[0]='E';OperandSize[0]='b';	OperandType[1]='I';OperandSize[1]='b';	ParseModRM();	ProcessOpcodeGroups(2);	break;}
		case 0xC1:{						OperandType[0]='E';OperandSize[0]='w';	Operands[1]="1";	ParseModRM();	ProcessOpcodeGroups(2);	break;}
		case 0xC2:{	Instruction += CString(" RET ");	OperandType[0]='I';OperandSize[0]='v';						break;}
		case 0xC3:{	Instruction += CString(" RET ");																break;}
		case 0xC4:{	Instruction += CString(" LES ");	OperandType[0]='G';OperandSize[0]='w';	Operands[1]="Mp";	break;}
		case 0xC5:{	Instruction += CString(" LDS ");	OperandType[0]='G';OperandSize[0]='w';	Operands[1]="Mp";	break;}
		case 0xC6:
		{
			ParseModRM();
			if (ModRMSIB[1]=='E')
			{
				Instruction += CString(" MOV ");		OperandType[0]='E';OperandSize[0]='b';	OperandType[1]='I';OperandSize[1]='b';
			}
			break;
		}
		case 0xC7:	
		{
			ParseModRM();
			if (ModRMSIB[1]=='E')
			{
				Instruction += CString(" MOV ");		OperandType[0]='E';OperandSize[0]='b';	OperandType[1]='I';OperandSize[1]='b';
			}
			break;
		}
		case 0xC8:{	Instruction += CString(" ENTER ");	OperandType[0]='I';OperandSize[0]='v';	OperandType[1]='I';OperandSize[1]='b';		break;}
		case 0xC9:{	Instruction += CString(" LEAVE ");																	break;}
		case 0xCA:{	Instruction += CString(" RET ");	OperandType[0]='I';OperandSize[0]='v';							break;}
		case 0xCB:{	Instruction += CString(" RET ");																	break;}
		case 0xCC:{	Instruction += CString(" INT 3 ");																	break;}
		case 0xCD:{	Instruction += CString(" INT ");	OperandType[0]='I';OperandSize[0]='b';							break;}
		case 0xCE:{	Instruction += CString(" INTO ");																	break;}
		case 0xCF:{	Instruction += CString(" IRET ");																	break;}
		case 0xD0:{		OperandType[0]='E';OperandSize[0]='b';	Operands[1]="1";	ParseModRM();	ProcessOpcodeGroups(2);	break;}
		case 0xD1:{		OperandType[0]='E';OperandSize[0]='w';	Operands[1]="1";	ParseModRM();	ProcessOpcodeGroups(2);	break;}
		case 0xD2:{		OperandType[0]='E';OperandSize[0]='b';	Operands[1]="CL";	ParseModRM();	ProcessOpcodeGroups(2);	break;}
		case 0xD3:{		OperandType[0]='E';OperandSize[0]='w';	Operands[1]="CL";	ParseModRM();	ProcessOpcodeGroups(2);	break;}
		case 0xD4:{	Instruction += CString(" AAM ");																	break;}
		case 0xD5:{	Instruction += CString(" AAD ");																	break;}
		case 0xD7:{	Instruction += CString(" XLAT ");																	break;}
		case 0xD8:{	Instruction += CString(" ESC ");																	break;}
		case 0xD9:{	Instruction += CString(" ESC ");																	break;}
		case 0xDA:{	Instruction += CString(" ESC ");																	break;}
		case 0xDB:{	Instruction += CString(" ESC ");																	break;}
		case 0xDC:{	Instruction += CString(" ESC ");																	break;}
		case 0xDD:{	Instruction += CString(" ESC ");																	break;}
		case 0xDE:{	Instruction += CString(" ESC ");																	break;}
		case 0xDF:{	Instruction += CString(" ESC ");																	break;}
		case 0xE0:{	Instruction += CString(" LOOPNZ ");	OperandType[0]='J';OperandSize[0]='w';							break;}
		case 0xE1:{	Instruction += CString(" LOOPZ ");	OperandType[0]='J';OperandSize[0]='w';							break;}
		case 0xE2:{	Instruction += CString(" LOOP ");	OperandType[0]='J';OperandSize[0]='w';							break;}
		case 0xE3:{	Instruction += CString(" JCXZ ");	OperandType[0]='J';OperandSize[0]='w';							break;}
		case 0xE4:{	Instruction += CString(" IN AL ");	OperandType[0]='I';OperandSize[0]='b';							break;}
		case 0xE5:{	Instruction += CString(" IN EAX ");	OperandType[0]='I';OperandSize[0]='b';							break;}
		case 0xE6:{	Instruction += CString(" OUT ");	OperandType[0]='I';OperandSize[0]='b';	Operands[1]="AL";		break;}
		case 0xE7:{	Instruction += CString(" OUT ");	OperandType[0]='I';OperandSize[0]='b';	Operands[1]="eAX";		break;}
		case 0xE8:{	Instruction += CString(" CALL ");	OperandType[0]='J';OperandSize[0]='w';							break;}
		case 0xE9:{	Instruction += CString(" JMP ");	OperandType[0]='J';OperandSize[0]='w';							break;}
		case 0xEA:{	Instruction += CString(" JMP ");	OperandType[0]='A';OperandSize[0]='w';							break;}
		case 0xEB:{	Instruction += CString(" JMP ");	OperandType[0]='J';OperandSize[0]='w';							break;}
		case 0xEC:{	Instruction += CString(" IN AL ");	Operands[0]="DX";												break;}
		case 0xED:{	Instruction += CString(" IN EAX ");	Operands[0]="DX";												break;}
		case 0xEE:{	Instruction += CString(" OUT DX ");	Operands[0]="AL";												break;}
		case 0xEF:{	Instruction += CString(" OUT DX ");	Operands[0]="eAX";												break;}
		case 0xF0:{	Instruction += CString(" LOCK ");																	break;}
		case 0xF2:{	Instruction += CString(" REPNZ ");																	break;}
		case 0xF3:{	Instruction += CString(" REPZ ");																	break;}
		case 0xF4:{	Instruction += CString(" HLT ");																	break;}
		case 0xF5:{	Instruction += CString(" CMC ");																	break;}
		case 0xF6:{						OperandType[0]='E';OperandSize[0]='b';	ParseModRM();	ProcessOpcodeGroups(3);	break;}
		case 0xF7:{						OperandType[0]='E';OperandSize[0]='w';	ParseModRM();	ProcessOpcodeGroups(3);	break;}
		case 0xF8:{	Instruction += CString(" CLC ");																	break;}
		case 0xF9:{	Instruction += CString(" STC ");																	break;}
		case 0xFA:{	Instruction += CString(" CLI ");																	break;}
		case 0xFB:{	Instruction += CString(" STI ");																	break;}
		case 0xFC:{	Instruction += CString(" CLD ");																	break;}
		case 0xFD:{	Instruction += CString(" STD ");																	break;}
		case 0xFE:{											ParseModRM();	ProcessOpcodeGroups(4);						break;}
		case 0xFF:{											ParseModRM();	ProcessOpcodeGroups(5);						break;}
		default:{	Instruction += CString(" Undefined ");																break;}
	}
}

////////////////////////////////////////////////////////////////////
//////////////////////Extended One-Byte Opcode Groups////////////
////////////////////////////////////////////////////////////////////
void CInstruction::ProcessOpcodeGroups(int groupNumber)
{
	switch (groupNumber)
	{
	case 1:
	{
		switch (ModRMSIB[1])
		{
		case 0x00:	{			Instruction += CString(" ADD ");										break;	}
		case 0x01:	{			Instruction += CString(" OR ");											break;	}
		case 0x02:	{			Instruction += CString(" ADC ");										break;	}
		case 0x03:	{			Instruction += CString(" SBB ");										break;	}
		case 0x04:	{			Instruction += CString(" AND ");										break;	}
		case 0x05:	{			Instruction += CString(" SUB ");										break;	}
		case 0x06:	{			Instruction += CString(" XOR ");										break;	}
		case 0x07:	{			Instruction += CString(" CMP ");										break;	}
		default:	{			Instruction = CString(" Undefined ");Operands[0]="";Operands[1]="";		break;	}
		}
	break;}
	case 2:
	{
		switch (ModRMSIB[1])
		{
		case 0x00:	{			Instruction += CString(" ROL ");										break;	}
		case 0x01:	{			Instruction += CString(" ROR ");										break;	}
		case 0x02:	{			Instruction += CString(" RCL ");										break;	}
		case 0x03:	{			Instruction += CString(" RCR ");										break;	}
		case 0x04:	{			Instruction += CString(" SHL/SAL ");									break;	}
		case 0x05:	{			Instruction += CString(" SHR ");										break;	}
		case 0x07:	{			Instruction += CString(" SAR ");										break;	}
		default:	{			Instruction = CString(" Undefined ");Operands[0]="";Operands[1]="";		break;	}
		}
	break;}
	case 3:
	{
		switch (ModRMSIB[1])
		{
		case 0x00:	{			Instruction += CString(" TEST ");Operands[0]="Ib/Iv";					break;	}
		case 0x02:	{			Instruction += CString(" NOT ");										break;	}
		case 0x03:	{			Instruction += CString(" NEG ");										break;	}
		case 0x04:	{			Instruction += CString(" MUL ");Operands[0]="AL/eAX";					break;	}
		case 0x05:	{			Instruction += CString(" IMUL ");Operands[0]="AL/eAX";					break;	}
		case 0x06:	{			Instruction += CString(" DIV ");Operands[0]="AL/eAX";					break;	}
		case 0x07:	{			Instruction += CString(" IDIV ");Operands[0]="AL/eAX";					break;	}
		default:	{			Instruction = CString(" Undefined ");Operands[0]="";Operands[1]="";		break;	}
		}
	break;}
	case 4:
	{
		switch (ModRMSIB[1])
		{
		case 0x00:	{			Instruction += CString(" INC ");Operands[0]="Eb";						break;	}
		case 0x01:	{			Instruction += CString(" DEC ");Operands[0]="Eb";						break;	}
		default:	{			Instruction = CString(" Undefined ");Operands[0]="";Operands[1]="";		break;	}
		}
	break;}
	case 5:
	{
		switch (ModRMSIB[1])
		{
		case 0x00:	{			Instruction += CString(" INC ");Operands[0]="Ev";						break;	}
		case 0x01:	{			Instruction += CString(" DEC ");Operands[0]="Ev";						break;	}
		case 0x02:	{			Instruction += CString(" CALL ");Operands[0]="Ev";						break;	}
		case 0x03:	{			Instruction += CString(" CALL ");Operands[0]="Mp";						break;	}
		case 0x04:	{			Instruction += CString(" JMP ");Operands[0]="Ev";						break;	}
		case 0x05:	{			Instruction += CString(" JMP ");Operands[0]="Mp";						break;	}
		case 0x06:	{			Instruction += CString(" PUSH ");Operands[0]="Ev";						break;	}
		case 0x07:	{			Instruction += CString(" Undefined ");Operands[0]="";Operands[1]="";	break;	}
		default:	{			Instruction = CString(" Undefined ");Operands[0]="";Operands[1]="";		break;	}
		}
	break;}
	case 6:
	{
		switch (ModRMSIB[1])
		{
		case 0x00:	{			Instruction += CString(" SLDT ");										break;	}
		case 0x01:	{			Instruction += CString(" STR ");										break;	}
		case 0x02:	{			Instruction += CString(" LLDT ");										break;	}
		case 0x03:	{			Instruction += CString(" LTR ");										break;	}
		case 0x04:	{			Instruction += CString(" VERR ");										break;	}
		case 0x05:	{			Instruction += CString(" VERW ");										break;	}
		case 0x06:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x07:	{			Instruction += CString(" Undefined ");									break;	}
		default:	{			Instruction = CString(" Undefined ");Operands[0]="";Operands[1]="";		break;	}
		}
	break;}
	case 7:
	{
		switch (ModRMSIB[1])
		{
		case 0x00:	{			Instruction += CString(" SGDT ");										break;	}
		case 0x01:	{			Instruction += CString(" SIDT ");										break;	}
		case 0x02:	{			Instruction += CString(" LGDT ");										break;	}
		case 0x03:	{			Instruction += CString(" LIDT ");										break;	}
		case 0x04:	{			Instruction += CString(" SMSW ");										break;	}
		case 0x05:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x06:	{			Instruction += CString(" LMSW ");										break;	}
		case 0x07:	{			Instruction += CString(" INVLPG ");										break;	}
		default:	{			Instruction = CString(" Undefined ");Operands[0]="";Operands[1]="";		break;	}
		}
	break;}
	case 8:
	{
		switch (ModRMSIB[1])
		{
		case 0x00:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x01:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x02:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x03:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x04:	{			Instruction += CString(" BT ");											break;	}
		case 0x05:	{			Instruction += CString(" BTS ");										break;	}
		case 0x06:	{			Instruction += CString(" BTR ");										break;	}
		case 0x07:	{			Instruction += CString(" BTC ");										break;	}
		default:	{			Instruction = CString(" Undefined ");Operands[0]="";Operands[1]="";		break;	}
		}
	break;}
	case 9:
	{
		switch (ModRMSIB[1])
		{
		case 0x00:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x01:	{			Instruction += CString(" CMPXCH ");										break;	}
		case 0x02:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x03:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x04:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x05:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x06:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x07:	{			Instruction += CString(" Undefined ");									break;	}
		default:	{			Instruction = CString(" Undefined ");Operands[0]="";Operands[1]="";		break;	}
		}
	break;}
	case 10:
	{
		switch (ModRMSIB[1])
		{
		case 0x00:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x01:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x02:	{			Instruction += CString(" PSRLD/PSRLW/PSRLQ ");							break;	}
		case 0x03:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x04:	{			Instruction += CString(" PSRAD/PSRAW ");								break;	}
		case 0x05:	{			Instruction += CString(" Undefined ");									break;	}
		case 0x06:	{			Instruction += CString(" PSLLD/PSLLW/PSLLQ ");							break;	}
		case 0x07:	{			Instruction += CString(" Undefined ");									break;	}
		default:	{			Instruction = CString(" Undefined ");Operands[0]="";Operands[1]="";		break;	}
		}
	break;}
	}
}



void CInstruction::DetermineTwoByteOpcodes()
{
	switch (Opcode[1])
	{
		case 0x00:{		ParseModRM();	ProcessOpcodeGroups(6);	break;}
		case 0x02:{		Instruction += CString(" LAR ");		break;}
		case 0x03:{		Instruction += CString(" LSL ");		break;}
		case 0x06:{		Instruction += CString(" CLTS ");		break;}
		case 0x08:{		Instruction += CString(" INVD ");		break;}
		case 0x09:{		Instruction += CString(" WBINVD ");		break;}
		case 0x0B:{		Instruction += CString(" UD2 ");		break;}	// INTENDED FOR DELIBERATE INVALID OPCODE EXCEPTION (#UD)
		case 0x20:{		Instruction += CString(" MOV ");		break;}
		case 0x21:{		Instruction += CString(" MOV ");		break;}
		case 0x22:{		Instruction += CString(" MOV ");		break;}
		case 0x23:{		Instruction += CString(" MOV ");		break;}
		case 0x30:{		Instruction += CString(" WRMSR ");		break;}
		case 0x31:{		Instruction += CString(" RDTSC ");		break;}
		case 0x32:{		Instruction += CString(" RDMSR ");		break;}
		case 0x33:{		Instruction += CString(" RDPMC ");		break;}
		case 0x40:{		Instruction += CString(" CMOVO ");		break;}
		case 0x41:{		Instruction += CString(" CMOVNO ");		break;}
		case 0x42:{		Instruction += CString(" CMOVC ");		break;}
		case 0x43:{		Instruction += CString(" CMOVNC ");		break;}
		case 0x44:{		Instruction += CString(" CMOVZ ");		break;}
		case 0x45:{		Instruction += CString(" CMOVNZ ");		break;}
		case 0x46:{		Instruction += CString(" CMOVNA ");		break;}
		case 0x47:{		Instruction += CString(" CMOVA ");		break;}
		case 0x48:{		Instruction += CString(" CMOVS ");		break;}
		case 0x49:{		Instruction += CString(" CMOVNS ");		break;}
		case 0x4A:{		Instruction += CString(" CMOVP ");		break;}
		case 0x4B:{		Instruction += CString(" CMOVNP ");		break;}
		case 0x4C:{		Instruction += CString(" CMOVNGE ");	break;}
		case 0x4D:{		Instruction += CString(" CMOVNL ");		break;}
		case 0x4E:{		Instruction += CString(" CMOVNG ");		break;}
		case 0x4F:{		Instruction += CString(" CMOVNLE ");	break;}
		case 0x60:{		Instruction += CString(" PUNPCKLBW ");	break;}
		case 0x61:{		Instruction += CString(" PUNPCKLWD ");	break;}
		case 0x62:{		Instruction += CString(" PUNOCKLDQ ");	break;}
		case 0x63:{		Instruction += CString(" PACKUSDW ");	break;}
		case 0x64:{		Instruction += CString(" PCMPGTB ");	break;}
		case 0x65:{		Instruction += CString(" PCMPGTW ");	break;}
		case 0x66:{		Instruction += CString(" PCMPGTD ");	break;}
		case 0x67:{		Instruction += CString(" PACKSSWB ");	break;}
		case 0x68:{		Instruction += CString(" PUNPCKHBW ");	break;}
		case 0x69:{		Instruction += CString(" PUNPCKHWD ");	break;}
		case 0x6A:{		Instruction += CString(" PUNPCKHDQ ");	break;}
		case 0x6B:{		Instruction += CString(" PACKSSDW ");	break;}
		case 0x6E:{		Instruction += CString(" MOVD ");		break;}
		case 0x6F:{		Instruction += CString(" MOVQ ");		break;}
		case 0x71:{		ParseModRM();	ProcessOpcodeGroups(10);break;}
		case 0x72:{		ParseModRM();	ProcessOpcodeGroups(10);break;}
		case 0x73:{		ParseModRM();	ProcessOpcodeGroups(10);break;}
		case 0x74:{		Instruction += CString(" PCMPEQB ");	break;}
		case 0x75:{		Instruction += CString(" PCMPEQW ");	break;}
		case 0x76:{		Instruction += CString(" PCMPEQD ");	break;}
		case 0x77:{		Instruction += CString(" EMMS ");		break;}
		case 0x7E:{		Instruction += CString(" MOVD ");		break;}
		case 0x7F:{		Instruction += CString(" MOVQ ");		break;}
		case 0x80:{		Instruction += CString(" JO ");			break;}
		case 0x81:{		Instruction += CString(" JNO ");		break;}
		case 0x82:{		Instruction += CString(" JB ");			break;}
		case 0x83:{		Instruction += CString(" JNB ");		break;}
		case 0x84:{		Instruction += CString(" JZ ");			break;}
		case 0x85:{		Instruction += CString(" JNZ ");		break;}
		case 0x86:{		Instruction += CString(" JBE ");		break;}
		case 0x87:{		Instruction += CString(" JNBE ");		break;}
		case 0x88:{		Instruction += CString(" JS ");			break;}
		case 0x89:{		Instruction += CString(" JNS ");		break;}
		case 0x8A:{		Instruction += CString(" JP ");			break;}
		case 0x8B:{		Instruction += CString(" JNP ");		break;}
		case 0x8C:{		Instruction += CString(" JL ");			break;}
		case 0x8D:{		Instruction += CString(" JNL ");		break;}
		case 0x8E:{		Instruction += CString(" JLE ");		break;}
		case 0x8F:{		Instruction += CString(" JNLE ");		break;}
		case 0x90:{		Instruction += CString(" SETO ");		break;}
		case 0x91:{		Instruction += CString(" SETNO ");		break;}
		case 0x92:{		Instruction += CString(" SETB ");		break;}
		case 0x93:{		Instruction += CString(" SETNB ");		break;}
		case 0x94:{		Instruction += CString(" SETZ ");		break;}
		case 0x95:{		Instruction += CString(" SETNZ ");		break;}
		case 0x96:{		Instruction += CString(" SETBE ");		break;}
		case 0x97:{		Instruction += CString(" SETNBE ");		break;}
		case 0x98:{		Instruction += CString(" SETS ");		break;}
		case 0x99:{		Instruction += CString(" SETNS ");		break;}
		case 0x9A:{		Instruction += CString(" SETP ");		break;}
		case 0x9B:{		Instruction += CString(" SETNP ");		break;}
		case 0x9C:{		Instruction += CString(" SETL ");		break;}
		case 0x9D:{		Instruction += CString(" SETNL ");		break;}
		case 0x9E:{		Instruction += CString(" SETLE ");		break;}
		case 0x9F:{		Instruction += CString(" SETNLE ");		break;}
		case 0xA0:{		Instruction += CString(" PUSH FS ");	break;}
		case 0xA1:{		Instruction += CString(" POP FS ");		break;}
		case 0xA2:{		Instruction += CString(" CPUID ");		break;}
		case 0xA3:{		Instruction += CString(" BT ");			break;}
		case 0xA4:{		Instruction += CString(" SHLD ");		break;}
		case 0xA5:{		Instruction += CString(" SHLD ");		break;}
		case 0xA8:{		Instruction += CString(" PUSH GS ");	break;}
		case 0xA9:{		Instruction += CString(" POP GS ");		break;}
		case 0xAA:{		Instruction += CString(" RSM ");		break;}
		case 0xAB:{		Instruction += CString(" BTS ");		break;}
		case 0xAC:{		Instruction += CString(" SHRD ");		break;}
		case 0xAD:{		Instruction += CString(" SHRD ");		break;}
		case 0xAF:{		Instruction += CString(" IMUL ");		break;}
		case 0xB0:{		Instruction += CString(" CMPXCHG ");	break;}
		case 0xB1:{		Instruction += CString(" CMPXCHG ");	break;}
		case 0xB2:{		Instruction += CString(" LSS ");		break;}
		case 0xB3:{		Instruction += CString(" BTR ");		break;}
		case 0xB4:{		Instruction += CString(" LFS ");		break;}
		case 0xB5:{		Instruction += CString(" LGS ");		break;}
		case 0xB6:{		Instruction += CString(" MOVZX ");		break;}
		case 0xB7:{		Instruction += CString(" MOVZX ");		break;}
		case 0xBA:{		ParseModRM();	ProcessOpcodeGroups(8);	break;}
		case 0xBB:{		Instruction += CString(" BTC ");		break;}
		case 0xBC:{		Instruction += CString(" BSF ");		break;}
		case 0xBD:{		Instruction += CString(" BSR ");		break;}
		case 0xBE:{		Instruction += CString(" MOVSX ");		break;}
		case 0xBF:{		Instruction += CString(" MOVSX ");		break;}
		case 0xC0:{		Instruction += CString(" XADD ");		break;}
		case 0xC1:{		Instruction += CString(" XADD ");		break;}
		case 0xC7:{		ParseModRM();	ProcessOpcodeGroups(9);	break;}
		case 0xC8:{		Instruction += CString(" BSWAP EAX ");	break;}
		case 0xC9:{		Instruction += CString(" BSWAP ECX ");	break;}
		case 0xCA:{		Instruction += CString(" BSWAP EDX ");	break;}
		case 0xCB:{		Instruction += CString(" BSWAP EBX ");	break;}
		case 0xCC:{		Instruction += CString(" BSWAP ESP ");	break;}
		case 0xCD:{		Instruction += CString(" BSWAP EBP ");	break;}
		case 0xCE:{		Instruction += CString(" BSWAP ESI ");	break;}
		case 0xCF:{		Instruction += CString(" BSWAP EDI ");	break;}
		case 0xD1:{		Instruction += CString(" PSRLW ");		break;}
		case 0xD2:{		Instruction += CString(" PSRLD ");		break;}
		case 0xD3:{		Instruction += CString(" PSRLQ ");		break;}
		case 0xD5:{		Instruction += CString(" PMULLW ");		break;}
		case 0xD8:{		Instruction += CString(" PSUBUSB ");	break;}
		case 0xD9:{		Instruction += CString(" PSUBUSW ");	break;}
		case 0xDB:{		Instruction += CString(" PAND ");		break;}
		case 0xDC:{		Instruction += CString(" PADDUSB ");	break;}
		case 0xDD:{		Instruction += CString(" PADDUSW ");	break;}
		case 0xDF:{		Instruction += CString(" PANDN ");		break;}
		case 0xE1:{		Instruction += CString(" PSRAW ");		break;}
		case 0xE2:{		Instruction += CString(" PSRAD ");		break;}
		case 0xE5:{		Instruction += CString(" PMULHW ");		break;}
		case 0xE8:{		Instruction += CString(" PSUBSB ");		break;}
		case 0xE9:{		Instruction += CString(" PSUBSW ");		break;}
		case 0xEB:{		Instruction += CString(" POR ");		break;}
		case 0xEC:{		Instruction += CString(" PADDSB ");		break;}
		case 0xED:{		Instruction += CString(" PADDSW ");		break;}
		case 0xEF:{		Instruction += CString(" PXOR ");		break;}
		case 0xF1:{		Instruction += CString(" PSLLW ");		break;}
		case 0xF2:{		Instruction += CString(" PSLLD ");		break;}
		case 0xF3:{		Instruction += CString(" PSLLQ ");		break;}
		case 0xF5:{		Instruction += CString(" PMADDWD ");	break;}
		case 0xF8:{		Instruction += CString(" PSUBB ");		break;}
		case 0xF9:{		Instruction += CString(" PSUBW ");		break;}
		case 0xFA:{		Instruction += CString(" PSUBD ");		break;}
		case 0xFC:{		Instruction += CString(" PADDB ");		break;}
		case 0xFD:{		Instruction += CString(" PADDW ");		break;}
		case 0xFE:{		Instruction += CString(" PADDD ");		break;}
	}
}


void CInstruction::ParseModRM(void)
{
	int RegSize=8;
	if (OperandSize[OperandNum] == 'v' || OperandSize[OperandNum] == 'w')	RegSize=CurrentAddressingWordSize;

	if ((InstructionPointer < dataSize) && !isModRM)
	{
		ModRMSIB[0]	=	(data[InstructionPointer]);			// Entire ModRM Byte
		ModRMSIB[1] =	(ModRMSIB[0] & 0xC0) >> 6;			// Mod
		ModRMSIB[2] =	(ModRMSIB[0] & 0x38) >> 3;			// Reg
		ModRMSIB[3]	=	(ModRMSIB[0] & 0x07) >> 0;			// RM
		isModRM		=	true;
		IncrementCounters(1);		
	}
	else if (InstructionPointer >= dataSize)
		EndOfInstructions=true;
	
	if (isModRM && !EndOfInstructions)
	{
		switch (ModRMSIB[2])	// Register Values
		{
			case 0x00:{	if (RegSize==8) Reg="AL";	if (RegSize==16) Reg="AX";	if (RegSize==32) Reg="EAX";		break;		}
			case 0x01:{	if (RegSize==8) Reg="CL";	if (RegSize==16) Reg="CX";	if (RegSize==32) Reg="ECX";		break;		}
			case 0x02:{	if (RegSize==8) Reg="DL";	if (RegSize==16) Reg="DX";	if (RegSize==32) Reg="EDX";		break;		}
			case 0x03:{	if (RegSize==8) Reg="BL";	if (RegSize==16) Reg="BX";	if (RegSize==32) Reg="EBX";		break;		}
			case 0x04:{	if (RegSize==8) Reg="AH";	if (RegSize==16) Reg="SP";	if (RegSize==32) Reg="ESP";		break;		}
			case 0x05:{	if (RegSize==8) Reg="CH";	if (RegSize==16) Reg="BP";	if (RegSize==32) Reg="EBP";		break;		}
			case 0x06:{	if (RegSize==8) Reg="DH";	if (RegSize==16) Reg="SI";	if (RegSize==32) Reg="ESI";		break;		}
			case 0x07:{	if (RegSize==8) Reg="BH";	if (RegSize==16) Reg="DI";	if (RegSize==32) Reg="EDI";		break;		}
		}
		
		if (CurrentAddressingWordSize == 16)
		{
			switch (ModRMSIB[1])	// Register/Memory Values
			{
				case 0x00:	{	switch (ModRMSIB[3])	// RM values
								{
								case 0x00:{	EA="[BX+SI]";											break;		}
								case 0x01:{	EA="[BX+DI]";											break;		}
								case 0x02:{	EA="[BP+SI]";											break;		}
								case 0x03:{	EA="[BP+DI]";											break;		}
								case 0x04:{	EA="[SI]";												break;		}
								case 0x05:{	EA="[DI]";												break;		}
								case 0x06:{	ParseDisplacements(16);	EA=Offsets[0];					break;		}
								case 0x07:{	EA="[BX]";												break;		}
								}
								break;
							}
				case 0x01:	{	switch (ModRMSIB[3])	// RM values (+8-BIT DISPLACEMENT)
								{
								default:{	ParseDisplacements(8);												}
								case 0x00:{	EA=CString("[BX+SI]+") + Offsets[0];					break;		}
								case 0x01:{	EA=CString("[BX+DI]+") + Offsets[0];					break;		}
								case 0x02:{	EA=CString("[BP+SI]+") + Offsets[0];					break;		}
								case 0x03:{	EA=CString("[BP+DI]+") + Offsets[0];					break;		}
								case 0x04:{	EA=CString("[SI]+") + Offsets[0];						break;		}
								case 0x05:{	EA=CString("[DI]+") + Offsets[0];						break;		}
								case 0x06:{	EA=CString("[BP]+") + Offsets[0];						break;		}
								case 0x07:{	EA=CString("[BX]+") + Offsets[0];						break;		}
								}
								break;
							}
				case 0x02:	{	switch (ModRMSIB[3])	// RM values (+16-BIT DISPLACEMENT)
								{
								default:{	ParseDisplacements(16);												}
								case 0x00:{	EA=CString("[BX+SI]+") + Offsets[0];		break;		}
								case 0x01:{	EA=CString("[BX+DI]+") + Offsets[0];		break;		}
								case 0x02:{	EA=CString("[BP+SI]+") + Offsets[0];		break;		}
								case 0x03:{	EA=CString("[BP+DI]+") + Offsets[0];		break;		}
								case 0x04:{	EA=CString("[SI]+") + Offsets[0];			break;		}
								case 0x05:{	EA=CString("[DI]+") + Offsets[0];			break;		}
								case 0x06:{	EA=CString("[BP]+") + Offsets[0];			break;		}
								case 0x07:{	EA=CString("[BX]+") + Offsets[0];			break;		}
								}
								break;
							}
				case 0x03:	{	switch (ModRMSIB[3])	// RM values
								{
								case 0x00:{	EA="[EAX]";		break;		}
								case 0x01:{	EA="[ECX]";		break;		}
								case 0x02:{	EA="[EDX]";		break;		}
								case 0x03:{	EA="[EBX]"; 	break;		}
								case 0x04:{	EA="[ESP]";		break;		}
								case 0x05:{	EA="[EBP]";		break;		}
								case 0x06:{	EA="[ESI]";		break;		}
								case 0x07:{	EA="[EDI]";		break;		}
								}
								break;
							}
			}
		}
		else if (CurrentAddressingWordSize == 32)
		{
			switch (ModRMSIB[1])	// Register/Memory Values
			{
				case 0x00:	{	switch (ModRMSIB[3])	// RM values
								{
								case 0x00:{	EA="[EAX]";													break;		}
								case 0x01:{	EA="[ECX]";													break;		}
								case 0x02:{	EA="[EDX]";													break;		}
								case 0x03:{	EA="[EBX]";													break;		}
								case 0x04:{	EA=ParseSIB(32);											break;		}
								case 0x05:{	ParseDisplacements(32);	EA="[]"; EA.Insert(1, Offsets[0]);	break;		}
								case 0x06:{	EA="[ESI]";													break;		}
								case 0x07:{	EA="[EDI]";													break;		}
								}
								break;
							}
				case 0x01:	{	switch (ModRMSIB[3])	// RM values (+8-BIT DISPLACEMENT)
								{
								default:{	ParseDisplacements(8);												}
								case 0x00:{	EA=Offsets[0]+CString("+[BX+SI]");						break;		}
								case 0x01:{	EA=Offsets[0]+CString("+[BX+DI]");						break;		}
								case 0x02:{	EA=Offsets[0]+CString("+[BP+SI]");						break;		}
								case 0x03:{	EA=Offsets[0]+CString("+[BP+DI]");						break;		}
								case 0x04:{	EA=Offsets[0]+ParseSIB(32);								break;		}
								case 0x05:{	EA=Offsets[0]+CString("+[DI]");							break;		}
								case 0x06:{	EA=Offsets[0]+CString("+[BP]");							break;		}
								case 0x07:{	EA=Offsets[0]+CString("+[BX]");							break;		}
								}
								break;
							}
				case 0x02:	{	switch (ModRMSIB[3])	// RM values (+32-BIT DISPLACEMENT)
								{
								default:{	ParseDisplacements(32);												}
								case 0x00:{	EA=Offsets[0]+CString("+[BX+SI]");				break;		}
								case 0x01:{	EA=Offsets[0]+CString("+[BX+DI]");				break;		}
								case 0x02:{	EA=Offsets[0]+CString("+[BP+SI]");				break;		}
								case 0x03:{	EA=Offsets[0]+CString("+[BP+DI]");				break;		}
								case 0x04:{	EA=ParseSIB(32);								break;		}
								case 0x05:{	EA=Offsets[0]+CString("+[DI]");					break;		}
								case 0x06:{	EA=Offsets[0]+CString("+[BP]");					break;		}
								case 0x07:{	EA=Offsets[0]+CString("+[BX]");					break;		}
								}
								break;
							}
				case 0x03:	{	switch (ModRMSIB[3])	// RM values
								{
								case 0x00:{	EA="[EAX]";		break;		}
								case 0x01:{	EA="[ECX]";		break;		}
								case 0x02:{	EA="[EDX]";		break;		}
								case 0x03:{	EA="[EBX]";		break;		}
								case 0x04:{	EA="[ESP]";		break;		}
								case 0x05:{	EA="[EBP]";		break;		}
								case 0x06:{	EA="[ESI]";		break;		}
								case 0x07:{	EA="[EDI]";		break;		}
								}
								break;
							}
			}
		}
	}
}


void CInstruction::ParseImmediate(int OpSize)
{
	Offsets[1].Empty();			// Initialize displacements
	char *buffer;
	
	switch (OpSize)
	{
	case 'b':
	{
		if (InstructionPointer < dataSize)
		{
			buffer = new char[3];
			_itoa_s(data[InstructionPointer], buffer, 3, 16);
			Offsets[1]=buffer;
			IncrementCounters(1);
		}
		else
			EndOfInstructions=true;
		break;
	}
	case 'w':
	{
		if ((InstructionPointer+3) < dataSize)
		{
			buffer = new char[9];
			_itoa_s((data[InstructionPointer+3]<<24) | (data[InstructionPointer+2]<<16) | (data[InstructionPointer+1]<<8) | (data[InstructionPointer]), buffer, 9, 16);
			Offsets[1]=buffer;
			IncrementCounters(4);
		}
		else
			EndOfInstructions=true;
		break;
	}
	case 'v':
	{
		if ((InstructionPointer+3) < dataSize)
		{
			buffer = new char[9];
			_itoa_s((data[InstructionPointer+3]<<24) | (data[InstructionPointer+2]<<16) | (data[InstructionPointer+1]<<8) | (data[InstructionPointer]), buffer, 9, 16);
			Offsets[1]=buffer;
			IncrementCounters(4);
		}
		else
			EndOfInstructions=true;
		break;
	}
	case 8:
	{
		if (InstructionPointer < dataSize)
		{
			buffer = new char[3];
			_itoa_s(data[InstructionPointer], buffer, 3, 16);
			Offsets[1]=buffer;
			IncrementCounters(1);
		}
		else
			EndOfInstructions=true;
		break;
	}
	case 16:
	{
		if ((InstructionPointer+1) < dataSize)
		{
			buffer = new char[5];
			_itoa_s((data[InstructionPointer+1]<<8) | (data[InstructionPointer]), buffer, 5, 16);
			Offsets[1]=buffer;
			IncrementCounters(1);
		}
		else
			EndOfInstructions=true;
		break;
	}
	case 32:
	{
		if ((InstructionPointer+3) < dataSize)
		{
			buffer = new char[9];
			_itoa_s((data[InstructionPointer+3]<<24) | (data[InstructionPointer+2]<<16) | (data[InstructionPointer+1]<<8) | (data[InstructionPointer]), buffer, 9, 16);
			Offsets[1]=buffer;
			IncrementCounters(4);
		}
		else
			EndOfInstructions=true;
		break;
	}
	default:{	break;};
	}
}


void CInstruction::ParseDisplacements(int OpSize)
{
	Offsets[0].Empty();			// Initialize displacements
	char *buffer;
	
	switch (OpSize)
	{
	case 'b':
	{
		if (InstructionPointer < dataSize)
		{
			buffer = new char[3];
			_itoa_s(data[InstructionPointer], buffer, 3, 16);
			Offsets[0]=buffer;
			IncrementCounters(1);
		}
		else
			EndOfInstructions=true;
		break;
	}
	case 'w':
	{
		if ((InstructionPointer+3) < dataSize)
		{
			buffer = new char[9];
			_itoa_s((data[InstructionPointer+3]<<24) | (data[InstructionPointer+2]<<16) | (data[InstructionPointer+1]<<8) | (data[InstructionPointer]), buffer, 9, 16);
			Offsets[0]=buffer;
			IncrementCounters(4);
		}
		else
			EndOfInstructions=true;
		break;
	}
	case 'v':
	{
		if ((InstructionPointer+3) < dataSize)
		{
			buffer = new char[9];
			_itoa_s((data[InstructionPointer+3]<<24) | (data[InstructionPointer+2]<<16) | (data[InstructionPointer+1]<<8) | (data[InstructionPointer]), buffer, 9, 16);
			Offsets[0]=buffer;
			IncrementCounters(4);
		}
		else
			EndOfInstructions=true;
		break;
	}
	case 8:
	{
		if (InstructionPointer < dataSize)
		{
			buffer = new char[3];
			_itoa_s(data[InstructionPointer], buffer, 3, 16);
			Offsets[0]=buffer;
			IncrementCounters(1);
		}
		else
			EndOfInstructions=true;
		break;
	}
	case 16:
	{
		if ((InstructionPointer+1) < dataSize)
		{
			buffer = new char[5];
			_itoa_s((data[InstructionPointer+1]<<8) | (data[InstructionPointer]), buffer, 5, 16);
			Offsets[0]=buffer;
			IncrementCounters(1);
		}
		else
			EndOfInstructions=true;
		break;
	}
	case 32:
	{
		if ((InstructionPointer+3) < dataSize)
		{
			buffer = new char[9];
			_itoa_s((data[InstructionPointer+3]<<24) | (data[InstructionPointer+2]<<16) | (data[InstructionPointer+1]<<8) | (data[InstructionPointer]), buffer, 9, 16);
			Offsets[0]=buffer;
			IncrementCounters(4);
		}
		else
			EndOfInstructions=true;
		break;
	}
	default:{	break;};
	}
}


CString CInstruction::DetermineOperand()
{
	for (OperandNum = 0; OperandNum < 3; OperandNum++)
	{
		switch (OperandType[OperandNum])
		{
		case 'E':	{	if (Instruction == " Undefined ")Operands[OperandNum].Empty();	if (!isModRM) ParseModRM();	Operands[OperandNum]=EA;	break;	}	//	ModRM specified operand
		case 'G':	{	if (Instruction == " Undefined ")Operands[OperandNum].Empty();	if (!isModRM) ParseModRM();	Operands[OperandNum]=Reg;	break;	}	//	ModRM REG selects Gen. Reg.
		case 'I':	{	if (Instruction == " Undefined ")Operands[OperandNum].Empty();	ParseImmediate(OperandSize[OperandNum]);	Operands[OperandNum]+=CString("[") + Offsets[1]; Operands[OperandNum]+=CString("]");	break;	}	//	Immediate data operand
		case 'O':	{	if (Instruction == " Undefined ")Operands[OperandNum].Empty();	ParseImmediate(OperandSize[OperandNum]);	Operands[OperandNum]+=CString("[") + Offsets[1]; Operands[OperandNum]+=CString("]");	break;	}
		case 'J':	{	/* Relative offset added to address of subsequent instruction*/												break;	}
		case 'X':	{	/* Memory addressed by DS:rSI pair*/																		break;	}
		case 'Y':	{	/* Memory addressed by ES:rSI pair*/																		break;	}
		case 'A':	{	/* 32-bit Seg:Offset pointer to Direct Address (No ModRegRM) encoded in instruction*/						break;	}
		case 'F':	{	/* Not used in 286*/																						break;	}
		case 'S':	{	/* Reg field of ModR/M byte selects word-sized segment register*/											break;	}
		case 'M':	{	/* ModR/M byte refers only to memory location address, two word/dword memory arguments*/					break;	}
		default:	{	Operands[OperandNum].Empty();																				break;	}
		}
	}
	return *Operands;
}


CString CInstruction::ParseSIB(int Size)
{
	CString Index, Base;
	
	if ((InstructionPointer < dataSize) && !isSIB)
	{
		ModRMSIB[4]	=	(data[InstructionPointer]);			// Entire ModRM Byte
		ModRMSIB[5] =	(ModRMSIB[4] & 0xC0) >> 6;			// Mod
		ModRMSIB[6] =	(ModRMSIB[4] & 0x38) >> 3;			// Base
		ModRMSIB[7]	=	(ModRMSIB[4] & 0x07) >> 0;			// RM
		isSIB		=	true;
		IncrementCounters(1);
	}
	else if (InstructionPointer >= dataSize)
		EndOfInstructions=true;

	if (isSIB && !EndOfInstructions)
	{
		switch (ModRMSIB[7])	// Base Values
		{
			case 0x00:{	Base="EAX";		break;		}
			case 0x01:{	Base="ECX";		break;		}
			case 0x02:{	Base="EDX";		break;		}
			case 0x03:{	Base="EBX";		break;		}
			case 0x04:{	Base="ESP";		break;		}
			case 0x05:
			{	
				if (ModRMSIB[1]==0x00)	
				{
					ParseDisplacements(32);
					Base=Offsets[0];
				}
				if (ModRMSIB[1]==0x01)
				{
					ParseDisplacements(8);
					Base=Offsets[0]+CString("[EBP]");
				}
				if (ModRMSIB[1]==0x02)
				{
					ParseDisplacements(32);
					Base=Offsets[0]+CString("[EBP]");
				}
				break;
			}
			case 0x06:{	Base="ESI";		break;		}
			case 0x07:{	Base="EDI";		break;		}
		}
	
		switch (ModRMSIB[5])	// Scale
		{
			case 0x00:	{	switch (ModRMSIB[6])	// Index values
							{
							case 0x00:{	Index="[EAX]";													break;		}
							case 0x01:{	Index="[ECX]";													break;		}
							case 0x02:{	Index="[EDX]";													break;		}
							case 0x03:{	Index="[EBX]";													break;		}
							case 0x04:{																	break;		}
							case 0x05:{	Index="[EBP]";													break;		}
							case 0x06:{	Index="[ESI]";													break;		}
							case 0x07:{	Index="[EDI]";													break;		}
							}
							break;
						}
			case 0x01:	{	switch (ModRMSIB[6])	// Index values
							{
							case 0x00:{	Index="[EAX*2]";													break;		}
							case 0x01:{	Index="[ECX*2]";													break;		}
							case 0x02:{	Index="[EDX*2]";													break;		}
							case 0x03:{	Index="[EBX*2]";													break;		}
							case 0x04:{																		break;		}
							case 0x05:{	Index="[EBP*2]";													break;		}
							case 0x06:{	Index="[ESI*2]";													break;		}
							case 0x07:{	Index="[EDI*2]";													break;		}
							}
							break;
						}
			case 0x02:	{	switch (ModRMSIB[6])	// Index values
							{
							case 0x00:{	Index="[EAX*4]";													break;		}
							case 0x01:{	Index="[ECX*4]";													break;		}
							case 0x02:{	Index="[EDX*4]";													break;		}
							case 0x03:{	Index="[EBX*4]";													break;		}
							case 0x04:{																		break;		}
							case 0x05:{	Index="[EBP*4]";													break;		}
							case 0x06:{	Index="[ESI*4]";													break;		}
							case 0x07:{	Index="[EDI*4]";													break;		}
							}
							break;
						}
			case 0x03:	{	switch (ModRMSIB[6])	// Index values
							{
							case 0x00:{	Index="[EAX*8]";		break;		}
							case 0x01:{	Index="[ECX*8]";		break;		}
							case 0x02:{	Index="[EDX*8]";		break;		}
							case 0x03:{	Index="[EBX*8]"; 		break;		}
							case 0x04:{							break;		}
							case 0x05:{	Index="[EBP*8]";		break;		}
							case 0x06:{	Index="[ESI*8]";		break;		}
							case 0x07:{	Index="[EDI*8]";		break;		}
							}
							break;
						}
		}
	}
	return (Base + Index);
}


void CInstruction::IncrementCounters(int incNum)
{
	InstructionPointer+=incNum;
}


void CInstruction::InitializeVariables(bool FirstTime)
{
	if (FirstTime==true)
	{
		switch (int i=0)
		{
		case 0:{ ModRMSIB[i]=NULL; SpecialBits[i]=NULL; Prefixes[i]=NULL; Opcode[i]=NULL; Operands[i].Empty(); OperandSize[i]=0; OperandType[i]=NULL; Offsets[i].Empty(); Instruction.Empty(); Reg.Empty(); EA.Empty(); OperandNum=0; isModRM=false; isSReg=false; isSIB=false; i++; }
		case 1:{ ModRMSIB[i]=NULL; SpecialBits[i]=NULL; Prefixes[i]=NULL; Opcode[i]=NULL; Operands[i].Empty(); OperandSize[i]=0; OperandType[i]=NULL; Offsets[i].Empty(); i++; }
		case 2:{ ModRMSIB[i]=NULL; SpecialBits[i]=NULL; Prefixes[i]=NULL; Opcode[i]=NULL; Operands[i].Empty(); OperandSize[i]=0; OperandType[i]=NULL; i++; }
		case 3:{ ModRMSIB[i]=NULL; SpecialBits[i]=NULL; Prefixes[i]=NULL; i++; }
		case 4:{ ModRMSIB[i]=NULL; SpecialBits[i]=NULL; i++; }
		case 5:{ ModRMSIB[i]=NULL; SpecialBits[i]=NULL; i++; }
		case 6:{ ModRMSIB[i]=NULL; i++;	}
		case 7:{ ModRMSIB[i]=NULL;	}
		}
	}
	else
	{
		Operands[0].Empty();		// Initialize Op1
		Operands[1].Empty();		// Initialize Op2
		Operands[2].Empty();		// Initialize Op3
		OperandType[0]=NULL;
		OperandType[1]=NULL;
		OperandType[2]=NULL;
		OperandSize[0]=NULL;
		OperandSize[1]=NULL;
		OperandSize[2]=NULL;
	}
}
