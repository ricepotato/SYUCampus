// CategoryView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SYUCampus.h"
#include "CategoryView.h"
#include "TreeViewData.h"
#include "PanoFileShowDlg.h"


// CCategoryView

IMPLEMENT_DYNAMIC(CCategoryView, CDockablePane)

CCategoryView::CCategoryView()
{

}

CCategoryView::~CCategoryView()
{
}


BEGIN_MESSAGE_MAP(CCategoryView, CDockablePane)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// CCategoryView 메시지 처리기입니다.



void CCategoryView::OnPaint()
{
	CPaintDC dc(this);

	// CDockablePane 이 다시그리기를 하지 않으므로 적절히 그리기를 한다.	

	GetClientRect( &m_ClntRect );	
	dc.Rectangle( m_ClntRect.left - 5, m_ClntRect.top - 5, m_ClntRect.right + 5, m_ClntRect.bottom + 5 );
}

int CCategoryView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_TRACKSELECT;

	if (!m_wndCategory.Create(dwViewStyle, CRect( 0, 0, 0, 0 ), this, 4))
	{
		TRACE0("파일 뷰를 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	m_SearchEdit.Create( WS_CHILD | WS_VISIBLE | WS_BORDER, CRect( 0, 0, 0, 0 ), this, 0 );

	m_BtnSearch.Create( _T("검색"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect( 0, 0, 0, 0 ), this, 1209 );
	
	HFONT hFont;

	hFont = CreateFont( 12, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, _T("굴림") );

	m_BtnSearch.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM( TRUE, 0 ) );
	m_SearchEdit.SendMessage( WM_SETFONT, (WPARAM)hFont, MAKELPARAM( TRUE, 0 ) );

	//DeleteObject( hFont );
	m_wndCategory.SetImageList(&Afx_CategoryImages, TVSIL_NORMAL);


	InitTree();
	//OnChangeVisualStyle();
	//AdjustLayout();

	m_BtnSearch.EnableWindow( TRUE );

	return 0;
}

void CCategoryView::InitTree( void )
{
	//m_wndCategory.DeleteAllItems();

	HTREEITEM hRoot = m_wndCategory.InsertItem(_T("삼육대학교"), 0, 0); // 루트 입니다,
	m_wndCategory.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD); // 굵은 글씨로 바꿔줍니다.
	
	// 트리의 0, 0, 은 삼육대학교 심벌 마크입니다.

	LoadTreeListFile();

	int num;
	num = AfxTotalTreeList.GetCount();
	POSITION pos;
	pos = AfxTotalTreeList.GetHeadPosition();

	CTreeViewData* pData;
	HTREEITEM temp;
	for( int i = 0 ; i < num ; i++ )
	{
		pData = (CTreeViewData*)AfxTotalTreeList.GetNext( pos );

		// 최상위
		if( pData->m_nParentIndex == 0 )
		{
			temp = m_wndCategory.InsertItem( pData->m_PointName, pData->m_nImgListIndex, pData->m_nImgListIndex, hRoot );
			pData->m_hTreeItem = temp;
			m_wndCategory.SetItemData( temp, (DWORD_PTR)pData );
		}
		else
		{
			POSITION posSearch;
			posSearch = AfxTotalTreeList.GetHeadPosition();
			CTreeViewData* pDataSearch;
			for( int j = 0 ; j < num ; j++ )
			{
				pDataSearch = (CTreeViewData*)AfxTotalTreeList.GetNext( posSearch );
				if( pDataSearch->m_nIndex == pData->m_nParentIndex )
				{
					temp = m_wndCategory.InsertItem( pData->m_PointName, 
						pData->m_nImgListIndex, 
						pData->m_nImgListIndex, 
						pDataSearch->m_hTreeItem );
					pData->m_hTreeItem = temp;
					m_wndCategory.SetItemData( temp, (DWORD_PTR)pData );

					break;
				}				
			}
		}
	}

	m_wndCategory.Expand(hRoot, TVE_EXPAND);

}
void CCategoryView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	GetClientRect( &m_ClntRect );
	m_SearchEdit.SetWindowPos( NULL, m_ClntRect.left + 5, m_ClntRect.top + 5, m_ClntRect.right - 55, 20, SWP_NOACTIVATE | SWP_NOZORDER );
	m_wndCategory.SetWindowPos( NULL, m_ClntRect.left - 1, m_ClntRect.top + 30, m_ClntRect.right, m_ClntRect.bottom - 30, SWP_NOACTIVATE | SWP_NOZORDER );
	m_BtnSearch.SetWindowPos( NULL, m_ClntRect.right - 45, m_ClntRect.top + 5, 40, 20, SWP_NOACTIVATE | SWP_NOZORDER );
}

void CCategoryView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//AfxMessageBox( _T("클릭이염ㅋ???") );
	//CDockablePane::OnLButtonDown(nFlags, point);
}

void CCategoryView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//AfxMessageBox( _T("클릭질..ㅁㄴㄹㅇㅁㄹㄴ?") );
}

BOOL CCategoryView::LoadTreeListFile( void )
{
	CFile File;
	CTreeViewData* pData;
	CString strTmp;
	BOOL bSuccess = FALSE;

	for( int i = 0 ; i < 13 ; i++ )
	{
		strTmp.Format( _T("%s\\Data\\TreeData_%d.dat"), AppDir, i );

		if( File.Open( strTmp, CFile::modeRead ) )
		{
			int num;
			File.Read( &num, sizeof( int ) );

			for( int i = 0 ; i < num ; i++ )
			{
				pData = new CTreeViewData;
				
				File.Read( pData->m_PointName, sizeof( TCHAR ) * 50 );
				File.Read( pData->m_FileName, sizeof( TCHAR ) * MAX_PATH );
				File.Read( &pData->m_Point, sizeof( CPoint ) );
				File.Read( &pData->m_ImgPos, sizeof( CPoint ) );
				File.Read( &pData->m_nIndex, sizeof( int ) );
				File.Read( &pData->m_nParentIndex, sizeof( int ) );
				File.Read( &pData->m_nImgListIndex, sizeof( int ) );
				File.Read( &pData->m_Detail, sizeof( TCHAR ) * 512 );

				AfxTotalTreeList.AddTail( pData );
			}

			File.Close();
			bSuccess = TRUE;
		}
	}
	return bSuccess;
}
