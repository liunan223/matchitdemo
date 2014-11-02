// inClassGameDoc.h : interface of the CinClassGameDoc class
//


#pragma once


class CinClassGameDoc : public CDocument
{
protected: // create from serialization only
	CinClassGameDoc();
	DECLARE_DYNCREATE(CinClassGameDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CinClassGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


