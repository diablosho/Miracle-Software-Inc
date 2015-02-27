// spiro.h : main header file for the SPIRO application
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#if !defined(AFX_SPIRO_H__4417CF86_AFA9_11D1_AB61_D9B80632F018__INCLUDED_)
#define AFX_SPIRO_H__4417CF86_AFA9_11D1_AB61_D9B80632F018__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpiroApp:
// See spiro.cpp for the implementation of this class
//

class CSpiroApp : public CWinApp
{
public:
	HCURSOR m_cursorWheel;
	HCURSOR m_cursorRing;
	CImageList	m_imageList;  // use for drag operations

	CSpiroApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpiroApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	void	SetLandscape();

	//{{AFX_MSG(CSpiroApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#define GetApp() ((CSpiroApp*)AfxGetApp())

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPIRO_H__4417CF86_AFA9_11D1_AB61_D9B80632F018__INCLUDED_)
