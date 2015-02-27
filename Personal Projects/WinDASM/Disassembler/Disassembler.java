package Disassembler;
import java.io.IOException;
import java.math.BigInteger;

import x86ISA.Database;
import FileProcesses.*;

public class Disassembler extends FileReader
{	
	Database	dbase	=	new	Database("x86 Instruction Set.accdb");
	
	byte[] Prefixes	=	
	{
		(byte) 0xF0,	//	LOCK
		(byte) 0xF2,	//	REPNE
		(byte) 0xF3,	//	REP/REPE
		(byte) 0x26,	//	ES SEGMENT OVERRIDE
		(byte) 0x2E,	//	CS SEGMENT OVERRIDE
		(byte) 0x36,	//	SS SEGMENT OVERRIDE
		(byte) 0x3E,	//	DS SEGMENT OVERRIDE
		(byte) 0x64,	//	FS SEGMENT OVERRIDE
		(byte) 0x65,	//	GS SEGMENT OVERRIDE
		(byte) 0x66,	//	OPERAND-SIZE OVERRIDE
		(byte) 0x67		//	ADDRESS-SIZE OVERRIDE
	};
	
	public Disassembler(String pathFile) throws IOException
	{
		super(pathFile, (byte) 15);
	}
	
	public String[] disassemble(byte[] fileBigInt)
	{
		
		return null;
	}
}