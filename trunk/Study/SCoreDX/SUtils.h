#pragma once
#define DIRECTINPUT_VERSION 0X0800
#define _CRT_SECURE_NO_WARNINGS
#ifndef UNICODE
#error "TBASIS는 유니코드로 컴파일 해야 합니다."
#endif
#pragma warning( disable:4005)

#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <crtdbg.h>
#include <cassert>
#include <math.h>
#include <set>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <bitset>
#include <limits>
#include <functional>
#include <unordered_map>
#include <mmsystem.h> // timeGetTime
#include <wrl.h>
#include <memory>
#pragma comment(lib, "winmm.lib")

using namespace Microsoft::WRL;
using namespace std;

namespace SBASIS
{
	typedef basic_string<TCHAR>		T_STR;
	typedef basic_string<wchar_t>	W_STG;
	typedef basic_string<char>		C_STR;
	typedef vector<T_STR>			T_STR_VECTOR;
	typedef vector<T_STR>			T_ARRAY_ITOR;
	typedef basic_string<TCHAR>::iterator	T_ITOR;
	typedef basic_string<wchar_t>::iterator W_ITOR;
	typedef basic_string<char>::iterator	C_ITOR;

	static std::wstring mtw(std::string str)
	{
		std::wstring ret = std::wstring(str.begin(), str.end());
		return ret;
	}
	static std::string wtm(std::wstring str)
	{
		return std::string(str.begin(), str.end());
	}
	static char* GetWtM(WCHAR* data)
	{
		char retData[4096] = { 0 };
		int iLength = WideCharToMultiByte(CP_ACP, 0,
			data, -1,
			0, 0,
			NULL, NULL);
		int iRet = WideCharToMultiByte(CP_ACP, 0, 
			data, -1,
			retData, iLength,
			NULL, NULL);
		return retData;
	}
	static bool GetWtM(WCHAR* src, char* pDest)
	{
		int iLength = WideCharToMultiByte(CP_ACP, 0,
			src, -1,
			0, 0,
			NULL, NULL);
		int iRet = WideCharToMultiByte(CP_ACP, 0,
			src, -1,
			pDest, iLength,
			NULL,NULL);
		if (iRet == 0) return false;
		return true;
	}
	static WCHAR* GetMtW(char* data)
	{
		WCHAR retData[4096] = { 0 };
		int iLength = MultiByteToWideChar(CP_ACP, 0,
			data, -1,
			0, 0);
		int iRet = MultiByteToWideChar(CP_ACP, 0,
			data, -1,
			retData, iLength);
		return retData;
	}
	static bool GetMtW(char* pSrc, WCHAR* pDest)
	{
		int iLength = MultiByteToWideChar(CP_ACP, 0,
			pSrc, -1,
			0, 0);
		int iRet = MultiByteToWideChar(CP_ACP, 0,
			pSrc, -1,
			pDest, iLength);
		if (iRet == 0) return false;
		return true;
	}
	static void PRINT(char* fmt, ...)
	{
		va_list arg;
		va_start(arg, fmt);
		char buf[256] = { 0, };
		vsprintf_s(buf, fmt, arg);
		printf("\n=====> %s", buf);
		va_end(arg);
	}
	static void ErrorQuit(TCHAR *msg)
	{
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			(TCHAR*)&lpMsgBuf, 0, NULL);
		MessageBox(NULL, (TCHAR*)lpMsgBuf, msg, MB_ICONERROR);
		LocalFree(lpMsgBuf);
		exit(-1);
	}

	template<class T> class SSingleton
	{
	public:
		static T& GetInstnace()
		{
			static T theSingleInstance;
			return theSingleInstance;
		}
	};

	struct SBASIS_INPUT_MAP
	{
		bool bUpKey;
		bool bDownKey;
		bool bLeftKey;
		bool bRightKey;

		bool bWKey;
		bool bSKey;
		bool bAKey;
		bool bDKey;
		bool bQKey;
		bool bEKey;
		bool bZkey;
		bool bCKey;

		bool bLeftClick;
		bool bRightClick;
		bool bMiddleClick;

		bool bLeftHold;
		bool bRightHold;
		bool bMiddleHold;

		bool bExit;
		bool bSpace;

		int iMouseValue[3];

		bool bFullScreen;
		bool bChangeFillMode;
		bool bChangePrimitive;
		bool bChangeCullMode;
		bool bChangeCameraType;
		bool bDebugRender;
	};
	extern SBASIS_INPUT_MAP g_InputData;
}

#define str(x) L#x
#define xstr(x) str(x)
#define randf(x) (x * rand() / (float)RAND_MAX)
#define randf2(x,off) (off + x * rand() / (float)RAND_MAX)
#define randstep(fMin,fMax) (fMin + ((float)fMax - (float)fMin) * rand() / (float)RAND_MAX)
#define clamp(x,MinX,MaxX) if (x > MaxX) x = MaxX; else if (x < MinX) x = MinX;

#ifndef Assert
#if defined(_DEBUG) || defined(_DEBUG)
#define Assert(b) do {if (!(b)) {OutputDebugStringW(L"Assert: " #b L"\n");}} while(0)
#else
#define Assert(b)
#endif //_DEBUG || _DEBUG
#endif

#ifdef _DEBUG
#define DEBUGMSG(lpText)\
	{\
		TCHAR szBuffer[256];\
		_stprintf_s(szBuffer, _T("[File: %s][Line: %d]\n[Note : %s]"), _CRT_WIDE(__FILE__), __LINE__, lpText); \
		MessageBox(NULL, szBuffer, _T("ERROR"), MB_ICONERROR);\
		_ASSERT(1);}
#else
	#define DEBUGMSG(lpText)
#endif

#ifndef SAFE_ZERO
#define SAFE_ZERO(A)				{ A = 0; }
#endif

#ifndef SAFE_NEW
#define SAFE_NEW(A, B)				{ if (!A) A = new B; }
#endif

#ifndef SAFE_DEL
#define SAFE_DEL(A)					{ if (A) delete A; (A) = NULL; }
#endif

#ifndef SAFE_NEW_ARRAY
#define SAFE_NEW_ARRAY(A, B, C)		{ if (!A && C) A = new B[C]; }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A) = NULL; } }
#endif

#ifndef SAFE_NEW_CLEAR
#define SAFE_NEW_CLEAR( A, B )		{ if (!A) A = new B; if(A) memset( A, 0, sizeof(B) ); };
#endif

#ifndef SAFE_NEW_ARRAY_CLEAR
#define SAFE_NEW_ARRAY_CLEAR( A, B, C ) { if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C); };
#endif