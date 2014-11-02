#include "StdAfx.h"
#include "Animation.h"
#include "resource.h"

CAnimation::CAnimation(CDC* pDC)
{
    m_pDC = pDC;
    m_x = 200;
    m_y = 200; 
    m_no = 0; m_count = 30;
    m_stepX = 2; m_stepY = 2;

    isPaused = false;
    isStoped = false;
    isStarted = false;

    m_nTimer = 0;
}

CAnimation::~CAnimation(void)
{
    delete m_pDC;
}

void CAnimation::Init()
{
    CBitmap bmp;
    BITMAP bmpInfo;

    // background
    bmp.LoadBitmap(IDB_BM_BACKGROUND);
    bmp.GetBitmap(&bmpInfo);
    memBkg.CreateCompatibleDC(m_pDC);
    memBkg.SelectObject(&bmp);
    bmp.DeleteObject();
    m_Width = bmpInfo.bmWidth;
    m_Height = bmpInfo.bmHeight;

    // mask
    bmp.LoadBitmap(IDB_BM_COINB);
    memMask.CreateCompatibleDC(m_pDC);
    memMask.SelectObject(&bmp);
    bmp.DeleteObject();

    // coin
    bmp.LoadBitmap(IDB_BM_COIN);
    memBmp.CreateCompatibleDC(m_pDC);
    memBmp.SelectObject(&bmp);
    bmp.GetBitmap(&bmpInfo);
    bmp.DeleteObject();
    m_cx = bmpInfo.bmWidth;
    m_cy = bmpInfo.bmHeight / m_count;
}

void CAnimation::MoveBmp()
{
    m_no = (m_no + 1) % m_count;
    m_pDC->BitBlt(m_x, m_y, m_cx, m_cy, &memBkg, m_x, m_y, SRCCOPY);

    NextStep();

    m_pDC->BitBlt(m_x, m_y, m_cx - 2, m_cy - 2, &memMask, 0, m_no*m_cy, SRCAND);

    m_pDC->BitBlt(m_x, m_y, m_cx - 2, m_cy - 2, &memBmp, 0, m_no*m_cy, SRCPAINT);
}

void CAnimation::NextStep()
{
    m_x += m_stepX;
    m_y += m_stepY;

    if ((m_x >= m_Width-m_cx) || (m_x <= -1))
    {
        m_stepX *= -1;
        m_x += m_stepX;
    }

    if ((m_y >= m_Height-m_cy) || (m_y <= -1))
    {
        m_stepY *= -1;
        m_y += m_stepY;
    }
}

void CAnimation::Cleanup()
{
    m_pDC->BitBlt(m_x, m_y, m_cx, m_cy, &memBkg, m_x, m_y, SRCCOPY);
}
