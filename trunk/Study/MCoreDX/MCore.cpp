#include "MCore.h"

void MCore::CreateDXResource()
{
	IDXGISurface* pSurface = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pSurface);
	m_Write.OnResize(pSurface);
	if (pSurface) pSurface->Release();
}
void MCore::DeleteDXResource()
{
	m_Write.DeleteDXResource();
}
bool MCore::Init() { return true; }
bool MCore::Frame() { return true; }
bool MCore::PreRender()
{
	m_pContext->OMSetRenderTargets(1, &m_pRTV, m_pDSV);
	m_pContext->RSSetViewports(1, &m_vp);

	float clearcolor[4] = { 0.4f,0.3f,0.654f,1 };
	m_pContext->ClearRenderTargetView(m_pRTV, clearcolor);
	m_pContext->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	ApplyRS(m_pContext, MDxState::g_pRSSolidBack);
	ApplyBS(m_pContext, MDxState::g_pBSAlphaBlend);
	ApplySS(m_pContext, MDxState::g_pSamplerState);
	ApplyDSS(m_pContext, MDxState::g_pDSSDepthEnable);

	if (g_InputData.bChangeFillMode)
	{
		ApplyRS(m_pContext, MDxState::g_pRSWireFrameBack);
	}
	if (g_InputData.bChangeCullMode)
	{
		ApplyRS(m_pContext, MDxState::g_pRSSolidNone);
	}
	return true;
}
bool MCore::Render() { return true; }
bool MCore::PostRender()
{
	m_Write.Render();
	m_pSwapChain->Present(0, 0);
	return true;
}
bool MCore::Release() { return true; }

bool MCore::MCoreInit()
{
	m_Timer.Init();
	//I_SoundMgr.Init();
	I_Input.Init();

	if (!SetD3DDevice(
		m_rtClient.right,
		m_rtClient.bottom)) return false;

	HRESULT hr = m_pGIFactory->MakeWindowAssociation(m_hWnd,
		DXGI_MWA_NO_WINDOW_CHANGES |
		DXGI_MWA_NO_ALT_ENTER);
	if (FAILED(hr))
	{
		return false;
	}

	m_Write.Init();

	IDXGISurface* pSurface = nullptr;
	m_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface),
		(void**)&pSurface);
	m_Write.OnResize(pSurface);
	if (pSurface) pSurface->Release();

	//BOOL fullscreen;
	//m_pSwapChain->GetFullscreenState(&fullscreen, NULL);
	//m_pSwapChain->SetFullscreenState(!fullscreen, NULL);

	MDxState::Create(m_pd3dDevice, m_pContext);

	m_Camera.Init();
	m_DirLine.Create(m_pd3dDevice,
		m_pContext,
		L"../../../data/loading.bmp",
		L"../../../data/shader/LineShader.txt");
	m_DirLine.m_pBlendState = MDxState::g_pBSAlphaBlend;
	m_DirLine.m_pSamplerState = MDxState::g_pSamplerState;

	Init();
	return true;
}
bool MCore::MCoreFrame()
{
	m_Timer.Frame();
	I_Input.Frame();
	//I_SoundMgr.Frame();

	if (g_InputData.bExit)
	{
		m_bExit = true;
		return false;
	}
	Frame();
	return true;
}
bool MCore::MCoreRender()
{
	PreRender();
	Render();

	//m_Timer.Render();
	//I_SoundMgr.Render();
	//I_Input.Render();

	T_STR strBuffer = L"GameTime";
	strBuffer += m_Timer.m_csBuffer;
	m_Write.Draw(1, strBuffer.c_str(), m_rtClient);

	m_DirLine.SetMatrix(NULL,
		&m_Camera.m_matView,
		&m_Camera.m_matProj);
	m_DirLine.Render();

	PostRender();
	return true;
}
bool MCore::MCoreRelease()
{
	MDxState::Release();
	Release();
	m_Timer.Release();
	I_Input.Release();
	//I_SoundMgr.Release();
	m_DirLine.Release();
	MDevice::ReleaseDevice();
	return true;
}
bool MCore::MRun()
{
	MCoreInit();
	while (!m_bExit)
	{
		if (WinRun())
		{
			MCoreFrame();
			MCoreRender();
		}
	}
	MCoreRelease();
	return true;
}
MCore::MCore()
{
	m_bExit = false;
}
MCore::~MCore()
{

}