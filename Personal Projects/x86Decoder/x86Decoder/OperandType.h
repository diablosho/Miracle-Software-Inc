// OperandType.h : Declaration of the COperandType

#pragma once

// code generated on Thursday, April 11, 2013, 8:15 AM

class COperandType : public CRecordset
{
public:
	COperandType(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(COperandType)

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
	CStringW m_recOperandType;
	BOOL	m_recOpSizeAttribute_not_matter,
			m_recTwo_WORD_or_DWORD_Mem_Operands,
			m_recBYTE_Operand,
			m_recBYTE_or_WORD_Operand,
			m_recDWORD_Operand,
			m_recDQWORD_Operand,
			m_rec32bit_or_48bit_Pointer_Operand,
			m_recQWORD_MMXReg_Operand,
			m_rec128bit_Packed_FP_Single_Precision_Data_Operand,
			m_recQWORD_Operand,
			m_rec6Byte_PseudoDescriptor_Operand,
			m_rec128bit_Packed_FP_Single_Precision_Scalar_Data_Operand,
			m_recDWORD_Integer_Operand,
			m_recWORD_or_DWORD_Operand,
			m_recWORD_Operand;
	void EmptyVariables(void);
};


