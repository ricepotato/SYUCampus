// PanoFileDeleteDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SYUCampus.h"
#include "PanoFileDeleteDlg.h"
#include "PanoFileData.h"
#include "MainFrm.h"


// CPanoFileDeleteDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPanoFileDeleteDlg, CDialog)

CPanoFileDeleteDlg::CPanoFileDeleteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPanoFileDeleteDlg::IDD, pParent)
{
	m_bDraw = TRUE;
}

CPanoFileDeleteDlg::~CPanoFileDeleteDlg()
{
}

void CPanoFileDeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PANOFILELIST, m_FileListBox);
}


BEGIN_MESSAGE_MAP(CPanoFileDeleteDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_LISTDELETE, &CPanoFileDeleteDlg::OnBnClickedBtnListdelete)
	ON_BN_CLICKED(IDC_BTN_FILEDELETE, &CPanoFileDeleteDlg::OnBnClickedBtnFiledelete)
	ON_BN_CLICKED(IDCANCEL, &CPanoFileDeleteDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPanoFileDeleteDlg �޽��� ó�����Դϴ�.

BOOL CPanoFileDeleteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_BufferedImg.Init( this );

	RefreshList();

	return TRUE;
}

BOOL CPanoFileDeleteDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	CPanoFileData* pData;
	CString strTmp;
	CRect ImageOutRt;
	CWnd* pWnd;
	double ratioWnd;
	double ratioImg;

	switch( LOWORD(wParam) )
	{
	case IDC_PANOFILELIST:
		switch( HIWORD(wParam) )
		{
		case LBN_SELCHANGE:
			m_CurSel = m_FileListBox.GetCurSel();
			pData = (CPanoFileData*)m_FileListBox.GetItemData( m_CurSel );

			strTmp.Format( _T("%s\\panoramas\\%s"), AppDir, pData->m_FileName );

			//AfxMessageBox( strTmp );

			if( m_BufferedImg.LoadFile( (TCHAR *)(LPCTSTR )strTmp ) )
			{
				pWnd = GetDlgItem( IDC_STATIC );
				::GetWindowRect( pWnd->m_hWnd, &ImageOutRt );
				ImageOutRt.top += 20;			
				ImageOutRt.left += 10;
				ImageOutRt.right -= 10;
				ImageOutRt.bottom -= 10;

				ratioWnd = (double)ImageOutRt.Width() / (double)ImageOutRt.Height();
				ratioImg = (double)m_BufferedImg.m_ImgSize.cx / (double)m_BufferedImg.m_ImgSize.cy;


				m_ImgPt.x = ImageOutRt.left;
				m_ImgPt.y = ImageOutRt.top;
				this->ScreenToClient( &m_ImgPt );

				if( ratioImg > ratioWnd )
				{
					if( m_BufferedImg.SetWidth( ImageOutRt.Width() ) )
					{
						m_ImgPt.y += (ImageOutRt.Height() - m_BufferedImg.GetHeight() ) / 2;
						m_bDraw = TRUE;
					}
					else
						AfxMessageBox( _T("���� �ε忡 �����߽��ϴ�!") );
				}
				else
				{				
					if( m_BufferedImg.SetHeight( ImageOutRt.Height() ) )
					{
						m_ImgPt.x += ( ImageOutRt.Width() - m_BufferedImg.GetWidth() ) / 2;			
						m_bDraw = TRUE;
					}
					else
						AfxMessageBox( _T("���� �ε忡 �����߽��ϴ�!") );
				}
				Invalidate();
			}
			
			break;
		}
		break;
	}

	return CDialog::OnCommand(wParam, lParam);
}

void CPanoFileDeleteDlg::OnPaint()
{
	CPaintDC dc(this);

	Graphics G( dc );

	if( m_BufferedImg.m_pCachedbmp && m_bDraw )
		G.DrawCachedBitmap( m_BufferedImg.m_pCachedbmp, m_ImgPt.x, m_ImgPt.y );
}

void CPanoFileDeleteDlg::OnBnClickedBtnListdelete()
{
	POSITION pos;
	int num;
	CPanoFileData* pData;

	pData = (CPanoFileData*)m_FileListBox.GetItemData( m_CurSel );

	num = AfxPanoFileList.GetCount();
	pos = AfxPanoFileList.GetHeadPosition();

	for( int i = 0 ; i < m_CurSel ; i++ )
	{
		AfxPanoFileList.GetNext( pos );
	}
	AfxPanoFileList.RemoveAt( pos );

	m_FileListBox.DeleteString( m_CurSel );

	CMainFrame* pMain;	
	pMain = (CMainFrame*)Afx_pVoidMain;

	pMain->SetCaptionBarText( _T("��Ͽ����� ������ ��� �ĳ�� ���� �߰��� �Ǵ� ���ø����̼� ����۽� ���������� ������ �ٽ� �߰��˴ϴ�. ������ �����Ϸ��� ������ �����Ͻʽÿ�.") );
	m_bDraw = FALSE;
	Invalidate();

	delete pData;
}
void CPanoFileDeleteDlg::OnBnClickedBtnFiledelete()
{
	CString DeleteFileFullPath;
	CString strTmp;
	CString strMeg;

	CPanoFileData* pData;

	pData = (CPanoFileData*)m_FileListBox.GetItemData( m_CurSel );

	strTmp = AppDir;
	DeleteFileFullPath.Format( _T("%s\\Panoramas\\%s"), strTmp, pData->m_FileName );

	strMeg.Format( _T("[ %s ] ������ ������ �����Ͻðڽ��ϱ�??"), pData->m_FileName );

	if( AfxMessageBox( strMeg, MB_YESNO | MB_ICONQUESTION ) ==  IDYES )
	{		
		m_BufferedImg.UpLoadFile();

		if( !DeleteFile( DeleteFileFullPath ) )
		{
			AfxMessageBox( _T("���� ������ �����Ͽ����ϴ�!") );
		}
		else
		{
			POSITION pos;
			int num;
			CPanoFileData* pData;

			pData = (CPanoFileData*)m_FileListBox.GetItemData( m_CurSel );

			num = AfxPanoFileList.GetCount();
			pos = AfxPanoFileList.GetHeadPosition();

			for( int i = 0 ; i < m_CurSel ; i++ )
			{
				AfxPanoFileList.GetNext( pos );
			}
			AfxPanoFileList.RemoveAt( pos );

			m_FileListBox.DeleteString( m_CurSel );

			delete pData;

			AfxMessageBox( _T("������ ���� �Ǿ����ϴ�.") );
			m_bDraw = FALSE;
			theApp.SavePanoFileData();
			Invalidate();
		}
	}

}

void CPanoFileDeleteDlg::RefreshList( void )
{
	POSITION pos;
	int num;
	int CtrlNum;
	CPanoFileData* pData;

	num = AfxPanoFileList.GetCount();
	pos = AfxPanoFileList.GetHeadPosition();

	CtrlNum = m_FileListBox.GetCount();


	for( int i = 0 ; i < CtrlNum ; i++ )
	{
		m_FileListBox.DeleteString( 0 );
	}

	for( int i = 0 ; i < num ; i++ )
	{
		pData = (CPanoFileData *)AfxPanoFileList.GetNext( pos );
		m_FileListBox.AddString( pData->m_FileName );
		m_FileListBox.SetItemData( i, (DWORD_PTR)pData );
	}
}
void CPanoFileDeleteDlg::OnBnClickedCancel()
{
	theApp.SavePanoFileData();
	OnCancel();
}
