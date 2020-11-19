#include "MLineObj.h"
bool MLineObj::Draw(ID3D11DeviceContext* pContext,
	D3DXVECTOR3 vStart,
	D3DXVECTOR3 vEnd,
	D3DXVECTOR4 Color)
{
	m_pVertexList[0].p = vStart;
	m_pVertexList[0].c = Color;
	m_pVertexList[1].p = vEnd;
	m_pVertexList[1].c = Color;
	pContext->UpdateSubresource(m_dxObj.m_pVertexBuffer.Get(),
		0, NULL, &m_pVertexList.at(0), 0, 0);
	m_dxObj.m_iPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
	return Render();
}
void MLineObj::CreateVertexData()
{
	m_dxObj.m_iPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_LINELIST;

	m_pVertexList.resize(2);
	m_pVertexList[0].p = { 0.0f, 0.0f, 0.0f };
	m_pVertexList[0].n = D3DXVECTOR3(0, 0, 1);
	m_pVertexList[0].c = D3DXVECTOR4(1, 0, 0, 1);
	m_pVertexList[0].t = D3DXVECTOR2(0, 0);

	m_pVertexList[1].p = { 1.0f, 0.0f, 0.0f };
	m_pVertexList[1].n = D3DXVECTOR3(0, 0, 1);
	m_pVertexList[1].c = D3DXVECTOR4(0, 1, 0, 1);
	m_pVertexList[1].t = D3DXVECTOR2(1, 0);
	m_iNumVertex = m_pVertexList.size();
}
void MLineObj::CreateIndexData()
{
	m_pIndexList.resize(2);
	m_pIndexList[0] = 0;
	m_pIndexList[1] = 1;

	m_iNumIndex = m_pIndexList.size();
}
void MDirectionLineObj::CreateVertexData()
{
	m_dxObj.m_iPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_LINELIST;

	m_pVertexList.resize(6);
	m_pVertexList[0].p = { 0.0f, 0.0f, 0.0f };
	m_pVertexList[0].n = D3DXVECTOR3(0, 0, 1);
	m_pVertexList[0].c = D3DXVECTOR4(1, 0, 0, 1);
	m_pVertexList[0].t = D3DXVECTOR2(0, 0);

	m_pVertexList[1].p = { 100000.0f, 0.0f, 0.0f };
	m_pVertexList[1].n = D3DXVECTOR3(0, 0, 1);
	m_pVertexList[1].c = D3DXVECTOR4(1, 0, 0, 1);
	m_pVertexList[1].t = D3DXVECTOR2(1, 0);

	m_pVertexList[2].p = { 0.0f, 0.0f, 0.0f };
	m_pVertexList[2].n = D3DXVECTOR3(0, 0, 1);
	m_pVertexList[2].c = D3DXVECTOR4(0, 1, 0, 1);
	m_pVertexList[2].t = D3DXVECTOR2(0, 0);

	m_pVertexList[3].p = { 0, 100000.0f, 0.0f };
	m_pVertexList[3].n = D3DXVECTOR3(0, 0, 1);
	m_pVertexList[3].c = D3DXVECTOR4(0, 1, 0, 1);
	m_pVertexList[3].t = D3DXVECTOR2(1, 0);

	m_pVertexList[4].p = { 0.0f, 0.0f, 0.0f };
	m_pVertexList[4].n = D3DXVECTOR3(0, 0, 1);
	m_pVertexList[4].c = D3DXVECTOR4(0, 0, 1, 1);
	m_pVertexList[4].t = D3DXVECTOR2(0, 0);

	m_pVertexList[5].p = { 0.0f, 0.0f, 100000.0f };
	m_pVertexList[5].n = D3DXVECTOR3(0, 0, 1);
	m_pVertexList[5].c = D3DXVECTOR4(0, 0, 1, 1);
	m_pVertexList[5].t = D3DXVECTOR2(1, 0);
	m_iNumVertex = m_pVertexList.size();
}
void MDirectionLineObj::CreateIndexData()
{
	m_pIndexList.resize(6);
	m_pIndexList[0] = 0;
	m_pIndexList[1] = 1;
	m_pIndexList[2] = 2;
	m_pIndexList[3] = 3;
	m_pIndexList[4] = 4;
	m_pIndexList[5] = 5;
	m_iNumIndex = m_pIndexList.size();
}