
// SYUCampusDoc.cpp : CSYUCampusDoc 클래스의 구현
//

#include "stdafx.h"
#include "SYUCampus.h"

#include "SYUCampusDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSYUCampusDoc

IMPLEMENT_DYNCREATE(CSYUCampusDoc, CDocument)

BEGIN_MESSAGE_MAP(CSYUCampusDoc, CDocument)
END_MESSAGE_MAP()


// CSYUCampusDoc 생성/소멸

CSYUCampusDoc::CSYUCampusDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CSYUCampusDoc::~CSYUCampusDoc()
{
}

BOOL CSYUCampusDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CSYUCampusDoc serialization

void CSYUCampusDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CSYUCampusDoc 진단

#ifdef _DEBUG
void CSYUCampusDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSYUCampusDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSYUCampusDoc 명령
