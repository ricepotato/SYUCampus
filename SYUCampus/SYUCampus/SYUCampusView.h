
// SYUCampusView.h : CSYUCampusView 클래스의 인터페이스
//


#pragma once

#include "CachedBmpOut.h"
#include "SYUCampusDoc.h"


class CSYUCampusView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSYUCampusView();
	DECLARE_DYNCREATE(CSYUCampusView) 

// 특성입니다.
public:
	CSYUCampusDoc* GetDocument() const;

// 작업입니다.
public:
	CPoint m_ImgPos; // 이미지위 위치입니다.
	CCachedBmpOut m_BufferdImg; // 이미지 출력 객체입니다.
	double m_lfRatio; // 이미지 출력 배율입니다.

	CCachedBmpOut m_BufferdSybol; // 학교 심벌 출력 객체
	BOOL m_bLoaded; // 로드 여부

	BOOL LoadImage( TCHAR *FileName ); // 이미지 로드 함수
	CRect m_ClientRect; // 클라이언트 영역의 Rect 가 저장되는 변수
	CString m_LoadedFileName; // 로드된 파일 이름입니다. 경로가 포함되어있지 않습니다.

	void SetImagePosRight( void ); // 이미지의 위치를 올바르게 만드는 함수입니다.
	void SetImageRatio( double lfRatio ); // 이미지의 크기가 변경될때 호출됩니다. 현재 파노라마 사진의 중앙이 축소/확대된 뒤에도 유지되도록 합니다.

	int m_nEast; // 이 값은 이미지상의 x 좌표가 안내도의 동쪽임을 나타내는 값입니다.
	int m_nSatelliteEast; // 이 값은 이미지상의 x 좌표가 위성 사진의 동쪽임을 나타내는 값입니다.	
	CPoint m_CurMousePos; // 이 값은 RButtonUp 메시지가 발생할때 마우스 위치 값을 갖습니다.

	CObList m_LinkFileList; // 이 리스트는 뷰 윈도우 상에 나타나는 링크의 리스트를 가지고 있습니다.

	int GetClientWidth( void ); // 클라이언트 영역의 가로크기를 리턴합니다.
	int GetClientHeight( void ); // 클라이언트 영역의 세로크기를 리턴합니다.

	// 링크 포인트를 로드합니다.
	BOOL LoadFileLinkData( void );
	void LoadFileLinkPoint( void );	

	// 방향을 계산합니다.
	void CalculateDirection( void );

	BOOL m_bNowLoading;

	BOOL IsImageSizeRight( double ratio ); // 변형된 이미지 크기가 클라이언트 영역보다 작은지 알아냅니다.
private:
	BOOL m_bClicked;
	CPoint m_PrevMousePos;
	CPoint m_MousePos;	
	

	// 좌 우 상 하 화살표 사각영역
	CRect m_DirectionMarkRect[4];
	// 좌 우 상하 화살표 마우스 오버 BOOL 변수
	// 마우스 오버 되면 TRUE 
	BOOL m_bDirectionMarkMouseOver[4];

	BOOL m_bLinkPointMouseOver;

	CCachedBmpOut m_ImageLoading;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CSYUCampusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRatio10();
	afx_msg void OnRatio08();
	afx_msg void OnRatio06();
	afx_msg void OnRatio04();
	afx_msg void OnUpdateRatio08(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRatio10(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRatio06(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRatio04(CCmdUI *pCmdUI);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnUpdateZoomin(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZoomout(CCmdUI *pCmdUI);
	afx_msg void OnRatioUser();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SYUCampusView.cpp의 디버그 버전
inline CSYUCampusDoc* CSYUCampusView::GetDocument() const
   { return reinterpret_cast<CSYUCampusDoc*>(m_pDocument); }
#endif

