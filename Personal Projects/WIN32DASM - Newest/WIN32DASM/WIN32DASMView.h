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

// WIN32DASMView.h : interface of the CWIN32DASMView class
//

#pragma once
#include "disasmlibrary.h"

class CWIN32DASMCntrItem;

class CWIN32DASMView : public CRichEditView
{
protected: // create from serialization only
	CWIN32DASMView();
	DECLARE_DYNCREATE(CWIN32DASMView)

// Attributes
public:
	CWIN32DASMDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CWIN32DASMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnDestroy();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
//	virtual void OnDraw(CDC* /*pDC*/);
public:
	CObArray* ParsedInstructionArray;
	CDisasmLibrary Instruction;
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // debug version in WIN32DASMView.cpp
inline CWIN32DASMDoc* CWIN32DASMView::GetDocument() const
   { return reinterpret_cast<CWIN32DASMDoc*>(m_pDocument); }
#endif

