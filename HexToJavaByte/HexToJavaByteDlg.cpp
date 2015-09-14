// HexToJavaByteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HexToJavaByte.h"
#include "HexToJavaByteDlg.h"
#include "zlib.h"
#pragma comment (lib, "zlib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexToJavaByteDlg dialog
/*
 *	����deflate���㷨ѹ������
 *	plain_text���ַ�������
 *	ptext_len���ַ�����С
 *	cryptr������ѹ���������ָ��
 *	crylen��ѹ�����ݴ�С
 *	isgzip����0��ʾ����gzipѹ���㷨
 *	����0��ʾ�ɹ�
 */
int deflate_str(unsigned char* plain_text, unsigned int ptext_len, 
				unsigned char** cryptr, unsigned int *crylen,  int isgzip)
{
	int ret;
	z_stream zs = {0};
	unsigned int outlen = 0;
	unsigned char *out;
	
	//��ʼ��ѹ��������
	if (isgzip == 0)
		ret = deflateInit(&zs, Z_DEFAULT_COMPRESSION);
	else
		ret = deflateInit2(&zs, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
				16 + MAX_WBITS, 8, Z_DEFAULT_STRATEGY);
	if (ret != Z_OK)
		return -1;

	//����ѹ���ڴ�
	outlen = ptext_len + 128;
	out = (unsigned char*)malloc(outlen);
	if (out == 0)
		return -1;

	zs.next_in = plain_text;
	zs.avail_in = ptext_len;
	zs.next_out = out;
	zs.avail_out = outlen;

	//��ʼѹ��
	ret = deflate(&zs, Z_NO_FLUSH);
	if (ret != Z_OK) {
		free(out);
		deflateEnd(&zs);
		return -1;
	}
	
	//��ʼ��������
	ret = deflate(&zs, Z_FINISH);
	if (ret != Z_STREAM_END) {
		//���������ڴ治���Դ洢ѹ�����ݣ���ʧ��
		free(out);
		deflateEnd(&zs);
		return -1;
	}

	outlen = zs.total_out;
	ret = deflateEnd(&zs);
	if (cryptr == 0) {
		//�������Ҫ�������ͷ���Դ
		free(out);
	} else
		*cryptr = out;
	if (crylen != 0)
		*crylen = outlen;

	return 0;
}

/*
 *	����inflate���㷨��ѹ����
 *	crypt_text���ַ�������
 *	crypt_len���ַ�����С
 *	plainptr�����ؽ�ѹ�������ָ��
 *	plainlen����ѹ���ݴ�С
 *	isgzip����0��ʾ����gzip��ѹ�㷨
 *	����0��ʾ�ɹ�
 */
int inflate_str(unsigned char *crypt_text, unsigned int crypt_len,
				unsigned char **plainptr, unsigned int *plainlen, int isgzip)
{
	z_stream zs = {0};
	int ret;

	unsigned int curpos = 0;
	unsigned int outlen = crypt_len;
	unsigned char *out = NULL;
	unsigned int templen = 16384*2;
	unsigned char *temp = NULL;
	unsigned char *tempo = NULL;

	zs.next_in = crypt_text;
	zs.avail_in = crypt_len;
	
	if (isgzip == 0)
		ret = inflateInit(&zs);
	else
		ret = inflateInit2(&zs, 16 + MAX_WBITS);
	if (ret != Z_OK) 
		return -1;

	//������ʱ�ռ䣬��ʼ��
	out = (unsigned char*)malloc(crypt_len);
	temp = (unsigned char*) malloc(templen);
	if (out == 0) {
		inflateEnd(&zs);
		return -1;
	}
	if (temp == 0) {
		inflateEnd(&zs);
		free(temp);
		return -1;
	}

	zs.next_out = temp;
	zs.avail_out = templen;

	//��ѹ
	do {
		ret = inflate(&zs, Z_NO_FLUSH);
		if (ret == Z_OK || ret == Z_STREAM_END) 
		{
copy_again:
			//���ѽ�ѹ�����ݷ��뵽out������
			if (outlen > templen - zs.avail_out) 
			{

				memcpy(out + curpos, temp, templen - zs.avail_out);
				curpos += templen - zs.avail_out;
				outlen -= templen - zs.avail_out;
			} 
			else 
			{
				//��ѹ���治��
				//�����µĻ���
				outlen *= 2;
				tempo = (unsigned char*)malloc(outlen+curpos);
				if (temp == 0) 
				{
					free(out);
					free(temp);
					inflateEnd(&zs);
					return -1;
				}

				//�����ѽ�ѹ������
				memcpy(tempo, out, curpos);
				free(out);
				out = tempo;
				goto copy_again;
			}

			zs.next_out = temp;
			zs.avail_out = templen;
		} else {
			free(out);
			free(temp);
			inflateEnd(&zs);
			return -1;
		}
	} while (ret != Z_STREAM_END) ;

	outlen = zs.total_out;
	free(temp);
	inflateEnd(&zs);
	if (plainptr == 0 || plainlen == 0) {
		free(out);	
		return 0;
	}

	*plainptr = out;
	*plainlen = outlen;

	return 0;
}
/*
*	�ͷ���Դ
*/
void free_zlib_prt(unsigned char *ptr)
{
	if (0 != ptr)
		 free(ptr);
}
CHexToJavaByteDlg::CHexToJavaByteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHexToJavaByteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHexToJavaByteDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHexToJavaByteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHexToJavaByteDlg)
	DDX_Control(pDX, IDC_EDIT_OUTBUF, m_editOut);
	DDX_Control(pDX, IDC_EDIT_INBUF, m_editIn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHexToJavaByteDlg, CDialog)
	//{{AFX_MSG_MAP(CHexToJavaByteDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SHIFT, OnButtonShift)
	ON_BN_CLICKED(IDC_BUTTON_DECTOHEX, OnButtonDectohex)
	ON_BN_CLICKED(IDC_BUTTON_UNZLIB, OnButtonUnzlib)
	ON_BN_CLICKED(IDC_BUTTON_ZLIB, OnButtonZlib)
	ON_BN_CLICKED(IDC_BUTTON_NETBEANSTOHEX, OnButtonNetbeanstohex)
	ON_BN_CLICKED(IDC_BUTTON_GZIP, OnButtonGzip)
	ON_BN_CLICKED(IDC_BUTTON_GUNZIP, OnButtonGunzip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexToJavaByteDlg message handlers

BOOL CHexToJavaByteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CheckDlgButton(IDC_CHECK_SHEAR,BST_CHECKED);   //ѡ�и�ѡ��
	m_editIn.SetLimitText(-1);
	m_editOut.SetLimitText(-1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHexToJavaByteDlg::OnPaint() 
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
HCURSOR CHexToJavaByteDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHexToJavaByteDlg::OnButtonShift() 
{
	// TODO: Add your control notification handler code here
	CString strInBuf = "";
	int i = 0;
	int j = 0;
	CString strsum = "byte data[] = \r\n{\r\n";
	CString StrTmp = "";
	GetDlgItemText(IDC_EDIT_INBUF,StrTmp);
	
	
	int nlen = StrTmp.GetLength();
	char *lpTmpBuf = (char*) malloc(nlen + 1);
	memset(lpTmpBuf, 0, nlen + 1);
	
	for(i = 0; i < nlen; i++)
	{
		char chTmp = StrTmp.GetAt(i);
		if(chTmp == '\n')
		{
		//	lpTmpBuf[j++] = StrTmp.GetAt(i);
			
			if(j > 0)
			{
				CString StrTmp2 = "";
				StrTmp2.Format("%02X", strtoul(lpTmpBuf, NULL, 16));
				strInBuf +=StrTmp2;
			}
//			strInBuf.Format("%s%02X", strInBuf, strtoul(lpTmpBuf, NULL, 16));
			memset(lpTmpBuf, 0, nlen + 1);
			j = 0;
		}
		else if ((chTmp >= 0x30 && chTmp <= 0x39) ||  (chTmp >= 'A' && chTmp <= 'F') ||
			(chTmp >= 'a' && chTmp <= 'f'))
		{
			lpTmpBuf[j++] = StrTmp.GetAt(i);
		}
	}
//	strInBuf.Format("%s", lpTmpBuf);
	if(j <= 2 && j > 0)
	{
		strInBuf.Format("%s%02X", strInBuf, strtoul(lpTmpBuf, NULL, 16));	
	}
	else if(j > 2)
	{
		strInBuf = StrTmp;
	}
	free(lpTmpBuf);
	j = 0;
	if(strInBuf.GetLength() % 2)
	{
		SetDlgItemText(IDC_EDIT_OUTBUF,"�������,û����2����");
		return;
	}
	nlen = strInBuf.GetLength();
	for(i = 0;i < nlen;i++)
	{
		TCHAR ch = strInBuf.GetAt(i);
		if((ch >= 0x30 && ch <= 0x39) || (ch >= 0x41 && ch <= 0x46) || (ch >= 0x61 && ch <= 0x66))
		{
			continue;
		}
		SetDlgItemText(IDC_EDIT_OUTBUF,"�������,���ڷ�16����ֵ");
		return;
	}
	char *lpBuf = strInBuf.GetBuffer(0);
	for(i = 0;i < nlen;i += 2)
	{
		StrTmp.Format("(byte) 0x%c%c,",lpBuf[i],lpBuf[i + 1]);
		j++;
		if((j % 0x8 == 0x0))
		{
			StrTmp += "\r\n";
		}
		strsum += StrTmp;
	}
	if(strInBuf.GetLength() % 16)
	{
		strsum += "\r\n";
	}
	strsum += "};";
	SetDlgItemText(IDC_EDIT_OUTBUF,strsum);
	IsSendChipboard();

}
//���Ctrl+A ȫѡ����
BOOL CHexToJavaByteDlg::PreTranslateMessage(MSG*pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(WM_KEYDOWN==pMsg->message&&_T('A')==pMsg->wParam)
	{
		if(HIBYTE(GetKeyState(VK_CONTROL)))
		{
			CEdit*pEdit;

			if (GetFocus()->GetSafeHwnd() == GetDlgItem(IDC_EDIT_INBUF)->m_hWnd )
			{
				pEdit=(CEdit*)GetDlgItem(IDC_EDIT_INBUF);
			}
			else
			{
				pEdit=(CEdit*)GetDlgItem(IDC_EDIT_OUTBUF);
			}
			pEdit->SetSel(0, -1);

		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CHexToJavaByteDlg::OnButtonDectohex() 
{
	// TODO: Add your control notification handler code here
	CString strInBuf;
	int i = 0;
	int j = 0;
	CString strsum = "";
	CString StrTmp = "";
	char szTmp[10] = {0};
	GetDlgItemText(IDC_EDIT_INBUF,strInBuf);
	char *lpBuf = strInBuf.GetBuffer(0);
	int nlen = strInBuf.GetLength();
	if(strInBuf.GetLength() % 3)
	{
		SetDlgItemText(IDC_EDIT_OUTBUF,"�������,û����3����");
		return;
	}
	for(i = 0;i < nlen;i++)
	{
		TCHAR ch = strInBuf.GetAt(i);
		if(ch >= 0x30 && ch <= 0x39)
		{
			continue;
		}
		SetDlgItemText(IDC_EDIT_OUTBUF,"�������,���ڷ�10����ֵ");
		return;
	}
	
	for(i = 0;i < nlen;i += 3)
	{
	//	StrTmp.Format("(byte) 0x%c%c,",lpBuf[i],lpBuf[i + 1]);
		memset(szTmp,0,10);
		memcpy(szTmp,lpBuf + i,3);
		strsum.Format("%s%02X",strsum,atol(szTmp));
		
	//	strsum += StrTmp;
	}
	SetDlgItemText(IDC_EDIT_OUTBUF,strsum);
	IsSendChipboard();
}

void CHexToJavaByteDlg::IsSendChipboard()
{
	
	if(IsDlgButtonChecked(IDC_CHECK_SHEAR))   //�ж��Ƿ�ѡ��
	{
		if(OpenClipboard()) //OpenClipboard()�Ǵ򿪼��а�ɹ�����TRUE ʧ�ܷ���FALSE
		{
			CString str;
			HANDLE handle;
			char* pBuf;
			EmptyClipboard(); //��ռ��а��ü��а�Ȩ��
			GetDlgItemText(IDC_EDIT_OUTBUF,str);
			handle=GlobalAlloc(GMEM_MOVEABLE,str.GetLength()+1); //�����ڴ�ռ�                                                  
			pBuf=(char*)GlobalLock(handle); //�����ռ�
			strcpy(pBuf,str); //���ռ�д������
			GlobalUnlock(handle); //�����ռ�
			SetClipboardData(CF_TEXT,handle);  //���ü��а�������
			CloseClipboard();  //�رռ��а� һ��Ҫ�ر� �������������޷�ʹ�ü��а�
		}
		else
		{
			AfxMessageBox("�򿪼��а�");
		}
	}
}

void CHexToJavaByteDlg::OnButtonUnzlib() 
{
	// TODO: Add your control notification handler code here
	CString strInBuf = "";
//	CString strsum = "";
	unsigned int nlen = 0;
	unsigned char *lpUnBuf = NULL;
	unsigned int nUnLen = 0;
	unsigned int nEnLen = 0;
	unsigned char *lpEnBuf = NULL;
	unsigned int i = 0;
	nlen = GetDlgItemText(IDC_EDIT_INBUF, strInBuf);
	if(nlen)
	{
		if(strInBuf.GetLength() % 2)
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"�������,û����2����");
			return;
		}
		if(!IsStrHexValues(strInBuf))
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"�������,���ڷ�16����ֵ");
			return;
		}
		nEnLen = nlen / 2;
		lpEnBuf = (unsigned char *)malloc(nlen + 1);
		memset(lpEnBuf, 0, nlen + 1);
		for(i = 0;i < nEnLen;i++)
		{
			sscanf(strInBuf.GetBuffer(0) + i * 2, "%02X", lpEnBuf + i);
		}
	}
	else
	{
		CFileDialog dlg(true,NULL,NULL,NULL,"�����ļ�(*.*)|*.*||",NULL);   
		//��һ����������Ϊture��ʾ�Ǵ��ļ�false��ʾ�Ǳ����ļ�
		
		if(dlg.DoModal()==IDOK)            //��ʾ�Ի��򲢷���(IDOK��IDCANCEL)�ֱ��ǰ��˴򿪺�ȡ��
		{
			nEnLen = ReadFileToBuf(dlg.GetPathName().GetBuffer(0), &lpEnBuf);
			if(0 == nEnLen)
			{
				SetDlgItemText(IDC_EDIT_OUTBUF,"��ȡ�ļ�ʧ��");
				return ;
			}
		}
		else
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"����������");
			return ;
		}
	}
	inflate_str(lpEnBuf, nEnLen, &lpUnBuf, &nUnLen, 0);
	if(nlen &&(nUnLen > 0) )
	{
		char *lpTmp = (char *)malloc(nUnLen * 2 + 1);
		memset(lpTmp, 0, nUnLen * 2 + 1);
		for(i = 0; i < nUnLen; i++)
		{
			sprintf(lpTmp + i * 2, "%02X", lpUnBuf[i]);
		}
		SetDlgItemText(IDC_EDIT_OUTBUF, lpTmp);
		free(lpTmp);
		IsSendChipboard();
	}
	else if( nlen == 0 && (nUnLen > 0) )
	{
		CFileDialog dlg(false,NULL,NULL,NULL,"�����ļ�(*.*)|*.*||",NULL);   
		//��һ����������Ϊture��ʾ�Ǵ��ļ�false��ʾ�Ǳ����ļ�
		
		if(dlg.DoModal()==IDOK)            //��ʾ�Ի��򲢷���(IDOK��IDCANCEL)�ֱ��ǰ��˴򿪺�ȡ��
		{
			CString str;
			nUnLen = WriteBufToFile(dlg.GetPathName().GetBuffer(0), lpUnBuf, nUnLen);
			if(nUnLen)
			{
				str.Format("��ѹ�ɹ�!\r\n���ݱ���·��:\r\n%s", dlg.GetPathName());
			}
			else
			{
				str.Format("��ѹ�ɹ�!\r\n���ݱ���ʧ��");
			}
			SetDlgItemText(IDC_EDIT_OUTBUF, str);
			
		}
		else
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"ȡ�������ݱ���!");
		}
	}
	else
	{
		SetDlgItemText(IDC_EDIT_OUTBUF,"��ѹʧ��");
	}
	free_zlib_prt(lpUnBuf);
	free(lpEnBuf);

}

void CHexToJavaByteDlg::OnButtonZlib() 
{
	CString strInBuf = "";
	//	CString strsum = "";
	unsigned int nlen = 0;
	
	unsigned int i = 0;
	unsigned char *lpBuf = NULL;
	unsigned int nUnLen = 0;
	unsigned char *lpEnBuf = NULL;
	unsigned int nEnLen = 0;
	nlen = GetDlgItemText(IDC_EDIT_INBUF, strInBuf);
	if(nlen)
	{
		if(strInBuf.GetLength() % 2)
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"�������,û����2����");
			return;
		}
		if(!IsStrHexValues(strInBuf))
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"�������,���ڷ�16����ֵ");
			return;
		}
		nUnLen = nlen / 2;
		lpBuf = (unsigned char *)malloc(nlen + 1);
		memset(lpBuf, 0, nlen + 1);
		for(i = 0;i < nUnLen;i++)
		{
			sscanf(strInBuf.GetBuffer(0) + i * 2, "%02X", lpBuf + i);
		}
	}
	else
	{
		CFileDialog dlg(true,NULL,NULL,NULL,"�����ļ�(*.*)|*.*||",NULL);   
		//��һ����������Ϊture��ʾ�Ǵ��ļ�false��ʾ�Ǳ����ļ�
		
		if(dlg.DoModal()==IDOK)            //��ʾ�Ի��򲢷���(IDOK��IDCANCEL)�ֱ��ǰ��˴򿪺�ȡ��
		{
			nUnLen = ReadFileToBuf(dlg.GetPathName().GetBuffer(0), &lpBuf);
			if(0 == nUnLen)
			{
				SetDlgItemText(IDC_EDIT_OUTBUF,"��ȡ�ļ�ʧ��");
				return ;
			}
		}
		else
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"����������");
			return ;
		}
	}
	deflate_str(lpBuf, nUnLen, &lpEnBuf, &nEnLen, 0);
	if(nlen && (nEnLen > 0) )
	{
		char *lpTmp = (char *)malloc(nEnLen * 2 + 1);
		memset(lpTmp, 0, nEnLen * 2 + 1);
		for(i = 0; i < nEnLen; i++)
		{
			sprintf(lpTmp + i * 2, "%02X", lpEnBuf[i]);
		}
		SetDlgItemText(IDC_EDIT_OUTBUF, lpTmp);
		IsSendChipboard();
		free(lpTmp);
	}
	else if( nlen == 0 && (nEnLen > 0) )
	{
		CFileDialog dlg(false,NULL,NULL,NULL,"�����ļ�(*.*)|*.*||",NULL);   
		//��һ����������Ϊture��ʾ�Ǵ��ļ�false��ʾ�Ǳ����ļ�
		
		if(dlg.DoModal()==IDOK)            //��ʾ�Ի��򲢷���(IDOK��IDCANCEL)�ֱ��ǰ��˴򿪺�ȡ��
		{
			CString str;
			nUnLen = WriteBufToFile(dlg.GetPathName().GetBuffer(0), lpEnBuf, nEnLen);
			if(nUnLen)
			{
				str.Format("ѹ���ɹ�!\r\n���ݱ���·��:\r\n%s", dlg.GetPathName());
			}
			else
			{
				str.Format("ѹ���ɹ�!\r\n���ݱ���ʧ��");
			}
			SetDlgItemText(IDC_EDIT_OUTBUF, str);
		}
		else
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"ȡ�������ݱ���!");
		}
	}
	else
	{
		SetDlgItemText(IDC_EDIT_OUTBUF,"ѹ��ʧ��");
	}
	free_zlib_prt(lpEnBuf);
	free(lpBuf);
}

BOOL CHexToJavaByteDlg::IsStrHexValues(CString str)
{
	int i = 0;
	int nlen = str.GetLength();
	for(i = 0;i < nlen;i++)
	{
		TCHAR ch = str.GetAt(i);
		if((ch >= 0x30 && ch <= 0x39) || (ch >= 0x41 && ch <= 0x46) || (ch >= 0x61 && ch <= 0x66))
		{
			continue;
		}
		return FALSE;
	}
	return TRUE;
}
CString * SplitString(CString str, char split, int& iSubStrs)
{
    int iPos = 0; //�ָ��λ��
    int iNums = 0; //�ָ��������
    CString strTemp = str;
    CString strRight;
    //�ȼ������ַ���������
    while (iPos != -1)
    {
        iPos = strTemp.Find(split);
        if (iPos == -1)
        {
            break;
        }
        strRight = strTemp.Mid(iPos + 1, str.GetLength());
        strTemp = strRight;
        iNums++;
    }
    if (iNums == 0) //û���ҵ��ָ��
    {
        //���ַ����������ַ�������
        iSubStrs = 1; 
        return NULL;
    }
    //���ַ�������
    iSubStrs = iNums + 1; //�Ӵ������� = �ָ������ + 1
    CString* pStrSplit;
    pStrSplit = new CString[iSubStrs];
    strTemp = str;
    CString strLeft;
    for (int i = 0; i < iNums; i++)
    {
        iPos = strTemp.Find(split);
        //���Ӵ�
        strLeft = strTemp.Left(iPos);
        //���Ӵ�
        strRight = strTemp.Mid(iPos + 1, strTemp.GetLength());
        strTemp = strRight;
        pStrSplit[i] = strLeft;
    }
    pStrSplit[iNums] = strTemp;
    return pStrSplit;
}
void CHexToJavaByteDlg::OnButtonNetbeanstohex() 
{
	// TODO: Add your control notification handler code here
	CString strInBuf = "";
	int i = 0;
	int j = 0;
	CString strsum = "";
	CString StrTmp = "";
	int nlen = 0;
	int nCount = 0;
	if( GetDlgItemText(IDC_EDIT_INBUF,StrTmp) <= 0)
	{
		SetDlgItemText(IDC_EDIT_OUTBUF,"����������");
		return;
	}
	CString *lpCStrs = SplitString(StrTmp, '\n', nCount);
	StrTmp = "";
	for(i = 0; i < nCount; i++)
	{
		int nTmp = 0;
		if( (nTmp = lpCStrs[i].Find("0x")) >= 0)
		{
			StrTmp += lpCStrs[i].GetBuffer(0) + nTmp + 2;
		}
	}
	
	nlen = StrTmp.GetLength();
	char *lpTmpBuf = (char*) malloc(nlen + 1);
	memset(lpTmpBuf, 0, nlen + 1);
	
	for(i = 0; i < nlen; i++)
	{
		char chTmp = StrTmp.GetAt(i);
		if(chTmp < '0')
		{
			//	lpTmpBuf[j++] = StrTmp.GetAt(i);
			
			if(j > 0)
			{
				CString StrTmp2 = "";
				StrTmp2.Format("%02X", strtoul(lpTmpBuf, NULL, 16));
				strInBuf +=StrTmp2;
			}
			//			strInBuf.Format("%s%02X", strInBuf, strtoul(lpTmpBuf, NULL, 16));
			memset(lpTmpBuf, 0, nlen + 1);
			j = 0;
		}
		else if ((chTmp >= 0x30 && chTmp <= 0x39) ||  (chTmp >= 'A' && chTmp <= 'F') ||
			(chTmp >= 'a' && chTmp <= 'f'))
		{
			lpTmpBuf[j++] = StrTmp.GetAt(i);
		}
	}
	//	strInBuf.Format("%s", lpTmpBuf);
	if(j <= 2 && j > 0)
	{
		strInBuf.Format("%s%02X", strInBuf, strtoul(lpTmpBuf, NULL, 16));	
	}
	else if(j > 2)
	{
		strInBuf = StrTmp;
	}
	free(lpTmpBuf);
	j = 0;
	if(strInBuf.GetLength() % 2)
	{
		SetDlgItemText(IDC_EDIT_OUTBUF,"�������,û����2����");
		return;
	}
	SetDlgItemText(IDC_EDIT_OUTBUF,strInBuf);
	IsSendChipboard();
}

void CHexToJavaByteDlg::OnButtonGzip() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	CString strInBuf = "";
	//	CString strsum = "";
	unsigned int nlen = 0;
	
	unsigned int i = 0;
	unsigned char *lpBuf = NULL;
	unsigned int nUnLen = 0;
	unsigned char *lpEnBuf = NULL;
	unsigned int nEnLen = 0;
	nlen = GetDlgItemText(IDC_EDIT_INBUF, strInBuf);
	if(nlen)
	{
		if(strInBuf.GetLength() % 2)
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"�������,û����2����");
			return;
		}
		if(!IsStrHexValues(strInBuf))
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"�������,���ڷ�16����ֵ");
			return;
		}
		nUnLen = nlen / 2;
		lpBuf = (unsigned char *)malloc(nlen + 1);
		memset(lpBuf, 0, nlen + 1);
		for(i = 0;i < nUnLen;i++)
		{
			sscanf(strInBuf.GetBuffer(0) + i * 2, "%02X", lpBuf + i);
		}
	}
	else
	{
		CFileDialog dlg(true,NULL,NULL,NULL,"�����ļ�(*.*)|*.*||",NULL);   
		//��һ����������Ϊture��ʾ�Ǵ��ļ�false��ʾ�Ǳ����ļ�
		
		if(dlg.DoModal()==IDOK)            //��ʾ�Ի��򲢷���(IDOK��IDCANCEL)�ֱ��ǰ��˴򿪺�ȡ��
		{
			nUnLen = ReadFileToBuf(dlg.GetPathName().GetBuffer(0), &lpBuf);
			if(0 == nUnLen)
			{
				SetDlgItemText(IDC_EDIT_OUTBUF,"��ȡ�ļ�ʧ��");
				return ;
			}
		}
		else
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"����������");
			return ;
		}
	}
	deflate_str(lpBuf, nUnLen, &lpEnBuf, &nEnLen, 1);
	if(nlen && (nEnLen > 0) )
	{
		char *lpTmp = (char *)malloc(nEnLen * 2 + 1);
		memset(lpTmp, 0, nEnLen * 2 + 1);
		for(i = 0; i < nEnLen; i++)
		{
			sprintf(lpTmp + i * 2, "%02X", lpEnBuf[i]);
		}
		SetDlgItemText(IDC_EDIT_OUTBUF, lpTmp);
		IsSendChipboard();
		free(lpTmp);
	}
	else if( nlen == 0 && (nEnLen > 0) )
	{
		CFileDialog dlg(false,NULL,NULL,NULL,"�����ļ�(*.*)|*.*||",NULL);   
		//��һ����������Ϊture��ʾ�Ǵ��ļ�false��ʾ�Ǳ����ļ�
		
		if(dlg.DoModal()==IDOK)            //��ʾ�Ի��򲢷���(IDOK��IDCANCEL)�ֱ��ǰ��˴򿪺�ȡ��
		{
			CString str;
			nUnLen = WriteBufToFile(dlg.GetPathName().GetBuffer(0), lpEnBuf, nEnLen);
			if(nUnLen)
			{
				str.Format("ѹ���ɹ�!\r\n���ݱ���·��:\r\n%s", dlg.GetPathName());
			}
			else
			{
				str.Format("ѹ���ɹ�!\r\n���ݱ���ʧ��");
			}
			SetDlgItemText(IDC_EDIT_OUTBUF, str);
		}
		else
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"ȡ�������ݱ���!");
		}
	}
	else
	{
		SetDlgItemText(IDC_EDIT_OUTBUF,"ѹ��ʧ��");
	}
	free_zlib_prt(lpEnBuf);
	free(lpBuf);
	
}

void CHexToJavaByteDlg::OnButtonGunzip() 
{
	// TODO: Add your control notification handler code here
	CString strInBuf = "";
	//	CString strsum = "";
	unsigned int nlen = 0;
	unsigned char *lpUnBuf = NULL;
	unsigned int nUnLen = 0;
	unsigned int nEnLen = 0;
	unsigned char *lpEnBuf = NULL;
	unsigned int i = 0;
	nlen = GetDlgItemText(IDC_EDIT_INBUF, strInBuf);
	if(nlen)
	{
		if(strInBuf.GetLength() % 2)
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"�������,û����2����");
			return;
		}
		if(!IsStrHexValues(strInBuf))
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"�������,���ڷ�16����ֵ");
			return;
		}
		nEnLen = nlen / 2;
		lpEnBuf = (unsigned char *)malloc(nlen + 1);
		memset(lpEnBuf, 0, nlen + 1);
		for(i = 0;i < nEnLen;i++)
		{
			sscanf(strInBuf.GetBuffer(0) + i * 2, "%02X", lpEnBuf + i);
		}
	}
	else
	{
		CFileDialog dlg(true,NULL,NULL,NULL,"�����ļ�(*.*)|*.*||",NULL);   
		//��һ����������Ϊture��ʾ�Ǵ��ļ�false��ʾ�Ǳ����ļ�
		
		if(dlg.DoModal()==IDOK)            //��ʾ�Ի��򲢷���(IDOK��IDCANCEL)�ֱ��ǰ��˴򿪺�ȡ��
		{
			nEnLen = ReadFileToBuf(dlg.GetPathName().GetBuffer(0), &lpEnBuf);
			if(0 == nEnLen)
			{
				SetDlgItemText(IDC_EDIT_OUTBUF,"��ȡ�ļ�ʧ��");
				return ;
			}
		}
		else
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"����������");
			return ;
		}
	}
	inflate_str(lpEnBuf, nEnLen, &lpUnBuf, &nUnLen, 1);
	if(nlen &&(nUnLen > 0) )
	{
		char *lpTmp = (char *)malloc(nUnLen * 2 + 1);
		memset(lpTmp, 0, nUnLen * 2 + 1);
		for(i = 0; i < nUnLen; i++)
		{
			sprintf(lpTmp + i * 2, "%02X", lpUnBuf[i]);
		}
		SetDlgItemText(IDC_EDIT_OUTBUF, lpTmp);
		IsSendChipboard();
		free(lpTmp);
	}
	else if( nlen == 0 && (nUnLen > 0) )
	{
		CFileDialog dlg(false,NULL,NULL,NULL,"�����ļ�(*.*)|*.*||",NULL);   
		//��һ����������Ϊture��ʾ�Ǵ��ļ�false��ʾ�Ǳ����ļ�
		
		if(dlg.DoModal()==IDOK)            //��ʾ�Ի��򲢷���(IDOK��IDCANCEL)�ֱ��ǰ��˴򿪺�ȡ��
		{
			CString str;
			nUnLen = WriteBufToFile(dlg.GetPathName().GetBuffer(0), lpUnBuf, nUnLen);
			if(nUnLen)
			{
				str.Format("��ѹ�ɹ�!\r\n���ݱ���·��:\r\n%s", dlg.GetPathName());
			}
			else
			{
				str.Format("��ѹ�ɹ�!\r\n���ݱ���ʧ��");
			}
			
			SetDlgItemText(IDC_EDIT_OUTBUF, str);
			
		}
		else
		{
			SetDlgItemText(IDC_EDIT_OUTBUF,"ȡ�������ݱ���!");
		}
	}
	else
	{
		SetDlgItemText(IDC_EDIT_OUTBUF,"��ѹʧ��");
	}
	free_zlib_prt(lpUnBuf);
	free(lpEnBuf);
}

int CHexToJavaByteDlg::WriteBufToFile(char *pPath, unsigned char *pbuf, int len)
{
	int iret = 0;
	FILE *fw = fopen(pPath, "wb");
	if(NULL == fw)
	{
		return 0;
	}
	iret = fwrite(pbuf, 1, len, fw);
	fclose(fw);
	return iret;
}

int CHexToJavaByteDlg::ReadFileToBuf(char *path, unsigned char **p)
{
	int iret = 0;
	if(path)
	{
		FILE *fr = fopen(path, "rb");
		if(fr)
		{
			fseek(fr, 0, SEEK_END);
			int len = ftell(fr);
			fseek(fr, 0, SEEK_SET);
			*p = (unsigned char *)malloc(len + 1);
			memset(*p, 0, len + 1);
			iret = fread(*p, 1, len, fr);
			fclose(fr);
		}
	}
	
	
	return iret;
}
