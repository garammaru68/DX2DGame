#include "MHeightMap.h"

bool MHeightMap::CreateHeightMap(ID3D11Device* pd3dDevice, const TCHAR* szFileName)
{
	HRESULT hr;
	D3DX11_IMAGE_INFO ImageInfo;
	D3DX11_IMAGE_LOAD_INFO loadinfo;
	ZeroMemory(&loadinfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
	loadinfo.Usage = D3D11_USAGE_STAGING;
	loadinfo.CpuAccessFlags = D3D11_CPU_ACCESS_READ;
	loadinfo.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	loadinfo.pSrcInfo = &ImageInfo;
	loadinfo.MipLevels = 1;
	ID3D11Resource* pResource;
	if (FAILED(hr = D3DX11CreateTextureFromFile(pd3dDevice,
		szFileName,
		&loadinfo, NULL,
		&pResource, NULL)))
	{

	}
	ID3D11Texture2D* pTex2D;
	pResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&pTex2D);
	pResource->Release();

	D3D11_TEXTURE2D_DESC pDesc;
	pTex2D->GetDesc(&pDesc);
	
	m_iNumRows = pDesc.Height;
	m_iNumCols = pDesc.Width;

	m_fHeightList.resize(pDesc.Height * pDesc.Width);
	return false;
}

float MHeightMap::GetHeightMap(int iIndex)
{
	return m_fHeightList[iIndex];
}

MHeightMap::MHeightMap()
{
}
MHeightMap::~MHeightMap()
{
}