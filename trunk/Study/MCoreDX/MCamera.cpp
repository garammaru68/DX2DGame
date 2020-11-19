#include "MCamera.h"
#include "MDxState.h"

void MCamera::CreateFrustumObject(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext)
{
	m_FrustumObj.Create(pd3dDevice, pContext, NULL, L"../../../data/Shader/VertexColorShader.txt");
	m_FrustumObj.m_pBlendState = MDxState::g_pBSAlphaBlend;
	m_FrustumObj.m_pSamplerState = MDxState::g_pSamplerState;
	m_FrustumObj.m_pRS = MDxState::g_pRSSolidNone;
	m_FrustumObj.m_pDS = MDxState::g_pDSSDepthDisable;
}
void MCamera::CreateFrustum(D3DXMATRIX m_matView, D3DXMATRIX m_matProj)
{
	D3DXMATRIX matViewProj = m_matView * m_matProj;
	D3DXMATRIX matInvViewProj;
	D3DXMatrixInverse(&matInvViewProj, NULL, &matViewProj);

	m_vFrustum[0] = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	m_vFrustum[1] = D3DXVECTOR3(-1.0f,  1.0f, 0.0f);
	m_vFrustum[2] = D3DXVECTOR3( 1.0f,  1.0f, 0.0f);
	m_vFrustum[3] = D3DXVECTOR3( 1.0f, -1.0f, 0.0f);
	m_vFrustum[4] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	m_vFrustum[5] = D3DXVECTOR3(-1.0f,  1.0f, 1.0f);
	m_vFrustum[6] = D3DXVECTOR3( 1.0f,  1.0f, 1.0f);
	m_vFrustum[7] = D3DXVECTOR3( 1.0f, -1.0f, 1.0f);
	for (int v = 0; v < 8; v++)
	{
		D3DXVec3TransformCoord(&m_vFrustum[v], &m_vFrustum[v], &matInvViewProj);
	}
	// left
	m_Plane[0].CreatePlane(m_vFrustum[0], m_vFrustum[1], m_vFrustum[5]);
	// right
	m_Plane[1].CreatePlane(m_vFrustum[7], m_vFrustum[6], m_vFrustum[2]);
	// front
	m_Plane[2].CreatePlane(m_vFrustum[3], m_vFrustum[2], m_vFrustum[1]);
	// back
	m_Plane[3].CreatePlane(m_vFrustum[4], m_vFrustum[5], m_vFrustum[6]);
	// top
	m_Plane[4].CreatePlane(m_vFrustum[2], m_vFrustum[6], m_vFrustum[5]);
	// down
	m_Plane[5].CreatePlane(m_vFrustum[3], m_vFrustum[0], m_vFrustum[4]);
}
void MCamera::UpdateVector()
{
	m_vLook.x = m_matView._13;
	m_vLook.x = m_matView._23;
	m_vLook.x = m_matView._33;
	m_vRight.x = m_matView._11;
	m_vRight.x = m_matView._21;
	m_vRight.x = m_matView._31;
	m_vUp.x = m_matView._12;
	m_vUp.x = m_matView._22;
	m_vUp.x = m_matView._32;

	D3DXVec3Normalize(&m_vLook, &m_vLook);
	D3DXVec3Normalize(&m_vRight, &m_vRight);
	D3DXVec3Normalize(&m_vUp, &m_vUp);

	CreateFrustum(m_matView, m_matProj);
}
D3DXMATRIX MCamera::SetViewMatrix(D3DXVECTOR3 vPos, D3DXVECTOR3 vTarget, D3DXVECTOR3 vUp)
{
	m_vPos = vPos;
	m_vTarget = vTarget;
	m_vUp = vUp;
	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vTarget, &m_vUp);
//	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vTarget, &vUp);

	UpdateVector();
	return m_matView;
}
D3DXMATRIX MCamera::SetProjMatrix(float fFow, float fAspect, float fNear, float fFar)
{
	D3DXMatrixPerspectiveFovLH(&m_matProj, fFow, fAspect, fNear, fFar);
	return m_matProj;
}

bool MCamera::Init()
{
	m_vPos = D3DXVECTOR3(0, 0, -5.0f);
	m_vTarget = D3DXVECTOR3(0, 0, 0.0f);
	m_vUp = D3DXVECTOR3(0, 1, 0.0f);
	return true;
}
void MCamera::Update(D3DXVECTOR3 vDir, float fDistance)
{
	m_fYaw = vDir.y;
	m_fPitch = vDir.x;
	m_fRoll = vDir.z;
	m_fRadiusOffset = fDistance;
}
bool MCamera::Frame()
{
	SetViewMatrix(m_vPos, m_vTarget);
	return true;
}

void MCamera::MoveLook(float fValue)
{
	m_vPos += m_vLook * fValue;
}
void MCamera::MoveSide(float fValue)
{
	m_vPos += m_vRight * fValue;
}
void MCamera::MoveUp(float fValue)
{
	m_vPos += m_vUp * fValue;
}

MCamera::MCamera()
{
	m_vPos = D3DXVECTOR3(0, 0, -5.0f);
	m_vTarget = D3DXVECTOR3(0, 0, 0.0f);
	m_vUp = D3DXVECTOR3(0, 1, 0.0f);
	m_fYaw = 0.0f;
	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
	m_fRadius = 10.0f;
	m_fRadiusOffset = 0.0f;
}