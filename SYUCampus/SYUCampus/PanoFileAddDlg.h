#pragma once


// CPanoFileAddDlg ��ȭ �����Դϴ�.
// �޴����� �ĳ�� ���� �߰��� ������ ��� �ߴ� ���̾�α� �ڽ��Դϴ�.
#include "CachedBmpOut.h"

class CPanoFileAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CPanoFileAddDlg)

public:
	CPanoFileAddDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPanoFileAddDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PANOFILEADD };
public:
	CCachedBmpOut m_BufferedImg;
	CPoint m_ImgPt;
	CString m_FileName;
	CString m_FileFullPath;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnFindfile();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnFileadd();
};
