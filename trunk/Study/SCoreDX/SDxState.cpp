#include "SDxState.h"

namespace DX
{
	ID3D11RasterizerState*	 SDxState::g_pRSWireFrame = 0;
	ID3D11RasterizerState*	 SDxState::g_pRSSolid = 0;
	ID3D11RasterizerState*	 SDxState::g_pRSBackCullSolid = 0;
	ID3D11RasterizerState*	 SDxState::g_pRSNoneCullSolid = 0;
	ID3D11RasterizerState*	 SDxState::g_pRSFrontCullSolid = 0;
	ID3D11RasterizerState*	 SDxState::g_pRSSlopeScaledDepthBias;
	ID3D11RasterizerState*	 SDxState::g_pRS[6] = { 0, };

	ID3D11SamplerState*		 SDxState::g_pTexSS = 0;
	ID3D11SamplerState*		 SDxState::g_pSSWrapLinear = NULL;
	ID3D11SamplerState*		 SDxState::g_pSSWrapPoint = NULL;
	ID3D11SamplerState*		 SDxState::g_pSSMirrorLinear = NULL;
	ID3D11SamplerState*		 SDxState::g_pSSClampLinear = NULL;
	ID3D11SamplerState*		 SDxState::g_pSSClampPoint = NULL;
	ID3D11SamplerState*		 SDxState::g_pSSShadowMap = NULL;
	ID3D11SamplerState*		 SDxState::g_pSS[8] = { 0, };

	ID3D11DepthStencilState* SDxState::g_pDSSDepthEnable = 0;
	ID3D11DepthStencilState* SDxState::g_pDSSDepthDisable = 0;
	ID3D11DepthStencilState* SDxState::g_pDSSDepthEnableNoWrite = 0;
	ID3D11DepthStencilState* SDxState::g_pDSSDepthDisableNoWrite = 0;
	ID3D11DepthStencilState* SDxState::g_pDSSDepthStencilAdd = 0;
	ID3D11DepthStencilState* SDxState::g_pDSSDepthAlways = 0;
	ID3D11DepthStencilState* SDxState::g_pDSS[6] = { 0, };

	ID3D11BlendState*		 SDxState::g_pAlphaBlend = 0;
	ID3D11BlendState*		 SDxState::g_pNoAlphaBlend = 0;
	ID3D11BlendState*		 SDxState::g_pBSColorOne = 0;
	ID3D11BlendState*		 SDxState::g_pBSOneOne = 0;
	ID3D11BlendState*		 SDxState::g_pBSOneZero = 0;
	ID3D11BlendState*		 SDxState::g_pBSAlphaOne = 0;
	ID3D11BlendState*		 SDxState::g_pBSMaxOneOne = 0;
	ID3D11BlendState*		 SDxState::g_pBS[7] = { 0, };

	HRESULT SDxState::SetState(ID3D11Device* pd3dDevice)
	{
		if (pd3dDevice == nullptr) return S_OK;
		if (g_pTexSS != nullptr) return S_OK;

		HRESULT hr = S_OK;
		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.BorderColor[0] = 1.0f;
		samplerDesc.BorderColor[1] = 0.0f;
		samplerDesc.BorderColor[2] = 0.0f;
		samplerDesc.BorderColor[3] = 1.0f;
		samplerDesc.MaxAnisotropy = 16;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.MaxLOD = FLT_MAX;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MinLOD = FLT_MIN;
		if (FAILED(hr = pd3dDevice->CreateSamplerState(&samplerDesc, &g_pTexSS)))
			return hr;

		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
		blendDesc.AlphaToCoverageEnable = FALSE;
		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		pd3dDevice->CreateBlendState(&blendDesc, &g_pAlphaBlend);

		blendDesc.RenderTarget[0].BlendEnable = FALSE;
		pd3dDevice->CreateBlendState(&blendDesc, &g_pNoAlphaBlend);

		blendDesc.RenderTarget[0].BlendEnable = TRUE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		pd3dDevice->CreateBlendState(&blendDesc, &SDxState::g_pBSColorOne);

		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		pd3dDevice->CreateBlendState(&blendDesc, &SDxState::g_pBSOneOne);

		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		pd3dDevice->CreateBlendState(&blendDesc, &SDxState::g_pBSOneZero);

		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		pd3dDevice->CreateBlendState(&blendDesc, &SDxState::g_pBSAlphaOne);

		blendDesc.AlphaToCoverageEnable = TRUE;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		pd3dDevice->CreateBlendState(&blendDesc, &SDxState::g_pBSMaxOneOne);

		D3D11_RASTERIZER_DESC rsDesc;
		ZeroMemory(&rsDesc, sizeof(rsDesc));
		rsDesc.DepthClipEnable = TRUE;
		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_BACK;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &SDxState::g_pRSBackCullSolid)))
			return hr;

		rsDesc.FillMode = D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_NONE;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &SDxState::g_pRSWireFrame)))
			return hr;

		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_BACK;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &SDxState::g_pRSSolid)))
			return hr;

		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_NONE;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &SDxState::g_pRSNoneCullSolid)))
			return hr;

		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_FRONT;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&rsDesc, &SDxState::g_pRSFrontCullSolid)))
			return hr;

		g_pRS[0] = g_pRSNoneCullSolid;
		g_pRS[1] = g_pRSFrontCullSolid;
		g_pRS[2] = g_pRSBackCullSolid;

		ID3D11SamplerState* pSamplerState = nullptr;
		D3D11_SAMPLER_DESC sd;
		memset(&sd, 0, sizeof(sd));
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sd.MaxLOD = FLT_MAX;
		sd.MinLOD = FLT_MIN;
		if (FAILED(hr = pd3dDevice->CreateSamplerState(&sd, &g_pSSWrapLinear)))
		{
			return hr;
		}

		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		if (FAILED(hr = pd3dDevice->CreateSamplerState(&sd, &g_pSSWrapPoint)))
		{
			return hr;
		}

		sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		if (FAILED(hr = pd3dDevice->CreateSamplerState(&sd, &g_pSSMirrorLinear)))
		{
			return hr;
		}

		sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		if (FAILED(hr = pd3dDevice->CreateSamplerState(&sd, &g_pSSMirrorPoint)))
		{
			return hr;
		}

		sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		if (FAILED(hr = pd3dDevice->CreateSamplerState(&sd, &g_pSSClampLinear)))
		{
			return hr;
		}

		sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		if (FAILED(hr = pd3dDevice->CreateSamplerState(&sd, &g_pSSClampPoint)))
		{
			return hr;
		}

		D3D11_SAMPLER_DESC SamDescShad =
		{
			D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
			D3D11_TEXTURE_ADDRESS_BORDER,
			D3D11_TEXTURE_ADDRESS_BORDER,
			D3D11_TEXTURE_ADDRESS_BORDER,
			0,
			0,
			D3D11_COMPARISON_LESS,
			0.0, 0.0, 0.0, 0.0,
			0,
			0
		};
		if (FAILED(hr = pd3dDevice->CreateSamplerState(&SamDescShad, &g_pSSShadowMap)))
		{
			return hr;
		}

		g_pSS[0] = g_pSSWrapLinear;
		g_pSS[1] = g_pSSWrapPoint;
		g_pSS[2] = g_pSSMirrorLinear;
		g_pSS[3] = g_pSSMirrorPoint;
		g_pSS[4] = g_pSSClampLinear;
		g_pSS[5] = g_pSSClampPoint;
		g_pSS[6] = g_pSSShadowMap;

		D3D11_DEPTH_STENCIL_DESC dsDescDepth;
		ZeroMemory(&dsDescDepth, sizeof(D3D11_DEPTH_STENCIL_DESC));
		dsDescDepth.DepthEnable = TRUE;
		dsDescDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDescDepth.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsDescDepth.StencilEnable = FALSE;
		dsDescDepth.StencilReadMask = 1;
		dsDescDepth.StencilWriteMask = 1;
		dsDescDepth.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsDescDepth.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
		dsDescDepth.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDescDepth.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

		dsDescDepth.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsDescDepth.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDescDepth.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDescDepth.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

		if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&dsDescDepth, &g_pDSSDepthEnable)))
		{
			return hr;
		}

		dsDescDepth.DepthEnable = FALSE;
		if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&dsDescDepth, &g_pDSSDepthDisable)))
		{
			return hr;
		}

		dsDescDepth.DepthEnable = TRUE;
		dsDescDepth.DepthFunc = D3D11_COMPARISON_ALWAYS;
		if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&dsDescDepth, &g_pDSSDepthAlways)))
		{
			return hr;
		}

		dsDescDepth.DepthEnable = FALSE;
		dsDescDepth.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsDescDepth.StencilEnable = TRUE;
		dsDescDepth.BackFace.StencilFunc = D3D11_COMPARISON_NOT_EQUAL;
		dsDescDepth.FrontFace.StencilFunc = D3D11_COMPARISON_NOT_EQUAL;
		dsDescDepth.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
		dsDescDepth.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;

		if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&dsDescDepth, &g_pDSSDepthStencilAdd)))
		{
			return hr;
		}

		dsDescDepth.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDescDepth.DepthEnable = TRUE;
		dsDescDepth.StencilEnable = FALSE;
		if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&dsDescDepth, &g_pDSSDepthEnableNoWrite)))
		{
			return hr;
		}
		return hr;
	}
	bool SDxState::Release()
	{
		if (g_pBSColorOne)	g_pBSColorOne->Release();	g_pBSColorOne = NULL;
		if (g_pTexSS)		g_pTexSS->Release();		g_pTexSS = NULL;
		if (g_pAlphaBlend)	g_pAlphaBlend->Release();	g_pAlphaBlend = NULL;
		if (g_pNoAlphaBlend)g_pNoAlphaBlend->Release(); g_pNoAlphaBlend = NULL;
		if (g_pBSOneOne)	g_pBSOneOne->Release();		g_pBSOneOne = NULL;
		if (g_pBSOneZero)	g_pBSOneZero->Release();	g_pBSOneZero = NULL;
		if (g_pBSAlphaOne)	g_pBSAlphaOne->Release();	g_pBSAlphaOne = NULL;
		if (g_pBSMaxOneOne)	g_pBSMaxOneOne->Release();	g_pBSMaxOneOne = NULL;

		if (g_pRSBackCullSolid)	g_pRSBackCullSolid->Release();	g_pRSBackCullSolid = NULL;
		if (g_pRSWireFrame)		g_pRSWireFrame->Release();		g_pRSWireFrame = NULL;
		if (g_pRSSolid)			g_pRSSolid->Release();			g_pRSSolid = NULL;
		if (g_pRSNoneCullSolid)	g_pRSNoneCullSolid->Release();	g_pRSNoneCullSolid = NULL;
		if (g_pRSFrontCullSolid)g_pRSFrontCullSolid->Release();	g_pRSFrontCullSolid = NULL;

		if (g_pSSWrapLinear)	g_pSSWrapLinear->Release();		g_pSSWrapLinear = NULL;
		if (g_pSSWrapPoint)		g_pSSWrapPoint->Release();		g_pSSWrapPoint = NULL;
		if (g_pSSMirrorLinear)	g_pSSMirrorLinear->Release();	g_pSSMirrorLinear = NULL;
		if (g_pSSMirrorPoint)	g_pSSMirrorPoint->Release();	g_pSSMirrorPoint = NULL;
		if (g_pSSClampLinear)	g_pSSClampLinear->Release();	g_pSSClampLinear = NULL;
		if (g_pSSClampPoint)	g_pSSClampPoint->Release();		g_pSSClampPoint = NULL;
		if (g_pSSShadowMap)		g_pSSShadowMap->Release();		g_pSSShadowMap = NULL;
		if (g_pRSSlopeScaledDepthBias) g_pRSSlopeScaledDepthBias->Release(); g_pRSSlopeScaledDepthBias = NULL;

		if (g_pDSSDepthEnable)			g_pDSSDepthEnable->Release();			g_pDSSDepthEnable = NULL;
		if (g_pDSSDepthDisable)			g_pDSSDepthDisable->Release();			g_pDSSDepthDisable = NULL;
		if (g_pDSSDepthEnableNoWrite)	g_pDSSDepthEnableNoWrite->Release();	g_pDSSDepthEnable = NULL;
		if (g_pDSSDepthDisableNoWrite)	g_pDSSDepthDisableNoWrite->Release();	g_pDSSDepthDisableNoWrite = NULL;
		if (g_pDSSDepthStencilAdd)		g_pDSSDepthStencilAdd->Release();		g_pDSSDepthStencilAdd = NULL;
		if (g_pDSSDepthEnableNoWrite)	g_pDSSDepthAlways->Release();			g_pDSSDepthAlways = NULL;

		return true;
	}
	SDxState::~SDxState()
	{
		Release();
	}
	SDxState g_DxState;
}