// HexToJavaByteDlg.h : header file
//

#if !defined(AFX_HEXTOJAVABYTEDLG_H__567774AD_A2F4_4280_8DD3_0674E1B96F02__INCLUDED_)
#define AFX_HEXTOJAVABYTEDLG_H__567774AD_A2F4_4280_8DD3_0674E1B96F02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHexToJavaByteDlg dialog

class CHexToJavaByteDlg : public CDialog
{
// Construction
public:
	int ReadFileToBuf(char *path, unsigned char **p);
	int WriteBufToFile(char *pPath, unsigned char *pbuf, int len);
	BOOL IsStrHexValues(CString str);
	void IsSendChipboard();
	CHexToJavaByteDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHexToJavaByteDlg)
	enum { IDD = IDD_HEXTOJAVABYTE_DIALOG };
	CEdit	m_editOut;
	CEdit	m_editIn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexToJavaByteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHexToJavaByteDlg)
	virtual BOOL OnInitDialog();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonShift();
	afx_msg void OnButtonDectohex();
	afx_msg void OnButtonUnzlib();
	afx_msg void OnButtonZlib();
	afx_msg void OnButtonNetbeanstohex();
	afx_msg void OnButtonGzip();
	afx_msg void OnButtonGunzip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXTOJAVABYTEDLG_H__567774AD_A2F4_4280_8DD3_0674E1B96F02__INCLUDED_)
