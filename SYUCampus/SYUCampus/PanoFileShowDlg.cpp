// PanoFileShowDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SYUCampus.h"
#include "PanoFileShowDlg.h"
#include "PanoFileData.h"


// CPanoFileShowDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPanoFileShowDlg, CDialog)

CPanoFileShowDlg::CPanoFileShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPanoFileShowDlg::IDD, pParent)
	, m_EditEast(0)
	, m_PosX(0)
	, m_PosY(0)
	, m_EditFileName(_T(""))
	, m_nSatelliteEast(0)
	, m_nSatellitePosX(0)
	, m_nSatellitePosY(0)
{

}

CPanoFileShowDlg::~CPanoFileShowDlg()
{
}

void CPanoFileShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT_POSX, m_PosX);
	DDX_Text(pDX, IDC_EDIT_POSY, m_PosY);
	DDX_Control(pDX, IDC_BTN_DELETE, m_Btn_Delete);
	DDX_Control(pDX, IDC_BTN_MODIFY, m_Btn_Modify);
	DDX_Control(pDX, IDC_EDIT_EAST, m_Edit_East);
	DDX_Control(pDX, IDC_EDIT_POSX, m_Edit_PosX);
	DDX_Control(pDX, IDC_EDIT_POSY, m_Edit_PosY);
	DDX_Text(pDX, IDC_EDIT_SATELLITEEAST, m_nSatelliteEast);
	DDX_Text(pDX, IDC_EDIT_SATELLITEPOSX, m_nSatellitePosX);
	DDX_Text(pDX, IDC_EDIT_SATELLITEPOSY, m_nSatellitePosY);
}


BEGIN_MESSAGE_MAP(CPanoFileShowDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CPanoFileShowDlg::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDCANCEL, &CPanoFileShowDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CPanoFileShowDlg::OnBnClickedBtnModify)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPanoFileShowDlg 메시지 처리기입니다.

BOOL CPanoFileShowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();	

	LV_COLUMN col;
	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH ;

	col.pszText = _T("파일이름");
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	m_ListCtrl.InsertColumn( 0, &col );

	col.pszText = _T("East");
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	m_ListCtrl.InsertColumn( 1, &col );

	col.pszText = _T("Point");
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	m_ListCtrl.InsertColumn( 2, &col );

	col.pszText = _T("SatelliteEast");
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	m_ListCtrl.InsertColumn( 3, &col );

	col.pszText = _T("SatellitePoint");
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	m_ListCtrl.InsertColumn( 4, &col );

	RefreshList();
	
	m_Edit_East.EnableWindow( FALSE );
	m_Edit_PosX.EnableWindow( FALSE );
	m_Edit_PosY.EnableWindow( FALSE );
	m_Btn_Delete.EnableWindow( FALSE );
	m_Btn_Modify.EnableWindow( FALSE );

	m_BufferedImg.Init( this );
	
	

	m_bDraw = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CPanoFileShowDlg::RefreshList( void )
{
	POSITION pos;

	CPanoFileData* pData;
	pos = AfxPanoFileList.GetHeadPosition();
	int num;
	num = AfxPanoFileList.GetCount();
	TCHAR strTmp[256];

	LV_ITEM it;
	it.mask = LVIF_TEXT;

	m_ListCtrl.DeleteAllItems();

	for( int i = 0 ; i < num ; i++ )
	{
		pData = (CPanoFileData*)AfxPanoFileList.GetNext( pos );
		it.iItem = i;
		it.iSubItem = 0;
		it.pszText = pData->m_FileName;
		m_ListCtrl.InsertItem( &it );

		it.iSubItem = 1;
		wsprintf( strTmp, _T("%d"), pData->m_nEast );
		it.pszText = strTmp;
		m_ListCtrl.SetItem( &it );

		it.iSubItem = 2;
		wsprintf( strTmp, _T("%d %d"), pData->m_TopViewPt.x, pData->m_TopViewPt.y );
		it.pszText = strTmp;
		m_ListCtrl.SetItem( &it );

		it.iSubItem = 3;
		wsprintf( strTmp, _T("%d"), pData->m_nSatelliteEast );
		it.pszText = strTmp;
		m_ListCtrl.SetItem( &it );

		it.iSubItem = 4;
		wsprintf( strTmp, _T("%d %d"), pData->m_SatelliteTopViewPt.x, pData->m_SatelliteTopViewPt.y );
		it.pszText = strTmp;
		m_ListCtrl.SetItem( &it );
	}

}
BOOL CPanoFileShowDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	LPNMHDR hdr;
	LPNMLISTVIEW nlv;
//	LPNMITEMACTIVATE nia;

	hdr = (LPNMHDR)lParam;
	nlv = (LPNMLISTVIEW)lParam;

	double ratioWnd;
	double ratioImg;

	TCHAR FileFullPath[ MAX_PATH ];

	if( hdr->hwndFrom == m_ListCtrl.GetSafeHwnd() )
	{
		switch( hdr->code )
		{
		case LVN_ITEMCHANGED:
			if( nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED )) 
			{
				m_Btn_Delete.EnableWindow( TRUE );
				m_Btn_Modify.EnableWindow( TRUE );
				m_Edit_East.EnableWindow( TRUE );
				m_Edit_PosX.EnableWindow( TRUE );
				m_Edit_PosY.EnableWindow( TRUE );

				POSITION pos;
				pos = AfxPanoFileList.GetHeadPosition();
				CPanoFileData* pData;
				for( int i = 0 ; i < nlv->iItem + 1 ; i++ )
				{
					pData = (CPanoFileData*)AfxPanoFileList.GetNext( pos );
				}

				if( !m_bInsert )
				{					
					m_EditFileName = pData->m_FileName;
					m_EditEast = pData->m_nEast;
					m_PosX = pData->m_TopViewPt.x;
					m_PosY = pData->m_TopViewPt.y;

					m_nSatelliteEast = pData->m_nSatelliteEast;
					m_nSatellitePosX = pData->m_SatelliteTopViewPt.x;
					m_nSatellitePosY = pData->m_SatelliteTopViewPt.y;

					UpdateData( FALSE );
				}
				else
				{
					if( m_bSatellite )
					{
						m_EditFileName = pData->m_FileName;
						m_EditEast = pData->m_nEast;
						m_PosX = pData->m_TopViewPt.x;
						m_PosY = pData->m_TopViewPt.y;
					}
					if( m_bTopView )
					{
						m_nSatelliteEast = pData->m_nSatelliteEast;
						m_nSatellitePosX = pData->m_SatelliteTopViewPt.x;
						m_nSatellitePosY = pData->m_SatelliteTopViewPt.y;
					}
					UpdateData( FALSE );

				}
				m_SelectedItem = nlv->iItem;

				wsprintf( FileFullPath, _T("%s\\Panoramas\\%s"), AppDir, pData->m_FileName );

				if( m_BufferedImg.LoadFile( FileFullPath ) )
				{
					CWnd* pWnd;
	
					pWnd = GetDlgItem( IDC_IMGOUT );
					::GetWindowRect( pWnd->m_hWnd, &m_ImgOutRect );
					m_ImgOutRect.top += 20;			
					m_ImgOutRect.left += 10;
					m_ImgOutRect.right -= 10;
					m_ImgOutRect.bottom -= 10;

					ratioWnd = (double)m_ImgOutRect.Width() / (double)m_ImgOutRect.Height();
					ratioImg = (double)m_BufferedImg.m_ImgSize.cx / (double)m_BufferedImg.m_ImgSize.cy;				

					m_ImgPt.x = m_ImgOutRect.left;
					m_ImgPt.y = m_ImgOutRect.top;
					this->ScreenToClient( &m_ImgPt );

					if( ratioImg > ratioWnd )
					{
						if( m_BufferedImg.SetWidth( m_ImgOutRect.Width() ) )
						{
							m_ImgPt.y += (m_ImgOutRect.Height() - m_BufferedImg.GetHeight() ) / 2;
							m_bDraw = TRUE;
						}
						else
							AfxMessageBox( _T("파일 로드에 실패했습니다!") );
					}
					else
					{				
						if( m_BufferedImg.SetHeight( m_ImgOutRect.Height() ) )
						{
							m_ImgPt.x += ( m_ImgOutRect.Width() - m_BufferedImg.GetWidth() ) / 2;			
							m_bDraw = TRUE;
						}
						else
							AfxMessageBox( _T("파일 로드에 실패했습니다!") );
					}

					if( m_bDraw )
						Invalidate();
				}

			}
			else
			{
				m_Btn_Delete.EnableWindow( FALSE );
				m_Btn_Modify.EnableWindow( FALSE );
				m_Edit_East.EnableWindow( FALSE );
				m_Edit_PosX.EnableWindow( FALSE );
				m_Edit_PosY.EnableWindow( FALSE );
			}
			break;
		}
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CPanoFileShowDlg::OnBnClickedBtnDelete()
{
	POSITION pos;
	pos = AfxPanoFileList.GetHeadPosition();
	CPanoFileData* pData;
	for( int i = 0 ; i < m_SelectedItem + 1; i++ )  // m_SelectedItem + 1은 pData 가 해당 아이템을 가리키도록 만듭니다.
	{
		pData = (CPanoFileData*)AfxPanoFileList.GetNext( pos );
	}
	delete pData;

	pos = AfxPanoFileList.GetHeadPosition();
	for( int i = 0 ; i < m_SelectedItem; i++ ) // m_SelectedItem 은 pos 가 해당 아이템을 가리키도록 만듭니다.
	{
		pData = (CPanoFileData*)AfxPanoFileList.GetNext( pos );
	}

	AfxPanoFileList.RemoveAt( pos );

	RefreshList();
}

void CPanoFileShowDlg::OnBnClickedCancel()
{
	EndDialog( IDCANCEL );
	OnCancel();
}

void CPanoFileShowDlg::OnBnClickedBtnModify()
{
	UpdateData( TRUE ); // 변수와 컨트롤을 동기화 시키되 변수를 바꾼뒤에;

	POSITION pos;
	pos = AfxPanoFileList.GetHeadPosition();
	CPanoFileData* pData;
	for( int i = 0 ; i < m_SelectedItem + 1; i++ )  // m_SelectedItem + 1은 pData 가 해당 아이템을 가리키도록 만듭니다.
	{
		pData = (CPanoFileData*)AfxPanoFileList.GetNext( pos );
	}	

	pData->m_nEast = m_EditEast;
	pData->m_TopViewPt.x = m_PosX;
	pData->m_TopViewPt.y = m_PosY;
	pData->m_nSatelliteEast = m_nSatelliteEast;
	pData->m_SatelliteTopViewPt.x = m_nSatellitePosX;
	pData->m_SatelliteTopViewPt.y = m_nSatellitePosY;

	//RefreshList();

	EndDialog( IDOK );
}

void CPanoFileShowDlg::OnBnClickedBtnInsert()
{
}

void CPanoFileShowDlg::OnPaint()
{
	CPaintDC dc(this);

	Graphics G( dc );

	if( m_bDraw && m_BufferedImg.m_pCachedbmp )
		G.DrawCachedBitmap( m_BufferedImg.m_pCachedbmp, m_ImgPt.x, m_ImgPt.y );
}
