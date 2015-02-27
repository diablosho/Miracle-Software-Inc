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

// x86DASMDoc.cpp : implementation of the Cx86DASMDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "x86DASM.h"
#include "Instruction.h"
#include "InstructionDecoder.h"
#endif

#include "x86DASMDoc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cx86DASMDoc

IMPLEMENT_DYNCREATE(Cx86DASMDoc, CDocument)

BEGIN_MESSAGE_MAP(Cx86DASMDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &Cx86DASMDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &Cx86DASMDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Cx86DASMDoc, CDocument)
END_DISPATCH_MAP()

// Note: we add support for IID_Ix86DASM to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {EA876594-F680-4C42-A46F-5FAFF4955832}
static const IID IID_Ix86DASM =
{ 0xEA876594, 0xF680, 0x4C42, { 0xA4, 0x6F, 0x5F, 0xAF, 0xF4, 0x95, 0x58, 0x32 } };

BEGIN_INTERFACE_MAP(Cx86DASMDoc, CDocument)
	INTERFACE_PART(Cx86DASMDoc, IID_Ix86DASM, Dispatch)
END_INTERFACE_MAP()


// Cx86DASMDoc construction/destruction

Cx86DASMDoc::Cx86DASMDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

Cx86DASMDoc::~Cx86DASMDoc()
{
	AfxOleUnlockApp();
}

BOOL Cx86DASMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cx86DASMDoc serialization

void Cx86DASMDoc::Serialize(CArchive& ar)
{
	//	MUST USE THE INDIVIDUAL OBJECT'S SERIALIZE() FUNCTION, SINCE THE TYPE OF DATA IS NOT KNOWN AHEAD OF TIME
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		CInstructionDecoder Decoder;
		Decoder.Serialize(ar);
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void Cx86DASMDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void Cx86DASMDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cx86DASMDoc::SetSearchContent(const CString& value)
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

// Cx86DASMDoc diagnostics

#ifdef _DEBUG
void Cx86DASMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cx86DASMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cx86DASMDoc commands