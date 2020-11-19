#include "MDebugCamera.h"

bool MDebugCamera::Frame()
{
	//D3DXMatrixRotationAxis();
	D3DXMATRIX matRotation;
	D3DXMatrixRotationYawPitchRoll(&matRotation, m_fYaw, m_fPitch, m_fRoll);
	matRotation._41 = m_vPos.x;
	matRotation._42 = m_vPos.y;
	matRotation._43 = m_vPos.z;
	D3DXMatrixInverse(&m_matView, NULL, &matRotation);
	UpdateVector();
	return true;
}
