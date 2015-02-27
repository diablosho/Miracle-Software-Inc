
// Disassembler1Dlg.h : header file
//

#pragma once
#include "afxdlgs.h"
#include "fileio.h"


// CDisassembler1Dlg dialog
class CDisassembler1Dlg : public CDialogEx
{
// Construction
public:
	CDisassembler1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_Disassembler1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickedBrowseforfile();
	DECLARE_MESSAGE_MAP()
public:
	void ProcessFile();
	void PopulateInstructionList(int TopIndex);
	
	CFileIO fileProcess;
	CString m_sFileName;
	
	CByteArray BinaryData;
	int BinaryDataSize;
	
	CStringArray DecodedInstructions;
	int DecodedInstructionsCount;
	CListCtrl m_cInstructionsList;
};
