// HexToJavaByte.h : main header file for the HEXTOJAVABYTE application
//

#if !defined(AFX_HEXTOJAVABYTE_H__274721A8_5D67_45F5_8B59_81500253546C__INCLUDED_)
#define AFX_HEXTOJAVABYTE_H__274721A8_5D67_45F5_8B59_81500253546C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHexToJavaByteApp:
// See HexToJavaByte.cpp for the implementation of this class
//

class CHexToJavaByteApp : public CWinApp
{
public:
	CHexToJavaByteApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexToJavaByteApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHexToJavaByteApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXTOJAVABYTE_H__274721A8_5D67_45F5_8B59_81500253546C__INCLUDED_)
