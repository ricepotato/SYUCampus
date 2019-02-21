#pragma once


// CPanoFileAddDlg 대화 상자입니다.
// 메뉴에서 파노라마 파일 추가를 눌렀을 경우 뜨는 다이얼로그 박스입니다.
#include "CachedBmpOut.h"

class CPanoFileAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CPanoFileAddDlg)

public:
	CPanoFileAddDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPanoFileAddDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PANOFILEADD };
public:
	CCachedBmpOut m_BufferedImg;
	CPoint m_ImgPt;
	CString m_FileName;
	CString m_FileFullPath;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnFindfile();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnFileadd();
};
