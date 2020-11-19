#include "Sample.h"
bool Sample::Init()
{
	m_fYaw = m_fPitch = m_fRoll = 0;

	//m_iSelectCam = 0;
	//for (int iCam = 0; iCam < 4; iCam++)
	//{
	//	m_DirCamera[iCam].SetProjMatrix(
	//		MBASIS_PI * 0.25f,
	//		g_rtClient.right / g_rtClient.bottom);
	//}
	m_DirCamera.SetProjMatrix(MBASIS_PI * 0.25f, g_rtClient.right / g_rtClient.bottom);

	m_DirCamera.SetViewMatrix(D3DXVECTOR3(0, 5, -5.0f));
	m_DirCamera.SetViewMatrix(D3DXVECTOR3(5, 5, 0.0f));
	m_DirCamera.SetViewMatrix(D3DXVECTOR3(0, 50, -0.01f));
	m_DirCamera.SetViewMatrix(D3DXVECTOR3(5, 5, -5.0f));

	D3DXMatrixIdentity(&m_matBoxWorld);
	//m_pMainCamera = &m_DirCamera[m_iSelectCam];
	m_pMainCamera = &m_DirCamera;

	SAFE_NEW(m_BoxObj, MBoxObject);
	m_pMainCamera->CreateFrustumObject(m_pd3dDevice, m_pContext);
	return true;
}
bool Sample::Frame()
{
	//if (I_Input.KeyCheck(DIK_P) == KEY_PUSH)
	//{
	//	++m_iSelectCam;
	//	if (m_iSelectCam >= 4) m_iSelectCam = 0;
	//	m_pMainCamera = &m_DirCamera[m_iSelectCam];
	//}
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
		m_BoxObj.m_vPos = m_BoxObj.m_vPos - m_BoxObj.m_vUp * g_fSecondPerFrame;
		m_matBoxWorld._41 = m_BoxObj.m_vPos.x;
		m_matBoxWorld._42 = m_BoxObj.m_vPos.y;
		m_matBoxWorld._43 = m_BoxObj.m_vPos.z;
		m_pMainCamera->m_vTarget = m_BoxObj.m_vPos;
		m_pMainCamera->MoveUp(-10.0f* g_fSecondPerFrame);
	}
	if (g_InputData.bEKey)
	{
		m_BoxObj.m_vPos = m_BoxObj.m_vPos + m_BoxObj.m_vUp * g_fSecondPerFrame;
		m_matBoxWorld._41 = m_BoxObj.m_vPos.x;
		m_matBoxWorld._42 = m_BoxObj.m_vPos.y;
		m_matBoxWorld._43 = m_BoxObj.m_vPos.z;
		m_pMainCamera->m_vTarget = m_BoxObj.m_vPos;
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

bool Sample::Render()
{
	//m_pMainCamera->m_FrustumObj.SetMatrix(NULL,
	//	&m_DirCamera[2].m_matView,
	//	&m_pMainCamera->m_matProj);

	m_pMainCamera->m_FrustumObj.SetMatrix(NULL,
		&m_DirCamera.m_matView,
		&m_pMainCamera->m_matProj);

	m_pMainCamera->m_FrustumObj.UpdateVertexData(
		m_pMainCamera->m_vFrustum);
	ApplyRS(m_pContext, m_pMainCamera->m_FrustumObj.m_pRS);
	ApplyDSS(m_pContext, m_pMainCamera->m_FrustumObj.m_pDS);
	m_pMainCamera->m_FrustumObj.Render();

	return true;
}
bool Sample::Release()
{
	m_BoxObj.Release();
	return true;
}
void Sample::ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext)
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
MWINGAME;