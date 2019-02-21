
// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "SYUCampus.h"

#include "MainFrm.h"
#include "PanoFileShowDlg.h"
#include "TreeViewEditorDlg.h"
#include "OptionDlg.h"
#include "SYUCampus.h"
#include "SYUCampusView.h"
#include "PanoFileAddDlg.h"
#include "PanoFileDeleteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_PANORAMA_FILE, &CMainFrame::OnPanoramaFile)
	ON_COMMAND(ID_SHOW_TVEDITOR, &CMainFrame::OnShowTveditor)
	ON_COMMAND(ID_TOPVIEW, &CMainFrame::OnTopview)
	ON_UPDATE_COMMAND_UI(ID_TOPVIEW, &CMainFrame::OnUpdateTopview)
	ON_COMMAND(ID_PARTWND, &CMainFrame::OnPartwnd)
	ON_UPDATE_COMMAND_UI(ID_PARTWND, &CMainFrame::OnUpdatePartwnd)
	ON_COMMAND(ID_OPTION, &CMainFrame::OnOption)
	ON_COMMAND(ID_SATELLITEVIEW, &CMainFrame::OnSatelliteview)
	ON_UPDATE_COMMAND_UI(ID_SATELLITEVIEW, &CMainFrame::OnUpdateSatelliteview)
	ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, OnResetToolBar )
	ON_COMMAND(ID_SHOW_HIDE, &CMainFrame::OnShowHide)
	ON_COMMAND(ID_BNAME_SHOWHIDE, &CMainFrame::OnBnameShowhide)
	ON_COMMAND(ID_CATEGORY_SHOWHIDE, &CMainFrame::OnCategoryShowhide)
	ON_UPDATE_COMMAND_UI(ID_WINDOWS_MOVE, &CMainFrame::OnUpdateWindowsMove)
	ON_UPDATE_COMMAND_UI(ID_RATIO_USER, &CMainFrame::OnUpdateRatioUser)
	ON_UPDATE_COMMAND_UI(ID_SLIDER1, &CMainFrame::OnUpdateSlider1)
	ON_COMMAND(ID_MINIMIZE_RIGHTTOP, &CMainFrame::OnMinimizeRighttop)
	ON_COMMAND(ID_MINIMIZE_RIGHTBOTTOM, &CMainFrame::OnMinimizeRightbottom)
	ON_COMMAND(ID_ADD_PANORAMA, &CMainFrame::OnAddPanorama)
	ON_COMMAND(ID_SLIDER1, &CMainFrame::OnSlider1)
	ON_COMMAND(ID_DELETE_PANORAMA, &CMainFrame::OnDeletePanorama)
	ON_COMMAND(ID_POPUP_ADDLINK, &CMainFrame::OnPopupAddlink)
	ON_COMMAND(ID_POPUP_ADDVIEW_SATE, &CMainFrame::OnPopupAddviewSate)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2003);
}

CMainFrame::~CMainFrame()
{
	m_nSliderPos = 0;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	//BOOL bNameValid;
	// ������ ���� ���� ���־� ������ �� ��Ÿ���� �����մϴ�.
	OnApplicationLook(theApp.m_nAppLook);

	m_wndRibbonBar.Create( this );
	InitializeRibbon();	
/*
	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("�޴� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// �޴� ������ Ȱ��ȭ�ص� ��Ŀ���� �̵����� �ʰ� �մϴ�.
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// ����� ���� ���� ���� �۾��� ����մϴ�.
	//InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);
*/
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: ���� ���� �� �޴� ������ ��ŷ�� �� ���� �Ϸ��� �� �ټ� ���� �����Ͻʽÿ�.
	//m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndMenuBar);
	//DockPane(&m_wndToolBar);


	// Visual Studio 2005 ��Ÿ�� ��ŷ â ������ Ȱ��ȭ�մϴ�.
	//CDockingManager::SetDockingMode(DT_SMART);
	// Visual Studio 2005 ��Ÿ�� ��ŷ â �ڵ� ���� ������ Ȱ��ȭ�մϴ�.
	//EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ���� ���� �� ��ŷ â �޴� �ٲٱ⸦ Ȱ��ȭ�մϴ�.
	//EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ����(<Alt> Ű�� ���� ä ����) ���� ���� ����� ������ Ȱ��ȭ�մϴ�.
	//CMFCToolBar::EnableQuickCustomization();
/*
	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// ����� ���� ���� ���� �̹����� �ε��մϴ�.
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			m_UserImages.SetImageSize(CSize(16, 16), FALSE);
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}
*/
	// �޴� ���� ������ Ȱ��ȭ�մϴ�(���� �ֱٿ� ����� ���).
	// TODO: ������� �⺻ ����� �����Ͽ� �� Ǯ�ٿ� �޴��� �ϳ� �̻��� �⺻ ����� ���Խ�ŵ�ϴ�.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_SHOW_HIDE);

	// ������� �ʴ� �޴��� ����ϴ�.
	//CMFCToolBar::SetBasicCommands(lstBasicCommands);

	
	SetWindowText( _T("�������б� ķ�۽� ��") ); // ���� ǥ���� ���ڿ� ����	

	// ž �� �����
	HICON hIcon;
	HCURSOR hCursor;

	hCursor = LoadCursor( NULL, IDC_ARROW );
	hIcon = LoadIcon( ::AfxGetInstanceHandle(), MAKEINTRESOURCE( IDR_MAINFRAME) );

	// ž �� �����
	m_TopViewWnd.CreateEx( WS_EX_OVERLAPPEDWINDOW , ::AfxRegisterWndClass( 0, hCursor, 0, hIcon ), _T("�������б� �ȳ���"), 
		WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME, CRect( 0, 0, 300 ,300 ), this, NULL ); 

	CRect WndRect;	
	GetWindowRect( &WndRect );
	CSize InfoViewSize( 400, 400 ); // ũ�⸦ �����Ѵ�.

	// ���� ����
	m_SatelliteViewWnd.CreateEx( WS_EX_OVERLAPPEDWINDOW, ::AfxRegisterWndClass( 0, hCursor, 0, hIcon ), _T("���� ����"), 
		WS_POPUP| WS_BORDER | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME, CRect( 0, 0, 300 ,300 ), this, NULL ); 

	if (!m_wndCategory.CreateEx( NULL, _T("ī�װ� ��"), this, CRect( 0, 0, 200, 200 ), TRUE, 904,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("ī�װ� �� â�� ������ ���߽��ϴ�.\n");
		return FALSE; // ������ ���߽��ϴ�.
	}

	CTabbedPane* pTabbedPane = new CTabbedPane( TRUE );
	if( !pTabbedPane->Create( _T(""), this, CRect( 0, 0, 250, 250 ),
		TRUE, (UINT)-1,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI ) )
	{
		return -1;
	}
	m_wndCategory.EnableDocking( CBRS_ALIGN_LEFT  | CBRS_ALIGN_RIGHT );
	DockPane( &m_wndCategory );

	pTabbedPane->AddTab( &m_wndCategory );
	pTabbedPane->EnableDocking( CBRS_ALIGN_LEFT  | CBRS_ALIGN_RIGHT  );
	DockPane( pTabbedPane );
	

	// ��Ʈ ������ �����.
	m_PartShow.CreateEx( 0, ::AfxRegisterWndClass( 0, hCursor, 0, hIcon ), _T("��Ʈ ������"), 
		WS_POPUP | WS_BORDER, CRect( 500, 500, 600 ,600 ), this, NULL ); 


//	m_wndToolBar.ResetAllImages();
//	m_wndToolBar.LoadBitmap( IDB_TOOLBAR );

	CreateCaptionBar();

	Afx_pVoidMain = this;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	cs.style &= ~FWS_ADDTOTITLE;// �����ڿ� ����


	return TRUE;
}

// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame �޽��� ó����

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* �޴��� �˻��մϴ�. */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	theApp.m_nAppLook = ID_VIEW_APPLOOK_OFF_2007_BLACK;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// �⺻ Ŭ������ ���� �۾��� �����մϴ�.

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// ��� ����� ���� ������ ����� ���� ���߸� Ȱ��ȭ�մϴ�.
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnPanoramaFile()
{
	CSYUCampusApp* App;

	App = (CSYUCampusApp*)Afx_pVoidApp;
	CPanoFileShowDlg dlg;

	dlg.m_bInsert = FALSE;

	if( dlg.DoModal() == IDOK )
	{
		App->SavePanoFileData();
	}
}

void CMainFrame::OnShowTveditor()
{
	CTreeViewEditorDlg Dlg;
	Dlg.DoModal();
}

void CMainFrame::OnTopview()
{
	if( m_TopViewWnd.IsWindowVisible() )
	{
		m_TopViewWnd.ShowWindow( SW_HIDE );
	}
	else
	{
		m_TopViewWnd.ShowWindow( SW_SHOW );
	}
}

void CMainFrame::OnUpdateTopview(CCmdUI *pCmdUI)
{
	if( m_TopViewWnd.IsWindowVisible() )
	{
		pCmdUI->SetCheck( TRUE );
	}
	else
	{
		pCmdUI->SetCheck( FALSE );
	}
}

void CMainFrame::OnPartwnd()
{
	if( m_PartShow.IsWindowVisible() )
		m_PartShow.ShowWindow( SW_HIDE );
	else
		m_PartShow.ShowWindow( SW_SHOW );
}

void CMainFrame::OnUpdatePartwnd(CCmdUI *pCmdUI)
{
	if( m_PartShow.IsWindowVisible() )
		pCmdUI->SetCheck( TRUE );
	else
		pCmdUI->SetCheck( FALSE );
}

void CMainFrame::OnOption()
{
	COptionDlg Dlg;
	Dlg.DoModal();
}

void CMainFrame::OnSatelliteview()
{
	if( m_SatelliteViewWnd.IsWindowVisible() )
		m_SatelliteViewWnd.ShowWindow( SW_HIDE );
	else
		m_SatelliteViewWnd.ShowWindow( SW_SHOW );

}

void CMainFrame::OnUpdateSatelliteview(CCmdUI *pCmdUI)
{
	if( m_SatelliteViewWnd.IsWindowVisible() )
		pCmdUI->SetCheck( TRUE );
	else
		pCmdUI->SetCheck( FALSE );
}

LRESULT CMainFrame::OnResetToolBar( WPARAM wParam, LPARAM lParam )
{
	UINT uID = (UINT)wParam;

	if( uID == IDR_MAINFRAME_256 )
	{
	}
	return 0;
}
void CMainFrame::OnShowHide()
{
	bViewPointShow = !bViewPointShow;

	m_TopViewWnd.Invalidate();
	m_SatelliteViewWnd.Invalidate();
}

void CMainFrame::OnBnameShowhide()
{
	bBuildingNameShow = !bBuildingNameShow;
	
	m_TopViewWnd.Invalidate();
	m_SatelliteViewWnd.Invalidate();
}


void CMainFrame::InitializeRibbon( void )
{	
	m_MainButton.SetImage( IDB_MAIN );
	m_MainButton.SetToolTipText( _T("�޴�") );

	m_PanelImages.SetImageSize(CSize(16, 16));
	m_PanelImages.Load(IDB_MAINMENUSM);

	m_wndRibbonBar.SetApplicationButton( &m_MainButton, CSize( 45, 45 ) );
	CMFCRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory(  _T("�������б� ķ�۽� ��"), IDB_MAINMENUSM, IDB_MAINMENU );

	pMainPanel->Add(new CMFCRibbonButton(ID_ADD_PANORAMA, _T("�� �ĳ�� ���� �߰�"), 12, 12, TRUE));
	pMainPanel->Add(new CMFCRibbonButton(ID_DELETE_PANORAMA, _T("���� �ĳ�� ���� ����"), 13, 13, TRUE));

	pMainPanel->Add(new CMFCRibbonSeparator( TRUE ) );
	pMainPanel->AddToBottom(new CMFCRibbonMainPanelButton( ID_APP_EXIT, _T("����"), 9 ) );
	

	CMFCRibbonCategory* pCategoryMenu = m_wndRibbonBar.AddCategory(_T("�޴�"), IDB_MAINMENUSM, IDB_MAINMENU);	
	CMFCRibbonCategory* pCategoryOption = m_wndRibbonBar.AddCategory(_T("�ɼ�"), IDB_MAINMENUSM, IDB_MAINMENU);	

	MakeRibbonPanel1( pCategoryMenu );
	MakeRibbonPanel2( pCategoryMenu );	
	MakeRibbonPanel3( pCategoryMenu );
	MakeRibbonPanel4( pCategoryMenu );	

	MakeRibbonOptionPanel1( pCategoryOption );

	CList<UINT, UINT> lstQATCmds;
	lstQATCmds.AddTail(ID_APP_ABOUT);
	//m_wndRibbonBar.SetQuickAccessCommands(lstQATCmds);
	m_wndRibbonBar.AddToTabs(new CMFCRibbonButton(ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (18)));
	
}

void CMainFrame::OnCategoryShowhide()
{
	m_wndCategory.ShowWindow( SW_HIDE );
}

void CMainFrame::OnUpdateWindowsMove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( TRUE );
}

void CMainFrame::OnUpdateRatioUser(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( TRUE );
}

void CMainFrame::MakeRibbonPanel1( CMFCRibbonCategory* Category )
{
	pPanelRatio = Category->AddPanel( _T("�ĳ�� ����"), m_PanelImages.ExtractIcon(0));
	CMFCRibbonButton* pBtnZoomIn = new CMFCRibbonButton(ID_ZOOMIN, _T("Ȯ��"), 0, 0);
	CMFCRibbonButton* pBtnZoomOut = new CMFCRibbonButton(ID_ZOOMOUT, _T("���"), 1, 1);
	CMFCRibbonButton* pBtnUser = new CMFCRibbonButton( ID_RATIO_USER, _T("����� ����"), 2);		

	CMFCRibbonSlider* Slider1 = new CMFCRibbonSlider( ID_SLIDER1, 150 /* Slider width */);
	Slider1->SetZoomIncrement( 5 );
	Slider1->SetZoomButtons();
	Slider1->SetRange(0, 100);
	Slider1->SetPos(0);

	pBtnUser->SetMenu( IDR_MENU_RATIO );
	pBtnUser->SetAlwaysLargeImage();
	
	pPanelRatio->Add( pBtnZoomIn );
	pPanelRatio->Add( pBtnZoomOut );
	
	pPanelRatio->Add(new CMFCRibbonSeparator());
	pPanelRatio->Add(new CMFCRibbonLabel(_T("���� �����̴�")));	
//	pPanelRatio->Remove( 4 );
//	pPanelRatio->Insert( new CMFCRibbonLabel( _T("�ĳ�� ���� : 80%") ), 4 );	
	pPanelRatio->Add(Slider1);
	pPanelRatio->Add( pBtnUser );
}
void CMainFrame::OnUpdateSlider1(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( TRUE );
}

void CMainFrame::OnMinimizeRighttop()
{
	CSYUCampusView* pView = (CSYUCampusView*)Afx_pVoidView;

	if( m_TopViewWnd.IsWindowVisible() )
	{
		m_TopViewWnd.m_ViewPtClicked = FALSE;
		m_TopViewWnd.MySetWindowSize( CPoint( pView->m_ClientRect.right - 300, 0 ), CSize( 300, 300 ) );
	}

	if( m_SatelliteViewWnd.IsWindowVisible() )
	{
		m_SatelliteViewWnd.m_ViewPtClicked = FALSE;
		if( m_TopViewWnd.IsWindowVisible() )
		{
			m_SatelliteViewWnd.MySetWindowSize( CPoint( pView->m_ClientRect.right - 600, 0 ), CSize( 300, 300 ) );
		}
		else
		{
			m_SatelliteViewWnd.MySetWindowSize( CPoint( pView->m_ClientRect.right - 300, 0 ), CSize( 300, 300 ) );
		}
	}

}

void CMainFrame::OnMinimizeRightbottom()
{
	CSYUCampusView* pView = (CSYUCampusView*)Afx_pVoidView;

	if( m_TopViewWnd.IsWindowVisible() )
	{
		m_TopViewWnd.m_ViewPtClicked = FALSE;
		m_TopViewWnd.MySetWindowSize( CPoint( pView->m_ClientRect.right - 300, pView->m_ClientRect.bottom - 300 ), CSize( 300, 300 ) );
	}
	if( m_SatelliteViewWnd.IsWindowVisible() )
	{
		m_SatelliteViewWnd.m_ViewPtClicked = FALSE;
		if( m_TopViewWnd.IsWindowVisible() )		
			m_SatelliteViewWnd.MySetWindowSize( CPoint( pView->m_ClientRect.right - 600, pView->m_ClientRect.bottom - 300 ), CSize( 300, 300 ) );
		else
			m_SatelliteViewWnd.MySetWindowSize( CPoint( pView->m_ClientRect.right - 300, pView->m_ClientRect.bottom - 300 ), CSize( 300, 300 ) );
	}
}

void CMainFrame::MakeRibbonPanel2( CMFCRibbonCategory* Category )
{
	CMFCRibbonPanel* pPanelTopView = Category->AddPanel( _T("����"), m_PanelImages.ExtractIcon(0) );
	CMFCRibbonButton* pBtnViewPointLink = new CMFCRibbonButton(ID_SHOW_HIDE, _T("�� ����Ʈ ���̱�/�����"), 6, 6 );
	CMFCRibbonButton* pBtnBulindingName = new CMFCRibbonButton(ID_BNAME_SHOWHIDE, _T("�ǹ��̸� ���̱�/�����"), 5, 5 );
	//CMFCRibbonButton* pBtnLinkPoint = new CMFCRibbonButton(ID_LINKPOINT_SHOWHIDE, _T("��ũ ����Ʈ ���̱�/�����"), 3, 3 );

	pPanelTopView->Add( pBtnViewPointLink );
	pPanelTopView->Add( pBtnBulindingName );
	//pPanelTopView->Add( pBtnLinkPoint );
}
void CMainFrame::MakeRibbonPanel3( CMFCRibbonCategory* Category )
{
	CMFCRibbonPanel* pPanelWindow = Category->AddPanel( _T("������"), m_PanelImages.ExtractIcon(0));
	CMFCRibbonButton* pBtnTopMap = new CMFCRibbonButton(ID_TOPVIEW, _T("�������б� �ȳ��� ���̱�/�����"), 7, 7);
	CMFCRibbonButton* pBtnSatellite = new CMFCRibbonButton(ID_SATELLITEVIEW, _T("���� ���� ���̱�/�����"), 8, 8);
	//CMFCRibbonButton* pBtnCategory = new CMFCRibbonButton(ID_CATEGORY_SHOWHIDE, _T("īŸ�� ���̱�/�����"), 4, 4);	
	CMFCRibbonButton* pBtnWindowMove = new CMFCRibbonButton(ID_WINDOWS_MOVE, _T("������ �̵�"), 17, 17 );

	CMFCRibbonButton* pBtnTopRight = new CMFCRibbonButton(ID_MINIMIZE_RIGHTTOP, _T("������ ������ ���� �ּ�ȭ"), 16 );	
	CMFCRibbonButton* pBtnBottomRight = new CMFCRibbonButton(ID_MINIMIZE_RIGHTBOTTOM, _T("������ ������ �Ʒ��� �ּ�ȭ"), 15 );	

	pBtnWindowMove->SetMenu( IDR_MENU_WINDOWMOVE );
	pBtnWindowMove->SetAlwaysLargeImage();
	pBtnWindowMove->RemoveSubItem(0);
	pBtnWindowMove->AddSubItem( pBtnTopRight );
	pBtnWindowMove->AddSubItem( pBtnBottomRight );

	pPanelWindow->Add( pBtnTopMap );
	pPanelWindow->Add( pBtnSatellite );
	pPanelWindow->Add( pBtnWindowMove );
	//pPanelWindow->Add( pBtnTopRight );
	//pPanelWindow->Add( pBtnBottomRight );	
}
void CMainFrame::MakeRibbonPanel4( CMFCRibbonCategory* Category )
{
	CMFCRibbonPanel* pPanelCustomize = Category->AddPanel( _T("����"), m_PanelImages.ExtractIcon(0));
	//CMFCRibbonButton* pBtnOption = new CMFCRibbonButton(ID_OPTION, _T("���� ����"), 11, 11);		
	CMFCRibbonButton* pBtnPanoEditor = new CMFCRibbonButton(ID_PANORAMA_FILE, _T("�ĳ�� ������ ����"), 4, 4 );
	//CMFCRibbonButton* pBtnPanoLinkEditor = new CMFCRibbonButton(ID_LINK_DATAEDITOR, _T("�ĳ�� ��ũ ������ ����"), 14, 14 );
	CMFCRibbonButton* pBtnCategoryEditor = new CMFCRibbonButton(ID_SHOW_TVEDITOR, _T("ī�װ� ������ ����"), 10, 10 );	

	//pPanelCustomize->Add( pBtnOption );
	pPanelCustomize->Add( pBtnPanoEditor );
	//pPanelCustomize->Add( pBtnPanoLinkEditor );
	pPanelCustomize->Add( pBtnCategoryEditor );
}
void CMainFrame::OnAddPanorama()
{
	CPanoFileAddDlg Dlg;

	Dlg.DoModal();
}
BOOL CMainFrame::CreateCaptionBar( void )
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, NULL, -1, TRUE))
	{
		TRACE0("ĸ�� ǥ������ ������ ���߽��ϴ�.\n");
		return FALSE;
	}

	//m_wndCaptionBar.SetButton( _T("����..."), ID_APP_EXIT, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	//m_wndCaptionBar.SetButtonToolTip( _T("������ ������ Ŭ���ϼ���!") );
	

	m_wndCaptionBar.SetText( _T("�������б� ķ�۽� �信 ���Ű��� ȯ���մϴ�! ������ ���÷��� ��ư�� Ŭ�� �ϼ���.") , CMFCCaptionBar::ALIGN_LEFT);
	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	m_wndCaptionBar.SetImageToolTip( _T("����"), _T("���α׷� ������ ǥ�õ˴ϴ�.") );
	

	return 0;
}

void CMainFrame::SetCaptionBarText( CString str )
{
	m_wndCaptionBar.SetText( str, CMFCCaptionBar::ALIGN_LEFT );	
}
void CMainFrame::OnSlider1()
{	
	CSYUCampusView* pView;
	pView = (CSYUCampusView*)Afx_pVoidView;
	CMFCRibbonSlider* Slider1 = (CMFCRibbonSlider*)pPanelRatio->GetElement( 4 );
	double ratio;
	if( pView->m_bLoaded )
	{		
		if( m_nSliderPos != Slider1->GetPos() )
		{
			m_nSliderPos = Slider1->GetPos();
			ratio = (double)m_nSliderPos / 100.0;
			pView->SetImageRatio( ratio );			
		}
	}
}

void CMainFrame::SyncSliderBarPos( double Ratio )
{
	int nSliderPos;
	CMFCRibbonSlider* Slider1 = (CMFCRibbonSlider*)pPanelRatio->GetElement( 4 );

	nSliderPos = (int)(Ratio * 100.0);
	Slider1->SetPos( nSliderPos );
}
void CMainFrame::OnDeletePanorama()
{
	 CPanoFileDeleteDlg Dlg;
	 Dlg.DoModal();
}

void CMainFrame::MakeRibbonOptionPanel1( CMFCRibbonCategory* Category )
{
	CMFCRibbonPanel* pPanelCustomize = Category->AddPanel( _T("����"), m_PanelImages.ExtractIcon(0));
}
void CMainFrame::OnPopupAddlink()
{
	CSYUCampusView* pView;
	pView = (CSYUCampusView*)Afx_pVoidView;

	if( pView->m_bLoaded )
	{
		m_TopViewWnd.SetWindowText( _T("������ ������Ʈ�� Ŭ���ϼ���!") );
		m_TopViewWnd.m_bNewLinkPointAdd = TRUE;
		pView->m_CurMousePos = GetImagePoint( pView->m_ImgPos, pView->m_ClientRect, pView->m_CurMousePos );
	}
}

void CMainFrame::OnPopupAddviewSate()
{
	m_SatelliteViewWnd.OpenViewPointAddDlg();
}
