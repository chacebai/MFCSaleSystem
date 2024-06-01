
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "SaleSystem.h"

#include "MainFrm.h"
#include "InfoFile.h"
#include "SelectView.h"
#include "DisplayView.h"
#include "UserDlg.h"
#include "SellDlg.h"
#include "InfoDlg.h"
#include "AddDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 避免C4996错误
#define _CRT_SECURE_NO_WARNINGS

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)

	ON_COMMAND(ID_32771, &CMainFrame::On32771)
	ON_COMMAND(ID_32772, &CMainFrame::On32772)
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


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	// return CFrameWnd::OnCreateClient(lpcs, pContext);

	// 一行两列
	m_spliter.CreateStatic(this, 1, 2);
	// 左侧和右侧具体显示的内容
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200,500), pContext);
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600,500), pContext);
	return TRUE;
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext context;
	if (wParam == NM_A)
	{
		// MessageBox(TEXT("个人信息挂载"));
		// 挂载界面
		context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 500), &context);
		CUserDlg *pNewView = (CUserDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_B)
	{
		// MessageBox(TEXT("销售管理挂载"));
		context.m_pNewViewClass = RUNTIME_CLASS(CSellDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CSellDlg), CSize(600, 500), &context);
		CSellDlg *pNewView = (CSellDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_C)
	{
		// MessageBox(TEXT("库存信息挂载"));
		context.m_pNewViewClass = RUNTIME_CLASS(CInfoDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CInfoDlg), CSize(600, 500), &context);
		CInfoDlg *pNewView = (CInfoDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_D)
	{
		// MessageBox(TEXT("添加商品挂载"));
		context.m_pNewViewClass = RUNTIME_CLASS(CAddDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAddDlg), CSize(600, 500), &context);
		CAddDlg *pNewView = (CAddDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_E)
	{
		MessageBox(TEXT("暂未实现"));
	}
	return 0;
}


void CMainFrame::On32771()
{
	// TODO: Add your command handler code here
	// 个人信息
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
}


void CMainFrame::On32772()
{
	// TODO: Add your command handler code here
	// 销售管理
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
}
