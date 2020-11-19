#ifndef SBASIS_H
#define SBASIS_H
#pragma warning(disable: 4005)
#include "SUtils.h"
#include "SDxHelper.h"

#if defined(DEBUG) || defined(_DEBUG)
	#if defined(WIN64)
		#pragma comment( lib, "SBasisLib64d.lib" )
	#else
		#pragma comment( lib, "SBasisLib32d.lib" )
	#endif
#else
	#if defined(WIN64)
		#pragma comment( lib, "SBasisLib64R.lib" )
	#else
		#pragma comment( lib, "SBasisLib32T.lib" )
	#endif
#endif

namespace SBASIS
{
	extern float		g_fSecPerFrame;
	extern float		g_fDurationTime;
	extern HWND			g_hWnd;
	extern HINSTANCE	g_hInstance;
	extern UINT			g_iClientWidth;
	extern UINT			g_iClientHeight;
	extern RECT			g_rtClient;
}
using namespace SBASIS;

#define SBASIS_START int WINAPI wWindMain( HINSTANCE hIstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ){ Sample gSample;
#define SBASIS_WIN(x) if( !gSample.InitWindow( hInstance, nCmdShow, L#x ) ) { return 0; } ShowCursor ( TRUE );gSample.Run(); return 1; }
#define SBASIS_RUN(x) SBASIS_START; SBASIS_WIN(x);

static TCHAR g_szDataPath[] = L"../../data";
#endif