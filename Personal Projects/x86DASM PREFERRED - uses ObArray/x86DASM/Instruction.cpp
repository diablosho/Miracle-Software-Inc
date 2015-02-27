#include "StdAfx.h"
#include "Instruction.h"


CInstruction::CInstruction()
{
}


//Create Instruction Constructor for building a COMPLETE Instruction object
CInstruction::CInstruction(CString mnemonic, int Prefixes, int Opcodes, int Displacement, int Immediate, BYTE ModRM, BYTE SIB, DECODING_FLAGS OperandFlags[3])
{
}

//Create Instruction Constructor for building Instruction_Set table
CInstruction::CInstruction(int Opcodes, CString mnemonic, int Op1Flag, int Op2Flag, int Op3Flag)
{
	InitializeVariables();
	this->Op1Type = Op1Flag;
	this->Op2Type = Op2Flag;
	this->Op3Type = Op3Flag;
	short int flags[3] = {	Op1Flag, Op2Flag, Op3Flag	};
	this->mnemonic = mnemonic;
	this->Opcodes = Opcodes;
	//	Populate all flags necessary to decode the instruction later
	char opType = NULL; 
	char opSize = NULL;
	for (int i = 0; i < 3, flags[i] != NULL; i++)
	{
		// Operand Types
		switch (((flags[i] & 0xFF00)>>8))
		{
		case 'A':	this->flags[i].isNoSIB = true;
					this->flags[i].OperandAddressEncodedInInstruction = true;
					break;
		case 'C':	this->flags[i].isModRM = true;
					this->flags[i].RegSelectsControlRegister = true;
					break;
		case 'D':	this->flags[i].isModRM = true;
					this->flags[i].RegSelectsDebugRegister = true;
					break;
		case 'E':	this->flags[i].isModRM = true;
					this->flags[i].isSIB = true;
					this->flags[i].OperandIsGPReg = true;
					this->flags[i].OperandIsMemAddress = true;
					break;
		case 'F':	this->flags[i].isEFLAGSRegister = true;
					break;
		case 'G':	this->flags[i].isModRM = true;
					this->flags[i].RegSelectsGeneralRegister = true;
					break;
		case 'I':	this->flags[i].isImmediateData = true;
					break;
		case 'J':	this->flags[i].InstructionContainsRelativeOffset = true;
					break;
		case 'M':	this->flags[i].ModRMByteRefersOnlyToMemory = true;
					this->flags[i].isModRM = true;
					break;
		case 'O':	this->flags[i].OperandOffsetCodedAsWORDorDWORD = true;
					this->flags[i].isNoSIB = true;
					break;
		case 'P':	this->flags[i].RegSelectsPackedQWORDMMXRegister = true;
					this->flags[i].isModRM = true;
					break;
		case 'Q':	this->flags[i].ModRMSpecifiesMMXorMemoryAddress = true;
					this->flags[i].isModRM = true;
					this->flags[i].isSIB = true;
					break;
		case 'R':	this->flags[i].ModSelectsGeneralRegister = true;
					this->flags[i].isModRM = true;
					break;
		case 'S':	this->flags[i].RegSelectsSegmentRegister = true;
					this->flags[i].isModRM = true;
					break;
		case 'T':	this->flags[i].RegSelectsTestRegister = true;
					this->flags[i].isModRM = true;
					break;
		case 'X':	this->flags[i].MemoryAddressedByDSSIRegPair = true;
					break;
		case 'Y':	this->flags[i].MemoryAddressedByESDIRegPair = true;
					break;
		case NULL:	break;
		default:	break;
		}
		// Operand Sizes
		switch (((BYTE)flags[i] & 0x00FF))
		{
		case 'a':	this->flags[i].isTwoWORDorDWORDmemOperands = true;	break;
		case 'b':	this->flags[i].isALWAYSBYTE = true;					break;
		case 'c':	this->flags[i].isByteOrWord = true;					break;
		case 'd':	this->flags[i].isALWAYSDWORD = true;				break;
		case 'p':	this->flags[i].is32or48bitPointer = true;			break;
		case 'q':	this->flags[i].isALWAYSQWORD = true;				break;
		case 's':	this->flags[i].is6bytePseudoDescriptor = true;		break;
		case 'v':	this->flags[i].isWORDorDWORD = true;				break;
		case 'w':	this->flags[i].isALWAYSWORD = true;					break;
		case NULL:	break;
		default:	break;
		}
	}
}


CInstruction::~CInstruction(void)
{
}


void CInstruction::InitializeVariables(void)
{
	mnemonic.Empty();
	Prefixes=NULL;
	Opcodes=NULL;
	Displacement=NULL;
	Immediate=NULL;
	Op1Type=NULL;
	Op2Type=NULL;
	Op3Type=NULL;
	ModRM=NULL;
	SIB=NULL;

	for (int i = 0; i < 3; i++)
	{
		this->flags[i].isModRM = false;
		this->flags[i].isSIB = false;								// E, Q
		this->flags[i].isNoSIB = false;								// A, O 
		this->flags[i].OperandAddressEncodedInInstruction = false;	// A
		this->flags[i].RegSelectsControlRegister = false;			// C
		this->flags[i].RegSelectsDebugRegister = false;				// D
		this->flags[i].OperandIsGPReg = false;						// E
		this->flags[i].OperandIsMemAddress = false;					// E
		this->flags[i].isEFLAGSRegister = false;					// F
		this->flags[i].RegSelectsGeneralRegister = false;			// G
		this->flags[i].isImmediateData = false;						// I
		this->flags[i].InstructionContainsRelativeOffset = false;	// J
		this->flags[i].ModRMByteRefersOnlyToMemory = false;			// M
		this->flags[i].OperandOffsetCodedAsWORDorDWORD = false;		// O
		this->flags[i].RegSelectsPackedQWORDMMXRegister = false;	// P
		this->flags[i].ModRMSpecifiesMMXorMemoryAddress = false;	// Q
		this->flags[i].ModSelectsGeneralRegister = false;			// R
		this->flags[i].RegSelectsSegmentRegister = false;			// S
		this->flags[i].RegSelectsTestRegister = false;				// T
		this->flags[i].MemoryAddressedByDSSIRegPair = false;		// X
		this->flags[i].MemoryAddressedByESDIRegPair = false;		// Y
		this->flags[i].isTwoWORDorDWORDmemOperands = false;			// a
		this->flags[i].isALWAYSBYTE = false;						// b
		this->flags[i].isByteOrWord = false;						// c
		this->flags[i].isALWAYSDWORD = false;						// d
		this->flags[i].is32or48bitPointer = false;					// p
		this->flags[i].isALWAYSQWORD = false;						// q
		this->flags[i].is6bytePseudoDescriptor = false;				// s
		this->flags[i].isWORDorDWORD = false;						// v
		this->flags[i].isALWAYSWORD = false;						// w
	}
}