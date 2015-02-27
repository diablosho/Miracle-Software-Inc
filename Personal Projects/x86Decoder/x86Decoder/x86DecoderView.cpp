
// x86DecoderView.cpp : implementation of the Cx86DecoderView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "x86Decoder.h"
#endif

#include "x86DecoderSet.h"
#include "AddressingMethod.h"
#include "OperandType.h"
#include "x86DecoderDoc.h"
#include "x86DecoderView.h"
#include "16BitModRM.h"
#include "32BitModRM.h"
#include "SIB.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cx86DecoderView

IMPLEMENT_DYNCREATE(Cx86DecoderView, CRecordView)

BEGIN_MESSAGE_MAP(Cx86DecoderView, CRecordView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cx86DecoderView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_Decode, &Cx86DecoderView::OnBnClickedDecode)
	ON_BN_CLICKED(IDC_recordNext, &Cx86DecoderView::OnBnClickedrecordnext)
	ON_BN_CLICKED(IDC_recordPrevious, &Cx86DecoderView::OnBnClickedrecordprevious)
END_MESSAGE_MAP()

// Cx86DecoderView construction/destruction

Cx86DecoderView::Cx86DecoderView() : CRecordView(Cx86DecoderView::IDD)
{
	m_pOpcodeSet = NULL;
	m_pAddressingMethodSet = NULL;
	m_pOperandTypeSet = NULL;
	EmptyVariables();
}

Cx86DecoderView::~Cx86DecoderView()
{
}

void Cx86DecoderView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// you can insert DDX_Field* functions here to 'connect' your controls to the database fields, ex.
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// See MSDN and ODBC samples for more information
	DDX_Text(pDX, IDC_InstructionToDecode, m_strInstructionToDecode);
	DDX_FieldText(pDX, IDC_Mnemonic, m_pOpcodeSet->m_recMnemonic, m_pOpcodeSet);
	DDX_FieldText(pDX, IDC_Op1, m_pOpcodeSet->m_recOperand1, m_pOpcodeSet);
	DDX_FieldText(pDX, IDC_Op2, m_pOpcodeSet->m_recOperand2, m_pOpcodeSet);
	DDX_FieldText(pDX, IDC_Op3, m_pOpcodeSet->m_recOperand3, m_pOpcodeSet);
	DDX_FieldText(pDX, IDC_Opcode1, m_pOpcodeSet->m_recOpcode1, m_pOpcodeSet);
	DDX_FieldText(pDX, IDC_Opcode2, m_pOpcodeSet->m_recOpcode2, m_pOpcodeSet);
	DDX_FieldText(pDX, IDC_Reg, m_pOpcodeSet->m_recReg, m_pOpcodeSet);
}

BOOL Cx86DecoderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void Cx86DecoderView::OnInitialUpdate()
{
	m_pOpcodeSet = &GetDocument()->m_x86DecoderSet;
	m_pAddressingMethodSet = &GetDocument()->m_AddressingMethod;
	m_pOperandTypeSet = &GetDocument()->m_OperandType;

	CRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}


// Cx86DecoderView printing


void Cx86DecoderView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cx86DecoderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cx86DecoderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cx86DecoderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Cx86DecoderView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cx86DecoderView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cx86DecoderView diagnostics

#ifdef _DEBUG
void Cx86DecoderView::AssertValid() const
{
	CRecordView::AssertValid();
}

void Cx86DecoderView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

Cx86DecoderDoc* Cx86DecoderView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cx86DecoderDoc)));
	return (Cx86DecoderDoc*)m_pDocument;
}
#endif //_DEBUG


// Cx86DecoderView database support
CRecordset* Cx86DecoderView::OnGetRecordset()
{
	return m_pOpcodeSet;
}


// Cx86DecoderView message handlers
void Cx86DecoderView::OnBnClickedrecordnext()
{
	m_pOpcodeSet->MoveNext();
	UpdateData(FALSE);
}

void Cx86DecoderView::OnBnClickedrecordprevious()
{
	m_pOpcodeSet->MovePrev();
	UpdateData(FALSE);
}

void Cx86DecoderView::OnBnClickedDecode()
{
	EmptyVariables();
	UpdateData(TRUE);
	DecodeInstruction(m_strInstructionToDecode);
	UpdateData(FALSE);
}

void Cx86DecoderView::DecodeInstruction(CString instToDecode)
{
	//	Try with:  008015000000
	//	Opcode 0x00	ADD Eb, Gb
	//	Eb:			ModR/M Byte specifies Byte-Size GP R/M Address
	//	Gb:			Reg-Field selects General Byte-Size Register
	//	ModRM 0x80:	[EAX][disp32]
	//	Disp32:		15 00 00 00 -> 00 00 00 15
	//	Decoded Instruction:	ADD [EAX][000000015], al

	//	Parse Opcode 1
	instDecoded.strOpcode1 = m_strInstructionToDecode.Left(2);
	instDecoded.byteOpcode1 = _tcstoul(instDecoded.strOpcode1.GetBuffer(2), 0, 16);
	m_pOpcodeSet->m_strFilter.Format(L"[Opcode 1] = '%02X'", instDecoded.byteOpcode1);
	m_pOpcodeSet->Requery();

	//	Parse Opcode 2
	if (!m_pOpcodeSet->m_recOpcode2.IsEmpty())
	{
		instDecoded.strOpcode2 = m_strInstructionToDecode.Mid(2,2);
		instDecoded.byteOpcode2 = _tcstoul(instDecoded.strOpcode2.GetBuffer(2), 0, 16);
		m_pOpcodeSet->m_strFilter.Format(L"[Opcode 1] = '%02X' AND \
										[Opcode 2] = '%02X'", 
										instDecoded.byteOpcode1, 
										instDecoded.byteOpcode2);
		m_pOpcodeSet->Requery();
	}

	//	Parse Reg
	if (!m_pOpcodeSet->m_recReg.IsEmpty())
	{
		//	Convert ModRM Byte from CString to BYTE
		instDecoded.strModRM.Format(L"%02s", m_strInstructionToDecode.Mid(4, 2));
		instDecoded.byteModRM = _tcstoul(instDecoded.strModRM.GetBuffer(2), 0, 16);
		instDecoded.byteReg = ((instDecoded.byteModRM & 0x38) >> 3);
		instDecoded.strReg.Format(L"%03X", instDecoded.byteReg);
		m_pOpcodeSet->m_strFilter.Format(L"[Opcode 1] = '%02X' AND \
											[Opcode 2] = '%02X' AND \
											[Reg] = %03i", 
											instDecoded.byteOpcode1, 
											instDecoded.byteOpcode2,
											instDecoded.byteReg);
		m_pOpcodeSet->Requery();
	}
	if (!m_pOpcodeSet->m_recOperand1.IsEmpty())
	{
		instDecoded.strOp1 = m_pOpcodeSet->m_recOperand1;
		instDecoded.numOfOperands = 1;
	}
	if (!m_pOpcodeSet->m_recOperand2.IsEmpty())
	{
		instDecoded.strOp2 = m_pOpcodeSet->m_recOperand2;
		instDecoded.numOfOperands++;
	}
	if (!m_pOpcodeSet->m_recOperand3.IsEmpty())	
	{
		instDecoded.strOp3 = m_pOpcodeSet->m_recOperand3;
		instDecoded.numOfOperands++;
	}
	DecodeOperands(instDecoded.numOfOperands);
}

void Cx86DecoderView::DecodeOperands(BYTE numOfOperands)
{
	CString Operands[3] =	{	instDecoded.strOp1, 
								instDecoded.strOp2, 
								instDecoded.strOp3
							};
	//	Get Size of Operand
	m_pOperandTypeSet->m_strFilter.Format(L"[Operand Type] = '%s'", instDecoded.strOp1.Mid(1,1));
	m_pOperandTypeSet->Open(m_pOperandTypeSet->snapshot, m_pOperandTypeSet->GetDefaultSQL(), NULL);
	GetAddressingSize();

	//	Get Operand Flags
	m_pAddressingMethodSet->m_strFilter.Format(L"[Addressing Method] = '%s'", instDecoded.strOp1.Left(1));
	m_pAddressingMethodSet->Open(m_pAddressingMethodSet->snapshot, m_pAddressingMethodSet->GetDefaultSQL(), NULL); 
	
	if (m_pAddressingMethodSet->m_recIsModRM && !m_pAddressingMethodSet->m_recIs_NO_ModRM)
	{
		DecodeModRM();
	}
}

void Cx86DecoderView::DecodeModRM(void)
{
	if (m_pAddressingMethodSet->m_recIsModRM || !m_pAddressingMethodSet->m_recIs_NO_ModRM)	//	If ModRM is required
	{
		if (instDecoded.AddressingMode == 16)		//	If 16-Bit Addressing Mode...
		{
			m_p16BitModRM->m_strFilter.Format(L"[ModRM] = '%s'", instDecoded.strModRM);
			m_p16BitModRM->Open(m_p16BitModRM->snapshot, m_p16BitModRM->GetDefaultSQL(), NULL);
			if (m_p16BitModRM->m_recDisp16)	instDecoded.strDisplacement.Format(L"%s", m_strInstructionToDecode.Mid(8,4));
			if (m_p16BitModRM->m_recDisp8)	instDecoded.strDisplacement.Format(L"%s", m_strInstructionToDecode.Mid(8,2));
		}
		else if (instDecoded.AddressingMode == 32)	//	If 32-Bit Addressing Mode...
		{
			m_p32BitModRM->m_strFilter.Format(L"[ModRM] = '%s'", instDecoded.strModRM);
			m_p32BitModRM->Open(m_p32BitModRM->snapshot, m_p32BitModRM->GetDefaultSQL(), NULL);
			
			if (m_p32BitModRM->m_recSIB)	//	If SIB BYTE Required...
			{
				DecodeSIB();
			}
			else							//	If SIB BYTE is NOT Required...
			{
				//	Is Displacement called for?
				if (m_p32BitModRM->m_recDisp32)	instDecoded.strDisplacement.Format(L"%s", m_strInstructionToDecode.Mid(8,8));
				if (m_p32BitModRM->m_recDisp8)	instDecoded.strDisplacement.Format(L"%s", m_strInstructionToDecode.Mid(8,2));
			}
		}
	}
}


void Cx86DecoderView::DecodeSIB(void)
{
	instDecoded.strSIB.Format(L"%s", m_strInstructionToDecode.Mid(6,2));
	m_pSIB->m_strFilter.Format(L"[SIB] = '%s'", instDecoded.strSIB);
	m_pSIB->Open(m_pSIB->snapshot, m_pSIB->GetDefaultSQL(), NULL);

	if (m_pSIB->m_recDisp32)	
		instDecoded.strDisplacement.Format(L"%s", m_strInstructionToDecode.Mid(8,12));

	if (m_pSIB->m_recDisp8)		
		instDecoded.strDisplacement.Format(L"%s", m_strInstructionToDecode.Mid(8,12));
}


void Cx86DecoderView::GetAddressingSize(void)
{
	if (m_pOperandTypeSet->m_recOpSizeAttribute_not_matter)
	{
		//if (m_pOperandTypeSet->m_recBYTE_Operand)	instDecoded.AddressingMode = 
	}
	else
	{

	}
}

void Cx86DecoderView::EmptyVariables(void)
{
	m_strInstructionToDecode		=	_T("");
	m_recMnemonic					=	_T("");
	m_recOperand1					=	_T("");
	m_recOperand2					=	_T("");
	m_recOperand3					=	_T("");
	m_recOpcode1					=	_T("");
	m_recOpcode2					=	_T("");
	m_recOpcode3					=	_T("");
	m_recReg						=	_T("");
	instDecoded.strOpcode1			=	_T("");
	instDecoded.strOpcode2			=	_T("");
	instDecoded.strModRM			=	_T("");
	instDecoded.strSIB				=	_T("");
	instDecoded.strDisplacement		=	_T("");
	instDecoded.strImmediate		=	_T("");
	instDecoded.strOp1				=	_T("");
	instDecoded.strOp2				=	_T("");
	instDecoded.strOp3				=	_T("");
	instDecoded.byteOpcode1			=	NULL;
	instDecoded.byteOpcode2			=	NULL;
	instDecoded.byteModRM			=	NULL;
	instDecoded.byteSIB				=	NULL;
	instDecoded.intDisplacement		=	NULL;
	instDecoded.intImmediate		=	NULL;
	instDecoded.numOfOperands		=	0;
	instDecoded.LengthOfOperands	=	0;
	instDecoded.AddressingMode		=	32;
}