// getsign.h : main header file for the GETSIGN application
//

#if !defined(AFX_GETSIGN_H__C40ADC4D_2C5A_4875_9AA9_401B8E549BBF__INCLUDED_)
#define AFX_GETSIGN_H__C40ADC4D_2C5A_4875_9AA9_401B8E549BBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGetsignApp:
// See getsign.cpp for the implementation of this class
//

class CGetsignApp : public CWinApp
{
public:
	CGetsignApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetsignApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGetsignApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETSIGN_H__C40ADC4D_2C5A_4875_9AA9_401B8E549BBF__INCLUDED_)
