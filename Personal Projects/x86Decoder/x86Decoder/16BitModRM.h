// 16BitModRM.h : Declaration of the C16BitModRM

#pragma once

// code generated on Thursday, April 11, 2013, 2:37 PM

class C16BitModRM : public CRecordset
{
public:
	C16BitModRM(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(C16BitModRM)

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
	CStringW	m_recModRM,
				m_recEffectiveAddress,
				m_recReg8,
				m_recReg16,
				m_recReg32,
				m_recMM,
				m_recXMM;
	BOOL		m_recDisp8,
				m_recDisp16,
				m_recDisp32;
};


