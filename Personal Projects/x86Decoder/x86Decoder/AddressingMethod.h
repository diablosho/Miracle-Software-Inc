// AddressingMethod.h : Declaration of the CAddressingMethod

#pragma once

// code generated on Thursday, April 11, 2013, 8:15 AM

class CAddressingMethod : public CRecordset
{
public:
	CAddressingMethod(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAddressingMethod)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).


// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CStringW m_recAddressing_Method;
	BOOL	m_recIsMemAdd_ComputedBy_SIB_and_Displacement,
			m_recOpAdd_Depends_AddSize_Attribute,
			m_recIsModRM,
			m_recIs_NO_ModRM,
			m_recIs_NO_SIB,
			m_recModRM_Either_GPReg_or_MemAdd,
			m_recModRM_Only_Mem,
			m_recModFld_Only_General_Reg,
			m_recRegFld_Selects_Control_Reg,
			m_recRegFld_Selects_Debug_Reg,
			m_recRegFld_Selects_General_Reg,
			m_recRegFld_Selects_Packed_QWORD_MMX_Reg,
			m_recRegFld_Selects_Segment_Reg,
			m_recRegFld_Selects_Test_Reg,
			m_recRegFld_Selects_Packed_SIMD_FP_Reg,
			m_recOpAdd_Encoded_in_Instruction,
			m_recOpOffset_Encoded_as_WORD_or_DWORD,
			m_recOperand_Either_GPReg_or_MemAdd,
			m_recOperand_Either_MMXReg_or_MemAdd,
			m_recOperand_Either_SIMD_FP_Reg_or_MemAdd,
			m_recRelOffset_Add_to_IPReg,
			m_recDSSI_Addressed_Mem_Operand,
			m_recESDI_Addressed_Mem_Operand,
			m_recIsEFLAGSReg,
			m_recIsImmediate;
	void EmptyVariables(void);
};