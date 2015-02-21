
// player-sample-win32-mfc.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// sampleApp:
// See player-sample-win32-mfc.cpp for the implementation of this class
//

class sampleApp : public CWinApp
{
public:
	sampleApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern sampleApp theApp;