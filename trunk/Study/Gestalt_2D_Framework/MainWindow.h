#pragma once
#include <Windows.h>

#include "Graphics.h"

class MainWindow
{
protected:
	HINSTANCE	hInstance;
	HWND			hWnd;
	LPWSTR		lpszClass;

private:
	float FPS;
	float delta;

public:
	MainWindow(HINSTANCE hInstance);
	~MainWindow();

	MainWindow(const MainWindow&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;

private:
	void _UpdateWindow();
	void _RenderWindow();

public:
	bool ProceedMessage();
	static LRESULT MainWndProc(	HWND hWnd, UINT iMessage,
																WPARAM wParam, LPARAM lParam);

public:
	virtual void Update(float delta) {}
	virtual void Render(float delta) {}
	virtual void Release() {}

	void Initiate();
};