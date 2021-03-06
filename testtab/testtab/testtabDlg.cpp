// testtabDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "testtab.h"
#include "testtabDlg.h"
#include "CTaskMgr.h"
#include "CNetWork.h"
#include "RegeDitDlg.h"
#include "FileExplorer.h"
#include  "StartMag.h"
#include "FileView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
	//	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CtesttabDlg 对话框


CYouHuaDlg::CYouHuaDlg(CWnd* pParent /*=NULL*/)
: CDialog(CYouHuaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYouHuaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabctr);
}

BEGIN_MESSAGE_MAP(CYouHuaDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CYouHuaDlg::OnTcnSelchangeTab1)

END_MESSAGE_MAP()


// CtesttabDlg 消息处理程序

BOOL CYouHuaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标



	HICON m_hIcon1 = ::LoadIcon( ::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1) );
	HICON m_hIcon2 = ::LoadIcon( ::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2) );
	HICON m_hIcon3 = ::LoadIcon( ::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON3) );
	HICON m_hIcon4 = ::LoadIcon( ::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON4) );
	HICON m_hIcon5 = ::LoadIcon( ::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON5) );
	HICON m_hIcon6 = ::LoadIcon( ::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1) );

	if(0==m_ImageTab.Create(16,16,ILC_COLOR32|ILC_MASK,2,2))
	{
		ASSERT(0);
		return -1;
	}

	TCITEM item;
	RECT      rc;
	item.mask = TCIF_TEXT;
	item.pszText = L"Process";
	item.cchTextMax = 200;

	m_para1.Create (IDD_TASKMGR,&m_tabctr);
	if(-1 ==m_ImageTab.Add(m_hIcon5))
	{
		ASSERT(0);
		return -1;
	}
	m_tabctr.SetImageList(&m_ImageTab);
	m_tabctr.InsertItem (0,item.pszText,0);


	item.pszText =L"network"; 
	m_para2.Create(IDD_NETWORK,&m_tabctr);
	if(-1 == m_ImageTab.Add(m_hIcon4))
	{
		ASSERT(0);
		return -1;
	}
	m_tabctr.SetImageList(&m_ImageTab);
	m_tabctr.InsertItem (1,item.pszText,1);

	item.pszText =L"File";
    m_para3.Create(IDD_FILEEXPLORER,&m_tabctr);
	m_ImageTab.Add(m_hIcon3);
	m_tabctr.SetImageList(&m_ImageTab);
	m_tabctr.InsertItem (2,item.pszText,2);

	item.pszText =L"StartUp";
	m_para4.Create(IDD_STARTMANGE,&m_tabctr);
	m_ImageTab.Add(m_hIcon2);
	m_tabctr.SetImageList(&m_ImageTab);
	m_tabctr.InsertItem (3,item.pszText,3);

	item.pszText =L"Clear";
	m_para5.Create(CRegeDitDlg::IDD,&m_tabctr);
	m_ImageTab.Add(m_hIcon1);
	m_tabctr.SetImageList(&m_ImageTab);
	m_tabctr.InsertItem (4,item.pszText,1);

	item.pszText =L"FileExplorer";
	m_para6.Create(CFileView::IDD,&m_tabctr);
	m_ImageTab.Add(m_hIcon1);
	m_tabctr.SetImageList(&m_ImageTab);
	m_tabctr.InsertItem (5,item.pszText,1);

	GetClientRect(&rc);
	rc.top += 25;
	rc.left += 1;
	rc.right -= 1;
	rc.bottom -= 2;

	m_para1.SetWindowPos (NULL,rc.left,rc.top,rc.right,rc.bottom,SWP_SHOWWINDOW);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CYouHuaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CYouHuaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CYouHuaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CYouHuaDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	CRect r;
	m_tabctr.GetClientRect (&r);

	switch(m_tabctr.GetCurSel())
	{
	case 0:
		m_para1.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_SHOWWINDOW);
		m_para2.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW );
		m_para3.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para4.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para5.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para6.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		//m_para7.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		break;
	case 1:
		m_para1.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para2.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_SHOWWINDOW ); 
		m_para3.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para4.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para5.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
			m_para6.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		//m_para7.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		break;
	case 2:
		m_para1.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para2.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW); 
		m_para3.SetWindowPos(NULL,10,30,r.right-20,r.bottom-40,SWP_SHOWWINDOW);
		m_para4.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para5.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para6.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		//m_para7.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		break;

	case 3:
		m_para1.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para2.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW); 
		m_para3.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para4.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_SHOWWINDOW);
		m_para5.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para6.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		//m_para7.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		break;
	case 4:
		m_para1.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para2.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW); 
		m_para3.SetWindowPos(NULL,10,30,r.right - 20,r.bottom -40,SWP_HIDEWINDOW);
		m_para3.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para4.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para5.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_SHOWWINDOW);
			m_para6.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		//m_para7.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		break;

	case  5:
		m_para1.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para2.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW); 
		m_para3.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para4.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para5.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		m_para6.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_SHOWWINDOW);
		//m_para7.SetWindowPos (NULL,10,30,r.right -20,r.bottom -40,SWP_HIDEWINDOW);
		break;

	}
	*pResult = 0;

}

void CYouHuaDlg::OnBnClickedButton1()
{


}

//LRESULT CAboutDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	return CDialog::WindowProc(message, wParam, lParam);
//}
