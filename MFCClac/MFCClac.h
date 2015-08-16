// MFCClac.h : main header file for the MFCCLAC application
//

#if !defined(AFX_MFCCLAC_H__E5B2B0B9_9C8F_45E5_AEB3_7D01EB65009C__INCLUDED_)
#define AFX_MFCCLAC_H__E5B2B0B9_9C8F_45E5_AEB3_7D01EB65009C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCClacApp:
// See MFCClac.cpp for the implementation of this class
//

class CMFCClacApp : public CWinApp
{
public:
	CMFCClacApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCClacApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFCClacApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCCLAC_H__E5B2B0B9_9C8F_45E5_AEB3_7D01EB65009C__INCLUDED_)
