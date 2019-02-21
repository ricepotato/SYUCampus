
// SYUCampus.h : SYUCampus ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.



// CSYUCampusApp:
// �� Ŭ������ ������ ���ؼ��� SYUCampus.cpp�� �����Ͻʽÿ�.
//

class CSYUCampusApp : public CWinAppEx
{
public:
	CSYUCampusApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();

public:
	// �ʿ��� ��� �̹��� ����Ʈ�� ���⼭ �ε��մϴ�.
	// initinstance �Լ����� cleanstate �Լ��� �Բ� ȣ��˴ϴ�.
	// ���Ǵ� �̹��� ����Ʈ�� ��� ���� ��ü�Դϴ�.
	BOOL LoadImageLists( void );	

	// �ĳ�� ���� �����͸� �ʱ�ȭ �մϴ�.
	// ���� ������ ������ ���� �ۼ��ϰ� ������ ���� ��ϰ� ���Ͽ� �� ������ �߰��մϴ�.
	// ������ ������ �˷��ִ� ����� �����ϴ�.
	BOOL InitailizePanoFileData( void );

	// �ĳ�� ������ ������ �ε��ϰ� ���̺��ϴ� �Լ��Դϴ�.
	BOOL LoadPanoFileData( void );
	BOOL SavePanoFileData( void );

	// ���� ���ϸ�ϰ� ���� ������ ���ϴ� �Լ��Դϴ�. ������ �����ϸ� TRUE �� �����մϴ�.
	BOOL IsExistInList( TCHAR* FileName );
};

extern CSYUCampusApp theApp;
