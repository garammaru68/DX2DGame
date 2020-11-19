#pragma once
#include "MCore.h"
#include "MPlaneObj.h"
#include "MBoxObject.h"
#include "MDebugCamera.h"
#include "MBackCamera.h"

#define OBJECT_NUM 100

class MFullScreen : public MPlaneObj
{
public:
	ID3D11ShaderResourceView* m_pSRV;
	bool Render()
	{
		PreRender();
		m_pContext->UpdateSubresource(
			m_dxObj.m_pConstantBuffer.Get(),
			0, NULL, &m_cbData, 0, 0);
		if (m_pTexture[0] != nullptr)
			m_pContext->PSSetShaderResources(0, 1, &m_pSRV);

		m_pContext->PSSetSamplers(0, 1, &m_pSamplerState);
		m_pContext->OMSetBlendState(m_pBlendState, 0, 0xff);

		PostRender();
		return true;
	}
};
class Sample : public MCore
{
	MBoxObject	m_BoxObj;
	MBackCamera		m_DirCamera;
	MCamera*    m_pMainCamera;
	int			m_iSelectCam;

	D3DXMATRIX  m_matBoxWorld;
	D3DXMATRIX  m_matPlaneWorld;

	D3DXMATRIX	m_matBox[OBJECT_NUM];
	D3DXVECTOR3 m_vBoxPos[OBJECT_NUM];
	D3DXVECTOR4 m_vBoxColor[OBJECT_NUM];

	float		m_fYaw, m_fPitch, m_fRoll;
	
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);
};
