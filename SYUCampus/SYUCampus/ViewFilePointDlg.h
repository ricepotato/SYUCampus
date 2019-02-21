#pragma once
#include "afxcmn.h"


// CViewFilePointDlg 대화 상자입니다.

class CViewFilePointDlg : public CDialog
{
	DECLARE_DYNAMIC(CViewFilePointDlg)

public:
	CViewFilePointDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CViewFilePointDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VIEWFILEPOINTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
