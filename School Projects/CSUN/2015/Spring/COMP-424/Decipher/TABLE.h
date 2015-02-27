#include <utility>
#pragma once
#include "afxtempl.h"

class TABLE
{
public:
	TABLE();
	~TABLE();
	TABLE(CString m_strData, CString m_strKey, int szKey);
	CArray<CString> TABLE_ROWS;
	CArray<CString> TABLE_COLS;
	float INDEX_OF_COINCIDENCE;
	CArray<std::pair<char, int>> CHAR_SET;		// Set of unique characters found within the Cipher-Text
	CString m_strCharSet;
	void FindIndexOfCoincidence();
	void FindCharacterSet(CString m_strData);
	void PopulateRows(CString m_strData, int szKey);
	void PopulateColumns(CString m_strData, int szKey);
};

