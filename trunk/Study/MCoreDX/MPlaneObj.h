#pragma once
#include "MObject.h"
class MPlaneObj : public MObject
{
public:
	virtual void	CreateVertexData();
	virtual void	CreateIndexData();
	//void CreateScreen2NDCVertexData();
};

