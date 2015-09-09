// getsignDlg.h : header file
//

#if !defined(AFX_GETSIGNDLG_H__5E6FAB44_AD1E_44C4_BB08_AB2A7F447A5B__INCLUDED_)
#define AFX_GETSIGNDLG_H__5E6FAB44_AD1E_44C4_BB08_AB2A7F447A5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGetsignDlg dialog

class CGetsignDlg : public CDialog
{
// Construction
public:
	BOOL ShowData(char *path);
	unsigned int hashCode(unsigned char *pbuf, int len);
	int getApkSign(char *ApkPath, unsigned char **ppOut);
	CGetsignDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGetsignDlg)
	enum { IDD = IDD_GETSIGN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetsignDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGetsignDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonLl();
	afx_msg void OnChangeEditSign();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETSIGNDLG_H__5E6FAB44_AD1E_44C4_BB08_AB2A7F447A5B__INCLUDED_)
