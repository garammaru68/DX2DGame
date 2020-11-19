#pragma once
#include "MStd.h"
class MDxState
{
public:
	static ID3D11SamplerState* g_pSamplerState;
	static ID3D11BlendState*   g_pBSAlphaBlend;
	static ID3D11BlendState*   g_pBSNoColorBlend;
	static ID3D11RasterizerState*   g_pRSSolidNone;
	static ID3D11RasterizerState*   g_pRSWireFrameBack;
	static ID3D11RasterizerState*   g_pRSSolidBack;
	static ID3D11RasterizerState*   g_pRSSolidFront;
	static ID3D11DepthStencilState* g_pDSSDepthEnable;
	static ID3D11DepthStencilState* g_pDSSDepthDisable;
public:
	static void Create(
		ID3D11Device* pd3dDevice,
		ID3D11DeviceContext*	pContext);
	static bool Release();

public:
	MDxState();
	~MDxState();
};

static void ApplySS(ID3D11DeviceContext* pContext,
	ID3D11SamplerState* pState,
	UINT iSlot = 0, UINT iArray = 1)
{
	pContext->PSSetSamplers(iSlot, iArray, &pState);
}
static void ApplyBS(ID3D11DeviceContext* pContext,
	ID3D11BlendState* pState,
	const FLOAT fBlendFactor[] = 0,
	UINT iMask = 0xff)
{
	pContext->OMSetBlendState(pState, fBlendFactor, iMask);
}
static void ApplyRS(ID3D11DeviceContext* pContext,
	ID3D11RasterizerState* pState)
{
	pContext->RSSetState(pState);
}

static void ApplyDSS(ID3D11DeviceContext* pContext,
	ID3D11DepthStencilState* pState,
	UINT iRef = 0x01)
{
	pContext->OMSetDepthStencilState(pState, iRef);
}