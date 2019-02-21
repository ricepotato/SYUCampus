#pragma once

class CCachedBmpOut
{
public:
	CCachedBmpOut(void);
	~CCachedBmpOut(void);
	
	void Init( CWnd *pWnd );
	BOOL LoadFile( TCHAR* FileName );
	void UpLoadFile( void );
	BOOL SetRatio( double Ratio );
	BOOL SetHeight( int Height );
	BOOL SetWidth( int Width );
	BOOL SetSize( CSize sz );
	BOOL SetSize( int width, int height );

	int GetWidth();
	int GetHeight();

public:
	CachedBitmap* m_pCachedbmp; // ���� ��µ� ����
	CSize m_ImgSize; // �̹��� ���� ũ��
	CSize m_ImgModiSize; // �̹��� ���� ũ��
	CString m_FileName;

private:	
	Image* m_pImg; // �̹����� �ε�� �̹��� ������
	CWnd *pWnd; // ������ ��ü������
};
