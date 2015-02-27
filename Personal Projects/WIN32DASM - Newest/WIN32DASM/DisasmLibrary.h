#pragma once
#include "afx.h"
class CDisasmLibrary :
	public CObject
{
public:
	CDisasmLibrary();
	CDisasmLibrary(BYTE* dataRead, BYTE numOfBytes);
	~CDisasmLibrary(void);
	BYTE Prefix[4], Opcode, ModRM, SIB;
	DWORD Displacement, immOperand;
	WORD immSegment;
	BYTE bufferLoc;
private:
	void ParsePrefixes(BYTE*);
	void ParseOpcodes(BYTE*);
	void ParseModRM(BYTE*);
	void ParseSIB(BYTE*);
	void ParseDisplacements(BYTE*);
	void ParseImmediates(BYTE*);
	void OutputInstruction();

	bool	isModRM, isSIB, isDisplacement, isImmediate,
			isWordOperandTypes, isAddressPrefix, isOperandPrefix, dbit;
	BYTE dispSize, immSize, numOfPrefixes;
	bool isGeneralRegister;
	bool isModRM_onlyMemory;
	BYTE Reg;
	bool isRegSelectGeneral, isRegSelectSegment, isRegSelectTest, isRegSelectDebug, 
		isRegSelectControl, isRegSelectMMX;
	bool isEFLAGS;
public:
	DWORD Operands[3];
	void FinishInstruction(void);
};