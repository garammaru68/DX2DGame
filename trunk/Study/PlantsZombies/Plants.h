#pragma once
#include "MObject.h"

class Plants : public MObject
{
	float ShooterX;
	float ShooterY;
	MObject* m_PeaShooter;
public:
	bool Render(HDC hOffScreenDC);
public:
	Plants();
	~Plants();
};

