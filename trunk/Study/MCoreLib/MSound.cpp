#include "MSound.h"
bool	MSound::Init()
{
	return true;
}
bool	MSound::Frame()
{
	if (m_pChannel == nullptr) return true;
	unsigned int ms;
	m_pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
	ZeroMemory(m_csBuffer, sizeof(TCHAR) * 256);
	_stprintf_s(m_csBuffer, 
		_T("TIME:%02d:%02d:%02d %02d:%02d:%02d"),
		ms / 1000 / 60,
		ms / 1000 % 60,
		ms / 10 % 100,
		m_msLength / 1000 / 60,
		m_msLength / 1000 / 60,
		m_msLength / 10 % 100
		);
	return true;
}
bool	MSound::Render()
{
	std::wcout << m_csBuffer << std::endl;
	return true;
}
bool	MSound::Release()
{
	return true;
}
bool	MSound::Load(T_STR szLoadName, FMOD::System* pSystem)
{
	assert(pSystem);

	TCHAR szDrive[MAX_PATH] = { 0, };
	TCHAR szDir[MAX_PATH] = { 0, };
	TCHAR szName[MAX_PATH] = { 0, };
	TCHAR szExt[MAX_PATH] = { 0, };
	_tsplitpath_s(szLoadName.c_str(), szDrive, szDir, szName, szExt);
	m_csName = szName;
	m_csName += szExt;
	m_pSystem = pSystem;

	FMOD_RESULT hr;
	hr = pSystem->createSound(wtm(szLoadName).c_str(), FMOD_DEFAULT, 0, &m_pSound);
	if (hr != FMOD_OK) return false;

	m_pSound->getLength(&m_msLength, FMOD_TIMEUNIT_MS);	
	m_pChannel->setVolume(0.5f);
	return true;
}
void	MSound::PlayEffect()
{
	FMOD_RESULT hr;
	hr = m_pSystem->playSound(m_pSound, false, false, &m_pChannel);
	if (hr != FMOD_OK) return;
}
void	MSound::Play()
{
	FMOD_RESULT hr;
	bool playing = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&playing);
	}
	if (!playing)
	{
		hr = m_pSystem->playSound(m_pSound, false, false, &m_pChannel);
		if (hr != FMOD_OK) return;
	}
}
void	MSound::Paused()
{
	bool playing = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&playing);
	}
	if (playing)
	{
		bool paused = false;
		m_pChannel->getPaused(&paused);
		m_pChannel->setPaused(!paused);
	}
}
void	MSound::Stop() 
{
	m_pChannel->stop();
}
void	MSound::VolumeUp() 
{
	float fVolume = 1.0f;
	m_pChannel->getVolume(&fVolume);
	m_fVolume = min(1.0f, fVolume + 0.1f * g_fSecondPerFrame);
	m_pChannel->setVolume(m_fVolume);
}
void	MSound::VolumeDown() 
{
	float fVolume = 1.0f;
	m_pChannel->getVolume(&fVolume);
	m_fVolume = max(0.0f, fVolume - 0.1f * g_fSecondPerFrame);
	m_pChannel->setVolume(m_fVolume);
}
void	MSound::SetMode(DWORD dwMode) 
{
	m_pSound->setMode(dwMode);
}
MSound::MSound() 
{
	m_pSystem = nullptr;
	m_pSound = nullptr;
	m_fVolume = 0.5f;
}
MSound::~MSound() 
{}