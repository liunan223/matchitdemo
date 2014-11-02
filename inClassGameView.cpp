// inClassGameView.cpp : implementation of the CinClassGameView class
//

#include "stdafx.h"
#include "inClassGame.h"

#include "inClassGameDoc.h"
#include "inClassGameView.h"


#include <sys/timeb.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CinClassGameView

IMPLEMENT_DYNCREATE(CinClassGameView, CView)

BEGIN_MESSAGE_MAP(CinClassGameView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
        ON_WM_CREATE()
        ON_WM_DESTROY()
        ON_WM_TIMER()
        ON_COMMAND(ID_ANIMATION_START, &CinClassGameView::OnAnimationStart)
        ON_COMMAND(ID_ANIMATION_STOP, &CinClassGameView::OnAnimationStop)
        ON_COMMAND(ID_ANIMATION_PAUSE, &CinClassGameView::OnAnimationPause)
        ON_COMMAND(ID_GAME_NEWGAME, &CinClassGameView::OnGameNewgame)
        ON_WM_LBUTTONDOWN()
//        ON_COMMAND(ID_LEVEL_EASY, &CinClassGameView::OnLevelEasy)
//        ON_COMMAND(ID_LEVEL_ADVANCE, &CinClassGameView::OnLevelAdvance)
//        ON_COMMAND(ID_LEVEL_NORMAL, &CinClassGameView::OnLevelNormal)
END_MESSAGE_MAP()

// CinClassGameView construction/destruction

CinClassGameView::CinClassGameView()
{
	// TODO: add construction code here

}

CinClassGameView::~CinClassGameView()
{
}

BOOL CinClassGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CinClassGameView drawing

void CinClassGameView::OnDraw(CDC* /*pDC*/)
{
	CinClassGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
        DrawBackground();
        //GameObj->DrawAllBmp();
      
}


// CinClassGameView printing

BOOL CinClassGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CinClassGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CinClassGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CinClassGameView diagnostics

#ifdef _DEBUG
void CinClassGameView::AssertValid() const
{
	CView::AssertValid();
}

void CinClassGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CinClassGameDoc* CinClassGameView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CinClassGameDoc)));
	return (CinClassGameDoc*)m_pDocument;
}

void CinClassGameView::DrawBackground()
{
  CBitmap bmp;
  BITMAP bmpInfo;
  CDC mem;
  CClientDC dc(this);

  bmp.LoadBitmap(IDB_BM_BACKGROUND);
  bmp.GetBitmap(&bmpInfo);
  mem.CreateCompatibleDC(&dc);
  mem.SelectObject(&bmp);
  dc.BitBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &mem, 0, 0, SRCCOPY);
  bmp.DeleteObject();
}

#endif //_DEBUG


// CinClassGameView message handlers

int CinClassGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CView::OnCreate(lpCreateStruct) == -1)
    return -1;

  // TODO:  Add your specialized creation code here
  CDC *pDC = new CClientDC(this);
  GameObj = new CGame(pDC);
  GameObj->InitData();

  
  Animation = new CAnimation(pDC);
  Animation->Init();
  /*
  SetTimer(0, 10, NULL);
  */

  return 0;
}

void CinClassGameView::OnDestroy()
{
  CView::OnDestroy();

  // TODO: Add your message handler code here
  KillTimer(Animation->m_nTimer);
}

void CinClassGameView::OnTimer(UINT_PTR nIDEvent)
{
  // TODO: Add your message handler code here and/or call default
  Animation->MoveBmp();

  CView::OnTimer(nIDEvent);
}

void CinClassGameView::OnAnimationStart()
{
  // TODO: Add your command handler code here
  CDC *pDC = new CClientDC(this);
  Animation = new CAnimation(pDC);
  Animation->Init();

  Animation->isStarted = true;

  if (!Animation->isStoped)
  {
  //  CDC *pDC = new CClientDC(this);
    //Animation = new CAnimation(pDC);
    //Animation->Init();

    Animation->Cleanup();
    Animation->m_nTimer = SetTimer(1, 10, NULL);
  }
  else
    Animation->m_nTimer = SetTimer(1, 10, NULL);

}

void CinClassGameView::OnAnimationStop()
{
  // TODO: Add your command handler code here
  if (Animation->isStarted)
  {
    Animation->isStoped = true;
    OnDestroy();
    Animation->Cleanup();
  }
  else
    MessageBoxA(NULL,"Animation is not started!", "WARNING", MB_OK);
}

void CinClassGameView::OnAnimationPause()
{
  // TODO: Add your command handler code here
  if (Animation->isStarted)
  {
    Animation->isPaused = !Animation->isPaused;
    if (Animation->isPaused)
      KillTimer(Animation->m_nTimer);
    else
      SetTimer(Animation->m_nTimer, 10, NULL); 
  }
  else
    MessageBoxA(NULL,"Animation is not started!", "WARNING", MB_OK);
}

void CinClassGameView::OnGameNewgame()
{
  // TODO: Add your command handler code here
  GameObj->DrawAllBmp();
  GameObj->isStarted = true;

}

void CinClassGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    clickFlag = false;
    if (!clickFlag)
    {
        GameObj->m_curPosE = point;
        clickFlag = !clickFlag;
    }
    else
    {
        GameObj->m_curPosS = point;
        clickFlag = !clickFlag;
        GameObj->eraseAni();
    }
        //GameObj->eraseAni();

    CView::OnLButtonDown(nFlags, point);
}