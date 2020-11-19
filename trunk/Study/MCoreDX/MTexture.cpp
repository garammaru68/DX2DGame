#include "MTexture.h"
bool MTexture::Frame()
{
	return true;
}
bool MTexture::Render()
{
	return true;
}
bool MTexture::Init()
{
	return true;
}

bool MTexture::Load(ID3D11Device* pd3dDevice, T_STR szLoadFileName)
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(pd3dDevice, szLoadFileName.c_str(), NULL, NULL, &m_pSRV, NULL);
	return true;
}
bool MTexture::Release()
{
	if (m_pSRV)m_pSRV->Release();
	return true;
}

MTexture::MTexture()
{
	m_pSRV = nullptr;
}
MTexture::~MTexture()
{

}