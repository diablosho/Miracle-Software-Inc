// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// Win32DASMDoc.cpp : implementation of the CWin32DASMDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Win32DASM.h"
#include "DisasmLibrary.h"
#endif

#include "Win32DASMDoc.h"
#include "CntrItem.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWin32DASMDoc

IMPLEMENT_DYNCREATE(CWin32DASMDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CWin32DASMDoc, CRichEditDoc)
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &CRichEditDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CWin32DASMDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CWin32DASMDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CWin32DASMDoc, CRichEditDoc)
END_DISPATCH_MAP()

// Note: we add support for IID_IWin32DASM to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {82B4A7EC-F6E5-4AE6-A741-A1C340CFC6B4}
static const IID IID_IWin32DASM =
{ 0x82B4A7EC, 0xF6E5, 0x4AE6, { 0xA7, 0x41, 0xA1, 0xC3, 0x40, 0xCF, 0xC6, 0xB4 } };

BEGIN_INTERFACE_MAP(CWin32DASMDoc, CRichEditDoc)
	INTERFACE_PART(CWin32DASMDoc, IID_IWin32DASM, Dispatch)
END_INTERFACE_MAP()


// CWin32DASMDoc construction/destruction

CWin32DASMDoc::CWin32DASMDoc()
	: ParsedInstructionArray(NULL)
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CWin32DASMDoc::~CWin32DASMDoc()
{
	AfxOleUnlockApp();
}

BOOL CWin32DASMDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CWin32DASMDoc::CreateClientItem(REOBJECT* preo) const
{
	return new CWin32DASMCntrItem(preo, const_cast<CWin32DASMDoc*>(this));
}




// CWin32DASMDoc serialization

void CWin32DASMDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CWin32DASMDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CWin32DASMDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CWin32DASMDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CWin32DASMDoc diagnostics

#ifdef _DEBUG
void CWin32DASMDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CWin32DASMDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG


// CWin32DASMDoc commands


BOOL CWin32DASMDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CRichEditDoc::OnOpenDocument(lpszPathName))
		return FALSE;

	BYTE dataRead[16];
	int instructionCount = 0, filePos = 0;
	BYTE fileOffset = 0x00, bufferSize = 0x00;
	
	CFile fileToDecode(lpszPathName, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary);
	ParsedInstructionArray = new CObArray;
	ParsedInstructionArray->SetSize(fileToDecode.GetLength()/4, 10240);
	do
	{
		CDisasmLibrary Instruction(dataRead, bufferSize = fileToDecode.Read(&dataRead, 16));
		instructionCount++;
		ParsedInstructionArray->Add(&Instruction);
		fileToDecode.Seek(Instruction.bufferLoc-16, CFile::current);
		filePos = fileToDecode.GetPosition();
//		Instruction.~CDisasmLibrary();	// might not work properly with CObArray;  If not, delete this line
	}	while (bufferSize == 16);
	// Output CObArray to screen
	UpdateAllViews(NULL);
//	ParsedInstructionArray->FreeExtra();
//	ParsedInstructionArray->~CObArray();
	
	return TRUE;
}
