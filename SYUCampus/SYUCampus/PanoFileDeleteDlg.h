#pragma once


// CPanoFileDeleteDlg ��ȭ �����Դϴ�.

#include "CachedBmpOut.h"
#include "afxwin.h"

class CPanoFileDeleteDlg : public CDialog
{
	DECLARE_DYNAMIC(CPanoFileDeleteDlg)

public:
	CPanoFileDeleteDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPanoFileDeleteDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PANOFILEDELETE };

public:
	CCachedBmpOut m_BufferedImg;
	CPoint m_ImgPt;
	CString m_FileName;
	CString m_FileFullPath;

	int m_CurSel;
	BOOL m_bDraw;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_FileListBox;

	void RefreshList( void );
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnListdelete();
	afx_msg void OnBnClickedBtnFiledelete();
	afx_msg void OnBnClickedCancel();
};
