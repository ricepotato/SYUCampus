// PanoFileAddDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SYUCampus.h"
#include "PanoFileAddDlg.h"
#include "MainFrm.h"


// CPanoFileAddDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPanoFileAddDlg, CDialog)

CPanoFileAddDlg::CPanoFileAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPanoFileAddDlg::IDD, pParent)
{

}

CPanoFileAddDlg::~CPanoFileAddDlg()
{
}

void CPanoFileAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPanoFileAddDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_FINDFILE, &CPanoFileAddDlg::OnBnClickedBtnFindfile)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_FILEADD, &CPanoFileAddDlg::OnBnClickedBtnFileadd)
END_MESSAGE_MAP()


// CPanoFileAddDlg �޽��� ó�����Դϴ�.

void CPanoFileAddDlg::OnBnClickedBtnFindfile()
{
	CString strTmp;
	CRect ImageOutRt;
	CWnd* pWnd;
	double ratioWnd;
	double ratioImg;

	// JPG ���� ���� ���̾�α�
	CFileDialog Dlg( TRUE, _T("jpg"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("jpg ����(*.jpg) | *.jpg||"), this );

	// ������ �����ߴٸ�
	if( Dlg.DoModal() == TRUE )
	{
		// ������ ��θ� �����ϰ�
		m_FileFullPath.Format( _T("%s"), Dlg.GetPathName() );

		// ����ϱ� ���� �ε��Ѵ�.
		if( m_BufferedImg.LoadFile( (TCHAR *)(LPCTSTR )m_FileFullPath ) )
		{
			// �ε强����
			// 
			m_FileName = Dlg.GetFileName();			

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
					m_ImgPt.y += (ImageOutRt.Height() - m_BufferedImg.GetHeight() ) / 2;
				else
					AfxMessageBox( _T("���� �ε忡 �����߽��ϴ�!") );
			}
			else
			{				
				if( m_BufferedImg.SetHeight( ImageOutRt.Height() ) )
					m_ImgPt.x += ( ImageOutRt.Width() - m_BufferedImg.GetWidth() ) / 2;			
				else
					AfxMessageBox( _T("���� �ε忡 �����߽��ϴ�!") );
			}

			Invalidate();
		}
		else
		{
			AfxMessageBox( _T("���� ���⿡ �����߽��ϴ�!") );
		}
	}
}

BOOL CPanoFileAddDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_BufferedImg.Init( this );	

	return TRUE;
}

void CPanoFileAddDlg::OnPaint()
{
	CPaintDC dc(this);

	Graphics G( dc );

	if( m_BufferedImg.m_pCachedbmp )
		G.DrawCachedBitmap( m_BufferedImg.m_pCachedbmp, m_ImgPt.x, m_ImgPt.y );
}

void CPanoFileAddDlg::OnBnClickedBtnFileadd()
{
	CString NewFileFullPath;
	CString strTmp;
	CMainFrame* pMain;
	pMain = (CMainFrame*)Afx_pVoidMain;

	strTmp = AppDir;
	NewFileFullPath.Format( _T("%s\\Panoramas\\%s"), strTmp, m_FileName );

	DWORD ErrorCode = GetLastError();
	if( CopyFile( m_FileFullPath, NewFileFullPath, TRUE ) ) 
	{
		theApp.InitailizePanoFileData();

		pMain->SetCaptionBarText( _T("�˸� : ���ο� �̹��� ������ �߰��ƽ��ϴ�!") );

		EndDialog( IDOK );
	}
	else
	{
		ErrorCode = GetLastError();
		if( ErrorCode == ERROR_FILE_EXISTS )
		{
			AfxMessageBox( _T("�̹� �����ϴ� ���� �Դϴ�!") );
		}
		else
		{
			AfxMessageBox( _T("������ ������ �� �����ϴ�!") );
		}
	}
}
