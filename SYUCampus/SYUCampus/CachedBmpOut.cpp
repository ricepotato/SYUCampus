#include "StdAfx.h"
#include "CachedBmpOut.h"

CCachedBmpOut::CCachedBmpOut(void)
{
	m_pCachedbmp = NULL;
	m_pImg = NULL;
	m_ImgSize = CSize( 0, 0 );
	m_FileName = _T("");
}

CCachedBmpOut::~CCachedBmpOut(void)
{
	if( m_pCachedbmp )
		delete m_pCachedbmp;
}
BOOL CCachedBmpOut::SetRatio( double Ratio )
{
	CClientDC dc( pWnd );
	Graphics G( dc );

	if( Ratio <= 0 )
		return FALSE;

	m_ImgModiSize.cx = (int)( (double)m_ImgSize.cx * Ratio );
	m_ImgModiSize.cy = (int)( (double)m_ImgSize.cy * Ratio );
	Bitmap* pBmp = new Bitmap( m_ImgModiSize.cx,  m_ImgModiSize.cy, &G );

	Graphics* pG = new Graphics( pBmp );

	pG->DrawImage( m_pImg, 0, 0, m_ImgModiSize.cx,  m_ImgModiSize.cy );	

	if( m_pCachedbmp )
		delete m_pCachedbmp;

	m_pCachedbmp = new CachedBitmap( pBmp ,&G);

	delete pG;
	delete pBmp;

	return TRUE;
}
BOOL CCachedBmpOut::SetHeight( int Height )
{
	if( Height <= 0 )
		return FALSE;

	CClientDC dc( pWnd );
	Graphics G( dc );

	double ratio;

	ratio = (double)Height / (double)m_ImgSize.cy;

	m_ImgModiSize.cx = (LONG)(m_ImgSize.cx * ratio);
	m_ImgModiSize.cy = (LONG)(m_ImgSize.cy * ratio);

	Bitmap* pBmp = new Bitmap( m_ImgModiSize.cx,  m_ImgModiSize.cy, &G );

	Graphics* pG = new Graphics( pBmp );

	pG->DrawImage( m_pImg, 0, 0, m_ImgModiSize.cx,  m_ImgModiSize.cy );	

	if( m_pCachedbmp )
		delete m_pCachedbmp;

	m_pCachedbmp = new CachedBitmap( pBmp ,&G);

	delete pG;
	delete pBmp;

	return TRUE;
}
BOOL CCachedBmpOut::SetWidth( int Width )
{
	if( Width <= 0 )
		return FALSE;

	CClientDC dc( pWnd );
	Graphics G( dc );

	double ratio;

	ratio = (double)Width / (double)m_ImgSize.cx;

	m_ImgModiSize.cx = (LONG)(m_ImgSize.cx * ratio);
	m_ImgModiSize.cy = (LONG)(m_ImgSize.cy * ratio);

	Bitmap* pBmp = new Bitmap( m_ImgModiSize.cx,  m_ImgModiSize.cy, &G );

	Graphics* pG = new Graphics( pBmp );

	pG->DrawImage( m_pImg, 0, 0, m_ImgModiSize.cx,  m_ImgModiSize.cy );	

	if( m_pCachedbmp )
		delete m_pCachedbmp;

	m_pCachedbmp = new CachedBitmap( pBmp ,&G);

	delete pG;
	delete pBmp;

	return TRUE;
}
BOOL CCachedBmpOut::SetSize( CSize sz )
{
	if( sz.cx <= 0 || sz.cy <= 0 )
		return FALSE;

	CClientDC dc( pWnd );
	Graphics G( dc );

	m_ImgModiSize.cx = sz.cx;
	m_ImgModiSize.cy = sz.cy;

	Bitmap* pBmp = new Bitmap( m_ImgModiSize.cx,  m_ImgModiSize.cy, &G );

	Graphics* pG = new Graphics( pBmp );

	pG->DrawImage( m_pImg, 0, 0, m_ImgModiSize.cx,  m_ImgModiSize.cy );	

	if( m_pCachedbmp )
		delete m_pCachedbmp;

	m_pCachedbmp = new CachedBitmap( pBmp ,&G);

	delete pG;
	delete pBmp;

	return TRUE;
}
BOOL CCachedBmpOut::SetSize( int width, int height )
{
	if( width <= 0 || height <= 0 )
		return FALSE;

	CClientDC dc( pWnd );
	Graphics G( dc );

	m_ImgModiSize.cx = width;
	m_ImgModiSize.cy = height;

	Bitmap* pBmp = new Bitmap( m_ImgModiSize.cx,  m_ImgModiSize.cy, &G );

	Graphics* pG = new Graphics( pBmp );

	pG->DrawImage( m_pImg, 0, 0, width,  height );	

	if( m_pCachedbmp )
		delete m_pCachedbmp;

	m_pCachedbmp = new CachedBitmap( pBmp ,&G);

	delete pG;
	delete pBmp;

	return TRUE;
}
void CCachedBmpOut::UpLoadFile( void )
{
	if( m_pImg )
	{
		delete m_pImg;
		m_pImg = NULL;
	}

	if( m_pCachedbmp )
	{
		delete m_pCachedbmp;
		m_pCachedbmp = NULL;
	}
}
BOOL CCachedBmpOut::LoadFile( TCHAR* FileName )
{
	if( m_pImg != NULL )
	{
		delete m_pImg;
		m_pImg = NULL;
	}

	m_pImg = Image::FromFile( FileName );

	m_ImgSize.cx = m_pImg->GetWidth();
	m_ImgSize.cy = m_pImg->GetHeight();

	if( m_ImgSize.cx == 0 || m_ImgSize.cy == 0 )
	{
		delete m_pImg;
		m_pImg = NULL;
		//pWnd->MessageBox( _T("해당 경로에 파일이 없거나 이미지 크기가 0입니다"), _T("SYUCampus - 파일 열기 오류"), MB_OK | MB_ICONSTOP );
		return FALSE;
	}
	else
	{
		m_FileName = FileName;
		return TRUE;
	}
}

void CCachedBmpOut::Init( CWnd *pWnd )
{
	this->pWnd = pWnd;
}

int CCachedBmpOut::GetWidth()
{
	return m_ImgModiSize.cx;
}
int CCachedBmpOut::GetHeight()
{
	return m_ImgModiSize.cy;
}