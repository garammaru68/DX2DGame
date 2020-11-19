#pragma once
#include "MObject.h"
#include "MBitmapMgr.h"

// Button
class Button : public MObject
{
public:
	int				m_iState;
	vector<int>		m_ButtonState;
public:
	virtual bool CreateButton(MObject* pOwner) { return true; }
	void SetState(int iIndex);
	bool Frame();
	bool Render(HDC hOffSCreenDC);
	void SetPos(MPoint pos, MObject* pOwner = nullptr);
	void SetPos(float x, float y, MObject* pOwner = nullptr);
	void SetRect(RECT rtSrc, RECT rtDest, MObject* pOwner = nullptr);

public:
	Button() {}
	~Button() {}
};

// UI
class UI : public Button
{
public:
	vector<MObject*> m_UI;
public:
	void SetState(int iIndex);
	bool Frame();
	bool Render(HDC hdc);
	void SetPos(MPoint pos, MObject* pOwner = nullptr);
	void SetPos(float x, float y, MObject* pOwner = nullptr);
	void SetRect(RECT rtSrc, RECT rtDest, MObject* pOwner = nullptr);
public:
	UI() {}
	~UI() {}
};

// UIList
class UIList : public Button
{
public:
	int					m_iNumUI;
	int					m_iState;
	vector<int>			m_ButtonState;
	vector<Button>		m_Button;
public:
	bool CreateUIList(MObject* pOwner, int x, int y, int iWidth, int iHeight, int iNumBtn);
	void SetState(int iIndex);
	bool Frame();
	bool Render(HDC hdc);
	void SetPos(MPoint pos, MObject* pOwner = nullptr);
	void SetPos(float x, float y, MObject* pOwner = nullptr);
	void SetRect(RECT rtSrc, RECT rtDest, MObject* pOwner = nullptr);
public:
	UIList() {}
	~UIList() {}
};