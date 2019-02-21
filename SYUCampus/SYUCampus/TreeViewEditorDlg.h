#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CTreeViewEditorDlg 대화 상자입니다.

class CTreeViewEditorDlg : public CDialog
{
	DECLARE_DYNAMIC(CTreeViewEditorDlg)

public:
	CTreeViewEditorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTreeViewEditorDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TREEVIEWEDITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_TreeEditorListCtrl;
	CComboBoxEx m_ImgComboBox;
	CComboBox m_Combo_SelectedTree; // 범주 콤보 박스
	CComboBox m_Combo_ParentIndex; // 부모 인덱스 콤보 박스
	CEdit m_PointNameCtrl;// 이름입력 에디트 컨트롤 객체

	CString m_strPointName;
	CString m_strFileName;
	int m_nPointX;
	int m_nPointY;	
	int m_nPosX;
	int m_PosY;
	int m_nIndex;
	CString m_strDetail;
	
	CButton m_BtnInsert;
	CButton m_BtnModify;
	CButton m_BtnDelete;
	CButton m_BtnUp;
	CButton m_BtnDown;
	CButton m_BtnSave;
	CButton m_BtnLocSave;

	CObList m_CurrentList; // 현재 선택된 트리를 저장하는 리스트 입니다.
	CObList m_UpperTree; // 상위 트리 포인터를 저장하는 리스트 입니다.
	int m_nCurComboSel; // 현재 선택된 셀의 인덱스 입니다.
	int m_nCurListSel;

protected:
//	virtual void OnOK();

private:
	
	BOOL FileSave( void );
	BOOL FileLoad( int nCursel );
	void RefreshList( void );

	BOOL FindParent( int nParentIndex );
	void GetParentName( int nParnetIndex, TCHAR* ParentName );
	int GetRandIndex( int SelectedSel );

	
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnInsert();
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDown();	
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedBtnSetparnet();
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelchangeComboboxex1();	
	afx_msg void OnCbnSelchangeComboSelectedtree();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnLocsave();
	
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_EditDetailCtrl;
};
