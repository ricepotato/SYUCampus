
// SYUCampus.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CSYUCampusApp 생성

CSYUCampusApp::CSYUCampusApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CSYUCampusApp 개체입니다.

CSYUCampusApp theApp;
ULONG_PTR gdiplusToken;


// CSYUCampusApp 초기화

BOOL CSYUCampusApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다. 
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// OLE 라이브러리를 초기화합니다.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));


	// 중복실행을 막습니다.
	
	hStartingMutex = new CMutex( 0, _T("ShamYook_University_CampusViewer_ver. 1.0ByD.O.T.") );
	if( GetLastError() == ERROR_ALREADY_EXISTS )
	{
		AfxMessageBox( _T("어플리케이션이 이미 실행되어있습니다!") );
		return FALSE;
	}
	

	// 레지스트리에 저장된 메뉴 도구모음 정보 무시합니다.
	CleanState();
	// 이미지리스트를 로드합니다.
	LoadImageLists();
	// 현재 디렉토리를 저장합니다.
	GetCurrentDirectory( MAX_PATH, AppDir );
	// 파노라마 jpg 파일정보를 초기화합니다.
	InitailizePanoFileData();
	bViewPointShow = FALSE;
	bBuildingNameShow = FALSE;



	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 응용 프로그램의 문서 템플릿을 등록합니다. 문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSYUCampusDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CSYUCampusView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	GdiplusStartupInput gdiplusStartupInput;
	 if( ::GdiplusStartup( &gdiplusToken, &gdiplusStartupInput, NULL ) != Ok )
	 {
		AfxMessageBox( _T("ERROR : Failed to initialize GDI+ library!") );
	 }

	


	// 이미지 이동시, 링크 클릭시 커서 모양
	hCursorMove = AfxGetApp()->LoadCursor( IDC_CURSOR_MOVE );
	hCursorLinkArrow = AfxGetApp()->LoadCursorW( IDC_CURSOR_LINK );

	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 접미사가 있을 경우에만 DragAcceptFiles를 호출합니다.
	//  SDI 응용 프로그램에서는 ProcessShellCommand 후에 이러한 호출이 발생해야 합니다.

	Afx_pVoidApp = this;

	return TRUE;
}



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CSYUCampusApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSYUCampusApp 사용자 지정 로드/저장 메서드

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

// CSYUCampusApp 메시지 처리기

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
		::AfxMessageBox( _T("파일 열기에 실패했습니다\n새로운 파일을 생성합니다") );

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
			AfxMessageBox( _T("파일 저장에 실패했습니다!") );
			return FALSE;
		}
		else
		{
			strTmp.Format( _T("%d 개의 새로운 파일이 발견됬습니다!"),  nNumNewFile );
			AfxMessageBox( strTmp );
			return TRUE;
		}
	}
	else
	{
		// 파일로드에 성공했으면 기존 파일리스트와 폴더내 파일을 검색해서 같은지 확인한다.
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

			// IsExistInList 는 기존 리스트에 파일이 존재하는지 찾는 함수이다.
			// FALSE 를 리턴하게 되면 새로 추가된 파일이라는 의미이다.
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


	// 기존의 파일 리스트와 현재 파일리스트를 비교해서 추가된 파일이 있으면 이 부분이 실행된다.
	if( bNewFileAdd )
	{
		CString strTmp;
		strTmp.Format( _T("%d 개의 새로운 파일이 발견되었습니다!"), nNumNewFile );
		AfxMessageBox( strTmp );
		if( !SavePanoFileData() )
		{
			AfxMessageBox( _T("파일 저장에 실패했습니다!") );
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
		TRACE(_T("비트맵을 로드할 수 없습니다. %x\n"), uiBmpId);
		ASSERT(FALSE);
		return FALSE;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	 UINT nFlags = ILC_MASK | ILC_COLOR24; // UINT 변수를 선언하고 ILC_COLOR24 와 ILC_MASK 를 적용한다.

	Afx_CategoryImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	Afx_CategoryImages.Add(&bmp, RGB(255, 0, 255));

	bmp.Detach();
	bmp.LoadBitmap( IDB_MINIMIZE ); // 리소스로부터 이미지를 읽어온다
	bmp.GetBitmap( &bmpObj );  // 이렇게 하면 BITMAP 이미지정보를 읽어올 수 있다	
	//그다음 이미지 리스트를 생성한다.
	// 이미지 리스트를 생성한다 이렇게 생성하면 이미지 리스트가 비어있는 상태가 된다.
	// 로드한 비트맵을 이미지 리스트에 추가시킨다.
	Afx_ImgList.Create( 29, bmpObj.bmHeight, nFlags, 0, 0 ); 	
	Afx_ImgList.Add(&bmp, RGB(255, 255, 255));

	bmp.Detach();
	bmp.LoadBitmap( IDB_BITMAP_STAR ); // 리소스로부터 이미지를 읽어온다
	bmp.GetBitmap( &bmpObj );  // 이렇게 하면 BITMAP 이미지정보를 읽어올 수 있다

	Afx_ImgListViewPoint.Create( 20, bmpObj.bmHeight, nFlags, 0, 0 ); 
	Afx_ImgListViewPoint.Add(&bmp, RGB(255, 255, 255));

	bmp.Detach();
	bmp.LoadBitmap( IDB_BITMAP_LTRB ); // 리소스로부터 이미지를 읽어온다
	bmp.GetBitmap( &bmpObj ); 

	Afx_ImgListLTRB.Create( 22, bmpObj.bmHeight, nFlags, 0, 0 );  // LTRB
	Afx_ImgListLTRB.Add(&bmp, RGB(255, 255, 0));

	bmp.Detach();
	bmp.LoadBitmap( IDB_BITMAP_FOOT ); // 발자국
	bmp.GetBitmap( &bmpObj ); 

	Afx_ImgListFoot.Create( 50, bmpObj.bmHeight, nFlags, 0, 0 ); 
	Afx_ImgListFoot.Add(&bmp, RGB(255, 255, 255));

	return TRUE;
}