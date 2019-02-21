
// SYUCampus.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "SYUCampus.h"
#include "MainFrm.h"

#include "SYUCampusDoc.h"
#include "SYUCampusView.h"
#include "PanoFileData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSYUCampusApp

BEGIN_MESSAGE_MAP(CSYUCampusApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CSYUCampusApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CSYUCampusApp ����

CSYUCampusApp::CSYUCampusApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CSYUCampusApp ��ü�Դϴ�.

CSYUCampusApp theApp;
ULONG_PTR gdiplusToken;


// CSYUCampusApp �ʱ�ȭ

BOOL CSYUCampusApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�. 
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));


	// �ߺ������� �����ϴ�.
	
	hStartingMutex = new CMutex( 0, _T("ShamYook_University_CampusViewer_ver. 1.0ByD.O.T.") );
	if( GetLastError() == ERROR_ALREADY_EXISTS )
	{
		AfxMessageBox( _T("���ø����̼��� �̹� ����Ǿ��ֽ��ϴ�!") );
		return FALSE;
	}
	

	// ������Ʈ���� ����� �޴� �������� ���� �����մϴ�.
	CleanState();
	// �̹�������Ʈ�� �ε��մϴ�.
	LoadImageLists();
	// ���� ���丮�� �����մϴ�.
	GetCurrentDirectory( MAX_PATH, AppDir );
	// �ĳ�� jpg ���������� �ʱ�ȭ�մϴ�.
	InitailizePanoFileData();
	bViewPointShow = FALSE;
	bBuildingNameShow = FALSE;



	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSYUCampusDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(CSYUCampusView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	GdiplusStartupInput gdiplusStartupInput;
	 if( ::GdiplusStartup( &gdiplusToken, &gdiplusStartupInput, NULL ) != Ok )
	 {
		AfxMessageBox( _T("ERROR : Failed to initialize GDI+ library!") );
	 }

	


	// �̹��� �̵���, ��ũ Ŭ���� Ŀ�� ���
	hCursorMove = AfxGetApp()->LoadCursor( IDC_CURSOR_MOVE );
	hCursorLinkArrow = AfxGetApp()->LoadCursorW( IDC_CURSOR_LINK );

	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	//  SDI ���� ���α׷������� ProcessShellCommand �Ŀ� �̷��� ȣ���� �߻��ؾ� �մϴ�.

	Afx_pVoidApp = this;

	return TRUE;
}



// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CSYUCampusApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSYUCampusApp ����� ���� �ε�/���� �޼���

void CSYUCampusApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CSYUCampusApp::LoadCustomState()
{
}

void CSYUCampusApp::SaveCustomState()
{
}

// CSYUCampusApp �޽��� ó����

int CSYUCampusApp::ExitInstance()
{
	::GdiplusShutdown( gdiplusToken );

	CleanUpList( AfxTotalTreeList );
	CleanUpList( AfxPanoFileList );
	CleanUpList( AfxViewFileLinkList );

	delete hStartingMutex;

	return CWinAppEx::ExitInstance();
}

BOOL CSYUCampusApp::LoadPanoFileData( void )
{
	TCHAR str[ MAX_PATH ];
	lstrcpy( str, AppDir );
	lstrcat( str, _T("\\data\\") );
	lstrcat( str, PANODATAFILE_NAME );

	CPanoFileData* pData;

	CFile File;

	if( File.Open( str, CFile::modeRead ) )
	{
		int num;
		File.Read( &num, sizeof(int) );

		for( int i = 0 ; i < num ; i++ )
		{
			pData = new CPanoFileData;
			File.Read( pData->m_FileName, sizeof( TCHAR ) * MAX_PATH );
			File.Read( &pData->m_TopViewPt, sizeof( CPoint ) ) ;
			File.Read( &pData->m_nEast, sizeof( int ) );
			File.Read( &pData->m_SatelliteTopViewPt, sizeof( CPoint ) );
			File.Read( &pData->m_nSatelliteEast, sizeof( int ) );			

			AfxPanoFileList.AddTail( pData );
		}
		return TRUE;			
	}
	else
		return FALSE;
}


BOOL CSYUCampusApp::IsExistInList( TCHAR* FileName )
{
		POSITION pos;

	pos = AfxPanoFileList.GetHeadPosition();
	int num;
	num = AfxPanoFileList.GetCount();

	CPanoFileData* pData;

	for( int i = 0 ; i < num ; i++ )
	{
		pData = (CPanoFileData*)AfxPanoFileList.GetNext( pos );
		if( lstrcmp( pData->m_FileName, FileName ) == 0 )
			return TRUE;
	}

	return FALSE;
}

BOOL CSYUCampusApp::InitailizePanoFileData( void )
{
	BOOL bNewFileAdd = FALSE;
	int nNumNewFile = 0;
	CleanUpList( AfxPanoFileList );
	if( !LoadPanoFileData() )
	{
		::AfxMessageBox( _T("���� ���⿡ �����߽��ϴ�\n���ο� ������ �����մϴ�") );

		CPanoFileData* pData;
		CString strTmp;
		strTmp.Format( _T("%s"), AppDir );
		strTmp = strTmp + _T("\\panoramas\\*.jpg");

		CFileFind Find;

		BOOL bSuccess = Find.FindFile( strTmp );		

		while( bSuccess )
		{
			bSuccess = Find.FindNextFile();
			if( Find.IsDirectory() )
				continue;

			pData = new CPanoFileData;
			lstrcpy( pData->m_FileName, Find.GetFileName() );
			pData->m_TopViewPt = CPoint( -10, -10 );
			pData->m_nEast = 0;
			pData->m_SatelliteTopViewPt = CPoint( -10, -10 );			
			pData->m_nSatelliteEast = 0;			

			AfxPanoFileList.AddTail( pData );
			nNumNewFile++;
		}

		if( !SavePanoFileData() )
		{
			AfxMessageBox( _T("���� ���忡 �����߽��ϴ�!") );
			return FALSE;
		}
		else
		{
			strTmp.Format( _T("%d ���� ���ο� ������ �߰߉���ϴ�!"),  nNumNewFile );
			AfxMessageBox( strTmp );
			return TRUE;
		}
	}
	else
	{
		// ���Ϸε忡 ���������� ���� ���ϸ���Ʈ�� ������ ������ �˻��ؼ� ������ Ȯ���Ѵ�.
		CPanoFileData* pData;

		CString strTmp;
		strTmp.Format( _T("%s"), AppDir );
		strTmp = strTmp + _T("\\panoramas\\*.jpg");

		CFileFind Find;

		BOOL bSuccess = Find.FindFile( strTmp );		

		while( bSuccess )
		{
			bSuccess = Find.FindNextFile();
			if( Find.IsDirectory() )
				continue;

			// IsExistInList �� ���� ����Ʈ�� ������ �����ϴ��� ã�� �Լ��̴�.
			// FALSE �� �����ϰ� �Ǹ� ���� �߰��� �����̶�� �ǹ��̴�.
			if( IsExistInList( (TCHAR *)(LPCTSTR)Find.GetFileName() )== FALSE )
			{
				pData = new CPanoFileData;
				lstrcpy( pData->m_FileName, Find.GetFileName() );
				pData->m_nEast = 0;
				pData->m_TopViewPt = CPoint( -10, -10 );

				AfxPanoFileList.AddTail( pData );
				bNewFileAdd = TRUE;
				nNumNewFile++;
			}
		}		
	}


	// ������ ���� ����Ʈ�� ���� ���ϸ���Ʈ�� ���ؼ� �߰��� ������ ������ �� �κ��� ����ȴ�.
	if( bNewFileAdd )
	{
		CString strTmp;
		strTmp.Format( _T("%d ���� ���ο� ������ �߰ߵǾ����ϴ�!"), nNumNewFile );
		AfxMessageBox( strTmp );
		if( !SavePanoFileData() )
		{
			AfxMessageBox( _T("���� ���忡 �����߽��ϴ�!") );
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CSYUCampusApp::SavePanoFileData( void )
{
	TCHAR str[ MAX_PATH ];

	lstrcpy( str, AppDir );
	lstrcat( str, _T("\\data\\") );
	lstrcat( str, PANODATAFILE_NAME );

	CPanoFileData* pData;
	POSITION pos;

	CFile File;
	if( File.Open( str, CFile::modeCreate | CFile::modeWrite ) )
	{
		int num;
		num = AfxPanoFileList.GetCount();

		File.Write( &num, sizeof( int ) );
		pos = AfxPanoFileList.GetHeadPosition();
		for( int i = 0 ; i < num ; i++ )
		{
			pData = (CPanoFileData*)AfxPanoFileList.GetNext( pos );
			File.Write( pData->m_FileName, sizeof( TCHAR ) * MAX_PATH );
			File.Write( &pData->m_TopViewPt, sizeof( CPoint ) ) ;
			File.Write( &pData->m_nEast, sizeof( int ) );			
			File.Write( &pData->m_SatelliteTopViewPt, sizeof( CPoint ) );
			File.Write( &pData->m_nSatelliteEast, sizeof( int ) );
		}
		return TRUE;			
	}
	else
		return FALSE;
}

BOOL CSYUCampusApp::LoadImageLists( void )
{
	UINT uiBmpId = IDB_BITMAP2;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("��Ʈ���� �ε��� �� �����ϴ�. %x\n"), uiBmpId);
		ASSERT(FALSE);
		return FALSE;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	 UINT nFlags = ILC_MASK | ILC_COLOR24; // UINT ������ �����ϰ� ILC_COLOR24 �� ILC_MASK �� �����Ѵ�.

	Afx_CategoryImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	Afx_CategoryImages.Add(&bmp, RGB(255, 0, 255));

	bmp.Detach();
	bmp.LoadBitmap( IDB_MINIMIZE ); // ���ҽ��κ��� �̹����� �о�´�
	bmp.GetBitmap( &bmpObj );  // �̷��� �ϸ� BITMAP �̹��������� �о�� �� �ִ�	
	//�״��� �̹��� ����Ʈ�� �����Ѵ�.
	// �̹��� ����Ʈ�� �����Ѵ� �̷��� �����ϸ� �̹��� ����Ʈ�� ����ִ� ���°� �ȴ�.
	// �ε��� ��Ʈ���� �̹��� ����Ʈ�� �߰���Ų��.
	Afx_ImgList.Create( 29, bmpObj.bmHeight, nFlags, 0, 0 ); 	
	Afx_ImgList.Add(&bmp, RGB(255, 255, 255));

	bmp.Detach();
	bmp.LoadBitmap( IDB_BITMAP_STAR ); // ���ҽ��κ��� �̹����� �о�´�
	bmp.GetBitmap( &bmpObj );  // �̷��� �ϸ� BITMAP �̹��������� �о�� �� �ִ�

	Afx_ImgListViewPoint.Create( 20, bmpObj.bmHeight, nFlags, 0, 0 ); 
	Afx_ImgListViewPoint.Add(&bmp, RGB(255, 255, 255));

	bmp.Detach();
	bmp.LoadBitmap( IDB_BITMAP_LTRB ); // ���ҽ��κ��� �̹����� �о�´�
	bmp.GetBitmap( &bmpObj ); 

	Afx_ImgListLTRB.Create( 22, bmpObj.bmHeight, nFlags, 0, 0 );  // LTRB
	Afx_ImgListLTRB.Add(&bmp, RGB(255, 255, 0));

	bmp.Detach();
	bmp.LoadBitmap( IDB_BITMAP_FOOT ); // ���ڱ�
	bmp.GetBitmap( &bmpObj ); 

	Afx_ImgListFoot.Create( 50, bmpObj.bmHeight, nFlags, 0, 0 ); 
	Afx_ImgListFoot.Add(&bmp, RGB(255, 255, 255));

	return TRUE;
}