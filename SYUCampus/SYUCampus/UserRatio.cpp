// UserRatio.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SYUCampus.h"
#include "UserRatio.h"
#include "SYUCampusView.h"


// CUserRatio 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUserRatio, CDialog)

CUserRatio::CUserRatio(CWnd* pParent /*=NULL*/)
	: CDialog(CUserRatio::IDD, pParent)
	, m_nSetRadioCtrl(1)
{
	m_lfViewRatio = 0;	
}

CUserRatio::~CUserRatio()
{
}

void CUserRatio::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_lfRatioEdit);
	DDX_Radio(pDX, IDC_RADIO_SETSCR, m_nSetRadioCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_nRatioEditCtrl);
}


BEGIN_MESSAGE_MAP(CUserRatio, CDialog)
	ON_BN_CLICKED(IDC_RADIO_SETSCR, &CUserRatio::OnBnClickedRadioSetscr)
	ON_BN_CLICKED(IDC_RADIO_SETSIZE, &CUserRatio::OnBnClickedRadioSetsize)
	ON_BN_CLICKED(IDOK, &CUserRatio::OnBnClickedOk)
END_MESSAGE_MAP()


// CUserRatio 메시지 처리기입니다.

BOOL CUserRatio::OnInitDialog()
{
	CDialog::OnInitDialog();

	CSYUCampusView* pView;
	pView = (CSYUCampusView*)Afx_pVoidView;

	m_lfViewRatio = pView->m_lfRatio;
	m_lfRatioEdit = m_lfViewRatio;
	
	UpdateData( FALSE );

	return TRUE;
}

void CUserRatio::OnBnClickedRadioSetscr()
{
	CSYUCampusView* pView;
	pView = (CSYUCampusView*)Afx_pVoidView;

	m_nRatioEditCtrl.EnableWindow( FALSE );
	double ratio;

	ratio = (double)pView->m_ClientRect.bottom / (double)pView->m_BufferdImg.m_ImgSize.cy;
	m_lfRatioEdit = ratio;

	m_nSetRadioCtrl = 0;
	UpdateData( FALSE );

}

void CUserRatio::OnBnClickedRadioSetsize()
{
	m_nSetRadioCtrl = 1;
	m_nRatioEditCtrl.EnableWindow( TRUE );
}

void CUserRatio::OnBnClickedOk()
{
	CSYUCampusView* pView;
	pView = (CSYUCampusView*)Afx_pVoidView;

	UpdateData( TRUE );
	double ratio;

	ratio = (double)pView->m_ClientRect.bottom / (double)pView->m_BufferdImg.m_ImgSize.cy;

	if( m_lfRatioEdit > 1 )
		m_lfRatioEdit = 1;	

	if( m_lfRatioEdit < ratio )
		m_lfRatioEdit = ratio;

	pView->SetImageRatio( m_lfRatioEdit );
		
	OnOK();
}
