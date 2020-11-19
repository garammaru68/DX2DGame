#pragma once
#include "MMath.h"
//#include "MObject.h"
#include "MBoxObj.h"

class MCamera
{
public:
	D3DXMATRIX		m_matView;
	D3DXMATRIX		m_matProj;
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vTarget;
	D3DXVECTOR3		m_vLook;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3		m_vRight;
	float			m_fYaw;
	float			m_fPitch;
	float			m_fRoll;
	float			m_fRadius;
	float			m_fRadiusOffset;
public:
	virtual void	UpdateVector();
	D3DXMATRIX		SetViewMatrix(	D3DXVECTOR3 vPos,
									D3DXVECTOR3 vTarget = D3DXVECTOR3(0, 0, 0),
									D3DXVECTOR3 vUp = D3DXVECTOR3(0, 1, 0) );
	D3DXMATRIX		SetProjMatrix(float fFow, float fAspect, float fNear = 1.0f, float fFar = 1000.0f);

public:
	MBoxObj		m_FrustumObj;
	D3DXVECTOR3	m_vFrustum[8];
	M_PLANE		m_Plane[6];
	void CreateFrustum(D3DXMATRIX matView, D3DXMATRIX matProj);
	void CreateFrustumObject(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext);

public:
	virtual bool Init();
	virtual bool Frame();
	virtual void Update(D3DXVECTOR3 vDir, float fDistance);
	virtual void MoveLook(float fValue);
	virtual void MoveSide(float fValue);
	virtual void MoveUp(float fValue);
	MCamera();
};

