// Clac.cpp : implementation file
//

#include "stdafx.h"
#include "MFCClac.h"
#include "Clac.h"
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClac dialog

#define MYADD	1
#define MYSUB	2
#define MYMUL	3
#define MYDIV	4
#define MYMOD	5
#define MYXOR	6
#define MYAND	7
#define MYOR	8
#define MYSHL	9
#define MYSHR	10
#define MYNOT	11



CClac::CClac(CWnd* pParent /*=NULL*/)
	: CDialog(CClac::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClac)
	m_unsigned = -1;
	m_arith = -1;
	m_AddSum = _T("");
	m_Add1 = _T("");
	m_Add2 = _T("");
	m_AndSum = _T("");
	m_And1 = _T("");
	m_And2 = _T("");
	m_Dec = _T("");
	m_DivSum = _T("");
	m_Div1 = _T("");
	m_Div2 = _T("");
	m_Hex = _T("");
	m_ModSum = _T("");
	m_Mod1 = _T("");
	m_Mod2 = _T("");
	m_MulSum = _T("");
	m_Mul1 = _T("");
	m_Mul2 = _T("");
	m_Not = _T("");
	m_NotSum = _T("");
	m_OrSum = _T("");
	m_Or1 = _T("");
	m_Or2 = _T("");
	m_ShlSum = _T("");
	m_Shl1 = _T("");
	m_Shl2 = _T("");
	m_ShrSum = _T("");
	m_Shr1 = _T("");
	m_Shr2 = _T("");
	m_SubSum = _T("");
	m_Sub1 = _T("");
	m_Sub2 = _T("");
	m_XorSum = _T("");
	m_Xor1 = _T("");
	m_Xor2 = _T("");
	//}}AFX_DATA_INIT
	Init();
}
CClac::CClac(CClac &b)
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

void CClac::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClac)
	DDX_Radio(pDX, IDC_RADIO_UNSIGNED, m_unsigned);
	DDX_Radio(pDX, IDC_RADIO_ARITH, m_arith);
	DDX_Text(pDX, IDC_EDIT_ADD_SUM, m_AddSum);
	DDX_Text(pDX, IDC_EDIT_ADD1, m_Add1);
	DDX_Text(pDX, IDC_EDIT_ADD2, m_Add2);
	DDX_Text(pDX, IDC_EDIT_AND_SUM, m_AndSum);
	DDX_Text(pDX, IDC_EDIT_AND1, m_And1);
	DDX_Text(pDX, IDC_EDIT_AND2, m_And2);
	DDX_Text(pDX, IDC_EDIT_DEC, m_Dec);
	DDX_Text(pDX, IDC_EDIT_DIV_SUM, m_DivSum);
	DDX_Text(pDX, IDC_EDIT_DIV1, m_Div1);
	DDX_Text(pDX, IDC_EDIT_DIV2, m_Div2);
	DDX_Text(pDX, IDC_EDIT_HEX, m_Hex);
	DDX_Text(pDX, IDC_EDIT_MOD_SUM, m_ModSum);
	DDX_Text(pDX, IDC_EDIT_MOD1, m_Mod1);
	DDX_Text(pDX, IDC_EDIT_MOD2, m_Mod2);
	DDX_Text(pDX, IDC_EDIT_MUL_SUM, m_MulSum);
	DDX_Text(pDX, IDC_EDIT_MUL1, m_Mul1);
	DDX_Text(pDX, IDC_EDIT_MUL2, m_Mul2);
	DDX_Text(pDX, IDC_EDIT_NOT, m_Not);
	DDX_Text(pDX, IDC_EDIT_NOT_SUM, m_NotSum);
	DDX_Text(pDX, IDC_EDIT_OR_SUM, m_OrSum);
	DDX_Text(pDX, IDC_EDIT_OR1, m_Or1);
	DDX_Text(pDX, IDC_EDIT_OR2, m_Or2);
	DDX_Text(pDX, IDC_EDIT_SHL_SUM, m_ShlSum);
	DDX_Text(pDX, IDC_EDIT_SHL1, m_Shl1);
	DDX_Text(pDX, IDC_EDIT_SHL2, m_Shl2);
	DDX_Text(pDX, IDC_EDIT_SHR_SUM, m_ShrSum);
	DDX_Text(pDX, IDC_EDIT_SHR1, m_Shr1);
	DDX_Text(pDX, IDC_EDIT_SHR2, m_Shr2);
	DDX_Text(pDX, IDC_EDIT_SUB_SUM, m_SubSum);
	DDX_Text(pDX, IDC_EDIT_SUB1, m_Sub1);
	DDX_Text(pDX, IDC_EDIT_SUB2, m_Sub2);
	DDX_Text(pDX, IDC_EDIT_XOR_SUM, m_XorSum);
	DDX_Text(pDX, IDC_EDIT_XOR1, m_Xor1);
	DDX_Text(pDX, IDC_EDIT_XOR2, m_Xor2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClac, CDialog)
	//{{AFX_MSG_MAP(CClac)
	ON_BN_CLICKED(IDC_RADIO_ARITH, OnRadioArith)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_EN_CHANGE(IDC_EDIT_ADD1, OnChangeEditAdd1)
	ON_EN_CHANGE(IDC_EDIT_ADD2, OnChangeEditAdd2)
	ON_EN_CHANGE(IDC_EDIT_SUB1, OnChangeEditSub1)
	ON_EN_CHANGE(IDC_EDIT_SUB2, OnChangeEditSub2)
	ON_EN_CHANGE(IDC_EDIT_MUL1, OnChangeEditMul1)
	ON_EN_CHANGE(IDC_EDIT_MUL2, OnChangeEditMul2)
	ON_EN_CHANGE(IDC_EDIT_DIV1, OnChangeEditDiv1)
	ON_EN_CHANGE(IDC_EDIT_DIV2, OnChangeEditDiv2)
	ON_EN_CHANGE(IDC_EDIT_MOD1, OnChangeEditMod1)
	ON_EN_CHANGE(IDC_EDIT_MOD2, OnChangeEditMod2)
	ON_EN_CHANGE(IDC_EDIT_XOR1, OnChangeEditXor1)
	ON_EN_CHANGE(IDC_EDIT_XOR2, OnChangeEditXor2)
	ON_EN_CHANGE(IDC_EDIT_AND1, OnChangeEditAnd1)
	ON_EN_CHANGE(IDC_EDIT_AND2, OnChangeEditAnd2)
	ON_EN_CHANGE(IDC_EDIT_OR1, OnChangeEditOr1)
	ON_EN_CHANGE(IDC_EDIT_OR2, OnChangeEditOr2)
	ON_EN_CHANGE(IDC_EDIT_SHL1, OnChangeEditShl1)
	ON_EN_CHANGE(IDC_EDIT_SHL2, OnChangeEditShl2)
	ON_EN_CHANGE(IDC_EDIT_SHR1, OnChangeEditShr1)
	ON_EN_CHANGE(IDC_EDIT_SHR2, OnChangeEditShr2)
	ON_EN_CHANGE(IDC_EDIT_NOT, OnChangeEditNot)
	ON_EN_CHANGE(IDC_EDIT_HEX, OnChangeEditHex)
	ON_EN_CHANGE(IDC_EDIT_DEC, OnChangeEditDec)
	ON_BN_CLICKED(IDC_RADIO_UNSIGNED, OnRadioUnsigned)
	ON_BN_CLICKED(IDC_RADIO_SIGNED, OnRadioSigned)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClac message handlers

void CClac::Init()
{
	m_unsigned = 0;
	m_arith = 1;
}

void CClac::OnRadioArith() 
{
	// TODO: Add your control notification handler code here
	if(m_arith == 0)
	{
		Clear();
	}
	m_arith = 0;
	
	UpdateData(FALSE);
}

void CClac::Clear()
{
	m_AddSum = _T("");
	m_Add1 = _T("");
	m_Add2 = _T("");
	m_AndSum = _T("");
	m_And1 = _T("");
	m_And2 = _T("");
	m_Dec = _T("");
	m_DivSum = _T("");
	m_Div1 = _T("");
	m_Div2 = _T("");
	m_Hex = _T("");
	m_ModSum = _T("");
	m_Mod1 = _T("");
	m_Mod2 = _T("");
	m_MulSum = _T("");
	m_Mul1 = _T("");
	m_Mul2 = _T("");
	m_Not = _T("");
	m_NotSum = _T("");
	m_OrSum = _T("");
	m_Or1 = _T("");
	m_Or2 = _T("");
	m_ShlSum = _T("");
	m_Shl1 = _T("");
	m_Shl2 = _T("");
	m_ShrSum = _T("");
	m_Shr1 = _T("");
	m_Shr2 = _T("");
	m_SubSum = _T("");
	m_Sub1 = _T("");
	m_Sub2 = _T("");
	m_XorSum = _T("");
	m_Xor1 = _T("");
	m_Xor2 = _T("");
	m_unsigned = 0;
	m_arith = 1;
	UpdateData(FALSE);
}

CString CClac::FiltHex(CString &str)
{
	CString strTmp = str;
	if(strTmp.Find("0x") >= 0)
	{
		str = strTmp.GetBuffer(0) + strTmp.Find("0x") + 2;
	}
	return str;
}

void CClac::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	
	if(m_arith == 1)
	{
		Clear();
	}
	m_arith = 1;
	UpdateData(FALSE);
}



CString CClac::Operation(CString str1, CString str2, int nType)
{
	CString strRet = "";
	str1.TrimLeft(" ");
	str2.TrimLeft(" ");
	str1.TrimRight(" ");
	str2.TrimRight(" ");
	if(!str1.GetLength() || !str2.GetLength())
	{
		return strRet;
	}
	CString strFormat= "%I64u";
	int nStrType = 10;
	if(m_arith)
	{
		FiltHex(str1);
		FiltHex(str2);
		nStrType = 16;
		strFormat = "%llX";
	}
	try
	{
		switch (nType)
		{
		case MYADD:
			strRet.Format(strFormat, strtoul64(str1.GetBuffer(0), NULL, nStrType) + strtoul64(str2.GetBuffer(0), NULL, nStrType));
			break;
		case MYSUB:
			strRet.Format(strFormat, strtoul64(str1.GetBuffer(0), NULL, nStrType) - strtoul64(str2.GetBuffer(0), NULL, nStrType));
			break;
		case MYMUL:
			strRet.Format(strFormat, strtoul64(str1.GetBuffer(0), NULL, nStrType) * strtoul64(str2.GetBuffer(0), NULL, nStrType));
			break;
		case MYDIV:
			if(strtoul64(str2.GetBuffer(0), NULL, nStrType) > 0)
			{
				strRet.Format(strFormat, strtoul64(str1.GetBuffer(0), NULL, nStrType) / strtoul64(str2.GetBuffer(0), NULL, nStrType));
			}
			else
			{
				strRet = "Error Div Zero";
			}
			break;
		case MYMOD:
			if(strtoul64(str2.GetBuffer(0), NULL, nStrType) > 0)
			{
				strRet.Format(strFormat, strtoul64(str1.GetBuffer(0), NULL, nStrType) % strtoul64(str2.GetBuffer(0), NULL, nStrType));
			}
			else
			{
				strRet = "Error Mod Zero";
			}
			break;
		case MYXOR:
			strRet.Format(strFormat, strtoul64(str1.GetBuffer(0), NULL, nStrType) ^ strtoul64(str2.GetBuffer(0), NULL, nStrType));
			break;
		case MYAND:
			strRet.Format(strFormat, strtoul64(str1.GetBuffer(0), NULL, nStrType) & strtoul64(str2.GetBuffer(0), NULL, nStrType));
			break;
		case MYOR:
			strRet.Format(strFormat, strtoul64(str1.GetBuffer(0), NULL, nStrType) | strtoul64(str2.GetBuffer(0), NULL, nStrType));
			break;
		case MYSHL:
			strRet.Format(strFormat, strtoul64(str1.GetBuffer(0), NULL, nStrType) << strtoul64(str2.GetBuffer(0), NULL, nStrType));
			break;
		case MYSHR:
			strRet.Format(strFormat, strtoul64(str1.GetBuffer(0), NULL, nStrType) >> strtoul64(str2.GetBuffer(0), NULL, nStrType));
			break;
		case MYNOT:
			strRet.Format(strFormat, ~strtoul64(str1.GetBuffer(0), NULL, nStrType));
			break;
		default:
			break;
		}
	}
	catch (...)
	{
		DWORD dwError = GetLastError();
		DWORD systemLocale=MAKELANGID(LANG_NEUTRAL,SUBLANG_NEUTRAL); //获得本机的语言
		HLOCAL hlocal=NULL;
		BOOL fOK=FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS //FORMAT_MESSAGE_FROM_SYSTEM标志告诉操作系统我们要获得系统定义的错误代码的相应字符串//FORMAT_MESSAGE_IGNORE_INSERTS 标志允许我们获得包含%占位符的消息
			|FORMAT_MESSAGE_ALLOCATE_BUFFER,  //FORMAT_MESSAGE_ALLOCATE_BUFFER 要请求操作系统分配一个可以容纳错误文本描述的内存这个句柄在hlocal中返回
			NULL, dwError,systemLocale,(PTSTR)&hlocal,0,NULL);
		if(!fOK)   //如果FormatMessage执行不成功
		{
			HMODULE hDll=LoadLibraryEx(TEXT("netmsg.dll"),NULL,DONT_RESOLVE_DLL_REFERENCES); //加载系统netmsg.dll 尝试查找错误代码
			if(hDll!=NULL)
			{
				fOK=FormatMessage(FORMAT_MESSAGE_FROM_HMODULE|FORMAT_MESSAGE_IGNORE_INSERTS
					|FORMAT_MESSAGE_ALLOCATE_BUFFER,hDll, dwError,systemLocale,(PTSTR)&hlocal,0,NULL);
				FreeLibrary(hDll);
			}
		}
		if(fOK&&hlocal)
		{
			AfxMessageBox((PCTSTR)LocalLock(hlocal));
			LocalFree(hlocal);
		}
		else
		{
			AfxMessageBox(TEXT("发生未知错误"));
		}
	}
	return strRet;
}
void CClac::OnChangeEditAdd1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	m_AddSum = Operation(m_Add1, m_Add2, MYADD);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}
void CClac::OnChangeEditAdd2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	OnChangeEditAdd1();
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditSub1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	m_SubSum = Operation(m_Sub1, m_Sub2, MYSUB);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditSub2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	OnChangeEditSub1();
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditMul1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	m_MulSum = Operation(m_Mul1, m_Mul2, MYMUL);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditMul2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	OnChangeEditMul1() ;
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditDiv1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	m_DivSum = Operation(m_Div1, m_Div2, MYDIV);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditDiv2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	OnChangeEditDiv1() ;
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditMod1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	m_ModSum = Operation(m_Mod1, m_Mod2, MYMOD);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditMod2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	OnChangeEditMod1() ;
	// TODO: Add your control notification handler code here
	
}
///////////////逻辑运算
void CClac::OnChangeEditXor1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	m_XorSum = Operation(m_Xor1, m_Xor2, MYXOR);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditXor2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	OnChangeEditXor1();
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditAnd1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	m_AndSum = Operation(m_And1, m_And2, MYAND);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditAnd2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	OnChangeEditAnd1();
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditOr1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	m_OrSum = Operation(m_Or1, m_Or2, MYOR);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditOr2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	OnChangeEditOr1();
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditShl1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	m_ShlSum = Operation(m_Shl1, m_Shl2, MYSHL);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditShl2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	OnChangeEditShl1();
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditShr1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	m_ShrSum = Operation(m_Shr1, m_Shr2, MYSHR);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditShr2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	OnChangeEditShr1();
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditNot() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	m_NotSum = Operation(m_Not, "0", MYNOT);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditHex() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	CString strFormat = "%I64u";
	m_Hex.TrimRight(" ");
	m_Hex.TrimLeft(" ");
	if(m_unsigned)
	{
		strFormat = "%I64d";
	}
	m_Dec.Format(strFormat, strtoul64(m_Hex.GetBuffer(0), NULL, 16));
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CClac::OnChangeEditDec() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	m_Dec.TrimRight(" ");
	m_Dec.TrimLeft(" ");
//	CString strTmp = m_Dec;
// 	if(m_unsigned)
// 	{
// 		if(m_Dec.GetAt(0) == '-')
// 		{
// 			strTmp.Format("%d", 0 - strtoul(m_Dec.GetBuffer(0) + 1, NULL, 10));
// 		}
// 	}
	m_Hex.Format("%llX", strtoul64(m_Dec.GetBuffer(0), NULL, 10));
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CClac::OnRadioUnsigned() 
{
	// TODO: Add your control notification handler code here
	m_unsigned = 0;
	OnChangeEditHex();
}

void CClac::OnRadioSigned() 
{
	// TODO: Add your control notification handler code here
	m_unsigned = 1;
	OnChangeEditHex();
}

void CClac::OnButtonAbout() 
{
	// TODO: Add your control notification handler code here
//	AfxMessageBox("by: 空道");
}

UINT64 CClac::strtoul64(const char *nptr, char **endptr, int base)
{
//	#   define ULLONG_MAX	18446744073709551615ULL
	const char *s;
	unsigned long long acc, cutoff;
	int c;
	int neg, any, cutlim;

	/*
	 * See strtoq for comments as to the logic used.
	 */
	s = nptr;
	do {
		c = (unsigned char) *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else { 
		neg = 0;
		if (c == '+')
			c = *s++;
	}
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;

	cutoff = ULLONG_MAX / (unsigned long long)base;
	cutlim = ULLONG_MAX % (unsigned long long)base;
	for (acc = 0, any = 0;; c = (unsigned char) *s++) {
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0)
			continue;
		if (acc > cutoff || (acc == cutoff && c > cutlim)) {
			any = -1;
			acc = ULLONG_MAX;
			errno = ERANGE;
		} else {
			any = 1;
			acc *= (unsigned long long)base;
			acc += c;
		}
	}
	if (neg && any > 0)
		acc = -acc;
	if (endptr != 0)
		*endptr = (char *) (any ? s - 1 : nptr);
	return (acc);
}
