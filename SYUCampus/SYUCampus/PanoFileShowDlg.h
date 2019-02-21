#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "CachedBmpOut.h"


// CPanoFileShowDlg 대화 상자입니다.

class CPanoFileShowDlg : public CDialog
{
	DECLARE_DYNAMIC(CPanoFileShowDlg)

public:
	CPanoFileShowDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPanoFileShowDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PANOFILESHOWDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
	BOOL m_bInsert; // 입력으로 대화상자를 열었는지, 설정으로 열었는지 알려줍니다.
	BOOL m_bSatellite; // 위성 뷰를 우클릭했을때 TURE 가 됩니다.
	BOOL m_bTopView; // 안내도를 우클릭했을때 TRUE  가 됩니다.	

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
