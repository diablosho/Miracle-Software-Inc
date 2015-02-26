
// DecipherDlg.h : header file
//
#include <vector>
#pragma once
#include "afxwin.h"

class CDecipherDlgAutoProxy;


// CDecipherDlg dialog
class CDecipherDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDecipherDlg);
	friend class CDecipherDlgAutoProxy;

// Construction
public:
	CDecipherDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CDecipherDlg();

// Dialog Data
	enum { IDD = IDD_DECIPHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CDecipherDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strKey;
	CEdit m_cKey;
	CEdit m_cValidCharacters;
	CString m_strValidCharacters;
	CEdit m_cKeyLengthMax;
	CString m_strKeyLengthMax;
	CEdit m_cInputCipher;
	CString m_strInputCipher;
	CListBox m_cListSolutions;
	afx_msg void OnBnClickedDeShift();
	afx_msg void OnBnClickedDeTranspose();
	afx_msg void OnSelchangePotentialSolutions();
	afx_msg void OnBnClickedSubstitute();
	unsigned long int factorial(unsigned int n);
	std::vector<CString> Permute(CString working_set);
};
