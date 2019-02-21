#pragma once
#include "afxcmn.h"


// CViewFilePointDlg ��ȭ �����Դϴ�.

class CViewFilePointDlg : public CDialog
{
	DECLARE_DYNAMIC(CViewFilePointDlg)

public:
	CViewFilePointDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CViewFilePointDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_VIEWFILEPOINTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	BOOL SaveFileLinkData( void ) ;
	void RefreshList( void );
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ListCtrl;
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

private:
	int m_nCurSel;

public:
	afx_msg void OnBnClickedBtnDelete();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
