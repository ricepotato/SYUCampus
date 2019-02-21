#pragma once

// CPanoFileData 명령 대상입니다.

class CPanoFileData : public CObject
{
public:
	CPanoFileData();
	~CPanoFileData();

	TCHAR m_FileName[ MAX_PATH ];
	CPoint m_TopViewPt;
	int m_nEast;
	CPoint m_SatelliteTopViewPt;
	int m_nSatelliteEast;
};


