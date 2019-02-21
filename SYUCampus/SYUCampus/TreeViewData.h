#pragma once
#include "afx.h"

class CTreeViewData :
	public CObject
{
public:
	CTreeViewData(void);
	~CTreeViewData(void);

	TCHAR m_PointName[ 50 ];
	TCHAR m_FileName[ MAX_PATH ];	
	CPoint m_Point;
	CPoint m_ImgPos;
	int m_nIndex;
	HTREEITEM m_hTreeItem;
	int m_nParentIndex;
	int m_nImgListIndex;
	TCHAR m_Detail[512];
};
