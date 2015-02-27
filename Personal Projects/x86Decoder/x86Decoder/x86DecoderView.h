
// x86DecoderView.h : interface of the Cx86DecoderView class
//

#pragma once

class Cx86DecoderSet;

class Cx86DecoderView : public CRecordView
{
protected: // create from serialization only
	Cx86DecoderView();
	DECLARE_DYNCREATE(Cx86DecoderView)

public:
	enum{ IDD = IDD_X86DECODER_FORM };
	Cx86DecoderSet* m_pOpcodeSet;
	CAddressingMethod* m_pAddressingMethodSet;
	COperandType* m_pOperandTypeSet;
	C16BitModRM* m_p16BitModRM;
	C32BitModRM* m_p32BitModRM;
	CSIB* m_pSIB;
	
// Attributes
public:
	Cx86DecoderDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Cx86DecoderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit3();
	CString m_strInstructionToDecode;
	CString m_recMnemonic;
	CString m_recOperand1;
	CString m_recOperand2;
	CString m_recOperand3;
	CString m_recOpcode1;
	CString m_recOpcode2;
	CString m_recOpcode3;
	CString m_recReg;
	struct
	{
		CString strOpcode1, 
				strOpcode2,
				strModRM, 
				strReg,
				strSIB, 
				strDisplacement, 
				strImmediate,
				strOp1, 
				strOp2, 
				strOp3;
		BYTE	byteOpcode1,
				byteOpcode2,
				byteModRM,
				byteReg,
				byteSIB,
				intDisplacement,
				intImmediate,
				numOfOperands,
				LengthOfOperands,
				OperandSize,
				AddressingMode;
	} instDecoded;
	afx_msg void OnBnClickedDecode();
	afx_msg void OnBnClickedrecordnext();
	afx_msg void OnBnClickedrecordprevious();
	void DecodeInstruction(CString instToDecode);
	void EmptyVariables(void);
	void DecodeOperands(BYTE numOfOperands);
	void DecodeModRM(void);
	void DecodeSIB(void);
	void GetAddressingSize(void);
};

#ifndef _DEBUG  // debug version in x86DecoderView.cpp
inline Cx86DecoderDoc* Cx86DecoderView::GetDocument() const
   { return reinterpret_cast<Cx86DecoderDoc*>(m_pDocument); }
#endif

