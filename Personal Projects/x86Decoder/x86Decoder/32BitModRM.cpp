// 32BitModRM.h : Implementation of the C32BitModRM class



// C32BitModRM implementation

// code generated on Thursday, April 11, 2013, 2:37 PM

#include "stdafx.h"
#include "32BitModRM.h"
IMPLEMENT_DYNAMIC(C32BitModRM, CRecordset)

C32BitModRM::C32BitModRM(CDatabase* pdb) : CRecordset(pdb)
{
	m_nFields = 11;
	m_nDefaultType = snapshot;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString C32BitModRM::GetDefaultConnect()
{
	return _T("DSN=x86 ISA;DBQ=C:\\Users\\Diablo\\Documents\\x86 Instruction Set.accdb;DefaultDir=C:\\Users\\Diablo\\Documents;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString C32BitModRM::GetDefaultSQL()
{
	return _T("[32-Bit Addressing ModRM]");
}

void C32BitModRM::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ModRM]"), m_recModRM);
	RFX_Text(pFX, _T("[Effective Address]"), m_recEffectiveAddress);
	RFX_Text(pFX, _T("[Reg8]"), m_recReg8);
	RFX_Text(pFX, _T("[Reg16]"), m_recReg16);
	RFX_Text(pFX, _T("[Reg32]"), m_recReg32);
	RFX_Text(pFX, _T("[MM]"), m_recMM);
	RFX_Text(pFX, _T("[XMM]"), m_recXMM);
	RFX_Bool(pFX, _T("[Disp8]"), m_recDisp8);
	RFX_Bool(pFX, _T("[Disp16]"), m_recDisp16);
	RFX_Bool(pFX, _T("[Disp32]"), m_recDisp32);
	RFX_Bool(pFX, _T("[SIB]"), m_recSIB);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type

}
/////////////////////////////////////////////////////////////////////////////
// C32BitModRM diagnostics

#ifdef _DEBUG
void C32BitModRM::AssertValid() const
{
	CRecordset::AssertValid();
}

void C32BitModRM::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


