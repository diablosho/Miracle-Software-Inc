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

// x86DASMView.cpp : implementation of the Cx86DASMView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "x86DASM.h"
#endif

#include "x86DASMDoc.h"
#include "x86DASMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cx86DASMView

IMPLEMENT_DYNCREATE(Cx86DASMView, CTreeView)

BEGIN_MESSAGE_MAP(Cx86DASMView, CTreeView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cx86DASMView construction/destruction

Cx86DASMView::Cx86DASMView()
{
	// TODO: add construction code here

}

Cx86DASMView::~Cx86DASMView()
{
}

BOOL Cx86DASMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

void Cx86DASMView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

}

void Cx86DASMView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cx86DASMView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cx86DASMView diagnostics

#ifdef _DEBUG
void Cx86DASMView::AssertValid() const
{
	CTreeView::AssertValid();
}

void Cx86DASMView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

Cx86DASMDoc* Cx86DASMView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cx86DASMDoc)));
	return (Cx86DASMDoc*)m_pDocument;
}
#endif //_DEBUG


// Cx86DASMView message handlers
