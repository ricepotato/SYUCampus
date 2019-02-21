// CategoryTree.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SYUCampus.h"
#include "CategoryTree.h"
#include "MainFrm.h"
#include "SYUCampusView.h"
#include "PanoFileData.h"


// CCategoryTree

IMPLEMENT_DYNAMIC(CCategoryTree, CTreeCtrl)

CCategoryTree::CCategoryTree()
{

}

CCategoryTree::~CCategoryTree()
{
}


BEGIN_MESSAGE_MAP(CCategoryTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CCategoryTree::OnNMClick)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CCategoryTree::OnTvnSelchanged)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CCategoryTree �޽��� ó�����Դϴ�.



void CCategoryTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	
}

void CCategoryTree::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	

	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}

void CCategoryTree::OnLButtonUp(UINT nFlags, CPoint point)
{	
	CTreeCtrl::OnLButtonUp(nFlags, point);
}

void CCategoryTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;

	CTreeCtrl* tree = this; // Ʈ���� ����ϰ��... �ƴҰ��� �� ��Ʈ�� ������ �ְ�����~
	
	HTREEITEM hItem;
	CString strName;

	hItem = tree->GetNextItem(NULL, TVGN_CARET); // ���� ���õǾ��� ���� �ڵ��� �����´�.
	strName = tree->GetItemText(hItem); // �� �������� �̸��� ���´�.
	//strName.Format( _T("[%s]"), tree->GetItemText(hItem) );
	//MessageBox(strName); // �̸� ��~
/*
	hItem = tree->GetNextItem(hItem, TVGN_PARENT); // ���� ���õǾ��� ���� ���� ������ �ڵ��� �����´�.
	strName = tree->GetItemText(hItem); // �� �������� �̸��� ���´�.
	MessageBox(strName); // �̸� ��~
	*/

	POSITION pos;
	int nListNum;
	CTreeViewData *pTVData;
	pos = AfxTotalTreeList.GetHeadPosition();
	nListNum = AfxTotalTreeList.GetCount();

	CMainFrame* pMain = (CMainFrame *)Afx_pVoidMain;
	CSYUCampusView* pView = (CSYUCampusView*)Afx_pVoidView;
	

	//CString CsOut;
	for( int i = 0 ; i < nListNum ; i++ )
	{
		pTVData = (CTreeViewData*)AfxTotalTreeList.GetNext( pos );
		if( pTVData->m_PointName == strName )
		{			
			//CsOut.Format( _T("�ǹ��̸� %s, ��ǥ%d %d"), pTVData->m_PointName, pTVData->m_Point.x, pTVData->m_Point.y );
			//AfxMessageBox(  CsOut );
			pMain->m_TopViewWnd.SetImagePosToClientPoint( pTVData->m_Point );

			if( pTVData->m_FileName == _T("") ) // �̹��� ������ �������� �ʾ��� ��� �׳� ����
				return ;
			if( pTVData->m_ImgPos.x == 0 )
				return ;

			TCHAR strTmp[MAX_PATH];			
			wsprintf( strTmp, _T("%s\\Panoramas\\%s"), AppDir, (TCHAR*)(LPCTSTR)pTVData->m_FileName );
			//pCharTmp = (TCHAR*)(LPCTSTR)pTVData->m_FileName; // �̹��� ���� �̸�
			pView->m_lfRatio = 1.0; // ���� �̹��� ũ��

			pView->m_bNowLoading = TRUE;
			pView->RedrawWindow();

			pView->LoadImage( strTmp ); // �̹��� �ε�
			pView->m_bNowLoading = FALSE;


			CPoint ImgPos; // �̹����� �߾��� Ŭ���̾�Ʈ�� �߾ӿ� ������ �̹��� ��ġ�� �����մϴ�.
			ImgPos = SetImagePosToClientPoint( pView->GetClientWidth(), pView->GetClientHeight(), pView->m_BufferdImg.GetWidth(), pView->m_BufferdImg.GetHeight(),  
				CPoint( pView->GetClientWidth() / 2 , pView->GetClientHeight() / 2 ), pTVData->m_ImgPos );
			pView->m_ImgPos = ImgPos; 
			
			// �̹��� ��� ��ġ
			pView->m_ImgPos.x = (long)( (double)pView->m_ImgPos.x * pView->m_lfRatio );
			pView->m_ImgPos.y = (long)( (double)pView->m_ImgPos.y * pView->m_lfRatio );
			pMain->m_SatelliteViewWnd.m_ViewerPt = pTVData->m_Point;
			pMain->m_SatelliteViewWnd.SetImagePosToClientPoint( pMain->m_SatelliteViewWnd.m_ViewerPt );	

			pos = AfxPanoFileList.GetHeadPosition();
			int num = AfxPanoFileList.GetCount();
			CPanoFileData* pData;

			for( int i = 0 ; i < num ; i++ )
			{
				pData = (CPanoFileData *)AfxPanoFileList.GetNext( pos );

				if( lstrcmp( pData->m_FileName, pTVData->m_FileName ) == 0 )
				{
					pMain->m_SatelliteViewWnd.m_nEast = pData->m_nSatelliteEast;
					pMain->m_TopViewWnd.m_nEast = pData->m_nEast;
					break;
				}
			}
			Afx_pVoidCurrentFile = pData;
			pView->m_LoadedFileName = pData->m_FileName;

			pView->CalculateDirection();

			pMain->m_SatelliteViewWnd.ShowWindow( SW_SHOW );
			pMain->m_TopViewWnd.ShowWindow( SW_HIDE );

			pView->Invalidate(); // �ٽñ׸���

			break;
		}
	}

}

void CCategoryTree::OnMouseMove(UINT nFlags, CPoint point)
{
	TVHITTESTINFO tvinfo;
	CTreeViewData* pData;
	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;

	tvinfo.pt = point;
	//ClientToScreen( &tvinfo.pt );
	//ScreenToClient( &tvinfo.pt );

	HTREEITEM hTree = 0;
	hTree = (HTREEITEM)SendMessage( TVM_HITTEST, 0, (LPARAM)&tvinfo );
	//::SendMessage( this->GetSafeHwnd(), TVM_HITTEST,  0, (LPARAM)&tvinfo );

	if( tvinfo.hItem )
	{			
		pData = (CTreeViewData*) GetItemData( tvinfo.hItem );

		if( lstrlen( pData->m_Detail ) > 0 )
			pMain->SetCaptionBarText( pData->m_Detail );
		
		//MyTooltip.ShowWindow( SW_SHOW );

		//AfxMessageBox( pData->m_PointName );
	}

	CTreeCtrl::OnMouseMove(nFlags, point);
}

void CCategoryTree::OnRButtonUp(UINT nFlags, CPoint point)
{
	

	//CTreeCtrl::OnRButtonUp(nFlags, point);
}

int CCategoryTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
