
// SYUCampusView.cpp : CSYUCampusView Ŭ������ ����
//

#include "stdafx.h"
#include "SYUCampus.h"

#include "SYUCampusDoc.h"
#include "SYUCampusView.h"

#include "BufferDC.h"
#include "PanoFileData.h"
#include "MainFrm.h"
#include "ViewFilePointDlg.h"
#include "ViewFileLinkData.h"
#include "ViewFilePointDlg.h"
#include "UserRatio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSYUCampusView

IMPLEMENT_DYNCREATE(CSYUCampusView, CView)

BEGIN_MESSAGE_MAP(CSYUCampusView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSYUCampusView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_COMMAND(ID_RATIO_10, &CSYUCampusView::OnRatio10)
	ON_COMMAND(ID_RATIO_08, &CSYUCampusView::OnRatio08)
	ON_COMMAND(ID_RATIO_06, &CSYUCampusView::OnRatio06)
	ON_COMMAND(ID_RATIO_04, &CSYUCampusView::OnRatio04)
	ON_UPDATE_COMMAND_UI(ID_RATIO_08, &CSYUCampusView::OnUpdateRatio08)
	ON_UPDATE_COMMAND_UI(ID_RATIO_10, &CSYUCampusView::OnUpdateRatio10)
	ON_UPDATE_COMMAND_UI(ID_RATIO_06, &CSYUCampusView::OnUpdateRatio06)
	ON_UPDATE_COMMAND_UI(ID_RATIO_04, &CSYUCampusView::OnUpdateRatio04)
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_COMMAND(ID_ZOOMIN, &CSYUCampusView::OnZoomin)
	ON_COMMAND(ID_ZOOMOUT, &CSYUCampusView::OnZoomout)
	ON_UPDATE_COMMAND_UI(ID_ZOOMIN, &CSYUCampusView::OnUpdateZoomin)
	ON_UPDATE_COMMAND_UI(ID_ZOOMOUT, &CSYUCampusView::OnUpdateZoomout)
	ON_COMMAND(ID_RATIO_USER, &CSYUCampusView::OnRatioUser)
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSYUCampusView ����/�Ҹ�

CSYUCampusView::CSYUCampusView()
{
	m_bClicked = FALSE;
	m_BufferdImg.Init( this );
	m_lfRatio = 1.0;
	m_ImgPos = CPoint(0, 0 );
	m_bLoaded = FALSE;
	m_BufferdSybol.Init( this );
	m_ImgPos = CPoint( 0, 0 );

	Afx_pVoidCurrentFile = NULL;

	for( int i = 0 ; i < 4 ; i++ )
	{
		m_bDirectionMarkMouseOver[i] = FALSE;
	}
	m_bLinkPointMouseOver = FALSE;	
	m_bNowLoading = FALSE;
}

CSYUCampusView::~CSYUCampusView()
{
}

BOOL CSYUCampusView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CSYUCampusView::OnDraw(CDC* /*pDC*/)
{
	CSYUCampusDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}
void CSYUCampusView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CSYUCampusView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CSYUCampusView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CSYUCampusView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CSYUCampusView::OnContextMenu(CWnd* pWnd, CPoint point)
{

	CMenu PopupMenu;
	PopupMenu.LoadMenu( IDR_MAINFRAME );
	CMenu* pMenu;
	pMenu = PopupMenu.GetSubMenu( 0 );
	pMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd() );

	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_MENU1, point.x, point.y, this, TRUE);
	//theApp.ShowPopupMenu( IDR_MENU1, point, this );
}


// CSYUCampusView ����

#ifdef _DEBUG
void CSYUCampusView::AssertValid() const
{
	CView::AssertValid();
}

void CSYUCampusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSYUCampusDoc* CSYUCampusView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSYUCampusDoc)));
	return (CSYUCampusDoc*)m_pDocument;
}
#endif //_DEBUG

// CSYUCampusView �޽��� ó����

BOOL CSYUCampusView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}

void CSYUCampusView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if( !m_bLoaded )
		return ;

	SetCapture();
	m_bClicked = TRUE;
	m_PrevMousePos = m_MousePos = point;

	CView::OnLButtonDown(nFlags, point);
}

void CSYUCampusView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;

	if( !m_bLoaded )
		return ;
	
	ReleaseCapture();
	m_bClicked = FALSE;

	// �� ��ư�� ������ ���
	if( PtInRect( m_DirectionMarkRect[0], point ) )	
		OnKeyDown( VK_LEFT, 0, 0 );// ����Ű�� ���������� ���� ȿ��

	// �� ��ư�� ������ ���
	if( PtInRect( m_DirectionMarkRect[1], point ) )
		OnKeyDown( VK_UP, 0, 0 );// ����Ű�� ���������� ���� ȿ��

	if( PtInRect( m_DirectionMarkRect[2], point ) )
		OnKeyDown( VK_RIGHT, 0, 0 );// ����Ű�� ���������� ���� ȿ��

	if( PtInRect( m_DirectionMarkRect[3], point ) )
		OnKeyDown( VK_DOWN, 0, 0 );// ����Ű�� ���������� ���� ȿ��

	CView::OnLButtonUp(nFlags, point);
}

BOOL CSYUCampusView::LoadImage( TCHAR *FileName )
{
	CString strTmp;
	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;	
	strTmp = _T("�̹��� �ε���...");
	pMain->SetCaptionBarText( strTmp );

	if( m_BufferdImg.LoadFile( FileName ) == FALSE )
	{
		return FALSE;
	}
	else
	{
		if( !m_BufferdImg.SetRatio( m_lfRatio ) )
		{
			return FALSE;
		}
	}
	
	strTmp.Format( _T("%s ������ �ε�Ǿ����ϴ�."), FileName );
	pMain->SetCaptionBarText( strTmp );	

	pMain->SyncSliderBarPos( m_lfRatio );

	m_bLoaded = TRUE;		

	return TRUE;
}
void CSYUCampusView::OnPaint()
{
	CBufferDC dc(this);
	//CPaintDC dc(this);

	Graphics G( dc );

	// �ε�� ȸ�� ����
	if( m_bLoaded )
	{
		CBrush brush( RGB( 217, 214, 206 ) );
		CBrush* pOldB;

		pOldB = dc.SelectObject( &brush );
		dc.Rectangle( m_ClientRect.left - 2, m_ClientRect.top - 2, m_ClientRect.right + 2, m_ClientRect.bottom + 2 );
		dc.SelectObject( pOldB );
		brush.DeleteObject();
	}
	else
	{
		dc.Rectangle( m_ClientRect.left - 2, m_ClientRect.top - 2, m_ClientRect.right + 2, m_ClientRect.bottom + 2 );
	}

	

	// �������б� �ɹ� ���
	if( !m_bLoaded )
	{
		if( m_BufferdSybol.m_pCachedbmp )
			G.DrawCachedBitmap( m_BufferdSybol.m_pCachedbmp, m_ClientRect.right / 2 - m_BufferdSybol.m_ImgModiSize.cx / 2, m_ClientRect.bottom / 2 - m_BufferdSybol.m_ImgModiSize.cy / 2 );
	}

	// �̹��� ���
	if( m_bLoaded )
	{
		if( m_BufferdImg.m_pCachedbmp )
		{
			G.DrawCachedBitmap( m_BufferdImg.m_pCachedbmp, m_ImgPos.x, m_ImgPos.y );
			G.DrawCachedBitmap( m_BufferdImg.m_pCachedbmp, (-m_BufferdImg.m_ImgModiSize.cx + m_ImgPos.x), m_ImgPos.y); // ���� �̹��� ���
			G.DrawCachedBitmap( m_BufferdImg.m_pCachedbmp, m_BufferdImg.m_ImgModiSize.cx + m_ImgPos.x, m_ImgPos.y);
		}
	}

	if( DEBUG_MODE )
	{
		CString strTmp;
		strTmp.Format( _T("ImgPos %d %d"), m_ImgPos.x, m_ImgPos.y );
		dc.TextOut( 0, 0, strTmp );
		strTmp.Format( _T("�̹��� ���� ũ�� %d %d"), m_BufferdImg.m_ImgSize.cx, m_BufferdImg.m_ImgSize.cy );
		dc.TextOut( 0, 20, strTmp );
		strTmp.Format( _T("�̹��� ũ�� %d %d"), m_BufferdImg.GetWidth(), m_BufferdImg.GetHeight() );
		dc.TextOut( 0, 40, strTmp );
		strTmp.Format( _T("���� %lf"), m_lfRatio );
		dc.TextOut( 0, 60, strTmp );
		strTmp.Format( _T("���� �̸� %s"), m_BufferdImg.m_FileName );
		dc.TextOut( 0, 80, strTmp );
		CPoint pt = GetImagePoint( m_ImgPos, m_ClientRect, CPoint( m_ClientRect.right / 2, m_ClientRect.bottom / 2 ) );
		strTmp.Format( _T("ȭ�� �߾� ��ǥ %d %d"), pt.x, pt.y );
		dc.TextOut( 0, 100, strTmp );
		strTmp.Format( _T("�� ũ�� %d %d"), m_ClientRect.Width(), m_ClientRect.Height() );
		dc.TextOut( 0, 120, strTmp );

		Pen pen( Color( 128, 255, 0, 0), 2.0f );
		G.DrawLine( &pen, m_ClientRect.right / 2 - 20, m_ClientRect.bottom / 2,  m_ClientRect.right / 2 + 20, m_ClientRect.bottom / 2 );
		G.DrawLine( &pen, m_ClientRect.right / 2, m_ClientRect.bottom / 2 - 20,  m_ClientRect.right / 2, m_ClientRect.bottom / 2 + 20 );
	}

	if( m_bLoaded )
	{
		POSITION pos;
		int num;
		CViewFileLinkData* pData;
		CPoint Pt;
		pos = m_LinkFileList.GetHeadPosition();
		num = m_LinkFileList.GetCount();
		for( int i = 0 ; i < num ; i++ )	
		{
			pData = (CViewFileLinkData*)m_LinkFileList.GetNext( pos );	
			Pt = pData->m_NewPoint + m_ImgPos;
			Pt.x -= 25;
			Pt.y -= 25;
			Afx_ImgListFoot.Draw( &dc, 0, Pt, ILD_NORMAL );
			Pt.x += m_BufferdImg.GetWidth();
			Afx_ImgListFoot.Draw( &dc, 0, Pt, ILD_NORMAL );
			Pt.x -= m_BufferdImg.GetWidth() * 2;
			Afx_ImgListFoot.Draw( &dc, 0, Pt, ILD_NORMAL );
		}

		if( m_bDirectionMarkMouseOver[0] )
			Afx_ImgListLTRB.Draw( &dc, 0 + 4, CPoint( 10 ,m_ClientRect.bottom / 2 - 11 ), ILD_NORMAL );
		else
			Afx_ImgListLTRB.Draw( &dc, 0, CPoint( 10 ,m_ClientRect.bottom / 2 - 11 ), ILD_NORMAL );

		if( m_bDirectionMarkMouseOver[1] )
			Afx_ImgListLTRB.Draw( &dc, 1 + 4, CPoint( m_ClientRect.right / 2 - 11, 10 ), ILD_NORMAL );
		else
			Afx_ImgListLTRB.Draw( &dc, 1, CPoint( m_ClientRect.right / 2 - 11, 10 ), ILD_NORMAL );

		if( m_bDirectionMarkMouseOver[2] )
			Afx_ImgListLTRB.Draw( &dc, 2 + 4, CPoint( m_ClientRect.right - 32 , m_ClientRect.bottom / 2 - 11 ), ILD_NORMAL );	
		else
			Afx_ImgListLTRB.Draw( &dc, 2, CPoint( m_ClientRect.right - 32 , m_ClientRect.bottom / 2 - 11 ), ILD_NORMAL );	

		if( m_bDirectionMarkMouseOver[3] )
			Afx_ImgListLTRB.Draw( &dc, 3 + 4, CPoint( m_ClientRect.right / 2  - 11, m_ClientRect.bottom - 32 ), ILD_NORMAL );
		else
			Afx_ImgListLTRB.Draw( &dc, 3, CPoint( m_ClientRect.right / 2  - 11, m_ClientRect.bottom - 32 ), ILD_NORMAL );
	}	

	if( m_bNowLoading )
	{
		G.DrawCachedBitmap( m_ImageLoading.m_pCachedbmp, m_ClientRect.right / 2 - m_ImageLoading.GetWidth() / 2, m_ClientRect.bottom / 2 - m_ImageLoading.GetHeight() / 2 );	
	}
}
void CSYUCampusView::OnMouseMove(UINT nFlags, CPoint point)
{	
	if( !m_bLoaded )
		return ;

	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;

	if( m_bClicked )
	{
		CPoint tmp;
		m_PrevMousePos = point;

		tmp = m_ImgPos - ( m_MousePos - m_PrevMousePos );

		if( tmp.y > 0 ) // �̹����� �Ʒ��� �������� �� ����
		{
			tmp.y = 0;
		}

		if( m_BufferdImg.m_ImgModiSize.cy > m_ClientRect.bottom ) // �̹���cy�� �� ũ��
 		{
			if( m_ClientRect.bottom - m_BufferdImg.m_ImgModiSize.cy > tmp.y )
			{
				tmp.y = m_ClientRect.bottom - m_BufferdImg.m_ImgModiSize.cy; // �̹����� ���� �ö󰡴°� ����
			}
			else
			{
			}
		}
		else //�̹��� ũ�Ⱑ �� �۴�
		{
			tmp.y = m_ClientRect.bottom / 2 - m_BufferdImg.m_ImgModiSize.cy / 2; // �̹����� ��� ���
		}

		m_ImgPos = tmp;

		m_MousePos = m_PrevMousePos; // ���� ��ǥ ����	

		if( m_ImgPos.x > m_BufferdImg.m_ImgModiSize.cx )
			m_ImgPos.x = 0;

		if( m_ImgPos.x < -m_BufferdImg.m_ImgModiSize.cx )
			m_ImgPos.x = 0;

		CalculateDirection();

		// SetRecuctionRect �Լ��� ���� Ŭ���̾�Ʈ�� ũ��, �̹��� ũ��, �̹��� ��ġ ������ �ް�
		// ���� Ŭ���̾�Ʈ�� ��ġ�� �̹����� ����κ����� ����س��� �Լ��Դϴ�.
		pMain->m_PartShow.SetReductionRect( m_ClientRect, CSize( m_BufferdImg.GetWidth(), m_BufferdImg.GetHeight() ), m_ImgPos );
		// ��Ʈ �� �����츦 ��ȿȭ�մϴ�.
		pMain->m_PartShow.Invalidate();

		// ���� �¿� ��ư���� ���콺 �����ߴ� Ȯ���ϰ� ���콺 �������� ��� ó���Դϴ�.
		// �ε�� ���¿����� ����˴ϴ�.
		for( int i = 0 ; i < 4 ; i++ )
		{
			if( PtInRect( m_DirectionMarkRect[i], point ) )
			{
				m_bDirectionMarkMouseOver[i] = TRUE;
				InvalidateRect( &m_DirectionMarkRect[i] );
				SetTimer( i, 10, NULL );
			}
			else
			{
				m_bDirectionMarkMouseOver[i] = FALSE;
				InvalidateRect( &m_DirectionMarkRect[i] );			
				KillTimer( i );
			}
		}

		// 	m_LinkFileList �� ��ũ ����Ʈ�� ����� ����Ʈ�Դϴ�.
		CViewFileLinkData* pData;
		POSITION pos;
		int num;
		pos = m_LinkFileList.GetHeadPosition();
		num = m_LinkFileList.GetCount();
		CRect LinkPointRect;
		BOOL bResult = FALSE;

		for( int i = 0 ; i < num ; i++ )
		{
			pData = (CViewFileLinkData*)m_LinkFileList.GetNext( pos );
			LinkPointRect = CRect( pData->m_NewPoint.x - 25 + m_ImgPos.x, 
				pData->m_NewPoint.y - 25 + m_ImgPos.y, 
				pData->m_NewPoint.x + 25 + m_ImgPos.x,
				pData->m_NewPoint.y + 25 + m_ImgPos.y);

			// ���߹ٴ��� ȭ�� ���ʿ� �־� �Ⱥ��̴� ���
			if( pData->m_NewPoint.x + 25 + m_ImgPos.x < 0 )
				break;
			// ���߹ٴ��� ȭ�� ���ʿ� �־� �Ⱥ��� ���
			if( pData->m_NewPoint.y + 25 + m_ImgPos.y < 0 )
				break;
			if( pData->m_NewPoint.x - 25 + m_ImgPos.x > m_ClientRect.right )
				break;
			if( pData->m_NewPoint.y - 25 + m_ImgPos.y > m_ClientRect.bottom )
				break;

			// ���߹ٴ�(��ũ ����Ʈ) ���� ���콺 ���� �ϸ� bResult TRUE �����Ѵ�
			if( PtInRect( &LinkPointRect, point ) )
			{
				bResult = TRUE;
				break;
			}

			CRect TempRect;
			TempRect = LinkPointRect;
			TempRect.left -= m_BufferdImg.GetWidth();
			TempRect.right -= m_BufferdImg.GetWidth();

			// ���� ���߹ٴ� �Դϴ�.
			if( PtInRect( &TempRect, point ) )
			{
				bResult = TRUE;
				break;
			}

			TempRect = LinkPointRect;
			TempRect.left += m_BufferdImg.GetWidth();
			TempRect.right += m_BufferdImg.GetWidth();

			// ������ ���߹ٴ� �Դϴ�.
			if( PtInRect( &TempRect, point ) )
			{
				bResult = TRUE;
				break;
			}		
		}
		Invalidate();
		m_bLinkPointMouseOver = bResult;
	}
	CView::OnMouseMove(nFlags, point);
}

void CSYUCampusView::OnSize(UINT nType, int cx, int cy)
{
	//CView::OnSize(nType, cx, cy);

	GetClientRect( &m_ClientRect );

	//m_ImgPos = SetImagePosRight( m_ClientRect.right, m_ClientRect.bottom, m_BufferdImg.m_ImgModiSize.cx, m_BufferdImg.m_ImgModiSize.cy, m_ImgPos );
	SetImagePosRight();

	CSYUCampusView* pView;
	CMainFrame* pMain;
	pView = (CSYUCampusView*)Afx_pVoidView;
	pMain = (CMainFrame*)Afx_pVoidMain;

	m_DirectionMarkRect[0] = CRect( 10 , m_ClientRect.bottom / 2 - 11, 10 + 22, m_ClientRect.bottom / 2 + 11 );
	m_DirectionMarkRect[1] = CRect( m_ClientRect.right / 2 - 11, 10, m_ClientRect.right / 2 + 11, 10 + 22 );
	m_DirectionMarkRect[2] = CRect( m_ClientRect.right - 32 , m_ClientRect.bottom / 2 - 11, m_ClientRect.right - 32 + 22, m_ClientRect.bottom / 2 + 11 );	
	m_DirectionMarkRect[3] = CRect( m_ClientRect.right / 2 - 11, m_ClientRect.bottom - 32, m_ClientRect.right / 2 + 11, m_ClientRect.bottom - 10 );

}

void CSYUCampusView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	CPoint ImgCenter; // �̹����� ��� ��ǥ�Դϴ�.
	CSize PrevImgSize; // ���� �̹����� ũ�� �Դϴ�.
	
	CViewFilePointDlg Dlg;
	double ratio; // ���� �̹����� �� �̤�
	
	ImgCenter = GetImagePoint( m_ImgPos, m_ClientRect, CPoint( m_ClientRect.right / 2, m_ClientRect.bottom / 2 ) ) ; //ȭ����� �̹��� �߾� ��ǥ�� ���մϴ�.

	PrevImgSize = m_BufferdImg.m_ImgModiSize; // �̹��� ũ�⸦ ���մϴ�
	
	CMainFrame* pMain = (CMainFrame *)Afx_pVoidMain;		
	CPanoFileData* pData = (CPanoFileData*)Afx_pVoidCurrentFile;	
	
	ratio = m_lfRatio;
	switch( nChar )
	{
	case VK_NEXT:
		// 20% ���
		ratio -= 0.2;
		if( ratio <= 0.4 )
		{
			ratio = 0.4;
			return ;
		}
 		break;
	case VK_PRIOR:
		// 20% Ȯ��
		ratio += 0.2;
		if( ratio > 1.0 )
		{
			ratio = 1.0;
			return ;
		}
		break;
	case VK_ADD:
		// �����ִ� �� ������
		if( Afx_pVoidCurrentFile == NULL )
			return ;
		pData->m_nEast = pData->m_nEast + 100;
		pMain->m_TopViewWnd.m_nEast = pData->m_nEast;
		pMain->m_TopViewWnd.m_lfDirection = (double)( ImgCenter.x - pMain->m_TopViewWnd.m_nEast ) * 360.0 / (double)( m_BufferdImg.GetWidth() );
		pMain->m_TopViewWnd.Invalidate();
		return ;
		break;
	case VK_SUBTRACT:
		if( Afx_pVoidCurrentFile == NULL )
			return ;
		pData->m_nEast = pData->m_nEast - 100;
		pMain->m_TopViewWnd.m_nEast = pData->m_nEast;
		pMain->m_TopViewWnd.m_lfDirection = (double)( ImgCenter.x - pMain->m_TopViewWnd.m_nEast ) * 360.0 / (double)( m_BufferdImg.GetWidth() );
		pMain->m_TopViewWnd.Invalidate();
		return ;
		break;
	case VK_MULTIPLY:
		if( Afx_pVoidCurrentFile == NULL )
			return ;
		pData->m_nSatelliteEast = pData->m_nSatelliteEast + 100;
		pMain->m_SatelliteViewWnd.m_nEast = pData->m_nSatelliteEast;
		pMain->m_SatelliteViewWnd.m_lfDirection = (double)( ImgCenter.x - pMain->m_SatelliteViewWnd.m_nEast ) * 360.0 / (double)( m_BufferdImg.GetWidth() );
		pMain->m_SatelliteViewWnd.Invalidate();
		return ;
		break;
	case VK_DIVIDE:
		if( Afx_pVoidCurrentFile == NULL )
			return ;
		pData->m_nSatelliteEast = pData->m_nSatelliteEast - 100;
		pMain->m_SatelliteViewWnd.m_nEast = pData->m_nSatelliteEast;
		pMain->m_SatelliteViewWnd.m_lfDirection = (double)( ImgCenter.x - pMain->m_SatelliteViewWnd.m_nEast ) * 360.0 / (double)( m_BufferdImg.GetWidth() );
		pMain->m_SatelliteViewWnd.Invalidate();
		return ;
		break;
	case VK_HOME:

		CSYUCampusApp* App;
		App = (CSYUCampusApp*)Afx_pVoidApp;
		App->SavePanoFileData();

		return ;
		break;
	case VK_DOWN:
		m_ImgPos.y -= m_BufferdImg.GetHeight() / 10;
		SetImagePosRight();
		
		Invalidate();
		return ;
		break;
	case VK_UP:
		m_ImgPos.y += m_BufferdImg.GetHeight() / 10;
		SetImagePosRight();
		Invalidate();
		return ;
		break;
	case VK_LEFT:
		m_ImgPos.x += m_BufferdImg.GetWidth() / 10;
		SetImagePosRight();
		CalculateDirection();
		pMain->m_SatelliteViewWnd.Invalidate();
		pMain->m_TopViewWnd.Invalidate();
		Invalidate();
		return ;
		break;
	case VK_RIGHT:
		m_ImgPos.x -= m_BufferdImg.GetWidth() / 10;
		SetImagePosRight();
		CalculateDirection();
		Invalidate();
		pMain->m_SatelliteViewWnd.Invalidate();
		pMain->m_TopViewWnd.Invalidate();

		return ;
		break;
	}
	
	SetImageRatio( ratio );
	pMain->SyncSliderBarPos( ratio );
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


int CSYUCampusView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	TCHAR str[ MAX_PATH ];
	GetCurrentDirectory( MAX_PATH, str );
	lstrcat( str, _T("\\Images\\ShamYookSymbol.jpg") );
	if( !m_BufferdSybol.LoadFile( str ) )
	{
		CString ErrorMsg;
		ErrorMsg.Format( _T("%s ������ �� �� �����ϴ�!"), str );
		AfxMessageBox( ErrorMsg );
	}
	else
	{
		if( m_BufferdSybol.SetRatio( 1 ) )
		{
		}
	}	

	LoadFileLinkData();

	Afx_pVoidView = this;
	
	TCHAR strTmp[ MAX_PATH ];

	lstrcpy( strTmp, AppDir );
	wsprintf( strTmp, _T("%s\\images\\ImageLoading.jpg"), strTmp );

	m_ImageLoading.Init( this );
	m_ImageLoading.LoadFile( strTmp );		
	m_ImageLoading.SetRatio( 1 );

	return 0;
}


void CSYUCampusView::SetImagePosRight( void )
{
	if( m_ImgPos.y > 0 )
	{
		m_ImgPos.y = 0;		
	}

	if( m_BufferdImg.GetHeight() > m_ClientRect.bottom )
	{
		if( m_ClientRect.bottom - m_BufferdImg.GetHeight() > m_ImgPos.y )
		{
			m_ImgPos.y = m_ClientRect.bottom - m_BufferdImg.GetHeight();
		}
	}
	else
	{
		m_ImgPos.y = m_ClientRect.bottom / 2 - m_BufferdImg.GetHeight() / 2 ;
	}

	if( abs(m_ImgPos.x) >= m_BufferdImg.GetWidth() )
	{
		if( m_ImgPos.x != 0 )
			m_ImgPos.x %= m_BufferdImg.GetWidth();
		/*
		if( m_ImgPos.x > 0 )
			m_ImgPos.x -= m_BufferdImg.GetWidth();
		else
			m_ImgPos.x += m_BufferdImg.GetWidth();
			*/
	}
}
int CSYUCampusView::GetClientWidth( void )
{
	return m_ClientRect.right;
}
int CSYUCampusView::GetClientHeight( void )
{
	return m_ClientRect.bottom;
}

void CSYUCampusView::SetImageRatio( double lfRatio )
{
	if( lfRatio == m_lfRatio )
		return ;

	if( lfRatio > 1.0 )
		return ;

	CPoint ImgCenter; // �̹����� ��� ��ǥ�Դϴ�.
	CPoint NewImgCenter; // ���ο�(ũ�Ⱑ �����) �̹����� ��� ��ǥ�Դϴ�.
	CSize PrevImgSize; // ���� �̹����� ũ�� �Դϴ�.
	CSize NewImgSize; // ���ο� �̹����� ũ�� �Դϴ�.
	double ratio; // ���� �̹����� �� �̤�
	
	ImgCenter = GetImagePoint( m_ImgPos, m_ClientRect, CPoint( m_ClientRect.right / 2, m_ClientRect.bottom / 2 ) ) ; //ȭ����� �̹��� �߾� ��ǥ�� ���մϴ�.

	PrevImgSize = m_BufferdImg.m_ImgModiSize; // �̹��� ũ�⸦ ���մϴ�
	
	CMainFrame* pMain = (CMainFrame *)Afx_pVoidMain;		
	CPanoFileData* pData = (CPanoFileData*)Afx_pVoidCurrentFile;

	if( (int)(double)m_BufferdImg.m_ImgSize.cy * lfRatio < m_ClientRect.bottom ) // ��� / Ȯ��� �̹����� ȭ�麸�� �۴�	
		m_lfRatio =(double)m_ClientRect.bottom / (double)m_BufferdImg.m_ImgSize.cy; // �̹��� ũ��� ���̸� �����.
	else
		m_lfRatio = lfRatio;

	if( !m_BufferdImg.SetRatio( m_lfRatio ) )
	{
		AfxMessageBox( _T("�̹��� �׸��� ����") );
	}
	else
	{
		NewImgSize = m_BufferdImg.m_ImgModiSize;

		ratio = (double)NewImgSize.cx / (double)PrevImgSize.cx; // ���ο� �̹��� ũ�⸦ ���� ������ ���մϴ�/

		NewImgCenter.x = (long)( (double)ImgCenter.x * ratio ); // ���ο� �̹����� �߾� ��ǥ�� ���մϴ�.
		NewImgCenter.y = (long)( (double)ImgCenter.y * ratio );

		m_ImgPos.x = ( NewImgCenter.x - m_ClientRect.right / 2 ) * (-1);
		m_ImgPos.y = ( NewImgCenter.y - m_ClientRect.bottom / 2 ) * (-1);


		//m_ImgPos = SetImagePosRight( m_ClientRect.right, m_ClientRect.bottom, m_BufferdImg.m_ImgModiSize.cx, m_BufferdImg.m_ImgModiSize.cy, m_ImgPos );
		SetImagePosRight();

		Invalidate();
	}
}

void CSYUCampusView::OnRatio10()
{
	
	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;
	if( m_bLoaded )
	{
		SetImageRatio( 1.0 );	
		pMain->SetCaptionBarText( _T("�̹��� ũ�⸦ 100% �� ���� �߽��ϴ�.") );
	}
	pMain->SyncSliderBarPos( 1.0 );
}
void CSYUCampusView::OnRatio08()
{
	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;
	if( m_bLoaded )
	{
		SetImageRatio( 0.8 );
		pMain->SetCaptionBarText( _T("�̹��� ũ�⸦ 80% �� ���� �߽��ϴ�.") );
	}
	pMain->SyncSliderBarPos( 0.8 );
}

void CSYUCampusView::OnRatio06()
{
	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;
	if( m_bLoaded )
	{
		SetImageRatio( 0.6 );
		pMain->SetCaptionBarText( _T("�̹��� ũ�⸦ 60% �� ���� �߽��ϴ�.") );
	}
	pMain->SyncSliderBarPos( 0.6 );
}

void CSYUCampusView::OnRatio04()
{	
	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;
	if( m_bLoaded )
	{
		SetImageRatio( 0.4 );
		pMain->SetCaptionBarText( _T("�̹��� ũ�⸦ 40% �� ���� �߽��ϴ�.") );
	}
	pMain->SyncSliderBarPos( 0.4 );
}


void CSYUCampusView::OnUpdateRatio10(CCmdUI *pCmdUI)
{
	if( m_bLoaded )
		pCmdUI->Enable( TRUE );
	else
		pCmdUI->Enable( FALSE );

	if( m_lfRatio == 1.0 )
	{
		pCmdUI->SetCheck( TRUE );
		pCmdUI->Enable( FALSE );
	}
	else
		pCmdUI->SetCheck( FALSE );
}

void CSYUCampusView::OnUpdateRatio08(CCmdUI *pCmdUI)
{
	if( m_bLoaded )
		pCmdUI->Enable( TRUE );
	else
		pCmdUI->Enable( FALSE );

	if( m_lfRatio == 0.8 )
	{
		pCmdUI->SetCheck( TRUE );
		pCmdUI->Enable( FALSE );
	}
	else
		pCmdUI->SetCheck( FALSE );
}


void CSYUCampusView::OnUpdateRatio06(CCmdUI *pCmdUI)
{
	if( m_bLoaded )
		pCmdUI->Enable( TRUE );
	else
		pCmdUI->Enable( FALSE );

	if( m_lfRatio == 0.6 )
	{
		pCmdUI->SetCheck( TRUE );
		pCmdUI->Enable( FALSE );
	}
	else
		pCmdUI->SetCheck( FALSE );
}

void CSYUCampusView::OnUpdateRatio04(CCmdUI *pCmdUI)
{

	if( m_bLoaded )
		pCmdUI->Enable( TRUE );
	else
		pCmdUI->Enable( FALSE );

	if( m_lfRatio == 0.4 )
	{
		pCmdUI->SetCheck( TRUE );
		pCmdUI->Enable( FALSE );
	}
	else
		pCmdUI->SetCheck( FALSE );
}

BOOL CSYUCampusView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	switch( nHitTest )
	{
	case HTCLIENT:		
		if( m_bLoaded )
		{
			if( m_bLinkPointMouseOver )
			{
				SetCursor( hCursorLinkArrow );
				return TRUE;
			}

			for( int i = 0 ; i < 4 ; i++ )
			{
				if( m_bDirectionMarkMouseOver[i] )
				{
					SetCursor( hCursorLinkArrow );
					return TRUE;
				}
			}
			SetCursor( hCursorMove );
			return TRUE;
		}
		break;
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CSYUCampusView::LoadFileLinkData( void )
{
	TCHAR str[ MAX_PATH ];

	lstrcpy( str, AppDir );
	lstrcat( str, _T("\\data\\") );
	lstrcat( str, _T("ViewFileLinkData.dat") );

	CViewFileLinkData* pData;

	CFile File;
	if( File.Open( str, CFile::modeRead ) )
	{
		int num;
		File.Read( &num, sizeof( int ) );

		for( int i = 0 ; i < num ; i++ )
		{
			pData = new CViewFileLinkData;
			File.Read( pData->m_CurFileName, sizeof( TCHAR ) * 50 );
			File.Read( pData->m_NewFileName, sizeof( TCHAR ) * 50 );
			File.Read( &pData->m_NewPoint, sizeof( CPoint ) );

			AfxViewFileLinkList.AddTail( pData );
		}
		return TRUE;			
	}
	else
		return FALSE;
}
void CSYUCampusView::LoadFileLinkPoint( void )
{
	POSITION pos;
	int num;
	pos = AfxViewFileLinkList.GetHeadPosition();
	num = AfxViewFileLinkList.GetCount();
	CViewFileLinkData* pData;
	TCHAR strTmp[50];
	//CPoint Pt;	

	lstrcpy( strTmp, m_LoadedFileName );

	m_LinkFileList.RemoveAll();
	for( int i = 0 ; i < num ; i++ )	
	{
		pData = (CViewFileLinkData*)AfxViewFileLinkList.GetNext( pos );		
		if( lstrcmp( strTmp, pData->m_CurFileName ) == 0 )
		{
			m_LinkFileList.AddTail( pData );
		}
	}
}
void CSYUCampusView::OnTimer(UINT_PTR nIDEvent)
{
	switch( nIDEvent )
	{
	case 0:
		m_ImgPos.x += 5;		
		break;
	case 1:
		m_ImgPos.y += 5;
		break;
	case 2:
		m_ImgPos.x -= 5;
		break;
	case 3:
		m_ImgPos.y -= 5;
		break;
	}
	CalculateDirection();
	SetImagePosRight();
	Invalidate();	

	CView::OnTimer(nIDEvent);
}

void CSYUCampusView::CalculateDirection( void )
{
	static int nNum = 0;

	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;

	CPoint pt;
	pt = GetImagePoint( m_ImgPos, m_ClientRect, CPoint( m_ClientRect.right / 2, m_ClientRect.bottom / 2 ) );	
	pMain->m_TopViewWnd.m_lfDirection = (double)( pt.x - pMain->m_TopViewWnd.m_nEast * m_lfRatio ) * 360.0 / (double)( m_BufferdImg.GetWidth() );
	pMain->m_SatelliteViewWnd.m_lfDirection = (double)( pt.x - pMain->m_SatelliteViewWnd.m_nEast * m_lfRatio ) * 360.0 / (double)( m_BufferdImg.GetWidth() );
	
	// �������б� �ȳ��� �ٽ� �׸���, �����ִ°� ����
	// ž �� �����츦 Invalidate �ϴ� ���� �ſ� ������.
	// ���� �� �Լ��� ȣ��ɶ����� Invalidate �ϴ� ���� �ƴ϶� 10���� �ѹ����� Invalidate �Ѵ�
	nNum++;
	if( nNum > 10000 )
	{
		nNum = 0;
	}
	if( nNum % 10 == 0 )
	{
		// ž �� �����츦 ��ȿȭ �մϴ�.
		if( pMain->m_TopViewWnd.IsWindowVisible() )
			pMain->m_TopViewWnd.Invalidate();
		if( pMain->m_SatelliteViewWnd.IsWindowVisible() )
			pMain->m_SatelliteViewWnd.Invalidate();
	}
}

void CSYUCampusView::OnZoomin()
{
	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;

	double ratio;
	if( m_lfRatio < 0.4 )
		ratio = 0.4;
	else if( m_lfRatio < 0.6 )
		ratio = 0.6;
	else if( m_lfRatio < 0.8 )
		ratio = 0.8;
	else
		ratio = 1.0;

	SetImageRatio( ratio );

	// �����̴� �� ����ȭ
	pMain->SyncSliderBarPos( ratio );
}

void CSYUCampusView::OnZoomout()
{
	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;

	double ratio;
	if( m_lfRatio > 0.8 )
		ratio = 0.8;
	else if( m_lfRatio > 0.6 )
		ratio = 0.6;
	else if( m_lfRatio > 0.4 )	
		ratio = 0.4;	
	else
		ratio = 0.2;

	SetImageRatio( ratio );
	pMain->SyncSliderBarPos( ratio );
}

void CSYUCampusView::OnUpdateZoomin(CCmdUI *pCmdUI)
{
	if( m_bLoaded )
		pCmdUI->Enable( TRUE );
	else
		pCmdUI->Enable( FALSE );

}

void CSYUCampusView::OnUpdateZoomout(CCmdUI *pCmdUI)
{
	if( m_bLoaded )
		pCmdUI->Enable( TRUE );
	else
		pCmdUI->Enable( FALSE );
}

BOOL CSYUCampusView::IsImageSizeRight( double ratio )
{

	if( m_BufferdImg.m_ImgSize.cy * ratio < m_ClientRect.bottom )
		return FALSE;
	else
		return TRUE;
}
void CSYUCampusView::OnRatioUser()
{
	CUserRatio Dlg;

	if( m_bLoaded )
		Dlg.DoModal();
	else
		AfxMessageBox( _T("ũ�⸦ ������ �̹����� �ε���� �ʾҽ��ϴ�!") );
}

void CSYUCampusView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if( m_bLoaded )
	{
		CPoint ScreenPoint = point;
		CMenu PopupMenu;
		PopupMenu.LoadMenu( IDR_MENU_POPUP );
		CMenu* pMenu;
		pMenu = PopupMenu.GetSubMenu( 0 );	
		ClientToScreen( &ScreenPoint );
		pMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, ScreenPoint.x, ScreenPoint.y, AfxGetMainWnd() );
		m_CurMousePos = point;
	}

	CView::OnRButtonUp(nFlags, point);
}
