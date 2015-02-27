
// x86DecoderSet.cpp : implementation of the Cx86DecoderSet class
//

#include "stdafx.h"
#include "x86Decoder.h"
#include "x86DecoderSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cx86DecoderSet implementation

// code generated on Tuesday, April 09, 2013, 7:33 PM

IMPLEMENT_DYNAMIC(Cx86DecoderSet, CRecordset)

Cx86DecoderSet::Cx86DecoderSet(CDatabase* pdb) : CRecordset(pdb)
{
	m_nFields = 7;
	m_nDefaultType = snapshot;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString Cx86DecoderSet::GetDefaultConnect()
{
	return _T("DSN=x86 ISA;DBQ=C:\\Users\\Diablo\\Documents\\x86 Instruction Set.accdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString Cx86DecoderSet::GetDefaultSQL()
{
	return _T("[Opcodes]");
}

void Cx86DecoderSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Opcode 1]"), m_recOpcode1);
	RFX_Text(pFX, _T("[Opcode 2]"), m_recOpcode2);
	RFX_Text(pFX, _T("[Reg]"), m_recReg);
	RFX_Text(pFX, _T("[Op1]"), m_recOperand1);
	RFX_Text(pFX, _T("[Op2]"), m_recOperand2);
	RFX_Text(pFX, _T("[Op3]"), m_recOperand3);
	RFX_Text(pFX, _T("[Mnemonic]"), m_recMnemonic);

// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type

}
/////////////////////////////////////////////////////////////////////////////
// Cx86DecoderSet diagnostics

#ifdef _DEBUG
void Cx86DecoderSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cx86DecoderSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG