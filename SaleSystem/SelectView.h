#pragma once


// CSelectView view

class CSelectView : public CTreeView
{
	DECLARE_DYNCREATE(CSelectView)

protected:
	CSelectView();           // protected constructor used by dynamic creation
	virtual ~CSelectView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

private:
	// ���ؼ�
	CTreeCtrl *m_treeCtrl;
	// ͼ���б�
	CImageList m_imageList;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


