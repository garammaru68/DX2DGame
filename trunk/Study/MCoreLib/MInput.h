#pragma once
#include "MStd.h"
enum { KEY_FREE, KEY_PUSH, KEY_HOLD, KEY_UP};
class MInput : public MSingleton<MInput>
{
	friend class MSingleton<MInput>;
	DWORD       m_dwKeyState[256];
	POINT		m_MousePos;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	POINT		GetPos();
	DWORD		KeyCheck(DWORD dwKey);
private:
	MInput();
public:
	~MInput();
};

#define I_Input MInput::GetInstance()