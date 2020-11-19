#pragma once
#include "MCore.h"
#include "MPlaneObj.h"
#include "MPlayUser.h"
#include "MDxRT.h"
#include "MDebugCamera.h"
#include "MBackCamera.h"
#include "MMap.h"

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
	MDxRT		m_DxRT;
	MMap		m_GameMap;
	MPlaneObj	m_PlaneObj;
	MPlayUser	m_BoxObj;
	MFullScreen m_FullScreenObj;
	MBackCamera		m_DirCamera[4];
	MCamera*    m_pMainCamera;
	int			m_iSelectCam;

	D3DXMATRIX  m_matBoxWorld;
	D3DXMATRIX  m_matPlaneWorld;

	float		m_fYaw, m_fPitch, m_fRoll;
public:
	bool Init()
	{
		m_fYaw = m_fPitch = m_fRoll = 0;
		m_iSelectCam = 0;
		RECT rt = { 0,0,800, 600 };
		m_PlaneObj.SetScreenRect(rt);
		m_PlaneObj.Create(m_pd3dDevice,
			m_pContext,
			L"../../../data/gg.bmp",
			L"../../../data/Shader/ShapeShader.txt");
		m_PlaneObj.m_pBlendState = MDxState::g_pBSAlphaBlend;
		m_PlaneObj.m_pSamplerState = MDxState::g_pSamplerState;

		m_BoxObj.Create(m_pd3dDevice,
			m_pContext,
			L"../../../data/loading.bmp",
			L"../../../data/Shader/ShapeShader.txt");
		m_BoxObj.m_pBlendState = MDxState::g_pBSAlphaBlend;
		m_BoxObj.m_pSamplerState = MDxState::g_pSamplerState;

		m_GameMap.Create(m_pd3dDevice,
			m_pContext,
			L"../../../data/gg.bmp",
			L"../../../data/Shader/ShapeShader.txt");
		m_GameMap.m_pBlendState = MDxState::g_pBSAlphaBlend;
		m_GameMap.m_pSamplerState = MDxState::g_pSamplerState;


		//m_FullScreenObj.SetScreenRect(rt);
		m_FullScreenObj.Create(m_pd3dDevice,
			m_pContext,
			L"../../../data/loading.bmp",
			L"../../../data/Shader/ShapeShader.txt");
		m_FullScreenObj.m_pBlendState = MDxState::g_pBSAlphaBlend;
		m_FullScreenObj.m_pSamplerState = MDxState::g_pSamplerState;

		m_DxRT.Create(m_pd3dDevice, 1024, 1024);

		for (int iCam = 0; iCam < 4; iCam++)
		{
			m_DirCamera[iCam].SetProjMatrix(
				MBASIS_PI * 0.25f,
				g_rtClient.right / g_rtClient.bottom);
		}

		m_DirCamera[0].SetViewMatrix(D3DXVECTOR3(0, 5, -5.0f));
		m_DirCamera[1].SetViewMatrix(D3DXVECTOR3(5, 5, 0.0f));
		m_DirCamera[2].SetViewMatrix(D3DXVECTOR3(0, 50, -0.01f));
		m_DirCamera[3].SetViewMatrix(D3DXVECTOR3(5, 5, -5.0f));


		D3DXMatrixIdentity(&m_matBoxWorld);
		m_pMainCamera = &m_DirCamera[m_iSelectCam];

		m_pMainCamera->CreateFrustumObject(m_pd3dDevice, m_pContext);
		return true;
	}
	bool Frame()
	{
		if (I_Input.KeyCheck(DIK_P) == KEY_PUSH)
		{
			++m_iSelectCam;
			if (m_iSelectCam >= 4) m_iSelectCam = 0;
			m_pMainCamera = &m_DirCamera[m_iSelectCam];
		}
		if (g_InputData.bWKey)
		{
			m_BoxObj.m_vPos = m_BoxObj.m_vPos + m_BoxObj.m_vLook * g_fSecondPerFrame;
			m_matBoxWorld._41 = m_BoxObj.m_vPos.x;
			m_matBoxWorld._42 = m_BoxObj.m_vPos.y;
			m_matBoxWorld._43 = m_BoxObj.m_vPos.z;
			m_pMainCamera->m_vTarget = m_BoxObj.m_vPos;
			m_BoxObj.MoveLook(10.0f* g_fSecondPerFrame);
		}
		if (g_InputData.bSKey)
		{
			m_BoxObj.m_vPos = m_BoxObj.m_vPos - m_BoxObj.m_vLook * g_fSecondPerFrame;
			m_matBoxWorld._41 = m_BoxObj.m_vPos.x;
			m_matBoxWorld._42 = m_BoxObj.m_vPos.y;
			m_matBoxWorld._43 = m_BoxObj.m_vPos.z;
			m_pMainCamera->m_vTarget = m_BoxObj.m_vPos;
			m_BoxObj.MoveLook(-10.0f* g_fSecondPerFrame);
		}
		if (g_InputData.bAKey)
		{
			m_BoxObj.m_vPos = m_BoxObj.m_vPos - m_BoxObj.m_vRight * g_fSecondPerFrame;
			m_matBoxWorld._41 = m_BoxObj.m_vPos.x;
			m_matBoxWorld._42 = m_BoxObj.m_vPos.y;
			m_matBoxWorld._43 = m_BoxObj.m_vPos.z;
			m_pMainCamera->m_vTarget = m_BoxObj.m_vPos;
			m_BoxObj.MoveSide(-10.0f* g_fSecondPerFrame);
		}
		if (g_InputData.bDKey)
		{
			m_BoxObj.m_vPos = m_BoxObj.m_vPos + m_BoxObj.m_vRight * g_fSecondPerFrame;
			m_matBoxWorld._41 = m_BoxObj.m_vPos.x;
			m_matBoxWorld._42 = m_BoxObj.m_vPos.y;
			m_matBoxWorld._43 = m_BoxObj.m_vPos.z;
			m_pMainCamera->m_vTarget = m_BoxObj.m_vPos;
			m_BoxObj.MoveSide(10.0f* g_fSecondPerFrame);
		}
		if (g_InputData.bQKey)
		{
			m_pMainCamera->MoveUp(-10.0f* g_fSecondPerFrame);
		}
		if (g_InputData.bEKey)
		{
			m_pMainCamera->MoveUp(10.0f* g_fSecondPerFrame);
		}

		if (g_InputData.bLeftHold)
		{
			m_fYaw += D3DXToRadian(g_InputData.iMouseValue[0] * 0.1f);
			m_fPitch += D3DXToRadian(g_InputData.iMouseValue[1] * 0.1f);
		}

		m_pMainCamera->Update(D3DXVECTOR3(m_fPitch, m_fYaw, m_fRoll), 10.0f);
		m_pMainCamera->Frame();

		m_BoxObj.Update(D3DXVECTOR3(0, m_fYaw, 0), 10.0f);
		m_BoxObj.Frame();
		return true;
	}
	
	bool Render()
	{
		//m_DxRT.Begin(m_pContext);
		//	m_PlaneObj.SetMatrix(NULL, &m_Camera.m_matView, &m_Camera.m_matProj);
		//	m_PlaneObj.Render();
		//m_DxRT.End(m_pContext);		
		//ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		//m_pContext->PSSetShaderResources(0, 16, pSRVs);

		//PreRender();
		//m_FullScreenObj.SetMatrix(NULL,	NULL,	NULL);
		//m_FullScreenObj.m_pSRV = m_DxRT.m_pRT_SRV.Get();
		//m_FullScreenObj.Render();
		m_GameMap.SetMatrix(NULL, &m_pMainCamera->m_matView,
			&m_pMainCamera->m_matProj);
		m_GameMap.Render();

		m_pMainCamera->m_FrustumObj.SetMatrix(NULL,
			&m_DirCamera[2].m_matView,
			&m_pMainCamera->m_matProj);
		m_pMainCamera->m_FrustumObj.UpdateVertexData(
			m_pMainCamera->m_vFrustum);
		ApplyRS(m_pContext, m_pMainCamera->m_FrustumObj.m_pRS);
		ApplyDSS(m_pContext, m_pMainCamera->m_FrustumObj.m_pDS);
		m_pMainCamera->m_FrustumObj.Render();

		//m_BoxObj.SetMatrix(NULL, &m_pMainCamera->m_matView,
		//							&m_pMainCamera->m_matProj);
		//m_BoxObj.Render();
		return true;
	}
	bool Release()
	{
		m_PlaneObj.Release();
		m_BoxObj.Release();
		m_FullScreenObj.Release();
		return true;
	}
	void ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext)
	{
		if (pd3dDeviceContext == NULL) return;

		ID3D11ShaderResourceView* pSRVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		ID3D11RenderTargetView* pRTVs[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		ID3D11DepthStencilView* pDSV = NULL;
		ID3D11Buffer* pBuffers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		ID3D11SamplerState* pSamplers[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		UINT StrideOffset[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

		// Shaders
		pd3dDeviceContext->VSSetShader(NULL, NULL, 0);
		pd3dDeviceContext->HSSetShader(NULL, NULL, 0);
		pd3dDeviceContext->DSSetShader(NULL, NULL, 0);
		pd3dDeviceContext->GSSetShader(NULL, NULL, 0);
		pd3dDeviceContext->PSSetShader(NULL, NULL, 0);

		// IA clear
		pd3dDeviceContext->IASetVertexBuffers(0, 16, pBuffers, StrideOffset, StrideOffset);
		pd3dDeviceContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);
		pd3dDeviceContext->IASetInputLayout(NULL);

		// Constant buffers
		pd3dDeviceContext->VSSetConstantBuffers(0, 14, pBuffers);
		pd3dDeviceContext->HSSetConstantBuffers(0, 14, pBuffers);
		pd3dDeviceContext->DSSetConstantBuffers(0, 14, pBuffers);
		pd3dDeviceContext->GSSetConstantBuffers(0, 14, pBuffers);
		pd3dDeviceContext->PSSetConstantBuffers(0, 14, pBuffers);

		// Resources
		pd3dDeviceContext->VSSetShaderResources(0, 16, pSRVs);
		pd3dDeviceContext->HSSetShaderResources(0, 16, pSRVs);
		pd3dDeviceContext->DSSetShaderResources(0, 16, pSRVs);
		pd3dDeviceContext->GSSetShaderResources(0, 16, pSRVs);
		pd3dDeviceContext->PSSetShaderResources(0, 16, pSRVs);

		// Samplers
		pd3dDeviceContext->VSSetSamplers(0, 16, pSamplers);
		pd3dDeviceContext->HSSetSamplers(0, 16, pSamplers);
		pd3dDeviceContext->DSSetSamplers(0, 16, pSamplers);
		pd3dDeviceContext->GSSetSamplers(0, 16, pSamplers);
		pd3dDeviceContext->PSSetSamplers(0, 16, pSamplers);

		// Render targets
		pd3dDeviceContext->OMSetRenderTargets(8, pRTVs, pDSV);

		// States
		FLOAT blendFactor[4] = { 0,0,0,0 };
		pd3dDeviceContext->OMSetBlendState(NULL, blendFactor, 0xFFFFFFFF);
		pd3dDeviceContext->OMSetDepthStencilState(NULL, 0);
		pd3dDeviceContext->RSSetState(NULL);
	}
};
MWINGAME;