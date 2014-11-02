//#pragma once

#ifndef _CANIMATION_H_
#define _CANIMATION_H_


class CAnimation
{
public:
  CAnimation(CDC* pDC);
  ~CAnimation(void);

public:
  CDC *m_pDC;
  CDC memBkg, memMask, memBmp;

  bool isPaused;
  bool isStoped;
  bool isStarted;
  int  m_nTimer;

  int m_cx, m_cy;         // coin's position
  int m_Width, m_Height;  // background's height and width
  int m_x, m_y;           // animation coordination
  int m_stepX, m_stepY;   // coin move stride
  int m_no, m_count;      // tag of animation

public:
  void Init();
  void MoveBmp();
  void NextStep();
  void Cleanup();
};

#endif
