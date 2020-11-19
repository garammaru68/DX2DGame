#pragma once
#include "MFrustum.h"
#include "MBoxObj.h"
class MCamera : public MFrustum
{
public:
	D3DXVECTOR3		m_vModelCenter;
	D3DXMATRIX		m_mModelLastRot;
	D3DXMATRIX		m_mMdelRot;

	float			m_fSpeed;
public:
	D3DXQUATERNION	m_qRotation;
	D3DXVECTOR3		m_vPosDelta;

	D3DXMATRIX		m_matWorld;
	D3DXMATRIX		
};
class MPlayUser : public MBoxObj
{
public:
	virtual bool Frame();
	virtual void Update(D3DXVECTOR3 vDir, float fDistance);
	virtual void MoveLook(float fValue);
	virtual void MoveSide(float fValue);
	virtual void MoveUp(float fValue);
};

