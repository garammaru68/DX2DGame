#include "MDxState.h"

ID3D11SamplerState* MDxState::g_pSamplerState = nullptr;
ID3D11BlendState*   MDxState::g_pBSAlphaBlend = nullptr;
ID3D11BlendState*   MDxState::g_pBSNoColorBlend = nullptr;
ID3D11RasterizerState*   MDxState::g_pRSSolidNone = nullptr;
ID3D11RasterizerState*   MDxState::g_pRSWireFrameBack = nullptr;
ID3D11RasterizerState*   MDxState::g_pRSSolidBack = nullptr;
ID3D11RasterizerState*   MDxState::g_pRSSolidFront = nullptr;
ID3D11DepthStencilState* MDxState::g_pDSSDepthEnable = nullptr;
ID3D11DepthStencilState* MDxState::g_pDSSDepthDisable = nullptr;
void MDxState::Create(	ID3D11Device* pd3dDevice,
						ID3D11DeviceContext*	pContext)
{
	HRESULT hr;
#pragma region  sampler state
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.BorderColor[0] = 1.0f;
	sd.BorderColor[1] = 1.0f;
	sd.BorderColor[2] = 0.0f;
	sd.BorderColor[3] = 1.0f;
	hr = pd3dDevice->CreateSamplerState(&sd, &g_pSamplerState);
#pragma endregion 
#pragma region blendstate
	D3D11_BLEND_DESC bsd;
	ZeroMemory(&bsd, sizeof(bsd));
	bsd.AlphaToCoverageEnable = FALSE;
	//BOOL IndependentBlendEnable;
	bsd.RenderTarget[0].BlendEnable = TRUE;
	bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bsd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bsd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bsd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	bsd.RenderTarget[0].RenderTargetWriteMask =
		D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = pd3dDevice->CreateBlendState(
		&bsd,
		&g_pBSAlphaBlend);

	bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
	bsd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bsd.RenderTarget[0].RenderTargetWriteMask = 0;

	hr = pd3dDevice->CreateBlendState(
		&bsd,
		&g_pBSNoColorBlend);

#pragma endregion 
#pragma region RasterizerState 
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID; // D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_NONE;
	pd3dDevice->CreateRasterizerState(&rd, &g_pRSSolidNone);

	rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.CullMode = D3D11_CULL_BACK;
	pd3dDevice->CreateRasterizerState(&rd, &g_pRSWireFrameBack);

	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_BACK;
	pd3dDevice->CreateRasterizerState(&rd, &g_pRSSolidBack);

	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_FRONT;
	pd3dDevice->CreateRasterizerState(&rd, &g_pRSSolidFront);
#pragma endregion 

#pragma region DSS
	D3D11_DEPTH_STENCIL_DESC dsd;
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	dsd.StencilEnable = FALSE;
	dsd.StencilReadMask = 1;
	dsd.StencilWriteMask = 1;
	dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	pd3dDevice->CreateDepthStencilState(&dsd, &g_pDSSDepthEnable);

	dsd.DepthEnable = FALSE;
	pd3dDevice->CreateDepthStencilState(&dsd, &g_pDSSDepthDisable);
#pragma endregion 
}

bool MDxState::Release()
{
	if (g_pDSSDepthEnable)g_pDSSDepthEnable->Release();
	if (g_pDSSDepthDisable)g_pDSSDepthDisable->Release();
	if (g_pRSSolidBack) g_pRSSolidBack->Release();
	if (g_pRSSolidFront) g_pRSSolidFront->Release();
	if (g_pRSSolidNone) g_pRSSolidNone->Release();
	if (g_pRSWireFrameBack) g_pRSWireFrameBack->Release();
	if (g_pSamplerState) g_pSamplerState->Release();
	if (g_pBSAlphaBlend) g_pBSAlphaBlend->Release();
	if (g_pBSNoColorBlend)g_pBSNoColorBlend->Release();
	return true;
}

MDxState::MDxState()
{
}


MDxState::~MDxState()
{
}
