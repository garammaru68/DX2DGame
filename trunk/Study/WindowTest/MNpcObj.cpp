#include "MNpcObj.h"

bool MNpcObj::Frame()
{
	if (m_fPosY < 0.0f)
	{
		m_fPosY = 0;
		m_fDirY *= -1.0f;
	}
	if (m_fPosY > g_rtClient.bottom)
	{
		m_fPosY = 600;
		m_fDirY *= -1.0f;
	}
	if (m_fPosX < 0.0f)
	{
		m_fPosX = 0;
		m_fDirX *= -1.0f;
	}
	if (m_fPosX > g_rtClient.right)
	{
		m_fPosX = 800;
		m_fDirY *= -1.0f;
	}
	m_fPosX += m_fDirX * g_fSecondPerFrame * 100.0f;
	m_fPosY += m_fDirY * g_fSecondPerFrame * 100.0f;

	SetPos(m_fPosX, m_fPosY);
	return true;
}

MNpcObj::MNpcObj()
{
	m_bDead = false;
}

MNpcObj::~MNpcObj()
{
}
