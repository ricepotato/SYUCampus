
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// SYUCampus.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

CObList AfxTotalTreeList;
CObList AfxPanoFileList;
CObList AfxViewFileLinkList;

// 카타고리 이미지 리스트
CImageList Afx_CategoryImages;
// 별 이미지 리스트
CImageList Afx_ImgListViewPoint;
CImageList Afx_ImgList;
CImageList Afx_ImgListLTRB;
CImageList Afx_ImgListFoot;

TCHAR ImgListName[ NUM_OF_CATEGORYIMGLIST ][20] = { 
	_T("삼육 심벌"), 	
	_T("학교 기관"), 
	_T("행정 본부"), 
	_T("대학 기구"), 
	_T("연구소"), 	
	_T("주요 건물"), 
	_T("수첩"), 
	_T("식당"), 
	_T("대학"),
	_T("복지"),
	_T("정보"),	
	_T("주요 장소"),	
	_T("언론"),	
	_T("학교 기업"),		
	_T("학생 자치"),
	_T("학교 시설 1"),
	_T("학교 시설 2"),
	_T("운동 시설")
};

TCHAR AppDir[ MAX_PATH ];

HCURSOR hCursorMove;
HCURSOR hCursorLinkArrow;

void* Afx_pVoidApp;
void* Afx_pVoidMain;
void* Afx_pVoidView;
void* Afx_pVoidCurrentFile;

BOOL bViewPointShow;
BOOL bBuildingNameShow;

CMutex* hStartingMutex;


CPoint SetImagePosRight( int ScreenCx, int ScreenCy, int ImgCx, int ImgCy, CPoint ImgPos )
{
	// 이미지가 화면 밖으로 벗어났을 경우 바로잡아줍니다.
	if( ImgPos.y > 0 )
	{
		ImgPos.y = 0;		
	}
	if( ImgPos.x > 0 )
	{
		ImgPos.x = 0;
	}

	if( ImgCx > ScreenCx ) // 이미지의 cx가 창보다 더 클때
	{
		if( ScreenCx - ImgCx > ImgPos.x )// 이미지가 왼쪽으로 가지 않게 함
		{
			ImgPos.x = ScreenCx - ImgCx;
		}
	}
	else // 이미지의 cx 가 창보다 작을때
	{
		ImgPos.x = ScreenCx / 2 - ImgCx / 2;  // 가운데 출력
	}

	if( ImgCy > ScreenCy )
	{
		if( ScreenCy - ImgCy > ImgPos.y )
		{
			ImgPos.y = ScreenCy - ImgCy;
		}
	}
	else
	{
		ImgPos.y = ScreenCy / 2 - ImgCy / 2;
	}

	return ImgPos;
}

CPoint GetImagePoint( CPoint ImagePos, RECT View, CPoint pt )
{	
	/*
	화면위의 점 pt의 image 상 좌표를 구해냅니다.
	*/
	CPoint ImgPoint;

	if( ImagePos.x >= 0)
	{
		ImgPoint.x = pt.x - ImagePos.x;
	}
	else
	{
		ImgPoint.x = abs(ImagePos.x) + pt.x;
	}

	if( ImagePos.y >= 0 )
	{
		ImgPoint.y = pt.y - ImagePos.y;
	}
	else
	{
		ImgPoint.y = abs(ImagePos.y) + pt.y;
	}

	return ImgPoint;
}
CPoint SetImagePosToClientPoint( int ClientCx, int ClientCy, int ImgCx, int ImgCy, CPoint PtOnClient, CPoint PtOnImg )
{
	CPoint ImgPos;

	if( ClientCx > ImgCx )
		return CPoint( 0, 0 );
	if( ClientCy > ImgCy )
		return CPoint( 0, 0 );

	// 이미지상의 좌표 PtOnImg 를 클라이언트 영역상의 좌표 PtOnClient에 오도록
	// ImgPos 를 조정합니다.

	ImgPos.x = -PtOnImg.x + PtOnClient.x;
	ImgPos.y = -PtOnImg.y + PtOnClient.y;

	return ImgPos;
}
void CleanUpList( CObList &List )
{

	POSITION pos;
	pos = List.GetHeadPosition();
	CObject* pObj;
	int num = List.GetCount();
	for( int i = 0 ; i < num ; i++ )
	{
		pObj = (CObject*)List.GetNext( pos );
		delete pObj;
	}

	List.RemoveAll();
}
