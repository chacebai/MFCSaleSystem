// InfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "InfoDlg.h"
#include "InfoFile.h"


// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)

CInfoDlg::CInfoDlg()
	: CFormView(CInfoDlg::IDD)
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
END_MESSAGE_MAP()


// CInfoDlg diagnostics

#ifdef _DEBUG
void CInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoDlg message handlers


void CInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	//设置扩展风格
	/////|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES,整行选中，网格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//初始化表头
	CString field[] = {TEXT("商品ID"),TEXT("商品名称"),TEXT("商品单价"),TEXT("商品库存")};

	for(int i=0; i<sizeof(field)/sizeof(field[0]);++i)
	{
		m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 90);
	}

	CInfoFile file;
	file.ReadDocline();	//读取商品信息
	// 添加数据
	int i=0;
	CString str;
	for(list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		str.Format(TEXT("%d"),it->id);
		m_list.InsertItem(i,str);
		int column = 1;
		m_list.SetItemText(i, column++, (CString)it->name.c_str());
		str.Format(TEXT("%d"),it->price);
		m_list.SetItemText(i, column++, str);
		str.Format(TEXT("%d"),it->num);
		m_list.SetItemText(i, column++, str);

		m_list.SetItemData(i,i);//用于存储排序关键字
		i++;
	}
}
