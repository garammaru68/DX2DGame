#pragma once
#include "MSprite.h"

class MSpriteMgr : public MSingleton<MSpriteMgr>
{
	friend class MSingleton<MSpriteMgr>;
	std::map<int, MSprite*>	m_Map;
	typedef std::map<int, MSprite*>::iterator MItor;
	int			m_iIndex;
public:
	bool Load(const TCHAR* pszLoad);
	bool Release();
	MSprite* GetPtr(int iIndex);
	int GetSize() { return m_Map.size(); }
public:
	MSpriteMgr();
	~MSpriteMgr();
};
#define I_Sprite MSpriteMgr::GetInstance()

