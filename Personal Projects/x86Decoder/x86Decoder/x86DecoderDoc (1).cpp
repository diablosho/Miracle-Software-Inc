
// x86DecoderDoc.cpp : implementation of the Cx86DecoderDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "x86Decoder.h"
#endif

#include "x86DecoderSet.h"
#include "x86DecoderDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cx86DecoderDoc

IMPLEMENT_DYNCREATE(Cx86DecoderDoc, CDocument)

BEGIN_MESSAGE_MAP(Cx86DecoderDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &Cx86DecoderDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &Cx86DecoderDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Cx86DecoderDoc, CDocument)
END_DISPATCH_MAP()

// Note: we add support for IID_Ix86Decoder to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {EFBBCEA4-0BAC-4206-9374-FC501F356050}
static const IID IID_Ix86Decoder =
{ 0xEFBBCEA4, 0xBAC, 0x4206, { 0x93, 0x74, 0xFC, 0x50, 0x1F, 0x35, 0x60, 0x50 } };

BEGIN_INTERFACE_MAP(Cx86DecoderDoc, CDocument)
	INTERFACE_PART(Cx86DecoderDoc, IID_Ix86Decoder, Dispatch)
END_INTERFACE_MAP()


// Cx86DecoderDoc construction/destruction

Cx86DecoderDoc::Cx86DecoderDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

Cx86DecoderDoc::~Cx86DecoderDoc()
{
	AfxOleUnlockApp();
}

BOOL Cx86DecoderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cx86DecoderDoc serialization

void Cx86DecoderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void Cx86DecoderDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void Cx86DecoderDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cx86DecoderDoc::SetSearchContent(const CString& value)
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

// Cx86DecoderDoc diagnostics

#ifdef _DEBUG
void Cx86DecoderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cx86DecoderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cx86DecoderDoc commands
