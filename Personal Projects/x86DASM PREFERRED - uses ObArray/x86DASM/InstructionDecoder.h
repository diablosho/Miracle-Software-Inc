#pragma once
#include <afx.h>
#include "Instruction.h"
#include "InstructionDecoder.h"
#include <vector>

class CInstructionDecoder
{
public:
	CInstructionDecoder(void);
	~CInstructionDecoder(void);
	void CreateISAReferenceTable(void);
	virtual void Serialize(CArchive& ar);
	std::vector<CInstruction> InstructionSet;
};

