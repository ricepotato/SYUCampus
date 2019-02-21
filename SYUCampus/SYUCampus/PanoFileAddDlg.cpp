// PanoFileAddDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SYUCampus.h"
#include "PanoFileAddDlg.h"
#include "MainFrm.h"


// CPanoFileAddDlg 대화 상자입니다.

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


// CPanoFileAddDlg 메시지 처리기입니다.

void CPanoFileAddDlg::OnBnClickedBtnFindfile()
{
	CString strTmp;
	CRect ImageOutRt;
	CWnd* pWnd;
	double ratioWnd;
	double ratioImg;

	// JPG 파일 열기 다이얼로그
	CFileDialog Dlg( TRUE, _T("jpg"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("jpg 파일(*.jpg) | *.jpg||"), this );

	// 파일을 선택했다면
	if( Dlg.DoModal() == TRUE )
	{
		// 파일의 경로를 저장하고
		m_FileFullPath.Format( _T("%s"), Dlg.GetPathName() );

		// 출력하기 위해 로드한다.
		if( m_BufferedImg.LoadFile( (TCHAR *)(LPCTSTR )m_FileFullPath ) )
		{
			// 로드성공시
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
					AfxMessageBox( _T("파일 로드에 실패했습니다!") );
			}
			else
			{				
				if( m_BufferedImg.SetHeight( ImageOutRt.Height() ) )
					m_ImgPt.x += ( ImageOutRt.Width() - m_BufferedImg.GetWidth() ) / 2;			
				else
					AfxMessageBox( _T("파일 로드에 실패했습니다!") );
			}

			Invalidate();
		}
		else
		{
			AfxMessageBox( _T("파일 열기에 실패했습니다!") );
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

		pMain->SetCaptionBarText( _T("알림 : 새로운 이미지 파일이 추가됐습니다!") );

		EndDialog( IDOK );
	}
	else
	{
		ErrorCode = GetLastError();
		if( ErrorCode == ERROR_FILE_EXISTS )
		{
			AfxMessageBox( _T("이미 존재하는 파일 입니다!") );
		}
		else
		{
			AfxMessageBox( _T("파일을 복사할 수 없습니다!") );
		}
	}
}
