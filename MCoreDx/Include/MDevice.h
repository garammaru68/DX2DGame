#pragma once
#include "MStd.h"
class MDevice
{
public:
	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*	m_pContext;
	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView* m_pRTV;
	ID3D11DepthStencilView* m_pDSV;
	//CreateDXGIFactory 외부 기호
	IDXGIFactory*			m_pGIFactory;
	D3D11_VIEWPORT			m_vp;

	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;
public:
	bool	SetD3DDevice(UINT width, UINT height);
	bool	CreateGIFactory();
	bool	CreateDevice();
	bool	CreateSwapChain(UINT width, UINT height);
	bool	CreateRenderTarget();
	bool	CreateDepthStencilView();
	bool	CreateViewport();
	bool	ReleaseDevice();
	virtual void ResizeDevice(UINT width, UINT height);
	virtual void CreateDXResource();
	virtual void DeleteDXResource();
public:
	MDevice();
	virtual ~MDevice();
};

