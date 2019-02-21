// ViewFilePointDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SYUCampus.h"
#include "ViewFilePointDlg.h"
#include "ViewFileLinkData.h"


// CViewFilePointDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CViewFilePointDlg, CDialog)

CViewFilePointDlg::CViewFilePointDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewFilePointDlg::IDD, pParent)
{

}

CViewFilePointDlg::~CViewFilePointDlg()
{
}

void CViewFilePointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CViewFilePointDlg, CDialog)
	ON_BN_CLICKED(ID_BTN_DELETE, &CViewFilePointDlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// CViewFilePointDlg 메시지 처리기입니다.

BOOL CViewFilePointDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	LV_COLUMN col;
	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH ;

	col.pszText = _T("파일 이름");
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	m_ListCtrl.InsertColumn( 0, &col );

	col.pszText = _T("새 파일 이름");
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	m_ListCtrl.InsertColumn( 1, &col );
	

	col.pszText = _T("포인트");
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	m_ListCtrl.InsertColumn( 2, &col );

	RefreshList();

	return TRUE;
}
void CViewFilePointDlg::RefreshList( void )
{
	POSITION pos;
	CViewFileLinkData* pData;

	pos = AfxViewFileLinkList.GetHeadPosition();

	LV_ITEM it;
	it.mask = LVIF_TEXT;
	TCHAR strTmp[256];
	int num;
	m_ListCtrl.DeleteAllItems();	
	num = AfxViewFileLinkList.GetCount();
	for( int i = 0 ; i < num ; i++ )
	{
		pData = (CViewFileLinkData*)AfxViewFileLinkList.GetNext( pos );

		it.iItem = i;
		it.iSubItem = 0;
		it.pszText = pData->m_CurFileName;
		m_ListCtrl.InsertItem( &it );

		it.iSubItem = 1;
		it.pszText = pData->m_NewFileName;
		m_ListCtrl.SetItem( &it );

		it.iSubItem = 2;
		wsprintf( strTmp, _T("%d, %d"), pData->m_NewPoint.x, pData->m_NewPoint.y );
		it.pszText = strTmp;
		m_ListCtrl.SetItem( &it );

		

	}
}
BOOL CViewFilePointDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	LPNMHDR hdr;
	LPNMLISTVIEW nlv;

	hdr = (LPNMHDR)lParam;
	nlv = (LPNMLISTVIEW)lParam;

	if( hdr->hwndFrom == m_ListCtrl.GetSafeHwnd() )
	{
		switch( hdr->code )
		{
		case LVN_ITEMCHANGED:
			if( nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED ))
			{
				m_nCurSel = nlv->iItem;
			}
			break;
		}
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CViewFilePointDlg::OnBnClickedBtnDelete()
{
	
	POSITION pos;
	pos = AfxViewFileLinkList.GetHeadPosition();
	CViewFileLinkData* pData;

	for( int i = 0 ; i < m_nCurSel + 1; i++ )
	{
		pData = (CViewFileLinkData*)AfxViewFileLinkList.GetNext( pos );					
	}
	delete pData;

	pos = AfxViewFileLinkList.GetHeadPosition();
	for( int i = 0 ; i < m_nCurSel ; i++ )
	{
		AfxViewFileLinkList.GetNext( pos );					
	}
	AfxViewFileLinkList.RemoveAt( pos );

	RefreshList();
}

void CViewFilePointDlg::OnOK()
{
	SaveFileLinkData();

	CDialog::OnOK();
}


BOOL CViewFilePointDlg::SaveFileLinkData( void )
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

void CViewFilePointDlg::OnCancel()
{

	CDialog::OnCancel();
}
