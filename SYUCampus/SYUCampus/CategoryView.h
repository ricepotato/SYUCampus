#pragma once


#include "CategoryTree.h"
// CCategoryView

class CCategoryView : public CDockablePane
{
	DECLARE_DYNAMIC(CCategoryView)

public:
	CCategoryView();
	virtual ~CCategoryView();

private:
	CRect m_ClntRect;
public:
	CCategoryTree m_wndCategory;	
	CObList m_ListMajorBuilding;
	CEdit m_SearchEdit;
	CButton m_BtnSearch;

	void InitTree( void );
	BOOL LoadTreeListFile( void );

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnUpdateRatio10(CCmdUI *pCmdUI);
};


