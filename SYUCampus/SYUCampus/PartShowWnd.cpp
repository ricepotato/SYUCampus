// PartShowWnd.cpp : ���� �����Դϴ�.
//


#include "stdafx.h"
#include "SYUCampus.h"
#include "PartShowWnd.h"
#include "SYUCampusView.h"
#include "BufferDC.h"


// CPartShowWnd

IMPLEMENT_DYNAMIC(CPartShowWnd, CWnd)

CPartShowWnd::CPartShowWnd()
{
	WndLong = ::GetWindowLong( this->GetSafeHwnd(), GWL_EXSTYLE );

	CBitmap bmp; // CBitmap ��ü�� �����ϰ�
	bmp.LoadBitmap( IDB_BITMAP_XBUTTON ); // ���ҽ��κ��� �̹����� �о�´�
	BITMAP bmpObj;// �̹��� ������ ��� ���� BITMAP �����̴�.
	bmp.GetBitmap( &bmpObj );  // �̷��� �ϸ� BITMAP �̹��������� �о�� �� �ִ�
	// �̹����� ���̸� ���ϱ� ���� getBitmap �Լ��� ȣ���ߴ�.

	 // UINT ������ �����ϰ� ILC_COLOR24 �� ILC_MASK �� �����Ѵ�.
	 UINT nFlags = ILC_MASK | ILC_COLOR24; 
	Afx_ImgList.Create( 10, bmpObj.bmHeight, nFlags, 0, 0 ); 
	// �ε��� ��Ʈ���� �̹��� ����Ʈ�� �߰���Ų��.
	Afx_ImgList.Add(&bmp, RGB(128, 128, 128));
	m_XbuttonMouseOver = FALSE;
	m_ScreenRect = CRect( 0, 0, 0, 0 );

	// n_Height �� ��Ʈ �� �������� ���̸� �����մϴ�.	
	m_nHeight = 50;
}

CPartShowWnd::~CPartShowWnd()
{
}


BEGIN_MESSAGE_MAP(CPartShowWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()



// CPartShowWnd �޽��� ó�����Դϴ�.



void CPartShowWnd::OnPaint()
{
	//CPaintDC dc(this);
	CBufferDC dc(this);


	CBrush BlackBrush( RGB( 0, 0, 0 ) );
	CBrush WhiteBrush( RGB( 255, 255, 255) );
	CPen WhitePen( PS_SOLID, 2, RGB( 255, 255, 255 ) );
	CPen RedPen( PS_SOLID, 1, RGB( 255, 0, 0 ) );
	CPen RedPen2( PS_SOLID, 2, RGB( 255, 0, 0 ) );

	CBrush* pBrush;
	CPen* pPen;

	pBrush = dc.SelectObject( &BlackBrush );
	dc.Rectangle( m_ClientRect.left - 5, m_ClientRect.top - 5, m_ClientRect.right + 5 , m_ClientRect.bottom + 5 );

	//dc.SelectObject( pBrush );

	dc.SelectObject( &WhitePen );	

	
	dc.Rectangle( &m_ScreenRect );
	
	dc.Rectangle( m_ScreenRect.left + m_SmallClientWidth, 
		m_ScreenRect.top, 
		m_ScreenRect.right + m_SmallClientWidth,
		m_ScreenRect.bottom);

	dc.Rectangle( m_ScreenRect.left - m_SmallClientWidth, 
		m_ScreenRect.top, 
		m_ScreenRect.right - m_SmallClientWidth,
		m_ScreenRect.bottom);
	

	pPen = dc.SelectObject( &RedPen ); 

	for( int i = 10 ; i > 0 ; i -= 2 )
	{
		dc.MoveTo( m_ClientRect.right - i, m_ClientRect.bottom );
		dc.LineTo( m_ClientRect.right, m_ClientRect.bottom - i );
	}

	if( m_XbuttonMouseOver )
		Afx_ImgList.Draw( &dc, 1, CPoint( m_ClientRect.right - 12, +2 ), ILD_NORMAL );
	else
		Afx_ImgList.Draw( &dc, 0, CPoint( m_ClientRect.right - 12, +2 ), ILD_NORMAL );


	dc.SelectObject( pBrush );
	dc.SelectObject( pPen );
}

int CPartShowWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetClientRect( &m_ClientRect );

	MoveWndRightBottom();

	MakeTransparentWnd( 128 );
	return 0;
}

void CPartShowWnd::MakeTransparentWnd( BYTE bAlpha )
{
	// �״��� SetLayeredWindowAttributes �Լ��� ȣ���ϸ� ���̴�..
	// �����찡 ����������..	
	WndCurrentLong = ::SetWindowLong( this->GetSafeHwnd(), GWL_EXSTYLE, ::GetWindowLong( this->GetSafeHwnd(), GWL_EXSTYLE ) | WS_EX_LAYERED );		
	SetLayeredWindowAttributes( RGB(255, 0, 0), bAlpha, LWA_ALPHA | LWA_COLORKEY );
}

void CPartShowWnd::MakeOpaqueWnd(void )
{
	//�̸� ����� �������� ������ �������� �ǵ�����.	
	WndCurrentLong = ::SetWindowLong( this->GetSafeHwnd(), GWL_EXSTYLE, WndLong );	
}

void CPartShowWnd::MoveWndRightBottom( void )
{
	GetClientRect( &m_ClientRect );

	CSYUCampusView* pView;

	pView = (CSYUCampusView *)Afx_pVoidView;

	CPoint Pt;
	Pt.x = pView->GetClientWidth();
	Pt.y = pView->GetClientHeight();

	pView->ClientToScreen( &Pt );

	SetWindowPos( NULL, 
		Pt.x - m_ClientRect.right, 
		Pt.y - m_ClientRect.bottom,
		0, 0, SWP_NOSIZE );
}
void CPartShowWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	GetClientRect( &m_ClientRect );
	m_Minimize = CRect( m_ClientRect.right - 10, m_ClientRect.bottom - 10, m_ClientRect.right, m_ClientRect.bottom	);
	m_Xbutton = CRect( m_ClientRect.right - 12, m_ClientRect.top + 2, m_ClientRect.right - 2, m_ClientRect.top + 12 );
}

BOOL CPartShowWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// �������� Ŭ���̾�Ʈ ������ �巹���Ͽ� �̵��� �� �ְ� �ϱ� ���Ͽ�
	// WM_NCHITTEST �޽����ڵ鷯�� ����� Ŭ���̾�Ʈ ������ ���콺�� ���� ��� HTCAPTION ���� �ٲپ���.
	// �� �������� ������ ��ư�� x ��ư �κ��� HTCAPTION �� �ƴϴ�..(Ŭ���� �ȵǹǷ�)
	switch( nHitTest )
	{
		// �� ���� Ŭ���̾�Ʈ ������ ���콺�� ���� ����̴�.
	case HTCAPTION:		
		m_XbuttonMouseOver = FALSE;		
		InvalidateRect( m_Xbutton );
		SetCursor( hCursorMove );
		return TRUE;
		break;
		// �̰��� ��ư�� ���� ���콺�� �ִ� ����̴�.
	case HTCLIENT:
		if( PtInRect( &m_Minimize, m_CurMousePos ) || PtInRect(m_Xbutton, m_CurMousePos) )
		{
			SetCursor( hCursorLinkArrow );
			return TRUE;
		}
		break;
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CPartShowWnd::OnMouseMove(UINT nFlags, CPoint point)
{	
	CPoint Move;

	m_CurMousePos = point;
	// ���콺�� ��ư ���� �̵����� ��� ������ �ٲ��ش�.
	if( PtInRect(m_Xbutton, m_CurMousePos) )
	{
		m_XbuttonMouseOver = TRUE;
		InvalidateRect( m_Xbutton );
	}
	else
	{
		m_XbuttonMouseOver = FALSE;
		InvalidateRect( m_Xbutton );
	}

	CWnd::OnMouseMove(nFlags, point);
}



void CPartShowWnd::OnClose()
{
	// �����츦 Ȱ�����ѳ��� Alt + F4 �� ������ ��츦 ���
	// WM_CLOSE �ڵ鷯�� ����ϰ� �����츦 �����ϴ� ���� �ƴ϶� ���⵵�� �ߴ�.
	this->ShowWindow( SW_HIDE );

	//CWnd::OnClose();
}

void CPartShowWnd::SetWindowSizeToImg( CSize ImgSize )
{
	// �̹��� �������� ũ�⿡ ���� �������� ũ�⸦ �ٲ۴�.
	// �������� ���̴� �̹��� ũ�⿡ ������� �׻� Height �� �����ȴ�.
	int Height = m_nHeight;
	int Width;

	Width = (int)( (double)Height * (double)ImgSize.cx / (double)ImgSize.cy );
	SetWindowPos( NULL, 0, 0, Width, Height, SWP_NOMOVE );
	MoveWndRightBottom();
}

void CPartShowWnd::SetReductionRect( CRect ViewClient, CSize ImgSize, CPoint ImgPos )
{
	// �� �Լ��� �̹����� ����κ��� �����ְ� �ִ��� �˷��ִ� �Ͼ�� �׸��� ��ġ�� ũ�⸦ ����Ѵ�.
	// 
	// SetRecuctionRect �Լ��� ���� Ŭ���̾�Ʈ�� ũ��, �̹��� ũ��, �̹��� ��ġ ������ �ް�
	// ���� Ŭ���̾�Ʈ�� ��ġ�� �̹����� ����κ����� ����س��� �Լ��Դϴ�.
	double ratio;
	CPoint SmallImgPos;
	int SmallWidth;
	int SmallHeight;

	// 100.0 �� 
	ratio = (double)m_nHeight / (double)ImgSize.cy;
	SmallImgPos.x = (int)( (double)ImgPos.x * ratio );
	SmallImgPos.y = (int)( (double)ImgPos.y * ratio );

	SmallWidth = (int)( ratio * (double)(ViewClient.right - ViewClient.left) );
	SmallHeight = (int)( ratio * (double)(ViewClient.bottom - ViewClient.top) );

	m_ScreenRect = CRect( -SmallImgPos.x,
		 -SmallImgPos.y,
		 -SmallImgPos.x + SmallWidth,
		 -SmallImgPos.y + SmallHeight );

	m_SmallClientWidth = (int)( (double)ImgSize.cx * ratio );
}

void CPartShowWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();

	CWnd::OnLButtonDown(nFlags, point);
}
void CPartShowWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	if( PtInRect( &m_Minimize, m_CurMousePos ) )
	{
		MoveWndRightBottom();
	}

	if( PtInRect( &m_Xbutton, m_CurMousePos ) )
	{
		ShowWindow( SW_HIDE );
	}
	CWnd::OnLButtonUp(nFlags, point);
}
LRESULT CPartShowWnd::OnNcHitTest(CPoint point)
{	
	CPoint ClientPt;
	ClientPt = point;
	
	ScreenToClient( &ClientPt );

	if( PtInRect( &m_Minimize, ClientPt ) )
	{
		return CWnd::OnNcHitTest(point);
	}
	if( PtInRect( &m_Xbutton, ClientPt ) )
	{
		return CWnd::OnNcHitTest(point);
	}
	UINT nHit = CWnd::OnNcHitTest(point);	

	if( nHit == HTCLIENT )
	{		
		nHit = HTCAPTION;
	}

	return nHit;
	//return CWnd::OnNcHitTest(point);
}
