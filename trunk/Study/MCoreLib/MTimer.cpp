#include "MTimer.h"
float	g_fSecondPerFrame = 0.0f;
float	g_fTimer = 0.0f;

bool	MTimer::Init()
{
	m_dwBeforeTick = timeGetTime();
	m_BeforeClock = MClock::now();
	return true;
}
bool	MTimer::Frame()
{
	//DWORD dwCurrentTick = timeGetTime();
	//DWORD dwElapseTick = dwCurrentTick - m_dwBeforeTick;
	//m_fSecondPerFrame = dwElapseTick / 1000.0f;
	//m_fTimer += m_fSecondPerFrame;
	//m_dwBeforeTick = dwCurrentTick;


	//m_fFrameTime += m_fSecondPerFrame;
	//if (m_fFrameTime > 1.0f)
	//{		
	//	m_dwFPS = m_dwFrameCnt;
	//	m_dwFrameCnt = 0;
	//	m_fFrameTime = m_fFrameTime - 1.0f;
	//}
	//m_dwFrameCnt++;
	//m_dwBeforeTick = dwCurrentTick;


	MClock::time_point current= MClock::now();
	MMilliSeconds ElapseClock = std::chrono::duration_cast<MMilliSeconds>(current - m_BeforeClock);
	
	m_fSecondPerFrame = ElapseClock.count() / 1000.0f;
	m_fTimer += m_fSecondPerFrame;
	g_fSecondPerFrame = m_fSecondPerFrame;
	g_fTimer = m_fTimer;

	m_fFrameTime += m_fSecondPerFrame;
	if (m_fFrameTime > 1.0f)
	{
		m_dwFPS = m_dwFrameCnt;
		m_dwFrameCnt = 0;
		m_fFrameTime = m_fFrameTime - 1.0f;
	}
	m_dwFrameCnt++;

	m_BeforeClock = current;

	_stprintf_s(m_csBuffer, L"%10.4f:%d", m_fTimer, m_dwFPS);
	return true;
}
bool	MTimer::Render()
{
	return true;
}
bool	MTimer::Release()
{
	return true;
}

MTimer::MTimer() 
{
	m_fSecondPerFrame = 0.0f;
	m_fTimer = 0.0f;
	m_fFrameTime = 0.0f;
	m_dwFrameCnt = 0;
	m_dwFPS = 0;
}
MTimer::~MTimer() {}
