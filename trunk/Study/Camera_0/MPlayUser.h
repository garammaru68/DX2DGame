#pragma once
#include "MBoxObj.h"
class MPlayUser : public MBoxObj
{
public:
	virtual bool Frame();
	virtual void Update(D3DXVECTOR3 vDir, float fDistance);
	virtual void MoveLook(float fValue);
	virtual void MoveSide(float fValue);
	virtual void MoveUp(float fValue);
};

