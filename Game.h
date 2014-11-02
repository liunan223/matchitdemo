#pragma once

const int MAX_COL = 16;
const int MAX_ROW = 9;

class CGame
{
public:
    CGame(CDC* pDC);
    ~CGame(void);

public:
    CDC* m_pDC;
    CDC memBkg, memAni;

    bool isStarted;
    bool isPaused;

    bool isFirst;
    bool lineTest;

    CPoint m_curPosS, m_curPosE;

    int m_xc, m_yc;   // initial position
    int m_column, m_row;
    int m_width, m_height;
    int m_data[MAX_COL][MAX_ROW];

    int x, y;

public:
    void InitData();
    void DrawAllBmp();
    void Gameprocedure();
    bool Match();
    bool VerticalTest();
    bool HorizontalTest();
    void DrawBmp(int, int, CDC*);
    void Disorganize();
    bool pickUp(CPoint);
    void eraseAni();
    bool isEmpty(CPoint);
    bool isEqual();
};
