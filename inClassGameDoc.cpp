// inClassGameDoc.cpp : implementation of the CinClassGameDoc class
//

#include "stdafx.h"
#include "inClassGame.h"

#include "inClassGameDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CinClassGameDoc

IMPLEMENT_DYNCREATE(CinClassGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CinClassGameDoc, CDocument)
END_MESSAGE_MAP()


// CinClassGameDoc construction/destruction

CinClassGameDoc::CinClassGameDoc()
{
	// TODO: add one-time construction code here

}

CinClassGameDoc::~CinClassGameDoc()
{
}

BOOL CinClassGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CinClassGameDoc serialization

void CinClassGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CinClassGameDoc diagnostics

#ifdef _DEBUG
void CinClassGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CinClassGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CinClassGameDoc commands
