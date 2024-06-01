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
	// ��ʼ����Ϣ��������
	// ��ʼ��������
	CInfoFile file;
	file.ReadDocline();
	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		m_combox.AddString(CString(it->name.c_str()));
	}

	// Ĭ��ѡ�е�һ��
	m_combox.SetCurSel(0);
	// ���µ�һ����Ʒ�������
	OnCbnSelchangeCombo1();
}


void CSellDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	// �л���Ʒ�����¼�
	// �Ȼ�ȡ��Ʒ����
	int index = m_combox.GetCurSel();
	// ����������ȡ����
	CString name;
	m_combox.GetLBText(index, name);
	// ������Ʒ�����ȡ����Ʒ�۸��� ������ʾ���ؼ���
	CInfoFile file;
	file.ReadDocline();
	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		CString tempStr(it->name.c_str());
		if (tempStr.Compare(name) == 0)
		{
			m_price = it->price;
			m_left = it->num;
			// ͬ�����ؼ�
			UpdateData(FALSE);
			break;
		}
	}
}


void CSellDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	// ����Ĺ���ʵ��
	if (m_num <= 0)
	{
		MessageBox(TEXT("������������С��0"));
		return;
	}
	// ������������ܴ��ڿ��
	if (m_num > m_left)
	{
		MessageBox(TEXT("�����������ܴ��ڿ��"));
		return;
	}
	// ����
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
			// ͬ�������
			it->num = m_left - m_num;
			m_left = it->num;
			// ��ʾ������Ϣ
			CString str;
			str.Format(_T("��Ʒ����%s \r\n����������%d \r\n���ۣ�%d \r\n�ܼۣ�%d"),name, m_num, m_price, m_price*m_num);
			m_sellInfo = str;
			UpdateData(FALSE);
			MessageBox(_T("����ɹ���"));
			break;
		}
	}

	file.WirteDocline();
	//�������
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);
}


void CSellDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	//�������
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);
}
