#pragma once
#include "Mesh.h"

class Graphics
{
	friend class MainWindow;
private:
	static UINT screenWidth;
	static UINT screenHeight;
	
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pImmediateContext;
	IDXGIFactory* pGIFactory;
	IDXGISwapChain* pSwapChain;
	ID3D11RenderTargetView* pRenderTargetView;
	D3D11_VIEWPORT	 viewPort;
	
	static bool bResize;

public:
	Mesh mesh;

private:
	void CreateGIFactory();
	void CreateDevice();
	void CreateSwapChain(HWND& hWnd);
	void CreateRenderTarget();
	void CreateViewport();

public:
	Graphics() = default;
	~Graphics();

	Graphics(const Graphics&) = delete;
	Graphics& operator=(Graphics&) = delete;

	static Graphics& GetInstance() {
		static Graphics gfx;
		return gfx;
	}

	void Initialzie(HWND& hWnd);
	void PreRender();
	void PostRender();
	void Resize();

	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetContext() const;

	static UINT GetScreenWidth() { return screenWidth; }
	static UINT GetScreenHeight() { return screenHeight; }
};