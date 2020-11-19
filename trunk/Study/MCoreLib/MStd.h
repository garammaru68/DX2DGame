#pragma once
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <set>
#include <assert.h>
#include <d3d11.h>
#include <dxgi.h>

using namespace std;
typedef basic_string<TCHAR> T_STR;
//using T_STR = basic_string <TCHAR>;
typedef basic_string<char>  C_STR;
typedef basic_string<wchar_t> W_STR;
typedef std::vector<T_STR> T_STR_VECTOR;

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "MCoreDx_d.lib")
#pragma comment (lib, "fmod_vc.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

struct MInputActionMap
{
	DWORD bAttack;
	DWORD bJump;
	DWORD bExit;

	DWORD bWKey;
	DWORD bSKey;
	DWORD bAKey;
	DWORD bDKey;

	DWORD bLeftClick;
	DWORD bRightClick;
	DWORD bMiddleClick;
};

extern float			g_fSecondPerFrame;
extern float			g_fTimer;
extern HINSTANCE		g_hInstance;
extern HWND				g_hWnd;
extern RECT				g_rtClient;
extern POINT			g_MousePos;
extern MInputActionMap	g_InputMap;
extern HDC			g_hScreenDC;
extern HDC			g_hOffScreenDC;

static std::wstring mtw(std::string str)
{
	return std::wstring(str.begin(), str.end());
}
static std::string wtm(std::wstring str)
{
	return std::string(str.begin(), str.end());
}
// Singleton
template <class T>
class MSingleton
{
public://TSoundMgr': private ¸â¹ö -> friend
	static T& GetInstance()
	{
		static T theSingleton;
		return theSingleton;
	}	
};

#ifndef SAFE_NEW
#define SAFE_NEW(A,B)  {if(!A) A= new B;}
#endif // !SAFE_NEW

#ifndef SAFE_DEL
#define SAFE_DEL(A)    {if(A) delete A; (A) = 0;}
#endif // !SAFE_DEL

#ifndef SAFE_ZERO
#define SAFE_ZERO(A)    {(A) = 0;}
#endif // !SAFE_DEL

#define MCORE_START void main() {
#define MCORE_RUN 	Sample sample;sample.MRun();
#define MCORE_END }
#define MGAME MCORE_START;MCORE_RUN;MCORE_END;

#define MWINCORE_START int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,int nCmdShow){
#define MWINCORE_RUN 	Sample win;if(win.SetWindow(hInstance)){win.MRun();}
#define MWINCORE_END }
#define MWINGAME MWINCORE_START;MWINCORE_RUN;MWINCORE_END;