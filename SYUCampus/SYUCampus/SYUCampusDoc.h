
// SYUCampusDoc.h : CSYUCampusDoc Ŭ������ �������̽�
//


#pragma once


class CSYUCampusDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CSYUCampusDoc();
	DECLARE_DYNCREATE(CSYUCampusDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CSYUCampusDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


