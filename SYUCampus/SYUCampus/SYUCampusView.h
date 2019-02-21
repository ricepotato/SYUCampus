
// SYUCampusView.h : CSYUCampusView Ŭ������ �������̽�
//


#pragma once

#include "CachedBmpOut.h"
#include "SYUCampusDoc.h"


class CSYUCampusView : public CView
{
protected: // serialization������ ��������ϴ�.
	CSYUCampusView();
	DECLARE_DYNCREATE(CSYUCampusView) 

// Ư���Դϴ�.
public:
	CSYUCampusDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	CPoint m_ImgPos; // �̹����� ��ġ�Դϴ�.
	CCachedBmpOut m_BufferdImg; // �̹��� ��� ��ü�Դϴ�.
	double m_lfRatio; // �̹��� ��� �����Դϴ�.

	CCachedBmpOut m_BufferdSybol; // �б� �ɹ� ��� ��ü
	BOOL m_bLoaded; // �ε� ����

	BOOL LoadImage( TCHAR *FileName ); // �̹��� �ε� �Լ�
	CRect m_ClientRect; // Ŭ���̾�Ʈ ������ Rect �� ����Ǵ� ����
	CString m_LoadedFileName; // �ε�� ���� �̸��Դϴ�. ��ΰ� ���ԵǾ����� �ʽ��ϴ�.

	void SetImagePosRight( void ); // �̹����� ��ġ�� �ùٸ��� ����� �Լ��Դϴ�.
	void SetImageRatio( double lfRatio ); // �̹����� ũ�Ⱑ ����ɶ� ȣ��˴ϴ�. ���� �ĳ�� ������ �߾��� ���/Ȯ��� �ڿ��� �����ǵ��� �մϴ�.

	int m_nEast; // �� ���� �̹������� x ��ǥ�� �ȳ����� �������� ��Ÿ���� ���Դϴ�.
	int m_nSatelliteEast; // �� ���� �̹������� x ��ǥ�� ���� ������ �������� ��Ÿ���� ���Դϴ�.	
	CPoint m_CurMousePos; // �� ���� RButtonUp �޽����� �߻��Ҷ� ���콺 ��ġ ���� �����ϴ�.

	CObList m_LinkFileList; // �� ����Ʈ�� �� ������ �� ��Ÿ���� ��ũ�� ����Ʈ�� ������ �ֽ��ϴ�.

	int GetClientWidth( void ); // Ŭ���̾�Ʈ ������ ����ũ�⸦ �����մϴ�.
	int GetClientHeight( void ); // Ŭ���̾�Ʈ ������ ����ũ�⸦ �����մϴ�.

	// ��ũ ����Ʈ�� �ε��մϴ�.
	BOOL LoadFileLinkData( void );
	void LoadFileLinkPoint( void );	

	// ������ ����մϴ�.
	void CalculateDirection( void );

	BOOL m_bNowLoading;

	BOOL IsImageSizeRight( double ratio ); // ������ �̹��� ũ�Ⱑ Ŭ���̾�Ʈ �������� ������ �˾Ƴ��ϴ�.
private:
	BOOL m_bClicked;
	CPoint m_PrevMousePos;
	CPoint m_MousePos;	
	

	// �� �� �� �� ȭ��ǥ �簢����
	CRect m_DirectionMarkRect[4];
	// �� �� ���� ȭ��ǥ ���콺 ���� BOOL ����
	// ���콺 ���� �Ǹ� TRUE 
	BOOL m_bDirectionMarkMouseOver[4];

	BOOL m_bLinkPointMouseOver;

	CCachedBmpOut m_ImageLoading;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CSYUCampusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // SYUCampusView.cpp�� ����� ����
inline CSYUCampusDoc* CSYUCampusView::GetDocument() const
   { return reinterpret_cast<CSYUCampusDoc*>(m_pDocument); }
#endif

