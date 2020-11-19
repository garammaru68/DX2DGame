#pragma once
#include "MSound.h"
class MSoundMgr : public MSingleton<MSoundMgr>
{
	friend class MSingleton<MSoundMgr>;
private:
	int						m_iCurIndex;
	std::map<int, MSound*>  m_Map;
	FMOD::System*			m_pSystem;
	T_STR					m_csDefaultPath;
public:
	typedef std::map<int, MSound*>::iterator MItor;
	//// Singleton
	//static MSoundMgr& GetInstance()
	//{
	//	static MSoundMgr mgr;
	//	return mgr;
	//}
	void	SetDefalutPath(T_STR szPath)
	{
		m_csDefaultPath = szPath;
	}
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	int		Load(T_STR szLoadName);
	MSound* GetPtr(int iIndex);
	
private:
	MSoundMgr();
public:
	~MSoundMgr();
};

#define I_SoundMgr MSoundMgr::GetInstance()