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
    



    //memset(m_data, -1, sizeof(m_data));

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
    disorganize();
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

void CGame::drawBack(int col, int row, CDC* mem)
{
    m_pDC->BitBlt(m_xc + col*m_width, m_yc+row*m_height,
        m_width, m_height, mem, m_xc+m_width*col, m_yc+m_width*row, SRCCOPY);
}

/*
 * Description: 
 */
void CGame::disorganize()
{
    for (int k = 0; k < 4000; k++)
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
    int row1 = (m_curPosS.y - m_yc)/m_height;
    int col2 = (m_curPosE.x - m_xc)/m_width;
    int row2 = (m_curPosE.y - m_yc)/m_height;
    drawBack(col1, row1, &memBkg);
    drawBack(col2, row2, &memBkg);
    m_curPosS.x = m_curPosS.y = 0;
    m_curPosE.x = m_curPosE.y = 0;
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
bool CGame::pickUp(CPoint p, bool flag)
{

    const int MAX_WIDTH = MAX_COL * m_width;
    const int MAX_HEIGHT = MAX_ROW * m_height;

    if ((p.x >= m_xc) && (p.x <= m_xc+MAX_WIDTH) && (p.y >= m_yc) && (p.y <= m_yc+MAX_HEIGHT))
    {
        switch (flag)
        {
        case true:
            m_curPosS = p;
            break;
        case false:
            m_curPosE = p;
            break;
        }
        return true;
    }
    else
        return false;
}


bool CGame::Match()
{
    int col1 = (m_curPosS.x - m_xc) / m_width;
    int row1 = (m_curPosS.y - m_yc) / m_height;
    int col2 = (m_curPosE.x - m_xc) / m_width;
    int row2 = (m_curPosE.y - m_yc) / m_height;

    bool isMatch = false;

    if (m_data[col1][row1] == m_data[col2][row2] && (!isEqual()))
    {
        int no1 = m_data[col1][row1];
        int no2 = m_data[col2][row2];
        
        m_data[col1][row1] = m_data[col2][row2] = -1;

        for (int x = 0; (x <= MAX_COL) && (!isMatch); x++)
        {
            isMatch = HorizontalTest(col1, x, row1) && \
                VerticalTest(x, row1, row2) && \
                HorizontalTest(x, col2, row2);
        }
        for (int y = 0; (y <= MAX_ROW) && (!isMatch); y++)
        {
            isMatch = VerticalTest(col1, row1, y) && \
                HorizontalTest(col1, col2, y) && \
                VerticalTest(col2, y, row2);
        }
        m_data[col1][row1] = no1;
        m_data[col2][row2] = no2;
        return isMatch;
    }
    else
        return false;
}

bool CGame::VerticalTest(int x, int y0, int y1)
{
    bool isOk = true ;

    if (y0>y1) swap(&y0, &y1);
    for(int y=y0; (y<=y1) && isOk; y++)
        isOk = (m_data[x][y] == -1) ;
    return isOk ;
}

bool CGame::HorizontalTest(int x0, int x1, int y)
{
    bool isOk = true ;

    if (x0 > x1) swap(&x0, &x1);
    for(int x = x0; (x <= x1) && isOk; x++)
        isOk = (m_data[x][y] == -1) ;
    return isOk ;
}


void CGame::swap(int *x, int *y)
{
    int tmp = *x ;
    *x = *y ;
    *y = tmp ;
}

void CGame::drawFrame(CPoint p)
{
    int col = (p.x-m_xc) / m_width;
    int row = (p.y-m_yc) / m_height;
    m_pDC->SelectStockObject(NULL_BRUSH);
    m_pDC->Rectangle(m_xc+col*m_width, m_yc+row*m_height, \
        m_xc+(col+1)*m_width, m_yc+(row+1)*m_height);
}

void CGame::drawBmp(CPoint p)
{
    int col = (p.x-m_xc) / m_width;
    int row = (p.y-m_yc) / m_height;
    DrawBmp(col, row, &memAni);
}
