#pragma once


// CPartShowWnd

class CPartShowWnd : public CWnd
{
	DECLARE_DYNAMIC(CPartShowWnd)

public:
	CPartShowWnd();
	virtual ~CPartShowWnd();
private:
	CRect m_ClientRect;
	LONG WndCurrentLong;
	LONG WndLong;
	CRect m_Minimize;
	CPoint m_CurMousePos;

	CImageList Afx_ImgList;
	CRect m_Xbutton;
	BOOL m_XbuttonMouseOver;
	CRect m_ScreenRect;
	int m_SmallClientWidth;

	int m_nHeight;

public:
	void MakeTransparentWnd( BYTE bAlpha );
	void MakeOpaqueWnd(void );
	void MoveWndRightBottom( void );
	void SetWindowSizeToImg( CSize ImgSize );
	void SetReductionRect( CRect ViewClient, CSize ImgSize, CPoint ImgPos );
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};


