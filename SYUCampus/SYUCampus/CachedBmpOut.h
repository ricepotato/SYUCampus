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
	CachedBitmap* m_pCachedbmp; // 최종 출력될 버퍼
	CSize m_ImgSize; // 이미지 원본 크기
	CSize m_ImgModiSize; // 이미지 변형 크기
	CString m_FileName;

private:	
	Image* m_pImg; // 이미지가 로드될 이미지 포인터
	CWnd *pWnd; // 윈도우 객체포인터
};
