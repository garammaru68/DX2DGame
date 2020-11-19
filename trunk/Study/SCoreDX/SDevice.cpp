#include "SDevice.h"

namespace SBASIS
{
	ID3D11Device*		g_pd3dDevice = NULL;
	ID3D11DeviceContext*	g_pImmediateContext = NULL;
	UINT					g_iClientWidth;
	UINT					g_iClientHeight;
}
HRESULT SDevice::InitDevice(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen)
{
	HRESULT hr = S_OK;
	if (FAILED(hr = CreateDevice()))
	{
		MessageBox(0, _T("CreateDevice 실패"), _T("Fatal error"), MB_OK);
		return hr;
	}
	if (FAILED(hr = CreateSwapChain(hWnd, iWidth, iHeight, IsFullScreen)))
	{
		MessageBox(0, _T("CreateSwapChain 실패"), _T("Fatal error"), MB_OK);
		return hr;
	}
	if (FAILED(hr = SetRenderTargetView()))
	{
		MessageBox(0, _T("SetRenderTargetView 실패"), _T("Fatal error"), MB_OK);
		return hr;
	}
	if (FAILED(hr = SetViewPort()))
	{
		MessageBox(0, _T("SetViewPort 실패"), _T("Fatal error"), MB_OK);
		return hr;
	}
	if (FAILED(hr = CreateDxResource()))
	{
		return hr;
	}
	if (FAILED(hr = GetGIFactory()->MakeWindowAssociation(hWnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER)))
	{
		return hr;
	}
	return hr;
}

BOOL SDevice::GetFullScreenFlag()
{
	return m_IsFullScreenMode;
}

void SDevice::SetFullScreenFlag( BOOL bFlag)
{
	m_IsFullScreenMode = bFlag;
}
HRESULT SDevice::ResizeDevice(UINT iWidth, UINT iHeight)
{
	if (m_pd3dDevice == NULL) return true;
	HRESULT hr;

	if (FAILED(hr = DeleteDxResource()))
	{
		return hr;
	}

	m_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
	m_DefaultRT.m_pRenderTargetView.ReleaseAndGetAddressOf();

	if (FAILED(hr = m_pSwapChain->ResizeBuffers(m_SwapChainDesc.BufferCount, iWidth, iHeight, m_SwapChainDesc.BufferDesc.Format, m_SwapChainDesc.Flags)))
	{
		return hr;
	}
}
void SDevice::DeleteDXResource()
{
}
void SDevice::ResizeDevice(UINT width, UINT height)
{
	if (m_pd3dDevice == nullptr) return;
	//ReleaseDevice();
	//SetD3DDevice(width, height
	DeleteDXResource();

	m_pContext->OMSetRenderTargets(0, NULL, NULL);
	if (m_pRTV) m_pRTV->Release();

	DXGI_SWAP_CHAIN_DESC currentSD;
	m_pSwapChain->GetDesc(&currentSD);
	HRESULT hr = m_pSwapChain->ResizeBuffers(
		currentSD.BufferCount,
		width,
		height,
		currentSD.BufferDesc.Format,
		currentSD.Flags);
	if (FAILED(hr)) return;

	CreateRenderTarget();
	CreateDepthStencilView();
	CreateViewport();

	CreateDXResource();
}
bool SDevice::SetD3DDevice(UINT width, UINT height)
{
	if (!CreateDevice()) return false;
	if (!CreateGIFactory()) return false;
	
	if (!CreateSwapChain(width, height)) return false;
	if (!CreateRenderTarget()) return false;
	if (!CreateDepthStencilView()) return false;
	if (!CreateViewport()) return false;
	return true;
}
bool SDevice::CreateGIFactory()
{
	if (m_pd3dDevice == NULL) return E_FAIL;
	HRESULT hr;
	IDXGIDevice * pDXGIDevice;
	hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);

	IDXGIFactory * pDXGIAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIFactory), (void **)&pDXGIAdapter);

	IDXGIFactory * pIDXGIFactory;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&m_pGIFactory);

	pDXGIDevice->Release();
	pDXGIAdapter->Release();
	return true;
}
bool SDevice::CreateDevice()
{
	// 1번 : 디바이스 생성

	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif _DEBUG
	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FeatureLevel;
	D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;

	HRESULT hr = D3D11CreateDevice(
		NULL,
		DriverType,
		NULL,
		Flags,
		&pFeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&m_pd3dDevice,
		&FeatureLevel,
		&m_pContext);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}
bool SDevice::CreateSwapChain(UINT width, UINT height)
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.OutputWindow = g_hWnd;
	sd.Windowed = TRUE;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SampleDesc.Count = 1;
	//sd.flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr = m_pGIFactory->CreateSwapChain(m_pd3dDevice, &sd, &m_pSwapChain);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}
bool SDevice::CreateRenderTarget()
{
	// 2번 랜더타겟 뷰 생성
	ID3D11Texture2D* pBackBuffer = nullptr;
	HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	if (FAILED(hr))
	{
		return false;
	}
	if (FAILED(m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV)))
	{
		return false;
	}
	pBackBuffer->Release();

	m_pSwapChain->GetDesc(&m_SwapChainDesc);

	return true;
}
bool SDevice::CreateDepthStencilView()
{
	HRESULT hr;
	ComPtr<ID3D11Texture2D> pDSTex = nullptr;
	D3D11_TEXTURE2D_DESC td;
	td.Width = m_SwapChainDesc.BufferDesc.Width;
	td.Height = m_SwapChainDesc.BufferDesc.Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	hr = m_pd3dDevice->CreateTexture2D(&td, NULL, pDSTex.GetAddressOf());

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	hr = m_pd3dDevice->CreateDepthStencilView(pDSTex.Get(), &dsvd, &m_pDSV);
	return true;
}
bool SDevice::CreateViewport()
{
	DXGI_SWAP_CHAIN_DESC currentSD;
	m_pSwapChain->GetDesc(&currentSD);
	// 3번 뷰포트 세팅
	m_vp.TopLeftX = 0;
	m_vp.TopLeftY = 0;
	m_vp.Width	= currentSD.BufferDesc.Width;
	m_vp.Height = currentSD.BufferDesc.Height;
	m_vp.MinDepth = 0;
	m_vp.MaxDepth = 1;
	m_pContext->RSSetViewports(1, &m_vp);
	return true;
}
bool SDevice::ReleaseDevice()
{
	if (m_pRTV)m_pRTV->Release();
	if (m_pDSV)m_pDSV->Release();
	if (m_pSwapChain)m_pSwapChain->Release();
	if (m_pd3dDevice)m_pd3dDevice->Release();
	if (m_pContext)m_pContext->Release();
	if (m_pGIFactory)m_pGIFactory->Release();
	return true;
}

SDevice::SDevice()
{
	m_pGIFactory = nullptr;
	m_pd3dDevice = nullptr;
	m_pContext = nullptr;
	m_pSwapChain = nullptr;
	m_pRTV = nullptr;
}
SDevice::~SDevice()
{
}