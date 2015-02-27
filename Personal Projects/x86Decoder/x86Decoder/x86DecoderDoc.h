
// x86DecoderDoc.h : interface of the Cx86DecoderDoc class
//


#pragma once
#include "x86DecoderSet.h"
#include "AddressingMethod.h"
#include "OperandType.h"
#include "16BitModRM.h"
#include "32BitModRM.h"
#include "SIB.h"


class Cx86DecoderDoc : public CDocument
{
protected: // create from serialization only
	Cx86DecoderDoc();
	DECLARE_DYNCREATE(Cx86DecoderDoc)

// Attributes
public:
	Cx86DecoderSet m_x86DecoderSet;
	CAddressingMethod m_AddressingMethod;
	COperandType m_OperandType;
	C16BitModRM m_16BitModRM;
	C32BitModRM m_32BitModRM;
	CSIB m_SIB;
	
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~Cx86DecoderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
