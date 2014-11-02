#include "StdAfx.h"
#include "Game.h"
#include "resource.h" 

CGame::CGame(CDC* pDC)
{
    m_pDC = pDC; 
    m_xc = 70, m_yc = 60;
    m_column = MAX_COL, m_row = MAX_ROW;
    m_width = 40, m_height = 50;

    isStarted = false;
    isPaused = false;
    m_curPosS.x = m_curPosS.y = 0;
    m_curPosE.x = m_curPosE.y = 0;

    isFirst = true;

    memset(m_data, -1, sizeof(m_data));

    CBitmap bmp;
    BITMAP bmpInfo;

    // background
    bmp.LoadBitmap(IDB_BM_BACKGROUND);
    bmp.GetBitmap(&bmpInfo);
    memBkg.CreateCompatibleDC(m_pDC);
    memBkg.SelectObject(&bmp);
    bmp.DeleteObject();

    bmp.LoadBitmap(IDB_BM_CHARA);
    bmp.GetBitmap(&bmpInfo);
    memAni.CreateCompatibleDC(m_pDC);
    memAni.SelectObject(&bmp);
    bmp.DeleteObject();
}

CGame::~CGame(void)
{
    delete m_pDC;
}

/*
 * Description:
 */
void CGame::InitData()
{
    int i, j;
    for (i = 0; i < MAX_COL; i++)
        for (j = 0; j < MAX_ROW; j++)
            m_data[i][j] = (i*MAX_ROW + j)/4;
    Disorganize();
}

/*
 * Description:
 */
void CGame::DrawAllBmp()
{
    for (int i = 0; i < m_column; i++)
        for (int j = 0; j < m_row; j++)
            if (m_data[i][j] != -1)
                DrawBmp(i, j, &memAni);
}
/*
 * Description:
 */
void CGame::DrawBmp(int col, int row, CDC* mem)
{
    m_pDC->BitBlt(m_xc + col*m_width, m_yc + row*m_height,
        m_width, m_height, mem, m_width*m_data[col][row], 0, SRCCOPY);
}

/*
 * Description: 
 */
void CGame::Disorganize()
{
    for (int k = 0; k < 2000; k++)
    {
        int i0 = rand()%MAX_COL, i1 = rand()%MAX_COL;
        int j0 = rand()%MAX_ROW, j1 = rand()%MAX_ROW;
        int tmp;
        tmp = m_data[i0][j0];
        m_data[i0][j0] = m_data[i1][j1];
        m_data[i1][j1] = tmp;
    }
}

void CGame::eraseAni()
{
    int col1 = (m_curPosS.x - m_xc)/m_width;
    int col2 = (m_curPosE.x - m_xc)/m_width;
    int row1 = (m_curPosS.y - m_yc)/m_height;
    int row2 = (m_curPosE.y - m_yc)/m_height;
    DrawBmp(col1, row1, &memBkg);
    DrawBmp(col2, row2, &memBkg);
}
bool CGame::isEmpty(CPoint p)
{
    if (m_data[(p.x-m_xc)/m_width][(p.y-m_yc)/m_height] == -1)
        return true;
    else
        return false;
}

bool CGame::isEqual()
{
    if (m_curPosE == m_curPosS)
        return true;
    else
        return false;
}
bool CGame::pickUp(CPoint p)
{
    if (!isEmpty(p))
    {
        if (isFirst)
        {
            m_curPosS = p;
            isFirst = !isFirst;
        }
        else 
        {
            m_curPosE = p;
            isFirst = !isFirst;
        }
    }
    return true;
}

void CGame::Gameprocedure()
{
}


bool CGame::Match()
{
    return true;
}

bool CGame::VerticalTest()
{
    return true;
}

bool CGame::HorizontalTest()
{
    return true;
}
