#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "CachedBmpOut.h"


// CPanoFileShowDlg ��ȭ �����Դϴ�.

class CPanoFileShowDlg : public CDialog
{
	DECLARE_DYNAMIC(CPanoFileShowDlg)

public:
	CPanoFileShowDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPanoFileShowDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PANOFILESHOWDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	CCachedBmpOut m_BufferedImg;
	
	CRect m_ImgOutRect;
	CPoint m_ImgPt;
	BOOL m_bDraw;

	void RefreshList( void );

	virtual BOOL OnInitDialog();
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	BOOL m_bInsert; // �Է����� ��ȭ���ڸ� ��������, �������� �������� �˷��ݴϴ�.
	BOOL m_bSatellite; // ���� �並 ��Ŭ�������� TURE �� �˴ϴ�.
	BOOL m_bTopView; // �ȳ����� ��Ŭ�������� TRUE  �� �˴ϴ�.	

	int m_EditEast;
	int m_PosX;
	int m_PosY;

	int m_nSatelliteEast;
	int m_nSatellitePosX;
	int m_nSatellitePosY;

	CString m_EditFileName;

	CButton m_Btn_Delete;
	CButton m_Btn_Modify;
	CEdit m_Edit_East;
	CEdit m_Edit_PosX;
	CEdit m_Edit_PosY;	

	int m_SelectedItem;	
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnInsert();

	
	afx_msg void OnPaint();
};
