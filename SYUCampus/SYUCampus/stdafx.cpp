
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// SYUCampus.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

CObList AfxTotalTreeList;
CObList AfxPanoFileList;
CObList AfxViewFileLinkList;

// īŸ�� �̹��� ����Ʈ
CImageList Afx_CategoryImages;
// �� �̹��� ����Ʈ
CImageList Afx_ImgListViewPoint;
CImageList Afx_ImgList;
CImageList Afx_ImgListLTRB;
CImageList Afx_ImgListFoot;

TCHAR ImgListName[ NUM_OF_CATEGORYIMGLIST ][20] = { 
	_T("���� �ɹ�"), 	
	_T("�б� ���"), 
	_T("���� ����"), 
	_T("���� �ⱸ"), 
	_T("������"), 	
	_T("�ֿ� �ǹ�"), 
	_T("��ø"), 
	_T("�Ĵ�"), 
	_T("����"),
	_T("����"),
	_T("����"),	
	_T("�ֿ� ���"),	
	_T("���"),	
	_T("�б� ���"),		
	_T("�л� ��ġ"),
	_T("�б� �ü� 1"),
	_T("�б� �ü� 2"),
	_T("� �ü�")
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
	// �̹����� ȭ�� ������ ����� ��� �ٷ�����ݴϴ�.
	if( ImgPos.y > 0 )
	{
		ImgPos.y = 0;		
	}
	if( ImgPos.x > 0 )
	{
		ImgPos.x = 0;
	}

	if( ImgCx > ScreenCx ) // �̹����� cx�� â���� �� Ŭ��
	{
		if( ScreenCx - ImgCx > ImgPos.x )// �̹����� �������� ���� �ʰ� ��
		{
			ImgPos.x = ScreenCx - ImgCx;
		}
	}
	else // �̹����� cx �� â���� ������
	{
		ImgPos.x = ScreenCx / 2 - ImgCx / 2;  // ��� ���
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
	ȭ������ �� pt�� image �� ��ǥ�� ���س��ϴ�.
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

	// �̹������� ��ǥ PtOnImg �� Ŭ���̾�Ʈ �������� ��ǥ PtOnClient�� ������
	// ImgPos �� �����մϴ�.

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
