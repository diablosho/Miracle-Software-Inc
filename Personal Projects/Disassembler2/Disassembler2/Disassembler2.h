
// Disassembler2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDisassembler2App:
// See Disassembler2.cpp for the implementation of this class
//

class CDisassembler2App : public CWinApp
{
public:
	CDisassembler2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDisassembler2App theApp;