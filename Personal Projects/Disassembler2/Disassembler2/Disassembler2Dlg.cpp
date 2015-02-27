
// Disassembler2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Disassembler2.h"
#include "Disassembler2Dlg.h"
#include "Instruction.h"
#include "FileIO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDisassembler2Dlg dialog




CDisassembler2Dlg::CDisassembler2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDisassembler2Dlg::IDD, pParent)
	, BinaryDataSize(0)
	, DecodedInstructionsCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_sFileName = _T("");
}

void CDisassembler2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_Filename, m_sFileName);
	DDX_Control(pDX, IDC_InstructionsList, m_cInstructionsList);
}

BEGIN_MESSAGE_MAP(CDisassembler2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BrowseForFile, &CDisassembler2Dlg::OnClickedBrowseforfile)
ON_WM_PAINT()
END_MESSAGE_MAP()


// CDisassembler2Dlg message handlers

BOOL CDisassembler2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_cInstructionsList.InsertColumn(0, CString("Instructions"), LVCFMT_LEFT, 150, 10);

	OnClickedBrowseforfile();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDisassembler2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDisassembler2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDisassembler2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDisassembler2Dlg::OnClickedBrowseforfile()
{
	CFileDialog fileToDecode(TRUE);
	if (fileToDecode.DoModal() == IDOK)
	{
		m_sFileName = fileToDecode.GetPathName();
		fileProcess.OpenFile(m_sFileName);									// Open file in FileIO library for binary parsing
		
		fileProcess.ReadBinaryDataFile();									// Parse data file into CByteArray object
		BinaryData.Copy(fileProcess.dataRead);								// Copy binary data to permanent storage CByteArray
		BinaryDataSize=BinaryData.GetCount();								// Get Number of Bytes in file
		
		fileProcess.CloseFile();											// File no longer needed
		
		ProcessFile();														// Process Instructions
	}
}


void CDisassembler2Dlg::ProcessFile()
{
	CInstruction processor(BinaryData.GetData(), BinaryDataSize);							// Create Instruction Parsing Object
	BinaryDataSize=0;
	
	DecodedInstructions.Copy(processor.FinalInstruction);									// Copy Instructions to local memory
	DecodedInstructionsCount = DecodedInstructions.GetCount();								// Get Number of Instructions

	PopulateInstructionList(0);
}



void CDisassembler2Dlg::PopulateInstructionList(int TopIndex)
{
	for (int index=0; index < 1000; index++)												// Process 1000 instructions
		m_cInstructionsList.InsertItem(index, DecodedInstructions[TopIndex+index]);			// Send instructions to list control
	UpdateData(FALSE);
}