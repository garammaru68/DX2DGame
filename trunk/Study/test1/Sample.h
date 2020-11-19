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
	// 각종 지원 객체 
	//--------------------------------------------------------------------------------------
	TCamera						m_MainCamera;
	TShape*						m_pBoxShape;
	TMiniMap					m_MiniMap;
	ComPtr<ID3D11PixelShader>   m_pPixelShader;// 프로스텀 전용 픽쉘쉐이더

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
	// 뷰포트 설정
	//--------------------------------------------------------------------------------------	
	TDxRT							m_MiniMapVP;
	HRESULT							ScreenViewPort(UINT iWidth, UINT iHeight);
	//--------------------------------------------------------------------------------------
	// 카메라 회전 정보
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
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();

public:
	Sample(void);
	virtual ~Sample(void);
};
