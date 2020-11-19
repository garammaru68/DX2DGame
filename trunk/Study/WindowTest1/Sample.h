#pragma once
#include "MCore.h"
#include "MHeroObj.h"
#include "MNpcObj.h"

struct MProjectile
{
	MPoint	pos;
	RECT	rtCollision;
	MSphere	m_Sphere;
	float	fLifeTime;
	RECT	rtDest;
	void	SetPos(MPoint p)
	{
		SetPos(p.x, p.y);
	}
	void	SetPos(float x, float y)
	{
		pos.x = x;
		pos.y = y;
		rtCollision.left	= pos.x;
		rtCollision.top		= pos.y;
		rtCollision.right	= rtCollision.left + rtDest.right;
		rtCollision.bottom	= rtCollision.top + rtDest.bottom;

		m_Sphere.vCenter.x = (rtCollision.left + rtCollision.right) / 2;
		m_Sphere.vCenter.y = (rtCollision.top + rtCollision.bottom) / 2;
		float fA = rtCollision.right - m_Sphere.vCenter.x;
		float fB = m_Sphere.vCenter.y - rtCollision.top;
		m_Sphere.fRadius = sqrt(fA * fA + fB * fB);
	}
};
class Sample : public MCore
{
	int				m_iLifeCounter;
	MHeroObj		m_Hero;
	MObject			m_BackGround;
	MObject			m_Projectile;
	list<MNpcObj*>		m_NpcList;
	list<MProjectile>	m_ProjectileList;

	float	m_fNpcTime;
	float	m_fHeroLifeTime;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	MNpcObj*	AddNpc();
	void		SetLifeCounter();
public:
	Sample();
	~Sample();
};

