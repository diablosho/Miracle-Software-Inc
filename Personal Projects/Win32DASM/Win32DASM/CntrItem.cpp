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

// CntrItem.cpp : implementation of the CWin32DASMCntrItem class
//

#include "stdafx.h"
#include "Win32DASM.h"

#include "Win32DASMDoc.h"
#include "Win32DASMView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWin32DASMCntrItem implementation

IMPLEMENT_SERIAL(CWin32DASMCntrItem, CRichEditCntrItem, 0)

CWin32DASMCntrItem::CWin32DASMCntrItem(REOBJECT* preo, CWin32DASMDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
}

CWin32DASMCntrItem::~CWin32DASMCntrItem()
{
	// TODO: add cleanup code here
}


// CWin32DASMCntrItem diagnostics

#ifdef _DEBUG
void CWin32DASMCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CWin32DASMCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

