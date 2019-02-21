// TopViewWnd.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MainFrm.h"
#include "BufferDC.h"
#include "SYUCampus.h"
#include "TopViewWnd.h"
#include "PanoFileData.h"
#include "ViewFileLinkData.h"
#include "SYUCampusView.h"
#include "PanoFileShowDlg.h"

// CTopViewWnd

IMPLEMENT_DYNAMIC(CTopViewWnd, CWnd)

CTopViewWnd::CTopViewWnd()
{
	m_ImgPos = CPoint( -700, -70 );
	m_lfRatio = 1;
	m_bClicked = FALSE;

	m_bSizeChanged = FALSE;
	m_ChangedSize = CSize( 0, 0 );

	m_ViewPtClicked = FALSE;	

	m_bNewLinkPointAdd = FALSE;

	m_bRightTop = FALSE;
	m_LinkPoint = FALSE;
	m_bMaximizeMouseOver = FALSE;
}

CTopViewWnd::~CTopViewWnd()
{
}


BEGIN_MESSAGE_MAP(CTopViewWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_SETCURSOR()
	ON_WM_RBUTTONUP()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()



// CTopViewWnd �޽��� ó�����Դϴ�.



int CTopViewWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// SetWindowLong �Լ��� ���ӿ��ؼ� ������ �Ӽ��� �ٲ۴�..
	// WndLong ������ ���� �����츦 ���� �ڿ� �ٽ� ������������� �����Ҷ� ���˴ϴ�.
	WndLong = WndCurrentLong = ::SetWindowLong( this->GetSafeHwnd(), GWL_EXSTYLE, ::GetWindowLong( this->GetSafeHwnd(), GWL_EXSTYLE ) );
	

	TCHAR str[ MAX_PATH ];
	lstrcpy( str, AppDir );
	lstrcat( str, _T("\\Images\\Topmap.png") );

	m_BuildingName.Init( this );
	if( m_BuildingName.LoadFile( str ) )	
		m_BuildingName.SetRatio( 1 );

	lstrcpy( str, AppDir );
	lstrcat( str, _T("\\Images\\Topmap.jpg") );

	CString strTmp;

	m_BufferdImg.Init( this );
	if( !m_BufferdImg.LoadFile( str ) )
	{
		strTmp.Format( _T("%s ������ �� �� �����ϴ�!"), str );
		AfxMessageBox( strTmp );
	}
	else
	{
		if( !m_BufferdImg.SetRatio( m_lfRatio ) )
		{
			AfxMessageBox( _T("�̹��� �׸��� ����") );
		}
		else
		{
		}
	}
	// ������ ��ġ ����;; �� ������ ������ ���� �̵�
	CSYUCampusView* pView = (CSYUCampusView*)Afx_pVoidView;
	CPoint pt;
	pt.x = pView->m_ClientRect.right;
	pt.y = 0;
	pView->ClientToScreen( &pt );

	SetWindowPos( NULL, pt.x - 300, pt.y, 0, 0, SWP_NOSIZE );

	return 0;
}


void CTopViewWnd::MakeTransparentWnd( BYTE bAlpha )
{
	// �״��� SetLayeredWindowAttributes �Լ��� ȣ���ϸ� ���̴�..
	// �����찡 ����������..	
	WndCurrentLong = ::SetWindowLong( this->GetSafeHwnd(), GWL_EXSTYLE, ::GetWindowLong( this->GetSafeHwnd(), GWL_EXSTYLE ) | WS_EX_LAYERED );		
	SetLayeredWindowAttributes( RGB(255, 0, 0), bAlpha, LWA_ALPHA | LWA_COLORKEY );
}

void CTopViewWnd::MakeOpaqueWnd(void )
{
	//�̸� ����� �������� ������ �������� �ǵ�����.	
	WndCurrentLong = ::SetWindowLong( this->GetSafeHwnd(), GWL_EXSTYLE, WndLong );	
}
void CTopViewWnd::OnPaint()
{
	//CPaintDC dc(this);

	CBufferDC dc(this);	

	Graphics G( dc );
	G.SetSmoothingMode( SmoothingModeHighQuality );

	// �簢���� �׸���, ����������� �ٽñ׸��⸦ ���� �����Ƿ�;;
	dc.Rectangle( m_ClientRect.left - 5, m_ClientRect.top - 5, m_ClientRect.right + 5, m_ClientRect.bottom + 5 );

	// �������б� �ȳ��� �׸���
	if( m_BufferdImg.m_pCachedbmp  )
	{
		G.DrawCachedBitmap( m_BufferdImg.m_pCachedbmp, m_ImgPos.x, m_ImgPos.y );			
	}
	if( m_BuildingName.m_pCachedbmp && bBuildingNameShow )
		G.DrawCachedBitmap( m_BuildingName.m_pCachedbmp, m_ImgPos.x, m_ImgPos.y );	

	if( bViewPointShow )
	{
		CPanoFileData *pData;
		POSITION pos;
		int num = AfxPanoFileList.GetCount();

		CPoint Pt;

		pos = AfxPanoFileList.GetHeadPosition();
		for( int i = 0 ; i < num ; i++ )
		{
			pData = (CPanoFileData *)AfxPanoFileList.GetNext( pos );
			Pt = pData->m_TopViewPt + m_ImgPos;
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

	// �ּ�ȭ ��ư�� ���콺 ����
	if( m_bRightTop ) // m_bTopRight
		Afx_ImgListLTRB.Draw( &dc, 6, CPoint( m_RightTopRt.left, m_RightTopRt.top ), ILD_NORMAL );
	else
		Afx_ImgListLTRB.Draw( &dc, 2, CPoint( m_RightTopRt.left, m_RightTopRt.top ), ILD_NORMAL );	

	if( m_bMaximizeMouseOver )
		Afx_ImgListLTRB.Draw( &dc, 5, CPoint( m_MaximizeRt.left, m_MaximizeRt.top ), ILD_NORMAL );
	else
		Afx_ImgListLTRB.Draw( &dc, 1, CPoint( m_MaximizeRt.left, m_MaximizeRt.top ), ILD_NORMAL );

		
/*
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
	}	
	*/
}

void CTopViewWnd::OnMouseMove(UINT nFlags, CPoint point)
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
			m_bRightTop = TRUE;
			InvalidateRect( &m_RightTopRt );
		}
		else
		{
			m_bRightTop = FALSE;
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

			PointRect = CRect(pData->m_TopViewPt.x - SIZE_RECT + m_ImgPos.x, 
				pData->m_TopViewPt.y - SIZE_RECT + m_ImgPos.y, 
				pData->m_TopViewPt.x + SIZE_RECT + m_ImgPos.x, 
				pData->m_TopViewPt.y + SIZE_RECT + m_ImgPos.y );
			
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

void CTopViewWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bClicked = TRUE;
	m_PrevMousePos = m_MousePos = point;
	SetCapture();

	return ;
	CWnd::OnLButtonDown(nFlags, point);
}

void CTopViewWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	CSYUCampusView* pView = (CSYUCampusView*)Afx_pVoidView;
	CMainFrame* pMain = (CMainFrame*)Afx_pVoidMain;

	m_bClicked = FALSE;
	ReleaseCapture();

	CPanoFileData* pData;
	POSITION pos;
	CRect PointRect;

	pos = AfxPanoFileList.GetHeadPosition();
	int num;
	num  = AfxPanoFileList.GetCount();

	for( int i = 0 ; i < num ; i++ )
	{
		pData = (CPanoFileData *)AfxPanoFileList.GetNext( pos );

		PointRect = CRect(pData->m_TopViewPt.x - SIZE_RECT + m_ImgPos.x, 
			pData->m_TopViewPt.y - SIZE_RECT + m_ImgPos.y, 
			pData->m_TopViewPt.x + SIZE_RECT + m_ImgPos.x, 
			pData->m_TopViewPt.y + SIZE_RECT + m_ImgPos.y );
		
		// ž �信�� �� ����Ʈ�� Ŭ������ ����̴�.
		if( PtInRect( &PointRect, point ) && bViewPointShow )
		{	
			
			if( m_bNewLinkPointAdd ) // �� �����쿡�� ��Ŭ���� �Ͽ� ���ο� ��ũ�� �����Ҷ� �̺κ��� Ȱ��ȭ�ȴ�.
			{
				CViewFileLinkData* pLinkData;
				pLinkData = new CViewFileLinkData;
				lstrcpy( pLinkData->m_CurFileName, pView->m_LoadedFileName );
				lstrcpy( pLinkData->m_NewFileName, pData->m_FileName );
				pLinkData->m_NewPoint = pView->m_CurMousePos;

				AfxViewFileLinkList.AddTail( pLinkData );				
				pView->m_LinkFileList.AddTail( pLinkData );
				m_bNewLinkPointAdd = FALSE;
				SetWindowText( _T("�������б� �ȳ���") );
				SaveFileLinkData();
				pView->Invalidate();
				return ;
			}			
			

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
				// Ŭ���� ��ġ�� �߾ӿ� ������ �Ѵ�.
				CPoint Pt;
				Pt = GetImagePoint( m_ImgPos, m_ClientRect, point );

				SetImagePosToClientPoint( Pt );
				m_ViewerPt = pData->m_TopViewPt;
				pMain->m_SatelliteViewWnd.m_ViewerPt = pData->m_SatelliteTopViewPt;

				Pt = GetImagePoint( pMain->m_SatelliteViewWnd.m_ImgPos, 
					pMain->m_SatelliteViewWnd.m_ClientRect,
					pData->m_SatelliteTopViewPt );
				Pt +=  pMain->m_SatelliteViewWnd.m_ImgPos;
				pMain->m_SatelliteViewWnd.SetImagePosToClientPoint( Pt );

				CPoint pt;
				int y;			
				pt = pView->m_ImgPos; // ���� �̹��� ��ġ�� �޽��ϴ�.
				y = pt.y;

				m_nEast = pData->m_nEast; // East ���� �����մϴ�.	
				pMain->m_SatelliteViewWnd.m_nEast = pData->m_nSatelliteEast;

				// �ٸ� �� ����Ʈ�� ���������� ���� ������ ������ �ϴ� �ڵ� �Դϴ�.
				// ȭ�� �߾� ��ġ�� ����մϴ�.
				pt.x = (LONG)( m_lfDirection * (double)( pView->m_BufferdImg.GetWidth() ) / 360.0 + (double)( m_nEast ) * pView->m_lfRatio );			
				// ȭ�� �߾���ġ�� �°� �̹��� ��ġ�� �����մϴ�
				pView->m_ImgPos = ::SetImagePosToClientPoint( pView->GetClientWidth(), 
					pView->GetClientHeight(),
					pView->m_BufferdImg.GetWidth(),
					pView->m_BufferdImg.GetHeight(),
					CPoint( pView->GetClientWidth() / 2, pView->GetClientHeight() / 2 ),
					pt);
				pView->m_ImgPos.y = y;
				// �̹����� ȭ������� ������ ���� �����մϴ�.
				pView->m_bNowLoading = FALSE;
				pView->SetImagePosRight();
				pView->Invalidate();
				
				// �ٽñ׸��ϴ�.
				// ��Ʈ�����찡 ȭ��� �̹����� ����� ��ġ�� ��Ÿ���� ���� �ڵ��Դϴ�.
				pMain->m_PartShow.SetWindowSizeToImg( CSize( pView->m_BufferdImg.GetWidth(), pView->m_BufferdImg.GetHeight() ) );
				pMain->m_PartShow.SetReductionRect( pView->m_ClientRect, CSize( pView->m_BufferdImg.GetWidth(), pView->m_BufferdImg.GetHeight() ), pView->m_ImgPos );				

				pMain->m_PartShow.ShowWindow( SW_SHOW );
				pMain->m_PartShow.Invalidate();
				pMain->m_SatelliteViewWnd.Invalidate();

				Invalidate();

				// Ÿ�̸Ӹ� �� ���Ѽ� �����찡 ������ ���������� �ڿ������� �̵��ϵ��� �մϴ�.

				MySetWindowSize( CPoint( pView->m_ClientRect.right - 300, 0 ), CSize( 300, 300 ) );
				if( pMain->m_SatelliteViewWnd.IsWindowVisible() )
					pMain->m_SatelliteViewWnd.MySetWindowSize( CPoint( pView->m_ClientRect.right - 600, 0 ), CSize( 300, 300 ) );
					
			}			
			break;
		} // if( PtInRect( &PointRect, point ) )
		// ������ ���� Ŭ���ϸ� â�� �� ������ ���� �̵��Ѵ�.	
	}	 // for
	//CRect RightTop	
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

BOOL CTopViewWnd::SaveFileLinkData( void )
{
	TCHAR str[ MAX_PATH ];

	lstrcpy( str, AppDir );
	lstrcat( str, _T("\\data\\") );
	lstrcat( str, _T("ViewFileLinkData.dat") );

	CViewFileLinkData* pData;
	POSITION pos;

	CFile File;
	if( File.Open( str, CFile::modeCreate | CFile::modeWrite ) )
	{
		int num;
		num = AfxViewFileLinkList.GetCount();

		File.Write( &num, sizeof( int ) );
		pos = AfxViewFileLinkList.GetHeadPosition();
		for( int i = 0 ; i < num ; i++ )
		{
			pData = (CViewFileLinkData*)AfxViewFileLinkList.GetNext( pos );
			File.Write( pData->m_CurFileName, sizeof( TCHAR ) * 50 );
			File.Write( pData->m_NewFileName, sizeof( TCHAR ) * 50 );
			File.Write( &pData->m_NewPoint, sizeof( CPoint ) );
		}
		return TRUE;			
	}
	else
		return FALSE;
}

void CTopViewWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	GetClientRect( &m_ClientRect );

	if( m_bSizeChanged == TRUE ) // ����� ��û�� ���� �̹��� ũ�� ������ ���
	{
		m_bSizeChanged = FALSE;
	}
	else// �ٽ� ũ�⸦ ��ȯ���� �ʽ��ϴ�.
	{
		if( m_ClientRect.right > m_BufferdImg.GetWidth() ) 
		{
			OnKeyUp( VK_UP, 0, 0 );
		}
		if( m_ClientRect.bottom > m_BufferdImg.GetHeight() )
		{
			OnKeyUp( VK_UP, 0, 0 );
		}
	}
	m_ImgPos = SetImagePosRight( m_ClientRect.right, m_ClientRect.bottom, m_BufferdImg.m_ImgModiSize.cx, m_BufferdImg.m_ImgModiSize.cy, m_ImgPos );
	Invalidate();
/*
	if( nType == SIZE_MAXIMIZED )
	{
		CSYUCampusView* pView;
		pView = (CSYUCampusView*)Afx_pVoidView;

		CPoint Pt( 0, 0 );

		pView->ClientToScreen( &Pt );

		SetWindowPos( NULL, Pt.x, Pt.y, pView->GetClientWidth(), pView->GetClientHeight(), SWP_NOACTIVATE );

	}
	*/

	m_RightTopRt = CRect( m_ClientRect.right - 24, 2, m_ClientRect.right - 2, 24 );
	m_MaximizeRt = CRect( m_RightTopRt.left - 24, 2, m_RightTopRt.left - 2, 24 );

}

void CTopViewWnd::OnClose()
{
	// �ݱ� ��ư�� ������ �����츦 �ı����� �ʰ� �����...

	this->ShowWindow( SW_HIDE );

	//CWnd::OnClose();
}
void CTopViewWnd::OnTimer(UINT_PTR nIDEvent)
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

void CTopViewWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch( nChar )
	{
		// esc Ű�� ���ο� ��ũ ������ ����Ѵ�. ������ �̸��� ������� �ٲٰ� PointAdd ������ FALSE �� �����.
	case VK_ESCAPE:
		SetWindowText( _T("�������б� �ȳ���") );
		m_bNewLinkPointAdd = FALSE;
		break;
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CTopViewWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	BOOL bLink = FALSE;
	CRect PointRect;
	CRect RightTop( m_ClientRect.right - 30, 0, m_ClientRect.right, 30 );
	switch( nHitTest )
	{
	case HTCLIENT:

		// �ּ�ȭ ��ư �Ǵ� ��ũ����Ʈ ���� ���콺 �������� ���
		if( m_LinkPoint || m_bRightTop || m_bMaximizeMouseOver )
			SetCursor( hCursorLinkArrow ); // ���콺 Ŀ���� ��ũ�� ���ߴϴ�.
		else
			SetCursor( hCursorMove ); // �׿��� ��쿡�� �ո�� Ŀ���� �ٲߴϴ�.
		return TRUE;

	default:
		break;
	}	
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}
void CTopViewWnd::MySetWindowSize( CPoint Pt, CSize sz )
{
	m_ChangedPoint = Pt;
	m_ChangedSize = sz;
	SetTimer( 5, 10, NULL );
}

void CTopViewWnd::SetImagePosToClientPoint( CPoint PtOnImg )
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

void CTopViewWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	CSYUCampusApp* App;

	App = (CSYUCampusApp*)Afx_pVoidApp;
	CPanoFileShowDlg Dlg;

	Dlg.m_bInsert = TRUE; // �Է¸��� ������ ���
	Dlg.m_bSatellite = FALSE;
	Dlg.m_bTopView = TRUE;

	point = GetImagePoint( m_ImgPos, m_ClientRect, point );
	Dlg.m_PosX = point.x; // ��Ʈ�ѿ� �̸� �Է��ϰ�
	Dlg.m_PosY = point.y;

	// ��ȭ���ڸ� ����.
	if( Dlg.DoModal() == IDOK )
	{
		App->SavePanoFileData();
	}

	Invalidate();
	return ;

	CWnd::OnRButtonUp(nFlags, point);
}


void CTopViewWnd::OnMyMinimize( void )
{
	CSYUCampusView* pView = (CSYUCampusView*)Afx_pVoidView;
	MySetWindowSize( CPoint( pView->m_ClientRect.right - 300, 0 ), CSize( 300, 300 ) );
}

void CTopViewWnd::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// �������� �ּ�ũ�⸦ 300x300 ���� �����մϴ�.
	lpMMI->ptMinTrackSize.x = 300;
	lpMMI->ptMinTrackSize.y = 300;

	CWnd::OnGetMinMaxInfo(lpMMI);
}

void CTopViewWnd::OnMyMaximize( void )
{
	CSYUCampusView* pView = (CSYUCampusView*)Afx_pVoidView;
	MySetWindowSize( CPoint( pView->m_ClientRect.left, 0 ), CSize( pView->GetClientWidth(), pView->GetClientHeight() ) );
}