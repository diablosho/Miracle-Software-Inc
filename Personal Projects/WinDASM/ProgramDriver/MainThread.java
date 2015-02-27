package ProgramDriver;

import java.io.IOException;
import java.math.BigInteger;

import Disassembler.Disassembler;

public class MainThread
{
	final	static	String		pathDecodeFile			=	"c:\\Downloads\\LODPatch_113d.exe";
			static	BigInteger	InstructionBlock	=	null;		
			static	byte[]		byteBuffer			=	null;
			
	public static void main(String[] args) throws IOException
	{
		Disassembler	DASM	=	new	Disassembler(pathDecodeFile);
		byteBuffer				=	DASM.ReadFile(0, 15);
		DASM.disassemble(byteBuffer);
		DASM.CloseFile();
	}
}