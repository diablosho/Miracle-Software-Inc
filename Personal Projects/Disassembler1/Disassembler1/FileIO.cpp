#include "StdAfx.h"
#include "FileIO.h"


CFileIO::CFileIO(CString filename)
{
	fileToProcess.Open(filename, CFile::modeRead);
}


CFileIO::CFileIO()
{
}


CFileIO::~CFileIO(void)
{
}


void CFileIO::ReadBinaryDataFile()
{
	byte *buffer = NULL;
	unsigned __int64 fileLength = fileToProcess.GetLength();
	buffer = new byte[fileLength];
	fileToProcess.Seek(0, CFile::begin);
	fileToProcess.Read(buffer, fileLength);

	for (unsigned __int64 i=0; i < fileLength; i++)
		dataRead.Add(buffer[i]);
}


void CFileIO::ReadHexDataFile()
{
}

void CFileIO::OpenFile(CString filename)
{
	fileToProcess.Open(filename, CFile::modeRead);
}


void CFileIO::CloseFile(void)
{
	fileToProcess.Close();
}
