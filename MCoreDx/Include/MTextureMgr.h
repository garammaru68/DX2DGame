#pragma once
#include "MTexture.h"
class MTextureMgr : public MSingleton<MTextureMgr>
{
	friend class MSingleton<MTextureMgr>;
private:
	int		m_iCurIndex;
	std::map<int, MTexture*> m_Map;
	T_STR	m_csDefaultPath;
public:
	typedef std::map<int, MTexture*>::iterator MItor;
	void	SetDefaultPath(T_STR szPath)
	{
		m_csDefaultPath = szPath;
	}
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	int  Load(ID3D11Device*, T_STR szName);
	MTexture* GetPtr(int iIndex);
private:
	MTextureMgr();
public:
	~MTextureMgr();
};

#define I_Tex MTextureMgr::GetInstance()

