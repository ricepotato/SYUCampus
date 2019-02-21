#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CTreeViewEditorDlg ��ȭ �����Դϴ�.

class CTreeViewEditorDlg : public CDialog
{
	DECLARE_DYNAMIC(CTreeViewEditorDlg)

public:
	CTreeViewEditorDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTreeViewEditorDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TREEVIEWEDITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_TreeEditorListCtrl;
	CComboBoxEx m_ImgComboBox;
	CComboBox m_Combo_SelectedTree; // ���� �޺� �ڽ�
	CComboBox m_Combo_ParentIndex; // �θ� �ε��� �޺� �ڽ�
	CEdit m_PointNameCtrl;// �̸��Է� ����Ʈ ��Ʈ�� ��ü

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

	CObList m_CurrentList; // ���� ���õ� Ʈ���� �����ϴ� ����Ʈ �Դϴ�.
	CObList m_UpperTree; // ���� Ʈ�� �����͸� �����ϴ� ����Ʈ �Դϴ�.
	int m_nCurComboSel; // ���� ���õ� ���� �ε��� �Դϴ�.
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
