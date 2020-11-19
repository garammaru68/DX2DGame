#pragma once
#include "MBitmap.h"
class MBitmapMgr : public MSingleton<MBitmapMgr>
{
	friend class MSingleton<MBitmapMgr>;
private:
	int						m_iCurIndex;
	std::map<int, MBitmap*>	m_Map;
	T_STR					m_csDefaultPath;
public:
	typedef std::map<int, MBitmap*>::iterator MItor;
	void	SetDefaultPath(T_STR szPath)
	{
		m_csDefaultPath = szPath;
	}
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int			Load(HDC hScreenDC, T_STR szLoadName);
	MBitmap*	GetPtr(int iIndex);

private:
	MBitmapMgr();
public:
	~MBitmapMgr();
};

#define I_BitmapMgr MBitmapMgr::GetInstance()