
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once

#include "CategoryView.h"
#include "TopViewWnd.h"
#include "PartShowWnd.h"
#include "SatelliteViewWnd.h"

/*
#include "SYUCampus.h"
#include "MainFrm.h"
#include "SYUCampusView.h"

*/
/*
CSYUCampusView* pView;
pView = (CSYUCampusView*)Afx_pVoidView;

CMainFrame* pMain;
pMain = (CMainFrame*)Afx_pVoidMain;
*/
class CMainFrame : public CFrameWndEx
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:	

// 작업입니다.
public:
	CCategoryView m_wndCategory;	
	
	CTopViewWnd m_TopViewWnd;	
	CSatelliteViewWnd m_SatelliteViewWnd;

	CPartShowWnd m_PartShow;

	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;

	CMFCCaptionBar    m_wndCaptionBar;

	void InitializeRibbon( void );

	void MakeRibbonPanel1( CMFCRibbonCategory* Category );
	void MakeRibbonPanel2( CMFCRibbonCategory* Category );
	void MakeRibbonPanel3( CMFCRibbonCategory* Category );
	void MakeRibbonPanel4( CMFCRibbonCategory* Category );

	void MakeRibbonOptionPanel1( CMFCRibbonCategory* Category );

	BOOL CreateCaptionBar( void );

	void SetCaptionBarText( CString str );

	// 배율 패널입니다. 슬라이더 바위치를 알아내기 위해 필요합니다.
	CMFCRibbonPanel* pPanelRatio; 
	// 슬라이더 바 위치입니다.
	int m_nSliderPos;

	void SyncSliderBarPos( double Ratio );

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;	

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnResetToolBar( WPARAM wParam, LPARAM lParam );

public:
	afx_msg void OnPanoramaFile();
	afx_msg void OnShowTveditor();
	afx_msg void OnTopview();
	afx_msg void OnUpdateTopview(CCmdUI *pCmdUI);
	afx_msg void OnPartwnd();
	afx_msg void OnUpdatePartwnd(CCmdUI *pCmdUI);
	afx_msg void OnOption();
	afx_msg void OnSatelliteview();
	afx_msg void OnUpdateSatelliteview(CCmdUI *pCmdUI);
	afx_msg void OnShowHide();
	afx_msg void OnBnameShowhide();
	afx_msg void OnCategoryShowhide();
	afx_msg void OnUpdateWindowsMove(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRatioUser(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSlider1(CCmdUI *pCmdUI);
	afx_msg void OnMinimizeRighttop();
	afx_msg void OnMinimizeRightbottom();
	afx_msg void OnAddPanorama();
	afx_msg void OnSlider1();
	afx_msg void OnDeletePanorama();
	afx_msg void OnPopupAddlink();
	afx_msg void OnPopupAddviewSate();
};


