#pragma once

// CViewFileLinkData ��� ����Դϴ�.

class CViewFileLinkData : public CObject
{
public:
	CViewFileLinkData();
	virtual ~CViewFileLinkData();
public:
	TCHAR m_CurFileName[ 50 ];
	TCHAR m_NewFileName[ 50 ];
	CPoint m_NewPoint;
};


