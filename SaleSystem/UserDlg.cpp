// UserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "UserDlg.h"
#include "InfoFile.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(CUserDlg::IDD)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_surePwd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserDlg diagnostics

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg message handlers


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_user = TEXT("销售员");

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	m_name = name;

	UpdateData(FALSE);

	// TODO: Add your specialized code here and/or call the base class
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	// 修改密码
	// 拿到最新的值
	UpdateData(TRUE);
	if (m_newPwd.IsEmpty() || m_surePwd.IsEmpty())
	{
		MessageBox(TEXT("输入的内容不能为空"));
		return;
	}
	// 新密码和确定密码要一致
	if (m_newPwd != m_surePwd)
	{
		MessageBox(TEXT("新密码与确定密码不一致"));
		return;
	}
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);
	if (m_newPwd == pwd)
	{
		MessageBox(TEXT("新密码与旧密码相同"));
		return;
	}
	// CString 转 char*
	CStringA tmp, tmp2;
	tmp = name;
	tmp2 = m_newPwd;
	file.WritePwd(tmp.GetBuffer(), tmp2.GetBuffer());
	MessageBox(TEXT("修改成功"));
	// 清空内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	// 取消修改密码
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}
