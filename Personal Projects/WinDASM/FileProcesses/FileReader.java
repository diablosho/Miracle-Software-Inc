package FileProcesses;

import java.io.FileInputStream;
import java.io.IOException;

public class FileReader
{	
	FileInputStream	fileToRead;
	byte[]			byteFile;
	
	public FileReader()	{}	
	public FileReader(String pathFile, byte bufferSize) throws IOException
	{
		fileToRead	=	new FileInputStream(pathFile);
		byteFile	=	new byte[bufferSize];
	}
	
	public byte[] ReadFile(int curPos, int countBytes) throws IOException
	{
		fileToRead.read(byteFile, curPos, countBytes);
		return byteFile;
	}
	
	public void CloseFile() throws IOException
	{
		fileToRead.close();
	}
}