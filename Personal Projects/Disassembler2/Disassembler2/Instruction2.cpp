#include "StdAfx.h"
#include "Instruction.h"
#include "HexOps.h"


CInstruction::CInstruction(void)
{

}


void CInstruction::InitialProcessing(CString Instructions)
{
	int InstructionCount = 0;
	EndOfInstructions=false;
	Instruction[0]=Instructions;
	Instruction[1]=Instructions;

	while (!EndOfInstructions)
	{
		Instruction[2].Empty();
		for (int i=0; i<6; i++)		Opcode[i].Empty();		// Zero out opcodes and binary opcodes
		ParsePrefixes();
		ParseOpcode();

		if (Opcode[0] != "")	ProcessInstruction();
		else	EndOfInstructions=true;
	
		if (!EndOfInstructions)	// Full Instruction Present
		{
			FinalInstruction[InstructionCount] = Instruction[0].Left(Instruction[0].GetLength() - Instruction[1].GetLength()) + CString(": ") + Instruction[2];
			Instruction[0] = Instruction[1];
			Instruction[2].Empty();
			InstructionCount++;
		}
	}
}


CInstruction::~CInstruction(void)
{
}


void CInstruction::ParsePrefixes()
{
	int count=0;
	while (count<4)
	{
		if (Instruction[1].Left(2) == "F3" || Instruction[1].Left(2) == "F2" || Instruction[1].Left(2) == "F0")	// Lock Prefixes
		{
			Prefixes[0]=Instruction[1].Left(2);
			Instruction[1].Delete(0, 2);
		}
		if (Instruction[1].Left(2) == "67")	// Address-Size Override Prefixes (16-bit vs. 32-bit)
		{
			Prefixes[1]="67";
			Instruction[1].Delete(0, 2);
		}
		if (Instruction[1].Left(2) == "66")	// Operand-Size Override Prefixes (16-bit vs. 32-bit)
		{
			Prefixes[2]="66";
			Instruction[1].Delete(0, 2);
		}
		if (Instruction[1].Left(2) == "2E" || Instruction[1].Left(2) == "36" || Instruction[1].Left(2) == "3E" || Instruction[1].Left(2) == "26" || 
			Instruction[1].Left(2) == "64" || Instruction[1].Left(2) == "65")			// Segment Override Prefixes
		{
			Prefixes[3]=Instruction[1].Left(2);
			Instruction[1].Delete(0, 2);
		}
		count++;
	}
}


void CInstruction::ParseOpcode()
{
	if (Instruction[1].GetLength() >= 2)
	{
		Opcode[0]=Instruction[1].Left(2);
		Opcode[1]=CHexOps::HexToBinaryString(Opcode[0]);
		Instruction[1].Delete(0, 2);
	
		SpecialBits[0] = Opcode[1].GetAt(6);		// D-Bit
		SpecialBits[1] = Opcode[1].GetAt(7);		// W-Bit
		SpecialBits[2] = Opcode[1].GetAt(6);		// S-Bit
	
		if (Opcode[0]=="0F")					// Two-Byte Opcodes
		{
			if (Instruction[1].GetLength() >= 2)
			{
				Opcode[2]=Instruction[1].Left(2);
				Opcode[3]=CHexOps::HexToBinaryString(Opcode[2]);
				Instruction[1].Delete(0, 2);

				SpecialBits[0] = Opcode[3].GetAt(6);		// D-Bit
				SpecialBits[1] = Opcode[3].GetAt(7);		// W-Bit
				SpecialBits[2] = Opcode[3].GetAt(6);		// S-Bit
			}
			if (Opcode[2]=="")
				EndOfInstructions=true;
		}
		if (Opcode[0]=="")
			EndOfInstructions=true;
	}
}


void CInstruction::ProcessInstruction()
{
	int InstructionCounter=0;
	int i=0;

	while (i<6)
	{
		ModRMSIB[i].Empty();
		i++;
	}
	DetermineGenInstructionAndOperandTypes();				// Determine Basic Instruction and Operand Types
	for (int OperandNum=0; OperandNum < 3; OperandNum++)
	{
		DetermineOperand(OperandNum);
		if (Operands[OperandNum] != "")
			if (OperandNum > 0)								// At least 2nd Operand, so...
				Instruction[2].Append(CString(", "));		//	 insert a comma prior to inserting Operand into Instruction string
			Instruction[2].Append(Operands[OperandNum]);	// Insert Operand into Instruction string
	}
}

void CInstruction::DetermineGenInstructionAndOperandTypes()
{
	Operands[0].Empty();
	Operands[1].Empty();
	Operands[2].Empty();

	if (Opcode[0]=="00")	
	{
		Instruction[2] += CString(" ADD ");Operands[0]="Eb";Operands[1]="Gb";
	}
	if (Opcode[0]=="01")	
	{
		Instruction[2] += CString(" ADD ");Operands[0]="Ev";Operands[1]="Gv";
	}
	if (Opcode[0]=="02")	
	{
		Instruction[2] += CString(" ADD ");Operands[0]="Gb";Operands[1]="Eb";
	}
	if (Opcode[0]=="03")	
	{
		Instruction[2] += CString(" ADD ");Operands[0]="Gv";Operands[1]="Ev";
	}
	if (Opcode[0]=="04")	
	{
		Instruction[2] += CString(" ADD ");Operands[0]="AL";Operands[1]="Ib";
	}
	if (Opcode[0]=="05")	
	{
		Instruction[2] += CString(" ADD ");Operands[0]="eAX";Operands[1]="Iv";
	}
	if (Opcode[0]=="06")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="ES";
	}
	if (Opcode[0]=="07")	
	{
		Instruction[2] += CString(" POP ");Operands[0]="ES";
	}
	if (Opcode[0]=="08")	
	{
		Instruction[2] += CString(" OR ");Operands[0]="Eb";Operands[1]="Gb";
	}
	if (Opcode[0]=="09")	
	{
		Instruction[2] += CString(" OR ");Operands[0]="Ev";Operands[1]="Gv";
	}
	if (Opcode[0]=="0A")	
	{
		Instruction[2] += CString(" OR ");Operands[0]="Gb";Operands[1]="Eb";
	}
	if (Opcode[0]=="0B")	
	{
		Instruction[2] += CString(" OR ");Operands[0]="Gv";Operands[1]="Ev";
	}
	if (Opcode[0]=="0C")	
	{
		Instruction[2] += CString(" OR ");Operands[0]="AL";Operands[1]="Ib";
	}
	if (Opcode[0]=="0D")	
	{
		Instruction[2] += CString(" OR ");Operands[0]="eAX";Operands[1]="Iv";
	}
	if (Opcode[0]=="0E")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="CS";
	}
	if (Opcode[0]=="0F")	
	{
		DetermineTwoByteOpcodes();
	}
	if (Opcode[0]=="10")	
	{
		Instruction[2] += CString(" ADC ");Operands[0]="Eb";Operands[1]="Gb";
	}
	if (Opcode[0]=="11")	
	{
		Instruction[2] += CString(" ADC ");Operands[0]="Ev";Operands[1]="Gv";
	}
	if (Opcode[0]=="12")	
	{
		Instruction[2] += CString(" ADC ");Operands[0]="Gb";Operands[1]="Eb";
	}
	if (Opcode[0]=="13")	
	{
		Instruction[2] += CString(" ADC ");Operands[0]="Gv";Operands[1]="Ev";
	}
	if (Opcode[0]=="14")	
	{
		Instruction[2] += CString(" ADC ");Operands[0]="AL";Operands[1]="Ib";
	}
	if (Opcode[0]=="15")	
	{
		Instruction[2] += CString(" ADC ");Operands[0]="eAX";Operands[1]="Iv";
	}
	if (Opcode[0]=="16")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="SS";
	}
	if (Opcode[0]=="17")	
	{
		Instruction[2] += CString(" POP ");Operands[0]="SS";
	}
	if (Opcode[0]=="18")	
	{
		Instruction[2] += CString(" SBB ");Operands[0]="Eb";Operands[1]="Gb";
	}
	if (Opcode[0]=="19")	
	{
		Instruction[2] += CString(" SBB ");Operands[0]="Ev";Operands[1]="Gv";
	}
	if (Opcode[0]=="1A")	
	{
		Instruction[2] += CString(" SBB ");Operands[0]="Gb";Operands[1]="Eb";
	}
	if (Opcode[0]=="1B")	
	{
		Instruction[2] += CString(" SBB ");Operands[0]="Gv";Operands[1]="Ev";
	}
	if (Opcode[0]=="1C")	
	{
		Instruction[2] += CString(" SBB ");Operands[0]="AL";Operands[1]="Ib";
	}
	if (Opcode[0]=="1D")	
	{
		Instruction[2] += CString(" SBB ");Operands[0]="eAX";Operands[1]="Iv";
	}
	if (Opcode[0]=="1E")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="DS";
	}
	if (Opcode[0]=="1F")	
	{
		Instruction[2] += CString(" POP ");Operands[0]="DS";
	}
	if (Opcode[0]=="20")	
	{
		Instruction[2] += CString(" AND ");Operands[0]="Eb";Operands[1]="Gb";
	}
	if (Opcode[0]=="21")	
	{
		Instruction[2] += CString(" AND ");Operands[0]="Ev";Operands[1]="Gv";
	}
	if (Opcode[0]=="22")	
	{
		Instruction[2] += CString(" AND ");Operands[0]="Gb";Operands[1]="Eb";
	}
	if (Opcode[0]=="23")	
	{
		Instruction[2] += CString(" AND ");Operands[0]="Gv";Operands[1]="Ev";
	}
	if (Opcode[0]=="24")	
	{
		Instruction[2] += CString(" AND ");Operands[0]="AL";Operands[1]="Ib";
	}
	if (Opcode[0]=="25")	
	{
		Instruction[2] += CString(" AND ");Operands[0]="eAX";Operands[1]="Iv";
	}
	if (Opcode[0]=="26")	
	{
		Instruction[2] += CString(" SEG ");Operands[0]="ES";
	}
	if (Opcode[0]=="27")	
	{
		Instruction[2] += CString(" DAA ");Operands[0]="ES";
	}
	if (Opcode[0]=="28")	
	{
		Instruction[2] += CString(" SUB ");Operands[0]="Eb";Operands[1]="Gb";
	}
	if (Opcode[0]=="29")	
	{
		Instruction[2] += CString(" SUB ");Operands[0]="Ev";Operands[1]="Gv";
	}
	if (Opcode[0]=="2A")	
	{
		Instruction[2] += CString(" SUB ");Operands[0]="Gb";Operands[1]="Eb";
	}
	if (Opcode[0]=="2B")	
	{
		Instruction[2] += CString(" SUB ");Operands[0]="Gv";Operands[1]="Ev";
	}
	if (Opcode[0]=="2C")	
	{
		Instruction[2] += CString(" SUB ");Operands[0]="AL";Operands[1]="Ib";
	}
	if (Opcode[0]=="2D")	
	{
		Instruction[2] += CString(" SUB ");Operands[0]="eAX";Operands[1]="Iv";
	}
	if (Opcode[0]=="2E")	
	{
		Instruction[2] += CString(" SEG ");Operands[0]="CS";
	}
	if (Opcode[0]=="2F")	
	{
		Instruction[2] += CString(" DAS ");
	}
	if (Opcode[0]=="30")	
	{
		Instruction[2] += CString(" XOR ");Operands[0]="Eb";Operands[1]="Gb";
	}
	if (Opcode[0]=="31")	
	{
		Instruction[2] += CString(" XOR ");Operands[0]="Ev";Operands[1]="Gv";
	}
	if (Opcode[0]=="32")	
	{
		Instruction[2] += CString(" XOR ");Operands[0]="Gb";Operands[1]="Eb";
	}
	if (Opcode[0]=="33")	
	{
		Instruction[2] += CString(" XOR ");Operands[0]="Gv";Operands[1]="Ev";
	}
	if (Opcode[0]=="34")	
	{
		Instruction[2] += CString(" XOR ");Operands[0]="AL";Operands[1]="Ib";
	}
	if (Opcode[0]=="35")	
	{
		Instruction[2] += CString(" XOR ");Operands[0]="eAX";Operands[1]="Iv";
	}
	if (Opcode[0]=="36")	
	{
		Instruction[2] += CString(" SEG ");Operands[0]="SS";
	}
	if (Opcode[0]=="37")	
	{
		Instruction[2] += CString(" AAA ");
	}
	if (Opcode[0]=="38")	
	{
		Instruction[2] += CString(" CMP ");Operands[0]="Eb";Operands[1]="Gb";
	}
	if (Opcode[0]=="39")	
	{
		Instruction[2] += CString(" CMP ");Operands[0]="Ev";Operands[1]="Gv";
	}
	if (Opcode[0]=="3A")	
	{
		Instruction[2] += CString(" CMP ");Operands[0]="Gb";Operands[1]="Eb";
	}
	if (Opcode[0]=="3B")	
	{
		Instruction[2] += CString(" CMP ");Operands[0]="Gv";Operands[1]="Ev";
	}
	if (Opcode[0]=="3C")	
	{
		Instruction[2] += CString(" CMP ");Operands[0]="AL";Operands[1]="Ib";
	}
	if (Opcode[0]=="3D")	
	{
		Instruction[2] += CString(" CMP ");Operands[0]="eAX";Operands[1]="Iv";
	}
	if (Opcode[0]=="3E")	
	{
		Instruction[2] += CString(" SEG ");Operands[0]="DS";
	}
	if (Opcode[0]=="3F")	
	{
		Instruction[2] += CString(" AAS ");
	}
	if (Opcode[0]=="40")	
	{
		Instruction[2] += CString(" INC ");Operands[0]="eAX";
	}
	if (Opcode[0]=="41")	
	{
		Instruction[2] += CString(" INC ");Operands[0]="eCX";
	}
	if (Opcode[0]=="42")	
	{
		Instruction[2] += CString(" INC ");Operands[0]="eDX";
	}
	if (Opcode[0]=="43")	
	{
		Instruction[2] += CString(" INC ");Operands[0]="eBX";
	}
	if (Opcode[0]=="44")	
	{
		Instruction[2] += CString(" INC ");Operands[0]="eSP";
	}
	if (Opcode[0]=="45")	
	{
		Instruction[2] += CString(" INC ");Operands[0]="eBP";
	}
	if (Opcode[0]=="46")	
	{
		Instruction[2] += CString(" INC ");Operands[0]="eSI";
	}
	if (Opcode[0]=="47")	
	{
		Instruction[2] += CString(" INC ");Operands[0]="eDI";
	}
	if (Opcode[0]=="48")	
	{
		Instruction[2] += CString(" DEC ");Operands[0]="eAX";
	}
	if (Opcode[0]=="49")	
	{
		Instruction[2] += CString(" DEC ");Operands[0]="eCX";
	}
	if (Opcode[0]=="4A")	
	{
		Instruction[2] += CString(" DEC ");Operands[0]="eDX";
	}
	if (Opcode[0]=="4B")	
	{
		Instruction[2] += CString(" DEC ");Operands[0]="eBX";
	}
	if (Opcode[0]=="4C")	
	{
		Instruction[2] += CString(" DEC ");Operands[0]="eSP";
	}
	if (Opcode[0]=="4D")	
	{
		Instruction[2] += CString(" DEC ");Operands[0]="eBP";
	}
	if (Opcode[0]=="4E")	
	{
		Instruction[2] += CString(" DEC ");Operands[0]="eSI";
	}
	if (Opcode[0]=="4F")	
	{
		Instruction[2] += CString(" DEC ");Operands[0]="eDI";
	}
	if (Opcode[0]=="50")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="eAX";
	}
	if (Opcode[0]=="51")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="eCX";
	}
	if (Opcode[0]=="52")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="eDX";
	}
	if (Opcode[0]=="53")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="eBX";
	}
	if (Opcode[0]=="54")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="eSP";
	}
	if (Opcode[0]=="55")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="eBP";
	}
	if (Opcode[0]=="56")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="eSI";
	}
	if (Opcode[0]=="57")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="eDI";
	}
	if (Opcode[0]=="58")	
	{
		Instruction[2] += CString(" POP ");Operands[0]="eAX";
	}
	if (Opcode[0]=="59")	
	{
		Instruction[2] += CString(" POP ");Operands[0]="eCX";
	}
	if (Opcode[0]=="5A")	
	{
		Instruction[2] += CString(" POP ");Operands[0]="eDX";
	}
	if (Opcode[0]=="5B")	
	{
		Instruction[2] += CString(" POP ");Operands[0]="eBX";
	}
	if (Opcode[0]=="5C")	
	{
		Instruction[2] += CString(" POP ");Operands[0]="eSP";
	}
	if (Opcode[0]=="5D")	
	{
		Instruction[2] += CString(" POP ");Operands[0]="eBP";
	}
	if (Opcode[0]=="5E")	
	{
		Instruction[2] += CString(" POP ");Operands[0]="eSI";
	}
	if (Opcode[0]=="5F")	
	{
		Instruction[2] += CString(" POP ");Operands[0]="eDI";
	}
	if (Opcode[0]=="60")	
	{
		Instruction[2] += CString(" PUSHA/PUSHAD ");			
	}
	if (Opcode[0]=="61")	
	{
		Instruction[2] += CString(" POPA/POPAD ");
	}
	if (Opcode[0]=="62")	
	{
		Instruction[2] += CString(" BOUND ");Operands[0]="Gv";Operands[1]="Ma";
	}
	if (Opcode[0]=="63")	
	{
		Instruction[2] += CString(" ARPL ");Operands[0]="Ew";Operands[1]="Gw";
	}
	if (Opcode[0]=="64")	
	{
		Instruction[2] += CString(" SEG ");Operands[0]="FS";
	}
	if (Opcode[0]=="65")	
	{
		Instruction[2] += CString(" SEG ");Operands[0]="GS";
	}
	if (Opcode[0]=="66")	
	{
		Instruction[2] += CString(" SWITCH OPERAND-SIZE ");		
	}
	if (Opcode[0]=="67")	
	{
		Instruction[2] += CString(" SWITCH ADDRESS-SIZE ");
	}
	if (Opcode[0]=="68")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="Iv";
		SpecialBits[2]=SpecialBits[0];
	}
	if (Opcode[0]=="69")	
	{
		Instruction[2] += CString(" IMUL ");Operands[0]="Gv";Operands[1]="Ev ";Operands[2]="Iv";
		SpecialBits[2]=SpecialBits[0];
	}
	if (Opcode[0]=="6A")	
	{
		Instruction[2] += CString(" PUSH ");Operands[0]="Ib";
		SpecialBits[2]=SpecialBits[0];
	}
	if (Opcode[0]=="6B")	
	{
		Instruction[2] += CString(" IMUL ");Operands[0]="Gv";Operands[1]="Ev ";Operands[2]="Ib";
		SpecialBits[2]=SpecialBits[0];
	}
	if (Opcode[0]=="6C")	
	{
		Instruction[2] += CString(" INSB ");Operands[0]="Yb";Operands[1]="DX";
	}
	if (Opcode[0]=="6D")	
	{
		Instruction[2] += CString(" INSW/D ");Operands[0]="Yv";Operands[1]="DX";
	}
	if (Opcode[0]=="6E")	
	{
		Instruction[2] += CString(" OUTSB ");Operands[0]="DX";Operands[1]="Xb";
	}
	if (Opcode[0]=="6F")	
	{
		Instruction[2] += CString(" OUTSW/D ");Operands[0]="DX";Operands[1]="Xv";
	}
	if (Opcode[0]=="70")	
	{
		Instruction[2] += CString(" JO ");		
	}
	if (Opcode[0]=="71")	
	{
		Instruction[2] += CString(" JNO ");
	}
	if (Opcode[0]=="72")	
	{
		Instruction[2] += CString(" JC ");		
	}
	if (Opcode[0]=="73")	
	{
		Instruction[2] += CString(" JNC ");
	}
	if (Opcode[0]=="74")	
	{
		Instruction[2] += CString(" JZ ");		
	}
	if (Opcode[0]=="75")	
	{
		Instruction[2] += CString(" JNZ ");		
	}
	if (Opcode[0]=="76")	
	{
		Instruction[2] += CString(" JBE ");			
	}
	if (Opcode[0]=="77")	
	{
		Instruction[2] += CString(" JA ");		
	}
	if (Opcode[0]=="78")	
	{
		Instruction[2] += CString(" JS ");		
	}
	if (Opcode[0]=="79")	
	{
		Instruction[2] += CString(" JNS ");		
	}
	if (Opcode[0]=="7A")	
	{
		Instruction[2] += CString(" JP ");		
	}
	if (Opcode[0]=="7B")	
	{
		Instruction[2] += CString(" JNP ");			
	}
	if (Opcode[0]=="7C")	
	{
		Instruction[2] += CString(" JL ");		
	}
	if (Opcode[0]=="7D")	
	{
		Instruction[2] += CString(" JGE ");		
	}
	if (Opcode[0]=="7E")	
	{
		Instruction[2] += CString(" JLE ");			
	}
	if (Opcode[0]=="7F")	
	{
		Instruction[2] += CString(" JG ");		
	}
	if (Opcode[0]=="80")	
	{
		Operands[0]="Eb";Operands[1]="Ib";
		SpecialBits[2]=SpecialBits[0];
		ProcessOpcodeGroups(1);
	}
	if (Opcode[0]=="81")	
	{
		Operands[0]="Ev";Operands[1]="Iv";
		SpecialBits[2]=SpecialBits[0];
		ProcessOpcodeGroups(1);
	}
	if (Opcode[0]=="82")	
	{
		Operands[0]="Eb";Operands[1]="Ib";
		SpecialBits[2]=SpecialBits[0];
		ProcessOpcodeGroups(1);
	}
	if (Opcode[0]=="83")	
	{
		Operands[0]="Ev";Operands[1]="Ib";
		SpecialBits[2]=SpecialBits[0];
		ProcessOpcodeGroups(1);
	}
	if (Opcode[0]=="84")	
	{
		Instruction[2] += CString(" TEST ");Operands[0]="Gb";Operands[1]="Eb";
	}
	if (Opcode[0]=="85")	
	{
		Instruction[2] += CString(" TEST ");Operands[0]="Gv";Operands[1]="Ev";
	}
	if (Opcode[0]=="86")	
	{
		Instruction[2] += CString(" XCHG ");Operands[0]="Gb";Operands[1]="Eb";
	}
	if (Opcode[0]=="87")	
	{
		Instruction[2] += CString(" XCHG ");Operands[0]="Gv";Operands[1]="Ev";
	}
	if (Opcode[0]=="88")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="Eb";Operands[1]="Gb";
	}
	if (Opcode[0]=="89")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="Ev";Operands[1]="Gv";
	}
	if (Opcode[0]=="8A")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="Gb";Operands[1]="Eb";
	}
	if (Opcode[0]=="8B")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="Gv";Operands[1]="Ev";
	}
	if (Opcode[0]=="8C")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="Ew";Operands[1]="Sw";
	}
	if (Opcode[0]=="8D")	
	{
		Instruction[2] += CString(" LEA ");Operands[0]="Gv";Operands[1]="M";
	}
	if (Opcode[0]=="8E")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="Sw";Operands[1]="Ew";
	}
	if (Opcode[0]=="8F")	
	{
		ParseModRM();
		if (ModRMSIB[1]=="000")
		{
			Instruction[2] += CString(" POP ");Operands[0]="Ev";
		}
	}
	if (Opcode[0]=="90")	
	{
		Instruction[2] += CString(" NOP ");		
	}
	if (Opcode[0]=="91")	
	{
		Instruction[2] += CString(" XCHG ");Operands[0]="eCX";
	}
	if (Opcode[0]=="92")	
	{
		Instruction[2] += CString(" XCHG ");Operands[0]="eDX";
	}
	if (Opcode[0]=="93")	
	{
		Instruction[2] += CString(" XCHG ");Operands[0]="eBX";
	}
	if (Opcode[0]=="94")	
	{
		Instruction[2] += CString(" XCHG ");Operands[0]="eSP";
	}
	if (Opcode[0]=="95")	
	{
		Instruction[2] += CString(" XCHG ");Operands[0]="eBP";
	}
	if (Opcode[0]=="96")	
	{
		Instruction[2] += CString(" XCHG ");Operands[0]="eSI";
	}
	if (Opcode[0]=="97")	
	{
		Instruction[2] += CString(" XCHG ");Operands[0]="eDI";
	}
	if (Opcode[0]=="98")	
	{
		Instruction[2] += CString(" CBW ");	
	}
	if (Opcode[0]=="99")	
	{
		Instruction[2] += CString(" CWD/CDQ ");
	}
	if (Opcode[0]=="9A")	
	{
		Instruction[2] += CString(" CALL ");Operands[0]="Ap";
	}
	if (Opcode[0]=="9B")	
	{
		Instruction[2] += CString(" WAIT ");		
	}
	if (Opcode[0]=="9C")	
	{
		Instruction[2] += CString(" PUSHF ");Operands[0]="Fv";
	}
	if (Opcode[0]=="9D")	
	{
		Instruction[2] += CString(" POPF ");Operands[0]="Fv";
	}
	if (Opcode[0]=="9E")	
	{
		Instruction[2] += CString(" SAHF ");		
	}
	if (Opcode[0]=="9F")	
	{
		Instruction[2] += CString(" LAHF ");		
	}
	if (Opcode[0]=="A0")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="AL";Operands[1]="Ob";
	}
	if (Opcode[0]=="A1")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="eAX";Operands[1]="Ov";
	}
	if (Opcode[0]=="A2")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="Ob";Operands[1]="AL";
	}
	if (Opcode[0]=="A3")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="Ov";Operands[1]="eAX";
	}
	if (Opcode[0]=="A4")	
	{
		Instruction[2] += CString(" MOVSB ");Operands[0]="Yb";Operands[1]="Xb";
	}
	if (Opcode[0]=="A5")	
	{
		Instruction[2] += CString(" MOVSW ");Operands[0]="Yv";Operands[1]="Xv";
	}
	if (Opcode[0]=="A6")	
	{
		Instruction[2] += CString(" CMPSB ");Operands[0]="Xb";Operands[1]="Yb";
	}
	if (Opcode[0]=="A7")	
	{
		Instruction[2] += CString(" CMPSW ");Operands[0]="Xv";Operands[1]="Yv";
	}
	if (Opcode[0]=="A8")	
	{
		Instruction[2] += CString(" TEST ");Operands[0]="AL";Operands[1]="Ib";
	}
	if (Opcode[0]=="A9")	
	{
		Instruction[2] += CString(" TEST ");Operands[0]="eAX";Operands[1]="Iv";
	}
	if (Opcode[0]=="AA")	
	{
		Instruction[2] += CString(" STOSB ");Operands[0]="Yb";Operands[1]="AL";
	}
	if (Opcode[0]=="AB")	
	{
		Instruction[2] += CString(" STOSW/D ");Operands[0]="Yv";Operands[1]="eAX";
	}
	if (Opcode[0]=="AC")	
	{
		Instruction[2] += CString(" LODSB ");Operands[0]="AL";Operands[1]="Xb";
	}
	if (Opcode[0]=="AD")	
	{
		Instruction[2] += CString(" LODSW/D ");Operands[0]="eAX";Operands[1]="Xv";
	}
	if (Opcode[0]=="AE")	
	{
		Instruction[2] += CString(" SCASB ");Operands[0]="AL";Operands[1]="Yb";
	}
	if (Opcode[0]=="AF")	
	{
		Instruction[2] += CString(" SCASW/D ");Operands[0]="eAX";Operands[1]="Yv";
	}
	if (Opcode[0]=="B0")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="AL";Operands[1]="Ib";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="B1")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="CL";Operands[1]="Ib";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="B2")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="DL";Operands[1]="Ib";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="B3")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="BL";Operands[1]="Ib";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="B4")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="AH";Operands[1]="Ib";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="B5")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="CH";Operands[1]="Ib";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="B6")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="DH";Operands[1]="Ib";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="B7")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="BH";Operands[1]="Ib";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="B8")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="eAX";Operands[1]="Iw";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="B9")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="eCX";Operands[1]="Iw";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="BA")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="eDX";Operands[1]="Iw";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="BB")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="eBX";Operands[1]="Iw";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="BC")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="eSP";Operands[1]="Iw";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="BD")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="eBP";Operands[1]="Iw";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="BE")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="eSI";Operands[1]="Iw";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="BF")	
	{
		Instruction[2] += CString(" MOV ");Operands[0]="eDI";Operands[1]="Iw";
		SpecialBits[1]=Opcode[1].GetAt(4);
	}
	if (Opcode[0]=="C0")	
	{
		Operands[0]="Eb";Operands[1]="Ib";
		ProcessOpcodeGroups(2);
	}
	if (Opcode[0]=="C1")	
	{
		Operands[0]="Ev";Operands[1]="1";
		ProcessOpcodeGroups(2);
	}
	if (Opcode[0]=="C2")	
	{
		Instruction[2] += CString(" RET ");Operands[0]="Iw";
	}
	if (Opcode[0]=="C3")	
	{
		Instruction[2] += CString(" RET ");			
	}
	if (Opcode[0]=="C4")	
	{
		Instruction[2] += CString(" LES ");Operands[0]="Gv";Operands[1]="Mp";
	}
	if (Opcode[0]=="C5")	
	{
		Instruction[2] += CString(" LDS ");Operands[0]="Gv";Operands[1]="Mp";
	}
	if (Opcode[0]=="C6")	
	{
		ParseModRM();
		if (ModRMSIB[1]=="000")
		{
			Instruction[2] += CString(" MOV ");Operands[0]="Eb";Operands[1]="Ib";
		}
	}
	if (Opcode[0]=="C7")	
	{
		ParseModRM();
		if (ModRMSIB[1]=="000")
		{
			Instruction[2] += CString(" MOV ");Operands[0]="Eb";Operands[1]="Ib";
		}
	}
	if (Opcode[0]=="C8")	
	{
		Instruction[2] += CString(" ENTER ");Operands[0]="Iw";Operands[1]="Ib";
	}
	if (Opcode[0]=="C9")	
	{
		Instruction[2] += CString(" LEAVE ");			
	}
	if (Opcode[0]=="CA")	
	{
		Instruction[2] += CString(" RET ");Operands[0]="Iw";
	}
	if (Opcode[0]=="CB")	
	{
		Instruction[2] += CString(" RET ");
	}
	if (Opcode[0]=="CC")	
	{
		Instruction[2] += CString(" INT 3");
	}
	if (Opcode[0]=="CD")	
	{
		Instruction[2] += CString(" INT ");Operands[0]="Ib";
	}
	if (Opcode[0]=="CE")	
	{
		Instruction[2] += CString(" INTO ");			
	}
	if (Opcode[0]=="CF")	
	{
		Instruction[2] += CString(" IRET ");
	}
	if (Opcode[0]=="D0")	
	{
		Operands[0]="Eb";Operands[1]="1";
		ProcessOpcodeGroups(2);
	}
	if (Opcode[0]=="D1")	
	{
		Operands[0]="Ev";Operands[1]="1";
		ProcessOpcodeGroups(2);
	}
	if (Opcode[0]=="D2")	
	{
		Operands[0]="Eb";Operands[1]="CL";
		ProcessOpcodeGroups(2);
	}
	if (Opcode[0]=="D3")	
	{
		Operands[0]="Ev";Operands[1]="CL";
		ProcessOpcodeGroups(2);
	}
	if (Opcode[0]=="D4")	
	{
		Instruction[2] += CString(" AAM ");			
	}
	if (Opcode[0]=="D5")	
	{
		Instruction[2] += CString(" AAD ");			
	}
	if (Opcode[0]=="D7")	
	{
		Instruction[2] += CString(" XLAT ");			
	}
	if (Opcode[0]=="D8")	
	{
		Instruction[2] += CString(" ESC ");			
	}
	if (Opcode[0]=="D9")	
	{
		Instruction[2] += CString(" ESC ");			
	}
	if (Opcode[0]=="DA")	
	{
		Instruction[2] += CString(" ESC ");			
	}
	if (Opcode[0]=="DB")	
	{
		Instruction[2] += CString(" ESC ");			
	}
	if (Opcode[0]=="DC")	
	{
		Instruction[2] += CString(" ESC ");			
	}
	if (Opcode[0]=="DD")	
	{
		Instruction[2] += CString(" ESC ");			
	}
	if (Opcode[0]=="DE")	
	{
		Instruction[2] += CString(" ESC ");			
	}
	if (Opcode[0]=="DF")	
	{
		Instruction[2] += CString(" ESC ");			
	}
	if (Opcode[0]=="E0")	
	{
		Instruction[2] += CString(" LOOPNZ ");Operands[0]="Jv";
	}
	if (Opcode[0]=="E1")	
	{
		Instruction[2] += CString(" LOOPZ ");Operands[0]="Jv";
	}
	if (Opcode[0]=="E2")	
	{
		Instruction[2] += CString(" LOOP ");Operands[0]="Jv";
	}
	if (Opcode[0]=="E3")	
	{
		Instruction[2] += CString(" JCXZ/JECXZ ");Operands[0]="Jv";
	}
	if (Opcode[0]=="E4")	
	{
		Instruction[2] += CString(" IN ");Operands[0]="AL";Operands[1]="Ib";
	}
	if (Opcode[0]=="E5")	
	{
		Instruction[2] += CString(" IN ");Operands[0]="eAX";Operands[1]="Ib";
	}
	if (Opcode[0]=="E6")	
	{
		Instruction[2] += CString(" OUT ");Operands[0]="Ib";Operands[1]="AL";
	}
	if (Opcode[0]=="E7")	
	{
		Instruction[2] += CString(" OUT ");Operands[0]="Ib";Operands[1]="eAX";
	}
	if (Opcode[0]=="E8")	
	{
		Instruction[2] += CString(" CALL ");Operands[0]="Jv";
	}
	if (Opcode[0]=="E9")	
	{
		Instruction[2] += CString(" JMP ");Operands[0]="Jv";
	}
	if (Opcode[0]=="EA")	
	{
		Instruction[2] += CString(" JMP ");Operands[0]="Ap";
	}
	if (Opcode[0]=="EB")	
	{
		Instruction[2] += CString(" JMP ");Operands[0]="Jv";
	}
	if (Opcode[0]=="EC")	
	{
		Instruction[2] += CString(" IN ");Operands[0]="AL";Operands[1]="DX";
	}
	if (Opcode[0]=="ED")	
	{
		Instruction[2] += CString(" IN ");Operands[0]="eAX";Operands[1]="DX";
	}
	if (Opcode[0]=="EE")	
	{
		Instruction[2] += CString(" OUT ");Operands[0]="DX";Operands[1]="AL";
	}
	if (Opcode[0]=="EF")	
	{
		Instruction[2] += CString(" OUT ");Operands[0]="DX";Operands[1]="eAX";
	}
	if (Opcode[0]=="F0")	
	{
		Instruction[2] += CString(" LOCK ");			
	}
	if (Opcode[0]=="F2")	
	{
		Instruction[2] += CString(" REPNZ ");			
	}
	if (Opcode[0]=="F3")	
	{
		Instruction[2] += CString(" REPZ ");			
	}
	if (Opcode[0]=="F4")	
	{
		Instruction[2] += CString(" HLT ");			
	}
	if (Opcode[0]=="F5")	
	{
		Instruction[2] += CString(" CMC ");			
	}
	if (Opcode[0]=="F6")	
	{
		Operands[0]="Eb";
		ProcessOpcodeGroups(3);
	}
	if (Opcode[0]=="F7")	
	{
		Operands[0]="Ev";
		ProcessOpcodeGroups(3);
	}
	if (Opcode[0]=="F8")	
	{
		Instruction[2] += CString(" CLC ");			
	}
	if (Opcode[0]=="F9")	
	{
		Instruction[2] += CString(" STC ");			
	}
	if (Opcode[0]=="FA")	
	{
		Instruction[2] += CString(" CLI ");			
	}
	if (Opcode[0]=="FB")	
	{
		Instruction[2] += CString(" STI ");			
	}
	if (Opcode[0]=="FC")	
	{
		Instruction[2] += CString(" CLD ");			
	}
	if (Opcode[0]=="FD")	
	{
		Instruction[2] += CString(" STD ");			
	}
	if (Opcode[0]=="FE")	
	{
		ProcessOpcodeGroups(4);
	}
	if (Opcode[0]=="FF")	
	{
		ProcessOpcodeGroups(5);
	}
	if (Operands[0] == "" && Operands[1] == "" && Operands[2] == "")
	{
		Instruction[2] += CString(" Undefined ");
	}
}

////////////////////////////////////////////////////////////////////
//////////////////////Extended One-Byte Opcode Groups////////////
////////////////////////////////////////////////////////////////////
void CInstruction::ProcessOpcodeGroups(int groupNumber)
{
	ParseModRM();
	if (groupNumber == 1)
	{
		if (ModRMSIB[1]=="000")
		{
			Instruction[2] += CString(" ADD ");		
		}
		if (ModRMSIB[1]=="001")
		{
			Instruction[2] += CString(" OR ");		
		}
		if (ModRMSIB[1]=="010")
		{
			Instruction[2] += CString(" ADC ");		
		}
		if (ModRMSIB[1]=="011")
		{
			Instruction[2] += CString(" SBB ");		
		}
		if (ModRMSIB[1]=="100")
		{
			Instruction[2] += CString(" AND ");		
		}
		if (ModRMSIB[1]=="101")
		{
			Instruction[2] += CString(" SUB ");		
		}
		if (ModRMSIB[1]=="110")
		{
			Instruction[2] += CString(" XOR ");		
		}
		if (ModRMSIB[1]=="111")
		{
			Instruction[2] += CString(" CMP ");		
		}
		if (Instruction[2].Right(13) == " Undefined ")
		{
			Operands[0]="";Operands[1]="";
		}
	}
	if (groupNumber == 2)
	{
		if (ModRMSIB[1]=="000")
		{
			Instruction[2] += CString(" ROL ");		
		}
		if (ModRMSIB[1]=="001")
		{
			Instruction[2] += CString(" ROR ");		
		}
		if (ModRMSIB[1]=="010")
		{
			Instruction[2] += CString(" RCL ");		
		}
		if (ModRMSIB[1]=="011")
		{
			Instruction[2] += CString(" RCR ");		
		}
		if (ModRMSIB[1]=="100")
		{
			Instruction[2] += CString(" SHL/SAL ");		
		}
		if (ModRMSIB[1]=="101")
		{
			Instruction[2] += CString(" SHR ");		
		}
		if (ModRMSIB[1]=="111")
		{
			Instruction[2] += CString(" SAR ");		
		}
		if (Instruction[2].Right(13) == " Undefined ")
		{
			Operands[0]="";Operands[1]="";
		}
	}
	if (groupNumber == 3)
	{
		if (ModRMSIB[1]=="000")
		{
			Instruction[2] += CString(" TEST ");Operands[0]="Ib/Iv";
		}
		if (ModRMSIB[1]=="010")
		{
			Instruction[2] += CString(" NOT ");		
		}
		if (ModRMSIB[1]=="011")
		{
			Instruction[2] += CString(" NEG ");		
		}
		if (ModRMSIB[1]=="100")
		{
			Instruction[2] += CString(" MUL ");Operands[0]="AL/eAX";
		}
		if (ModRMSIB[1]=="101")
		{
			Instruction[2] += CString(" IMUL ");Operands[0]="AL/eAX";
		}
		if (ModRMSIB[1]=="110")
		{
			Instruction[2] += CString(" DIV ");Operands[0]="AL/eAX";
		}
		if (ModRMSIB[1]=="111")
		{
			Instruction[2] += CString(" IDIV ");Operands[0]="AL/eAX";
		}
		if (Instruction[2].Right(13) == " Undefined ")
		{
			Operands[0]="";Operands[1]="";
		}
	}
	if (groupNumber == 4)
	{
		if (ModRMSIB[1]=="000")
		{
			Instruction[2] += CString(" INC ");Operands[0]="Eb";
		}
		if (ModRMSIB[1]=="001")
		{
			Instruction[2] += CString(" DEC ");Operands[0]="Eb";
		}
		if (Instruction[2].Right(13) == " Undefined ")
		{
			Operands[0]="";Operands[1]="";
		}
	}
	if (groupNumber == 5)
	{
		if (ModRMSIB[1]=="000")
		{
			Instruction[2] += CString(" INC ");Operands[0]="Ev";
		}
		if (ModRMSIB[1]=="001")
		{
			Instruction[2] += CString(" DEC ");Operands[0]="Ev";
		}
		if (ModRMSIB[1]=="010")
		{
			Instruction[2] += CString(" CALL ");Operands[0]="Ev";
		}
		if (ModRMSIB[1]=="011")
		{
			Instruction[2] += CString(" CALL ");Operands[0]="Mp";
		}
		if (ModRMSIB[1]=="100")
		{
			Instruction[2] += CString(" JMP ");Operands[0]="Ev";
		}
		if (ModRMSIB[1]=="101")
		{
			Instruction[2] += CString(" JMP ");Operands[0]="Mp";
		}
		if (ModRMSIB[1]=="110")
		{
			Instruction[2] += CString(" PUSH ");Operands[0]="Ev";
		}
		if (Instruction[2].Right(13) == " Undefined ")
		{
			Operands[0]="";Operands[1]="";
		}
	}
	if (groupNumber == 6)
	{
		if			(ModRMSIB[1]=="000")	Instruction[2] += CString(" SLDT ");
		else if		(ModRMSIB[1]=="001")	Instruction[2] += CString(" STR ");
		else if		(ModRMSIB[1]=="010")	Instruction[2] += CString(" LLDT ");
		else if		(ModRMSIB[1]=="011")	Instruction[2] += CString(" LTR ");
		else if		(ModRMSIB[1]=="100")	Instruction[2] += CString(" VERR ");
		else if		(ModRMSIB[1]=="101")	Instruction[2] += CString(" VERW ");
		else if		(ModRMSIB[1]=="110")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="111")	Instruction[2] += CString(" Undefined ");
		
		if (Instruction[2].Right(11) == " Undefined ")
		{
			Operands[0]="";Operands[1]="";
		}
	}
	if (groupNumber == 7)
	{
		if			(ModRMSIB[1]=="000")	Instruction[2] += CString(" SGDT ");
		else if		(ModRMSIB[1]=="001")	Instruction[2] += CString(" SIDT ");
		else if		(ModRMSIB[1]=="010")	Instruction[2] += CString(" LGDT ");
		else if		(ModRMSIB[1]=="011")	Instruction[2] += CString(" LIDT ");
		else if		(ModRMSIB[1]=="100")	Instruction[2] += CString(" SMSW ");
		else if		(ModRMSIB[1]=="101")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="110")	Instruction[2] += CString(" LMSW ");
		else if		(ModRMSIB[1]=="111")	Instruction[2] += CString(" INVLPG ");

		if (Instruction[2].Right(13) == " Undefined ")
		{
			Operands[0]="";Operands[1]="";
		}
	}
	if (groupNumber == 8)
	{
		if			(ModRMSIB[1]=="000")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="001")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="010")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="011")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="100")	Instruction[2] += CString(" BT ");
		else if		(ModRMSIB[1]=="101")	Instruction[2] += CString(" BTS ");
		else if		(ModRMSIB[1]=="110")	Instruction[2] += CString(" BTR ");
		else if		(ModRMSIB[1]=="111")	Instruction[2] += CString(" BTC ");

		if (Instruction[2].Right(13) == " Undefined ")
		{
			Operands[0]="";Operands[1]="";
		}
	}
	if (groupNumber == 9)
	{
		if			(ModRMSIB[1]=="000")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="001")	Instruction[2] += CString(" CMPXCH ");
		else if		(ModRMSIB[1]=="010")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="011")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="100")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="101")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="110")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="111")	Instruction[2] += CString(" Undefined ");

		if (Instruction[2].Right(13) == " Undefined ")
		{
			Operands[0]="";Operands[1]="";
		}
	}
	if (groupNumber == 10)
	{
		if			(ModRMSIB[1]=="000")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="001")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="010")	Instruction[2] += CString(" PSRLD/PSRLW/PSRLQ ");
		else if		(ModRMSIB[1]=="011")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="100")	Instruction[2] += CString(" PSRAD/PSRAW ");
		else if		(ModRMSIB[1]=="101")	Instruction[2] += CString(" Undefined ");
		else if		(ModRMSIB[1]=="110")	Instruction[2] += CString(" PSLLD/PSLLW/PSLLQ ");
		else if		(ModRMSIB[1]=="111")	Instruction[2] += CString(" Undefined ");

		if (Instruction[2].Right(13) == " Undefined ")
		{
			Operands[0]="";Operands[1]="";
		}
	}
}


void CInstruction::ParseModRM(void)
{
	if (Instruction[1].GetLength() >= 2)
	{
		CString BinaryModRM = CHexOps::HexToBinaryString(Instruction[1].Left(2));
		Instruction[1].Delete(0, 2);
	
		ModRMSIB[0]=BinaryModRM.Left(2);		// Mod
		ModRMSIB[1]=BinaryModRM.Mid(2, 3);		// Reg
		ModRMSIB[2]=BinaryModRM.Right(3);		// RM
	}
	else
		EndOfInstructions=true;
}


void CInstruction::ParseImmediate(int OpSize)
{
	if (OpSize==8 || OpSize==16 || OpSize==32)
	{
		Offsets[1]=Instruction[1].Left(2);
		Instruction[1].Delete(0, 2);
	}
	if (OpSize==16 || OpSize==32)
	{
		Offsets[1].Insert(0, Instruction[1].Left(2));
		Instruction[1].Delete(0, 2);
	}
	if (OpSize==32)
	{
		Offsets[1].Insert(0, Instruction[1].Left(2));
		Instruction[1].Delete(0, 2);
		Offsets[1].Insert(0, Instruction[1].Left(2));
		Instruction[1].Delete(0, 2);
	}
}


void CInstruction::ParseDisplacements(int OpSize)
{
	if (OpSize==8 || OpSize==16 || OpSize==32)
	{
		Offsets[0]=Instruction[1].Left(2);
		Instruction[1].Delete(0, 2);
	}
	if (OpSize==16 || OpSize==32)
	{
		Offsets[0].Insert(0, Instruction[1].Left(2));
		Instruction[1].Delete(0, 2);
	}
	if (OpSize==32)
	{
		Offsets[0]=Instruction[1].Left(2);
		Instruction[1].Delete(0, 2);
		Offsets[0].Insert(0, Instruction[1].Left(2));
		Instruction[1].Delete(0, 2);
	}
}

CString CInstruction::DetermineOperand(int OperandNum)
{
	int OpSize;
	if (Operands[OperandNum]=="Eb")				// ModR/M specified operand (GP Register or Mem. Address (=Seg register + base register/index register/disp.)), Byte argument
	{
		OpSize=8;
		goto ModRM;
	}
	if (Operands[OperandNum]=="Ev")				// ModR/M specified operand (GP Register or Mem. Address (=Seg register + base register/index register/disp.)), Word argument
	{
		OpSize=16;
		goto ModRM;
	}
	if (Operands[OperandNum]=="Ew")				// ModR/M specified operand (GP Register or Mem. Address (=Seg register + base register/index register/disp.)), Word argument
	{
		OpSize=16;
		goto ModRM;
	}
	if (Operands[OperandNum]=="Gb")				// The Reg field of the ModR/M byte selects general register, Byte argument
	{
		OpSize=8;
		goto GP;
	}
	if (Operands[OperandNum]=="Gv")				// The Reg field of the ModR/M byte selected general register, Word argument
	{
		OpSize=16;
		goto GP;
	}
	if (Operands[OperandNum]=="Gw")				// The Reg field of the ModR/M byte selected general register, Word argument
	{
		OpSize=32;
		goto GP;
	}
	if (Operands[OperandNum]=="Ma")				// ModR/M byte refers only to memory location address, two word/dword memory arguments
	{
	}
	if (Operands[OperandNum]=="Sw")				// Reg field of ModR/M byte selects word-sized segment register
	{
		goto SReg3;
	}
	if (Operands[OperandNum]=="Fv")				// Not used in 286
	{
	}
	if (Operands[OperandNum]=="Ib")				// Immediate data operand, byte argument
	{
		ParseImmediate(8);
		Operands[OperandNum]=Offsets[1];
	}
	if (Operands[OperandNum]=="Iv")				// Immediate data operand, word argument
	{
		if (SpecialBits[2]=="0" || SpecialBits[1]=="1")	ParseImmediate(32);
		if (SpecialBits[2]=="1" || SpecialBits[1]=="0")	ParseImmediate(16);
		Operands[OperandNum]=Offsets[1];
	}
	if (Operands[OperandNum]=="Iw")				// Immediate data operand, word argument
	{
		if (SpecialBits[2]=="0" || SpecialBits[1]=="1")	ParseImmediate(32);
		else if (SpecialBits[2]=="1" || SpecialBits[1]=="0")	ParseImmediate(16);
		Operands[OperandNum]=Offsets[1];
	}
	if (Operands[OperandNum]=="Jb")				// Relative offset added to address of subsequent instruction
	{
	}
	if (Operands[OperandNum]=="Ap")				// 32-bit Seg:Offset pointer to Direct Address (No ModRegRM) encoded in instruction
	{
	}
	if (Operands[OperandNum]=="Ob")				// No ModR/M byte, operand offset encoded as Byte in instruction
	{
		ParseImmediate(16);
		Operands[OperandNum]=CString("[") + Offsets[1] + CString("]");
	}
	if (Operands[OperandNum]=="Ov")				// No ModR/M byte, operand offset encoded as Word in instruction
	{
		ParseImmediate(16);
		Operands[OperandNum]=CString("[") + Offsets[1] + CString("]");
	}
	if (Operands[OperandNum]=="Ow")				// No ModR/M byte, operand offset encoded as Word in instruction
	{
		ParseImmediate(16);
		Operands[OperandNum]=CString("[") + Offsets[1] + CString("]");
	}
	if (Operands[OperandNum]=="Xb")				// Memory addressed by DS:rSI pair, byte argument
	{
	}
	if (Operands[OperandNum]=="Xv")				// Memory addressed by DS:rSI pair, word argument
	{
	}
	if (Operands[OperandNum]=="Yb")				// Memory addressed by ES:rSI pair, byte argument
	{
	}
	if (Operands[OperandNum]=="Yv")				// Memory addressed by ES:rSI pair, word argument
	{
	}
	return Operands[OperandNum];	
ModRM:
	int Size=32;
	if (ModRMSIB[2] == "")	ParseModRM();		// Only parse ModRM byte if not already done-so
	if (ModRMSIB[0] == "")
	{
		Instruction[2].Empty();
		Operands[OperandNum].Empty();
		EndOfInstructions=true;
	}
	if (Size==16)
	{
		if (ModRMSIB[0]=="00")				// Mod=00
		{
			if (ModRMSIB[2]=="000")	Operands[OperandNum] = "[BX+SI]";
			if (ModRMSIB[2]=="001")	Operands[OperandNum] = "[BX+DI]";
			if (ModRMSIB[2]=="010")	Operands[OperandNum] = "[BP+SI]";
			if (ModRMSIB[2]=="011")	Operands[OperandNum] = "[BX+DI]";
			if (ModRMSIB[2]=="100")	Operands[OperandNum] = "[SI]";
			if (ModRMSIB[2]=="101")	Operands[OperandNum] = "[DI]";
			if (ModRMSIB[2]=="110")
			{
				ParseDisplacements(16);
				Operands[OperandNum] = CString("[") + Offsets[0] + CString("]");
			}
			if (ModRMSIB[2]=="111")	Operands[OperandNum] = "[BX]";
		}
		if (ModRMSIB[0]=="01")				// Mod=01
		{
			ParseDisplacements(8);
			if (ModRMSIB[2]=="000")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="001")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="010")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="011")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="100")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="101")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="110")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="111")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
		}
		if (ModRMSIB[0]=="10")				// Mod=10
		{
			ParseDisplacements(16);
			if (ModRMSIB[2]=="000")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="001")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="010")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="011")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="100")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="101")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="110")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="111")	Operands[OperandNum] = CString("[BX+SI][") + Offsets[0] + CString("]");
		}
		if (ModRMSIB[0]=="11")				// Mod=11
		{
			if (OpSize==8)
			{
				if (ModRMSIB[2]=="000")
					Operands[OperandNum]="AL";
				if (ModRMSIB[2]=="001")
					Operands[OperandNum]="CL";
				if (ModRMSIB[2]=="010")
					Operands[OperandNum]="DL";
				if (ModRMSIB[2]=="011")
					Operands[OperandNum]="BL";
				if (ModRMSIB[2]=="100")
					Operands[OperandNum]="AH";
				if (ModRMSIB[2]=="101")
					Operands[OperandNum]="CH";
				if (ModRMSIB[2]=="110")
					Operands[OperandNum]="DH";
				if (ModRMSIB[2]=="111")
					Operands[OperandNum]="BH";
			}
			if (OpSize==16)
			{
				if (ModRMSIB[2]=="000")
					Operands[OperandNum]="AX";
				if (ModRMSIB[2]=="001")
					Operands[OperandNum]="CX";
				if (ModRMSIB[2]=="010")
					Operands[OperandNum]="DX";
				if (ModRMSIB[2]=="011")
					Operands[OperandNum]="BX";
				if (ModRMSIB[2]=="100")
					Operands[OperandNum]="SP";
				if (ModRMSIB[2]=="101")
					Operands[OperandNum]="BP]";
				if (ModRMSIB[2]=="110")
					Operands[OperandNum]="SI";
				if (ModRMSIB[2]=="111")
					Operands[OperandNum]="DI";
			}
			if (OpSize==32)
			{
				if (ModRMSIB[2]=="000")
					Operands[OperandNum]="EAX";
				if (ModRMSIB[2]=="001")
					Operands[OperandNum]="ECX";
				if (ModRMSIB[2]=="010")
					Operands[OperandNum]="EDX";
				if (ModRMSIB[2]=="011")
					Operands[OperandNum]="EBX";
				if (ModRMSIB[2]=="100")
					Operands[OperandNum]="ESP";
				if (ModRMSIB[2]=="101")
					Operands[OperandNum]="EBP";
				if (ModRMSIB[2]=="110")
					Operands[OperandNum]="ESI";
				if (ModRMSIB[2]=="111")
					Operands[OperandNum]="EDI";
			}
		}
	}
	if (Size==32)
	{
		if (ModRMSIB[0]=="00")				// Mod=00
		{
			if (ModRMSIB[2]=="000")	Operands[OperandNum] = "[EAX]";
			if (ModRMSIB[2]=="001")	Operands[OperandNum] = "[ECX]";
			if (ModRMSIB[2]=="010")	Operands[OperandNum] = "[EDX]";
			if (ModRMSIB[2]=="011")	Operands[OperandNum] = "[EBX]";
			if (ModRMSIB[2]=="100")	ParseSIB(32);
			if (ModRMSIB[2]=="101")
			{
				ParseDisplacements(32);
				Operands[OperandNum] = CString("[") + Offsets[0] + CString("]");
			}
			if (ModRMSIB[2]=="110") Operands[OperandNum] = "[ESI]";
			if (ModRMSIB[2]=="111")	Operands[OperandNum] = "[EDI]";
		}
		if (ModRMSIB[0]=="01")				// Mod=01
		{
			ParseDisplacements(8);
			if (ModRMSIB[2]=="000")	Operands[OperandNum] = CString("[EAX][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="001")	Operands[OperandNum] = CString("[ECX][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="010")	Operands[OperandNum] = CString("[EDX][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="011")	Operands[OperandNum] = CString("[EBX][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="100")	ParseSIB(32);	// + 8-Bit Displacement
			if (ModRMSIB[2]=="101")	Operands[OperandNum] = CString("[EBP][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="110")	Operands[OperandNum] = CString("[ESI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="111")	Operands[OperandNum] = CString("[EDI][") + Offsets[0] + CString("]");
		}
		if (ModRMSIB[0]=="10")				// Mod=10
		{
			ParseDisplacements(32);
			if (ModRMSIB[2]=="000")	Operands[OperandNum] = CString("[EAX][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="001")	Operands[OperandNum] = CString("[ECX][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="010")	Operands[OperandNum] = CString("[EDX][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="011")	Operands[OperandNum] = CString("[EBX][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="100")	ParseSIB(32);	// + 32-Bit Displacement
			if (ModRMSIB[2]=="101")	Operands[OperandNum] = CString("[EBP][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="110")	Operands[OperandNum] = CString("[ESI][") + Offsets[0] + CString("]");
			if (ModRMSIB[2]=="111")	Operands[OperandNum] = CString("[EDI][") + Offsets[0] + CString("]");
		}
		if (ModRMSIB[0]=="11")				// Mod=11
		{
			if (OpSize==8)
			{
				if (ModRMSIB[2]=="000")
					Operands[OperandNum]="AL";
				if (ModRMSIB[2]=="001")
					Operands[OperandNum]="CL";
				if (ModRMSIB[2]=="010")
					Operands[OperandNum]="DL";
				if (ModRMSIB[2]=="011")
					Operands[OperandNum]="BL";
				if (ModRMSIB[2]=="100")
					Operands[OperandNum]="AH";
				if (ModRMSIB[2]=="101")
					Operands[OperandNum]="CH";
				if (ModRMSIB[2]=="110")
					Operands[OperandNum]="DH";
				if (ModRMSIB[2]=="111")
					Operands[OperandNum]="BH";
			}
			if (OpSize==16)
			{
				if (ModRMSIB[2]=="000")
					Operands[OperandNum]="AX";
				if (ModRMSIB[2]=="001")
					Operands[OperandNum]="CX";
				if (ModRMSIB[2]=="010")
					Operands[OperandNum]="DX";
				if (ModRMSIB[2]=="011")
					Operands[OperandNum]="BX";
				if (ModRMSIB[2]=="100")
					Operands[OperandNum]="SP";
				if (ModRMSIB[2]=="101")
					Operands[OperandNum]="BP]";
				if (ModRMSIB[2]=="110")
					Operands[OperandNum]="SI";
				if (ModRMSIB[2]=="111")
					Operands[OperandNum]="DI";
			}
			if (OpSize==32)
			{
				if (ModRMSIB[2]=="000")
					Operands[OperandNum]="EAX";
				if (ModRMSIB[2]=="001")
					Operands[OperandNum]="ECX";
				if (ModRMSIB[2]=="010")
					Operands[OperandNum]="EDX";
				if (ModRMSIB[2]=="011")
					Operands[OperandNum]="EBX";
				if (ModRMSIB[2]=="100")
					Operands[OperandNum]="ESP";
				if (ModRMSIB[2]=="101")
					Operands[OperandNum]="EBP";
				if (ModRMSIB[2]=="110")
					Operands[OperandNum]="ESI";
				if (ModRMSIB[2]=="111")
					Operands[OperandNum]="EDI";
			}
		}
	}
	return Operands[OperandNum];
GP:
	if (ModRMSIB[1] == "")	ParseModRM();		// Only parse ModRM byte if not already done-so
	if (ModRMSIB[1] == "")
	{
		Operands[OperandNum].Empty();
		Instruction[2].Empty();
		EndOfInstructions=true;
	}
	
	if (OpSize==8)
	{
		if (ModRMSIB[1]=="000")
			Operands[OperandNum]="AL";
		if (ModRMSIB[1]=="001")
			Operands[OperandNum]="CL";
		if (ModRMSIB[1]=="010")
			Operands[OperandNum]="DL";
		if (ModRMSIB[1]=="011")
			Operands[OperandNum]="BL";
		if (ModRMSIB[1]=="100")
			Operands[OperandNum]="AH";
		if (ModRMSIB[1]=="101")
			Operands[OperandNum]="CH";
		if (ModRMSIB[1]=="110")
			Operands[OperandNum]="DH";
		if (ModRMSIB[1]=="111")
			Operands[OperandNum]="BH";
	}
	if (OpSize==16)
	{
		if (ModRMSIB[1]=="000")
			Operands[OperandNum]="AX";
		if (ModRMSIB[1]=="001")
			Operands[OperandNum]="CX";
		if (ModRMSIB[1]=="010")
			Operands[OperandNum]="DX";
		if (ModRMSIB[1]=="011")
			Operands[OperandNum]="BX";
		if (ModRMSIB[1]=="100")
			Operands[OperandNum]="SP";
		if (ModRMSIB[1]=="101")
			Operands[OperandNum]="BP]";
		if (ModRMSIB[1]=="110")
			Operands[OperandNum]="SI";
		if (ModRMSIB[1]=="111")
			Operands[OperandNum]="DI";
	}
	if (OpSize==32)
	{
		if (ModRMSIB[1]=="000")
			Operands[OperandNum]="EAX";
		if (ModRMSIB[1]=="001")
			Operands[OperandNum]="ECX";
		if (ModRMSIB[1]=="010")
			Operands[OperandNum]="EDX";
		if (ModRMSIB[1]=="011")
			Operands[OperandNum]="EBX";
		if (ModRMSIB[1]=="100")
			Operands[OperandNum]="ESP";
		if (ModRMSIB[1]=="101")
			Operands[OperandNum]="EBP";
		if (ModRMSIB[1]=="110")
			Operands[OperandNum]="ESI";
		if (ModRMSIB[1]=="111")
			Operands[OperandNum]="EDI";
	}
	return Operands[OperandNum];
SReg2:											// Reg field points to 2-Bit Segment Register
	if (ModRMSIB[1] == "")	ParseModRM();		// Only parse ModRM byte if not already done-so

	if (ModRMSIB[1]=="00")	Operands[OperandNum]="ES";
	if (ModRMSIB[1]=="01")	Operands[OperandNum]="CS";
	if (ModRMSIB[1]=="10")	Operands[OperandNum]="SS";
	if (ModRMSIB[1]=="11")	Operands[OperandNum]="DS";
	return Operands[OperandNum];
SReg3:											// Reg field points to 3-Bit Segment Register
	if (ModRMSIB[1] == "")	ParseModRM();		// Only parse ModRM byte if not already done-so

	if (ModRMSIB[1]=="000")	Operands[OperandNum]="ES";
	if (ModRMSIB[1]=="001")	Operands[OperandNum]="CS";
	if (ModRMSIB[1]=="010")	Operands[OperandNum]="SS";
	if (ModRMSIB[1]=="011")	Operands[OperandNum]="DS";
	if (ModRMSIB[1]=="100")	Operands[OperandNum]="FS";
	if (ModRMSIB[1]=="101")	Operands[OperandNum]="GS";
	return Operands[OperandNum];
eeeCR:
	if (ModRMSIB[1] == "")	ParseModRM();		// Only parse ModRM byte if not already done-so
	SpecialBits[5]=ModRMSIB[1];
	
	if (SpecialBits[5]=="000")	Operands[OperandNum]="CR0";
	if (SpecialBits[5]=="001")	Operands[OperandNum]="";
	if (SpecialBits[5]=="010")	Operands[OperandNum]="CR2";
	if (SpecialBits[5]=="011")	Operands[OperandNum]="CR3";
	if (SpecialBits[5]=="100")	Operands[OperandNum]="CR4";
	if (SpecialBits[5]=="101")	Operands[OperandNum]="";
	if (SpecialBits[5]=="110")	Operands[OperandNum]="";
	if (SpecialBits[5]=="111")	Operands[OperandNum]="";
	return Operands[OperandNum];
eeeDR:
	if (ModRMSIB[1] == "")	ParseModRM();
	SpecialBits[5]=ModRMSIB[1];

	if (SpecialBits[5]=="000")	Operands[OperandNum]="DR0";
	if (SpecialBits[5]=="001")	Operands[OperandNum]="DR1";
	if (SpecialBits[5]=="010")	Operands[OperandNum]="DR2";
	if (SpecialBits[5]=="011")	Operands[OperandNum]="DR3";
	if (SpecialBits[5]=="100")	Operands[OperandNum]="";
	if (SpecialBits[5]=="101")	Operands[OperandNum]="";
	if (SpecialBits[5]=="110")	Operands[OperandNum]="DR6";
	if (SpecialBits[5]=="111")	Operands[OperandNum]="DR7";
	return Operands[OperandNum];
}


void CInstruction::DetermineTwoByteOpcodes()
{
	if (Opcode[2]=="00")	
	{
		ProcessOpcodeGroups(6);
	}
	if (Opcode[2]=="02")	
	{
		Instruction[2] += CString(" LAR ");
	}
	if (Opcode[2]=="03")	
	{
		Instruction[2] += CString(" LSL ");
	}
	if (Opcode[2]=="06")	
	{
		Instruction[2] += CString(" CLTS ");
	}
	if (Opcode[2]=="08")	
	{
		Instruction[2] += CString(" INVD ");
	}
	if (Opcode[2]=="09")	
	{
		Instruction[2] += CString(" WBINVD ");
	}
	if (Opcode[2]=="0B")	
	{
		Instruction[2] += CString(" UD2 ");		// INTENDED FOR DELIBERATE INVALID OPCODE EXCEPTION (#UD)
	}
	if (Opcode[2]=="20")	
	{
		Instruction[2] += CString(" MOV ");
	}
	if (Opcode[2]=="21")	
	{
		Instruction[2] += CString(" MOV ");
	}
	if (Opcode[2]=="22")	
	{
		Instruction[2] += CString(" MOV ");
	}
	if (Opcode[2]=="23")	
	{
		Instruction[2] += CString(" MOV ");
	}
	if (Opcode[2]=="30")	
	{
		Instruction[2] += CString(" WRMSR ");
	}
	if (Opcode[2]=="31")	
	{
		Instruction[2] += CString(" RDTSC ");
	}
	if (Opcode[2]=="32")	
	{
		Instruction[2] += CString(" RDMSR ");
	}
	if (Opcode[2]=="33")	
	{
		Instruction[2] += CString(" RDPMC ");
	}
	if (Opcode[2]=="40")	
	{
		Instruction[2] += CString(" CMOVO ");
	}
	if (Opcode[2]=="41")	
	{
		Instruction[2] += CString(" CMOVNO ");
	}
	if (Opcode[2]=="42")	
	{
		Instruction[2] += CString(" CMOVC ");
	}
	if (Opcode[2]=="43")	
	{
		Instruction[2] += CString(" CMOVNC ");
	}
	if (Opcode[2]=="44")	
	{
		Instruction[2] += CString(" CMOVZ ");
	}
	if (Opcode[2]=="45")	
	{
		Instruction[2] += CString(" CMOVNZ ");
	}
	if (Opcode[2]=="46")	
	{
		Instruction[2] += CString(" CMOVNA ");
	}
	if (Opcode[2]=="47")	
	{
		Instruction[2] += CString(" CMOVA ");
	}
	if (Opcode[2]=="48")	
	{
		Instruction[2] += CString(" CMOVS ");
	}
	if (Opcode[2]=="49")	
	{
		Instruction[2] += CString(" CMOVNS ");
	}
	if (Opcode[2]=="4A")	
	{
		Instruction[2] += CString(" CMOVP ");
	}
	if (Opcode[2]=="4B")	
	{
		Instruction[2] += CString(" CMOVNP ");
	}
	if (Opcode[2]=="4C")	
	{
		Instruction[2] += CString(" CMOVNGE ");
	}
	if (Opcode[2]=="4D")	
	{
		Instruction[2] += CString(" CMOVNL ");
	}
	if (Opcode[2]=="4E")	
	{
		Instruction[2] += CString(" CMOVNG ");
	}
	if (Opcode[2]=="4F")	
	{
		Instruction[2] += CString(" CMOVNLE ");
	}
	if (Opcode[2]=="60")	
	{
		Instruction[2] += CString(" PUNPCKLBW ");			
	}
	if (Opcode[2]=="61")	
	{
		Instruction[2] += CString(" PUNPCKLWD ");
	}
	if (Opcode[2]=="62")	
	{
		Instruction[2] += CString(" PUNOCKLDQ ");
	}
	if (Opcode[2]=="63")	
	{
		Instruction[2] += CString(" PACKUSDW ");
	}
	if (Opcode[2]=="64")	
	{
		Instruction[2] += CString(" PCMPGTB ");
	}
	if (Opcode[2]=="65")	
	{
		Instruction[2] += CString(" PCMPGTW ");
	}
	if (Opcode[2]=="66")	
	{
		Instruction[2] += CString(" PCMPGTD ");		
	}
	if (Opcode[2]=="67")	
	{
		Instruction[2] += CString(" PACKSSWB ");
	}
	if (Opcode[2]=="68")	
	{
		Instruction[2] += CString(" PUNPCKHBW ");
	}
	if (Opcode[2]=="69")	
	{
		Instruction[2] += CString(" PUNPCKHWD ");
	}
	if (Opcode[2]=="6A")	
	{
		Instruction[2] += CString(" PUNPCKHDQ ");
	}
	if (Opcode[2]=="6B")	
	{
		Instruction[2] += CString(" PACKSSDW ");
	}
	if (Opcode[2]=="6E")	
	{
		Instruction[2] += CString(" MOVD ");
	}
	if (Opcode[2]=="6F")	
	{
		Instruction[2] += CString(" MOVQ ");
	}
	if (Opcode[2]=="71")	
	{
		ProcessOpcodeGroups(10);
	}
	if (Opcode[2]=="72")	
	{
		ProcessOpcodeGroups(10);		
	}
	if (Opcode[2]=="73")	
	{
		ProcessOpcodeGroups(10);
	}
	if (Opcode[2]=="74")	
	{
		Instruction[2] += CString(" PCMPEQB ");		
	}
	if (Opcode[2]=="75")	
	{
		Instruction[2] += CString(" PCMPEQW ");		
	}
	if (Opcode[2]=="76")	
	{
		Instruction[2] += CString(" PCMPEQD ");			
	}
	if (Opcode[2]=="77")	
	{
		Instruction[2] += CString(" EMMS ");		
	}
	if (Opcode[2]=="7E")	
	{
		Instruction[2] += CString(" MOVD ");			
	}
	if (Opcode[2]=="7F")	
	{
		Instruction[2] += CString(" MOVQ ");		
	}
	if (Opcode[2]=="80")	
	{
		Instruction[2] += CString(" JO ");
	}
	if (Opcode[2]=="81")	
	{
		Instruction[2] += CString(" JNO ");
	}
	if (Opcode[2]=="82")	
	{
		Instruction[2] += CString(" JB ");
	}
	if (Opcode[2]=="83")	
	{
		Instruction[2] += CString(" JNB ");
	}
	if (Opcode[2]=="84")	
	{
		Instruction[2] += CString(" JZ ");
	}
	if (Opcode[2]=="85")	
	{
		Instruction[2] += CString(" JNZ ");
	}
	if (Opcode[2]=="86")	
	{
		Instruction[2] += CString(" JBE ");
	}
	if (Opcode[2]=="87")	
	{
		Instruction[2] += CString(" JNBE ");
	}
	if (Opcode[2]=="88")	
	{
		Instruction[2] += CString(" JS ");
	}
	if (Opcode[2]=="89")	
	{
		Instruction[2] += CString(" JNS ");
	}
	if (Opcode[2]=="8A")	
	{
		Instruction[2] += CString(" JP ");
	}
	if (Opcode[2]=="8B")	
	{
		Instruction[2] += CString(" JNP ");
	}
	if (Opcode[2]=="8C")	
	{
		Instruction[2] += CString(" JL ");
	}
	if (Opcode[2]=="8D")	
	{
		Instruction[2] += CString(" JNL ");
	}
	if (Opcode[2]=="8E")	
	{
		Instruction[2] += CString(" JLE ");
	}
	if (Opcode[2]=="8F")	
	{
		Instruction[2] += CString(" JNLE ");
	}
	if (Opcode[2]=="90")	
	{
		Instruction[2] += CString(" SETO ");		
	}
	if (Opcode[2]=="91")	
	{
		Instruction[2] += CString(" SETNO ");
	}
	if (Opcode[2]=="92")	
	{
		Instruction[2] += CString(" SETB ");
	}
	if (Opcode[2]=="93")	
	{
		Instruction[2] += CString(" SETNB ");
	}
	if (Opcode[2]=="94")	
	{
		Instruction[2] += CString(" SETZ ");
	}
	if (Opcode[2]=="95")	
	{
		Instruction[2] += CString(" SETNZ ");
	}
	if (Opcode[2]=="96")	
	{
		Instruction[2] += CString(" SETBE ");
	}
	if (Opcode[2]=="97")	
	{
		Instruction[2] += CString(" SETNBE ");
	}
	if (Opcode[2]=="98")	
	{
		Instruction[2] += CString(" SETS ");	
	}
	if (Opcode[2]=="99")	
	{
		Instruction[2] += CString(" SETNS ");
	}
	if (Opcode[2]=="9A")	
	{
		Instruction[2] += CString(" SETP ");
	}
	if (Opcode[2]=="9B")	
	{
		Instruction[2] += CString(" SETNP ");		
	}
	if (Opcode[2]=="9C")	
	{
		Instruction[2] += CString(" SETL ");
	}
	if (Opcode[2]=="9D")	
	{
		Instruction[2] += CString(" SETNL ");
	}
	if (Opcode[2]=="9E")	
	{
		Instruction[2] += CString(" SETLE ");		
	}
	if (Opcode[2]=="9F")	
	{
		Instruction[2] += CString(" SETNLE ");		
	}
	if (Opcode[2]=="A0")	
	{
		Instruction[2] += CString(" PUSH FS ");
	}
	if (Opcode[2]=="A1")	
	{
		Instruction[2] += CString(" POP FS ");
	}
	if (Opcode[2]=="A2")	
	{
		Instruction[2] += CString(" CPUID ");
	}
	if (Opcode[2]=="A3")	
	{
		Instruction[2] += CString(" BT ");
	}
	if (Opcode[2]=="A4")	
	{
		Instruction[2] += CString(" SHLD ");
	}
	if (Opcode[2]=="A5")	
	{
		Instruction[2] += CString(" SHLD ");
	}
	if (Opcode[2]=="A8")	
	{
		Instruction[2] += CString(" PUSH GS ");
	}
	if (Opcode[2]=="A9")	
	{
		Instruction[2] += CString(" POP GS ");
	}
	if (Opcode[2]=="AA")	
	{
		Instruction[2] += CString(" RSM ");
	}
	if (Opcode[2]=="AB")	
	{
		Instruction[2] += CString(" BTS ");
	}
	if (Opcode[2]=="AC")	
	{
		Instruction[2] += CString(" SHRD ");
	}
	if (Opcode[2]=="AD")	
	{
		Instruction[2] += CString(" SHRD ");
	}
	if (Opcode[2]=="AF")	
	{
		Instruction[2] += CString(" IMUL ");
	}
	if (Opcode[2]=="B0")	
	{
		Instruction[2] += CString(" CMPXCHG ");
	}
	if (Opcode[2]=="B1")	
	{
		Instruction[2] += CString(" CMPXCHG ");
	}
	if (Opcode[2]=="B2")	
	{
		Instruction[2] += CString(" LSS ");
	}
	if (Opcode[2]=="B3")	
	{
		Instruction[2] += CString(" BTR ");
	}
	if (Opcode[2]=="B4")	
	{
		Instruction[2] += CString(" LFS ");
	}
	if (Opcode[2]=="B5")	
	{
		Instruction[2] += CString(" LGS ");
	}
	if (Opcode[2]=="B6")	
	{
		Instruction[2] += CString(" MOVZX ");
	}
	if (Opcode[2]=="B7")	
	{
		Instruction[2] += CString(" MOVZX ");
	}
	if (Opcode[2]=="BA")	
	{
		ProcessOpcodeGroups(8);
	}
	if (Opcode[2]=="BB")	
	{
		Instruction[2] += CString(" BTC ");
	}
	if (Opcode[2]=="BC")	
	{
		Instruction[2] += CString(" BSF ");
	}
	if (Opcode[2]=="BD")	
	{
		Instruction[2] += CString(" BSR ");
	}
	if (Opcode[2]=="BE")	
	{
		Instruction[2] += CString(" MOVSX ");
	}
	if (Opcode[2]=="BF")	
	{
		Instruction[2] += CString(" MOVSX ");
	}
	if (Opcode[2]=="C0")	
	{
		Instruction[2] += CString(" XADD ");
	}
	if (Opcode[2]=="C1")	
	{
		Instruction[2] += CString(" XADD ");
	}
	if (Opcode[2]=="C7")	
	{
		ProcessOpcodeGroups(9);
	}
	if (Opcode[2]=="C8")	
	{
		Instruction[2] += CString(" BSWAP EAX ");
	}
	if (Opcode[2]=="C9")	
	{
		Instruction[2] += CString(" BSWAP ECX ");			
	}
	if (Opcode[2]=="CA")	
	{
		Instruction[2] += CString(" BSWAP EDX ");
	}
	if (Opcode[2]=="CB")	
	{
		Instruction[2] += CString(" BSWAP EBX ");
	}
	if (Opcode[2]=="CC")	
	{
		Instruction[2] += CString(" BSWAP ESP ");
	}
	if (Opcode[2]=="CD")	
	{
		Instruction[2] += CString(" BSWAP EBP ");
	}
	if (Opcode[2]=="CE")	
	{
		Instruction[2] += CString(" BSWAP ESI ");			
	}
	if (Opcode[2]=="CF")	
	{
		Instruction[2] += CString(" BSWAP EDI ");
	}
	if (Opcode[2]=="D1")	
	{
		Instruction[2] += CString(" PSRLW ");
	}
	if (Opcode[2]=="D2")	
	{
		Instruction[2] += CString(" PSRLD ");
	}
	if (Opcode[2]=="D3")	
	{
		Instruction[2] += CString(" PSRLQ ");
	}
	if (Opcode[2]=="D5")	
	{
		Instruction[2] += CString(" PMULLW ");			
	}
	if (Opcode[2]=="D8")	
	{
		Instruction[2] += CString(" PSUBUSB ");			
	}
	if (Opcode[2]=="D9")	
	{
		Instruction[2] += CString(" PSUBUSW ");			
	}
	if (Opcode[2]=="DB")	
	{
		Instruction[2] += CString(" PAND ");			
	}
	if (Opcode[2]=="DC")	
	{
		Instruction[2] += CString(" PADDUSB ");			
	}
	if (Opcode[2]=="DD")	
	{
		Instruction[2] += CString(" PADDUSW ");			
	}
	if (Opcode[2]=="DF")	
	{
		Instruction[2] += CString(" PANDN ");			
	}
	if (Opcode[2]=="E1")	
	{
		Instruction[2] += CString(" PSRAW ");
	}
	if (Opcode[2]=="E2")	
	{
		Instruction[2] += CString(" PSRAD ");
	}
	if (Opcode[2]=="E5")	
	{
		Instruction[2] += CString(" PMULHW ");
	}
	if (Opcode[2]=="E8")	
	{
		Instruction[2] += CString(" PSUBSB ");
	}
	if (Opcode[2]=="E9")	
	{
		Instruction[2] += CString(" PSUBSW ");
	}
	if (Opcode[2]=="EB")	
	{
		Instruction[2] += CString(" POR ");
	}
	if (Opcode[2]=="EC")	
	{
		Instruction[2] += CString(" PADDSB ");
	}
	if (Opcode[2]=="ED")	
	{
		Instruction[2] += CString(" PADDSW ");
	}
	if (Opcode[2]=="EF")	
	{
		Instruction[2] += CString(" PXOR ");
	}
	if (Opcode[2]=="F1")	
	{
		Instruction[2] += CString(" PSLLW ");			
	}
	if (Opcode[2]=="F2")	
	{
		Instruction[2] += CString(" PSLLD ");			
	}
	if (Opcode[2]=="F3")	
	{
		Instruction[2] += CString(" PSLLQ ");			
	}
	if (Opcode[2]=="F5")	
	{
		Instruction[2] += CString(" PMADDWD ");			
	}
	if (Opcode[2]=="F8")	
	{
		Instruction[2] += CString(" PSUBB ");			
	}
	if (Opcode[2]=="F9")	
	{
		Instruction[2] += CString(" PSUBW ");			
	}
	if (Opcode[2]=="FA")	
	{
		Instruction[2] += CString(" PSUBD ");			
	}
	if (Opcode[2]=="FC")	
	{
		Instruction[2] += CString(" PADDB ");			
	}
	if (Opcode[2]=="FD")	
	{
		Instruction[2] += CString(" PADDW ");			
	}
	if (Opcode[2]=="FE")	
	{
		Instruction[2] += CString(" PADDD ");
	}
}


CString CInstruction::ParseSIB(int Size)
{
	if (Instruction[1].Left(2) != "")
	{
		CString SIB = CHexOps::HexToBinaryString(Instruction[1].Left(2));
		Instruction[1].Delete(0, 2);
		CString Scale=SIB.Left(2);
		CString Index=SIB.Mid(2, 5);
		CString Base=SIB.Right(3);
		ModRMSIB[3]=Scale;
		ModRMSIB[4]=Index;
		ModRMSIB[5]=Base;
		CString Op1, Op2, Operand;
	
		if (Scale=="00")
		{
				if (Base=="000")	Op1="EAX";
			if (Base=="001")	Op1="ECX";
			if (Base=="010")	Op1="EDX";
			if (Base=="011")	Op1="EBX";
			if (Base=="100")	Op1="ESP";
			// (Base=="101")	//	???
			if (Base=="110")	Op1="ESI";
			if (Base=="111")	Op1="EDI";
		
			if (Index=="000")	Op2="EAX";
			if (Index=="001")	Op2="ECX";
			if (Index=="010")	Op2="EDX";
			if (Index=="011")	Op2="EBX";
			if (Index=="101")	Op2="EBP";
			if (Index=="110")	Op2="ESI";
			if (Index=="111")	Op2="EDI";
		}
		if (Scale=="01")
		{

		}
		if (Scale=="10")
		{

		}
	}
	return CString();
}
