
// SYUCampusDoc.cpp : CSYUCampusDoc Ŭ������ ����
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


// CSYUCampusDoc ����/�Ҹ�

CSYUCampusDoc::CSYUCampusDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CSYUCampusDoc::~CSYUCampusDoc()
{
}

BOOL CSYUCampusDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CSYUCampusDoc serialization

void CSYUCampusDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CSYUCampusDoc ����

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


// CSYUCampusDoc ���
