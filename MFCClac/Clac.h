#if !defined(AFX_CLAC_H__E3B2EA12_859E_4432_8583_52AE08710CAC__INCLUDED_)
#define AFX_CLAC_H__E3B2EA12_859E_4432_8583_52AE08710CAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Clac.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClac dialog

class CClac : public CDialog
{
// Construction
public:
	UINT64 strtoul64(const char *nptr, char **endptr, int base);
	CString Operation(CString str1, CString str2, int nType);
	CString FiltHex(CString &str);
	void Clear();
	void Init();
	CClac(CWnd* pParent = NULL);   // standard constructor
	CClac(CClac &b);
	void SetValues(CClac &b)
	{
		this->m_unsigned=b.m_unsigned;
		this->m_arith=b.m_arith;
		this->m_AddSum=b.m_AddSum;
		this->m_Add1=b.m_Add1;
		this->m_Add2=b.m_Add2;
		this->m_AndSum=b.m_AndSum;
		this->m_And1=b.m_And1;
		this->m_And2=b.m_And2;
		this->m_Dec=b.m_Dec;
		this->m_DivSum=b.m_DivSum;
		this->m_Div1=b.m_Div1;
		this->m_Div2=b.m_Div2;
		this->m_Hex=b.m_Hex;
		this->m_ModSum=b.m_ModSum;
		this->m_Mod1=b.m_Mod1;
		this->m_Mod2=b.m_Mod2;
		this->m_MulSum=b.m_MulSum;
		this->m_Mul1=b.m_Mul1;
		this->m_Mul2=b.m_Mul2;
		this->m_Not=b.m_Not;
		this->m_NotSum=b.m_NotSum;
		this->m_OrSum=b.m_OrSum;
		this->m_Or1=b.m_Or1;
		this->m_Or2=b.m_Or2;
		this->m_ShlSum=b.m_ShlSum;
		this->m_Shl1=b.m_Shl1;
		this->m_Shl2=b.m_Shl2;
		this->m_ShrSum=b.m_ShrSum;
		this->m_Shr1=b.m_Shr1;
		this->m_Shr2=b.m_Shr2;
		this->m_SubSum=b.m_SubSum;
		this->m_Sub1=b.m_Sub1;
		this->m_Sub2=b.m_Sub2;
		this->m_XorSum=b.m_XorSum;
		this->m_Xor1=b.m_Xor1;
		this->m_Xor2=b.m_Xor2;
	}
// Dialog Data
	//{{AFX_DATA(CClac)
	enum { IDD = IDD_DIALOG };
	int		m_unsigned;
	int		m_arith;
	CString	m_AddSum;
	CString	m_Add1;
	CString	m_Add2;
	CString	m_AndSum;
	CString	m_And1;
	CString	m_And2;
	CString	m_Dec;
	CString	m_DivSum;
	CString	m_Div1;
	CString	m_Div2;
	CString	m_Hex;
	CString	m_ModSum;
	CString	m_Mod1;
	CString	m_Mod2;
	CString	m_MulSum;
	CString	m_Mul1;
	CString	m_Mul2;
	CString	m_Not;
	CString	m_NotSum;
	CString	m_OrSum;
	CString	m_Or1;
	CString	m_Or2;
	CString	m_ShlSum;
	CString	m_Shl1;
	CString	m_Shl2;
	CString	m_ShrSum;
	CString	m_Shr1;
	CString	m_Shr2;
	CString	m_SubSum;
	CString	m_Sub1;
	CString	m_Sub2;
	CString	m_XorSum;
	CString	m_Xor1;
	CString	m_Xor2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClac)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClac)
	afx_msg void OnRadioArith();
	afx_msg void OnRadio2();
	afx_msg void OnChangeEditAdd1();
	afx_msg void OnChangeEditAdd2();
	afx_msg void OnChangeEditSub1();
	afx_msg void OnChangeEditSub2();
	afx_msg void OnChangeEditMul1();
	afx_msg void OnChangeEditMul2();
	afx_msg void OnChangeEditDiv1();
	afx_msg void OnChangeEditDiv2();
	afx_msg void OnChangeEditMod1();
	afx_msg void OnChangeEditMod2();
	afx_msg void OnChangeEditXor1();
	afx_msg void OnChangeEditXor2();
	afx_msg void OnChangeEditAnd1();
	afx_msg void OnChangeEditAnd2();
	afx_msg void OnChangeEditOr1();
	afx_msg void OnChangeEditOr2();
	afx_msg void OnChangeEditShl1();
	afx_msg void OnChangeEditShl2();
	afx_msg void OnChangeEditShr1();
	afx_msg void OnChangeEditShr2();
	afx_msg void OnChangeEditNot();
	afx_msg void OnChangeEditHex();
	afx_msg void OnChangeEditDec();
	afx_msg void OnRadioUnsigned();
	afx_msg void OnRadioSigned();
	afx_msg void OnButtonAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLAC_H__E3B2EA12_859E_4432_8583_52AE08710CAC__INCLUDED_)
