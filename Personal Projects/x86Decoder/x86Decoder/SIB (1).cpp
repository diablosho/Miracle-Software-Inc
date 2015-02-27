// 32BitSIB.h : Implementation of the C32BitSIB class



// C32BitSIB implementation

// code generated on Thursday, April 11, 2013, 2:37 PM

#include "stdafx.h"
#include "SIB.h"
IMPLEMENT_DYNAMIC(CSIB, CRecordset)

CSIB::CSIB(CDatabase* pdb) : CRecordset(pdb)
{
	m_nFields = 7;
	m_nDefaultType = snapshot;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CSIB::GetDefaultConnect()
{
	return _T("DSN=x86 ISA;DBQ=C:\\Users\\Diablo\\Documents\\x86 Instruction Set.accdb;DefaultDir=C:\\Users\\Diablo\\Documents;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CSIB::GetDefaultSQL()
{
	return _T("[32-Bit SIB]");
}

void CSIB::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[SIB]"), m_recSIB);
	RFX_Bool(pFX, _T("[Disp8]"), m_recDisp8);
	RFX_Bool(pFX, _T("[Disp32]"), m_recDisp32);
	RFX_Text(pFX, _T("[Reg]"), m_recReg);
	RFX_Text(pFX, _T("[Scaled Index (2^SS)]"), m_recScaledIndex);
	RFX_Text(pFX, _T("[SS]"), m_recSS);
	RFX_Text(pFX, _T("[Index]"), m_recIndex);

// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type

}
/////////////////////////////////////////////////////////////////////////////
// C32BitSIB diagnostics

#ifdef _DEBUG
void CSIB::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSIB::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


