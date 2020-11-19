#include "MBitmapMgr.h"

bool MBitmapMgr::Init()
{
	return true;
}

bool MBitmapMgr::Frame()
{
	for (int iSound = 0; iSound < m_Map.size(); iSound++)
	{
		m_Map[iSound + 1]->Frame();
	}
	return true;
}

bool MBitmapMgr::Render()
{
	for (int iSound = 0; iSound < m_Map.size(); iSound++)
	{
		m_Map[iSound + 1]->Render();
	}
	return true;
}

bool MBitmapMgr::Release()
{
	MBitmap* pData = nullptr;
	for (MItor iter = m_Map.begin(); iter != m_Map.end(); iter++)
	{
		pData = iter->second;
		pData->Release();
		SAFE_DEL(pData);
	}
	m_Map.clear();
	return true;
}

int MBitmapMgr::Load(HDC hScreenDC, T_STR szLoadName)
{
	TCHAR szDrive[MAX_PATH] = { 0, };
	TCHAR szDir[MAX_PATH] = { 0, };
	TCHAR szName[MAX_PATH] = { 0, };
	TCHAR szExt[MAX_PATH] = { 0, };
	_tsplitpath_s(szLoadName.c_str(), szDrive, szDir, szName, szExt);
	T_STR szFileName = szName;
	szFileName += szExt;
	for (MItor itor = m_Map.begin(); itor != m_Map.end(); itor++)
	{
		MBitmap* pData = (*itor).second;
		if (pData->m_csName == szFileName)
		{
			return (*itor).first;
		}
	}

	MBitmap* pData = nullptr;
	SAFE_NEW(pData, MBitmap);
	pData->Init();
	pData->m_csName = szFileName;
	if (pData->Load(hScreenDC, szLoadName))
	{
		m_Map.insert(make_pair(++m_iCurIndex, pData));
		return m_iCurIndex;
	}
	SAFE_DEL(pData);
	return -1;
}

MBitmap* MBitmapMgr::GetPtr(int iIndex)
{
	MItor iter = m_Map.find(iIndex);
	if (iter != m_Map.end())
	{
		return iter->second;
	}
	return nullptr;
}

MBitmapMgr::MBitmapMgr()
{
	m_iCurIndex = 0;
	m_csDefaultPath = L"../../../data/bitmap/";
	Init();
}

MBitmapMgr::~MBitmapMgr()
{
	Release();
}
