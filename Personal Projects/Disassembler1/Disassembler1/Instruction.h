#pragma once
#include "afxcoll.h"

class CInstruction
{
public:
	CInstruction(byte* bytesRead, int Size);
	~CInstruction();
	
	void ParsePrefixes();
	void ParseOpcode();
	void DetermineGenInstructionAndOperandTypes();
	void DetermineTwoByteOpcodes();
	void ProcessOpcodeGroups(int groupNumber);		// Decode Opcode Groups
	void ParseModRM();
	void ParseDisplacements(int Opsize);
	void ParseImmediate(int OpSize);
	void ProcessInstruction();
	CString ParseSIB(int Size);
	CString DetermineOperand();
	
	int InstructionPointer, dataSize;
	bool EndOfInstructions;			//  Is string processed?
	bool SpecialBits[6];			//	[0] = D-Bit				[1] = W-Bit									[2] = S-Bit
									//	[3] = tttn bits			[4] = Flags (CF/PF/ZF/SF/OF)				[5] = eeeBits (see below)
	byte* data;
	bool Prefixes[4];				//	[0] = Lock				[1] = Address			[2] = Operand		[3] = Segment
	byte Opcode[3];					//	[0] = Primary Opcode	[1] = Secondary Opcode	[2] = Third Opcode
	byte ModRMSIB[8];				//	[0] = ModRM				[1] = Mod				[2] = Reg			[3] = RM			
									//	[4] = SIB				[5] = Scale				[6] = Index			[7] = Base
	CString Offsets[2];				//	[0] = Displacements		[1] = Immediates
	CString Operands[3];			//	[0] = Op1 Type			[1] = Op2 Type			[2] = Op3 Type
	CString Instruction;
	CString Reg, EA;
	CStringArray FinalInstruction;	//  Keeps a list of final instructions inside string to process


								//////////////////////////////////////////////////////////////////
								//	eeeBits are in ModRM byte:  00 eee 000						//
								//																//
								//	eee			Control Register		Debug Register			//
								//	000				CR0						DR0					//
								//	001				RESERVED				DR1					//
								//	010				CR2						DR2					//
								//	011				CR3						DR3					//
								//	100				CR4						RESERVED			//
								//	101				RESERVED				RESERVED			//
								//	110				RESERVED				DR6					//
								//	111				RESERVED				DR7					//
								//////////////////////////////////////////////////////////////////
	bool isModRM, isSReg, isSIB;
	int OperandNum;
	int InstructionOffset;
	void IncrementCounters(int incNum);
	char OperandType[3];		//[E,G,I,O,J,X,Y,A,F,S,M, (~ = Direct Reg)]	E = Reg/Mem, G = Reg, A = Direct Address/No ModRM/No SIB/Address in Opcode
	char OperandSize[3];		//[b=8, w=16, v=32]
	void InitializeVariables(bool FirstTime);
	unsigned short int CurrentAddressingWordSize;
};

