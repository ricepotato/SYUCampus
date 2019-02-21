
// SYUCampus.h : SYUCampus 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.



// CSYUCampusApp:
// 이 클래스의 구현에 대해서는 SYUCampus.cpp을 참조하십시오.
//

class CSYUCampusApp : public CWinAppEx
{
public:
	CSYUCampusApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();

public:
	// 필요한 모든 이미지 리스트를 여기서 로드합니다.
	// initinstance 함수에서 cleanstate 함수와 함께 호출됩니다.
	// 사용되는 이미지 리스트는 모두 전역 객체입니다.
	BOOL LoadImageLists( void );	

	// 파노라마 파일 데이터를 초기화 합니다.
	// 만약 파일이 없으면 새로 작성하고 있으면 기존 목록과 비교하여 새 파일을 추가합니다.
	// 삭제된 파일을 알려주는 기능은 없습니다.
	BOOL InitailizePanoFileData( void );

	// 파노라마 데이터 파일을 로드하고 세이브하는 함수입니다.
	BOOL LoadPanoFileData( void );
	BOOL SavePanoFileData( void );

	// 기존 파일목록과 현재 파일을 비교하는 함수입니다. 파일이 존재하면 TRUE 를 리턴합니다.
	BOOL IsExistInList( TCHAR* FileName );
};

extern CSYUCampusApp theApp;
