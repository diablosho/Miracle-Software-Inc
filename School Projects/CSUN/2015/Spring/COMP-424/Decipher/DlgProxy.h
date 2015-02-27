
// DlgProxy.h: header file
//

#pragma once

class CDecipherDlg;


// CDecipherDlgAutoProxy command target

class CDecipherDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CDecipherDlgAutoProxy)

	CDecipherDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CDecipherDlg* m_pDialog;

// Operations
public:

// Overrides
	public:
	virtual void OnFinalRelease();

// Implementation
protected:
	virtual ~CDecipherDlgAutoProxy();

	// Generated message map functions

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CDecipherDlgAutoProxy)

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

