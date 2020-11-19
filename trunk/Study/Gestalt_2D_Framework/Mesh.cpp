#include "Mesh.h"
#include "Graphics.h"

namespace FramebufferShaders
{
#include "FramebufferVS.shh"
#include "FramebufferPS.shh"
};

Mesh::~Mesh()
{
	if (pRasterizerState) pRasterizerState->Release();
	if (pBlendState) pBlendState->Release();
	if (pSamplerState) pSamplerState->Release();
	if (pVertexBuffer) pVertexBuffer->Release();
	if (pVertexShader) pVertexShader->Release();
	if (pPixelShader) pPixelShader->Release();
	if (pInputLayout) pInputLayout->Release();
}

void Mesh::Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
{
	this->pDevice = pDevice;
	this->pImmediateContext = pImmediateContext;

	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth = sizeof(PCTVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0u;
	bd.Usage = D3D11_USAGE_DEFAULT;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = vertices;
	if (FAILED(pDevice->CreateBuffer(&bd, &initData, &pVertexBuffer)))
	{
		MessageBox(nullptr, L"Failed To Create Vertex Buffer", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	bd.ByteWidth = sizeof(DWORD) * 6;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	DWORD indexes[6];
	indexes[0] = 0;
	indexes[1] = 1;
	indexes[2] = 2;
	indexes[3] = 2;
	indexes[4] = 1;
	indexes[5] = 3;
	initData.pSysMem = indexes;
	if (FAILED(pDevice->CreateBuffer(&bd, &initData, &pIndexBuffer)))
	{
		MessageBox(nullptr, L"Failed To Create Index Buffer", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	initData.pSysMem = &cb;
	if (FAILED(pDevice->CreateBuffer(&bd, &initData, &pConstBuffer)))
	{
		MessageBox(nullptr, L"Failed To Create Constant Buffer", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	if (FAILED(pDevice->CreateVertexShader(
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		nullptr,
		&pVertexShader)))
	{
		MessageBox(nullptr, L"Failed To Create Vertex Shader", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	if (FAILED(pDevice->CreatePixelShader(
		FramebufferShaders::FramebufferPSBytecode,
		sizeof(FramebufferShaders::FramebufferPSBytecode),
		nullptr,
		&pPixelShader)))
	{
		MessageBox(nullptr, L"Failed To Create Pixel Shader", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	const D3D11_INPUT_ELEMENT_DESC ied[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT nElement = sizeof(ied) / sizeof(ied[0]);
	if (FAILED(pDevice->CreateInputLayout(ied, nElement,
		FramebufferShaders::FramebufferVSBytecode,
		sizeof(FramebufferShaders::FramebufferVSBytecode),
		&pInputLayout)))
	{
		MessageBox(nullptr, L"Failed To Create Layout", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(pDevice->CreateSamplerState(&sampDesc, &pSamplerState)))
	{
		MessageBox(nullptr, L"Failed To Create SamplerState", L"ERROR", MB_OK);
		PostQuitMessage(0);
	}

	D3D11_BLEND_DESC blendDesc = {};
	/*blendDesc.AlphaToCoverageEnable;
	blendDesc.IndependentBlendEnable;*/
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;

	if (FAILED(pDevice->CreateBlendState(&blendDesc, &pBlendState)))
	{
		MessageBox(nullptr, L"Failed To Create BlendState", L"ERROR", MB_OK);
		PostQuitMessage(0);
	};

	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	/*BOOL FrontCounterClockwise;
	INT DepthBias;
	FLOAT DepthBiasClamp;
	FLOAT SlopeScaledDepthBias;
	BOOL DepthClipEnable = false;
	BOOL ScissorEnable = false;
	BOOL MultisampleEnable = false;
	BOOL AntialiasedLineEnable = false;*/
	if (FAILED(pDevice->CreateRasterizerState(&rasterizerDesc, &pRasterizerState)))
	{
		MessageBox(nullptr, L"Failed To Create RasterizerState", L"ERROR", MB_OK);
		PostQuitMessage(0);
	};

	pImmediateContext->VSSetConstantBuffers(0u, 1u, &pConstBuffer);
	pImmediateContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0u);
	pImmediateContext->IASetInputLayout(pInputLayout);
	pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pImmediateContext->VSSetShader(pVertexShader, nullptr, 0u);
	pImmediateContext->PSSetShader(pPixelShader, nullptr, 0u);
	pImmediateContext->PSSetSamplers(0u, 1u, &pSamplerState);
	pImmediateContext->RSSetState(pRasterizerState);
	pImmediateContext->OMSetBlendState(pBlendState, nullptr, 0xff);
}

void Mesh::Render(Texture& texture)
{
	auto pSRV = texture.GetSRV();
	if (pSRV == nullptr)
	{
		MessageBox(nullptr, L"pSRV = nullptr", L"Failed To Render", MB_OK);
		PostQuitMessage(0);
	}

	SetTexCoord(texture.GetDestRect());
	SetUV(texture.GetSrcRect(), texture.GetWidth(), texture.GetHeight());

	const UINT stride = sizeof(PCTVertex);
	const UINT offset = 0u;
	pImmediateContext->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset);
	pImmediateContext->PSSetShaderResources(0u, 1u, &pSRV);
	pImmediateContext->UpdateSubresource(pVertexBuffer, 0u, nullptr, vertices, 0u, 0u);
	pImmediateContext->UpdateSubresource(pConstBuffer, 0u, 0u, &cb, 0u, 0u);
	pImmediateContext->DrawIndexed(6u, 0u, 0u);
}

void Mesh::SetTexCoord(RECT_F rt)
{
	rt = {
		(rt.left) / Graphics::GetScreenWidth() * 2.0f - 1.0f,
		-((rt.top) / Graphics::GetScreenHeight() * 2.0f - 1.0f),
		(rt.right) / Graphics::GetScreenWidth() * 2.0f - 1.0f,
		-((rt.bottom) / Graphics::GetScreenHeight() * 2.0f - 1.0f)
	};

	vertices[0].x = rt.left;	vertices[0].y = rt.top;
	vertices[1].x = rt.right; vertices[1].y = rt.top;
	vertices[2].x = rt.left;	vertices[2].y = rt.bottom;
	vertices[3].x = rt.right; vertices[3].y = rt.bottom;
}

void Mesh::SetUV(RECT_F rt, UINT w, UINT h)
{
	rt = {
		rt.left / w,
		rt.top / h,
		rt.right / w,
		rt.bottom / h
	};

	vertices[0].u = rt.left; vertices[0].v = rt.top;
	vertices[1].u = rt.right; vertices[1].v = rt.top;
	vertices[2].u = rt.left; vertices[2].v = rt.bottom;
	vertices[3].u = rt.right; vertices[3].v = rt.bottom;
}

void Mesh::ToggleWireframe()
{
	if (rasterizerDesc.FillMode != D3D11_FILL_WIREFRAME)
		rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
	else rasterizerDesc.FillMode = D3D11_FILL_SOLID;

	if (FAILED(pDevice->CreateRasterizerState(&rasterizerDesc, &pRasterizerState)))
	{
		MessageBox(nullptr, L"Failed To Create RasterizerState", L"ERROR", MB_OK);
		PostQuitMessage(0);
	};
	pImmediateContext->RSSetState(pRasterizerState);
}