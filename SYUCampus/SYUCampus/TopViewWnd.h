#pragma once


#include "CachedBmpOut.h"

#define PANODATAFILE_NAME _T("PanoData.dat")

// CTopViewWnd

class CTopViewWnd : public CWnd
{
	DECLARE_DYNAMIC(CTopViewWnd)

public:
	CTopViewWnd();
	virtual ~CTopViewWnd();

	void MakeTransparentWnd( BYTE bAlpha );
	void MakeOpaqueWnd(void );

	void SetImagePosToClientPoint( CPoint PtOnImg );

	void MySetWindowSize( CPoint Pt, CSize sz );

	void OnMyMinimize( void );
	void OnMyMaximize( void );

	BOOL SaveFileLinkData( void );

	// �� ������ ���ο� �� ����Ʈ�� ����ϱ� ���� �� ������ �󿡼� �� Ŭ���� ���� ��� TRUE �� �Ǿ� Ȱ��ȭ �˴ϴ�.
	BOOL m_bNewLinkPointAdd;
	// �� ����Ʈ�� Ŭ������ ��� ��� ������ ���� �ִ��� ��Ÿ���� ���ɿ��� ��Ÿ���ϴ�.
	// �� ���ɿ��� ��ǥ�Դϴ�.
	CPoint m_ViewerPt; 	
	// �� ������ �ּ�ȭ�� Ŭ������ ���� ������Ʈ�� Ŭ��������츦 �����ϱ� ���� ���˴ϴ�.
	BOOL m_ViewPtClicked;

	double m_lfDirection;
	int m_nEast;
	CRect m_ClientRect;
	CPoint m_ImgPos;

private:

	CCachedBmpOut m_BuildingName;

	LONG WndLong; // ������ �Ӽ��� ����Ǵ� LONG ����
	// ���� ������ ����Ǵ� LONG �����Դϴ�.
	LONG WndCurrentLong;
	// ������ ���콺 Ŀ���Դϴ�.
	
	// ���� ���콺 ��ġ�� ����Ǵ� �ɹ������Դϴ�.
	// �� �����͸� ���콺�� ���� ���� �� ���콺Ŀ���� ���ϰ� �˴ϴ�(�̶� ���˴ϴ�)
	CPoint m_CurMousePos;

	// MySetWindowSize �Լ��� ȣ��ɶ� ���ϴ� ũ�Ⱑ ����Ǵ� �ɹ������Դϴ�.
	CSize m_ChangedSize;
	CPoint m_ChangedPoint;
	
	// ������Ʈ�� Ŭ������ ��� TRUE �� �˴ϴ�.
	
	// ������ �� �ּ�ȭ ��ư�� ���콺 ���� ���� ��� ���� ������ TRUE �� �ٲ�ϴ�.
	BOOL m_bRightTop;
	// ������Ʈ�� ���콺 ���� ���� ��� �� ������ TRUE �� �ٲ�ϴ�.
	BOOL m_LinkPoint;

	CCachedBmpOut m_BufferdImg; // �̹��� ��� ��ü
	double m_lfRatio; // ����
	BOOL m_bClicked; // Ŭ�� ����
	CPoint m_PrevMousePos; // ���� ���콺 ��ġ
	CPoint m_MousePos; // ���콺 ��ġ

	BOOL m_bSizeChanged; 

	CRect m_RightTopRt; // ������ �� �ּ�ȭ ��ư �簢�����Դϴ�.
	CRect m_MaximizeRt;
	BOOL m_bMaximizeMouseOver;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
//	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};


