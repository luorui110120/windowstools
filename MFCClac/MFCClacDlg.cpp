// MFCClacDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCClac.h"
#include "MFCClacDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCClacDlg dialog

CMFCClacDlg::CMFCClacDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCClacDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMFCClacDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCClacDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMFCClacDlg)
	DDX_Control(pDX, IDC_TAB, m_table);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMFCClacDlg, CDialog)
	//{{AFX_MSG_MAP(CMFCClacDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_TAB, OnClickTab)
	ON_NOTIFY(NM_RCLICK, IDC_TAB, OnRclickTab)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_TAB, OnOutofmemoryTab)
	ON_NOTIFY(TCN_KEYDOWN, IDC_TAB, OnKeydownTab)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB, OnSelchangingTab)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_NOTIFY(TCN_GETOBJECT, IDC_TAB, OnGetobjectTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCClacDlg message handlers

BOOL CMFCClacDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_table.InsertItem(0,"Table-1");  //添加参数一选项卡
//	m_table.InsertItem(1,"参数二");  //添加参数二选项卡
//	m_table.InsertItem(2,"结果");    //添加结果选项卡
	m_ClacDlg.Create(IDD_DIALOG, GetDlgItem(IDC_TAB));
//	m_ClacDlg.Init();
	CRect rs;
	m_table.GetClientRect(&rs);
	//调整子对话框在父窗口中的位置
	rs.top+=16;
	rs.bottom-=2;
	rs.left+=1;
	rs.right-=2;
    
	//设置子对话框尺寸并移动到指定位置
	m_ClacDlg.MoveWindow(&rs);
	
	//分别设置隐藏和显示
	m_ClacDlg.ShowWindow(true);
    
	//设置默认的选项卡
	m_table.SetCurSel(0);

	CClac *lpClass = new CClac(m_ClacDlg);
	m_vClacs.Add(lpClass);
	m_ClacDlg.Clear();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCClacDlg::OnPaint() 
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
HCURSOR CMFCClacDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMFCClacDlg::OnClickTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(m_nSel == m_table.GetCurSel())
	{
		if(m_table.GetItemCount() > 1)
		{
			int nIndex = m_table.GetCurSel();
			if(nIndex > 0)
			{
				nIndex--;
			}
			delete *m_vClacs.GetAt(m_table.GetCurSel());
			m_vClacs.RemoveAt(m_table.GetCurSel());
			m_table.DeleteItem(m_table.GetCurSel());
			m_table.SetCurSel(nIndex);
			m_ClacDlg.SetValues(*m_vClacs.GetAt(nIndex));
			m_ClacDlg.UpdateData(FALSE);
			m_table.InvalidateRect (NULL, TRUE) ;
			m_table.UpdateWindow();
			
		}	
		m_nSel = -1;
	}
	else
	{
		if(m_table.GetItemCount() > 1)
		{
			m_ClacDlg.SetValues(*m_vClacs.GetAt(m_table.GetCurSel()));
			m_ClacDlg.UpdateData(FALSE);
		}
		m_nSel = m_table.GetCurSel();
	}

	*pResult = 0;
}

void CMFCClacDlg::OnRclickTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_ClacDlg.UpdateData(TRUE);
	m_vClacs.GetAt(m_table.GetCurSel())->SetValues(m_ClacDlg);
	int nTable = m_table.GetItemCount();
	CString str = "";
	str.Format("Table-%d", nTable + 1);
	m_table.InsertItem(nTable, str);
	m_table.SetCurSel(nTable);
	
	CClac *lpClass = new CClac();
	m_vClacs.Add(lpClass);
	m_ClacDlg.Clear();
	m_nSel = -1;
	m_table.InvalidateRect (NULL, TRUE) ;
	m_table.UpdateWindow();
	*pResult = 0;
}

void CMFCClacDlg::OnOutofmemoryTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//	AfxMessageBox("OnOutofmemoryTab");
	*pResult = 0;
}

void CMFCClacDlg::OnKeydownTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TC_KEYDOWN* pTCKeyDown = (TC_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CMFCClacDlg::OnSelchangingTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//	CClac *lpClass = new CClac(m_ClacDlg);
	m_ClacDlg.UpdateData(TRUE);
	if(m_table.GetCurSel() >= 0)
	{
		m_vClacs.GetAt(m_table.GetCurSel())->SetValues(m_ClacDlg);
	}
	
	*pResult = 0;
}

void CMFCClacDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CMFCClacDlg::OnGetobjectTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMOBJECTNOTIFY* pTCObjectNotify = (NMOBJECTNOTIFY*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
