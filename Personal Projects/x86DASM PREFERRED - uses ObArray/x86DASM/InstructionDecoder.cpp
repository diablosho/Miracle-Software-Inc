#include "StdAfx.h"
#include "InstructionDecoder.h"
#include "Instruction.h"


CInstructionDecoder::CInstructionDecoder(void)
{
	
}


CInstructionDecoder::~CInstructionDecoder(void)
{
}


void CInstructionDecoder::CreateISAReferenceTable(void)
{
	//InstructionSet.push_back(CInstruction(0x00, _T("ADD"), 'Eb', 'Gb', NULL));
	/*InstructionSet.push_back(CInstruction(0x01, _T("ADD"), 'Ev', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0x02, _T("ADD"), 'Gb', 'Eb', NULL));
	InstructionSet.push_back(CInstruction(0x03, _T("ADD"), 'Gv', 'Ev', NULL));
	InstructionSet.push_back(CInstruction(0x04, _T("ADD"), 'AL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0x05, _T("ADD"), 'eAX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0x06, _T("PUSH"), 'ES', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x07, _T("POP"), 'ES', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x08, _T("OR"), 'Eb', 'Gb', NULL));
	InstructionSet.push_back(CInstruction(0x09, _T("OR"), 'Ev', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0x0A, _T("OR"), 'Gb', 'Eb', NULL));
	InstructionSet.push_back(CInstruction(0x0B, _T("OR"), 'Gv', 'Ev', NULL));
	InstructionSet.push_back(CInstruction(0x0C, _T("OR"), 'AL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0x0D, _T("OR"), 'eAX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0x0E, _T("PUSH"), 'CS', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x0F, _T("EXTENDED"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x10, _T("ADC"), 'Eb', 'Gb', NULL));
	InstructionSet.push_back(CInstruction(0x11, _T("ADC"), 'Ev', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0x12, _T("ADC"), 'Gb', 'Eb', NULL));
	InstructionSet.push_back(CInstruction(0x13, _T("ADC"), 'Gv', 'Ev', NULL));
	InstructionSet.push_back(CInstruction(0x14, _T("ADC"), 'AL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0x15, _T("ADC"), 'eAX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0x16, _T("PUSH"), 'SS', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x17, _T("POP"), 'SS', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x18, _T("SBB"), 'Eb', 'Gb', NULL));
	InstructionSet.push_back(CInstruction(0x19, _T("SBB"), 'Ev', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0x1A, _T("SBB"), 'Gb', 'Eb', NULL));
	InstructionSet.push_back(CInstruction(0x1B, _T("SBB"), 'Gv', 'Ev', NULL));
	InstructionSet.push_back(CInstruction(0x1C, _T("SBB"), 'AL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0x1D, _T("SBB"), 'eAX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0x1E, _T("PUSH"), 'DS', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x1F, _T("POP"), 'DS', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x20, _T("AND"), 'Eb', 'Gb', NULL));
	InstructionSet.push_back(CInstruction(0x21, _T("AND"), 'Ev', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0x22, _T("AND"), 'Gb', 'Eb', NULL));
	InstructionSet.push_back(CInstruction(0x23, _T("AND"), 'Gv', 'Ev', NULL));
	InstructionSet.push_back(CInstruction(0x24, _T("AND"), 'AL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0x25, _T("AND"), 'eAX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0x26, _T("PREFIX"), 'ES:', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x27, _T("DAA"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x28, _T("SUB"), 'Eb', 'Gb', NULL));
	InstructionSet.push_back(CInstruction(0x29, _T("SUB"), 'Ev', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0x2A, _T("SUB"), 'Gb', 'Eb', NULL));
	InstructionSet.push_back(CInstruction(0x2B, _T("SUB"), 'Gv', 'Ev', NULL));
	InstructionSet.push_back(CInstruction(0x2C, _T("SUB"), 'AL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0x2D, _T("SUB"), 'eAX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0x2E, _T("PREFIX"), 'CS:', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x2F, _T("DAS"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x30, _T("XOR"), 'Eb', 'Gb', NULL));
	InstructionSet.push_back(CInstruction(0x31, _T("XOR"), 'Ev', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0x32, _T("XOR"), 'Gb', 'Eb', NULL));
	InstructionSet.push_back(CInstruction(0x33, _T("XOR"), 'Gv', 'Ev', NULL));
	InstructionSet.push_back(CInstruction(0x34, _T("XOR"), 'AL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0x35, _T("XOR"), 'eAX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0x36, _T("PREFIX"), 'SS:', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x37, _T("AAA"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x38, _T("CMP"), 'Eb', 'Gb', NULL));
	InstructionSet.push_back(CInstruction(0x39, _T("CMP"), 'Ev', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0x3A, _T("CMP"), 'Gb', 'Eb', NULL));
	InstructionSet.push_back(CInstruction(0x3B, _T("CMP"), 'Gv', 'Ev', NULL));
	InstructionSet.push_back(CInstruction(0x3C, _T("CMP"), 'AL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0x3D, _T("CMP"), 'eAX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0x3E, _T("PREFIX"), 'DS:', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x3F, _T("AAS"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x40, _T("INC"), 'eAX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x41, _T("INC"), 'eCX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x42, _T("INC"), 'eDX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x43, _T("INC"), 'eBX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x44, _T("INC"), 'eSP', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x45, _T("INC"), 'eBP', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x46, _T("INC"), 'eSI', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x47, _T("INC"), 'eDI', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x48, _T("DEC"), 'eAX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x49, _T("DEC"), 'eCX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x4A, _T("DEC"), 'eDX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x4B, _T("DEC"), 'eBX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x4C, _T("DEC"), 'eSP', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x4D, _T("DEC"), 'eBP', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x4E, _T("DEC"), 'eSI', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x4F, _T("DEC"), 'eDI', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x50, _T("PUSH"), 'eAX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x51, _T("PUSH"), 'eCX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x52, _T("PUSH"), 'eDX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x53, _T("PUSH"), 'eBX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x54, _T("PUSH"), 'eSP', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x55, _T("PUSH"), 'eBP', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x56, _T("PUSH"), 'eSI', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x57, _T("PUSH"), 'eDI', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x58, _T("POP"), 'eAX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x59, _T("POP"), 'eCX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x5A, _T("POP"), 'eDX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x5B, _T("POP"), 'eBX', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x5C, _T("POP"), 'eSP', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x5D, _T("POP"), 'eBP', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x5E, _T("POP"), 'eSI', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x5F, _T("POP"), 'eDI', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x60, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x61, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x62, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x63, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x64, _T("PREFIX"), 'FS:', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x65, _T("PREFIX"), 'GS:', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x66, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x67, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x68, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x69, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x6A, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x6B, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x6C, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x6D, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x6E, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x6F, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x70, _T("JO"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x71, _T("JNO"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x72, _T("JB"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x73, _T("JNB"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x74, _T("JZ"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x75, _T("JNZ"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x76, _T("JBE"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x77, _T("JA"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x78, _T("JS"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x79, _T("JNS"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x7A, _T("JPE"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x7B, _T("JPO"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x7C, _T("JL"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x7D, _T("JGE"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x7E, _T("JLE"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x7F, _T("JG"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x80, _T("GROUP1"), 'Eb', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0x81, _T("GROUP1"), 'Ev', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0x82, _T("GROUP1"), 'Eb', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0x83, _T("GROUP1"), 'Ev', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0x84, _T("TEST"), 'Gb', 'Eb', NULL));
	InstructionSet.push_back(CInstruction(0x85, _T("TEST"), 'Gv', 'Ev', NULL));
	InstructionSet.push_back(CInstruction(0x86, _T("XCHG"), 'Gb', 'Eb', NULL));
	InstructionSet.push_back(CInstruction(0x87, _T("XCHG"), 'Gv', 'Ev', NULL));
	InstructionSet.push_back(CInstruction(0x88, _T("MOV"), 'Eb', 'Gb', NULL));
	InstructionSet.push_back(CInstruction(0x89, _T("MOV"), 'Ev', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0x8A, _T("MOV"), 'Gb', 'Eb', NULL));
	InstructionSet.push_back(CInstruction(0x8B, _T("MOV"), 'Gv', 'Ev', NULL));
	InstructionSet.push_back(CInstruction(0x8C, _T("MOV"), 'Ew', 'Sw', NULL));
	InstructionSet.push_back(CInstruction(0x8D, _T("LEA"), 'Gv', 'M', NULL));
	InstructionSet.push_back(CInstruction(0x8E, _T("MOV"), 'Sw', 'Ew', NULL));
	InstructionSet.push_back(CInstruction(0x8F, _T("POP"), 'Ev', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x90, _T("NOP"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x91, _T("XCHG"), 'eCX', 'eAX', NULL));
	InstructionSet.push_back(CInstruction(0x92, _T("XCHG"), 'eDX', 'eAX', NULL));
	InstructionSet.push_back(CInstruction(0x93, _T("XCHG"), 'eBX', 'eAX', NULL));
	InstructionSet.push_back(CInstruction(0x94, _T("XCHG"), 'eSP', 'eAX', NULL));
	InstructionSet.push_back(CInstruction(0x95, _T("XCHG"), 'eBP', 'eAX', NULL));
	InstructionSet.push_back(CInstruction(0x96, _T("XCHG"), 'eSI', 'eAX', NULL));
	InstructionSet.push_back(CInstruction(0x97, _T("XCHG"), 'eDI', 'eAX', NULL));
	InstructionSet.push_back(CInstruction(0x98, _T("XBW"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x99, _T("XWD"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x9A, _T("CALL"), 'Ap', NULL, NULL));
	InstructionSet.push_back(CInstruction(0x9B, _T("WAIT"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x9C, _T("PUSHF"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x9D, _T("POPF"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x9E, _T("SAHF"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0x9F, _T("LAHF"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xA0, _T("MOV"), 'Al', 'Ob', NULL));
	InstructionSet.push_back(CInstruction(0xA1, _T("MOV"), 'eAX', 'Ov', NULL));
	InstructionSet.push_back(CInstruction(0xA2, _T("MOV"), 'Ob', 'AL', NULL));
	InstructionSet.push_back(CInstruction(0xA3, _T("MOV"), 'Ov', 'eAX', NULL));
	InstructionSet.push_back(CInstruction(0xA4, _T("MOVSB"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xA5, _T("MOVSW"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xA6, _T("CMPSB"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xA7, _T("CMPSW"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xA8, _T("TEST"), 'AL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xA9, _T("TEST"), 'eAX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0xAA, _T("STOSB"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xAB, _T("STOSW"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xAC, _T("LODSB"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xAD, _T("LODSW"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xAE, _T("SCASB"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xAF, _T("SCASW"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xB0, _T("MOV"), 'AL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xB1, _T("MOV"), 'CL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xB2, _T("MOV"), 'DL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xB3, _T("MOV"), 'BL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xB4, _T("MOV"), 'AH', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xB5, _T("MOV"), 'CH', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xB6, _T("MOV"), 'DH', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xB7, _T("MOV"), 'BH', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xB8, _T("MOV"), 'eAX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0xB9, _T("MOV"), 'eCX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0xBA, _T("MOV"), 'eDX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0xBB, _T("MOV"), 'eBX', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0xBC, _T("MOV"), 'eSP', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0xBD, _T("MOV"), 'eBP', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0xBE, _T("MOV"), 'eSI', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0xBF, _T("MOV"), 'eDI', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0xC0, _T("GROUP2A"), 'Eb', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xC1, _T("GROUP2A"), 'Ev', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0xC2, _T("RET"), 'Iw', NULL, NULL));
	InstructionSet.push_back(CInstruction(0xC3, _T("RET"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xC4, _T("LES"), 'Gv', 'Mp', NULL));
	InstructionSet.push_back(CInstruction(0xC5, _T("LDS"), 'Gv', 'Mp', NULL));
	InstructionSet.push_back(CInstruction(0xC6, _T("MOV"), 'Eb', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xC7, _T("MOV"), 'Ev', 'Iv', NULL));
	InstructionSet.push_back(CInstruction(0xC8, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xC9, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xCA, _T("RETF"), 'Iw', NULL, NULL));
	InstructionSet.push_back(CInstruction(0xCB, _T("RETF"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xCC, _T("INT"), '3', NULL, NULL));
	InstructionSet.push_back(CInstruction(0xCD, _T("INT"), 'Ib', NULL, NULL));
	InstructionSet.push_back(CInstruction(0xCE, _T("INTO"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xCF, _T("IRET"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xD0, _T("GROUP2"), 'Eb', '1', NULL));
	InstructionSet.push_back(CInstruction(0xD1, _T("GROUP2"), 'Ev', '1', NULL));
	InstructionSet.push_back(CInstruction(0xD2, _T("GROUP2"), 'Eb', 'CL', NULL));
	InstructionSet.push_back(CInstruction(0xD3, _T("GROUP2"), 'Ev', 'CL', NULL));
	InstructionSet.push_back(CInstruction(0xD4, _T("AAM"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xD5, _T("AAD"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xD6, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xD7, _T("XLAT"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xD8, _T("ESCAPE"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xD9, _T("ESCAPE"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xDA, _T("ESCAPE"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xDB, _T("ESCAPE"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xDC, _T("ESCAPE"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xDD, _T("ESCAPE"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xDE, _T("ESCAPE"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xDF, _T("ESCAPE"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xE0, _T("LOOPNZ"), 'Jb', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0xE1, _T("LOOPZ"), 'Jb', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0xE2, _T("LOOP"), 'Jb', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0xE3, _T("JCXZ"), 'Jb', 'Gv', NULL));
	InstructionSet.push_back(CInstruction(0xE4, _T("IN"), 'AL', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xE5, _T("IN"), 'eAX', 'Ib', NULL));
	InstructionSet.push_back(CInstruction(0xE6, _T("OUT"), 'Ib', 'AL', NULL));
	InstructionSet.push_back(CInstruction(0xE7, _T("OUT"), 'Ib', 'eAX', NULL));
	InstructionSet.push_back(CInstruction(0xE8, _T("CALL"), 'Jv', NULL, NULL));
	InstructionSet.push_back(CInstruction(0xE9, _T("JMP"), 'Jv', NULL, NULL));
	InstructionSet.push_back(CInstruction(0xEA, _T("JMP"), 'AP', NULL, NULL));
	InstructionSet.push_back(CInstruction(0xEB, _T("JMP"), 'Jb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0xEC, _T("IN"), 'AL', 'DX', NULL));
	InstructionSet.push_back(CInstruction(0xED, _T("IN"), 'eAX', 'DX', NULL));
	InstructionSet.push_back(CInstruction(0xEE, _T("OUT"), 'DX', 'AL', NULL));
	InstructionSet.push_back(CInstruction(0xEF, _T("OUT"), 'DX', 'eAX', NULL));
	InstructionSet.push_back(CInstruction(0xF0, _T("LOCK"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xF1, _T("N/A"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xF2, _T("REPNZ"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xF3, _T("REPZ"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xF4, _T("HLT"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xF5, _T("CMC"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xF6, _T("GROUP3"), 'Eb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0xF7, _T("GROUP3"), 'Ev', NULL, NULL));
	InstructionSet.push_back(CInstruction(0xF8, _T("CLC"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xF9, _T("STC"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xFA, _T("CLI"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xFB, _T("STI"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xFC, _T("CLD"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xFD, _T("STD"), NULL, NULL, NULL));
	InstructionSet.push_back(CInstruction(0xFE, _T("GROUP4"), 'Eb', NULL, NULL));
	InstructionSet.push_back(CInstruction(0xFF, _T("GROUP5"), 'Ev', NULL, NULL));*/
}

void CInstructionDecoder::Serialize(CArchive& ar)
{
	CreateISAReferenceTable();
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
