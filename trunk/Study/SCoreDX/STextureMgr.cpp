#include "STextureMgr.h"

HRESULT STexture::Load(ID3D11Device* pDevice, const TCHAR* strFilePath)
{
	if (strFilePath == NULL) return S_OK;
	HRESULT hr = S_OK;
	TCHAR szFileName[MAX_PATH] = { 0, };
	_stprintf_s(szFileName, _T("%s%s"), m_szPath.c_str(), strFilePath);
	m_szName = strFilePath;

	D3DX11_IMAGE_LOAD_INFO loadInfo;
	ZeroMemory(&loadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
	loadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	loadInfo.Format = DXGI_FORMAT_FROM_FILE;

	hr = D3DX11CreateShaderResourceViewFromFile(pDevice, szFileName, &loadInfo, NULL, &m_pTextureRV, NULL);
	if (FAILED(hr))
	{
		return hr;
	}
	return hr;
}
bool STexture::Apply(ID3D11DeviceContext* pImmediateContext)
{
	assert(pImmediateContext);
	if (!m_pTextureRV)
	{
		return false;
	}
	pImmediateContext->PSSetShaderResources(0, 1, &m_pTextureRV);

	return true;
}
bool STexture::Release()
{
	SAFE_RELEASE(m_pTextureRV);
	SAFE_RELEASE(m_pSamplerState);

	return true;
}

STexture::STexture(void)
{
	SAFE_ZERO(m_pTextureRV);
	SAFE_ZERO(m_pSamplerState);
	m_szPath = _T("");
}
STexture::~STexture(void)
{
}

void STexture::SetPath(const TCHAR* pPath)
{
	m_szPath = pPath;
}

INT STextureMgr::Add(ID3D11Device* pDevice, const TCHAR *pFileName)
{
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	if (pFileName)
	{
		_tsplitpath(pFileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		memset(szFileName, 0, sizeof(TCHAR) * MAX_PATH);

		if (_tcsicmp(Ext, _T(".tga")) == 0)
		{
			_tcscpy(Ext, _T(".bmp"));
		}
		_stprintf_s(szFileName, _T("%s%s"), FName, Ext);

		for (TemplateMapItor itor = SMap.begin(); itor != SMap.end(); itor++)
		{
			STexture *pPoint = (STexture *)(*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szFileName))
			{
				return (*itor).first;
			}
		}
	}
	STexture *pPoint = NULL;
	SAFE_NEW(pPoint, STexture);

	TCHAR szPath[MAX_PATH] = { 0, };
	_stprintf_s(szPath, _T("%s%s"), Drive, Dir);
	pPoint->SetPath(szPath);

	if (FAILED(pPoint->Load(pDevice, szFileName)))
	{
		return 0;
	}
	SMap.insert(make_pair(++m_iCurIndex, pPoint));
	return m_iCurIndex;
}
INT STextureMgr::Add(ID3D11Device* pDevice, const TCHAR *pFileName, const TCHAR* szPath)
{
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	if (pFileName)
	{
		_tsplitpath(pFileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		memset(szFileName, 0, sizeof(TCHAR) * MAX_PATH);
		if (_tcsicmp(Ext, _T(".tga")) == 0)
		{
			_tcscpy(Ext, _T(".dds"));
		}
		_stprintf_s(szFileName, _T("%s%s"), FName, Ext);

		for (TemplateMapItor itor = SMap.begin(); itor != SMap.end(); itor++)
		{
			STexture *pPoint = (STexture *)(*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szFileName))
			{
				return (*itor).first;
			}
		}
	}
	STexture *pPoint = NULL;
	SAFE_NEW(pPoint, STexture);
	pPoint->SetPath(szPath);

	if (FAILED(pPoint->Load(pDevice, szFileName)))
	{
		return 0;
	}
	SMap.insert(make_pair(++m_iCurIndex, pPoint));
	return m_iCurIndex;
}
bool STextureMgr::Release()
{
	STexture *pPoint;
	for (TemplateMapItor itor = SMap.begin(); itor != SMap.end(); itor++)
	{
		pPoint = (STexture *)(*itor).second;
		pPoint->Release();
	}
	SMap.clear();
	return true;
}
STexture* const STextureMgr::GetPtr(INT iIndex)
{
	TemplateMapItor itor = SMap.find(iIndex);
	if (itor == SMap.end())	return NULL;
	STexture *pPoint = (*itor).second;
	return pPoint;
}
STexture* const STextureMgr::GetPtr(T_STR strFindName)
{
	for (TemplateMapItor itor = SMap.begin(); itor != SMap.end(); itor++)
	{
		STexture *pPoint = (STexture *)(*itor).second;
		if (pPoint->m_szName == strFindName)
		{
			return (*itor).second;
		}
	}
	return NULL;
}

STextureMgr::STextureMgr(void)
{
	m_pd3dDevice = NULL;
	m_iCurIndex = 0;
	SMap.clear();
}
STextureMgr::~STextureMgr(void)
{
	STexture *pPoint;
	for (TemplateMapItor itor = SMap.begin(); itor != SMap.end(); itor++)
	{
		pPoint = (STexture *)(*itor).second;
		pPoint->Release();
		SAFE_DEL(pPoint);
	}
	SMap.clear();
	m_iCurIndex = 0;
}