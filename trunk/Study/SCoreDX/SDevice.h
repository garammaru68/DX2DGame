#pragma once
#include "SBasisStd.h"
#include "SDxHelperEx.h"
using namespace DX;

class SDevice
{
public:
	SDxRT					m_DefaultRT;

	ID3D11Device*			m_pd3dDevice;
	IDXGISwapChain*			m_pSwapChain;
	D3D_DRIVER_TYPE			m_driverType;
	IDXGIFactory*			m_pGIFactory;
	ID3D11DeviceContext*	m_pImmediateContext;
	D3D_FEATURE_LEVEL		m_FeatureLevel;
	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;
	BOOL					m_IsFullScreenMode;

public:
	BOOL						GetFullScreenFlag();
	void						SetFullScreenFlag(BOOL blFlag);
	ID3D11Device*				GetDevice();
	ID3D11DeviceContext*		Getcontext();
	IDXGISwapChain*				GetSwapChain();
	ID3D11RenderTargetView*		GetRenderTargetView();
	ID3D11RenderTargetView**	GetRenderTargetViewDaddress() { return m_DefaultRT.m_pRenderTargetView.GetAddressOf(); }
	ID3D11DepthStencilView*		GetDepthStencilView() { return m_DefaultRT.m_pDepthStencilView.Get(); }
	ID3D11DepthStencilView**	GetDepthStencilViewAddress() { return m_DefaultRT.m_pDepthStencilView.GetAddressOf(); }
	IDXGIFactory*				GetGIFactory();
public:
	HRESULT InitDevice(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen = FALSE);
	HRESULT CreateDevice();
	HRESULT CreateGIFactory();
	HRESULT CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen = FALSE);
	HRESULT CreateDeviceAndSwapChain(HWND hWnd, UINT iWidth, UINT iHeight, BOOL IsFullScreen = FALSE);

	bool CleanupDevice();

	HRESULT ResizeDevice(UINT width, UINT height);
	virtual HRESULT SetRenderTargetView();
	virtual HRESULT SetViewPort();
	virtual HRESULT DeleteDxResource();
	virtual HRESULT CreateDxResource();

public:
	SDevice(void);
	virtual ~SDevice(void);
};

