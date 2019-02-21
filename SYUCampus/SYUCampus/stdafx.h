
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#define DEBUG_MODE 0

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"
#include "TreeViewData.h"
#include "sql.h"
#include "sqlext.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����

#include<gdiplus.h>
#include <afx.h>
#pragma comment(lib, "gdiplus")
using namespace Gdiplus;


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

CPoint SetImagePosRight( int ScreenCx, int ScreenCy, int ImgCx, int ImgCy, CPoint ImgPos );
CPoint GetImagePoint( CPoint ImagePos, RECT View, CPoint pt );
CPoint SetImagePosToClientPoint( int ClientCx, int ClientCy, int ImgCx, int ImgCy, CPoint PtOnClient, CPoint PtOnImg );
void CleanUpList( CObList &List );

extern CObList AfxTotalTreeList;
extern CObList AfxPanoFileList;
extern CObList AfxViewFileLinkList;

extern CImageList Afx_CategoryImages;
extern CImageList Afx_ImgListViewPoint;
extern CImageList Afx_ImgList;
extern CImageList Afx_ImgListLTRB;
extern CImageList Afx_ImgListFoot;

#define SIZE_RECT 10 // ž ��� ���� ���� ��ũ ����Ʈ ũ��
#define NUM_OF_CATEGORYIMGLIST 18 // īŸ�� ����
extern TCHAR ImgListName[ NUM_OF_CATEGORYIMGLIST ][20];

extern TCHAR AppDir[ MAX_PATH ];

extern void* Afx_pVoidApp;
extern void* Afx_pVoidMain;
extern void* Afx_pVoidView;
extern void* Afx_pVoidCurrentFile;

// ���� ���콺 Ŀ���Դϴ�.
extern HCURSOR hCursorMove;
extern HCURSOR hCursorLinkArrow;

extern BOOL bViewPointShow;
extern BOOL bBuildingNameShow;

extern CMutex* hStartingMutex;