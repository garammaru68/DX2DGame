#pragma once
#include "TBasisLib.h"
#include "TMiniMap.h"

#define NUM_OBJECTS 100
//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
};

class Sample : public TBasisLib
{
public:
	//--------------------------------------------------------------------------------------
	// ���� ���� ��ü 
	//--------------------------------------------------------------------------------------
	TCamera						m_MainCamera;
	TShape*						m_pBoxShape;
	TMiniMap					m_MiniMap;
	ComPtr<ID3D11PixelShader>   m_pPixelShader;// ���ν��� ���� �Ƚ����̴�

	//TCamera							m_MainCamera;
	//TShape*							m_pBoxShape;
	//TMiniMap						m_MiniMap;
	//ID3D11DepthStencilState*		m_pDepthStencilStateDepthEnable;
	TShape*							m_pLine;

public:
	//--------------------------------------------------------------------------------------
	// Matrix
	//--------------------------------------------------------------------------------------
	D3DXMATRIX					m_matBoxWorld[NUM_OBJECTS];
	D3DXVECTOR3					m_vBoxPosition[NUM_OBJECTS];
	D3DXVECTOR4					m_vBoxColor[NUM_OBJECTS];

	T_BOX								m_TBox[NUM_OBJECTS];
	T_BOX								m_TBoxBase;
	//--------------------------------------------------------------------------------------
	// ����Ʈ ����
	//--------------------------------------------------------------------------------------	
	TDxRT							m_MiniMapVP;
	HRESULT							ScreenViewPort(UINT iWidth, UINT iHeight);
	//--------------------------------------------------------------------------------------
	// ī�޶� ȸ�� ����
	//--------------------------------------------------------------------------------------
	float									m_fCameraYaw;
	float									m_fCameraPitch;
	float									m_fCameraRoll;
	float									m_fRadius;

public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	bool		DrawDebug(bool bDrawString, bool bDrawLine);
	void		DrawMiniMap();

	//--------------------------------------------------------------------------------------
	// ����� Ŭ���̾�Ʈ ������ �缳���� ���� �Ҹ� �� ����
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

public:
	Sample(void);
	virtual ~Sample(void);
};
