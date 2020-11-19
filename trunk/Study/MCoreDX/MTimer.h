#pragma once
#include "MStd.h"
#include <chrono>
class MTimer
{
public:
	T_STR		m_csName;
	TCHAR		m_csBuffer[MAX_PATH];
	float		m_fSecondPerFrame;
	float		m_fTimer;
	float		m_fFrameTime;
	DWORD		m_dwBeforeTick;
	DWORD		m_dwFrameCnt;
	int			m_dwFPS;

public:
	typedef std::chrono::high_resolution_clock	MClock;
	typedef std::chrono::milliseconds			MMilliSeconds;
	MClock::time_point m_BeforeClock;
public:
	virtual bool	Init();		// 초기화
	virtual bool	Frame();	// 계산
	virtual bool	Render();	// 드로우
	virtual bool	Release();	// 소멸
public:
	MTimer();
	virtual ~MTimer();
};


