#pragma once

// CPanoFileData ��� ����Դϴ�.

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


