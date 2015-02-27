#include "StdAfx.h"
#include "DisasmLibrary.h"
#include <iomanip>
#include <iostream>
using namespace std;


CDisasmLibrary::CDisasmLibrary(BYTE* dataRead, BYTE numOfBytes)
	: bufferLoc(0)
	, isModRM(false)
	, Opcode(0)
	, ModRM(0)
	, SIB(0)
	, isSIB(false)
	, isDisplacement(false)
	, isImmediate(false)
	, dispSize(8)
	, immSize(8)
	, isWordOperandTypes(false)
	, isAddressPrefix(false)
	, isOperandPrefix(false)
	, numOfPrefixes(0)
	, Displacement(0)
	, immSegment(0)
	, immOperand(0)
	, dbit(false)
	, isGeneralRegister(false)
	, isModRM_onlyMemory(false)
	, Reg(0)
	, isRegSelectGeneral(false)
	, isEFLAGS(false)
{
	// Begin parsing and decoding instruction passed as argument in this function
	ParsePrefixes(dataRead);
	ParseOpcodes(dataRead);
	if (isModRM)			ParseModRM(dataRead);
	if (isSIB)				ParseSIB(dataRead);
	if (isDisplacement)		ParseDisplacements(dataRead);
	if (isImmediate)		ParseImmediates(dataRead);
	FinishInstruction();
	OutputInstruction();
	system("Pause");
}


CDisasmLibrary::~CDisasmLibrary(void)
{
}


void CDisasmLibrary::ParsePrefixes(BYTE* dataRead)
{
	int count = 0;

	while (count < 4)
	{
		switch (dataRead[bufferLoc])
		{
			case 0x26:	Prefix[count] = 0x26;	numOfPrefixes++;	count++;	bufferLoc++;	break;
			case 0x2E:	Prefix[count] = 0x2E;	numOfPrefixes++;	count++;	bufferLoc++;	break;
			case 0x36:	Prefix[count] = 0x36;	numOfPrefixes++;	count++;	bufferLoc++;	break;
			case 0x3E:	Prefix[count] = 0x3E;	numOfPrefixes++;	count++;	bufferLoc++;	break;
			case 0x64:	Prefix[count] = 0x64;	numOfPrefixes++;	count++;	bufferLoc++;	break;
			case 0x65:	Prefix[count] = 0x65;	numOfPrefixes++;	count++;	bufferLoc++;	break;
			case 0x66:	Prefix[count] = 0x66;	numOfPrefixes++;	count++;	bufferLoc++;	break;
			case 0x67:	Prefix[count] = 0x67;	numOfPrefixes++;	count++;	bufferLoc++;	break;
			case 0xF0:	Prefix[count] = 0xF0;	numOfPrefixes++;	count++;	bufferLoc++;	break;
			case 0xF2:  Prefix[count] = 0xF2;	numOfPrefixes++;	count++;	bufferLoc++;	break;
			case 0xF3:	Prefix[count] = 0xF3;	numOfPrefixes++;	count++;	bufferLoc++;	break;
			default:	count = 4;									break;
		}
	}
}


void CDisasmLibrary::ParseOpcodes(BYTE* dataRead)
{
	Opcode = dataRead[bufferLoc];
	bufferLoc++;
	
	switch (Opcode & 0x03)
	{
		case 0x00:	dbit = false;	isWordOperandTypes = false;		break;
		case 0x01:	dbit = false;	isWordOperandTypes = true;		break;
		case 0x02:	dbit = true;	isWordOperandTypes = false;		break;
		case 0x03:	dbit = true;	isWordOperandTypes = true;		break;
		default:													break;
	}
	int OperandTypes[3];
	switch (Opcode)
	{
	case 0x00:	OperandTypes[0] = 'Eb';		OperandTypes[1] = 'Gb';		break;
	case 0x01:	OperandTypes[0] = 'Ev';		OperandTypes[1] = 'Gv';		break;
	case 0x02:	OperandTypes[0] = 'Gb';		OperandTypes[1] = 'Eb';		break;
	case 0x03:	OperandTypes[0] = 'Gv';		OperandTypes[1] = 'Ev';		break;
	case 0x04:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Ib';		break;
	case 0x05:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Iv';		break;
	case 0x06:	OperandTypes[0] = 'ES';									break;
	case 0x07:	OperandTypes[0] = 'ES';									break;
	
	case 0x08:	OperandTypes[0] = 'Eb';		OperandTypes[1] = 'Gb';		break;
	case 0x09:	OperandTypes[0] = 'Ev';		OperandTypes[1] = 'Gv';		break;
	case 0x0A:	OperandTypes[0] = 'Gb';		OperandTypes[1] = 'Eb';		break;
	case 0x0B:	OperandTypes[0] = 'Gv';		OperandTypes[1] = 'Ev';		break;
	case 0x0C:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Ib';		break;
	case 0x0D:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Iv';		break;
	case 0x0E:	OperandTypes[0] = 'CS';									break;
	
	case 0x10:	OperandTypes[0] = 'Eb';		OperandTypes[1] = 'Gb';		break;
	case 0x11:	OperandTypes[0] = 'Ev';		OperandTypes[1] = 'Gv';		break;
	case 0x12:	OperandTypes[0] = 'Gb';		OperandTypes[1] = 'Eb';		break;
	case 0x13:	OperandTypes[0] = 'Gv';		OperandTypes[1] = 'Ev';		break;
	case 0x14:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Ib';		break;
	case 0x15:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Iv';		break;
	case 0x16:	OperandTypes[0] = 'SS';									break;
	case 0x17:	OperandTypes[0] = 'SS';									break;
	
	case 0x18:	OperandTypes[0] = 'Eb';		OperandTypes[1] = 'Gb';		break;
	case 0x19:	OperandTypes[0] = 'Ev';		OperandTypes[1] = 'Gv';		break;
	case 0x1A:	OperandTypes[0] = 'Gb';		OperandTypes[1] = 'Eb';		break;
	case 0x1B:	OperandTypes[0] = 'Gv';		OperandTypes[1] = 'Ev';		break;
	case 0x1C:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Ib';		break;
	case 0x1D:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Iv';		break;
	case 0x1E:	OperandTypes[0] = 'DS';									break;
	case 0x1F:	OperandTypes[0] = 'DS';									break;
	
	case 0x20:	OperandTypes[0] = 'Eb';		OperandTypes[1] = 'Gb';		break;
	case 0x21:	OperandTypes[0] = 'Ev';		OperandTypes[1] = 'Gv';		break;
	case 0x22:	OperandTypes[0] = 'Gb';		OperandTypes[1] = 'Eb';		break;
	case 0x23:	OperandTypes[0] = 'Gv';		OperandTypes[1] = 'Ev';		break;
	case 0x24:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Ib';		break;
	case 0x25:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Iv';		break;
	case 0x26:	OperandTypes[0] = 'ES';									break;
	
	case 0x28:	OperandTypes[0] = 'Eb';		OperandTypes[1] = 'Gb';		break;
	case 0x29:	OperandTypes[0] = 'Ev';		OperandTypes[1] = 'Gv';		break;
	case 0x2A:	OperandTypes[0] = 'Gb';		OperandTypes[1] = 'Eb';		break;
	case 0x2B:	OperandTypes[0] = 'Gv';		OperandTypes[1] = 'Ev';		break;
	case 0x2C:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Ib';		break;
	case 0x2D:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Iv';		break;
	case 0x2E:	OperandTypes[0] = 'CS';									break;
	
	case 0x30:	OperandTypes[0] = 'Eb';		OperandTypes[1] = 'Gb';		break;
	case 0x31:	OperandTypes[0] = 'Ev';		OperandTypes[1] = 'Gv';		break;
	case 0x32:	OperandTypes[0] = 'Gb';		OperandTypes[1] = 'Eb';		break;
	case 0x33:	OperandTypes[0] = 'Gv';		OperandTypes[1] = 'Ev';		break;
	case 0x34:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Ib';		break;
	case 0x35:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Iv';		break;
	case 0x36:	OperandTypes[0] = 'SS';									break;
	
	case 0x38:	OperandTypes[0] = 'Eb';		OperandTypes[1] = 'Gb';		break;
	case 0x39:	OperandTypes[0] = 'Ev';		OperandTypes[1] = 'Gv';		break;
	case 0x3A:	OperandTypes[0] = 'Gb';		OperandTypes[1] = 'Eb';		break;
	case 0x3B:	OperandTypes[0] = 'Gv';		OperandTypes[1] = 'Ev';		break;
	case 0x3C:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Iv';		break;
	case 0x3D:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Iv';		break;
	case 0x3E:	OperandTypes[0] = 'DS';						break;
	
	case 0x40:	OperandTypes[0] = 'EAX';					break;
	case 0x41:	OperandTypes[0] = 'ECX';					break;
	case 0x42:	OperandTypes[0] = 'EDX';					break;
	case 0x43:	OperandTypes[0] = 'EBX';					break;
	case 0x44:	OperandTypes[0] = 'ESP';					break;
	case 0x45:	OperandTypes[0] = 'EBP';					break;
	case 0x46:	OperandTypes[0] = 'ESI';					break;
	case 0x47:	OperandTypes[0] = 'EDI';					break;
	
	case 0x48:	OperandTypes[0] = 'EAX';					break;
	case 0x49:	OperandTypes[0] = 'ECX';					break;
	case 0x4A:	OperandTypes[0] = 'EDX';					break;
	case 0x4B:	OperandTypes[0] = 'EBX';					break;
	case 0x4C:	OperandTypes[0] = 'ESP';					break;
	case 0x4D:	OperandTypes[0] = 'EBP';					break;
	case 0x4E:	OperandTypes[0] = 'ESI';					break;
	case 0x4F:	OperandTypes[0] = 'EDI';					break;
	
	case 0x50:	OperandTypes[0] = 'EAX';					break;
	case 0x51:	OperandTypes[0] = 'ECX';					break;
	case 0x52:	OperandTypes[0] = 'EDX';					break;
	case 0x53:	OperandTypes[0] = 'EBX';					break;
	case 0x54:	OperandTypes[0] = 'ESP';					break;
	case 0x55:	OperandTypes[0] = 'EBP';					break;
	case 0x56:	OperandTypes[0] = 'ESI';					break;
	case 0x57:	OperandTypes[0] = 'EDI';					break;
	
	case 0x58:	OperandTypes[0] = 'EAX';					break;
	case 0x59:	OperandTypes[0] = 'ECX';					break;
	case 0x5A:	OperandTypes[0] = 'EDX';					break;
	case 0x5B:	OperandTypes[0] = 'EBX';					break;
	case 0x5C:	OperandTypes[0] = 'ESP';					break;
	case 0x5D:	OperandTypes[0] = 'EBP';					break;
	case 0x5E:	OperandTypes[0] = 'ESI';					break;
	case 0x5F:	OperandTypes[0] = 'EDI';					break;
	
	case 0x62:	OperandTypes[0] = 'Gv';	OperandTypes[1] = 'Ma';	break;
	case 0x63:	OperandTypes[0] = 'Ew';	OperandTypes[1] = 'Gw';	break;
	
	case 0x68:	OperandTypes[0] = 'Iv';						break;
	case 0x69:	OperandTypes[0] = 'Gv';	OperandTypes[1] = 'Ev';	OperandTypes[2] = 'Iv';	break;
	case 0x6A:	OperandTypes[0] = 'Iv';						break;
	case 0x6B:	OperandTypes[0] = 'Gv';	OperandTypes[1] = 'Ev';	OperandTypes[2] = 'Ib';	break;
	case 0x6C:	OperandTypes[0] = 'Yb';	OperandTypes[1] = 'DX';	break;
	case 0x6D:	OperandTypes[0] = 'Yv';	OperandTypes[1] = 'DX';	break;
	case 0x6E:	OperandTypes[0] = 'DX';	OperandTypes[1] = 'Xb';	break;
	case 0x6F:	OperandTypes[0] = 'DX';	OperandTypes[1] = 'Xv';	break;
	
	case 0x70:	OperandTypes[0] = 'JO';						break;
	case 0x71:	OperandTypes[0] = 'JNO';					break;
	case 0x72:	OperandTypes[0] = 'JB';						break;
	case 0x73:	OperandTypes[0] = 'JNB';					break;
	case 0x74:	OperandTypes[0] = 'JZ';						break;
	case 0x75:	OperandTypes[0] = 'JNZ';					break;
	case 0x76:	OperandTypes[0] = 'JBE';					break;
	case 0x77:	OperandTypes[0] = 'JNBE';					break;
	
	case 0x78:	OperandTypes[0] = 'JS';						break;
	case 0x79:	OperandTypes[0] = 'JNS';					break;
	case 0x7A:	OperandTypes[0] = 'JP';						break;
	case 0x7B:	OperandTypes[0] = 'JNP';					break;
	case 0x7C:	OperandTypes[0] = 'JL';						break;
	case 0x7D:	OperandTypes[0] = 'JNL';					break;
	case 0x7E:	OperandTypes[0] = 'JLE';					break;
	case 0x7F:	OperandTypes[0] = 'JNLE';					break;
	
	case 0x80:	OperandTypes[0] = 'Eb';	OperandTypes[1] = 'Ib';	break;
	case 0x81:	OperandTypes[0] = 'Ev';	OperandTypes[1] = 'Iv';	break;
	case 0x82:	OperandTypes[0] = 'Ev';	OperandTypes[1] = 'Ib';	break;
	case 0x83:	OperandTypes[0] = 'Eb';	OperandTypes[1] = 'Ib';	break;
	case 0x84:	OperandTypes[0] = 'Eb';	OperandTypes[1] = 'Gb';	break;
	case 0x85:	OperandTypes[0] = 'Ev';	OperandTypes[1] = 'Gv';	break;
	case 0x86:	OperandTypes[0] = 'Eb';	OperandTypes[1] = 'Gb';	break;
	case 0x87:	OperandTypes[0] = 'Ev';	OperandTypes[1] = 'Gv';	break;
	
	case 0x88:	OperandTypes[0] = 'Eb';	OperandTypes[1] = 'Gb';	break;
	case 0x89:	OperandTypes[0] = 'Ev';	OperandTypes[1] = 'Gv';	break;
	case 0x8A:	OperandTypes[0] = 'Gb';	OperandTypes[1] = 'Eb';	break;
	case 0x8B:	OperandTypes[0] = 'Gv';	OperandTypes[1] = 'Ev';	break;
	case 0x8C:	OperandTypes[0] = 'Ew';	OperandTypes[1] = 'Sw';	break;
	case 0x8D:	OperandTypes[0] = 'Gv';	OperandTypes[1] = 'M';	break;
	case 0x8E:	OperandTypes[0] = 'Sw';	OperandTypes[1] = 'Ew';	break;
	case 0x8F:	OperandTypes[0] = 'Ev';						break;
	
	case 0x91:	OperandTypes[0] = 'ECX';					break;
	case 0x92:	OperandTypes[0] = 'EDX';					break;
	case 0x93:	OperandTypes[0] = 'EBX';					break;
	case 0x94:	OperandTypes[0] = 'ESP';					break;
	case 0x95:	OperandTypes[0] = 'EBP';					break;
	case 0x96:	OperandTypes[0] = 'ESI';					break;
	case 0x97:	OperandTypes[0] = 'EDI';					break;
	
	case 0x9A:	OperandTypes[0] = 'Ap';						break;
	case 0x9C:	OperandTypes[0] = 'Fv';						break;
	case 0x9D:	OperandTypes[0] = 'Fv';						break;
	
	case 0xA0:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Ob';	break;
	case 0xA1:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Ov';	break;
	case 0xA2:	OperandTypes[0] = 'Ob';		OperandTypes[1] = 'AL';	break;
	case 0xA3:	OperandTypes[0] = 'Ov';		OperandTypes[1] = 'EAX';break;
	case 0xA4:	OperandTypes[0] = 'Xb';		OperandTypes[1] = 'Yb';	break;
	case 0xA5:	OperandTypes[0] = 'Xv';		OperandTypes[1] = 'Yv';	break;
	case 0xA6:	OperandTypes[0] = 'Xb';		OperandTypes[1] = 'Yb';	break;
	case 0xA7:	OperandTypes[0] = 'Xv';		OperandTypes[1] = 'Yv';	break;
	
	case 0xA8:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Ib';	break;
	case 0xA9:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Iv';	break;
	case 0xAA:	OperandTypes[0] = 'Yb';		OperandTypes[1] = 'AL';	break;
	case 0xAB:	OperandTypes[0] = 'Yv';		OperandTypes[1] = 'EAX';break;
	case 0xAC:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Xb';	break;
	case 0xAD:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Xv';	break;
	case 0xAE:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Yb';	break;
	case 0xAF:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Yv';	break;
	
	case 0xB0:	OperandTypes[0] = 'AL';		OperandTypes[1] = 'Ib';	break;
	case 0xB1:	OperandTypes[0] = 'CL';		OperandTypes[1] = 'Ib';	break;
	case 0xB2:	OperandTypes[0] = 'DL';		OperandTypes[1] = 'Ib';	break;
	case 0xB3:	OperandTypes[0] = 'BL';		OperandTypes[1] = 'Ib';	break;
	case 0xB4:	OperandTypes[0] = 'AH';		OperandTypes[1] = 'Ib';	break;
	case 0xB5:	OperandTypes[0] = 'CH';		OperandTypes[1] = 'Ib';	break;
	case 0xB6:	OperandTypes[0] = 'DH';		OperandTypes[1] = 'Ib';	break;
	case 0xB7:	OperandTypes[0] = 'BH';		OperandTypes[1] = 'Ib';	break;
	
	case 0xB8:	OperandTypes[0] = 'EAX';	OperandTypes[1] = 'Iv';	break;
	case 0xB9:	OperandTypes[0] = 'ECX';	OperandTypes[1] = 'Iv';	break;
	case 0xBA:	OperandTypes[0] = 'EDX';	OperandTypes[1] = 'Iv';	break;
	case 0xBB:	OperandTypes[0] = 'EBX';	OperandTypes[1] = 'Iv';	break;
	case 0xBC:	OperandTypes[0] = 'ESP';	OperandTypes[1] = 'Iv';	break;
	case 0xBD:	OperandTypes[0] = 'EBP';	OperandTypes[1] = 'Iv';	break;
	case 0xBE:	OperandTypes[0] = 'ESI';	OperandTypes[1] = 'Iv';	break;
	case 0xBF:	OperandTypes[0] = 'EDI';	OperandTypes[1] = 'Iv';	break;
	
	case 0xC0:	OperandTypes[0] = 'Eb';		OperandTypes[0] = 'Ib';	break;
	case 0xC1:	OperandTypes[0] = 'Ev';		OperandTypes[0] = 'Ib';	break;
	case 0xC2:	OperandTypes[0] = 'Iw';								break;
	case 0xC3:														break;
	case 0xC4:	OperandTypes[0] = 'Gv';		OperandTypes[0] = 'Mp';	break;
	case 0xC5:	OperandTypes[0] = 'Gv';		OperandTypes[0] = 'Mp';	break;
	case 0xC6:	OperandTypes[0] = 'Eb';		OperandTypes[0] = 'Ib';	break;
	case 0xC7:	OperandTypes[0] = 'Ev';		OperandTypes[0] = 'Iv';	break;
	
	case 0xC8:	OperandTypes[0] = 'Iw';		OperandTypes[0] = 'Ib';	break;
	case 0xCA:	OperandTypes[0] = 'Iw';								break;
	case 0xCC:	OperandTypes[0] = '3';								break;
	case 0xCD:	OperandTypes[0] = 'Ib';								break;
		
	case 0xD0:	OperandTypes[0] = 'Eb';		OperandTypes[0] = '1';	break;
	case 0xD1:	OperandTypes[0] = 'Ev';		OperandTypes[0] = '1';	break;
	case 0xD2:	OperandTypes[0] = 'Eb';		OperandTypes[0] = 'CL';	break;
	case 0xD3:	OperandTypes[0] = 'Ev';		OperandTypes[0] = 'CL';	break;
	
	case 0xE0:	OperandTypes[0] = 'Jb';								break;
	case 0xE1:	OperandTypes[0] = 'Jb';								break;
	case 0xE2:	OperandTypes[0] = 'Jb';								break;
	case 0xE3:	OperandTypes[0] = 'Jb';								break;
	case 0xE4:	OperandTypes[0] = 'AL';		OperandTypes[0] = 'Ib';	break;
	case 0xE5:	OperandTypes[0] = 'EAX';	OperandTypes[0] = 'Ib';	break;
	case 0xE6:	OperandTypes[0] = 'Ib';		OperandTypes[0] = 'AL';	break;
	case 0xE7:	OperandTypes[0] = 'Ib';		OperandTypes[0] = 'EAX';break;
	
	case 0xE8:	OperandTypes[0] = 'Jv';								break;
	case 0xE9:	OperandTypes[0] = 'Jv';								break;
	case 0xEA:	OperandTypes[0] = 'Ap';								break;
	case 0xEB:	OperandTypes[0] = 'Jb';								break;
	case 0xEC:	OperandTypes[0] = 'AL';		OperandTypes[0] = 'DX';	break;
	case 0xED:	OperandTypes[0] = 'EAX';	OperandTypes[0] = 'DX';	break;
	case 0xEE:	OperandTypes[0] = 'DX';		OperandTypes[0] = 'AL';	break;
	case 0xEF:	OperandTypes[0] = 'DX';		OperandTypes[0] = 'EAX';break;
	
	case 0xF6:	OperandTypes[0] = 'Eb';								break;
	case 0xF7:	OperandTypes[0] = 'Ev';								break;
	
	case 0xFE:	/*	Group 4	*/										break;
	case 0xFF:	/*	Group 5	*/										break;
	default:	break;
	}

	for (int currentOperand = 0; currentOperand < 3; currentOperand++)
	{
		switch (OperandTypes[currentOperand])
		{
		case 'Eb':	isModRM = true;								break;
		case 'Ev':	isModRM = true;								break;
		case 'Ew':	isModRM = true;								break;
		case 'Gb':	isModRM = true;	isRegSelectGeneral = true;	break;
		case 'Gv':	isRegSelectGeneral = true;					break;
		case 'Gw':	isRegSelectGeneral = true;					break;
		case 'Ib':	immSize = 8;	isImmediate = true;			break;
		case 'Iv':	immSize = 32;	isImmediate = true;			break;
		case 'Iw':	immSize = 16;	isImmediate = true;			break;
		case 'Ma':	isModRM = true;								break;
		case 'Mp':												break;
		case 'Ob':	immSize = 32;	isImmediate = true;			break;
		case 'Ov':	immSize = 32;	isImmediate = true;			break;
		case 'Xb':												break;
		case 'Xv':												break;
		case 'Yb':												break;
		case 'Yv':												break;
		case 'Jb':	immSize = 8;	isImmediate = true;			break;
		case 'Jv':	immSize = 32;	isImmediate = true;			break;
		case 'Sw':	isModRM = true;	isRegSelectSegment = true;	break;
		case 'M':	isModRM = true;	isModRM_onlyMemory = true;	break;
		case 'Ap':	immSize = 48;	isImmediate = true;			break;
		case 'Fv':	isEFLAGS = true;							break;
		case '1':	break;
		case '3':	break;
		case 'JO':	immSize = 8;	isImmediate = true;	break;
		case 'JNO':	immSize = 8;	isImmediate = true;	break;
		case 'JB':	immSize = 8;	isImmediate = true;	break;
		case 'JNB':	immSize = 8;	isImmediate = true;	break;
		case 'JZ':	immSize = 8;	isImmediate = true;	break;
		case 'JNZ':	immSize = 8;	isImmediate = true;	break;
		case 'JBE':	immSize = 8;	isImmediate = true;	break;
		case 'JNBE':immSize = 8;	isImmediate = true;	break;
		case 'JS':	immSize = 8;	isImmediate = true;	break;
		case 'JNS':	immSize = 8;	isImmediate = true;	break;
		case 'JP':	immSize = 8;	isImmediate = true;	break;
		case 'JNP':	immSize = 8;	isImmediate = true;	break;
		case 'JL':	immSize = 8;	isImmediate = true;	break;
		case 'JNL':	immSize = 8;	isImmediate = true;	break;
		case 'JLE':	immSize = 8;	isImmediate = true;	break;
		case 'JNLE':immSize = 8;	isImmediate = true;	break;
		default:	break;
		}
	}
}


void CDisasmLibrary::ParseModRM(BYTE* dataRead)
{
	ModRM = dataRead[bufferLoc];
	Reg = ModRM & 0x38;
	bufferLoc++;

	if (isWordOperandTypes && !isOperandPrefix)
	{
		if (isRegSelectGeneral)
		{
			switch (Reg)
			{
			case 0x00:	Operands[0] = 'EAX';	break;	//	eax
			case 0x08:	Operands[0] = 'ECX';	break;	//	ecx
			case 0x10:	Operands[0] = 'EDX';	break;	//	edx
			case 0x18:	Operands[0] = 'EBX';	break;	//	ebx
			case 0x20:	Operands[0] = 'ESP';	break;	//	esp
			case 0x28:	Operands[0] = 'EBP';	break;	//	ebp
			case 0x30:	Operands[0] = 'ESI';	break;	//	esi
			case 0x38:	Operands[0] = 'EDI';	break;	//	edi
			}
		}
		switch (ModRM & 0xC7)	// DWORD OperandTypes
		{
			case 0x00:																break;
			case 0x01:																break;
			case 0x02:																break;
			case 0x03:																break;
			case 0x04:											isSIB = true;		break;
			case 0x05:	isDisplacement = true;	dispSize = 32;						break;
			case 0x06:																break;
			case 0x07:																break;
			case 0x40:	isDisplacement = true;	dispSize = 8;						break;
			case 0x41:	isDisplacement = true;	dispSize = 8;						break;
			case 0x42:	isDisplacement = true;	dispSize = 8;						break;
			case 0x43:	isDisplacement = true;	dispSize = 8;						break;
			case 0x44:	isDisplacement = true;	dispSize = 8;	isSIB = true;		break;
			case 0x45:	isDisplacement = true;	dispSize = 8;						break;
			case 0x46:	isDisplacement = true;	dispSize = 8;						break;
			case 0x47:	isDisplacement = true;	dispSize = 8;						break;
			case 0x80:	isDisplacement = true;	dispSize = 32;						break;
			case 0x81:	isDisplacement = true;	dispSize = 32;						break;
			case 0x82:	isDisplacement = true;	dispSize = 32;						break;
			case 0x83:	isDisplacement = true;	dispSize = 32;						break;
			case 0x84:	isDisplacement = true;	dispSize = 32;	isSIB = true;		break;
			case 0x85:	isDisplacement = true;	dispSize = 32;						break;
			case 0x86:	isDisplacement = true;	dispSize = 32;						break;
			case 0x87:	isDisplacement = true;	dispSize = 32;						break;
			case 0xC0:																break;
			case 0xC1:																break;
			case 0xC2:																break;
			case 0xC3:																break;
			case 0xC4:																break;
			case 0xC5:																break;
			case 0xC6:																break;
			case 0xC7:																break;
			default:																							break;
		}
	}
	else if (isWordOperandTypes && isOperandPrefix)
	{
		if (isRegSelectGeneral)
		{
			switch (Reg)	// 16-Bit Operands
			{
			case 0x00:	Operands[0] = 'AX';	break;	//	ax
			case 0x08:	Operands[0] = 'CX';	break;	//	cx
			case 0x10:	Operands[0] = 'DX';	break;	//	dx
			case 0x18:	Operands[0] = 'BX';	break;	//	bx
			case 0x20:	Operands[0] = 'SP';	break;	//	sp
			case 0x28:	Operands[0] = 'BP';	break;	//	bp
			case 0x30:	Operands[0] = 'SI';	break;	//	si
			case 0x38:	Operands[0] = 'DI';	break;	//	di
			}
		}
		switch (ModRM & 0xC7)	// WORD OperandTypes
		{
			case 0x00:																break;
			case 0x01:																break;
			case 0x02:																break;
			case 0x03:																break;
			case 0x04:											isSIB = true;		break;
			case 0x05:	isDisplacement = true;	dispSize = 32;						break;
			case 0x06:																break;
			case 0x07:																break;
			case 0x40:	isDisplacement = true;	dispSize = 8;						break;
			case 0x41:	isDisplacement = true;	dispSize = 8;						break;
			case 0x42:	isDisplacement = true;	dispSize = 8;						break;
			case 0x43:	isDisplacement = true;	dispSize = 8;						break;
			case 0x44:	isDisplacement = true;	dispSize = 8;	isSIB = true;		break;
			case 0x45:	isDisplacement = true;	dispSize = 8;						break;
			case 0x46:	isDisplacement = true;	dispSize = 8;						break;
			case 0x47:	isDisplacement = true;	dispSize = 8;						break;
			case 0x80:	isDisplacement = true;	dispSize = 32;						break;
			case 0x81:	isDisplacement = true;	dispSize = 32;						break;
			case 0x82:	isDisplacement = true;	dispSize = 32;						break;
			case 0x83:	isDisplacement = true;	dispSize = 32;						break;
			case 0x84:	isDisplacement = true;	dispSize = 32;	isSIB = true;		break;
			case 0x85:	isDisplacement = true;	dispSize = 32;						break;
			case 0x86:	isDisplacement = true;	dispSize = 32;						break;
			case 0x87:	isDisplacement = true;	dispSize = 32;						break;
			case 0xC0:																break;
			case 0xC1:																break;
			case 0xC2:																break;
			case 0xC3:																break;
			case 0xC4:																break;
			case 0xC5:																break;
			case 0xC6:																break;
			case 0xC7:																break;
			default:																							break;
		}
	}
	else if (!isWordOperandTypes)
	{
		if (isRegSelectGeneral)
		{
			switch (Reg)	// 8-Bit Operands
			{
			case 0x00:	Operands[0] = 'AL';		break;	//	al
			case 0x08:	Operands[0] = 'CL';		break;	//	cl
			case 0x10:	Operands[0] = 'DL';		break;	//	dl
			case 0x18:	Operands[0] = 'BL';		break;	//	bl
			case 0x20:	Operands[0] = 'AH';		break;	//	ah
			case 0x28:	Operands[0] = 'CH';		break;	//	ch
			case 0x30:	Operands[0] = 'DH';		break;	//	dh
			case 0x38:	Operands[0] = 'BH';		break;	//	bh
			}
		}
		switch (ModRM & 0xC7)	// BYTE OperandTypes
		{
			case 0x00:																break;
			case 0x01:																break;
			case 0x02:																break;
			case 0x03:																break;
			case 0x04:											isSIB = true;		break;
			case 0x05:	isDisplacement = true;	dispSize = 32;						break;
			case 0x06:																break;
			case 0x07:																break;
			case 0x40:	isDisplacement = true;	dispSize = 8;						break;
			case 0x41:	isDisplacement = true;	dispSize = 8;						break;
			case 0x42:	isDisplacement = true;	dispSize = 8;						break;
			case 0x43:	isDisplacement = true;	dispSize = 8;						break;
			case 0x44:	isDisplacement = true;	dispSize = 8;	isSIB = true;		break;
			case 0x45:	isDisplacement = true;	dispSize = 8;						break;
			case 0x46:	isDisplacement = true;	dispSize = 8;						break;
			case 0x47:	isDisplacement = true;	dispSize = 8;						break;
			case 0x80:	isDisplacement = true;	dispSize = 32;						break;
			case 0x81:	isDisplacement = true;	dispSize = 32;						break;
			case 0x82:	isDisplacement = true;	dispSize = 32;						break;
			case 0x83:	isDisplacement = true;	dispSize = 32;						break;
			case 0x84:	isDisplacement = true;	dispSize = 32;	isSIB = true;		break;
			case 0x85:	isDisplacement = true;	dispSize = 32;						break;
			case 0x86:	isDisplacement = true;	dispSize = 32;						break;
			case 0x87:	isDisplacement = true;	dispSize = 32;						break;
			case 0xC0:																break;
			case 0xC1:																break;
			case 0xC2:																break;
			case 0xC3:																break;
			case 0xC4:																break;
			case 0xC5:																break;
			case 0xC6:																break;
			case 0xC7:																break;
			default:																							break;
		}
	}
}


void CDisasmLibrary::ParseSIB(BYTE* dataRead)
{
	SIB = dataRead[bufferLoc];
	bufferLoc++;

	switch (SIB & 0x07)
	{
		case 0x00:	break;	//EAX
		case 0x01:	break;	//ECX
		case 0x02:	break;	//EDX
		case 0x03:	break;	//EBX
		case 0x04:	break;	//ESP
		case 0x06:	break;	//ESI
		case 0x07:	break;	//EDI
		case 0x05:	
		{
			if ((ModRM & 0xC0) == 0x00)
			{
				isDisplacement = true;
				ParseDisplacements(dataRead);
			}
			if ((ModRM & 0xC0) == 0x40 || (ModRM & 0xC0) == 0x80)
			{
			}
			break;
		}
	}
	
	switch (SIB & 0xF8)
	{
		case 0x00:	break;	//EAX * 1
		case 0x08:	break;	//ECX * 1
		case 0x10:	break;	//EDX * 1
		case 0x18:	break;	//EBX * 1
		case 0x20:	break;	//ILLEGAL
		case 0x28:	break;	//EBP * 1
		case 0x30:	break;	//ESI * 1
		case 0x38:	break;	//EDI * 1
		case 0x40:	break;	//EAX * 2
		case 0x48:	break;	//ECX * 2
		case 0x50:	break;	//EDX * 2
		case 0x58:	break;	//EBX * 2
		case 0x60:	break;	//ILLEGAL
		case 0x68:	break;	//EBP * 2
		case 0x70:	break;	//ESI * 2
		case 0x78:	break;	//EDI * 2
		case 0x80:	break;	//EAX * 4
		case 0x88:	break;	//ECX * 4
		case 0x90:	break;	//EDX * 4
		case 0x98:	break;	//EBX * 4
		case 0xA0:	break;	//ILLEGAL
		case 0xA8:	break;	//EBP * 4
		case 0xB0:	break;	//ESI * 4
		case 0xB8:	break;	//EDI * 4
		case 0xC0:	break;	//EAX * 8
		case 0xC8:	break;	//ECX * 8
		case 0xD0:	break;	//EDX * 8
		case 0xD8:	break;	//EBX * 8
		case 0xE0:	break;	//ILLEGAL
		case 0xE8:	break;	//EBP * 8
		case 0xF0:	break;	//ESI * 8
		case 0xF8:	break;	//EDI * 8
	}
}


void CDisasmLibrary::ParseDisplacements(BYTE* dataRead)
{
	switch (dispSize)
	{
		case 8:	
		{
			Displacement = (BYTE)(*((DWORD*)(dataRead + bufferLoc)));;
			bufferLoc += 1;
			break;
		}
		case 32:	
		{
			if (isOperandPrefix)	{	Displacement = _byteswap_ushort((WORD)(*(WORD*)(dataRead + bufferLoc)));		bufferLoc += 2;}
			else					{	Displacement = _byteswap_ulong((DWORD)(*(DWORD*)(dataRead + bufferLoc)));		bufferLoc += 4;}
			break;
		}
		default:	break;
	}
}


void CDisasmLibrary::ParseImmediates(BYTE* dataRead)
{
	if (isOperandPrefix)
	{
		switch (immSize)
		{
			case 8:		immOperand = (BYTE)(*((DWORD*)(dataRead + bufferLoc)));					bufferLoc += 1;		break;
			case 32:	immOperand = _byteswap_ushort((WORD)(*(WORD*)(dataRead + bufferLoc)));	bufferLoc += 2;		break;
			case 48:	
			{
				immOperand = _byteswap_ushort((WORD)(*(WORD*)(dataRead + bufferLoc)));	
				bufferLoc += 4;		
			}
			break;
		}		
	}	
	else if (!isOperandPrefix)
	{
		switch (immSize)
		{
			case 8:		immOperand = (BYTE)(*((DWORD*)(dataRead + bufferLoc)));					bufferLoc += 1;		break;
			case 32:	immOperand = _byteswap_ulong((DWORD)(*(DWORD*)(dataRead + bufferLoc)));	bufferLoc += 4;		break;
			case 48:	
			{
				immOperand = _byteswap_ulong((DWORD)(*(DWORD*)(dataRead + bufferLoc)));	
				bufferLoc += 4;
				immSegment = _byteswap_ushort((WORD)(*(WORD*)(dataRead + bufferLoc)));
				bufferLoc += 2;		
			}
			break;
		}
	}
}


void CDisasmLibrary::OutputInstruction()
{
	switch (numOfPrefixes)
	{
	case 0x00:	break;
	case 0x01:	printf("%02X", (int)Prefix[0]);		break;
	case 0x02:	printf("%02X%02X", (int)Prefix[0], (int)Prefix[1]);		break;
	case 0x03:	printf("%02X%02X%02X", (int)Prefix[0], (int)Prefix[1], (int)Prefix[2]);		break;
	case 0x04:	printf("%02X%02X%02X%02X", (int)Prefix[0], (int)Prefix[1], (int)Prefix[2], (int)Prefix[3]);	break;
	}

	printf("%02X", (int)Opcode);
	if (isModRM)
		printf("%02X", (int)ModRM);
	if (isSIB)
		printf("%02X", (int)SIB);
	if (isDisplacement)
	{
		switch (dispSize)
		{
		case 0x08:	printf("%02X", (int)Displacement);	break;
		case 0x10:	printf("%04X", (int)Displacement);	break;
		case 0x20:	printf("%08X", (int)Displacement);	break;
		}
	}
	if (isImmediate)
	{
		switch (immSize)
		{
			case 0x08:	printf("%02X", (int)immOperand);	break;
			case 0x10:	printf("%04X", (int)immOperand);	break;
			case 0x20:	printf("%08X", (int)immOperand);	break;
			case 0x30:	
			{
				if (isOperandPrefix)
				{
					printf("%04X", immOperand);
					printf("%04X", immSegment);
				}
				else
				{
					printf("%08X", immOperand);
					printf("%04X", immSegment);
				}
			}
			break;	
		}
	}
	printf("\n");
}


void CDisasmLibrary::FinishInstruction(void)
{
	if (dbit)						// Swap operands due to D-Bit in Opcode changing direction
	{
		DWORD temp = 0;
		temp = Operands[1];
		Operands[0] = Operands[1];
		Operands[1] = temp;
	}
}
