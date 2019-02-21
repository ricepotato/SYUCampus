// SatelliteViewWnd.cpp : ���� �����Դϴ�.
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



// CSatelliteViewWnd �޽��� ó�����Դϴ�.



void CSatelliteViewWnd::OnPaint()
{
	//CPaintDC dc(this);
	CBufferDC dc(this);	
	dc.Rectangle( m_ClientRect.left - 5, m_ClientRect.top - 5, m_ClientRect.right + 5, m_ClientRect.bottom + 5 );

	Graphics G( dc );
	G.SetSmoothingMode( SmoothingModeHighQuality );

	// �簢���� �׸���, ����������� �ٽñ׸��⸦ ���� �����Ƿ�;;
	dc.Rectangle( m_ClientRect.left - 5, m_ClientRect.top - 5, m_ClientRect.right + 5, m_ClientRect.bottom + 5 );

	// �������б� �ȳ��� �׸���
	if( m_BufferdImg.m_pCachedbmp )
	{
		G.DrawCachedBitmap( m_BufferdImg.m_pCachedbmp, m_ImgPos.x, m_ImgPos.y );		
	}
	if( m_BuildingName.m_pCachedbmp && bBuildingNameShow )
	{
		G.DrawCachedBitmap( m_BuildingName.m_pCachedbmp, m_ImgPos.x, m_ImgPos.y );
	}

	if( bViewPointShow ) // bViewPointShow ���������� FALSE �� �Ǹ� �� ����Ʈ�� ������� �ʽ��ϴ�.
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
				// �� ����Ʈ �̹��� ���
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

	//�Ͼ���
	Pen WhitePen( Color( 255, 255, 255, 255 ), 2.0f );
	// �Ͼ� ���� ���� ��
	Pen BoldWhitePen( Color( 180, 255, 255, 255 ), 10.0f );
	// ������ �帰 �Ͼ� �귯��
	SolidBrush HalfWhite( Color( 100, 255, 255, 255 ) );
	// ���� ���� �Ͼ� �귯��
	SolidBrush DimWhite( Color( 80, 255, 255, 255 ) );
	// �Ͼ� �귯��
	SolidBrush White( Color( 255, 255, 255, 255 ) );

	Pen RedPen( Color( 255, 255, 0, 0 ), 2.0f );
	Pen BlackPen( Color( 128, 0, 0, 0), 2.0f );
	SolidBrush Red( Color( 255, 255, 0, 0 ) );
	SolidBrush DimRed( Color( 255, 255, 0, 0 ) );	

	// �� ����
	G.FillPie( &HalfWhite, 
		(REAL)(m_ViewerPt.x - 50 + m_ImgPos.x), 
		(REAL)(m_ViewerPt.y - 50 + m_ImgPos.y), 
		(REAL)100, (REAL)100, 
		(REAL)(m_lfDirection - 45), 90 );

	// ũ�� ���� ����
	
	G.FillPie( &HalfWhite, 
		(REAL)(m_ViewerPt.x - 250+ m_ImgPos.x), 
		(REAL)(m_ViewerPt.y - 250 + m_ImgPos.y), 
		(REAL)500, (REAL)500, 
		(REAL)(m_lfDirection - 5), 10 );

	// ���� ��ġ ��
	G.FillEllipse( &White, 
		m_ViewerPt.x - 10 + m_ImgPos.x, 
		m_ViewerPt.y - 10 + m_ImgPos.y, 
		20, 20 );	

	// �ܰ� ��
	G.DrawEllipse( &WhitePen, 
		m_ViewerPt.x - 50 + m_ImgPos.x, 
		m_ViewerPt.y - 50 + m_ImgPos.y, 
		100, 100 );
	
	// ���� �帰��
	G.FillEllipse( &DimWhite, 
		m_ViewerPt.x - 50 + m_ImgPos.x, 
		m_ViewerPt.y - 50 + m_ImgPos.y, 
		100, 100 );

	// ���� ��� �Ͼ� ��
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
		strTmp.Format( _T("�̹����� ��ǥ %d %d"), pt.x, pt.y );
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
		ErrorMsg.Format( _T("%s ������ �� �� �����ϴ�! ž �� �����츦 ����� �� �����ϴ�!"), str );
		AfxMessageBox( ErrorMsg );
		ErrorMsg = _T("�̹��� �ε� ����!");
	}
	else
	{
		if( !m_BufferdImg.SetRatio( m_lfRatio ) )
		{
			AfxMessageBox( _T("�̹��� �׸��� ����") );
			ErrorMsg = _T("�̹��� �׸��� ����!");
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
		
		// ž �信�� �� ����Ʈ�� Ŭ������ ����̴�.
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
				pView->m_LoadedFileName = pData->m_FileName; // �̹��� �� ��ũ�� ��ġ��Ű�� ���� ���ϸ��� �˷��־�� �Ѵ�.
				pView->LoadFileLinkPoint(); // ViewŬ������ m_LinkFileList �� �ʱ�ȭ ��Ű�� ���� �� �Լ��� ȣ���� �ش�.
				
				CPoint Pt;
				Pt = GetImagePoint( m_ImgPos, m_ClientRect, point );
				// Ŭ���� ��ġ�� �߾ӿ� ������ �Ѵ�.
				SetImagePosToClientPoint( Pt );
				m_ViewerPt = pData->m_SatelliteTopViewPt;
				pMain->m_TopViewWnd.m_ViewerPt = pData->m_TopViewPt;

				// ž �� �����찡 Ŭ���� �κ��� �߾ӿ� ��Ÿ������ �̹��� ��ġ�� ������ŵ�ϴ�.
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
				pt = pView->m_ImgPos; // ���� �̹��� ��ġ�� �޽��ϴ�.
				y = pt.y;
				m_nEast = pData->m_nSatelliteEast;
				pMain->m_TopViewWnd.m_nEast = pData->m_nEast; // East ���� �����մϴ�.

				// ȭ�� �߾� ��ġ�� ����մϴ�.
				pt.x = (LONG)( m_lfDirection * (double)( pView->m_BufferdImg.GetWidth() ) / 360.0 + (double)( pView->m_nEast ) * pView->m_lfRatio );			
				// ȭ�� �߾���ġ�� �°� �̹��� ��ġ�� �����մϴ�
				pView->m_ImgPos = ::SetImagePosToClientPoint( pView->GetClientWidth(), 
					pView->GetClientHeight(),
					pView->m_BufferdImg.GetWidth(),
					pView->m_BufferdImg.GetHeight(),
					CPoint( pView->GetClientWidth() / 2, pView->GetClientHeight() / 2 ),
					pt);
				pView->m_ImgPos.y = y;
				// �̹����� ȭ������� ������ ���� �����մϴ�.
				
				// �ٽñ׸��ϴ�.
				pMain->m_PartShow.SetWindowSizeToImg( CSize( pView->m_BufferdImg.GetWidth(), pView->m_BufferdImg.GetHeight() ) );
				pMain->m_PartShow.SetReductionRect( pView->m_ClientRect, CSize( pView->m_BufferdImg.GetWidth(), pView->m_BufferdImg.GetHeight() ), pView->m_ImgPos );

				pView->m_bNowLoading = FALSE;

				pView->SetImagePosRight();
				pView->Invalidate();

				pMain->m_PartShow.ShowWindow( SW_SHOW );
				pMain->m_PartShow.Invalidate();
				pMain->m_TopViewWnd.Invalidate();
				Invalidate();

				// Ÿ�̸Ӹ� �� ���Ѽ� �����찡 ������ ���������� �ڿ������� �̵��ϵ��� �մϴ�.
				
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

		// ������ ���� Ŭ���ϸ� â�� �� ������ ���� �̵��Ѵ�.
		
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

		m_MousePos = m_PrevMousePos; // ���� ��ǥ ����			

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
		// ����� ��� ���¿����� �̹������� ���콺 ��ǥ�� ������ �ϹǷ�
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
	// x ��ư�� ������ �������� �ʰ� �����츦 ����ϴ�.
	ShowWindow( SW_HIDE );
	
	return ;// ���� ����

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

		// �ּ�ȭ ��ư �Ǵ� ��ũ����Ʈ ���� ���콺 �������� ���
		if( m_LinkPoint || m_RightTop || m_bMaximizeMouseOver )
			SetCursor( hCursorLinkArrow ); // ���콺 Ŀ���� ��ũ�� ���ߴϴ�.
		else
			SetCursor( hCursorMove ); // �׿��� ��쿡�� �ո�� Ŀ���� �ٲߴϴ�.
		return TRUE;

	default:
		break;
	}	
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CSatelliteViewWnd::SetImagePosToClientPoint( CPoint PtOnImg )
{
		// �̹����� �� PtOnImg �� ȭ�� �߾����� ������ �̹��� ��ġ�� �����մϴ�.
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

		// ���� �������� ȭ����ǥ�� �ʺ� ����.
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
	// �������� �ּ�ũ�⸦ 300x300 ���� �����մϴ�.
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

	Dlg.m_bInsert = TRUE; // �Է¸��� ������ ���
	Dlg.m_bSatellite = TRUE;
	Dlg.m_bTopView = FALSE;

	m_RbuttonPt = GetImagePoint( m_ImgPos, m_ClientRect, m_RbuttonPt );
	Dlg.m_nSatellitePosX = m_RbuttonPt.x; // ��Ʈ�ѿ� �̸� �Է��ϰ�
	Dlg.m_nSatellitePosY = m_RbuttonPt.y;

	// ��ȭ���ڸ� ����.
	if( Dlg.DoModal() == IDOK )
	{
		App->SavePanoFileData();
	}

	Invalidate();
}