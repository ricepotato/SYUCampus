#include "StdAfx.h"
#include "TreeViewData.h"

CTreeViewData::CTreeViewData(void)
{
	memset( m_PointName, 0, sizeof( m_PointName ) );
	memset( m_FileName, 0, sizeof( m_FileName ) );	
	memset( &m_Point, 0, sizeof( CPoint ) );
	memset( &m_ImgPos, 0, sizeof( CPoint ) );	
	m_nIndex = 0;
	m_hTreeItem = 0;
	m_nParentIndex = 0;
	m_nImgListIndex = 0;
}
CTreeViewData::~CTreeViewData(void)
{
}

