// AddDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "AddDlg.h"
#include "InfoFile.h"


// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(CAddDlg::IDD)
	, m_price1(0)
	, m_num1(0)
	, m_name2(_T(""))
	, m_price2(0)
	, m_num2(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combox);
	DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT2, m_num1);
	DDX_Text(pDX, IDC_EDIT5, m_name2);
	DDX_Text(pDX, IDC_EDIT6, m_price2);
	DDX_Text(pDX, IDC_EDIT7, m_num2);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CAddDlg diagnostics

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg message handlers


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CInfoFile file;
	file.ReadDocline();
	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		m_combox.AddString(CString(it->name.c_str()));
	}

	// 默认选中第一个
	m_combox.SetCurSel(0);
	// 更新第一个商品里的数据
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	// 切换商品触发事件
	// 先获取商品名称
	int index = m_combox.GetCurSel();
	// 根据索引获取内容
	CString name;
	m_combox.GetLBText(index, name);
	// 根据商品名你获取到商品价格库存 并且显示到控件中
	CInfoFile file;
	file.ReadDocline();
	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		CString tempStr(it->name.c_str());
		if (tempStr.Compare(name) == 0)
		{
			m_price1 = it->price;
			// 同步到控件
			UpdateData(FALSE);
			break;
		}
	}
}


void CAddDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// 添加功能的实现
	if(m_num1 <= 0)
	{
		MessageBox(TEXT("添加个数不能小于等于0"));
		return;
	}

	//购买
	//获取到具体的要购买的商品名称
	CString name;
	int index = m_combox.GetCurSel();
	m_combox.GetLBText(index, name);

	CInfoFile file;
	file.ReadDocline();
	for(list<msg>::iterator it=file.ls.begin(); it != file.ls.end(); it++)
	{
		CString tempStr(it->name.c_str());
		if (tempStr.Compare(name) == 0)
		{
			// 添加库存
			it->num = it->num + m_num1;
			m_num1 = 0;
			MessageBox(_T("添加成功！"));
			
		}
	}

	//清空数据
	file.WirteDocline();
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	//清空数据
	m_num1 = 0;
	UpdateData(FALSE);
	m_combox.SetCurSel(0);
	// 更新第一个商品里的数据
	OnCbnSelchangeCombo1();
}
