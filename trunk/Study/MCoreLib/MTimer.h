#pragma once
#include "MBaseObject.h"
#include <chrono>
class MTimer : public MBaseObject
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
	virtual bool	Init()	override;		// �ʱ�ȭ
	virtual bool	Frame()	override;	// ���
	virtual bool	Render()	override;	// ��ο�
	virtual bool	Release()	override;	// �Ҹ�
public:
	MTimer();
	virtual ~MTimer();
};


