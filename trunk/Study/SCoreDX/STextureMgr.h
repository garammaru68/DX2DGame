#pragma once
#include "SBasisStd.h"

class STexture
{
public:
	T_STR	m_szName;
	T_STR	m_szPath;

	ID3D11ShaderResourceView*	m_pTextureRV;
	ID3D11SamplerState*			m_pSamplerState;
	D3D11_SAMPLER_DESC			m_SampleDesc;
public:
	HRESULT		Load(ID3D11Device* pDevice, const TCHAR* strFilePath);
	bool		Apply(ID3D11DeviceContext* pImmediateContext);
	bool		Release();
	void		SetPath(const TCHAR* pPath);
public:
	STexture(void);
	virtual ~STexture(void);
};

class STextureMgr : public SSingleton < STextureMgr >
{
private:
	friend class SSingleton<STextureMgr>;
	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*	m_pImmediateContext;
public:
	typedef unordered_map <INT, STexture*>	TemplateMap;
	typedef TemplateMap::iterator			TemplateMapItor;
	TemplateMapItor							SItor;
	TemplateMap								SMap;
	INT										m_iCurIndex;
public:
	INT				Add(ID3D11Device*	pDevice, const TCHAR *pFileName);
	INT				Add(ID3D11Device*	pDevice, const TCHAR *pFileName, const TCHAR* szPath);
	STexture* const GetPtr(INT iIndex);
	STexture* const GetPtr(T_STR strFindname);
	bool			Release();
public:
	STextureMgr();
	virtual ~STextureMgr();
};
#define I_Texture STextureMgr::GetInstnace()

