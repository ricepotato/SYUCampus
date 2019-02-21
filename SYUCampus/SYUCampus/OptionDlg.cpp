// OptionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SYUCampus.h"
#include "OptionDlg.h"


// COptionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(COptionDlg, CDialog)

COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionDlg::IDD, pParent)
{

}

COptionDlg::~COptionDlg()
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialog)
END_MESSAGE_MAP()


// COptionDlg 메시지 처리기입니다.
