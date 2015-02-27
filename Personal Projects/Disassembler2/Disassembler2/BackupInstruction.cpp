#include "StdAfx.h"
#include "Instruction.h"


CInstruction::CInstruction(CString Instruction)
{
	InstructionPrefix="";	// Instruction Prefix: F3(Rep/Repe/Repz), F2(Repne/Repnz), F0(Lock);  
	AddressPrefix=false;	// Address-Size: 67(Address-Size Operand);  
	OperandPrefix=false;	// Operand-Size: 66(Operand-Size Override);  
	SegmentPrefix="";		// Segment Override: 2E(CS Override), 36(SS Override), 3E(DS Override), 26(ES Override), 64(FS Override > 386), 65(GS Override > 386)
	Opcode="";				// 0F = Extended (2-byte) opcode
	ExtendedOpcode="";
	BinaryOpcode="";
	dBit=0;
	wBit=0;
	ModRegRM="";
	BinaryModRegRM="";
	SIB="";
	BinarySIB="";
	Displacement="";
	Immediate="";

	if (Instruction.GetLength() >= 2)
		Instruction = ParsePrefixes(Instruction);
	if (Instruction.GetLength() >= 2)
		Instruction = ParseOpcode(Instruction);
	if (Instruction.GetLength() >= 2)
		Instruction = ParseModRegRM(Instruction);
	if (Instruction.GetLength() >= 2)
		Instruction = ParseSIB(Instruction);
	if (Instruction.GetLength() >= 2)
		Instruction = ParseDisplacement(Instruction);
	if (Instruction.GetLength() >= 2)
		Instruction = ParseImmediate(Instruction);

	if (BinaryOpcode != "")	// Opcode Present
	{
		ProcessOpcode();
		if (ModRegRM != "")
		{
			ProcessModRegRM();
		}
	}
	Mod = _T("");
	Reg = _T("");
	RM = _T("");
}


CInstruction::~CInstruction(void)
{
}


CString CInstruction::ParsePrefixes(CString Instruction)
{
	int count=0;
	while (count<4)
	{
		if (Instruction.Left(2) == "F3" || Instruction.Left(2) == "F2" || Instruction.Left(2) == "F0")
		{
			InstructionPrefix=Instruction.Left(2);
			Instruction.Delete(0, 2);
		}
		if (Instruction.Left(2) == "67")
		{
			AddressPrefix=true;
			Instruction.Delete(0, 2);
		}
		if (Instruction.Left(2) == "66")
		{
			OperandPrefix=true;
			Instruction.Delete(0, 2);
		}
		if (Instruction.Left(2) == "2E" || Instruction.Left(2) == "36" || Instruction.Left(2) == "3E" || Instruction.Left(2) == "26" || 
			Instruction.Left(2) == "64" || Instruction.Left(2) == "65")
		{
			SegmentPrefix=Instruction.Left(2);
			Instruction.Delete(0, 2);
		}
		count++;
	}
	return Instruction;
}


CString CInstruction::ParseOpcode(CString Instruction)
{
	Opcode=Instruction.Left(2);
	BinaryOpcode=HexToBinaryString(Opcode);
	Instruction.Delete(0, 2);

	if (Opcode=="0F")
	{
		ExtendedOpcode=Instruction.Left(2);
		BinaryExtendedOpcode=HexToBinaryString(ExtendedOpcode);
		Instruction.Delete(0, 2);

		if (BinaryExtendedOpcode.GetAt(6)=='1')
			dBit=1;
		else
			dBit=0;
		if (BinaryExtendedOpcode.GetAt(7)=='1')
			wBit=1;
		else
			wBit=0;
	}
	else if (Opcode != "0F")
	{
		if (BinaryOpcode.GetAt(6)=='1')
			dBit=1;
		else
			dBit=0;
		if (BinaryOpcode.GetAt(7)=='1')
			wBit=1;
		else
			wBit=0;
	}

	return Instruction;
}


CString CInstruction::ParseModRegRM(CString Instruction)
{
	ModRegRM=Instruction.Left(2);
	BinaryModRegRM=HexToBinaryString(ModRegRM);
	Mod=BinaryModRegRM.Left(2);
	Reg=BinaryModRegRM.Mid(2, 3);
	RM=BinaryModRegRM.Right(3);
	Instruction.Delete(0, 2);
	return Instruction;
}


CString CInstruction::ParseSIB(CString Instruction)
{
	SIB=Instruction.Left(2);
	BinarySIB=HexToBinaryString(SIB);
	Instruction.Delete(0, 2);
	return Instruction;
}


CString CInstruction::ParseDisplacement(CString Instruction)
{
	if (wBit==0)	// Byte Displacement (8bit)
	{
		Displacement=Instruction.Left(2);
		Instruction.Delete(0, 2);
	}
	if (wBit==1)	// Word Displacement (16/32 bit)
	{
		if (AddressPrefix)
		{
			Displacement=Instruction.Left(8);
			Instruction.Delete(0, 8);
		}
		else
		{
			Displacement=Instruction.Left(4);
			Instruction.Delete(0, 4);
		}
	}
	return Instruction;
}


CString CInstruction::ParseImmediate(CString Instruction)
{
	if (wBit==0)	// Byte Immediate (8bit)
	{
		Immediate=Instruction.Left(2);
		Instruction.Delete(0, 2);
	}
	if (wBit==1)	// Word Immediate (16/32 bit)
	{
		if (OperandPrefix)
		{
			Immediate=Instruction.Left(8);
			Instruction.Delete(0, 8);
		}
		else
		{
			Immediate=Instruction.Left(4);
			Instruction.Delete(0, 4);
		}
	}
	return Instruction;
}


CString CInstruction::HexToBinaryString(CString Instruction)
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


// This function will replace the value in a given string (Instruction), at Position, with ReplacementString
CString CInstruction::ReplaceValue(CString Instruction, int Position, CString ReplacementString)
{
	Instruction.Delete(Position, 1);
	Instruction.Insert(Position, ReplacementString);
	return Instruction;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////FINISHED///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CInstruction::ProcessOpcode(void)
{
/*	if(Opcode=="00")	GenInst="ADD";			if(Opcode=="01")	GenInst="ADD";			if(Opcode=="02")	GenInst="ADD";		if(Opcode=="03")	GenInst="ADD";
	if(Opcode=="04")	GenInst="ADD";			if(Opcode=="05")	GenInst="ADD";			if(Opcode=="06")	GenInst="PUSH";		if(Opcode=="07")	GenInst="POP";
	if(Opcode=="08")	GenInst="OR";			if(Opcode=="09")	GenInst="OR";			if(Opcode=="0A")	GenInst="OR";		if(Opcode=="0B")	GenInst="OR";
	if(Opcode=="0C")	GenInst="OR";			if(Opcode=="0D")	GenInst="OR";			if(Opcode=="0E")	GenInst="PUSH";		if(Opcode=="10")	GenInst="ADC";			
	if(Opcode=="11")	GenInst="ADC";			if(Opcode=="12")	GenInst="ADC";			if(Opcode=="13")	GenInst="ADC";		if(Opcode=="14")	GenInst="ADC";			
	if(Opcode=="15")	GenInst="ADC";			if(Opcode=="16")	GenInst="PUSH";			if(Opcode=="17")	GenInst="POP";		if(Opcode=="18")	GenInst="SBB";
	if(Opcode=="19")	GenInst="SBB";			if(Opcode=="1A")	GenInst="SBB";			if(Opcode=="1B")	GenInst="SBB";		if(Opcode=="1C")	GenInst="SBB";	
	if(Opcode=="1D")	GenInst="SBB";			if(Opcode=="1E")	GenInst="PUSH";			if(Opcode=="1F")	GenInst="POP";		if(Opcode=="20")	GenInst="AND";	
	if(Opcode=="21")	GenInst="AND";			if(Opcode=="22")	GenInst="AND";			if(Opcode=="23")	GenInst="AND";		if(Opcode=="24")	GenInst="AND";			
	if(Opcode=="25")	GenInst="AND";			if(Opcode=="27")	GenInst="DAA";			if(Opcode=="28")	GenInst="SUB";		if(Opcode=="29")	GenInst="SUB";
	if(Opcode=="2A")	GenInst="SUB";			if(Opcode=="2B")	GenInst="SUB";			if(Opcode=="2C")	GenInst="SUB";		if(Opcode=="2D")	GenInst="SUB";
	if(Opcode=="2F")	GenInst="DAS";			if(Opcode=="30")	GenInst="XOR";			if(Opcode=="31")	GenInst="XOR";		if(Opcode=="32")	GenInst="XOR";	
	if(Opcode=="33")	GenInst="XOR";			if(Opcode=="34")	GenInst="XOR";			if(Opcode=="35")	GenInst="XOR";		if(Opcode=="37")	GenInst="AAA";
	if(Opcode=="38")	GenInst="CMP";			if(Opcode=="39")	GenInst="SEG";			if(Opcode=="3A")	GenInst="AAS";		if(Opcode=="40")	GenInst="INC";
	if(Opcode=="41")	GenInst="INC";			if(Opcode=="42")	GenInst="INC";			if(Opcode=="43")	GenInst="INC";		if(Opcode=="44")	GenInst="INC";
	if(Opcode=="45")	GenInst="INC";			if(Opcode=="46")	GenInst="INC";			if(Opcode=="47")	GenInst="INC";		if(Opcode=="48")	GenInst="DEC";
	if(Opcode=="49")	GenInst="DEC";			if(Opcode=="4A")	GenInst="DEC";			if(Opcode=="4B")	GenInst="DEC";		if(Opcode=="4C")	GenInst="DEC";	
	if(Opcode=="4D")	GenInst="DEC";			if(Opcode=="4E")	GenInst="DEC";			if(Opcode=="4F")	GenInst="DEC";		if(Opcode=="50")	GenInst="PUSH";	
	if(Opcode=="51")	GenInst="PUSH";			if(Opcode=="52")	GenInst="PUSH";			if(Opcode=="53")	GenInst="PUSH";		if(Opcode=="54")	GenInst="PUSH";	
	if(Opcode=="55")	GenInst="PUSH";			if(Opcode=="56")	GenInst="PUSH";			if(Opcode=="57")	GenInst="PUSH";		if(Opcode=="58")	GenInst="POP";
	if(Opcode=="59")	GenInst="POP";			if(Opcode=="5A")	GenInst="POP";			if(Opcode=="5B")	GenInst="POP";		if(Opcode=="5C")	GenInst="POP";	
	if(Opcode=="5D")	GenInst="POP";			if(Opcode=="5E")	GenInst="POP";			if(Opcode=="5F")	GenInst="POP";		if(Opcode=="60")	GenInst="PUSHA";
	if(Opcode=="61")	GenInst="POPA";			if(Opcode=="62")	GenInst="BOUND";		if(Opcode=="63")	GenInst="ARPL";		if(Opcode=="68")	GenInst="PUSH";	
	if(Opcode=="69")	GenInst="IMUL";			if(Opcode=="6A")	GenInst="PUSH";			if(Opcode=="6B")	GenInst="IMUL";		if(Opcode=="6C")	GenInst="INSB";	
	if(Opcode=="6D")	GenInst="INSW/D";		if(Opcode=="6E")	GenInst="OUTSB";		if(Opcode=="6F")	GenInst="OUTSW/D";	if(Opcode=="70")	GenInst="JO";	
	if(Opcode=="71")	GenInst="JNO";			if(Opcode=="72")	GenInst="JB/JNAE/JC";	if(Opcode=="73")	GenInst="JNB";		if(Opcode=="74")	GenInst="JZ";	
	if(Opcode=="75")	GenInst="JNZ";			if(Opcode=="76")	GenInst="JBE";			if(Opcode=="77")	GenInst="JNBE";		if(Opcode=="78")	GenInst="JS";
	if(Opcode=="79")	GenInst="JNS";			if(Opcode=="7A")	GenInst="JP";			if(Opcode=="7B")	GenInst="JNP";		if(Opcode=="7C")	GenInst="JL";
	if(Opcode=="7D")	GenInst="JNL";			if(Opcode=="7E")	GenInst="JLE";			if(Opcode=="7F")	GenInst="JNLE";		if(Opcode=="80")	GenInst="ADD";
	if(Opcode=="81")	GenInst="ADD";			if(Opcode=="82")	GenInst="ADD";			if(Opcode=="83")	GenInst="ADD";		if(Opcode=="84")	GenInst="TEST";
	if(Opcode=="85")	GenInst="TEST";			if(Opcode=="86")	GenInst="XCHG";			if(Opcode=="87")	GenInst="XCHG";		if(Opcode=="88")	GenInst="MOV";
	if(Opcode=="89")	GenInst="MOV";			if(Opcode=="8A")	GenInst="MOV";			if(Opcode=="8B")	GenInst="MOV";		if(Opcode=="8C")	GenInst="MOV";
	if(Opcode=="8D")	GenInst="LEA";			if(Opcode=="8E")	GenInst="MOV";			if(Opcode=="8F")	GenInst="POP";		if(Opcode=="90")	GenInst="NOP";
	if(Opcode=="91")	GenInst="XCHG";			if(Opcode=="92")	GenInst="XCHG";			if(Opcode=="93")	GenInst="XCHG";		if(Opcode=="94")	GenInst="XCHG";
	if(Opcode=="95")	GenInst="XCHG";			if(Opcode=="96")	GenInst="XCHG";			if(Opcode=="97")	GenInst="XCHG";		if(Opcode=="98")	GenInst="CBW";
	if(Opcode=="99")	GenInst="CWD/CDQ";		if(Opcode=="9A")	GenInst="CALL";			if(Opcode=="9B")	GenInst="WAIT";		if(Opcode=="9C")	GenInst="PUSHF";
	if(Opcode=="9D")	GenInst="POP";			if(Opcode=="9E")	GenInst="SAHF";			if(Opcode=="9F")	GenInst="LAHF";		if(Opcode=="A0")	GenInst="MOV";	
	if(Opcode=="A1")	GenInst="MOV";			if(Opcode=="A2")	GenInst="MOV";			if(Opcode=="A3")	GenInst="MOV";		if(Opcode=="A4")	GenInst="MOVSB";	
	if(Opcode=="A5")	GenInst="MOVSW";		if(Opcode=="A6")	GenInst="CMPSB";		if(Opcode=="A7")	GenInst="CMPSW";	if(Opcode=="A8")	GenInst="TEST";	
	if(Opcode=="A9")	GenInst="TEST";			if(Opcode=="AA")	GenInst="STOSB";		if(Opcode=="AB")	GenInst="STOSW/D";	if(Opcode=="AC")	GenInst="LODSB";
	if(Opcode=="AD")	GenInst="LODSW/D";		if(Opcode=="AE")	GenInst="SCASB";		if(Opcode=="AF")	GenInst="SCASW/D";	if(Opcode=="B0")	GenInst="MOV";		
	if(Opcode=="B1")	GenInst="MOV";			if(Opcode=="B2")	GenInst="MOV";			if(Opcode=="B3")	GenInst="MOV";		if(Opcode=="B4")	GenInst="MOV";	
	if(Opcode=="B5")	GenInst="MOV";			if(Opcode=="B6")	GenInst="MOV";			if(Opcode=="B7")	GenInst="MOV";		if(Opcode=="B8")	GenInst="MOV";
	if(Opcode=="B9")	GenInst="MOV";			if(Opcode=="BA")	GenInst="MOV";			if(Opcode=="BB")	GenInst="MOV";		if(Opcode=="BC")	GenInst="MOV";	
	if(Opcode=="BD")	GenInst="MOV";			if(Opcode=="BE")	GenInst="MOV";			if(Opcode=="BF")	GenInst="MOV";		if(Opcode=="C0")	GenInst="SHIFT";
	if(Opcode=="C1")	GenInst="SHIFT";		if(Opcode=="C2")	GenInst="RET";			if(Opcode=="C3")	GenInst="RET";		if(Opcode=="C4")	GenInst="LES";
	if(Opcode=="C5")	GenInst="LDS";			if(Opcode=="C6")	GenInst="MOV";			if(Opcode=="C7")	GenInst="MOV";		if(Opcode=="C8")	GenInst="ENTER";
	if(Opcode=="C9")	GenInst="LEAVE";		if(Opcode=="CA")	GenInst="RET";			if(Opcode=="CB")	GenInst="RET";		if(Opcode=="CC")	GenInst="INT";
	if(Opcode=="CD")	GenInst="INT";			if(Opcode=="CE")	GenInst="INTO";			if(Opcode=="CF")	GenInst="IRET";		if(Opcode=="D0")	GenInst="SHIFT";
	if(Opcode=="D1")	GenInst="SHIFT";		if(Opcode=="D2")	GenInst="SHIFT";		if(Opcode=="D3")	GenInst="SHIFT";	if(Opcode=="D4")	GenInst="AAM";
	if(Opcode=="D5")	GenInst="AAD";			if(Opcode=="D7")	GenInst="XLAT";			if(Opcode=="D8")	GenInst="ESC";		if(Opcode=="D9")	GenInst="ESC";
	if(Opcode=="DA")	GenInst="ESC";			if(Opcode=="DB")	GenInst="ESC";			if(Opcode=="DC")	GenInst="ESC";		if(Opcode=="DD")	GenInst="ESC";
	if(Opcode=="DE")	GenInst="ESC";			if(Opcode=="DF")	GenInst="ESC";			if(Opcode=="E0")	GenInst="LOOPN";	if(Opcode=="E1")	GenInst="LOOPE";
	if(Opcode=="E2")	GenInst="LOOP";			if(Opcode=="E3")	GenInst="JCXZ/JECXZ";	if(Opcode=="E4")	GenInst="IN";		if(Opcode=="E5")	GenInst="IN";
	if(Opcode=="E6")	GenInst="OUT";			if(Opcode=="E7")	GenInst="OUT";			if(Opcode=="E8")	GenInst="CALL";		if(Opcode=="E9")	GenInst="JMP";
	if(Opcode=="EA")	GenInst="JMP";			if(Opcode=="EB")	GenInst="JMP";			if(Opcode=="EC")	GenInst="IN";		if(Opcode=="ED")	GenInst="IN";
	if(Opcode=="EE")	GenInst="OUT";			if(Opcode=="EF")	GenInst="OUT";			if(Opcode=="F0")	GenInst="LOCK";		if(Opcode=="F2")	GenInst="REPNE";	
	if(Opcode=="F3")	GenInst="REP";			if(Opcode=="F4")	GenInst="HLT";			if(Opcode=="F5")	GenInst="CMC";		if(Opcode=="F6")	GenInst="UNARY";
	if(Opcode=="F7")	GenInst="UNARY";		if(Opcode=="F8")	GenInst="CLC";			if(Opcode=="F9")	GenInst="STC";		if(Opcode=="FA")	GenInst="CLI";
	if(Opcode=="FB")	GenInst="STI";			if(Opcode=="FC")	GenInst="CLD";			if(Opcode=="FD")	GenInst="STD";		if(Opcode=="FE")	GenInst="INC/DEC";	
	if(Opcode=="FF")	GenInst="INC/DEC";

	if (Opcode=="0F")	// TWO-BYTE OPCODES
	{
		if(ExtendedOpcode=="00")	GenInst="Group 6";	if(ExtendedOpcode=="02")	GenInst="LAR";		if(ExtendedOpcode=="03")	GenInst="LSL";
		if(ExtendedOpcode=="06")	GenInst="CLTS";		if(ExtendedOpcode=="08")	GenInst="INVD";		if(ExtendedOpcode=="09")	GenInst="WBINVD";
		if(ExtendedOpcode=="0B")	GenInst="UD2";		if(ExtendedOpcode=="20")	GenInst="MOV";		if(ExtendedOpcode=="21")	GenInst="MOV";
		if(ExtendedOpcode=="22")	GenInst="MOV";		if(ExtendedOpcode=="23")	GenInst="MOV";		if(ExtendedOpcode=="30")	GenInst="WRMSR";
		if(ExtendedOpcode=="31")	GenInst="RDTSC";	if(ExtendedOpcode=="32")	GenInst="RDMSR";	if(ExtendedOpcode=="33")	GenInst="RDPMC";	
		if(ExtendedOpcode=="40")	GenInst="CMOVO";	if(ExtendedOpcode=="41")	GenInst="CMOVNO";	if(ExtendedOpcode=="42")	GenInst="CMOVB";
		if(ExtendedOpcode=="43")	GenInst="CMOVAE";	if(ExtendedOpcode=="44")	GenInst="CMOVE";	if(ExtendedOpcode=="45")	GenInst="CMOVNE";
		if(ExtendedOpcode=="46")	GenInst="CMOVBE";	if(ExtendedOpcode=="47")	GenInst="CMOVA";	if(ExtendedOpcode=="48")	GenInst="CMOVS";
		if(ExtendedOpcode=="49")	GenInst="CMOVNS";	if(ExtendedOpcode=="4A")	GenInst="CMOVP";	if(ExtendedOpcode=="4B")	GenInst="CMOVNP";
		if(ExtendedOpcode=="4C")	GenInst="CMOVL";	if(ExtendedOpcode=="4D")	GenInst="CMOVGE";	if(ExtendedOpcode=="4E")	GenInst="CMOVLE";
		if(ExtendedOpcode=="4F")	GenInst="CMOVG";	if(ExtendedOpcode=="60")	GenInst="PUNPCKLBW";if(ExtendedOpcode=="61")	GenInst="PUNPCKLWD";
		if(ExtendedOpcode=="62")	GenInst="PUNOCKLDQ";if(ExtendedOpcode=="63")	GenInst="PACKUSDW";	if(ExtendedOpcode=="64")	GenInst="PCMPGTB";
		if(ExtendedOpcode=="65")	GenInst="PCMPGTW";	if(ExtendedOpcode=="66")	GenInst="PCMPGTD";	if(ExtendedOpcode=="67")	GenInst="PACKSSWB";
		if(ExtendedOpcode=="68")	GenInst="PUNPCKHBW";if(ExtendedOpcode=="69")	GenInst="PUNPCKHWD";if(ExtendedOpcode=="6A")	GenInst="PUNPCKHDQ";
		if(ExtendedOpcode=="6B")	GenInst="PACKSSDW";	if(ExtendedOpcode=="6E")	GenInst="MOVD";		if(ExtendedOpcode=="6F")	GenInst="MOVQ";
		if(ExtendedOpcode=="71")	GenInst="PSHIMW";	if(ExtendedOpcode=="72")	GenInst="PSHIMD";	if(ExtendedOpcode=="73")	GenInst="PSHIMQ";
		if(ExtendedOpcode=="74")	GenInst="PCMPEQB";	if(ExtendedOpcode=="75")	GenInst="PCMPEQW";	if(ExtendedOpcode=="76")	GenInst="PCMPEQD";
		if(ExtendedOpcode=="77")	GenInst="EMMS";		if(ExtendedOpcode=="7E")	GenInst="MOVD";		if(ExtendedOpcode=="7F")	GenInst="MOVQ";
		if(ExtendedOpcode=="80")	GenInst="JO";		if(ExtendedOpcode=="81")	GenInst="JNO";		if(ExtendedOpcode=="82")	GenInst="JB";
		if(ExtendedOpcode=="83")	GenInst="JNB";		if(ExtendedOpcode=="84")	GenInst="JZ";		if(ExtendedOpcode=="85")	GenInst="JNZ";
		if(ExtendedOpcode=="86")	GenInst="JBE";		if(ExtendedOpcode=="87")	GenInst="JNBE";		if(ExtendedOpcode=="88")	GenInst="JS";
		if(ExtendedOpcode=="89")	GenInst="JNS";		if(ExtendedOpcode=="8A")	GenInst="JP";		if(ExtendedOpcode=="8B")	GenInst="JNP";	
		if(ExtendedOpcode=="8C")	GenInst="JL";		if(ExtendedOpcode=="8D")	GenInst="JNL";		if(ExtendedOpcode=="8E")	GenInst="JLE";
		if(ExtendedOpcode=="8F")	GenInst="JNLE";		if(ExtendedOpcode=="90")	GenInst="SETO";		if(ExtendedOpcode=="91")	GenInst="SETNO";
		if(ExtendedOpcode=="92")	GenInst="SETB";		if(ExtendedOpcode=="93")	GenInst="SETNB";	if(ExtendedOpcode=="94")	GenInst="SETZ";
		if(ExtendedOpcode=="95")	GenInst="SETNZ";	if(ExtendedOpcode=="96")	GenInst="SETBE";	if(ExtendedOpcode=="97")	GenInst="SETNBE";
		if(ExtendedOpcode=="98")	GenInst="SETS";		if(ExtendedOpcode=="99")	GenInst="SETNS";	if(ExtendedOpcode=="9A")	GenInst="SETP";
		if(ExtendedOpcode=="9B")	GenInst="SETNP";	if(ExtendedOpcode=="9C")	GenInst="SETL";		if(ExtendedOpcode=="9D")	GenInst="SETNL";
		if(ExtendedOpcode=="9E")	GenInst="SETLE";	if(ExtendedOpcode=="9F")	GenInst="SETNLE";	if(ExtendedOpcode=="A0")	GenInst="PUSH";
		if(ExtendedOpcode=="A1")	GenInst="POP";		if(ExtendedOpcode=="A2")	GenInst="CPUID";	if(ExtendedOpcode=="A3")	GenInst="BT";
		if(ExtendedOpcode=="A4")	GenInst="SHLD";		if(ExtendedOpcode=="A5")	GenInst="SHLD";		if(ExtendedOpcode=="A8")	GenInst="PUSH";
		if(ExtendedOpcode=="A9")	GenInst="POP";		if(ExtendedOpcode=="AA")	GenInst="RSM";		if(ExtendedOpcode=="AB")	GenInst="BTS";	
		if(ExtendedOpcode=="AC")	GenInst="SHRD";		if(ExtendedOpcode=="AD")	GenInst="SHRD";		if(ExtendedOpcode=="AF")	GenInst="IMUL";
		if(ExtendedOpcode=="B0")	GenInst="CMPXCHG";	if(ExtendedOpcode=="B1")	GenInst="CMPXCHG";	if(ExtendedOpcode=="B2")	GenInst="LSS";
		if(ExtendedOpcode=="B3")	GenInst="BTR";		if(ExtendedOpcode=="B4")	GenInst="LFS";		if(ExtendedOpcode=="B5")	GenInst="LGS";
		if(ExtendedOpcode=="B6")	GenInst="MOVZX";	if(ExtendedOpcode=="B7")	GenInst="MOVZX";	if(ExtendedOpcode=="B9")	GenInst="INVALID";
		if(ExtendedOpcode=="BA")	GenInst="Group 8";	if(ExtendedOpcode=="BB")	GenInst="BTC";		if(ExtendedOpcode=="BC")	GenInst="BSF";
		if(ExtendedOpcode=="BD")	GenInst="BSR";		if(ExtendedOpcode=="BE")	GenInst="MOVSX";	if(ExtendedOpcode=="BF")	GenInst="MOVSX";
		if(ExtendedOpcode=="C0")	GenInst="XADD";		if(ExtendedOpcode=="C1")	GenInst="XADD";		if(ExtendedOpcode=="C7")	GenInst="Group 9";	
		if(ExtendedOpcode=="C8")	GenInst="BSWAP";	if(ExtendedOpcode=="C9")	GenInst="BSWAP";	if(ExtendedOpcode=="CA")	GenInst="BSWAP";
		if(ExtendedOpcode=="CB")	GenInst="BSWAP";	if(ExtendedOpcode=="CC")	GenInst="BSWAP";	if(ExtendedOpcode=="CD")	GenInst="BSWAP";
		if(ExtendedOpcode=="CE")	GenInst="BSWAP";	if(ExtendedOpcode=="CF")	GenInst="BSWAP";	if(ExtendedOpcode=="D1")	GenInst="PSRLW";
		if(ExtendedOpcode=="D2")	GenInst="PSRLD";	if(ExtendedOpcode=="D3")	GenInst="PSRLQ";	if(ExtendedOpcode=="D5")	GenInst="PMULLW";
		if(ExtendedOpcode=="D8")	GenInst="PSUBUSB";	if(ExtendedOpcode=="D9")	GenInst="PSUBUSW";	if(ExtendedOpcode=="DB")	GenInst="PAND";	
		if(ExtendedOpcode=="DC")	GenInst="PADDUSB";	if(ExtendedOpcode=="DD")	GenInst="PADDUSW";	if(ExtendedOpcode=="DF")	GenInst="PANDN";
		if(ExtendedOpcode=="E1")	GenInst="PSRAW";	if(ExtendedOpcode=="E2")	GenInst="PSRAD";	if(ExtendedOpcode=="E5")	GenInst="PMULHW";
		if(ExtendedOpcode=="E8")	GenInst="PSUBSB";	if(ExtendedOpcode=="E9")	GenInst="PSUBSW";	if(ExtendedOpcode=="EB")	GenInst="POR";
		if(ExtendedOpcode=="EC")	GenInst="PADDSB";	if(ExtendedOpcode=="ED")	GenInst="PADDSW";	if(ExtendedOpcode=="EF")	GenInst="PXOR";
		if(ExtendedOpcode=="F1")	GenInst="PSLLW";	if(ExtendedOpcode=="F2")	GenInst="PSLLD";	if(ExtendedOpcode=="F3")	GenInst="PSLLQ";	
		if(ExtendedOpcode=="F5")	GenInst="PMADDWD";	if(ExtendedOpcode=="F8")	GenInst="PSUBB";	if(ExtendedOpcode=="F9")	GenInst="PSUBW";
		if(ExtendedOpcode=="FA")	GenInst="PSUBD";	if(ExtendedOpcode=="FC")	GenInst="PADDB";	if(ExtendedOpcode=="FD")	GenInst="PADDW";
		if(ExtendedOpcode=="FE")	GenInst="PADDD";
	}
	*/
	CString Ops;
	if (Opcode.Left(1)=="0")
	{
		if (Opcode.Right(1)=="0")	//First #:  0
		{
			GenInst="ADD";
			Ops="EbGb";
		}
		if (Opcode.Right(1)=="1")	//First #:  0
		{
			GenInst="ADD";
			Ops="EvGv";
		}
		if (Opcode.Right(1)=="2")	//First #:  0
		{
			GenInst="ADD";
			Ops="GbEb";
		}
		if (Opcode.Right(1)=="3")	//First #:  0
		{
			GenInst="ADD";
			Ops="GvEv";
		}
		if (Opcode.Right(1)=="4")	//First #:  0
		{
			GenInst="ADD";
			Ops="ALIb";
		}
		if (Opcode.Right(1)=="5")	//First #:  0
		{
			GenInst="ADD";
			Ops="eAXIv";
		}
		if (Opcode.Right(1)=="6")	//First #:  0
		{
			GenInst="PUSH";
			Ops="ES";
		}
		if (Opcode.Right(1)=="7")	//First #:  0
		{
			GenInst="POP";
			Ops="ES";
		}
		if (Opcode.Right(1)=="8")	//First #:  0
		{
			GenInst="OR";
			Ops="EbGb";
		}
		if (Opcode.Right(1)=="9")	//First #:  0
		{
			GenInst="OR";
			Ops="EvGv";
		}
		if (Opcode.Right(1)=="A")	//First #:  0
		{
			GenInst="OR";
			Ops="GbEb";
		}
		if (Opcode.Right(1)=="B")	//First #:  0
		{
			GenInst="OR";
			Ops="GvEv";
		}
		if (Opcode.Right(1)=="C")	//First #:  0
		{
			GenInst="OR";
			Ops="ALIb";
		}
		if (Opcode.Right(1)=="D")	//First #:  0
		{
			GenInst="OR";
			Ops="eAXIv";
		}
		if (Opcode.Right(1)=="E")	//First #:  0
		{
			GenInst="PUSH";
			Ops="CS";
		}
		if (Opcode.Right(1)=="F")	//First #:  0
		{
			GenInst="EXTENDED TWO-BYTE OPCODE";
			Ops="ESCAPE";
		}
	}
	if (Opcode.Left(1)=="1")
	{
		if (Opcode.Right(1)=="0")	//First #:  1
		{
			GenInst="ADC";
			Ops="EbGb";
		}
		if (Opcode.Right(1)=="1")	//First #:  1
		{
			GenInst="ADC";
			Ops="EvGv";
		}
		if (Opcode.Right(1)=="2")	//First #:  1
		{
			GenInst="ADC";
			Ops="GbEb";
		}
		if (Opcode.Right(1)=="3")	//First #:  1
		{
			GenInst="ADC";
			Ops="GvEv";
		}
		if (Opcode.Right(1)=="4")	//First #:  1
		{
			GenInst="ADC";
			Ops="ALIb";
		}
		if (Opcode.Right(1)=="5")	//First #:  1
		{
			GenInst="ADC";
			Ops="eAXIv";
		}
		if (Opcode.Right(1)=="6")	//First #:  1
		{
			GenInst="PUSH";
			Ops="SS";
		}
		if (Opcode.Right(1)=="7")	//First #:  1
		{
			GenInst="POP";
			Ops="SS";
		}
		if (Opcode.Right(1)=="8")	//First #:  1
		{
			GenInst="SBB";
			Ops="EbGb";
		}
		if (Opcode.Right(1)=="9")	//First #:  1
		{
			GenInst="SBB";
			Ops="EvGv";
		}
		if (Opcode.Right(1)=="A")	//First #:  1
		{
			GenInst="SBB";
			Ops="GbEb";
		}
		if (Opcode.Right(1)=="B")	//First #:  1
		{
			GenInst="SBB";
			Ops="GvEv";
		}
		if (Opcode.Right(1)=="C")	//First #:  1
		{
			GenInst="SBB";
			Ops="ALIb";
		}
		if (Opcode.Right(1)=="D")	//First #:  1
		{
			GenInst="SBB";
			Ops="eAXIv";
		}
		if (Opcode.Right(1)=="E")	//First #:  1
		{
			GenInst="PUSH";
			Ops="DS";
		}
		if (Opcode.Right(1)=="F")	//First #:  1
		{
			GenInst="POP";
			Ops="DS";
		}
	}
	if (Opcode.Left(1)=="2")
	{
		if (Opcode.Right(1)=="0")	//First #:  2
		{
			GenInst="AND";
			Ops="EbGb";
		}
		if (Opcode.Right(1)=="1")	//First #:  2
		{
			GenInst="AND";
			Ops="EvGv";
		}
		if (Opcode.Right(1)=="2")	//First #:  2
		{
			GenInst="AND";
			Ops="GbEb";
		}
		if (Opcode.Right(1)=="3")	//First #:  2
		{
			GenInst="AND";
			Ops="GvEv";
		}
		if (Opcode.Right(1)=="4")	//First #:  2
		{
			GenInst="AND";
			Ops="ALIb";
		}
		if (Opcode.Right(1)=="5")	//First #:  2
		{
			GenInst="AND";
			Ops="eAXIv";
		}
		if (Opcode.Right(1)=="6")	//First #:  2
		{
			GenInst="SEG";
			Ops="ES";
		}
		if (Opcode.Right(1)=="7")	//First #:  2
		{
			GenInst="DAA";
			Ops="ES";
		}
		if (Opcode.Right(1)=="8")	//First #:  2
		{
			GenInst="SUB";
			Ops="EbGb";
		}
		if (Opcode.Right(1)=="9")	//First #:  2
		{
			GenInst="SUB";
			Ops="EvGv";
		}
		if (Opcode.Right(1)=="A")	//First #:  2
		{
			GenInst="SUB";
			Ops="GbEb";
		}
		if (Opcode.Right(1)=="B")	//First #:  2
		{
			GenInst="SUB";
			Ops="GvEv";
		}
		if (Opcode.Right(1)=="C")	//First #:  2
		{
			GenInst="SUB";
			Ops="ALIb";
		}
		if (Opcode.Right(1)=="D")	//First #:  2
		{
			GenInst="SUB";
			Ops="eAXIv";
		}
		if (Opcode.Right(1)=="E")	//First #:  2
		{
			GenInst="SEG";
			Ops="CS";
		}
		if (Opcode.Right(1)=="F")	//First #:  2
		{
			GenInst="DAS";
			Ops="";
		}
	}
	if (Opcode.Left(1)=="3")
	{
		if (Opcode.Right(1)=="0")	//First #:  3
		{
			GenInst="XOR";
			Ops="EbGb";
		}
		if (Opcode.Right(1)=="1")	//First #:  3
		{
			GenInst="XOR";
			Ops="EvGv";
		}
		if (Opcode.Right(1)=="2")	//First #:  3
		{
			GenInst="XOR";
			Ops="GbEb";
		}
		if (Opcode.Right(1)=="3")	//First #:  3
		{
			GenInst="XOR";
			Ops="GvEv";
		}
		if (Opcode.Right(1)=="4")	//First #:  3
		{
			GenInst="XOR";
			Ops="ALIb";
		}
		if (Opcode.Right(1)=="5")	//First #:  3
		{
			GenInst="XOR";
			Ops="eAXIv";
		}
		if (Opcode.Right(1)=="6")	//First #:  3
		{
			GenInst="SEG";
			Ops="SS";
		}
		if (Opcode.Right(1)=="7")	//First #:  3
		{
			GenInst="AAA";
			Ops="";
		}
		if (Opcode.Right(1)=="8")	//First #:  3
		{
			GenInst="CMP";
			Ops="EbGb";
		}
		if (Opcode.Right(1)=="9")	//First #:  3
		{
			GenInst="CMP";
			Ops="EvGv";
		}
		if (Opcode.Right(1)=="A")	//First #:  3
		{
			GenInst="CMP";
			Ops="GbEb";
		}
		if (Opcode.Right(1)=="B")	//First #:  3
		{
			GenInst="CMP";
			Ops="GvEv";
		}
		if (Opcode.Right(1)=="C")	//First #:  3
		{
			GenInst="CMP";
			Ops="ALIb";
		}
		if (Opcode.Right(1)=="D")	//First #:  3
		{
			GenInst="CMP";
			Ops="eAXIv";
		}
		if (Opcode.Right(1)=="E")	//First #:  3
		{
			GenInst="SEG";
			Ops="DS";
		}
		if (Opcode.Right(1)=="F")	//First #:  3
		{
			GenInst="AAS";
			Ops="";
		}
	}
	if (Opcode.Left(1)=="4")
	{
		if (Opcode.Right(1)=="0")	//First #:  4
		{
			GenInst="INC";
			Ops="eAX";
		}
		if (Opcode.Right(1)=="1")	//First #:  4
		{
			GenInst="INC";
			Ops="eCX";
		}
		if (Opcode.Right(1)=="2")	//First #:  4
		{
			GenInst="INC";
			Ops="eDX";
		}
		if (Opcode.Right(1)=="3")	//First #:  4
		{
			GenInst="INC";
			Ops="eBX";
		}
		if (Opcode.Right(1)=="4")	//First #:  4
		{
			GenInst="INC";
			Ops="eSP";
		}
		if (Opcode.Right(1)=="5")	//First #:  4
		{
			GenInst="INC";
			Ops="eBP";
		}
		if (Opcode.Right(1)=="6")	//First #:  4
		{
			GenInst="INC";
			Ops="eSI";
		}
		if (Opcode.Right(1)=="7")	//First #:  4
		{
			GenInst="INC";
			Ops="eDI";
		}
		if (Opcode.Right(1)=="8")	//First #:  4
		{
			GenInst="DEC";
			Ops="eAX";
		}
		if (Opcode.Right(1)=="9")	//First #:  4
		{
			GenInst="DEC";
			Ops="eCX";
		}
		if (Opcode.Right(1)=="A")	//First #:  4
		{
			GenInst="DEC";
			Ops="eDX";
		}
		if (Opcode.Right(1)=="B")	//First #:  4
		{
			GenInst="DEC";
			Ops="eBX";
		}
		if (Opcode.Right(1)=="C")	//First #:  4
		{
			GenInst="DEC";
			Ops="eSP";
		}
		if (Opcode.Right(1)=="D")	//First #:  4
		{
			GenInst="DEC";
			Ops="eBP";
		}
		if (Opcode.Right(1)=="E")	//First #:  4
		{
			GenInst="DEC";
			Ops="eSI";
		}
		if (Opcode.Right(1)=="F")	//First #:  4
		{
			GenInst="DEC";
			Ops="eDI";
		}
	}
	if (Opcode.Left(1)=="5")
	{
		if (Opcode.Right(1)=="0")	//First #:  5
		{
			GenInst="PUSH";
			Ops="eAX";
		}
		if (Opcode.Right(1)=="1")	//First #:  5
		{
			GenInst="PUSH";
			Ops="eCX";
		}
		if (Opcode.Right(1)=="2")	//First #:  5
		{
			GenInst="PUSH";
			Ops="eDX";
		}
		if (Opcode.Right(1)=="3")	//First #:  5
		{
			GenInst="PUSH";
			Ops="eBX";
		}
		if (Opcode.Right(1)=="4")	//First #:  5
		{
			GenInst="PUSH";
			Ops="eSP";
		}
		if (Opcode.Right(1)=="5")	//First #:  5
		{
			GenInst="PUSH";
			Ops="eBP";
		}
		if (Opcode.Right(1)=="6")	//First #:  5
		{
			GenInst="PUSH";
			Ops="eSI";
		}
		if (Opcode.Right(1)=="7")	//First #:  5
		{
			GenInst="PUSH";
			Ops="eDI";
		}
		if (Opcode.Right(1)=="8")	//First #:  5
		{
			GenInst="POP";
			Ops="eAX";
		}
		if (Opcode.Right(1)=="9")	//First #:  5
		{
			GenInst="POP";
			Ops="eCX";
		}
		if (Opcode.Right(1)=="A")	//First #:  5
		{
			GenInst="POP";
			Ops="eDX";
		}
		if (Opcode.Right(1)=="B")	//First #:  5
		{
			GenInst="POP";
			Ops="eBX";
		}
		if (Opcode.Right(1)=="C")	//First #:  5
		{
			GenInst="POP";
			Ops="eSP";
		}
		if (Opcode.Right(1)=="D")	//First #:  5
		{
			GenInst="POP";
			Ops="eBP";
		}
		if (Opcode.Right(1)=="E")	//First #:  5
		{
			GenInst="POP";
			Ops="eSI";
		}
		if (Opcode.Right(1)=="F")	//First #:  5
		{
			GenInst="POP";
			Ops="eDI";
		}
	}
	if (Opcode.Left(1)=="6")
	{
		if (Opcode.Right(1)=="0")	//First #:  6
		{
			GenInst="PUSHA/PUSHAD";
			Ops="";
		}
		if (Opcode.Right(1)=="1")	//First #:  6
		{
			GenInst="POPA/POPAD";
			Ops="";
		}
		if (Opcode.Right(1)=="2")	//First #:  6
		{
			GenInst="BOUND";
			Ops="GvMa";
		}
		if (Opcode.Right(1)=="3")	//First #:  6
		{
			GenInst="ARPL";
			Ops="EwGw";
		}
		if (Opcode.Right(1)=="4")	//First #:  6
		{
			GenInst="SEG";
			Ops="FS";
		}
		if (Opcode.Right(1)=="5")	//First #:  6
		{
			GenInst="SEG";
			Ops="GS";
		}
		if (Opcode.Right(1)=="6")	//First #:  6
		{
			GenInst="SWITCH OPERAND-SIZE";
			Ops="";
		}
		if (Opcode.Right(1)=="7")	//First #:  6
		{
			GenInst="SWITCH ADDRESS-SIZE";
			Ops="";
		}
		if (Opcode.Right(1)=="8")	//First #:  6
		{
			GenInst="PUSH";
			Ops="Iv";
		}
		if (Opcode.Right(1)=="9")	//First #:  6
		{
			GenInst="IMUL";
			Ops="GvEvIv";
		}
		if (Opcode.Right(1)=="A")	//First #:  6
		{
			GenInst="PUSH";
			Ops="Ib";
		}
		if (Opcode.Right(1)=="B")	//First #:  6
		{
			GenInst="IMUL";
			Ops="GvEvIb";
		}
		if (Opcode.Right(1)=="C")	//First #:  6
		{
			GenInst="INSB";
			Ops="YbDX";
		}
		if (Opcode.Right(1)=="D")	//First #:  6
		{
			GenInst="INSW/D";
			Ops="YvDX";
		}
		if (Opcode.Right(1)=="E")	//First #:  6
		{
			GenInst="OUTSB";
			Ops="DXXb";
		}
		if (Opcode.Right(1)=="F")	//First #:  6
		{
			GenInst="OUTSW/D";
			Ops="DXXv";
		}
	}
	if (Opcode.Left(1)=="7")
	{
		if (Opcode.Right(1)=="0")	//First #:  7
		{
			GenInst="JO";
			Ops="";
		}
		if (Opcode.Right(1)=="1")	//First #:  7
		{
			GenInst="JNO";
			Ops="";
		}
		if (Opcode.Right(1)=="2")	//First #:  7
		{
			GenInst="JB/JNAE/JC";
			Ops="";
		}
		if (Opcode.Right(1)=="3")	//First #:  7
		{
			GenInst="JNB/JAE/JNC";
			Ops="";
		}
		if (Opcode.Right(1)=="4")	//First #:  7
		{
			GenInst="JZ";
			Ops="";
		}
		if (Opcode.Right(1)=="5")	//First #:  7
		{
			GenInst="JNZ";
			Ops="";
		}
		if (Opcode.Right(1)=="6")	//First #:  7
		{
			GenInst="JBE";
			Ops="";
		}
		if (Opcode.Right(1)=="7")	//First #:  7
		{
			GenInst="JA";
			Ops="";
		}
		if (Opcode.Right(1)=="8")	//First #:  7
		{
			GenInst="JS";
			Ops="";
		}
		if (Opcode.Right(1)=="9")	//First #:  7
		{
			GenInst="JNS";
			Ops="";
		}
		if (Opcode.Right(1)=="A")	//First #:  7
		{
			GenInst="JPE";
			Ops="";
		}
		if (Opcode.Right(1)=="B")	//First #:  7
		{
			GenInst="JPO";
			Ops="";
		}
		if (Opcode.Right(1)=="C")	//First #:  7
		{
			GenInst="JL";
			Ops="";
		}
		if (Opcode.Right(1)=="D")	//First #:  7
		{
			GenInst="JGE";
			Ops="";
		}
		if (Opcode.Right(1)=="E")	//First #:  7
		{
			GenInst="JLE";
			Ops="";
		}
		if (Opcode.Right(1)=="F")	//First #:  7
		{
			GenInst="JG";
			Ops="";
		}
	}
	if (Opcode.Left(1)=="8")
	{
		if (Opcode.Right(1)=="0")	//First #:  8
		{
			Ops="EbIb";
			goto group1;
		}
		if (Opcode.Right(1)=="1")	//First #:  8
		{
			Ops="EvIv";
			goto group1;
		}
		if (Opcode.Right(1)=="2")	//First #:  8
		{
			Ops="EbIb";
			goto group1;
		}
		if (Opcode.Right(1)=="3")	//First #:  8
		{
			Ops="EvIb";
			goto group1;
		}
		if (Opcode.Right(1)=="4")	//First #:  8
		{
			GenInst="TEST";
			Ops="GbEb";
		}
		if (Opcode.Right(1)=="5")	//First #:  8
		{
			GenInst="TEST";
			Ops="GvEv";
		}
		if (Opcode.Right(1)=="6")	//First #:  8
		{
			GenInst="XCHG";
			Ops="GbEb";
		}
		if (Opcode.Right(1)=="7")	//First #:  8
		{
			GenInst="XCHG";
			Ops="GvEv";
		}
		if (Opcode.Right(1)=="8")	//First #:  8
		{
			GenInst="MOV";
			Ops="EbGb";
		}
		if (Opcode.Right(1)=="9")	//First #:  8
		{
			GenInst="MOV";
			Ops="EvGv";
		}
		if (Opcode.Right(1)=="A")	//First #:  8
		{
			GenInst="MOV";
			Ops="GbEb";
		}
		if (Opcode.Right(1)=="B")	//First #:  8
		{
			GenInst="MOV";
			Ops="GvEv";
		}
		if (Opcode.Right(1)=="C")	//First #:  8
		{
			GenInst="MOV";
			Ops="EwSw";
		}
		if (Opcode.Right(1)=="D")	//First #:  8
		{
			GenInst="LEA";
			Ops="GvM";
		}
		if (Opcode.Right(1)=="E")	//First #:  8
		{
			GenInst="MOV";
			Ops="SwEw";
		}
		if (Opcode.Right(1)=="F")	//First #:  8
		{
			if (Reg=="000")
			{
				GenInst="POP";
				Ops="Ev";
			}
		}
	}
	if (Opcode.Left(1)=="9")
	{
		if (Opcode.Right(1)=="0")	//First #:  9
		{
			GenInst="NOP";
			Ops="";
		}
		if (Opcode.Right(1)=="1")	//First #:  9
		{
			GenInst="XCHG";
			Ops="eCX";
		}
		if (Opcode.Right(1)=="2")	//First #:  9
		{
			GenInst="XCHG";
			Ops="eDX";
		}
		if (Opcode.Right(1)=="3")	//First #:  9
		{
			GenInst="XCHG";
			Ops="eBX";
		}
		if (Opcode.Right(1)=="4")	//First #:  9
		{
			GenInst="XCHG";
			Ops="eSP";
		}
		if (Opcode.Right(1)=="5")	//First #:  9
		{
			GenInst="XCHG";
			Ops="eBP";
		}
		if (Opcode.Right(1)=="6")	//First #:  9
		{
			GenInst="XCHG";
			Ops="eSI";
		}
		if (Opcode.Right(1)=="7")	//First #:  9
		{
			GenInst="XCHG";
			Ops="eDI";
		}
		if (Opcode.Right(1)=="8")	//First #:  9
		{
			GenInst="CBW";
			Ops="";
		}
		if (Opcode.Right(1)=="9")	//First #:  9
		{
			GenInst="CWD/CDQ";
			Ops="";
		}
		if (Opcode.Right(1)=="A")	//First #:  9
		{
			GenInst="CALL";
			Ops="Ap";
		}
		if (Opcode.Right(1)=="B")	//First #:  9
		{
			GenInst="WAIT";
			Ops="";
		}
		if (Opcode.Right(1)=="C")	//First #:  9
		{
			GenInst="PUSHF";
			Ops="Fv";
		}
		if (Opcode.Right(1)=="D")	//First #:  9
		{
			GenInst="POPF";
			Ops="Fv";
		}
		if (Opcode.Right(1)=="E")	//First #:  9
		{
			GenInst="SAHF";
			Ops="";
		}
		if (Opcode.Right(1)=="F")	//First #:  9
		{
			GenInst="LAHF";
			Ops="";
		}
	}
	if (Opcode.Left(1)=="A")
	{
		if (Opcode.Right(1)=="0")	//First #:  A
		{
			GenInst="MOV";
			Ops="ALOb";
		}
		if (Opcode.Right(1)=="1")	//First #:  A
		{
			GenInst="MOV";
			Ops="eAXOv";
		}
		if (Opcode.Right(1)=="2")	//First #:  A
		{
			GenInst="MOV";
			Ops="ObAL";
		}
		if (Opcode.Right(1)=="3")	//First #:  A
		{
			GenInst="MOV";
			Ops="OveAX";
		}
		if (Opcode.Right(1)=="4")	//First #:  A
		{
			GenInst="MOVSB";
			Ops="YbXb";
		}
		if (Opcode.Right(1)=="5")	//First #:  A
		{
			GenInst="MOVSW";
			Ops="YvXv";
		}
		if (Opcode.Right(1)=="6")	//First #:  A
		{
			GenInst="CMPSB";
			Ops="XbYb";
		}
		if (Opcode.Right(1)=="7")	//First #:  A
		{
			GenInst="CMPSW";
			Ops="XvYv";
		}
		if (Opcode.Right(1)=="8")	//First #:  A
		{
			GenInst="TEST";
			Ops="ALIb";
		}
		if (Opcode.Right(1)=="9")	//First #:  A
		{
			GenInst="TEST";
			Ops="eAXIv";
		}
		if (Opcode.Right(1)=="A")	//First #:  A
		{
			GenInst="STOSB";
			Ops="YbAL";
		}
		if (Opcode.Right(1)=="B")	//First #:  A
		{
			GenInst="STOSW/D";
			Ops="YveAX";
		}
		if (Opcode.Right(1)=="C")	//First #:  A
		{
			GenInst="LODSB";
			Ops="ALXb";
		}
		if (Opcode.Right(1)=="D")	//First #:  A
		{
			GenInst="LODSW/D";
			Ops="eAXXv";
		}
		if (Opcode.Right(1)=="E")	//First #:  A
		{
			GenInst="SCASB";
			Ops="ALYb";
		}
		if (Opcode.Right(1)=="F")	//First #:  A
		{
			GenInst="SCASW/D";
			Ops="eAXYv";
		}
	}
	if (Opcode.Left(1)=="B")
	{
		if (Opcode.Right(1)=="0")	//First #:  B
		{
			GenInst="MOV";
			Ops="AL";
		}
		if (Opcode.Right(1)=="1")	//First #:  B
		{
			GenInst="MOV";
			Ops="CL";
		}
		if (Opcode.Right(1)=="2")	//First #:  B
		{
			GenInst="MOV";
			Ops="DL";
		}
		if (Opcode.Right(1)=="3")	//First #:  B
		{
			GenInst="MOV";
			Ops="BL";
		}
		if (Opcode.Right(1)=="4")	//First #:  B
		{
			GenInst="MOV";
			Ops="AH";
		}
		if (Opcode.Right(1)=="5")	//First #:  B
		{
			GenInst="MOV";
			Ops="CH";
		}
		if (Opcode.Right(1)=="6")	//First #:  B
		{
			GenInst="MOV";
			Ops="DH";
		}
		if (Opcode.Right(1)=="7")	//First #:  B
		{
			GenInst="MOV";
			Ops="BH";
		}
		if (Opcode.Right(1)=="8")	//First #:  B
		{
			GenInst="MOV";
			Ops="eAX";
		}
		if (Opcode.Right(1)=="9")	//First #:  B
		{
			GenInst="MOV";
			Ops="eCX";
		}
		if (Opcode.Right(1)=="A")	//First #:  B
		{
			GenInst="MOV";
			Ops="eDX";
		}
		if (Opcode.Right(1)=="B")	//First #:  B
		{
			GenInst="MOV";
			Ops="eBX";
		}
		if (Opcode.Right(1)=="C")	//First #:  B
		{
			GenInst="MOV";
			Ops="eSP";
		}
		if (Opcode.Right(1)=="D")	//First #:  B
		{
			GenInst="MOV";
			Ops="eBP";
		}
		if (Opcode.Right(1)=="E")	//First #:  B
		{
			GenInst="MOV";
			Ops="eSI";
		}
		if (Opcode.Right(1)=="F")	//First #:  B
		{
			GenInst="MOV";
			Ops="eDI";
		}
	}
	if (Opcode.Left(1)=="C")
	{
		if (Opcode.Right(1)=="0")	//First #:  C
		{
			Ops="EbIb";
			goto group2;
		}
		if (Opcode.Right(1)=="1")	//First #:  C
		{
			Ops="Ev1";
			goto group2;
		}
		if (Opcode.Right(1)=="2")	//First #:  C
		{
			GenInst="RET";
			Ops="Iw";
		}
		if (Opcode.Right(1)=="3")	//First #:  C
		{
			GenInst="RET";
			Ops="";
		}
		if (Opcode.Right(1)=="4")	//First #:  C
		{
			GenInst="LES";
			Ops="GvMp";
		}
		if (Opcode.Right(1)=="5")	//First #:  C
		{
			GenInst="LDS";
			Ops="GvMp";
		}
		if (Opcode.Right(1)=="6")	//First #:  C
		{
			if (Reg=="000")
			{
				GenInst="MOV";
				Ops="EbIb";
			}
		}
		if (Opcode.Right(1)=="7")	//First #:  C
		{
			if (Reg=="000")
			{
				GenInst="MOV";
				Ops="EbIb";
			}
		}
		if (Opcode.Right(1)=="8")	//First #:  C
		{
			GenInst="ENTER";
			Ops="IwIb";
		}
		if (Opcode.Right(1)=="9")	//First #:  C
		{
			GenInst="LEAVE";
			Ops="";
		}
		if (Opcode.Right(1)=="A")	//First #:  C
		{
			GenInst="RET";
			Ops="Iw";
		}
		if (Opcode.Right(1)=="B")	//First #:  C
		{
			GenInst="RET";
			Ops="";
		}
		if (Opcode.Right(1)=="C")	//First #:  C
		{
			GenInst="INT 3";
			Ops="";
		}
		if (Opcode.Right(1)=="D")	//First #:  C
		{
			GenInst="INT";
			Ops="Ib";
		}
		if (Opcode.Right(1)=="E")	//First #:  C
		{
			GenInst="INTO";
			Ops="";
		}
		if (Opcode.Right(1)=="F")	//First #:  C
		{
			GenInst="IRET";
			Ops="";
		}
	}
	if (Opcode.Left(1)=="D")
	{
		if (Opcode.Right(1)=="0")	//First #:  D
		{
			Ops="Eb1";
			goto group2;
		}
		if (Opcode.Right(1)=="1")	//First #:  D
		{
			Ops="Ev1";
			goto group2;
		}
		if (Opcode.Right(1)=="2")	//First #:  D
		{
			Ops="EbCL";
			goto group2;
		}
		if (Opcode.Right(1)=="3")	//First #:  D
		{
			Ops="EvCL";
			goto group2;
		}
		if (Opcode.Right(1)=="4")	//First #:  D
		{
			GenInst="AAM";
			Ops="";
		}
		if (Opcode.Right(1)=="5")	//First #:  D
		{
			GenInst="AAD";
			Ops="";
		}
		if (Opcode.Right(1)=="7")	//First #:  D
		{
			GenInst="XLAT";
			Ops="";
		}
		if (Opcode.Right(1)=="8")	//First #:  D
		{
			GenInst="ESC";
			Ops="";
		}
		if (Opcode.Right(1)=="9")	//First #:  D
		{
			GenInst="ESC";
			Ops="";
		}
		if (Opcode.Right(1)=="A")	//First #:  D
		{
			GenInst="ESC";
			Ops="";
		}
		if (Opcode.Right(1)=="B")	//First #:  D
		{
			GenInst="ESC";
			Ops="";
		}
		if (Opcode.Right(1)=="C")	//First #:  D
		{
			GenInst="ESC";
			Ops="";
		}
		if (Opcode.Right(1)=="D")	//First #:  D
		{
			GenInst="ESC";
			Ops="";
		}
		if (Opcode.Right(1)=="E")	//First #:  D
		{
			GenInst="ESC";
			Ops="";
		}
		if (Opcode.Right(1)=="F")	//First #:  D
		{
			GenInst="ESC";
			Ops="";
		}
	}
	if (Opcode.Left(1)=="E")
	{
		if (Opcode.Right(1)=="0")	//First #:  E
		{
			GenInst="LOOPNZ";
			Ops="Jb";
		}
		if (Opcode.Right(1)=="1")	//First #:  E
		{
			GenInst="LOOPZ";
			Ops="Jb";
		}
		if (Opcode.Right(1)=="2")	//First #:  E
		{
			GenInst="LOOP";
			Ops="Jb";
		}
		if (Opcode.Right(1)=="3")	//First #:  E
		{
			GenInst="JCXZ/JECXZ";
			Ops="Jb";
		}
		if (Opcode.Right(1)=="4")	//First #:  E
		{
			GenInst="IN";
			Ops="ALIb";
		}
		if (Opcode.Right(1)=="5")	//First #:  E
		{
			GenInst="IN";
			Ops="eAXIb";
		}
		if (Opcode.Right(1)=="6")	//First #:  E
		{
			GenInst="OUT";
			Ops="IbAL";
		}
		if (Opcode.Right(1)=="7")	//First #:  E
		{
			GenInst="OUT";
			Ops="IbeAX";
		}
		if (Opcode.Right(1)=="8")	//First #:  E
		{
			GenInst="CALL";
			Ops="Jv";
		}
		if (Opcode.Right(1)=="9")	//First #:  E
		{
			GenInst="JMP";
			Ops="Jv";
		}
		if (Opcode.Right(1)=="A")	//First #:  E
		{
			GenInst="JMP";
			Ops="Ap";
		}
		if (Opcode.Right(1)=="B")	//First #:  E
		{
			GenInst="JMP";
			Ops="Jb";
		}
		if (Opcode.Right(1)=="C")	//First #:  E
		{
			GenInst="IN";
			Ops="ALDX";
		}
		if (Opcode.Right(1)=="D")	//First #:  E
		{
			GenInst="IN";
			Ops="eAXDX";
		}
		if (Opcode.Right(1)=="E")	//First #:  E
		{
			GenInst="OUT";
			Ops="DXAL";
		}
		if (Opcode.Right(1)=="F")	//First #:  E
		{
			GenInst="OUT";
			Ops="DXeAX";
		}
	}
	if (Opcode.Left(1)=="F")
	{
		if (Opcode.Right(1)=="0")	//First #:  F
		{
			GenInst="LOCK";
			Ops="";
		}
		if (Opcode.Right(1)=="2")	//First #:  F
		{
			GenInst="REPNZ";
			Ops="";
		}
		if (Opcode.Right(1)=="3")	//First #:  F
		{
			GenInst="REPZ";
			Ops="";
		}
		if (Opcode.Right(1)=="4")	//First #:  F
		{
			GenInst="HLT";
			Ops="";
		}
		if (Opcode.Right(1)=="5")	//First #:  F
		{
			GenInst="CMC";
			Ops="";
		}
		if (Opcode.Right(1)=="6")	//First #:  F
		{
			Ops="Eb";
			goto group3;
		}
		if (Opcode.Right(1)=="7")	//First #:  F
		{
			Ops="Ev";
			goto group3;
		}
		if (Opcode.Right(1)=="8")	//First #:  F
		{
			GenInst="CLC";
			Ops="";
		}
		if (Opcode.Right(1)=="9")	//First #:  F
		{
			GenInst="STC";
			Ops="";
		}
		if (Opcode.Right(1)=="A")	//First #:  F
		{
			GenInst="CLI";
			Ops="";
		}
		if (Opcode.Right(1)=="B")	//First #:  F
		{
			GenInst="STI";
			Ops="";
		}
		if (Opcode.Right(1)=="C")	//First #:  F
		{
			GenInst="CLD";
			Ops="";
		}
		if (Opcode.Right(1)=="D")	//First #:  F
		{
			GenInst="STD";
			Ops="";
		}
		if (Opcode.Right(1)=="E")	//First #:  F
		{
			goto group4;
		}
		if (Opcode.Right(1)=="F")	//First #:  F
		{
			goto group5;
		}
	}
	goto End;

////////////////////////////////////////////////////////////////////
//////////////////////Extended One-Byte Opcode Groups///////////////
////////////////////////////////////////////////////////////////////
group1:
	if (Reg=="000")
	{
		GenInst="ADD";
		Ops="";
	}
	if (Reg=="001")
	{
		GenInst="OR";
		Ops="";
	}
	if (Reg=="010")
	{
		GenInst="ADC";
		Ops="";
	}
	if (Reg=="011")
	{
		GenInst="SBB";
		Ops="";
	}
	if (Reg=="100")
	{
		GenInst="AND";
		Ops="";
	}
	if (Reg=="101")
	{
		GenInst="SUB";
		Ops="";
	}
	if (Reg=="110")
	{
		GenInst="XOR";
		Ops="";
	}
	if (Reg=="111")
	{
		GenInst="CMP";
		Ops="";
	}
	goto End;
group2:
	if (Reg=="000")
	{
		GenInst="ROL";
		Ops="";
	}
	if (Reg=="001")
	{
		GenInst="ROR";
		Ops="";
	}
	if (Reg=="010")
	{
		GenInst="RCL";
		Ops="";
	}
	if (Reg=="011")
	{
		GenInst="RCR";
		Ops="";
	}
	if (Reg=="100")
	{
		GenInst="SHL/SAL";
		Ops="";
	}
	if (Reg=="101")
	{
		GenInst="SHR";
		Ops="";
	}
	if (Reg=="111")
	{
		GenInst="SAR";
		Ops="";
	}
	goto End;
group3:
	if (Reg=="000")
	{
		GenInst="TEST";
		Ops="Ib/Iv";
	}
	if (Reg=="010")
	{
		GenInst="NOT";
		Ops="";
	}
	if (Reg=="011")
	{
		GenInst="NEG";
		Ops="";
	}
	if (Reg=="100")
	{
		GenInst="MUL";
		Ops="AL/eAX";
	}
	if (Reg=="101")
	{
		GenInst="IMUL";
		Ops="AL/eAX";
	}
	if (Reg=="110")
	{
		GenInst="DIV";
		Ops="AL/eAX";
	}
	if (Reg=="111")
	{
		GenInst="IDIV";
		Ops="AL/eAX";
	}
	goto End;
group4:
	if (Reg=="000")
	{
		GenInst="INC";
		Ops="Eb";
	}
	if (Reg=="001")
	{
		GenInst="DEC";
		Ops="Eb";
	}
	goto End;
group5:
	if (Reg=="000")
	{
		GenInst="INC";
		Ops="Ev";
	}
	if (Reg=="001")
	{
		GenInst="DEC";
		Ops="Ev";
	}
	if (Reg=="010")
	{
		GenInst="CALL";
		Ops="Ev";
	}
	if (Reg=="011")
	{
		GenInst="CALL";
		Ops="Mp";
	}
	if (Reg=="100")
	{
		GenInst="JMP";
		Ops="Ev";
	}
	if (Reg=="101")
	{
		GenInst="JMP";
		Ops="Mp";
	}
	if (Reg=="110")
	{
		GenInst="PUSH";
		Ops="Ev";
	}
	goto End;
/*group6:
	if (Reg=="000")
	{
		GenInst="SLDT";
		Ops="Ew";
	}
	if (Reg=="001")
	{
		GenInst="STR";
		Ops="Ew";
	}
	if (Reg=="010")
	{
		GenInst="LLDT";
		Ops="Ew";
	}
	if (Reg=="011")
	{
		GenInst="LTR";
		Ops="Ew";
	}
	if (Reg=="100")
	{
		GenInst="VERR";
		Ops="Ew";
	}
	if (Reg=="101")
	{
		GenInst="VERW";
		Ops="Ew";
	}
	goto End;
group7:
	if (Reg=="000")
	{
		GenInst="SGDT";
		Ops="Ms";
	}
	if (Reg=="001")
	{
		GenInst="SIDT";
		Ops="Ms";
	}
	if (Reg=="010")
	{
		GenInst="LGDT";
		Ops="Ms";
	}
	if (Reg=="011")
	{
		GenInst="LIDT";
		Ops="Ms";
	}
	if (Reg=="100")
	{
		GenInst="SMSW";
		Ops="Ew";
	}
	if (Reg=="110")
	{
		GenInst="LMSW";
		Ops="Ew";
	}
	if (Reg=="111")
	{
		GenInst="INVLPG";
		Ops="";
	}
	goto End;
group8:
	if (Reg=="100")
	{
		GenInst="BT";
		Ops="";
	}
	if (Reg=="101")
	{
		GenInst="BTS";
		Ops="";
	}
	if (Reg=="110")
	{
		GenInst="BTR";
		Ops="";
	}
	if (Reg=="111")
	{
		GenInst="BTC";
		Ops="";
	}
	goto End;
group9:
	if (Reg=="001")
	{
		GenInst="CMPXCH";
		Ops="8BMq";
	}
	goto End;
groupA:
	if (Reg=="010")
	{
		GenInst="PSRLD/PSRLW/PSRLQ";
		Ops="PqIb";
	}
	if (Reg=="100")
	{
		GenInst="PSRAD/PSRAW";
		Ops="PqIb";
	}
	if (Reg=="110")
	{
		GenInst="PSLLD/PSLLW/PSLLQ";
		Ops="PqIb";
	}
	goto End;*/
End:;
	CString Op1, Op2, Op3;
	if (Ops.Left(2) != "eA")
	{
		Op1=Ops.Left(2);
		Ops.Delete(0, 2);
	}
	else
	{
		Op1=Ops.Left(3);
		Ops.Delete(0, 3);
	}
	if (Ops.GetLength() >= 2)
	{
		if (Ops.Left(2) != "eA")
		{
			Op2=Ops.Left(2);
			Ops.Delete(0, 2);
		}
		else
		{
			Op2=Ops.Left(3);
			Ops.Delete(0, 3);
		}
	}
	if (Ops.GetLength() >= 2)
	{
		if (Ops.Left(2) != "eA")
		{
			Op3=Ops.Left(2);
			Ops.Delete(0, 2);
		}
		else
		{
			Op3=Ops.Left(3);
			Ops.Delete(0, 3);
		}
	}
	if (Op1=="aP")
	{
	}
	if (Op1=="Ap")
	{
	}
	if (Op1=="Eb")
	{
	}
	if (Op1=="Ev")
	{
	}
	if (Op1=="Ew")
	{
	}
	if (Op1=="Fv")
	{
	}
	if (Op1=="Gb")
	{
	}
	if (Op1=="Gv")
	{
	}
	if (Op1=="Gw")
	{
	}
	if (Op1=="Ib")
	{
	}
	if (Op1=="Iv")
	{
	}
	if (Op1=="Iw")
	{
	}
	if (Op1=="Jb")
	{
	}
	if (Op1=="Ma")
	{
	}
	if (Op1=="Ov")
	{
	}
	if (Op1=="Ob")
	{
	}
	if (Op1=="Ow")
	{
	}
	if (Op1=="Sw")
	{
	}
	if (Op1=="Xb")
	{
	}
	if (Op1=="Xv")
	{
	}
	if (Op1=="Yb")
	{
	}
	if (Op1=="Yv")
	{
	}
	if (Op1=="AL")
	{
	}
	if (Op1=="CL")
	{
	}
	if (Op1=="DL")
	{
	}
	if (Op1=="BL")
	{
	}
	if (Op1=="AH")
	{
	}
	if (Op1=="CH")
	{
	}
	if (Op1=="DH")
	{
	}
	if (Op1=="BH")
	{
	}
	if (Op1=="AX")
	{
	}
	if (Op1=="CX")
	{
	}
	if (Op1=="DX")
	{
	}
	if (Op1=="BX")
	{
	}
	if (Op1=="eAX")
	{
	}
	if (Op1=="eBX")
	{
	}
	if (Op1=="eCX")
	{
	}
	if (Op1=="eDX")
	{
	}
	if (Op1=="eBP")
	{
	}
	if (Op1=="eSP")
	{
	}
	if (Op1=="eSI")
	{
	}
	if (Op1=="eDI")
	{
	}
	if (Op2=="aP")
	{
	}
	if (Op2=="Ap")
	{
	}
	if (Op2=="Eb")
	{
	}
	if (Op2=="Ev")
	{
	}
	if (Op2=="Ew")
	{
	}
	if (Op2=="Fv")
	{
	}
	if (Op2=="Gb")
	{
	}
	if (Op2=="Gv")
	{
	}
	if (Op2=="Gw")
	{
	}
	if (Op2=="Ib")
	{
	}
	if (Op2=="Iv")
	{
	}
	if (Op2=="Iw")
	{
	}
	if (Op2=="Jb")
	{
	}
	if (Op2=="Ma")
	{
	}
	if (Op2=="Ov")
	{
	}
	if (Op2=="Ob")
	{
	}
	if (Op2=="Ow")
	{
	}
	if (Op2=="Sw")
	{
	}
	if (Op2=="Xb")
	{
	}
	if (Op2=="Xv")
	{
	}
	if (Op2=="Yb")
	{
	}
	if (Op2=="Yv")
	{
	}
	if (Op2=="AL")
	{
	}
	if (Op2=="CL")
	{
	}
	if (Op2=="DL")
	{
	}
	if (Op2=="BL")
	{
	}
	if (Op2=="AH")
	{
	}
	if (Op2=="CH")
	{
	}
	if (Op2=="DH")
	{
	}
	if (Op2=="BH")
	{
	}
	if (Op2=="AX")
	{
	}
	if (Op2=="CX")
	{
	}
	if (Op2=="DX")
	{
	}
	if (Op2=="BX")
	{
	}
	if (Op2=="eAX")
	{
	}
	if (Op2=="eBX")
	{
	}
	if (Op2=="eCX")
	{
	}
	if (Op2=="eDX")
	{
	}
	if (Op2=="eBP")
	{
	}
	if (Op2=="eSP")
	{
	}
	if (Op2=="eSI")
	{
	}
	if (Op2=="eDI")
	{
	}
	if (Op3=="aP")
	{
	}
	if (Op3=="Ap")
	{
	}
	if (Op3=="Eb")
	{
	}
	if (Op3=="Ev")
	{
	}
	if (Op3=="Ew")
	{
	}
	if (Op3=="Fv")
	{
	}
	if (Op3=="Gb")
	{
	}
	if (Op3=="Gv")
	{
	}
	if (Op3=="Gw")
	{
	}
	if (Op3=="Ib")
	{
	}
	if (Op3=="Iv")
	{
	}
	if (Op3=="Iw")
	{
	}
	if (Op3=="Jb")
	{
	}
	if (Op3=="Ma")
	{
	}
	if (Op3=="Ov")
	{
	}
	if (Op3=="Ob")
	{
	}
	if (Op3=="Ow")
	{
	}
	if (Op3=="Sw")
	{
	}
	if (Op3=="Xb")
	{
	}
	if (Op3=="Xv")
	{
	}
	if (Op3=="Yb")
	{
	}
	if (Op3=="Yv")
	{
	}
	if (Op3=="AL")
	{
	}
	if (Op3=="CL")
	{
	}
	if (Op3=="DL")
	{
	}
	if (Op3=="BL")
	{
	}
	if (Op3=="AH")
	{
	}
	if (Op3=="CH")
	{
	}
	if (Op3=="DH")
	{
	}
	if (Op3=="BH")
	{
	}
	if (Op3=="AX")
	{
	}
	if (Op3=="CX")
	{
	}
	if (Op3=="DX")
	{
	}
	if (Op3=="BX")
	{
	}
	if (Op3=="eAX")
	{
	}
	if (Op3=="eBX")
	{
	}
	if (Op3=="eCX")
	{
	}
	if (Op3=="eDX")
	{
	}
	if (Op3=="eBP")
	{
	}
	if (Op3=="eSP")
	{
	}
	if (Op3=="eSI")
	{
	}
	if (Op3=="eDI")
	{
	}
}


// //Processes Mod Reg R/M byte and determines addressing, registers, immediate and displacement sizes, as well as direction
void CInstruction::ProcessModRegRM(void)
{
	if (Mod=="00")			//Memory Operand w/ NO DISPLACEMENT
	{
		if (RM=="110")
		{
			isByteDisplacement=false;
			isWordDisplacement=true;
		}
		else
		{
			isByteDisplacement=false;
			isWordDisplacement=false;
		}
		isMemoryOperand=true;
		isRegisterOperand=false;
	}
	else if (Mod=="01")		//Memory Operand w/ 8-Bit Displacement
	{
		isByteDisplacement=true;
		isWordDisplacement=false;
		isMemoryOperand=true;
		isRegisterOperand=false;
	}
	else if (Mod=="10")		//Memory Operand w/ 16-Bit Displacement
	{
		isByteDisplacement=false;
		isWordDisplacement=true;
		isMemoryOperand=true;
		isRegisterOperand=false;
	}
	else if (Mod=="11")		//Register Operand
	{
		isByteDisplacement=false;
		isWordDisplacement=false;
		isMemoryOperand=false;
		isRegisterOperand=true;
	}
	if (isMemoryOperand)
	{
		
	}
	if (isRegisterOperand)
	{
	}
}
