#pragma once
#include "MDxHelperEx.h"
class MDxRT
{
public:
	ComPtr<ID3D11RenderTargetView>		m_pRTV;
	ComPtr<ID3D11DepthStencilView>		m_pDSV;
	ComPtr<ID3D11ShaderResourceView>	m_pRT_SRV;
	ComPtr<ID3D11ShaderResourceView>	m_pDS_SRV;
	ComPtr<ID3D11Texture2D>				m_pTexRT;
	ComPtr<ID3D11Texture2D>				m_pTexDS;
public:
	D3D11_TEXTURE2D_DESC			m_TexDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC	m_DepthStencilDesc;
	D3D11_VIEWPORT					m_vp;
public:
	HRESULT Create(ID3D11Device* pd3dDevice, UINT w, UINT h);
	bool	Begin(ID3D11DeviceContext* pContext);
	bool	End(ID3D11DeviceContext* pContext);
};

