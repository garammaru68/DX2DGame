#pragma once
#include "MObject.h"
class MBoxObj : public MObject
{
public:
	virtual void	CreateVertexData();
	virtual void	CreateIndexData();
	void UpdateVertexData(D3DXVECTOR3* vList);
};

