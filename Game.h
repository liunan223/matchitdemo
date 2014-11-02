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


    bool lineTest;

    CPoint m_curPosS, m_curPosE;

    int m_xc, m_yc;   // initial position
    int m_column, m_row;
    int m_width, m_height;
    int m_data[MAX_COL][MAX_ROW];

public:
    void InitData();
    void DrawAllBmp();
    //void Gameprocedure();
    bool Match();
    bool VerticalTest(int, int, int);
    bool HorizontalTest(int, int, int);
    void DrawBmp(int, int, CDC*);
    void drawBmp(CPoint);
    void drawBack(int, int, CDC*);
    void disorganize();
    bool pickUp(CPoint, bool);
    void eraseAni();
    bool isEmpty(CPoint);
    bool isEqual();
    void swap(int*, int*);
    void drawFrame(CPoint);
};
