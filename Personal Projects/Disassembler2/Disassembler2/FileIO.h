#pragma once
#include "afx.h"
#include "afxcoll.h"
class CFileIO
{
public:
	CFileIO(CString file);
	CFileIO();
	~CFileIO(void);
	void ReadBinaryDataFile();
	void ReadHexDataFile();
	CFile fileToProcess;	
	CByteArray dataRead;
	void OpenFile(CString filename);
	void CloseFile(void);
};

