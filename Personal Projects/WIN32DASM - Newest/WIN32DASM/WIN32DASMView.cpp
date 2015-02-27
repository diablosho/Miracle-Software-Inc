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

// WIN32DASMView.cpp : implementation of the CWIN32DASMView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "WIN32DASM.h"
#endif

#include "WIN32DASMDoc.h"
#include "CntrItem.h"
#include "resource.h"
#include "WIN32DASMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWIN32DASMView

IMPLEMENT_DYNCREATE(CWIN32DASMView, CRichEditView)

BEGIN_MESSAGE_MAP(CWIN32DASMView, CRichEditView)
	ON_WM_DESTROY()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWIN32DASMView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_WM_DRAWITEM()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CWIN32DASMView construction/destruction

CWIN32DASMView::CWIN32DASMView()
	: ParsedInstructionArray(NULL)
{
	EnableActiveAccessibility();
	// TODO: add construction code here

}

CWIN32DASMView::~CWIN32DASMView()
{
}

BOOL CWIN32DASMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CWIN32DASMView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch)
	SetMargins(CRect(720, 720, 720, 720));
}


// CWIN32DASMView printing


void CWIN32DASMView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWIN32DASMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CWIN32DASMView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   CRichEditView::OnDestroy();
}


void CWIN32DASMView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWIN32DASMView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWIN32DASMView diagnostics

#ifdef _DEBUG
void CWIN32DASMView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CWIN32DASMView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CWIN32DASMDoc* CWIN32DASMView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWIN32DASMDoc)));
	return (CWIN32DASMDoc*)m_pDocument;
}
#endif //_DEBUG


// CWIN32DASMView message handlers


void CWIN32DASMView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// Do not call CRichEditView::OnPaint() for painting messages
	
	CWIN32DASMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	ParsedInstructionArray = pDoc->ParsedInstructionArray;
	
	CRect windowRect;
	GetClientRect(&windowRect);
	
	dc.SetTextAlign(TA_BASELINE | TA_CENTER);
	dc.TextOut((windowRect.right / 2), (windowRect.bottom / 2), _T("testing"));
}
