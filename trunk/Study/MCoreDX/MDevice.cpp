#include "MDevice.h"

void MDevice::CreateDXResource()
{
}
void MDevice::DeleteDXResource()
{
}
void MDevice::ResizeDevice(UINT width, UINT height)
{
	if (m_pd3dDevice == nullptr) return;

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
	CreateViewport();

	CreateDXResource();
}
bool MDevice::SetD3DDevice(UINT width, UINT height)
{
	if (!CreateDevice()) return false;
	if (!CreateGIFactory()) return false;
	if (!CreateDepthStencilView()) return false;
	if (!CreateSwapChain(width, height)) return false;
	if (!CreateRenderTarget()) return false;
	if (!CreateViewport()) return false;
	return true;
}
bool MDevice::CreateGIFactory()
{
	if (m_pd3dDevice == NULL) return E_FAIL;
	HRESULT hr;
	IDXGIDevice* pDXGIDevice;
	hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);

	IDXGIAdapter* pDXGIAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);

	IDXGIFactory* pIDXGIFactory;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory),
		(void **)&m_pGIFactory);

	pDXGIDevice->Release();
	pDXGIAdapter->Release();
	return true;
}
bool MDevice::CreateDevice()
{
	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
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
bool MDevice::CreateSwapChain(UINT width, UINT height)
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = 800;
	sd.BufferDesc.Height = 600;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.OutputWindow = g_hWnd;
	sd.Windowed = TRUE;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SampleDesc.Count = 1;

	HRESULT hr = m_pGIFactory->CreateSwapChain(m_pd3dDevice, &sd, &m_pSwapChain);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}
bool MDevice::CreateRenderTarget()
{
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
	m_pContext->OMSetRenderTargets(1, &m_pRTV, NULL);

	return true;
}
bool MDevice::CreateDepthStencilView()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture;
	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Width = 800;// g_rtClient.right;
	textureDesc.Height = 600;// g_rtClient.bottom;
	textureDesc.MipLevels = 1u;
	textureDesc.ArraySize = 1u;
	textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textureDesc.SampleDesc.Count = 1u;
	textureDesc.SampleDesc.Quality = 0u;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = FALSE;
	textureDesc.MiscFlags = FALSE;

	m_pd3dDevice->CreateTexture2D(&textureDesc, nullptr, pTexture.GetAddressOf());

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	dsvDesc.Flags = 0u;
	dsvDesc.Texture2D.MipSlice = 0u;

	m_pd3dDevice->CreateDepthStencilView(pTexture.Get(), &dsvDesc, &m_pDSV);
	return true;
}
bool MDevice::CreateViewport()
{
	DXGI_SWAP_CHAIN_DESC currentSD;
	m_pSwapChain->GetDesc(&currentSD);
	m_vp.TopLeftX = 0;
	m_vp.TopLeftY = 0;
	m_vp.Width	= currentSD.BufferDesc.Width;
	m_vp.Height = currentSD.BufferDesc.Height;
	m_vp.MinDepth = 0;
	m_vp.MaxDepth = 1;
	m_pContext->RSSetViewports(1, &m_vp);
	return true;
}
bool MDevice::ReleaseDevice()
{
	if (m_pRTV)m_pRTV->Release();
	if (m_pSwapChain)m_pSwapChain->Release();
	if (m_pd3dDevice)m_pd3dDevice->Release();
	if (m_pContext)m_pContext->Release();
	if (m_pGIFactory)m_pGIFactory->Release();
	return true;
}
MDevice::MDevice()
{
	m_pGIFactory = nullptr;
	m_pd3dDevice = nullptr;
	m_pContext = nullptr;
	m_pSwapChain = nullptr;
	m_pRTV = nullptr;
}
MDevice::~MDevice()
{

}