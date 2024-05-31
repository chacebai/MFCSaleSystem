// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "InfoFile.h"


// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg message handlers


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	// 登录按钮点击事件
	UpdateData(TRUE);
	if (m_user.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空"));
		return;
	}

	// 获取正确的值
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	if (name == m_user)
	{
		if (pwd == m_pwd)
		{
			// 关闭当前对话框
			CDialog::OnCancel();
		}
		else
		{
			MessageBox(TEXT("密码有误"));
		}
	}
	else
	{
		MessageBox(TEXT("用户名有误"));
	}
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	// 默认登录信息
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	m_user = name;
	m_pwd = pwd;

	// 同步到控件
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CLoginDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	exit(0);
}


void CLoginDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	// 防止点击回车继续
	// CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	// 关闭当前对话框
	// CDialogEx::OnClose();

	// 退出程序
	exit(0);
}
