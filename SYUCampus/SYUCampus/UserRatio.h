#pragma once
#include "afxwin.h"


// CUserRatio ��ȭ �����Դϴ�.

class CUserRatio : public CDialog
{
	DECLARE_DYNAMIC(CUserRatio)

public:
	CUserRatio(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUserRatio();

	double m_lfViewRatio;

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_USERRATIO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
