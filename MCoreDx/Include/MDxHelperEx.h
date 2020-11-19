#pragma once
#include "MDxHelper.h"
namespace DX
{
	ID3D11Buffer* CreateVertexBuffer(
		ID3D11Device* pd3dDevice,
		void*  pData,
		UINT iCounter,
		UINT iSize);
	ID3D11Buffer* CreateIndexBuffer(
		ID3D11Device* pd3dDevice,
		void*  pData,
		UINT iCounter,
		UINT iSize);
	ID3D11Buffer* CreateConstantBuffer(
		ID3D11Device* pd3dDevice,
		void*  pData,
		UINT iCounter,
		UINT iSize);
	ID3D11InputLayout* CreateInputlayout(
		ID3D11Device* pd3dDevice,
		DWORD dwSize,
		LPCVOID lpData,
		D3D11_INPUT_ELEMENT_DESC* layout,
		UINT iElements);

	HRESULT CompileShaderFromFile(
		ID3D11Device * pd3dDevice,
		const WCHAR* szFileName,
		DWORD flags,
		LPCSTR szEntryPoint,
		LPCSTR szShaderModel,
		ID3DBlob** ppBlobOut);

	ID3D11VertexShader* LoadVertexShaderFile(
		ID3D11Device * pd3dDevice,
		const WCHAR* szFileName,
		DWORD flags,
		LPCSTR szEntryPoint,
		LPCSTR szShaderModel,
		ID3DBlob** ppBlobOut = nullptr);

	ID3D11PixelShader* LoadPixelShaderFile(
		ID3D11Device * pd3dDevice,
		const WCHAR* szFileName,
		DWORD flags,
		LPCSTR szEntryPoint,
		LPCSTR szShaderModel,
		ID3DBlob** ppBlobOut = nullptr);

	ID3D11PixelShader* LoadGeometryShaderFile(ID3D11Device* pd3dDevice);
	ID3D11PixelShader* LoadHullShaderFile(ID3D11Device* pd3dDevice);
	ID3D11PixelShader* LoadDomainShaderFile(ID3D11Device* pd3dDevice);
	ID3D11PixelShader* LoadComputeShaderFile(ID3D11Device* pd3dDevice);

	class MDxObject
	{
	public:
		Microsoft::WRL::ComPtr<ID3D11Buffer>	m_pVertexBuffer;
		ComPtr < ID3D11Buffer>					m_pIndexBuffer;
		ComPtr < ID3D11Buffer>					m_pConstantBuffer;
		ComPtr < ID3D11InputLayout>				m_pVertexLayout;
		ComPtr < ID3D11VertexShader>			m_pVS;
		ComPtr < ID3D11PixelShader>				m_pPS;
		ComPtr < ID3DBlob>						m_pVSBuf;
	public:
		UINT				m_iNumVertex;
		UINT				m_iNumIndex;
		UINT				m_iPrimitiveType;
	public:
		bool	PreRender(
			ID3D11DeviceContext* pContext,
			UINT iVertexSize = 0);
		bool	Render(
			ID3D11DeviceContext* pContext,
			UINT iVertexSize = 0,
			UINT iCount = 0);
		bool	PostRender(
			ID3D11DeviceContext* pContext,
			UINT iCount = 0);
	public:
		MDxObject();
		virtual ~MDxObject();
	};
}

