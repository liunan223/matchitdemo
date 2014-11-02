// inClassGameView.h : interface of the CinClassGameView class
//

#include "Game.h"
#include "Animation.h"


#pragma once


class CinClassGameView : public CView
{
protected: // create from serialization only
	CinClassGameView();
	DECLARE_DYNCREATE(CinClassGameView)

// Attributes
public:
	CinClassGameDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CinClassGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

        // user defined variables and functions
public:
        

        CGame *GameObj;
        CAnimation *Animation;

        bool isFirst;

       // bool clickFlag; // determine whether it is the first point
        // true for first, false for second

        void DrawBackground();

public:
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnDestroy();
        afx_msg void OnTimer(UINT_PTR nIDEvent);
        afx_msg void OnAnimationStart();
        afx_msg void OnAnimationStop();
        afx_msg void OnAnimationPause();
        afx_msg void OnGameNewgame();
        afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in inClassGameView.cpp
inline CinClassGameDoc* CinClassGameView::GetDocument() const
   { return reinterpret_cast<CinClassGameDoc*>(m_pDocument); }
#endif

