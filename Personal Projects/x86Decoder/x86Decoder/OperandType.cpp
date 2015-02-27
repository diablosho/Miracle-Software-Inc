// OperandType.h : Implementation of the COperandType class



// COperandType implementation

// code generated on Thursday, April 11, 2013, 8:15 AM

#include "stdafx.h"
#include "OperandType.h"
IMPLEMENT_DYNAMIC(COperandType, CRecordset)

COperandType::COperandType(CDatabase* pdb) : CRecordset(pdb)
{
	m_nFields = 16;
	m_nDefaultType = snapshot;
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString COperandType::GetDefaultConnect()
{
	return _T("DSN=x86 ISA;DBQ=C:\\Users\\Diablo\\Documents\\x86 Instruction Set.accdb;DefaultDir=C:\\Users\\Diablo\\Documents;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString COperandType::GetDefaultSQL()
{
	return _T("[Operand Type]");
}

void COperandType::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Operand Type]"), m_recOperandType);
	RFX_Bool(pFX, _T("[Regardless of Operand-Size Attribute]"), m_recOpSizeAttribute_not_matter);
	RFX_Bool(pFX, _T("[Two WORD/DWORD Operands in Memory]"), m_recTwo_WORD_or_DWORD_Mem_Operands);
	RFX_Bool(pFX, _T("[BYTE Operand]"), m_recBYTE_Operand);
	RFX_Bool(pFX, _T("[BYTE/WORD Operand]"), m_recBYTE_or_WORD_Operand);
	RFX_Bool(pFX, _T("[DWORD Operand]"), m_recDWORD_Operand);
	RFX_Bool(pFX, _T("[DQWORD Operand]"), m_recDQWORD_Operand);
	RFX_Bool(pFX, _T("[32-bit/48-bit pointer]"), m_rec32bit_or_48bit_Pointer_Operand);
	RFX_Bool(pFX, _T("[QWORD MMX Register]"), m_recQWORD_MMXReg_Operand);
	RFX_Bool(pFX, _T("[128-bit Packed Floating-Point Single-Precision data]"), m_rec128bit_Packed_FP_Single_Precision_Data_Operand);
	RFX_Bool(pFX, _T("[QWORD]"), m_recQWORD_Operand);
	RFX_Bool(pFX, _T("[6-Byte Pseudo-Descriptor]"), m_rec6Byte_PseudoDescriptor_Operand);
	RFX_Bool(pFX, _T("[128-bit Packed FP Single-Precision Scalar Data Element]"), m_rec128bit_Packed_FP_Single_Precision_Scalar_Data_Operand);
	RFX_Bool(pFX, _T("[DWORD Integer Register]"), m_recDWORD_Integer_Operand);
	RFX_Bool(pFX, _T("[WORD/DWORD]"), m_recWORD_or_DWORD_Operand);
	RFX_Bool(pFX, _T("[WORD]"), m_recWORD_Operand);

// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type

}
/////////////////////////////////////////////////////////////////////////////
// COperandType diagnostics

#ifdef _DEBUG
void COperandType::AssertValid() const
{
	CRecordset::AssertValid();
}

void COperandType::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG




void COperandType::EmptyVariables(void)
{
	m_recOperandType = _T("");
	m_recOpSizeAttribute_not_matter = false;
	m_recTwo_WORD_or_DWORD_Mem_Operands = false;
	m_recBYTE_Operand = false;
	m_recBYTE_or_WORD_Operand = false;
	m_recDWORD_Operand = false;
	m_recDQWORD_Operand = false;
	m_rec32bit_or_48bit_Pointer_Operand = false;
	m_recQWORD_MMXReg_Operand = false;
	m_rec128bit_Packed_FP_Single_Precision_Data_Operand = false;
	m_recQWORD_Operand = false;
	m_rec6Byte_PseudoDescriptor_Operand = false;
	m_rec128bit_Packed_FP_Single_Precision_Scalar_Data_Operand = false;
	m_recDWORD_Integer_Operand = false;
	m_recWORD_or_DWORD_Operand = false;
	m_recWORD_Operand = false;
}
