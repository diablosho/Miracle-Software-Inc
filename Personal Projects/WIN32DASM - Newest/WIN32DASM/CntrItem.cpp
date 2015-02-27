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

// CntrItem.cpp : implementation of the CWIN32DASMCntrItem class
//

#include "stdafx.h"
#include "WIN32DASM.h"

#include "WIN32DASMDoc.h"
#include "WIN32DASMView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWIN32DASMCntrItem implementation

IMPLEMENT_SERIAL(CWIN32DASMCntrItem, CRichEditCntrItem, 0)

CWIN32DASMCntrItem::CWIN32DASMCntrItem(REOBJECT* preo, CWIN32DASMDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
}

CWIN32DASMCntrItem::~CWIN32DASMCntrItem()
{
	// TODO: add cleanup code here
}


// CWIN32DASMCntrItem diagnostics

#ifdef _DEBUG
void CWIN32DASMCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CWIN32DASMCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

