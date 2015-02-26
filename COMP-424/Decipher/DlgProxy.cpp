
// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "Decipher.h"
#include "DlgProxy.h"
#include "DecipherDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDecipherDlgAutoProxy

IMPLEMENT_DYNCREATE(CDecipherDlgAutoProxy, CCmdTarget)

CDecipherDlgAutoProxy::CDecipherDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CDecipherDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CDecipherDlg)))
		{
			m_pDialog = reinterpret_cast<CDecipherDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CDecipherDlgAutoProxy::~CDecipherDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CDecipherDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CDecipherDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDecipherDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_IDecipher to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {7A535ACA-EEB6-4A90-89B8-30F9BB0BC787}
static const IID IID_IDecipher =
{ 0x7A535ACA, 0xEEB6, 0x4A90, { 0x89, 0xB8, 0x30, 0xF9, 0xBB, 0xB, 0xC7, 0x87 } };

BEGIN_INTERFACE_MAP(CDecipherDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CDecipherDlgAutoProxy, IID_IDecipher, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {166E0410-AEF9-4E8C-BEB4-AA845327888E}
IMPLEMENT_OLECREATE2(CDecipherDlgAutoProxy, "Decipher.Application", 0x166e0410, 0xaef9, 0x4e8c, 0xbe, 0xb4, 0xaa, 0x84, 0x53, 0x27, 0x88, 0x8e)


// CDecipherDlgAutoProxy message handlers
