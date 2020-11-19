#include "MMap.h"

void MMap::CreateVertexData()
{
	m_iNumCellRows = m_iNumRows - 1;
	m_iNumCellCols = m_iNumCols - 1;
	m_fCellDistance = 1.0f;
	m_iNumVertex = m_iNumRows * m_iNumCols;
	m_pVertexList.resize(m_iNumVertex);
	m_iNumFaces = m_iNumCellRows * m_iNumCellCols * 2;
	// 0	1	2	3	4
	// 5	6	7	8	9
	// 10	11	12	13	14
	// 15	16	17	18	19
	// 20	21	22	23	24
	float fHalfCols = (m_iNumCols - 1) / 2.0f;
	float fHalfRows = (m_iNumRows - 1) / 2.0f;
	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			int iIndex = iRow * m_iNumCols + iCol;
			m_pVertexList[iIndex].p =
				D3DXVECTOR3((iCol - fHalfCols) * m_fCellDistance,
					GetHeightMap(iIndex),
					-(iRow - fHalfRows) * m_fCellDistance);
			m_pVertexList[iIndex].n = D3DXVECTOR3(0, 1.0f, 0);
			m_pVertexList[iIndex].c = D3DXVECTOR4(1, 1.0f, 1, 1);
			m_pVertexList[iIndex].t = D3DXVECTOR2(
				(float)iCol / (m_iNumCols - 1),
				(float)iRow / (m_iNumRows - 1));
		}
	}
}
void MMap::CreateIndexData()
{
	m_iNumIndex = m_iNumFaces * 3;
	m_pIndexList.resize(m_iNumIndex);

	int iIndex = 0;
	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			int iNextRow = (iRow + 1) * m_iNumCols;
			int iNextCol = iCol + 1;
			m_pIndexList[iIndex + 0] = iRow * m_iNumCols + iCol;
			m_pIndexList[iIndex + 1] = m_pIndexList[iIndex + 0] + 1;
			m_pIndexList[iIndex + 2] = iNextRow + iCol;
			m_pIndexList[iIndex + 3] = m_pIndexList[iIndex + 2];
			m_pIndexList[iIndex + 4] = m_pIndexList[iIndex + 1];
			m_pIndexList[iIndex + 5] = m_pIndexList[iIndex + 3] + 1;
			iIndex += 6;
		}
	}
}

float MMap::GetHeightMap(int iIndex)
{
	return 0.0f;
}