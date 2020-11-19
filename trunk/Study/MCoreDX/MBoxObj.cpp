#include "MBoxObj.h"

void MBoxObj::UpdateVertexData(D3DXVECTOR3* vList)
{
	int iVertex = 0;
	//up
	m_pVertexList[16].p		= vList[2];
	m_pVertexList[16].c.w	= 0.5f;
	m_pVertexList[17].p		= vList[1];
	m_pVertexList[17].c.w	= 0.5f;
	m_pVertexList[18].p		= vList[6];
	m_pVertexList[18].c.w	= 0.5f;
	m_pVertexList[19].p		= vList[5];
	m_pVertexList[19].c.w	= 0.5f;

	m_pContext->UpdateSubresource(m_dxObj.m_pVertexBuffer.Get(), 0, NULL, &m_pVertexList.at(0), 0, 0);
	m_iNumVertex = m_pVertexList.size();

}
void MBoxObj::CreateVertexData()
{
	int iVertex = 0;
	m_pVertexList.resize(24);
	m_pVertexList[iVertex].p = { -1.0f, 1.0f, -1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(1, 0, 0, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(0, 0);
	iVertex++;
	m_pVertexList[iVertex].p = { 1.0f, 1.0f, -1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(0, 1, 0, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(1, 0);
	iVertex++;
	m_pVertexList[iVertex].p = { -1.0f, -1.0f, -1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(0, 0, 1, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(0, 1);
	iVertex++;
	m_pVertexList[iVertex].p = { 1.0f, -1.0f, -1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(1, 1, 1, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(1, 1);
	iVertex++;
	// back
	m_pVertexList[iVertex].p = { 1.0f, 1.0f, 1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(1, 0, 0, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(0, 0);
	iVertex++;
	m_pVertexList[iVertex].p = { -1.0f, 1.0f, 1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(0, 1, 0, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(1, 0);
	iVertex++;
	m_pVertexList[iVertex].p = { 1.0f, -1.0f, 1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(0, 0, 1, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(0, 1);
	iVertex++;
	m_pVertexList[iVertex].p = { -1.0f, -1.0f, 1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(1, 1, 1, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(1, 1);
	iVertex++;

	// right
	m_pVertexList[iVertex].p = { 1.0f, 1.0f, -1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(1, 0, 0, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(0, 0);
	iVertex++;
	m_pVertexList[iVertex].p = { 1.0f, 1.0f, 1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(0, 1, 0, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(1, 0);
	iVertex++;
	m_pVertexList[iVertex].p = { 1.0f, -1.0f, -1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(0, 0, 1, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(0, 1);
	iVertex++;
	m_pVertexList[iVertex].p = { 1.0f, -1.0f, 1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(1, 1, 1, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(1, 1);
	iVertex++;
	//left
	m_pVertexList[iVertex].p = { -1.0f, 1.0f, 1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(1, 0, 0, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(0, 0);
	iVertex++;
	m_pVertexList[iVertex].p = { -1.0f, 1.0f, -1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(0, 1, 0, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(1, 0);
	iVertex++;
	m_pVertexList[iVertex].p = { -1.0f, -1.0f, 1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(0, 0, 1, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(0, 1);
	iVertex++;
	m_pVertexList[iVertex].p = { -1.0f, -1.0f, -1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(1, 1, 1, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(1, 1);
	iVertex++;
	//up
	m_pVertexList[iVertex].p = { -1.0f, 1.0f, 1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(1, 0, 0, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(0, 0);
	iVertex++;
	m_pVertexList[iVertex].p = { 1.0f, 1.0f, 1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(0, 1, 0, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(1, 0);
	iVertex++;
	m_pVertexList[iVertex].p = { -1.0f, 1.0f, -1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(0, 0, 1, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(0, 1);
	iVertex++;
	m_pVertexList[iVertex].p = { 1.0f, 1.0f, -1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(1, 1, 1, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(1, 1);
	iVertex++;
	//down
	m_pVertexList[iVertex].p = { -1.0f, -1.0f, -1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(1, 0, 0, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(0, 0);
	iVertex++;
	m_pVertexList[iVertex].p = { 1.0f, -1.0f, -1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(0, 1, 0, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(1, 0);
	iVertex++;
	m_pVertexList[iVertex].p = { -1.0f, -1.0f, 1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(0, 0, 1, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(0, 1);
	iVertex++;
	m_pVertexList[iVertex].p = { 1.0f, -1.0f, 1.0f };
	m_pVertexList[iVertex].n = D3DXVECTOR3(0, 0, -1);
	m_pVertexList[iVertex].c = D3DXVECTOR4(1, 1, 1, 1);
	m_pVertexList[iVertex].t = D3DXVECTOR2(1, 1);

	m_iNumVertex = m_pVertexList.size();
}
void MBoxObj::CreateIndexData()
{
	m_pIndexList.resize(36);
	int iIndex = 0;
	m_pIndexList[iIndex++] = 0; m_pIndexList[iIndex++] = 1; m_pIndexList[iIndex++] = 2;
	m_pIndexList[iIndex++] = 2; m_pIndexList[iIndex++] = 1; m_pIndexList[iIndex++] = 3;

	m_pIndexList[iIndex++] = 4; m_pIndexList[iIndex++] = 5; m_pIndexList[iIndex++] = 6;
	m_pIndexList[iIndex++] = 6; m_pIndexList[iIndex++] = 5; m_pIndexList[iIndex++] = 7;

	m_pIndexList[iIndex++] = 8; m_pIndexList[iIndex++] = 9; m_pIndexList[iIndex++] = 10;
	m_pIndexList[iIndex++] = 10; m_pIndexList[iIndex++] = 9; m_pIndexList[iIndex++] = 11;

	m_pIndexList[iIndex++] = 12; m_pIndexList[iIndex++] = 13; m_pIndexList[iIndex++] = 14;
	m_pIndexList[iIndex++] = 14; m_pIndexList[iIndex++] = 13; m_pIndexList[iIndex++] = 15;

	m_pIndexList[iIndex++] = 16; m_pIndexList[iIndex++] = 17; m_pIndexList[iIndex++] = 18;
	m_pIndexList[iIndex++] = 18; m_pIndexList[iIndex++] = 17; m_pIndexList[iIndex++] = 19;

	m_pIndexList[iIndex++] = 20; m_pIndexList[iIndex++] = 21; m_pIndexList[iIndex++] = 22;
	m_pIndexList[iIndex++] = 22; m_pIndexList[iIndex++] = 21; m_pIndexList[iIndex++] = 23;
	m_iNumIndex = m_pIndexList.size();
}
