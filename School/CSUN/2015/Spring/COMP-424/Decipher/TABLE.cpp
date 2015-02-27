#include "stdafx.h"
#include <utility>
#include <algorithm>
#include "TABLE.h"

TABLE::TABLE()
	: INDEX_OF_COINCIDENCE(0)
	, m_strCharSet(_T(""))
{
}


TABLE::~TABLE()
{
}


TABLE::TABLE(CString m_strData, CString m_strKey, int szKey)
{
	PopulateRows(m_strData, szKey);
	PopulateColumns(m_strData, szKey);
	FindCharacterSet(m_strData);
	FindIndexOfCoincidence();
}

void TABLE::FindIndexOfCoincidence()	/*	Determine the Index of Coincidence	*/
{
	float	sum1 = 0,	sum2 = 0;
	for (int i = 0; i < CHAR_SET.GetSize(); i++)
	{
		sum1 += CHAR_SET.GetAt(i).second;
		sum2 += (CHAR_SET.GetAt(i).second*(CHAR_SET.GetAt(i).second - 1));
	}
	INDEX_OF_COINCIDENCE = (sum2 / (sum1 * (sum1 - 1)));
}

void TABLE::FindCharacterSet(CString m_strData)
{
	//	Determine the set of Unique Characters in the Cipher-Text Input String
	std::pair<char, int> pairs = { m_strData.GetAt(0), 0 };
	for (int dupIndex = 0; (m_strData.GetLength()) >= 0;)
	{
		dupIndex = m_strData.Find(pairs.first);
		if (dupIndex < 0)
		{
			CHAR_SET.Add(pairs);
			m_strCharSet.AppendChar(pairs.first);
			if (m_strData.GetLength() == 0)
				break;
			else
			{
				pairs = { m_strData.GetAt(0), 0 };
				dupIndex = 0;
			}
		}
		pairs.second++;
		m_strData.Delete(dupIndex, 1);
	}
	
	CString sortStringBuffer = m_strCharSet.GetBuffer(m_strCharSet.GetLength());
	std::sort(sortStringBuffer.GetBuffer(), sortStringBuffer.GetBuffer() + sortStringBuffer.GetLength());
	m_strCharSet = sortStringBuffer;
}

void TABLE::PopulateRows(CString m_strData, int szKey)			//	Populate the Rows in the Table
{
	int numROWS = (m_strData.GetLength() / szKey) + 1;
	TABLE_ROWS.SetSize(numROWS);
	for (int row = 0; row < numROWS; row++)
		TABLE_ROWS.SetAt(row, m_strData.Mid(row*szKey, szKey));
}


void TABLE::PopulateColumns(CString m_strData, int szKey)		//	Populate the Columns in the Table
{
	int numROWS = (m_strData.GetLength() / szKey) + 1;
	TABLE_COLS.SetSize(szKey);
	for (int col = 0; col < szKey; col++)
		for (int row = 0; row < numROWS; row++)
			TABLE_COLS[col] += TABLE_ROWS[row].Mid(col, 1);
}