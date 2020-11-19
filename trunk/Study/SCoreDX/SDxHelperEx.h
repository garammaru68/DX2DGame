#pragma once
#include "SDxRT.h"

namespace DX
{
	void ClearD3D11DeviceContext(ID3D11DeviceContext* pd3dDeviceContext);

	HRESULT					ComplieShaderFromeFile(	const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	ID3D11VertexShader*		LoadVertexShaderFile(	ID3D11Device* pd3dDevice, const void* pLoadShaderFile, ID3DBlob** ppBlobOut = nullptr, char *pFuntionName = 0, bool bBinary = false);
	ID3D11PixelShader*		LoadPixelShaderFile(	ID3D11Device* pd3dDevice, const void* pLoadShaderFile, char *pFuntionName = 0, bool bBinary = false, ID3DBlob** pRetBlob = nullptr);
	ID3D11GeometryShader*	LoadGeometryShaderFile(	ID3D11Device* pd3dDevice, const void* pLoadShaderFile, ID3DBlob** ppBlobOut = nullptr, char *pFuntionName = 0, bool bBinary = false);
	ID3D11HullShader*		LoadHullShaderFile(		ID3D11Device* pd3dDevice, const void* pLoadShaderFile, ID3DBlob** ppblobOut = nullptr, char *pFunctionName = 0, bool bBinary = false);
	ID3D11DomainShader*		LoadDomainShaderFile(	ID3D11Device* pd3dDevice, const void* pLoadShaderFile, ID3DBlob** ppBlobOut = nullptr, char *pFuntionName = 0, bool bBinary = false);
	ID3D11ComputeShader*	LoadComputeShaderFile(	ID3D11Device* pd3dDevice, const void* pLoadShaderFile, ID3DBlob** ppblobOut = nullptr, char *pFuntionName = 0, bool bBinary = false);

	ID3D11InputLayout*	CreateInputlayout(		ID3D11Device* pd3dDevice, DWORD dwSize, LPCVOID lpData, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements);
	ID3D11Buffer*		CreateVertexBuffer(		ID3D11Device* pd3dDevice, void *vertices, UINT iNumVertex, UINT iVertexSize, bool bDynamic = false);
	ID3D11Buffer*		CreateIndexBuffer(		ID3D11Device* pd3dDevice, void *indices, UINT iNumIndex, UINT iSize, bool bDynamic = false);
	ID3D11Buffer*		CreateConstantBuffer(	ID3D11Device* pd3dDevice, void *data, UINT iNumIndex, UINT iSize, bool bDynamic = false);

	ID3D11ShaderResourceView*	CreateShaderResourceView(ID3D11Device* pDevice, const TCHAR* strfilePath);
	ID3D11DepthStencilView*		CreateDepthSTencilView(ID3D11Device* pDevice, DWORD dwWidth, DWORD dwHeight);
}

class SDxObject
{
public:
	Microsoft::WRL::ComPtr<ID3D11Buffer>		g_pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		g_pIndexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		g_pConstantBuffer;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>	g_pVertexShader;
};

