#pragma once

#include "CachedBmpOut.h"
// CSatelliteViewWnd

class CSatelliteViewWnd : public CWnd
{
	DECLARE_DYNAMIC(CSatelliteViewWnd)

public:
	CSatelliteViewWnd();
	virtual ~CSatelliteViewWnd();

	void SetImagePosToClientPoint( CPoint PtOnImg );

	void MySetWindowSize( CPoint Pt, CSize sz );

	void OnMyMinimize( void );
	void OnMyMaximize( void );

	void OpenViewPointAddDlg( void );

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

	// 뷰 포인트를 클릭했을 경우 어느 방향을 보고 있는지 나타내는 동심원이 나타납니다.
	// 그 동심원의 좌표입니다.
	CPoint m_ViewerPt;
	// 이 변수는 최소화를 클릭했을 경우와 뷰포인트를 클릭했을경우를 구분하기 위해 사용됩니다.
	BOOL m_ViewPtClicked;

	double m_lfDirection;
	int m_nEast;

	// 클라이언트 영역 입니다.
	CRect m_ClientRect;
	// 이미지 위치입니다.
	CPoint m_ImgPos;

private:

	CCachedBmpOut m_BuildingName;

	LONG WndLong; // 윈도우 속성이 저장되는 LONG 변수
	// 현재 설정이 저장되는 LONG 변수입니다.
	LONG WndCurrentLong;
	// 움직임 마우스 커서입니다.
	
	// 현재 마우스 위치가 저장되는 맴버변수입니다.
	// 뷰 포인터를 마우스에 갖다 댔을 때 마우스커서가 변하게 됩니다(이때 사용됩니다)
	CPoint m_CurMousePos;

	// MySetWindowSize 함수가 호출될때 원하는 크기가 저장되는 맴버변수입니다.
	CSize m_ChangedSize;
	CPoint m_ChangedPoint;
	
	// 뷰포인트를 클릭했을 경우 TRUE 가 됩니다.
	
	// 오른쪽 위 최소화 버튼에 마우스 오버 했을 경우 ㅇㅣ 변수가 TRUE 로 바뀝니다.
	BOOL m_RightTop;
	// 뷰포인트에 마우스 오버 했을 경우 이 변수가 TRUE 로 바뀝니다.
	BOOL m_LinkPoint;

	
	
	CString ErrorMsg;

	CCachedBmpOut m_BufferdImg; // 이미지 출력 객체
	double m_lfRatio; // 배율
	BOOL m_bClicked; // 클릭 여부
	CPoint m_PrevMousePos; // 이전 마우스 위치
	CPoint m_MousePos; // 마우스 위치

	BOOL m_bSizeChanged; //

	
	// 날개 위에 마우스를 올렸을 경우 TRUE 가 도비니다.
	BOOL m_bMouseOver;

	CRect m_RightTopRt;
	CRect m_MaximizeRt;
	BOOL m_bMaximizeMouseOver;
	CPoint m_RbuttonPt;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
//	afx_msg void OnPopupAddviewSate();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
//	afx_msg void OnUpdatePopupAddviewSate(CCmdUI *pCmdUI);
};


