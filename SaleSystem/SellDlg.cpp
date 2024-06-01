// SellDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "SellDlg.h"
#include "InfoFile.h"


// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(CSellDlg::IDD)
	, m_price(0)
	, m_left(0)
	, m_num(0)
	, m_sellInfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combox);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_left);
	DDX_Text(pDX, IDC_EDIT5, m_num);
	DDX_Text(pDX, IDC_EDIT4, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSellDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSellDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CSellDlg diagnostics

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg message handlers


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	// 初始化消息订单窗口
	// 初始化下拉框
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


void CSellDlg::OnCbnSelchangeCombo1()
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
			m_price = it->price;
			m_left = it->num;
			// 同步到控件
			UpdateData(FALSE);
			break;
		}
	}
}


void CSellDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// 购买的功能实现
	if (m_num <= 0)
	{
		MessageBox(TEXT("购买数量不能小于0"));
		return;
	}
	// 购买的数量不能大于库存
	if (m_num > m_left)
	{
		MessageBox(TEXT("购买数量不能大于库存"));
		return;
	}
	// 购买
	int index = m_combox.GetCurSel();
	CString name;
	m_combox.GetLBText(index, name);
	
	CInfoFile file;
	file.ReadDocline();
	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		CString tempStr(it->name.c_str());
		if (tempStr.Compare(name) == 0)
		{
			// 同步库存量
			it->num = m_left - m_num;
			m_left = it->num;
			// 提示购买信息
			CString str;
			str.Format(_T("商品名：%s \r\n购买数量：%d \r\n单价：%d \r\n总价：%d"),name, m_num, m_price, m_price*m_num);
			m_sellInfo = str;
			UpdateData(FALSE);
			MessageBox(_T("购买成功！"));
			break;
		}
	}

	file.WirteDocline();
	//清空数据
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);
}


void CSellDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	//清空数据
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);
}
