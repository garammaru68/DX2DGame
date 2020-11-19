#include "MDxHelperEx.h"

ID3D11Buffer * DX::CreateVertexBuffer(
	ID3D11Device * pd3dDevice,
	void*  pData,
	UINT iCounter,
	UINT iSize)
{
	HRESULT hr = S_OK;
	ID3D11Buffer* pBuffer = nullptr;
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = iSize * iCounter;
	bd.Usage = D3D11_USAGE_DEFAULT; // 그래픽카드 메모리에
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = pData;
	hr = pd3dDevice->CreateBuffer(&bd, &sd, &pBuffer);
	return pBuffer;
}

ID3D11Buffer * DX::CreateIndexBuffer(
	ID3D11Device * pd3dDevice,
	void*  pData,
	UINT iCounter,
	UINT iSize)
{
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	ID3D11Buffer* pBuffer = nullptr;
	bd.ByteWidth = iSize * iCounter;
	bd.Usage = D3D11_USAGE_DEFAULT; // 그래픽카드 메모리에
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = pData;
	hr = pd3dDevice->CreateBuffer(&bd, &sd, &pBuffer);

	return pBuffer;
}

ID3D11Buffer * DX::CreateConstantBuffer(
	ID3D11Device * pd3dDevice,
	void*  pData,
	UINT iCounter,
	UINT iSize)
{
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ID3D11Buffer* pBuffer = nullptr;
	bd.ByteWidth = iSize * iCounter;
	bd.Usage = D3D11_USAGE_DEFAULT; // 그래픽카드 메모리에
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = pData;
	hr = pd3dDevice->CreateBuffer(&bd, &sd, &pBuffer);
	return pBuffer;
}

ID3D11InputLayout * DX::CreateInputlayout(
	ID3D11Device * pd3dDevice,
	DWORD dwSize,
	LPCVOID lpData,
	D3D11_INPUT_ELEMENT_DESC* layout,
	UINT iElements)
{
	HRESULT hr = S_OK;
	ID3D11InputLayout*  pBuffer = nullptr;
	hr = pd3dDevice->CreateInputLayout(
		layout,
		iElements,
		lpData,
		dwSize,
		&pBuffer);
	return pBuffer;
}

HRESULT DX::CompileShaderFromFile(
	ID3D11Device * pd3dDevice,
	const WCHAR* szFileName,
	DWORD flags,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	ID3DBlob** ppBlobOut)
{
	HRESULT hr;
	ID3D11VertexShader* pVS = nullptr;
	ID3DBlob* pErrorBuf = nullptr;
	HANDLE hFile = CreateFile(szFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return E_FAIL;
	}
	LARGE_INTEGER filesize;
	GetFileSizeEx(hFile, &filesize);

	DWORD dwRead = 0;
	BYTE* pFileData = new BYTE[filesize.LowPart];
	ReadFile(hFile, pFileData, filesize.LowPart,
		&dwRead, NULL);

	CloseHandle(hFile);

	hr = D3DCompile(pFileData,
		filesize.LowPart,
		"none",
		NULL, NULL,
		szEntryPoint,
		szShaderModel, flags,
		D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS,
		ppBlobOut,
		&pErrorBuf);
	if (FAILED(hr))
	{
		OutputDebugStringA((char*)pErrorBuf->GetBufferPointer());
		return E_FAIL;
	}
	if (pErrorBuf)pErrorBuf->Release();
	return hr;
}

ID3D11VertexShader * DX::LoadVertexShaderFile(
	ID3D11Device * pd3dDevice,
	const WCHAR* szFileName,
	DWORD flags,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	ID3DBlob** ppBlobOut)
{
	HRESULT hr;
	ID3D11VertexShader* pVS = nullptr;
	ID3DBlob* pBlob = nullptr;
	LPCVOID  lpData = nullptr;
	DWORD dwSize;
	if (FAILED(hr = DX::CompileShaderFromFile(
		pd3dDevice,
		szFileName, flags, "VS", "vs_5_0",
		&pBlob)))
	{
		return nullptr;
	}
	lpData = pBlob->GetBufferPointer();
	dwSize = pBlob->GetBufferSize();

	if (FAILED(hr = pd3dDevice->CreateVertexShader(
		lpData,
		dwSize,
		NULL,
		&pVS)))
	{
		pBlob->Release();
		return nullptr;
	}
	if (ppBlobOut == nullptr)
	{
		pBlob->Release();
	}
	else
	{
		*ppBlobOut = pBlob;
	}
	return pVS;
}

ID3D11PixelShader * DX::LoadPixelShaderFile(
	ID3D11Device * pd3dDevice,
	const WCHAR* szFileName,
	DWORD flags,
	LPCSTR szEntryPoint,
	LPCSTR szShaderModel,
	ID3DBlob** ppBlobOut)
{
	HRESULT hr;
	ID3D11PixelShader* pPS = nullptr;
	ID3DBlob* pBlob = nullptr;
	LPCVOID  lpData = nullptr;
	DWORD dwSize;
	if (FAILED(hr = DX::CompileShaderFromFile(
		pd3dDevice,
		szFileName, flags, "PS", "ps_5_0",
		&pBlob)))
	{
		return nullptr;
	}
	lpData = pBlob->GetBufferPointer();
	dwSize = pBlob->GetBufferSize();

	if (FAILED(hr = pd3dDevice->CreatePixelShader(
		lpData,
		dwSize,
		NULL,
		&pPS)))
	{
		pBlob->Release();
		return nullptr;
	}
	if (ppBlobOut == nullptr)
	{
		pBlob->Release();
	}
	else
	{
		*ppBlobOut = pBlob;
	}
	return pPS;
}

ID3D11PixelShader * DX::LoadGeometryShaderFile(ID3D11Device * pd3dDevice)
{
	return nullptr;
}

ID3D11PixelShader * DX::LoadHullShaderFile(ID3D11Device * pd3dDevice)
{
	return nullptr;
}

ID3D11PixelShader * DX::LoadDomainShaderFile(ID3D11Device * pd3dDevice)
{
	return nullptr;
}

ID3D11PixelShader * DX::LoadComputeShaderFile(ID3D11Device * pd3dDevice)
{
	return nullptr;
}

bool DX::MDxObject::PreRender(
	ID3D11DeviceContext * pContext,
	UINT iVertexSize)
{
	UINT stride = iVertexSize;
	UINT offset = 0;

	pContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	pContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	pContext->IASetInputLayout(m_pVertexLayout.Get());
	pContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)m_iPrimitiveType);
	pContext->VSSetShader(m_pVS.Get(), NULL, 0);
	pContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	pContext->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	pContext->HSSetShader(NULL, NULL, 0);
	pContext->DSSetShader(NULL, NULL, 0);
	pContext->GSSetShader(NULL, NULL, 0);
	pContext->PSSetShader(m_pPS.Get(), NULL, 0);
	return true;
}

bool DX::MDxObject::Render(ID3D11DeviceContext * pContext,
	UINT iVertexSize,
	UINT iCount)
{
	PreRender(pContext, iVertexSize);
	PostRender(pContext, iCount);
	return false;
}

bool DX::MDxObject::PostRender(
	ID3D11DeviceContext * pContext,
	UINT iCount)
{
	if (iCount == 0) iCount = m_iNumIndex;
	if (iCount != 0)
	{
		pContext->DrawIndexed(iCount, 0, 0);
	}
	else
	{
		pContext->Draw(m_iNumVertex, 0);

	}
	return false;
}

DX::MDxObject::MDxObject()
{
	m_iNumVertex = 0;
	m_iNumIndex = 0;
	m_iPrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

DX::MDxObject::~MDxObject()
{
}
