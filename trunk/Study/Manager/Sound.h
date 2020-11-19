#pragma once
#include "MBaseObject.h"
class Sound : public MBaseObject
{
private:
	TCHAR	m_ClsName;
public:
	virtual bool	Init()		override;
	virtual bool	Frame()		override;
	virtual bool	Render()	override;
	virtual bool	Release()	override;
public:
	bool	Load(TCHAR ftName);
	void	Play();
public:
	Sound() {};
	virtual ~Sound() {};
};

