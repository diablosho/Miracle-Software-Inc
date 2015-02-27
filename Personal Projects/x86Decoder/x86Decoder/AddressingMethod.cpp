// AddressingMethod.h : Implementation of the CAddressingMethod class



// CAddressingMethod implementation

// code generated on Thursday, April 11, 2013, 8:15 AM

#include "stdafx.h"
#include "AddressingMethod.h"
IMPLEMENT_DYNAMIC(CAddressingMethod, CRecordset)

CAddressingMethod::CAddressingMethod(CDatabase* pdb) : CRecordset(pdb)
{
	m_nFields = 26;
	m_nDefaultType = snapshot;
	EmptyVariables();
}

// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CAddressingMethod::GetDefaultConnect()
{
	return _T("DSN=x86 ISA;DBQ=C:\\Users\\Diablo\\Documents\\x86 Instruction Set.accdb;DefaultDir=C:\\Users\\Diablo\\Documents;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CAddressingMethod::GetDefaultSQL()
{
	return _T("[Addressing Method]");
}

void CAddressingMethod::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Addressing Method]"), m_recAddressing_Method);
	RFX_Bool(pFX, _T("[Memory Address Operand Computer by SIB + Displacement]"), m_recIsMemAdd_ComputedBy_SIB_and_Displacement);
	RFX_Bool(pFX, _T("[Operand-Address depends on Address-Size Attribute]"), m_recOpAdd_Depends_AddSize_Attribute);
	RFX_Bool(pFX, _T("[is ModRM?]"), m_recIsModRM);
	RFX_Bool(pFX, _T("[is NO ModRM?]"), m_recIs_NO_ModRM);
	RFX_Bool(pFX, _T("[is NO SIB?]"), m_recIs_NO_SIB);
	RFX_Bool(pFX, _T("[ModRM Specifies either GP-Register or Memory Address]"), m_recModRM_Either_GPReg_or_MemAdd);
	RFX_Bool(pFX, _T("[ModRM refers only to Memory]"), m_recModRM_Only_Mem);
	RFX_Bool(pFX, _T("[Mod Field selects only General Register]"), m_recModFld_Only_General_Reg);
	RFX_Bool(pFX, _T("[Reg Field selects Control Register]"), m_recRegFld_Selects_Control_Reg);
	RFX_Bool(pFX, _T("[Reg Field selects Debug Register]"), m_recRegFld_Selects_Debug_Reg);
	RFX_Bool(pFX, _T("[Reg Field selects General Register]"), m_recRegFld_Selects_General_Reg);
	RFX_Bool(pFX, _T("[Reg Field selects Packed QWORD MMX Register]"), m_recRegFld_Selects_Packed_QWORD_MMX_Reg);
	RFX_Bool(pFX, _T("[Reg Field selects Segment Register]"), m_recRegFld_Selects_Segment_Reg);
	RFX_Bool(pFX, _T("[Reg Field selects Test Register]"), m_recRegFld_Selects_Test_Reg);
	RFX_Bool(pFX, _T("[Reg Field selects Packed SIMD Floating-Point Register]"), m_recRegFld_Selects_Packed_SIMD_FP_Reg);
	RFX_Bool(pFX, _T("[Operand Address Encoded in Instruction]"), m_recOpAdd_Encoded_in_Instruction);
	RFX_Bool(pFX, _T("[Operand Offset is coded as WORD or DWORD]"), m_recOpOffset_Encoded_as_WORD_or_DWORD);
	RFX_Bool(pFX, _T("[Operand is either GP Register or Memory Address]"), m_recOperand_Either_GPReg_or_MemAdd);
	RFX_Bool(pFX, _T("[Operand is either MMX Register or Memory Address]"), m_recOperand_Either_MMXReg_or_MemAdd);
	RFX_Bool(pFX, _T("[Operand is either SIMD Floating-Point Register or Memory Address]"), m_recOperand_Either_SIMD_FP_Reg_or_MemAdd);
	RFX_Bool(pFX, _T("[is Relative Offset to add to IP-Register]"), m_recRelOffset_Add_to_IPReg);
	RFX_Bool(pFX, _T("[Memory addressed by DS:SI Register Pair]"), m_recDSSI_Addressed_Mem_Operand);
	RFX_Bool(pFX, _T("[Memory Addressed by ES:DI Register Pair]"), m_recESDI_Addressed_Mem_Operand);
	RFX_Bool(pFX, _T("[EFLAGS Register]"), m_recIsEFLAGSReg);
	RFX_Bool(pFX, _T("[is Immediate]"), m_recIsImmediate);

// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type

}
/////////////////////////////////////////////////////////////////////////////
// CAddressingMethod diagnostics

#ifdef _DEBUG
void CAddressingMethod::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAddressingMethod::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


void CAddressingMethod::EmptyVariables(void)
{
	m_recAddressing_Method = _T("");
	m_recIsMemAdd_ComputedBy_SIB_and_Displacement = false;
	m_recOpAdd_Depends_AddSize_Attribute = false;
	m_recIsModRM = false;
	m_recIs_NO_ModRM = false;
	m_recIs_NO_SIB = false;
	m_recModRM_Either_GPReg_or_MemAdd = false;
	m_recModRM_Only_Mem = false;
	m_recModFld_Only_General_Reg = false;
	m_recRegFld_Selects_Control_Reg = false;
	m_recRegFld_Selects_Debug_Reg = false;
	m_recRegFld_Selects_General_Reg = false;
	m_recRegFld_Selects_Packed_QWORD_MMX_Reg = false;
	m_recRegFld_Selects_Segment_Reg = false;
	m_recRegFld_Selects_Test_Reg = false;
	m_recRegFld_Selects_Packed_SIMD_FP_Reg = false;
	m_recOpAdd_Encoded_in_Instruction = false;
	m_recOpOffset_Encoded_as_WORD_or_DWORD = false;
	m_recOperand_Either_GPReg_or_MemAdd = false;
	m_recOperand_Either_MMXReg_or_MemAdd = false;
	m_recOperand_Either_SIMD_FP_Reg_or_MemAdd = false;
	m_recRelOffset_Add_to_IPReg = false;
	m_recDSSI_Addressed_Mem_Operand = false;
	m_recESDI_Addressed_Mem_Operand = false;
	m_recIsEFLAGSReg = false;
	m_recIsImmediate = false;
}