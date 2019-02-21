// PartShowWnd.cpp : 구현 파일입니다.
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

	CBitmap bmp; // CBitmap 객체를 생성하고
	bmp.LoadBitmap( IDB_BITMAP_XBUTTON ); // 리소스로부터 이미지를 읽어온다
	BITMAP bmpObj;// 이미지 정보를 얻기 위한 BITMAP 변수이다.
	bmp.GetBitmap( &bmpObj );  // 이렇게 하면 BITMAP 이미지정보를 읽어올 수 있다
	// 이미지의 높이를 구하기 위해 getBitmap 함수를 호출했다.

	 // UINT 변수를 선언하고 ILC_COLOR24 와 ILC_MASK 를 적용한다.
	 UINT nFlags = ILC_MASK | ILC_COLOR24; 
	Afx_ImgList.Create( 10, bmpObj.bmHeight, nFlags, 0, 0 ); 
	// 로드한 비트맵을 이미지 리스트에 추가시킨다.
	Afx_ImgList.Add(&bmp, RGB(128, 128, 128));
	m_XbuttonMouseOver = FALSE;
	m_ScreenRect = CRect( 0, 0, 0, 0 );

	// n_Height 는 파트 뷰 윈도우의 높이를 결정합니다.	
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



// CPartShowWnd 메시지 처리기입니다.



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
	// 그다음 SetLayeredWindowAttributes 함수를 호출하면 끝이다..
	// 윈도우가 투명해진다..	
	WndCurrentLong = ::SetWindowLong( this->GetSafeHwnd(), GWL_EXSTYLE, ::GetWindowLong( this->GetSafeHwnd(), GWL_EXSTYLE ) | WS_EX_LAYERED );		
	SetLayeredWindowAttributes( RGB(255, 0, 0), bAlpha, LWA_ALPHA | LWA_COLORKEY );
}

void CPartShowWnd::MakeOpaqueWnd(void )
{
	//미리 저장된 불투명한 윈도우 설정으로 되돌린다.	
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
	// 윈도우의 클라이언트 영역을 드레그하여 이동할 수 있게 하기 위하여
	// WM_NCHITTEST 메시지핸들러를 등록해 클라이언트 영역에 마우스가 갔을 경우 HTCAPTION 으로 바꾸었다.
	// 단 구석으로 보내기 버튼과 x 버튼 부분은 HTCAPTION 이 아니다..(클릭이 안되므로)
	switch( nHitTest )
	{
		// 이 경우는 클라이언트 영역에 마우스가 있을 경우이다.
	case HTCAPTION:		
		m_XbuttonMouseOver = FALSE;		
		InvalidateRect( m_Xbutton );
		SetCursor( hCursorMove );
		return TRUE;
		break;
		// 이경우는 버튼들 위에 마우스가 있는 경우이다.
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
	// 마우스가 버튼 위로 이동했을 경우 색깔을 바꿔준다.
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
	// 윈도우를 활성시켜놓고 Alt + F4 를 눌렀을 경우를 대비
	// WM_CLOSE 핸들러를 등록하고 윈도우를 종료하는 것이 아니라 숨기도록 했다.
	this->ShowWindow( SW_HIDE );

	//CWnd::OnClose();
}

void CPartShowWnd::SetWindowSizeToImg( CSize ImgSize )
{
	// 이미지 사이즈의 크기에 따라 윈도우의 크기를 바꾼다.
	// 윈도우의 높이는 이미지 크기에 관계없이 항상 Height 로 유지된다.
	int Height = m_nHeight;
	int Width;

	Width = (int)( (double)Height * (double)ImgSize.cx / (double)ImgSize.cy );
	SetWindowPos( NULL, 0, 0, Width, Height, SWP_NOMOVE );
	MoveWndRightBottom();
}

void CPartShowWnd::SetReductionRect( CRect ViewClient, CSize ImgSize, CPoint ImgPos )
{
	// 이 함수는 이미지의 어느부분을 보여주고 있는지 알려주는 하얀색 네모의 위치와 크기를 계산한다.
	// 
	// SetRecuctionRect 함수는 현재 클라이언트의 크기, 이미지 크기, 이미지 위치 정보를 받고
	// 현재 클라이언트의 위치가 이미지의 어느부분인지 계산해내는 함수입니다.
	double ratio;
	CPoint SmallImgPos;
	int SmallWidth;
	int SmallHeight;

	// 100.0 은 
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
