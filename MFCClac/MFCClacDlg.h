// MFCClacDlg.h : header file
//

#if !defined(AFX_MFCCLACDLG_H__4B6700D3_F966_4F6F_A2AB_D9FADA2E62E3__INCLUDED_)
#define AFX_MFCCLACDLG_H__4B6700D3_F966_4F6F_A2AB_D9FADA2E62E3__INCLUDED_

#include "Clac.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
/////////////////////////////////////////////////////////////////////////////
// CMFCClacDlg dialog

class CMFCClacDlg : public CDialog
{
// Construction
public:
	int m_nSel;
	CClac m_ClacDlg;
	CMFCClacDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMFCClacDlg)
	enum { IDD = IDD_MFCCLAC_DIALOG };
	CTabCtrl	m_table;
	CArray <CClac*,CClac *> m_vClacs;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCClacDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFCClacDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemoryTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetobjectTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCCLACDLG_H__4B6700D3_F966_4F6F_A2AB_D9FADA2E62E3__INCLUDED_)
