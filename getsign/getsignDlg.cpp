// getsignDlg.cpp : implementation file
//

#include "stdafx.h"
#include "getsign.h"
#include "getsignDlg.h"
#include "unzip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CGetsignDlg dialog

CGetsignDlg::CGetsignDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetsignDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetsignDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetsignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetsignDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetsignDlg, CDialog)
	//{{AFX_MSG_MAP(CGetsignDlg)
	ON_WM_PAINT()
	ON_WM_DROPFILES()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LL, OnButtonLl)
	ON_EN_CHANGE(IDC_EDIT_SIGN, OnChangeEditSign)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetsignDlg message handlers

BOOL CGetsignDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGetsignDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGetsignDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGetsignDlg:: OnDropFiles(HDROP hDropInfo)
{
	char szFilePath[MAX_PATH] = {0};
	::DragQueryFile( hDropInfo, 0, szFilePath, MAX_PATH );
	ShowData(szFilePath);
	CWnd::OnDropFiles(hDropInfo);
}

int CGetsignDlg::getApkSign(char *ApkPath, unsigned char **ppOut)
{
	HZIP hz;          //Zip文件句柄
	ZRESULT zr;    //操作返回值 
    ZIPENTRY ze;  //Zip文件入口  
	int nSiglen = 0;
	int ECsigoffset = 0;
	hz=OpenZip(ApkPath, NULL);  ////第一个参数表示路径  第二个参数表示密码
	if(hz==0)
	{
		AfxMessageBox("打开ZIP文件失败!");
		return 0;
	}
	zr=GetZipItem(hz,-1,&ze);  
	int numitems=ze.index;   //获得RAR文件中一共有多少个文件
    for (int i=0; i < numitems;i++)   
	{ 
        zr=GetZipItem(hz,i,&ze);  //为了获得文件名
        if(zr != ZR_OK) 
        {   
			AfxMessageBox("读取ZIP文件内容失败!");
			break;
        } 
		else
		{
			static char sigdir[] = "META-INF";
			OutputDebugString(ze.name);
			if(0 == memcmp(sigdir, ze.name, strlen(sigdir)) && strrchr(ze.name,'.') &&
				(0 == memcmp("RSA", strrchr(ze.name,'.') + 1, strlen("RSA")) ||
				0 == memcmp("DSA", strrchr(ze.name,'.') + 1, strlen("DSA")) ||
				0 == memcmp("EC", strrchr(ze.name,'.') + 1, strlen("EC"))) )
			{
				if(0 == memcmp("EC", strrchr(ze.name,'.') + 1, strlen("EC")))
				{
					ECsigoffset = 4;
				}
				unsigned char *pBuf = (unsigned char *)malloc(ze.unc_size + 1);
				memset(pBuf, 0, ze.unc_size + 1);
				zr=UnzipItem(hz,i, pBuf, ze.unc_size);   //释放文件
				if(zr == ZR_OK && ppOut) 
				{   
					nSiglen = pBuf[0x36 + ECsigoffset] * 0x100 + pBuf[0x37 + ECsigoffset];
					if(pBuf[0x36 + ECsigoffset + 2] >= 0x80)
					{
						ECsigoffset += 3;
						while(pBuf[0x36 + ECsigoffset] >= 0x80)
						{
							ECsigoffset ++;
						}
						nSiglen = pBuf[0x36 + ECsigoffset] * 0x100 + pBuf[0x37 + ECsigoffset];
					}
					if(nSiglen < ze.unc_size - 0x36 - ECsigoffset)
					{
						*ppOut =(unsigned char *)malloc(nSiglen+1);
						memset(*ppOut, 0, nSiglen + 1);
						memcpy(*ppOut, pBuf + 0x38 + ECsigoffset, nSiglen);
					}
					else
					{
						AfxMessageBox("签名文件已损坏!");
					}
						
				} 
				else
				{
					AfxMessageBox("读取签名文件失败!");
					
				}
				free(pBuf);
				break;
			}
			
		}
    }
    CloseZip(hz); 
	if(i == numitems)
	{
		AfxMessageBox("未找到签名文件!");
	}
	return nSiglen;
}

BOOL CGetsignDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(WM_KEYDOWN==pMsg->message&&_T('A')==pMsg->wParam)
	{
		if(HIBYTE(GetKeyState(VK_CONTROL)))
		{
			CEdit*pEdit;
			
			if (GetFocus()->GetSafeHwnd() == GetDlgItem(IDC_EDIT_SIGN)->m_hWnd )
			{
				pEdit=(CEdit*)GetDlgItem(IDC_EDIT_SIGN);
				pEdit->SetSel(0, -1);
			}	
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CGetsignDlg::OnButtonLl() 
{
	// TODO: Add your control notification handler code here
	
	CFileDialog dlg(true,NULL,NULL,NULL,"*.apk|*.apk|所有文件(*.*)|*.*||",NULL);   
	CString strPath = "";
	if(dlg.DoModal()==IDOK)            //显示对话框并返回(IDOK或IDCANCEL)分别是按了打开和取消
	{
		strPath = dlg.GetPathName();   ////比如:C:\asd.bat
		if(!strPath.IsEmpty())
		{
			ShowData(strPath.GetBuffer(0));
		}
	}
}

unsigned int CGetsignDlg::hashCode(unsigned char *pbuf, int len)
{
	if (pbuf == NULL) 
	{
		return 0xFFFFFFFF;
	}
	int hashCode = 1;
	int i = 0;
	for (i = 0; i < len; i++)
	{
		// the hash code value for byte value is its integer value
		hashCode = 31 * hashCode + char(pbuf[i]);
	}
    return (unsigned int)hashCode;
	
}

BOOL CGetsignDlg::ShowData(char *path)
{
	BOOL iRet = FALSE;
	unsigned char *pSign = NULL;
	char szHashCodeBuf[100] = {0};
	// 调用控件的接口播放拖进的文件
	int nSiglen = getApkSign(path, &pSign);
	if(nSiglen)
	{
		char *pTmp = (char *)malloc(nSiglen * 2 + 1);
		memset(pTmp, 0, nSiglen * 2 + 1);
		int i = 0;
		for(i = 0; i < nSiglen; i++)
		{
			sprintf(pTmp + i * 2, "%02X", pSign[i]);
		}
		SetDlgItemText(IDC_EDIT_SIGN, pTmp);
		free(pTmp);
		sprintf(szHashCodeBuf, "0x%08X", hashCode(pSign, nSiglen));
		SetDlgItemText(IDC_EDIT_HASHCODE, szHashCodeBuf);
		SetDlgItemText(IDC_EDIT_PATH, path);
		iRet = TRUE;
	}
	free(pSign);
	return iRet;
}

void CGetsignDlg::OnChangeEditSign() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString strData;
	char szHashCodeBuf[100] = {0};
	if(GetDlgItemText(IDC_EDIT_SIGN, strData))
	{
		unsigned char *pSign = (unsigned char*)malloc(strData.GetLength() + 1);
		memset(pSign, 0, strData.GetLength() + 1);
		int i = 0;
		int nSiglen = strData.GetLength() / 2;
		char *p = strData.GetBuffer(0);
		for(i = 0; i < nSiglen; i++)
		{
			sscanf(p + i * 2, "%02X", pSign + i);
		}
		sprintf(szHashCodeBuf, "0x%08X", hashCode(pSign, nSiglen));
		SetDlgItemText(IDC_EDIT_HASHCODE, szHashCodeBuf);
	}
	
}
