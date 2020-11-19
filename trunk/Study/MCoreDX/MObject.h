#pragma once
#include "MTextureMgr.h"
#include "MMath.h"

struct M_PLANE
{
	float fA, fB, fC, fD;
	void CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2)
	{
		D3DXVECTOR3 vEdge0 = v1 - v0;
		D3DXVECTOR3 vEdge1 = v2 - v0;
		D3DXVECTOR3 vNormal;
		D3DXVec3Cross(&vNormal, &vEdge0, &vEdge1);
		D3DXVec3Normalize(&vNormal, &vNormal);
		fA = vNormal.x;
		fB = vNormal.y;
		fC = vNormal.z;
		fD = D3DXVec3Dot(&vNormal, &v0);
	}
	void CreatePlane(D3DXVECTOR3 n, D3DXVECTOR3 v)
	{
		D3DXVECTOR3 vNormal;
		D3DXVec3Normalize(&vNormal, &n);
		fA = vNormal.x;
		fB = vNormal.y;
		fC = vNormal.z;
		//fD = -(fA * v0.x + fB * v0.y + fC * v0.z);
		fD = D3DXVec3Dot(&vNormal, &v);
	}
	void Normalize()
	{
		float fLength = sqrt(fA*fA + fB * fB + fC * fC);
		fA = fA / fLength;
		fB = fB / fLength;
		fC = fC / fLength;
		fD = fD / fLength;
	}
};
struct PCT_VERTEX
{
	D3DXVECTOR3 p;   // POSITION
	D3DXVECTOR4 c;	 // COLOR
	Vector2 t;
};
struct PNCT_VERTEX
{
	D3DXVECTOR3 p;   // POSITION
	D3DXVECTOR3 n;   // 정점노말
	D3DXVECTOR4 c;	 // COLOR
	D3DXVECTOR2 t;
	PNCT_VERTEX() {};
	PNCT_VERTEX(const PNCT_VERTEX& v)
	{
		p = v.p;
		n = v.n;
		c = v.c;
		t = v.t;
	}
};
// 상수버퍼는 레지스터(float4) 단위로만 저장되어야 한다.
struct VS_CB
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;
	D3DXVECTOR4 c;
	float x, y, z, fTime;
};
class MObject
{
public:
	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*	m_pContext;
	UINT					m_iNumVertex;
	UINT					m_iNumIndex;
	std::vector<PNCT_VERTEX>	m_pVertexList;
	std::vector<DWORD>		m_pIndexList;

	RECT					m_rt;
	VS_CB					m_cbData;
	D3DXVECTOR3				m_vInitPos;
	D3DXVECTOR3				m_vPos;

	D3DXMATRIX				m_matWorld;
	D3DXMATRIX				m_matView;
	D3DXMATRIX				m_matProj;
public:
	D3DXVECTOR3				m_vLook; //z
	D3DXVECTOR3				m_vUp; //y
	D3DXVECTOR3				m_vRight; //x
	float					m_fYaw;
	float					m_fPitch;
	float					m_fRoll;
	float					m_fRadius;
public:
	DX::MDxObject			m_dxObj;
	MTexture*				m_pTexture[2];
	ID3D11SamplerState*		m_pSamplerState;
	ID3D11BlendState*		m_pBlendState;
	ID3D11RasterizerState*		m_pRS;
	ID3D11DepthStencilState*	m_pDS;
public:
	void	SetMatrix(	D3DXMATRIX* matWorld,
						D3DXMATRIX* matView = nullptr,
						D3DXMATRIX* matProj = nullptr);
	void    SetPos(D3DXVECTOR3 p);
	D3DXVECTOR3  ScreenToNDC(POINT pt);
	void     SetScreenRect(RECT rt)
	{
		m_rt = rt;
	}
	virtual bool Create(
		ID3D11Device* pd3dDevice,
		ID3D11DeviceContext*	pContext,
		const TCHAR* pTextureFileName,
		const TCHAR* pShaderFileName);

	virtual void	CreateVertexData();
	virtual void	CreateIndexData();
	virtual void	CreateConstantData();
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateConstantBuffer();
	virtual HRESULT LoadShaderFile(T_STR szShaderFileName);
	virtual HRESULT SetInputLayout();
	virtual bool	LoadTexture(ID3D11Device * pd3dDevice,
		const TCHAR* pTextureFileName);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();
	virtual bool Release();
public:
	MObject();
	~MObject();
};