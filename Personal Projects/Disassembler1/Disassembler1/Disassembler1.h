
// Disassembler1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDisassembler1App:
// See Disassembler1.cpp for the implementation of this class
//

class CDisassembler1App : public CWinApp
{
public:
	CDisassembler1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDisassembler1App theApp;