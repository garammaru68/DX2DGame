#include "MSoundMgr.h"

bool	MSoundMgr::Init()
{
	FMOD_RESULT hr;
	hr = FMOD::System_Create(&m_pSystem);
	if (hr != FMOD_OK) return false;
	hr = m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	if (hr != FMOD_OK) return false;
	return true;
}
bool	MSoundMgr::Frame()
{
	for (int iSound=0;iSound< m_Map.size(); iSound++)
	{
		m_Map[iSound + 1]->Frame();
	}
	m_pSystem->update();
	return true;
}
bool	MSoundMgr::Render()
{
	for (int iSound = 0; iSound < m_Map.size(); iSound++)
	{
		m_Map[iSound + 1]->Render();
	}
	return true;
}
int		MSoundMgr::Load(T_STR szLoadName)
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
		MSound* pData = (*itor).second;
		if (pData->m_csName == szFileName)
		{
			return (*itor).first;
		}
	}

	MSound* pData = new MSound;
	SAFE_NEW(pData, MSound);
	pData->Init();
	pData->m_csName = szFileName;
	if (pData->Load(szLoadName, m_pSystem))
	{
		m_Map.insert(make_pair(++m_iCurIndex, pData));
		return m_iCurIndex;
	}
	SAFE_DEL(pData);
	return -1;
}
MSound* MSoundMgr::GetPtr(int iIndex)
{
	MItor iter = m_Map.find(iIndex);
	if (iter != m_Map.end())
	{
		return iter->second;
	}
	return nullptr;
}
bool MSoundMgr::Release()
{
	MSound* pData = nullptr;
	for (MItor iter = m_Map.begin();
		 iter != m_Map.end();
			iter++)
	{
		pData = iter->second;
		pData->Release();
		SAFE_DEL(pData);
	}
	m_Map.clear();
	m_pSystem->close();
	m_pSystem->release();
	return true;
}
MSoundMgr::MSoundMgr()
{
	m_iCurIndex = 0;
	m_pSystem = nullptr;
	m_csDefaultPath = L"../../../data/sound/";
	Init();
}
MSoundMgr::~MSoundMgr()
{
	Release();
}