// SatelliteViewWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SYUCampus.h"
#include "SYUCampusView.h"
#include "SatelliteViewWnd.h"
#include "BufferDC.h"
#include "PanoFileShowDlg.h"
#include "PanoFileData.h"
#include "MainFrm.h"


// CSatelliteViewWnd

IMPLEMENT_DYNAMIC(CSatelliteViewWnd, CWnd)

CSatelliteViewWnd::CSatelliteViewWnd()
{
	m_ImgPos = CPoint( -1150, -550 );
	m_lfRatio = 1;
	m_bClicked = FALSE;
	ErrorMsg = _T("");

	m_bSizeChanged = FALSE;
	m_ChangedSize = CSize( 0, 0 );

	m_ViewPtClicked = FALSE;	

	m_bMouseOver = FALSE;
	m_RightTop = FALSE;
	m_LinkPoint = FALSE;

	m_bMaximizeMouseOver = FALSE;
}

CSatelliteViewWnd::~CSatelliteViewWnd()
{
}


BEGIN_MESSAGE_MAP(CSatelliteViewWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_RBUTTONUP()
	ON_WM_CLOSE()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_GETMINMAXINFO()
//	ON_COMMAND(ID_POPUP_ADDVIEW_SATE, &CSatelliteViewWnd::OnPopupAddviewSate)
	ON_WM_CONTEXTMENU()
//	ON_UPDATE_COMMAND_UI(ID_POPUP_ADDVIEW_SATE, &CSatelliteViewWnd::OnUpdatePopupAddviewSate)
END_MESSAGE_MAP()



// CSatelliteViewWnd 메시지 처리기입니다.



void CSatelliteViewWnd::OnPaint()
{
	//CPaintDC dc(this);
	CBufferDC dc(this);	
	dc.Rectangle( m_ClientRect.left - 5, m_ClientRect.top - 5, m_ClientRect.right + 5, m_ClientRect.bottom + 5 );

	Graphics G( dc );
	G.SetSmoothingMode( SmoothingModeHighQuality );

	// 사각영역 그리기, 패인윈도우는 다시그리기를 하지 않으므로;;
	dc.Rectangle( m_ClientRect.left - 5, m_ClientRect.top - 5, m_ClientRect.right + 5, m_ClientRect.bottom + 5 );

	// 삼육대학교 안내도 그리기
	if( m_BufferdImg.m_pCachedbmp )
	{
		G.DrawCachedBitmap( m_BufferdImg.m_pCachedbmp, m_ImgPos.x, m_ImgPos.y );		
	}
	if( m_BuildingName.m_pCachedbmp && bBuildingNameShow )
	{
		G.DrawCachedBitmap( m_BuildingName.m_pCachedbmp, m_ImgPos.x, m_ImgPos.y );
	}

	if( bViewPointShow ) // bViewPointShow 전역변수가 FALSE 가 되면 뷰 포인트를 출력하지 않습니다.
	{
		CPanoFileData *pData;
		POSITION pos;
		int num = AfxPanoFileList.GetCount();

		CPoint Pt;

		pos = AfxPanoFileList.GetHeadPosition();
		for( int i = 0 ; i < num ; i++ )
		{
			pData = (CPanoFileData *)AfxPanoFileList.GetNext( pos );
			Pt = pData->m_SatelliteTopViewPt + m_ImgPos;
			Pt.x -= 10;
			Pt.y -= 10;

			if( pData->m_nEast == 0 )
			{		
				Afx_ImgListViewPoint.Draw( &dc, 1, Pt, ILD_NORMAL );
			}
			else
			{			
				// 뷰 포인트 이미지 출력
				if( m_LinkPoint )
				{
					Afx_ImgListViewPoint.Draw( &dc, 1, Pt, ILD_NORMAL );
				}
				else
				{
					Afx_ImgListViewPoint.Draw( &dc, 0, Pt, ILD_NORMAL );
				}
			}
			
		}
	}

	CSYUCampusView* pView = (CSYUCampusView*)Afx_pVoidView;

	//하얀팬
	Pen WhitePen( Color( 255, 255, 255, 255 ), 2.0f );
	// 하얀 굵은 프린 팬
	Pen BoldWhitePen( Color( 180, 255, 255, 255 ), 10.0f );
	// 적당히 흐린 하얀 브러시
	SolidBrush HalfWhite( Color( 100, 255, 255, 255 ) );
	// 많이 프린 하얀 브러스
	SolidBrush DimWhite( Color( 80, 255, 255, 255 ) );
	// 하얀 브러시
	SolidBrush White( Color( 255, 255, 255, 255 ) );

	Pen RedPen( Color( 255, 255, 0, 0 ), 2.0f );
	Pen BlackPen( Color( 128, 0, 0, 0), 2.0f );
	SolidBrush Red( Color( 255, 255, 0, 0 ) );
	SolidBrush DimRed( Color( 255, 255, 0, 0 ) );	

	// 주 파이
	G.FillPie( &HalfWhite, 
		(REAL)(m_ViewerPt.x - 50 + m_ImgPos.x), 
		(REAL)(m_ViewerPt.y - 50 + m_ImgPos.y), 
		(REAL)100, (REAL)100, 
		(REAL)(m_lfDirection - 45), 90 );

	// 크고 좁은 파이
	
	G.FillPie( &HalfWhite, 
		(REAL)(m_ViewerPt.x - 250+ m_ImgPos.x), 
		(REAL)(m_ViewerPt.y - 250 + m_ImgPos.y), 
		(REAL)500, (REAL)500, 
		(REAL)(m_lfDirection - 5), 10 );

	// 현재 위치 원
	G.FillEllipse( &White, 
		m_ViewerPt.x - 10 + m_ImgPos.x, 
		m_ViewerPt.y - 10 + m_ImgPos.y, 
		20, 20 );	

	// 외곽 원
	G.DrawEllipse( &WhitePen, 
		m_ViewerPt.x - 50 + m_ImgPos.x, 
		m_ViewerPt.y - 50 + m_ImgPos.y, 
		100, 100 );
	
	// 내부 흐린원
	G.FillEllipse( &DimWhite, 
		m_ViewerPt.x - 50 + m_ImgPos.x, 
		m_ViewerPt.y - 50 + m_ImgPos.y, 
		100, 100 );

	// 내부 장식 하얀 원
	G.DrawEllipse( &BoldWhitePen, 
		m_ViewerPt.x - 25 + m_ImgPos.x, 
		m_ViewerPt.y - 25 + m_ImgPos.y, 
		50, 50 );

	if( m_RightTop ) // m_bTopRight
		Afx_ImgListLTRB.Draw( &dc, 6, CPoint( m_RightTopRt.left, m_RightTopRt.top ), ILD_NORMAL );
	else
		Afx_ImgListLTRB.Draw( &dc, 2, CPoint( m_RightTopRt.left, m_RightTopRt.top ), ILD_NORMAL );		

	if( m_bMaximizeMouseOver )
		Afx_ImgListLTRB.Draw( &dc, 5, CPoint( m_MaximizeRt.left, m_MaximizeRt.top ), ILD_NORMAL );
	else
		Afx_ImgListLTRB.Draw( &dc, 1, CPoint( m_MaximizeRt.left, m_MaximizeRt.top ), ILD_NORMAL );

	//Afx_ImgListViewPoint.Draw( &dc, 1, CPoint( 0, 0 ), ILD_NORMAL );

	if( DEBUG_MODE )
	{		
		CString strTmp;
		strTmp.Format( _T("ImgPos %d %d"), m_ImgPos.x, m_ImgPos.y );
		dc.TextOut( 0, 0, strTmp );
		strTmp.Format( _T("ImgSize %d %d"), m_BufferdImg.m_ImgModiSize.cx, m_BufferdImg.m_ImgModiSize.cy );
		dc.TextOut( 0, 20, strTmp );	
		
		CPoint pt;
		pt = ::GetImagePoint( m_ImgPos, m_ClientRect, m_MousePos );
		strTmp.Format( _T("이미지상 좌표 %d %d"), pt.x, pt.y );
		dc.TextOut( 0, 40, strTmp );
		strTmp.Format( _T("m_ViewerPt %d %d"), m_ViewerPt.x, m_ViewerPt.y );
		dc.TextOut( 0, 60, strTmp );
		strTmp.Format( _T("m_lfDirection %lf"), m_lfDirection );
		dc.TextOut( 0, 80, strTmp );
	}
	
}

int CSatelliteViewWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	TCHAR str[ MAX_PATH ];
	lstrcpy( str, AppDir );

	lstrcat( str, _T("\\Images\\satellite.png") );

	m_BuildingName.Init( this );
	if( m_BuildingName.LoadFile( str ) )
	{
		m_BuildingName.SetRatio( 1 );
	}	
	
	lstrcpy( str, AppDir );
	lstrcat( str, _T("\\Images\\satellite.jpg") );

	m_BufferdImg.Init( this );
	if( !m_BufferdImg.LoadFile( str ) )
	{
		ErrorMsg.Format( _T("%s 파일을 열 수 없습니다! 탑 뷰 윈도우를 사용할 수 없습니다!"), str );
		AfxMessageBox( ErrorMsg );
		ErrorMsg = _T("이미지 로드 실패!");
	}
	else
	{
		if( !m_BufferdImg.SetRatio( m_lfRatio ) )
		{
			AfxMessageBox( _T("이미지 그리기 실패") );
			ErrorMsg = _T("이미지 그리기 실패!");
		}
		else
		{
			ErrorMsg = _T("");
		}
	}

	CSYUCampusView* pView = (CSYUCampusView*)Afx_pVoidView;
	CPoint pt;
	pt.x = pView->m_ClientRect.right;
	pt.y = 0;
	pView->ClientToScreen( &pt );

	SetWindowPos( NULL, pt.x - 600, pt.y, 0, 0, SWP_NOSIZE );
	
	return 0;
}

void CSatelliteViewWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bClicked = TRUE;
	m_PrevMousePos = m_MousePos = point;
	SetCapture();
	
	return ;
	CWnd::OnLButtonDown(nFlags, point);
}

void CSatelliteViewWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	CSYUCampusView* pView = (CSYUCampusView*)Afx_pVoidView;
	CMainFrame* pMain = (CMainFrame*)Afx_pVoidMain;		

	m_bClicked = FALSE;
	ReleaseCapture();

	CPanoFileData* pData;
	POSITION pos;
	CRect PointRect;

	pos = AfxPanoFileList.GetHeadPosition();
	int num = AfxPanoFileList.GetCount();

	for( int i = 0 ; i < num ; i++ )
	{
		pData = (CPanoFileData *)AfxPanoFileList.GetNext( pos );

		PointRect = CRect(pData->m_SatelliteTopViewPt.x - SIZE_RECT + m_ImgPos.x, 
			pData->m_SatelliteTopViewPt.y - SIZE_RECT + m_ImgPos.y, 
			pData->m_SatelliteTopViewPt.x + SIZE_RECT + m_ImgPos.x, 
			pData->m_SatelliteTopViewPt.y + SIZE_RECT + m_ImgPos.y );
		
		// 탑 뷰에서 뷰 포인트를 클릭했을 경우이다.
		if( PtInRect( &PointRect, point ) && bViewPointShow )
		{				
			
			TCHAR str[ MAX_PATH ];

			lstrcpy( str, AppDir );
			wsprintf( str, _T("%s\\panoramas\\%s"), str, pData->m_FileName );

			pView->m_bNowLoading = TRUE;
			pView->RedrawWindow();

			if( pView->LoadImage( str ) )
			{
				Afx_pVoidCurrentFile = pData;
				pView->m_LoadedFileName = pData->m_FileName; // 이미지 상에 링크를 위치시키기 위해 파일명을 알려주어야 한다.
				pView->LoadFileLinkPoint(); // View클래스에 m_LinkFileList 를 초기화 시키기 위해 이 함수를 호출해 준다.
				
				CPoint Pt;
				Pt = GetImagePoint( m_ImgPos, m_ClientRect, point );
				// 클릭한 위치가 중앙에 오도록 한다.
				SetImagePosToClientPoint( Pt );
				m_ViewerPt = pData->m_SatelliteTopViewPt;
				pMain->m_TopViewWnd.m_ViewerPt = pData->m_TopViewPt;

				// 탑 뷰 윈도우가 클릭한 부분을 중앙에 나타내도록 이미지 위치를 조정시킵니다.
				if( pData->m_TopViewPt.x > 0 )
				{
					Pt = GetImagePoint( pMain->m_TopViewWnd.m_ImgPos, 
						pMain->m_TopViewWnd.m_ClientRect,
						pData->m_TopViewPt );
					Pt +=  pMain->m_TopViewWnd.m_ImgPos;
					pMain->m_TopViewWnd.SetImagePosToClientPoint( Pt );
				}

				CPoint pt;
				int y;			
				pt = pView->m_ImgPos; // 현재 이미지 위치를 받습니다.
				y = pt.y;
				m_nEast = pData->m_nSatelliteEast;
				pMain->m_TopViewWnd.m_nEast = pData->m_nEast; // East 값을 지정합니다.

				// 화면 중앙 위치를 계산합니다.
				pt.x = (LONG)( m_lfDirection * (double)( pView->m_BufferdImg.GetWidth() ) / 360.0 + (double)( pView->m_nEast ) * pView->m_lfRatio );			
				// 화면 중앙위치에 맞게 이미지 위치를 조정합니다
				pView->m_ImgPos = ::SetImagePosToClientPoint( pView->GetClientWidth(), 
					pView->GetClientHeight(),
					pView->m_BufferdImg.GetWidth(),
					pView->m_BufferdImg.GetHeight(),
					CPoint( pView->GetClientWidth() / 2, pView->GetClientHeight() / 2 ),
					pt);
				pView->m_ImgPos.y = y;
				// 이미지가 화면밖으로 나가는 것을 방지합니다.
				
				// 다시그립니다.
				pMain->m_PartShow.SetWindowSizeToImg( CSize( pView->m_BufferdImg.GetWidth(), pView->m_BufferdImg.GetHeight() ) );
				pMain->m_PartShow.SetReductionRect( pView->m_ClientRect, CSize( pView->m_BufferdImg.GetWidth(), pView->m_BufferdImg.GetHeight() ), pView->m_ImgPos );

				pView->m_bNowLoading = FALSE;

				pView->SetImagePosRight();
				pView->Invalidate();

				pMain->m_PartShow.ShowWindow( SW_SHOW );
				pMain->m_PartShow.Invalidate();
				pMain->m_TopViewWnd.Invalidate();
				Invalidate();

				// 타이머를 온 시켜서 윈도우가 오른쪽 윗구석으로 자연스럽게 이동하도록 합니다.
				
				if( pMain->m_TopViewWnd.IsWindowVisible() )
				{
					MySetWindowSize( CPoint( pView->m_ClientRect.right - 600, 0 ), CSize( 300, 300 ) );
					pMain->m_TopViewWnd.MySetWindowSize( CPoint( pView->m_ClientRect.right - 300, 0 ), CSize( 300, 300 ) );
				}
				else
					MySetWindowSize( CPoint( pView->m_ClientRect.right - 300, 0 ), CSize( 300, 300 ) );
					


			} //if( pView->LoadImage( str ) )
			break;
		}// if( PtInRect )

		// 오른쪽 위를 클릭하면 창이 뷰 오른쪽 위로 이동한다.
		
	}	// for	
	
	if( PtInRect( &m_RightTopRt, point ) )
	{
		OnMyMinimize();
	}
	if( PtInRect( &m_MaximizeRt, point ) )
	{
		OnMyMaximize();
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void CSatelliteViewWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	m_CurMousePos = point;	

	if( m_bClicked )
	{
		CPoint tmp;
		m_PrevMousePos = point;

		tmp = m_ImgPos - (m_MousePos - m_PrevMousePos );

		tmp = SetImagePosRight( m_ClientRect.right, m_ClientRect.bottom, m_BufferdImg.m_ImgModiSize.cx, m_BufferdImg.m_ImgModiSize.cy, tmp );

		m_ImgPos = tmp;

		m_MousePos = m_PrevMousePos; // 현재 좌표 갱신			

		Invalidate();
	}
	else
	{		
		if( PtInRect( &m_RightTopRt, point ) )
		{
			m_RightTop = TRUE;
			InvalidateRect( &m_RightTopRt );
		}
		else
		{
			m_RightTop = FALSE;
		}

		if( PtInRect( &m_MaximizeRt, point ) )
		{
			m_bMaximizeMouseOver = TRUE;
			InvalidateRect( &m_MaximizeRt );
		}
		else
		{
			m_bMaximizeMouseOver = FALSE;
		}
		// 디버그 모드 상태에서는 이미지상의 마우스 좌표가 보여야 하므로
		if( DEBUG_MODE )
		{
			m_MousePos = point;
			//Invalidate();
		}

		BOOL bExist = FALSE;
		CRect PointRect;
		CPanoFileData* pData;
		POSITION pos;
		
		pos = AfxPanoFileList.GetHeadPosition();
		int num;
		num  = AfxPanoFileList.GetCount();
		for( int i = 0 ; i < num ; i++ )
		{
			pData = (CPanoFileData *)AfxPanoFileList.GetNext( pos );

			PointRect = CRect(pData->m_SatelliteTopViewPt.x - SIZE_RECT + m_ImgPos.x, 
				pData->m_SatelliteTopViewPt.y - SIZE_RECT + m_ImgPos.y, 
				pData->m_SatelliteTopViewPt.x + SIZE_RECT + m_ImgPos.x, 
				pData->m_SatelliteTopViewPt.y + SIZE_RECT + m_ImgPos.y );
			
			if( PtInRect( &PointRect, m_CurMousePos ) )
			{
				m_LinkPoint = TRUE;
				bExist = TRUE;
				InvalidateRect( &PointRect );
				break;
			}
		}
		if( bExist == FALSE )
		{
			m_LinkPoint = FALSE;
			Invalidate();
		}

	}


	CWnd::OnMouseMove(nFlags, point);
}

void CSatelliteViewWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	GetClientRect( &m_ClientRect );

	m_ImgPos = SetImagePosRight( m_ClientRect.right, m_ClientRect.bottom, m_BufferdImg.m_ImgModiSize.cx, m_BufferdImg.m_ImgModiSize.cy, m_ImgPos );
	Invalidate();

	m_RightTopRt = CRect( m_ClientRect.right - 24, 2, m_ClientRect.right - 2, 24 );
	m_MaximizeRt = CRect( m_RightTopRt.left - 24, 2, m_RightTopRt.left - 2, 24 );
}

void CSatelliteViewWnd::OnRButtonUp(UINT nFlags, CPoint point)
{

	m_RbuttonPt = point;
	CWnd::OnRButtonUp(nFlags, point);
}

void CSatelliteViewWnd::OnClose()
{
	// x 버튼을 누르면 종료하지 않고 윈도우를 숨깁니다.
	ShowWindow( SW_HIDE );
	
	return ;// 종료 방지

	CWnd::OnClose();
}

BOOL CSatelliteViewWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	BOOL bLink = FALSE;
	CRect PointRect;
	CRect RightTop( m_ClientRect.right - 30, 0, m_ClientRect.right, 30 );
	switch( nHitTest )
	{
	case HTCLIENT:

		// 최소화 버튼 또는 링크포인트 위에 마우스 오버했을 경우
		if( m_LinkPoint || m_RightTop || m_bMaximizeMouseOver )
			SetCursor( hCursorLinkArrow ); // 마우스 커서를 링크로 버꿉니다.
		else
			SetCursor( hCursorMove ); // 그외의 경우에는 손모양 커서로 바꿉니다.
		return TRUE;

	default:
		break;
	}	
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CSatelliteViewWnd::SetImagePosToClientPoint( CPoint PtOnImg )
{
		// 이미지의 점 PtOnImg 가 화면 중앙으로 오도록 이미지 위치를 조정합니다.
	if( m_ClientRect.right > m_BufferdImg.GetWidth() )
		return ;	
	if( m_ClientRect.bottom > m_BufferdImg.GetHeight() )
		return ;
	m_ImgPos.x = -PtOnImg.x + m_ClientRect.right / 2;
	m_ImgPos.y = -PtOnImg.y + m_ClientRect.bottom / 2;
	
	m_ImgPos = SetImagePosRight( m_ClientRect.right, m_ClientRect.bottom, m_BufferdImg.GetWidth(), m_BufferdImg.GetHeight(), m_ImgPos );	
	Invalidate();
}
void CSatelliteViewWnd::OnTimer(UINT_PTR nIDEvent)
{
	int nSpeed = 40;
	switch( nIDEvent )
	{
	case 5:
		CRect WRect;
		CRect ViewClientRect;

		this->GetWindowRect( &WRect );
		CSYUCampusView* pView;
		pView = (CSYUCampusView*)Afx_pVoidView;
		pView->GetClientRect( &ViewClientRect );
		int x,y,w,h;

		// 현재 윈도우의 화면좌표와 너비 높이.
		x = WRect.left;
		y = WRect.top;
		w = WRect.right - WRect.left;
		h = WRect.bottom - WRect.top;

		CPoint PtInView;
		PtInView = m_ChangedPoint;
		pView->ClientToScreen( &PtInView );
		
		if( PtInView.x > x )
		{
			if( PtInView.x - x < nSpeed )
				x = PtInView.x;
			else
				x += nSpeed;
		}
		else
		{
			if( x - PtInView.x < nSpeed )
				x = PtInView.x;
			else
				x -= nSpeed;
		}

		if( PtInView.y > y )
		{
			if( PtInView.y - y < nSpeed )
				y = PtInView.y;
			else
				y += nSpeed;
		}
		else
		{
			if (y - PtInView.y < nSpeed )
				y = PtInView.y;
			else
				y -= nSpeed;
		}

		if( w > m_ChangedSize.cx )
		{
			if( w - m_ChangedSize.cx < nSpeed )
				w = m_ChangedSize.cx;
			else
				w -= nSpeed;
		}
		else
		{
			if( m_ChangedSize.cx - w < nSpeed )
				w = m_ChangedSize.cx;
			else
				w += nSpeed;
		}

		if( h > m_ChangedSize.cy )
		{
			if( h - m_ChangedSize.cy < nSpeed )
				h = m_ChangedSize.cy;
			else
				h -= nSpeed;
		}
		else
		{
			if( m_ChangedSize.cy - h < nSpeed )
				h = m_ChangedSize.cy;
			else
				h += nSpeed;				
		}

		if( PtInView.x == x && PtInView.y == y && h == m_ChangedSize.cy && w == m_ChangedSize.cx )
			KillTimer( 5 );

		CPoint ImgCenterPt;
		ImgCenterPt = GetImagePoint( m_ImgPos, m_ClientRect, CPoint( m_ClientRect.right / 2, m_ClientRect.bottom / 2 ) );
		SetWindowPos( NULL, x, y, w, h, SWP_NOZORDER | SWP_NOACTIVATE );
		SetImagePosToClientPoint( ImgCenterPt );

		break;
	}
	CWnd::OnTimer(nIDEvent);
}

void CSatelliteViewWnd::MySetWindowSize( CPoint Pt, CSize sz )
{
	m_ChangedPoint = Pt;
	m_ChangedSize = sz;
	SetTimer( 5, 10, NULL );
}
void CSatelliteViewWnd::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// 윈도우의 최소크기를 300x300 으로 제한합니다.
	lpMMI->ptMinTrackSize.x = 300;
	lpMMI->ptMinTrackSize.y = 300;

	CWnd::OnGetMinMaxInfo(lpMMI);
}

void CSatelliteViewWnd::OnMyMinimize( void )
{
	CSYUCampusView* pView = (CSYUCampusView*)Afx_pVoidView;
	MySetWindowSize( CPoint( pView->m_ClientRect.right - 300, 0 ), CSize( 300, 300 ) );
}
void CSatelliteViewWnd::OnMyMaximize( void )
{
	CSYUCampusView* pView = (CSYUCampusView*)Afx_pVoidView;
	MySetWindowSize( CPoint( pView->m_ClientRect.left, 0 ), CSize( pView->GetClientWidth(), pView->GetClientHeight() ) );
}

void CSatelliteViewWnd::OnContextMenu(CWnd* pWnd, CPoint point )
{
	CMenu PopupMenu;
	PopupMenu.LoadMenu( IDR_MENU_POPUP );
	CMenu* pMenu;
	pMenu = PopupMenu.GetSubMenu( 1 );
	pMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd() );
}
void CSatelliteViewWnd::OpenViewPointAddDlg( void )
{
	CSYUCampusApp* App;

	App = (CSYUCampusApp*)Afx_pVoidApp;
	CPanoFileShowDlg Dlg;

	Dlg.m_bInsert = TRUE; // 입력모드로 들어왔을 경우
	Dlg.m_bSatellite = TRUE;
	Dlg.m_bTopView = FALSE;

	m_RbuttonPt = GetImagePoint( m_ImgPos, m_ClientRect, m_RbuttonPt );
	Dlg.m_nSatellitePosX = m_RbuttonPt.x; // 컨트롤에 미리 입력하고
	Dlg.m_nSatellitePosY = m_RbuttonPt.y;

	// 대화상자를 연다.
	if( Dlg.DoModal() == IDOK )
	{
		App->SavePanoFileData();
	}

	Invalidate();
}