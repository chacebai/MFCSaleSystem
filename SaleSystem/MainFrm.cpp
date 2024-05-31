
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "SaleSystem.h"

#include "MainFrm.h"
#include "InfoFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 避免C4996错误
#define _CRT_SECURE_NO_WARNINGS

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// 设置图标
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_WIN));

	// 设置横杠右侧标题
	SetTitle(TEXT("2024/06/01"));

	// 设置窗口大小
	MoveWindow(0, 0, 800, 500);

	// 设置居中
	CenterWindow();

	// 测试CInfoFile
	/*CInfoFile file;
	CString name;
	CString pwd;
	// file.WritePwd("斧头帮帮主", "123");
	file.ReadLogin(name, pwd);
	MessageBox(name);
	MessageBox(pwd);*/

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序
