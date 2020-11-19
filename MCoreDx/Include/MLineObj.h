#pragma once
#include "MObject.h"
class MLineObj : public MObject
{
public:
	virtual void	CreateVertexData();
	virtual void	CreateIndexData();
	virtual bool	Draw(ID3D11DeviceContext* pContext,
		D3DXVECTOR3 vStart,
		D3DXVECTOR3 vEnd,
		D3DXVECTOR4 Color);
};

class MDirectionLineObj : public MObject
{
public:
	virtual void	CreateVertexData();
	virtual void	CreateIndexData();
};