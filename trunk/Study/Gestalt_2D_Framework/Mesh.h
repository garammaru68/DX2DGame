#pragma once
#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

#include "Texture.h"

class Mesh
{
public:
	struct PCTVertex
	{
		float x, y, z;
		float r, g, b, a;
		float u, v;
	};
	struct ConstBuffer
	{
		float r, g, b, a;
		float x, y, z, delta;
	};
private:
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pImmediateContext;

	ID3D11PixelShader* pPixelShader;
	ID3D11VertexShader* pVertexShader;
	ID3D11InputLayout* pInputLayout;
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer* pIndexBuffer;
	ID3D11Buffer* pConstBuffer;
	ID3D11SamplerState* pSamplerState;
	ID3D11BlendState* pBlendState;
	ID3D11RasterizerState* pRasterizerState;

	D3D11_RASTERIZER_DESC rasterizerDesc;

	PCTVertex vertices[4];
	ConstBuffer cb = {};
public:
	Mesh() = default;
	~Mesh();

	Mesh(const Mesh&) = delete;
	Mesh& operator =(const Mesh&) = delete;

private:
	void SetTexCoord(RECT_F rt);
	void SetUV(RECT_F rt, UINT w, UINT h);

public:
	void Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);
	void Render(Texture& texture);

	void ToggleWireframe();
};