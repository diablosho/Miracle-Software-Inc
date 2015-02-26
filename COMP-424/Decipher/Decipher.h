
// Decipher.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDecipherApp:
// See Decipher.cpp for the implementation of this class
//

class CDecipherApp : public CWinApp
{
public:
	CDecipherApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDecipherApp theApp;