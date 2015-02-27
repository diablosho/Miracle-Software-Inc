
// x86DecoderSet.h: interface of the Cx86DecoderSet class
//


#pragma once

// code generated on Tuesday, April 09, 2013, 7:33 PM

class Cx86DecoderSet : public CRecordset
{
public:
	Cx86DecoderSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cx86DecoderSet)

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
	CStringW	m_strInstructionToDecode, 
				m_recOpcode1, m_recOpcode2, m_recOpcode3, 
				m_recReg, 
				m_recOperand1, m_recOperand2, m_recOperand3, 
				m_recMnemonic;
};

