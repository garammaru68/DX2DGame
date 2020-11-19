#include "MPlayUser.h"

void MPlayUser::Update(D3DXVECTOR3 vDir, float fDistance)
{
	m_fYaw = vDir.y;
	m_fPitch = vDir.x;
	m_fRoll = vDir.z;
	m_fRadius = fDistance;
}
bool MPlayUser::Frame()
{
	D3DXMatrixRotationYawPitchRoll(&m_matWorld, m_fYaw, m_fPitch, m_fRoll);
	m_matWorld._41 = m_vPos.x;
	m_matWorld._42 = m_vPos.y;
	m_matWorld._43 = m_vPos.z;
	m_vLook.x = m_matWorld._31;
	m_vLook.y = m_matWorld._32;
	m_vLook.z = m_matWorld._33;
	m_vRight.x = m_matWorld._11;
	m_vRight.y = m_matWorld._12;
	m_vRight.z = m_matWorld._13;
	m_vUp.x = m_matWorld._21;
	m_vUp.y = m_matWorld._22;
	m_vUp.z = m_matWorld._23;

	D3DXVec3Normalize(&m_vLook, &m_vLook);
	D3DXVec3Normalize(&m_vRight, &m_vRight);
	D3DXVec3Normalize(&m_vUp, &m_vUp);
	return true;
}

void MPlayUser::MoveLook(float fValue)
{
	m_vPos += m_vLook * fValue;
}
void MPlayUser::MoveSide(float fValue)
{
	m_vPos += m_vRight * fValue;
}
void MPlayUser::MoveUp(float fValue)
{
	m_vPos += m_vUp * fValue;
}                                                                                                                                                                     