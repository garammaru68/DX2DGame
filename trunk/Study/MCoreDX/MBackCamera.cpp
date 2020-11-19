#include "MBackCamera.h"
bool MBackCamera::Frame()
{
	D3DXMATRIX matRotation;
	D3DXMatrixRotationYawPitchRoll(&matRotation, m_fYaw, m_fPitch, m_fRoll);

	//m_fRadius += m_fRadius * g_InputData.iMouseValue[2];
	//m_fRadius += m_fRadiusOffset * 0.5f;
	m_fRadius = __min(100.0f, m_fRadius);
	m_fRadius = __max(3.0f, m_fRadius);

	D3DXVECTOR3 vLocalLook = D3DXVECTOR3(0, 0, 1);
	D3DXVECTOR3 vLocalUp = D3DXVECTOR3(0, 1, 0);
	D3DXVECTOR3 vWorldLook;
	D3DXVECTOR3 vWorldUp;
	D3DXVec3TransformCoord(&vWorldLook, &vLocalLook, &matRotation);
	D3DXVec3TransformCoord(&vWorldUp, &vLocalUp, &matRotation);
	m_vPos = m_vTarget - vWorldLook * m_fRadius;
	m_vPos += vWorldUp * 10.0f;
	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vTarget, &vWorldUp);

	UpdateVector();
	return true;
}