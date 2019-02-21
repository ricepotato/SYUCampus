#pragma once
#include "afxwin.h"


// CUserRatio 대화 상자입니다.

class CUserRatio : public CDialog
{
	DECLARE_DYNAMIC(CUserRatio)

public:
	CUserRatio(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUserRatio();

	double m_lfViewRatio;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_USERRATIO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	double m_lfRatioEdit;
	afx_msg void OnBnClickedRadio1();
	int m_nSetRadioCtrl;
	afx_msg void OnBnClickedRadioSetscr();
	CEdit m_nRatioEditCtrl;
	afx_msg void OnBnClickedRadioSetsize();
	afx_msg void OnBnClickedOk();
};
