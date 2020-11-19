#pragma once
#include "MBaseObject.h"
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>
class MSound : public MBaseObject
{
private:
	FMOD::System*	m_pSystem;
	FMOD::Sound*	m_pSound;
	FMOD::Channel*	m_pChannel;
public:
	T_STR			m_csName;
	float			m_fVolume;
	unsigned int	m_msLength;
	TCHAR			m_csBuffer[256];
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
public:
	void	Paused();
	void	Stop();
	void	VolumeUp();
	void	VolumeDown();
	void	SetMode(DWORD dwMode=FMOD_LOOP_NORMAL);
public:
	bool	Load(T_STR szLoadName, FMOD::System* pSystem);
	void	Play();
	void	PlayEffect();
public:
	MSound();
	virtual ~MSound();
};

