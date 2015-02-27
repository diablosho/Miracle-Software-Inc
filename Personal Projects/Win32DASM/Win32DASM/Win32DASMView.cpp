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

// Win32DASMView.cpp : implementation of the CWin32DASMView class
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
#include "resource.h"
#include "Win32DASMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWin32DASMView

IMPLEMENT_DYNCREATE(CWin32DASMView, CRichEditView)

BEGIN_MESSAGE_MAP(CWin32DASMView, CRichEditView)
	ON_WM_DESTROY()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWin32DASMView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_WM_NCPAINT()
END_MESSAGE_MAP()

// CWin32DASMView construction/destruction

CWin32DASMView::CWin32DASMView()
{
	EnableActiveAccessibility();
	// TODO: add construction code here

}

CWin32DASMView::~CWin32DASMView()
{
}

BOOL CWin32DASMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CWin32DASMView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch)
	SetMargins(CRect(720, 720, 720, 720));
}


// CWin32DASMView printing


void CWin32DASMView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWin32DASMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CWin32DASMView::OnDestroy()
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


void CWin32DASMView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWin32DASMView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWin32DASMView diagnostics

#ifdef _DEBUG
void CWin32DASMView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CWin32DASMView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CWin32DASMDoc* CWin32DASMView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWin32DASMDoc)));
	return (CWin32DASMDoc*)m_pDocument;
}
#endif //_DEBUG


// CWin32DASMView message handlers


void CWin32DASMView::OnDraw(CDC* pDC)
{
	// TODO: Add your specialized code here and/or call the base class
	
	CWin32DASMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CObArray* inst = new CObArray;
	inst->SetSize(pDoc->ParsedInstructionArray->GetCount(), 1);

	for (int Index = 0; Index < pDoc->ParsedInstructionArray->GetCount(); Index++)
	{
		inst = pDoc->ParsedInstructionArray;
		inst[0].GetData();
	}
}


void CWin32DASMView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: Add your specialized code here and/or call the base class
}
