#include "MObject.h"

void	 MObject::SetMatrix(D3DXMATRIX* matWorld,
	D3DXMATRIX* matView,
	D3DXMATRIX* matProj)
{
	if (matWorld != nullptr)m_matWorld = *matWorld;
	if (matView != nullptr)m_matView = *matView;
	if (matProj != nullptr)m_matProj = *matProj;
	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);

	m_vLook.x = m_matWorld._31; // z
	m_vLook.y = m_matWorld._32; // z
	m_vLook.z = m_matWorld._33; // z
	m_vRight.x = m_matWorld._11; // z
	m_vRight.y = m_matWorld._12; // z
	m_vRight.z = m_matWorld._13; // z
	m_vUp.x = m_matWorld._21; // z
	m_vUp.y = m_matWorld._22; // z
	m_vUp.z = m_matWorld._23; // z

	D3DXVec3Normalize(&m_vLook, &m_vLook);
	D3DXVec3Normalize(&m_vRight, &m_vRight);
	D3DXVec3Normalize(&m_vUp, &m_vUp);

	m_pContext->UpdateSubresource(
		m_dxObj.m_pConstantBuffer.Get(),
		0, NULL, &m_cbData, 0, 0);
}
void    MObject::SetPos(D3DXVECTOR3 p)
{
	m_vPos = p;
}
D3DXVECTOR3  MObject::ScreenToNDC(POINT pt)
{
	D3DXVECTOR3 v;
	v.x = ((float)pt.x / (float)g_rtClient.right)*2.0f - 1.0f; //-1.0f;
	v.y = -(((float)pt.y / (float)g_rtClient.bottom)*2.0f - 1.0f);// 1.0f;
	v.z = 0.5f;
	return v;
}
void MObject::CreateVertexData()
{
}
void MObject::CreateIndexData()
{
}
void MObject::CreateConstantData()
{
	m_cbData.c = { 1,1,1,1 };
	m_cbData.x = 0.0f;
	m_cbData.y = 0.0f;
	m_cbData.z = 0.0f;
	m_cbData.fTime = 0.0f * (3.141592f / 180.0f);
}

HRESULT MObject::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	m_dxObj.m_pVertexBuffer.Attach(DX::CreateVertexBuffer(
		m_pd3dDevice,
		&m_pVertexList.at(0),
		m_iNumVertex,
		sizeof(PNCT_VERTEX)));
	//D3D11_BUFFER_DESC bd;
	//bd.ByteWidth = sizeof(PNCT_VERTEX)*m_iNumVertex;
	//bd.Usage = D3D11_USAGE_DEFAULT; // 그래픽카드 메모리에
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;
	//bd.MiscFlags = 0;
	//D3D11_SUBRESOURCE_DATA sd;
	//sd.pSysMem = &m_pVertexList.at(0);
	////hr=m_pd3dDevice->CreateBuffer(&bd, NULL,&m_pVertexBuffer);
	//hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	return hr;
}
HRESULT MObject::CreateIndexBuffer()
{
	HRESULT hr = S_OK;
	m_dxObj.m_pIndexBuffer.Attach(DX::CreateIndexBuffer(
		m_pd3dDevice,
		&m_pIndexList.at(0),
		m_iNumIndex,
		sizeof(DWORD)));
	//D3D11_BUFFER_DESC bd;
	//bd.ByteWidth = sizeof(DWORD)*m_iNumIndex;
	//bd.Usage = D3D11_USAGE_DEFAULT; // 그래픽카드 메모리에
	//bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//bd.CPUAccessFlags = 0;
	//bd.MiscFlags = 0;
	//D3D11_SUBRESOURCE_DATA sd;
	//sd.pSysMem = &m_pIndexList.at(0);	
	//hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer);
	return hr;
}
HRESULT MObject::CreateConstantBuffer()
{
	HRESULT hr = S_OK;
	m_dxObj.m_pConstantBuffer.Attach(DX::CreateConstantBuffer(
		m_pd3dDevice,
		&m_cbData,
		1,
		sizeof(VS_CB)));
	//D3D11_BUFFER_DESC bd;
	//bd.ByteWidth = sizeof(VS_CB);
	//bd.Usage = D3D11_USAGE_DEFAULT; // 그래픽카드 메모리에
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//bd.MiscFlags = 0;
	//D3D11_SUBRESOURCE_DATA sd;
	//sd.pSysMem = &m_cbData;
	//hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pConstantBuffer);
	//
	return hr;
}

HRESULT MObject::LoadShaderFile(T_STR szShaderFileName)
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = 0;
	ID3DBlob* pErrorBuf = nullptr;
	m_dxObj.m_pVS.Attach(DX::LoadVertexShaderFile(m_pd3dDevice,
		szShaderFileName.c_str(),
		0,
		"VS",
		"vs_5_0",
		&m_dxObj.m_pVSBuf));
	if (m_dxObj.m_pVS.Get() == nullptr)
	{
		hr = E_FAIL;
	}
	m_dxObj.m_pPS.Attach(DX::LoadPixelShaderFile(m_pd3dDevice,
		szShaderFileName.c_str(),
		0,
		"PS",
		"ps_5_0",
		nullptr));
	if (m_dxObj.m_pPS.Get() == nullptr)
	{
		hr = E_FAIL;
	}
	return hr;
}
HRESULT MObject::SetInputLayout()
{
	HRESULT hr = S_OK;
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{  "POSITION", 0,	DXGI_FORMAT_R32G32B32_FLOAT,0,0,
							D3D11_INPUT_PER_VERTEX_DATA, 0},
		{  "NORMAL", 0,		DXGI_FORMAT_R32G32B32_FLOAT,0,12,
							D3D11_INPUT_PER_VERTEX_DATA, 0},
		{  "COLOR", 0,		DXGI_FORMAT_R32G32B32A32_FLOAT,0,24,
							D3D11_INPUT_PER_VERTEX_DATA, 0},
		{  "TEXCOORD", 0,	DXGI_FORMAT_R32G32_FLOAT,0,40,
							D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT iNumElement = sizeof(layout) / sizeof(layout[0]);
	m_dxObj.m_pVertexLayout.Attach(DX::CreateInputlayout(
		m_pd3dDevice,
		m_dxObj.m_pVSBuf->GetBufferSize(),
		m_dxObj.m_pVSBuf->GetBufferPointer(),
		layout,
		iNumElement));

	/*UINT iNumElement = sizeof(layout) / sizeof(layout[0]);
	hr = m_pd3dDevice->CreateInputLayout(
		layout,
		iNumElement,
		m_pVSBuf->GetBufferPointer(),
		m_pVSBuf->GetBufferSize(),
		&m_pVertexLayout);

	if (m_pVSBuf)m_pVSBuf->Release();*/
	return hr;
}
bool MObject::LoadTexture(
	ID3D11Device* pd3dDevice,
	const TCHAR* pTextureFileName)
{
	if (pTextureFileName == nullptr) return true;
	m_pTexture[0] = I_Tex.GetPtr(I_Tex.Load(pd3dDevice, pTextureFileName));
	T_STR szMask = L"Mask";
	szMask += pTextureFileName;
	m_pTexture[1] = I_Tex.GetPtr(I_Tex.Load(pd3dDevice, szMask.c_str()));
	return true;
}
bool MObject::Create(
	ID3D11Device * pd3dDevice,
	ID3D11DeviceContext * pContext,
	const TCHAR* pTextureFileName,
	const TCHAR* pShaderFileName)
{
	HRESULT hr;
	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;

	Init();

	CreateVertexData();
	CreateIndexData();
	CreateConstantData();

	if (FAILED(CreateVertexBuffer()))
	{
		return false;
	}
	if (FAILED(CreateIndexBuffer()))
	{
		return false;
	}
	if (FAILED(CreateConstantBuffer()))
	{
		return false;
	}
	if (FAILED(LoadShaderFile(pShaderFileName)))
	{
		return false;
	}
	if (FAILED(SetInputLayout()))
	{
		return false;
	}

	if (FAILED(LoadTexture(pd3dDevice, pTextureFileName)))
	{
		return false;
	}
	return true;
}

bool MObject::Init()
{
	return true;
}
bool MObject::Frame()
{
	return true;
}

bool MObject::PreRender()
{
	m_dxObj.PreRender(m_pContext, sizeof(PNCT_VERTEX));
	return true;
}
bool MObject::Render()
{
	PreRender();

	m_pContext->UpdateSubresource(
		m_dxObj.m_pConstantBuffer.Get(), 0, NULL,
		&m_cbData, 0, 0);

	if (m_pTexture[0] != nullptr)
		m_pContext->PSSetShaderResources(0, 1, &m_pTexture[0]->m_pSRV);
	if (m_pTexture[1] != nullptr)
		m_pContext->PSSetShaderResources(1, 1, &m_pTexture[1]->m_pSRV);
	m_pContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pContext->OMSetBlendState(m_pBlendState, 0, 0xff);

	PostRender();
	return true;
}
bool MObject::PostRender()
{
	m_dxObj.PostRender(m_pContext, m_iNumIndex);
	return true;
}
bool MObject::Release()
{

	return true;
}

MObject::MObject()
{
	m_pBlendState = nullptr;
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
}

MObject::~MObject()
{
}
