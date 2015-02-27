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

// WIN32DASMDoc.cpp : implementation of the CWIN32DASMDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "WIN32DASM.h"
#include "DisasmLibrary.h"
#endif

#include "WIN32DASMDoc.h"
#include "CntrItem.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWIN32DASMDoc

IMPLEMENT_DYNCREATE(CWIN32DASMDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CWIN32DASMDoc, CRichEditDoc)
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &CRichEditDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CWIN32DASMDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CWIN32DASMDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CWIN32DASMDoc, CRichEditDoc)
END_DISPATCH_MAP()

// Note: we add support for IID_IWIN32DASM to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {E170FB6E-2D27-43FE-B739-EDBE47D09CA2}
static const IID IID_IWIN32DASM =
{ 0xE170FB6E, 0x2D27, 0x43FE, { 0xB7, 0x39, 0xED, 0xBE, 0x47, 0xD0, 0x9C, 0xA2 } };

BEGIN_INTERFACE_MAP(CWIN32DASMDoc, CRichEditDoc)
	INTERFACE_PART(CWIN32DASMDoc, IID_IWIN32DASM, Dispatch)
END_INTERFACE_MAP()


// CWIN32DASMDoc construction/destruction

CWIN32DASMDoc::CWIN32DASMDoc()
	: ParsedInstructionArray(NULL)
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CWIN32DASMDoc::~CWIN32DASMDoc()
{
	AfxOleUnlockApp();
}

BOOL CWIN32DASMDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CWIN32DASMDoc::CreateClientItem(REOBJECT* preo) const
{
	return new CWIN32DASMCntrItem(preo, const_cast<CWIN32DASMDoc*>(this));
}




// CWIN32DASMDoc serialization

void CWIN32DASMDoc::Serialize(CArchive& ar)
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
void CWIN32DASMDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CWIN32DASMDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CWIN32DASMDoc::SetSearchContent(const CString& value)
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

// CWIN32DASMDoc diagnostics

#ifdef _DEBUG
void CWIN32DASMDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CWIN32DASMDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG


// CWIN32DASMDoc commands


BOOL CWIN32DASMDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CRichEditDoc::OnOpenDocument(lpszPathName))
		return FALSE;

	BYTE dataRead[16];
	unsigned long long instructionCount = 0, filePos = 0;
	BYTE fileOffset = 0x00, bufferSize = 0x00;
	
	CFile fileToDecode(lpszPathName, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary);
	ParsedInstructionArray = new CObArray;
	ParsedInstructionArray->SetSize(fileToDecode.GetLength()/4, 10240);
	do
	{
		CDisasmLibrary Instruction(dataRead, bufferSize = fileToDecode.Read(&dataRead, 16));
		instructionCount++;
		fileToDecode.Seek(Instruction.bufferLoc-16, CFile::current);
		filePos = fileToDecode.GetPosition();
		ParsedInstructionArray->Add(&Instruction);
		Instruction.~CDisasmLibrary();	// might not work properly with CObArray;  If not, delete this line
	}	while (bufferSize == 16);
	
	// Output CObArray to screen
	UpdateAllViews(NULL);
	ParsedInstructionArray->FreeExtra();
	ParsedInstructionArray->~CObArray();

	return TRUE;
}
