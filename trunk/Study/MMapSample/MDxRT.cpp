#include "MDxRT.h"
#include "MStd.h"

HRESULT MDxRT::Create(ID3D11Device * pd3dDevice, UINT w, UINT h)
{
	HRESULT hr = S_OK;
	m_TexDesc.Width = w;
	m_TexDesc.Height = h;
	m_TexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_TexDesc.ArraySize = 1;
	m_TexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	m_TexDesc.CPUAccessFlags = 0;
	m_TexDesc.MipLevels = 1;
	m_TexDesc.SampleDesc.Count = 1;
	m_TexDesc.SampleDesc.Quality = 0;
	m_TexDesc.Usage = D3D11_USAGE_DEFAULT;

	if (FAILED(hr = pd3dDevice->CreateTexture2D(&m_TexDesc, NULL, m_pTexRT.GetAddressOf())))
	{
		return hr;
	}
	if (FAILED(hr = pd3dDevice->CreateRenderTargetView(m_pTexRT.Get(), NULL, m_pRTV.GetAddressOf())))
	{
		return hr;
	}
	if (FAILED(hr = pd3dDevice->CreateShaderResourceView(m_pTexRT.Get(), NULL, m_pRT_SRV.GetAddressOf())))
	{
		return hr;
	}

	m_TexDesc.Width = w;
	m_TexDesc.Height = h;
	m_TexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	m_TexDesc.ArraySize = 1;
	m_TexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	m_TexDesc.CPUAccessFlags = 0;
	m_TexDesc.MipLevels = 1;
	m_TexDesc.MiscFlags = 0;
	m_TexDesc.SampleDesc.Count = 1;
	m_TexDesc.SampleDesc.Quality = 0;
	m_TexDesc.Usage = D3D11_USAGE_DEFAULT;

	if (FAILED(hr = pd3dDevice->CreateTexture2D(&m_TexDesc, NULL, m_pTexDS.GetAddressOf())))
	{
		return hr;
	}
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = m_TexDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	if (FAILED(hr = pd3dDevice->CreateDepthStencilView(m_pTexDS.Get(), NULL, m_pDSV.GetAddressOf())))
	{
		return hr;
	}
	if (dsvDesc.Format == DXGI_FORMAT_R32_TYPELESS)
	{
		if (FAILED(hr = pd3dDevice->CreateShaderResourceView(m_pTexDS.Get(), NULL, m_pDS_SRV.GetAddressOf())))
		{
			return hr;
		}
	}

	m_vp.TopLeftX = 0;
	m_vp.TopLeftY = 0;
	m_vp.MinDepth = 0.0f;
	m_vp.MaxDepth = 1.0f;
	m_vp.Width = w;
	m_vp.Height = h;
	return hr;
}

bool MDxRT::Begin(ID3D11DeviceContext * pContext)
{
	ID3D11RenderTargetView* pNullRTV = NULL;
	ID3D11DepthStencilView* pNUllDSV = NULL;
	pContext->OMSetRenderTargets(1, &pNullRTV, pNUllDSV);
	pContext->OMSetRenderTargets(1, m_pRTV.GetAddressOf(), m_pDSV.Get());
	pContext->RSSetViewports(1, &m_vp);

	float fColor[4] = { cos(g_fTimer) * 0.5f + 0.5f, 0, 0, 1 };
	pContext->ClearRenderTargetView(m_pRTV.Get(), fColor);
	pContext->ClearDepthStencilView(m_pDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	return true;
}
bool MDxRT::End(ID3D11DeviceContext * pContext)
{
	HRESULT hr;
	//// 랜더타겟뷰에서 텍스처 파일로 저장
	//if (m_pTexRT.Get() != nullptr)
	//{
	//	// 랜더타겟 텍스처를 텍스처 파일로 저장
	//	if (FAILED(hr = D3DX11SaveTextureToFile(pContext, m_pTexRT.Get(), D3DX11_IFF_BMP, L"save.bmp")))
	//	{
	//		return true;
	//	}
	//}
	ID3D11RenderTargetView* pNullRTV = NULL;
	ID3D11DepthStencilView* pNullDSV = NULL;
	pContext->OMSetRenderTargets(1, &pNullRTV, pNullDSV);
	return true;
}