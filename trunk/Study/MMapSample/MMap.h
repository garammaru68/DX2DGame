#pragma once
#include "MObject.h"

class MMap : public MObject
{
public:
	int m_iNumRows;
	int m_iNumCols;
	int m_iNumCellRows;
	int m_iNumCellCols;
	float m_fCellDistance;
	int m_iNumFaces;
public:
	virtual void CreateVertexData();
	virtual void CreateIndexData();
	virtual float GetHeightMap(int iIndex);
};

