#pragma once
#include "afx.h"
#include "Instruction.h"
#include "InstructionDecoder.h"

class CInstruction :	
	public CObject
{
public:
	CString mnemonic;
	int		Prefixes, Opcodes, Displacement, Immediate;
	short int Op1Type, Op2Type, Op3Type;
	BYTE	ModRM, SIB;
	struct	DECODING_FLAGS
	{
		// Operand Addressing Methods
		bool isModRM;							// C, D, E, G, M, P, Q, R, S, T
		bool isSIB;								// E, Q
		bool isNoSIB;							// A, O 
		bool OperandAddressEncodedInInstruction;// A
		bool RegSelectsControlRegister;			// C
		bool RegSelectsDebugRegister;			// D
		bool OperandIsGPReg;					// E
		bool OperandIsMemAddress;				// E
		bool isEFLAGSRegister;					// F
		bool RegSelectsGeneralRegister;			// G
		bool isImmediateData;					// I
		bool InstructionContainsRelativeOffset;	// J
		bool ModRMByteRefersOnlyToMemory;		// M
		bool OperandOffsetCodedAsWORDorDWORD;	// O
		bool RegSelectsPackedQWORDMMXRegister;	// P
		bool ModRMSpecifiesMMXorMemoryAddress;	// Q
		bool ModSelectsGeneralRegister;			// R
		bool RegSelectsSegmentRegister;			// S
		bool RegSelectsTestRegister;			// T
		bool MemoryAddressedByDSSIRegPair;		// X
		bool MemoryAddressedByESDIRegPair;		// Y
		// Operand Sizes
		bool isTwoWORDorDWORDmemOperands;		// a
		bool isALWAYSBYTE;						// b
		bool isByteOrWord;						// c
		bool isALWAYSDWORD;						// d
		bool is32or48bitPointer;				// p
		bool isALWAYSQWORD;						// q
		bool is6bytePseudoDescriptor;			// s
		bool isWORDorDWORD;						// v
		bool isALWAYSWORD;						// w
	}	flags[3];
	CInstruction();
	CInstruction(int Opcodes, CString mnemonic, int Op1Flag, int Op2Flag, int Op3Flag);	// ISA Reference Table Instruction Object
	CInstruction(CString mnemonic, int Prefixes, int Opcodes, int Displacement, int Immediate, BYTE ModRM, BYTE SIB, DECODING_FLAGS OperandFlags[3]);	// Complete Individual Instruction Object
	~CInstruction(void);	
	void InitializeVariables(void);
};

