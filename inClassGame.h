// inClassGame.h : main header file for the inClassGame application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CinClassGameApp:
// See inClassGame.cpp for the implementation of this class
//

class CinClassGameApp : public CWinApp
{
public:
	CinClassGameApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CinClassGameApp theApp;