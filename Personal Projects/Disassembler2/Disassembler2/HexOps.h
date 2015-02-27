#pragma once
class CHexOps
{
public:
	CHexOps();
	~CHexOps();
static CString HexToBinaryString(CString Instruction);
static CString ReplaceValue(CString Instruction, int Position, CString ReplacementString);
CString BinaryToHex(long charArray);
};

