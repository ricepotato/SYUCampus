
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#define DEBUG_MODE 0

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"
#include "TreeViewData.h"
#include "sql.h"
#include "sqlext.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원

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

#define SIZE_RECT 10 // 탑 뷰와 위성 보기 링크 포인트 크기
#define NUM_OF_CATEGORYIMGLIST 18 // 카타고리 갯수
extern TCHAR ImgListName[ NUM_OF_CATEGORYIMGLIST ][20];

extern TCHAR AppDir[ MAX_PATH ];

extern void* Afx_pVoidApp;
extern void* Afx_pVoidMain;
extern void* Afx_pVoidView;
extern void* Afx_pVoidCurrentFile;

// 연결 마우스 커서입니다.
extern HCURSOR hCursorMove;
extern HCURSOR hCursorLinkArrow;

extern BOOL bViewPointShow;
extern BOOL bBuildingNameShow;

extern CMutex* hStartingMutex;