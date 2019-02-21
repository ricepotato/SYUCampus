// TreeViewEditorDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SYUCampus.h"
#include "TreeViewEditorDlg.h"
#include "TreeViewData.h"
#include "MainFrm.h"
#include "SYUCampusView.h"


// CTreeViewEditorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTreeViewEditorDlg, CDialog)

CTreeViewEditorDlg::CTreeViewEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeViewEditorDlg::IDD, pParent)
	, m_nPointX(0)
	, m_nPointY(0)
	, m_nPosX(0)
	, m_PosY(0)
	, m_nIndex(0)
	, m_strPointName(_T(""))
	, m_strFileName(_T(""))
	, m_strDetail(_T(""))
{

}

CTreeViewEditorDlg::~CTreeViewEditorDlg()
{
}

void CTreeViewEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TreeEditorListCtrl);
	DDX_Text(pDX, IDC_EDIT_POINTX, m_nPointX);
	DDX_Text(pDX, IDC_EDIT_POINTY, m_nPointY);
	DDX_Text(pDX, IDC_EDIT_POSX, m_nPosX);
	DDX_Text(pDX, IDC_EDIT_POSY, m_PosY);
	DDX_Text(pDX, IDC_EDIT_INDEX, m_nIndex);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strPointName);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_strFileName);
	DDX_Control(pDX, IDC_BTN_INSERT, m_BtnInsert);
	DDX_Control(pDX, IDC_BTN_MODIFY, m_BtnModify);
	DDX_Control(pDX, IDC_BTN_DELETE, m_BtnDelete);
	DDX_Control(pDX, IDC_BTN_UP, m_BtnUp);
	DDX_Control(pDX, IDC_BTN_DOWN, m_BtnDown);
	DDX_Control(pDX, IDC_BTN_SAVE, m_BtnSave);
	DDX_Text(pDX, IDC_EDIT_DETAIL, m_strDetail);
	DDX_Control(pDX, IDC_COMBOBOXEX1, m_ImgComboBox);
	DDX_Control(pDX, IDC_COMBO_SELECTEDTREE, m_Combo_SelectedTree);
	DDX_Control(pDX, IDC_COMBO_PARENTINDEX, m_Combo_ParentIndex);
	DDX_Control(pDX, IDC_EDIT_NAME, m_PointNameCtrl);
	DDX_Control(pDX, IDC_BTN_LOCSAVE, m_BtnLocSave);
	DDX_Control(pDX, IDC_EDIT_DETAIL, m_EditDetailCtrl);
}


BEGIN_MESSAGE_MAP(CTreeViewEditorDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_INSERT, &CTreeViewEditorDlg::OnBnClickedBtnInsert)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CTreeViewEditorDlg::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CTreeViewEditorDlg::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_UP, &CTreeViewEditorDlg::OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DOWN, &CTreeViewEditorDlg::OnBnClickedBtnDown)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CTreeViewEditorDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CTreeViewEditorDlg::OnBnClickedBtnCancel)
	ON_CBN_SELCHANGE(IDC_COMBOBOXEX1, &CTreeViewEditorDlg::OnCbnSelchangeComboboxex1)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECTEDTREE, &CTreeViewEditorDlg::OnCbnSelchangeComboSelectedtree)
	ON_BN_CLICKED(IDOK, &CTreeViewEditorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_LOCSAVE, &CTreeViewEditorDlg::OnBnClickedBtnLocsave)
END_MESSAGE_MAP()


// CTreeViewEditorDlg 메시지 처리기입니다.

BOOL CTreeViewEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	LV_COLUMN col;
	col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH ;

	col.pszText = _T("이름");
	col.fmt = LVCFMT_LEFT;
	col.cx = 150;
	m_TreeEditorListCtrl.InsertColumn( 0, &col );

	col.pszText = _T("탑 뷰 상의 위치");
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	m_TreeEditorListCtrl.InsertColumn( 1, &col );

	col.pszText = _T("파일 이름");
	col.fmt = LVCFMT_LEFT;
	col.cx = 100;
	m_TreeEditorListCtrl.InsertColumn( 2, &col );

	col.pszText = _T("이미지 위치");
	col.fmt = LVCFMT_LEFT;
	col.cx = 80;
	m_TreeEditorListCtrl.InsertColumn( 3, &col );

	col.pszText = _T("인덱스");
	col.fmt = LVCFMT_LEFT;
	col.cx = 60;
	m_TreeEditorListCtrl.InsertColumn( 4, &col );

	col.pszText = _T("부모 트리");
	col.fmt = LVCFMT_LEFT;
	col.cx = 80;
	m_TreeEditorListCtrl.InsertColumn( 5, &col );

	col.pszText = _T("간단 설명");
	col.fmt = LVCFMT_LEFT;
	col.cx = 400;
	m_TreeEditorListCtrl.InsertColumn( 6, &col );	

	m_TreeEditorListCtrl.SetImageList( &Afx_CategoryImages, LVSIL_SMALL );

	m_BtnUp.EnableWindow( FALSE );
	m_BtnDown.EnableWindow( FALSE );
	m_BtnDelete.EnableWindow( FALSE );
	m_BtnLocSave.EnableWindow( FALSE );

	m_ImgComboBox.SetImageList( &Afx_CategoryImages );

	CString strTmp;	
	COMBOBOXEXITEM cbi;
	::ZeroMemory( &cbi, sizeof( cbi ) );

	cbi.mask = CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_TEXT;

	for( int i = 0 ; i < NUM_OF_CATEGORYIMGLIST ; i++ )
	{
		cbi.iItem = i;
		cbi.iImage = i;
		cbi.iSelectedImage = i;
		cbi.pszText = ImgListName[i];

		m_ImgComboBox.InsertItem( &cbi );
	}	

	m_Combo_ParentIndex.AddString( _T("상위 트리") );
	m_Combo_ParentIndex.SetCurSel( 0 );

	int index = 1;

	m_CurrentList.RemoveAll();
	FileLoad( 0 );
	POSITION pos = m_CurrentList.GetHeadPosition();
	int num = m_CurrentList.GetCount();
	CTreeViewData* pData;

	// 상위 트리를 UpperTree 리스트에 복사합니다.
	for( int i = 0 ; i < num ; i++ )
	{
		pData = (CTreeViewData*)m_CurrentList.GetNext( pos );
		m_Combo_ParentIndex.AddString( pData->m_PointName );
		m_Combo_ParentIndex.SetItemData( index++, (DWORD_PTR)pData );
		m_UpperTree.AddTail( pData );
	}	

	// 주요 건물을 상위트리에 복사합니다.
	m_CurrentList.RemoveAll();
	FileLoad( 1 );
	pos = m_CurrentList.GetHeadPosition();
	num = m_CurrentList.GetCount();
	for( int i = 0 ; i < num ; i++ )
	{
		pData = (CTreeViewData*)m_CurrentList.GetNext( pos );
		m_Combo_ParentIndex.AddString( pData->m_PointName );
		m_Combo_ParentIndex.SetItemData( index++, (DWORD_PTR)pData );
		m_UpperTree.AddTail( pData );
	}	

	m_CurrentList.RemoveAll();

	// 차례 중요!
	m_Combo_SelectedTree.AddString( _T("상위 트리") );
	m_Combo_SelectedTree.AddString( _T("주요 건물") );
	m_Combo_SelectedTree.AddString( _T("주요 장소") );
	m_Combo_SelectedTree.AddString( _T("대학 기구") );
	m_Combo_SelectedTree.AddString( _T("행정 본부") );
	m_Combo_SelectedTree.AddString( _T("학교 기관") );
	m_Combo_SelectedTree.AddString( _T("학생 자치") );
	m_Combo_SelectedTree.AddString( _T("대학 언론") );
	m_Combo_SelectedTree.AddString( _T("학과") );
	m_Combo_SelectedTree.AddString( _T("연구소") );
	m_Combo_SelectedTree.AddString( _T("복지 시설") );	
	m_Combo_SelectedTree.AddString( _T("식 당") );
	m_Combo_SelectedTree.AddString( _T("학교 시설") );

	m_Combo_SelectedTree.SetCurSel( 0 );

	m_nCurComboSel = m_Combo_SelectedTree.GetCurSel();

	FileLoad( m_nCurComboSel );

	RefreshList();	
	return TRUE;
}

void CTreeViewEditorDlg::OnBnClickedBtnInsert()
{
	UpdateData( TRUE );
	int ParentCursel;

	ParentCursel = m_Combo_ParentIndex.GetCurSel();
	if( m_strPointName == _T("") )
	{
		AfxMessageBox( _T("이름을 입력하지 않았습니다!") );
		return ;
	}

	CTreeViewData* pTemp;
	CTreeViewData* pData;
	pData = new CTreeViewData;

	// 컨트롤에 입력된 대로 값을 지정한다.
	lstrcpy( pData->m_PointName, m_strPointName );
	pData->m_Point.x = m_nPointX;
	pData->m_Point.y = m_nPointY;
	lstrcpy( pData->m_FileName, m_strFileName );
	pData->m_ImgPos.x = m_nPosX;
	pData->m_ImgPos.y = m_PosY;
	lstrcpy( pData->m_Detail, (TCHAR*)(LPCTSTR)m_strDetail );
	
	// 랜덤값을 저장한다. 랜덤값은 0 ~ (m_nCurComboSel + 1) * 1000 - 1 범위를 가지며 같은 값을 갖지 않는다.
	pData->m_nIndex = GetRandIndex( m_nCurComboSel );

	// 상위 트리 콤보가 선택되어있을 경우 그냥 0을 지정한다.
	if( ParentCursel == 0 )
	{
		pData->m_nParentIndex = 0;
	}
	else// 다른경우 그 트리의 인덱스를 넣는다.
	{
		pTemp = (CTreeViewData*)m_Combo_ParentIndex.GetItemData( ParentCursel );
		if( pTemp )
			pData->m_nParentIndex = pTemp->m_nIndex;
	}

	pData->m_nImgListIndex = m_ImgComboBox.GetCurSel();
	lstrcpy( pData->m_Detail, m_strDetail );

	m_CurrentList.AddTail( pData );
	if( pData->m_nParentIndex == 0 )
	{
		AfxMessageBox( _T("이 아이템은 부모를 지정하지 않았으므로 최상위 트리가 될 것입니다.") );
	}

	m_strPointName = _T("");
	m_nPointX = 0;
	m_nPointY = 0;
	m_strFileName = _T("");
	m_nPosX = 0;
	m_PosY = 0;
	m_nIndex = 0;
	UpdateData( FALSE );

	RefreshList();

	m_PointNameCtrl.SetFocus();
}
BOOL CTreeViewEditorDlg::FileSave( void )
{
	CFile File;
	POSITION pos;
	CTreeViewData* pData;
	CString strTmp;

	strTmp.Format( _T("%s\\Data\\TreeData_%d.dat"), AppDir, m_nCurComboSel );

	if( File.Open( strTmp, CFile::modeCreate | CFile::modeReadWrite ) )
	{
		pos = m_CurrentList.GetHeadPosition();
		int num = m_CurrentList.GetCount();

		File.Write( &num, sizeof( int ) );

		pos = m_CurrentList.GetHeadPosition();
		for( int i = 0 ; i < num ; i++ )
		{
			pData = ( CTreeViewData* )m_CurrentList.GetNext( pos );
			File.Write( pData->m_PointName, sizeof( TCHAR ) * 50 );
			File.Write( pData->m_FileName, sizeof( TCHAR ) * MAX_PATH );
			File.Write( &pData->m_Point, sizeof( CPoint ) );
			File.Write( &pData->m_ImgPos, sizeof( CPoint ) );
			File.Write( &pData->m_nIndex, sizeof( int ) );
			File.Write( &pData->m_nParentIndex, sizeof( int ) );
			File.Write( &pData->m_nImgListIndex, sizeof( int ) );
			File.Write( pData->m_Detail, sizeof( TCHAR ) * 512 );
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


BOOL CTreeViewEditorDlg::FileLoad( int nCursel )
{
	CFile File;
	CTreeViewData* pData;
	CString strTmp;

	strTmp.Format( _T("%s\\Data\\TreeData_%d.dat"), AppDir, nCursel );

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

			m_CurrentList.AddTail( pData );
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CTreeViewEditorDlg::RefreshList( void )
{
	POSITION pos;
	CTreeViewData* pData;

	pos = m_CurrentList.GetHeadPosition();

	LV_ITEM it;
	it.mask = LVIF_TEXT | LVIF_IMAGE;
	TCHAR strTmp[256];
	int num;
	m_TreeEditorListCtrl.DeleteAllItems();	
	num = m_CurrentList.GetCount();
	int ListNum = 0;

	for( int i = 0 ; i < num ; i++ )
	{		
		pData = (CTreeViewData*)m_CurrentList.GetNext( pos );

		it.iItem = ListNum;
		it.iImage = pData->m_nImgListIndex;
		it.iSubItem = 0;
		it.pszText = pData->m_PointName;
		m_TreeEditorListCtrl.InsertItem( &it );
		
		m_TreeEditorListCtrl.SetItemData( ListNum, (DWORD_PTR)pData );
		ListNum++;

		it.iSubItem = 1;
		wsprintf( strTmp, _T("%d %d"), pData->m_Point.x, pData->m_Point.y );
		it.pszText = strTmp;
		m_TreeEditorListCtrl.SetItem( &it );

		it.iSubItem = 2;
		it.pszText = pData->m_FileName;
		m_TreeEditorListCtrl.SetItem( &it );

		it.iSubItem = 3;
		wsprintf( strTmp, _T("%d %d"), pData->m_ImgPos.x, pData->m_ImgPos.y );
		it.pszText = strTmp;
		m_TreeEditorListCtrl.SetItem( &it );

		it.iSubItem = 4;
		wsprintf( strTmp, _T("%d"), pData->m_nIndex );
		it.pszText = strTmp;
		m_TreeEditorListCtrl.SetItem( &it );

		it.iSubItem = 5;
		GetParentName( pData->m_nParentIndex, strTmp );
		it.pszText = strTmp;
		m_TreeEditorListCtrl.SetItem( &it );

		it.iSubItem = 6;
		it.pszText = pData->m_Detail;

		m_TreeEditorListCtrl.SetItem( &it );		
	}
}
void CTreeViewEditorDlg::OnDestroy()
{
	CDialog::OnDestroy();

	CleanUpList( m_CurrentList );
	CleanUpList( m_UpperTree );
}

BOOL CTreeViewEditorDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	LPNMHDR hdr;
	LPNMLISTVIEW nlv;

	hdr = (LPNMHDR)lParam;
	nlv = (LPNMLISTVIEW)lParam;

	if( hdr->hwndFrom == m_TreeEditorListCtrl.GetSafeHwnd() )
	{
		switch( hdr->code )
		{
		case LVN_ITEMCHANGED:
			if( nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED ))
			{
				m_nCurListSel = nlv->iItem;
				int num;
				num = m_CurrentList.GetCount();

				m_BtnUp.EnableWindow( TRUE );
				m_BtnDown.EnableWindow( TRUE );
				m_BtnDelete.EnableWindow( TRUE );
				m_BtnModify.EnableWindow( TRUE );
				CSYUCampusView* pView;
				pView = (CSYUCampusView*)Afx_pVoidView;
				if( pView->m_bLoaded )
					m_BtnLocSave.EnableWindow( TRUE );

				if( m_nCurListSel == 0 )
					m_BtnUp.EnableWindow( FALSE );
				if( m_nCurListSel == num - 1 )
					m_BtnDown.EnableWindow( FALSE );				

				CTreeViewData* pData;
				CTreeViewData* pTemp = NULL;

				pData = (CTreeViewData*)m_TreeEditorListCtrl.GetItemData( m_nCurListSel );
/*
				POSITION pos;
				pos = AfxNewTreeList.GetHeadPosition();
				for( int i = 0 ; i < nlv->iItem + 1 ; i++ )
				{
					pData = (CTreeViewData*)AfxNewTreeList.GetNext( pos );					
				}
*/
				m_strPointName = pData->m_PointName;
				m_nPointX = pData->m_Point.x;
				m_nPointY = pData->m_Point.y;
				m_strFileName = pData->m_FileName;
				m_nPosX = pData->m_ImgPos.x;
				m_PosY = pData->m_ImgPos.y;
				m_nIndex = pData->m_nIndex;
				m_strDetail = pData->m_Detail;
				
				//m_nParentIndex = pData->m_nParentIndex;
				if( pData->m_nParentIndex == 0 )
				{
					m_Combo_ParentIndex.SetCurSel( 0 );
				}
				else
				{
					for( int i = 0 ; i < m_Combo_ParentIndex.GetCount() ; i++ )
					{
						pTemp = (CTreeViewData*)m_Combo_ParentIndex.GetItemData( i );
						if( pTemp )
						{
							if( pTemp->m_nIndex == pData->m_nParentIndex )
								m_Combo_ParentIndex.SetCurSel( i );
						}
					}
				}

				m_ImgComboBox.SetCurSel( pData->m_nImgListIndex );
				m_strDetail = pData->m_Detail;

				UpdateData( FALSE );
			}
			else
			{
				m_BtnUp.EnableWindow( FALSE );
				m_BtnDown.EnableWindow( FALSE );
				m_BtnDelete.EnableWindow( FALSE );
				m_BtnModify.EnableWindow( FALSE );

				m_strPointName = _T("");
				m_nPointX = 0;
				m_nPointY = 0;
				m_strFileName = _T("");
				m_nPosX = 0;
				m_PosY = 0;
				m_nIndex = 0;
				UpdateData( FALSE );
			}
			break;
		}
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CTreeViewEditorDlg::OnBnClickedBtnModify()
{
	UpdateData( TRUE );

	int ParentCursel;
	CTreeViewData* pTemp = NULL;

	ParentCursel = m_Combo_ParentIndex.GetCurSel();
	CTreeViewData* pData;

	pData = (CTreeViewData*)m_TreeEditorListCtrl.GetItemData( m_nCurListSel );

	lstrcpy( pData->m_PointName, m_strPointName );
	pData->m_Point.x = m_nPointX;
	pData->m_Point.y = m_nPointY;
	lstrcpy( pData->m_FileName, m_strFileName );
	pData->m_ImgPos.x = m_nPosX;
	pData->m_ImgPos.y = m_PosY;
	pData->m_nIndex = m_nIndex;
	lstrcpy( pData->m_Detail, (TCHAR*)(LPCTSTR)m_strDetail );

	if( ParentCursel == 0 )
	{
		pData->m_nParentIndex = 0;
	}
	else
	{
		pTemp = (CTreeViewData*)m_Combo_ParentIndex.GetItemData( ParentCursel );
		pData->m_nParentIndex = pTemp->m_nIndex;
	}

	pData->m_nImgListIndex = m_ImgComboBox.GetCurSel();

	RefreshList();
}

void CTreeViewEditorDlg::OnBnClickedBtnDelete()
{
	m_nCurComboSel;

	POSITION pos;
	pos = m_CurrentList.GetHeadPosition();	
	int num = m_CurrentList.GetCount();
	CTreeViewData* pData;
	CTreeViewData* pTemp;
	int i;

	pData = (CTreeViewData*)m_TreeEditorListCtrl.GetItemData( m_nCurListSel );
	for( i = 0 ; i < num; i++ )
	{
		pTemp = (CTreeViewData*)m_CurrentList.GetNext( pos );					
		if( pTemp == pData )
			break;
	}
	pos = m_CurrentList.GetHeadPosition();	
	for( int j = 0 ; j < i; j++ )
	{
		m_CurrentList.GetNext( pos );	
	}
	delete pData;
	m_CurrentList.RemoveAt( pos );

	//RefreshList();
	m_TreeEditorListCtrl.DeleteItem( m_nCurListSel );
}

void CTreeViewEditorDlg::OnBnClickedBtnUp()
{
	if( m_nCurListSel <= 0 )
	{		
		return ;
	}

	CTreeViewData* pDataCur;
	CTreeViewData* pDataPrev;
	CTreeViewData* pTemp;
	CTreeViewData Temp;	

	/*
	선택된 항목과 그 위 항목의 값을 서로 복사하여 바꾼다.
	*/
	pDataCur = (CTreeViewData*)m_TreeEditorListCtrl.GetItemData( m_nCurListSel );
	pDataPrev = (CTreeViewData*)m_TreeEditorListCtrl.GetItemData( m_nCurListSel - 1 );
	
	memcpy( &Temp, pDataCur, sizeof( CTreeViewData ) );
	memcpy( pDataCur, pDataPrev, sizeof( CTreeViewData ) );
	memcpy( pDataPrev, &Temp, sizeof( CTreeViewData ) );
	m_nCurListSel--;

	// 가장 위 항목의 포인터와 현재 항목의 포인터를 얻어 서로 같은지 비교하여 
	// 같으면 버튼을 비활성 시킨다. 아니면 버튼을 활성시킨다.

	RefreshList();
	m_TreeEditorListCtrl.EnsureVisible( m_nCurListSel, TRUE );

	pDataCur = (CTreeViewData*)m_TreeEditorListCtrl.GetItemData( m_nCurListSel );
	pTemp = (CTreeViewData*)m_TreeEditorListCtrl.GetItemData( 0 );

	if( pDataCur == pTemp )
		m_BtnUp.EnableWindow( FALSE );
	else
		m_BtnUp.EnableWindow( TRUE );	
}

void CTreeViewEditorDlg::OnBnClickedBtnDown()
{	
	int num = m_TreeEditorListCtrl.GetItemCount();
	if( m_nCurListSel >= num - 1 )
		return ;

	CTreeViewData* pDataCur;
	CTreeViewData* pDataNext;
	CTreeViewData* pTemp;
	CTreeViewData Temp;	

	pDataCur = (CTreeViewData*)m_TreeEditorListCtrl.GetItemData( m_nCurListSel );
	pDataNext = (CTreeViewData*)m_TreeEditorListCtrl.GetItemData( m_nCurListSel + 1 );

	memcpy( &Temp, pDataCur, sizeof( CTreeViewData ) );
	memcpy( pDataCur, pDataNext, sizeof( CTreeViewData ) );
	memcpy( pDataNext, &Temp, sizeof( CTreeViewData ) );

	m_nCurListSel++;

	RefreshList();
	m_TreeEditorListCtrl.EnsureVisible( m_nCurListSel, TRUE );

	pDataCur = (CTreeViewData*)m_TreeEditorListCtrl.GetItemData( m_nCurListSel );
	pTemp = (CTreeViewData*)m_TreeEditorListCtrl.GetItemData( num - 1 );

	if( pDataCur == pTemp )
		m_BtnDown.EnableWindow( FALSE );
	else
		m_BtnDown.EnableWindow( TRUE );	
}

void CTreeViewEditorDlg::OnBnClickedBtnSave()
{
	FileSave();
	RefreshList();
}

BOOL CTreeViewEditorDlg::FindParent( int nParentIndex )
{
	POSITION pos;
	pos = m_CurrentList.GetHeadPosition();
	int num = m_CurrentList.GetCount();
	CTreeViewData* pData;

	for( int i = 0 ; i < num ; i++ )
	{
		pData = (CTreeViewData*)m_CurrentList.GetNext( pos );
		if( pData->m_nIndex == nParentIndex )
			return TRUE;
	}
	return FALSE;
}
void CTreeViewEditorDlg::OnBnClickedBtnCancel()
{
	EndDialog( IDCANCEL );
}

void CTreeViewEditorDlg::OnBnClickedBtnSetparnet()
{
}

void CTreeViewEditorDlg::OnCbnSelchangeComboboxex1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CTreeViewEditorDlg::GetParentName( int nParnetIndex, TCHAR* ParentName )
{
	if( ParentName == NULL )
		return ;
	if( nParnetIndex == 0 )
	{
		lstrcpy( ParentName, _T("상위 트리") );
		return ;
	}	

	POSITION pos;
	CTreeViewData* pData;
	pos = m_UpperTree.GetHeadPosition();
	int num = m_UpperTree.GetCount();

	for( int i = 0 ; i < num; i++ )
	{
		pData = (CTreeViewData*)m_UpperTree.GetNext( pos );
		if( nParnetIndex == pData->m_nIndex )
		{
			lstrcpy( ParentName, pData->m_PointName );
			return ;
		}
	}
	lstrcpy( ParentName, _T("부모 없음") );
}

int CTreeViewEditorDlg::GetRandIndex( int SelectedSel )
{
	int RandomIndex;
	BOOL bExist = FALSE;
	POSITION pos;
	CTreeViewData* pData;
	int num;
	int i;

	num = m_CurrentList.GetCount();

	while( 1 )
	{
		RandomIndex = rand() % 1000 + SelectedSel * 1000;
		bExist = FALSE;		
		
		pos = m_CurrentList.GetHeadPosition();	

		if( num == 0 )
			return RandomIndex;

		for( i = 0 ; i < num; i++ )
		{
			pData = (CTreeViewData*)m_CurrentList.GetNext( pos );
			if( pData->m_nIndex == RandomIndex )
			{
				bExist = TRUE;
				break;
			}
		}

		if( bExist == FALSE )
			return RandomIndex;
	}
	return 0;
}
void CTreeViewEditorDlg::OnCbnSelchangeComboSelectedtree()
{

	FileSave();
	m_nCurComboSel = m_Combo_SelectedTree.GetCurSel();
	if( m_nCurComboSel < 3 )
		m_Combo_ParentIndex.SetCurSel( m_nCurComboSel );

	switch( m_nCurComboSel )
	{
	case 1:
		m_ImgComboBox.SetCurSel( 5 );
		break;
	case 2:
		m_ImgComboBox.SetCurSel( 11 );
		break;
	case 8:
		m_ImgComboBox.SetCurSel( 8 );
		break;
	case 9:
		m_ImgComboBox.SetCurSel( 4 );
		break;

	}
	CleanUpList( m_CurrentList );
	FileLoad( m_nCurComboSel );
	RefreshList();
}

//BOOL CTreeViewEditorDlg::PreTranslateMessage(MSG* pMsg)
//{
//	
//	return CDialog::PreTranslateMessage(pMsg);
//}

void CTreeViewEditorDlg::OnBnClickedOk()
{
	FileSave();
	OnOK();
}

void CTreeViewEditorDlg::OnBnClickedBtnLocsave()
{
	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;
	CSYUCampusView* pView;
	pView = (CSYUCampusView*)Afx_pVoidView;

	CPoint PtOnImg;
	CPoint ImgPos;

	// 이미지의 중앙 좌표를 구해냅니다.
	// 이미지의 중앙 좌표가 저장되고
	// 로드될때 이미지의 중앙 좌표에 따라 이미지위치가 결정되어야 함.
	// 해상도가 다른 환경에서 실행될때 항상 이미지의 중앙이 같은 위치가 되도록 해야함.
	PtOnImg = GetImagePoint( pView->m_ImgPos, pView->m_ClientRect, CPoint( pView->GetClientWidth() / 2 , pView->GetClientHeight() / 2 ) );

	m_nPointX = pMain->m_SatelliteViewWnd.m_ViewerPt.x;
	m_nPointY = pMain->m_SatelliteViewWnd.m_ViewerPt.y;
	m_strFileName = pView->m_LoadedFileName;

	m_nPosX = PtOnImg.x;
	m_PosY = PtOnImg.y;	

	UpdateData( FALSE );
}

BOOL CTreeViewEditorDlg::PreTranslateMessage(MSG* pMsg)
{
	if( pMsg->hwnd == m_PointNameCtrl.m_hWnd && pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_INSERT )
	{
		OnBnClickedBtnInsert();
	}

	if( pMsg->hwnd == m_EditDetailCtrl.m_hWnd && pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_HOME )
	{
		OnBnClickedBtnModify();
	}
	return CDialog::PreTranslateMessage(pMsg);
}
