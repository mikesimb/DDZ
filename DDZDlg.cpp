
// DDZDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DDZ.h"
#include "DDZDlg.h"
#include "afxdialogex.h"
#include "DDZ_Game.h"
#include "FileUtils.h"
#include "Log.h"
#include "ZQString.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDDZDlg 对话框



CDDZDlg::CDDZDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DDZ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDDZDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDDZDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDDZDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDDZDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDDZDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDDZDlg 消息处理程序

BOOL CDDZDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDDZDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDDZDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDDZDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDDZDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_DDZ_Game = new CDDZ_Game();
	m_DDZ_Game->Initialize_Game();
	m_DDZ_Game->StartGame();
	m_DDZ_Game->SendCardtoPlayer(0);
	m_DDZ_Game->Fightforlandlord();
	m_DDZ_Game->FightforLandlordEnd();
}


void CDDZDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (FileExists("F:\\Key.txt"))
		OutputDebugString("文件存在");
	else
		OutputDebugString("文件不存在");
	
}


void CDDZDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CLog::getInstance()->InitializeLogFile();
	CLog::getInstance()->WriteLog("kaksjfaksfj", 11);

	CLog::getInstance()->WriteLog("上天啊上帝啊我治安和四代是发啊发顺丰", 11);
//	delete CLog::getInstance();



	
	CZQString zl = "kkkkkkkk";

	CZQString zl1 = "LLLLLLLL";
	CZQString zl2 = zl1 + zl + "/n";
	OutputDebugString((char*)(zl2));
	if (zl1 == zl2)
		OutputDebugString("zl1 == zl2");
	else
		OutputDebugString("zl1 != zl2");
	
}
