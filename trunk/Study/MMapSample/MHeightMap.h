#pragma once
#include "MMap.h"

class MHeightMap : public MMap
{
public:
	vector<float>	m_fHeightList;
public:
	bool CreateHeightMap(ID3D11Device* pd3dDevice, const TCHAR* szFileName);
	float GetHeightMap(int iIndex);
public:
	MHeightMap();
	virtual ~MHeightMap();
};

