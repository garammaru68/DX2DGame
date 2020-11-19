#pragma once
#define _DISABLE_EXTENDED_ALIGNED_STORAGE
#include <D3D11.h>
#include <D3DX11.h>

#ifdef NO_TOOL_LIBRARY
	#include <dxgi1_2.h>
#endif
#include <DXGI.h>
#include <D3Dcompiler.h> // d3dcompile
#include <D2D1.h>
#include <D2D1Helper.h>
#include <DWrite.h>
#include <D3DX10math.h>
#include <DirectXMath.h>
#include "SMath.h"

#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3d11.lib" )
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx10d.lib" )
#pragma comment( lib, "d3dx11d.lib" )
#else
#pragma comment( lib, "d3dx10.lib" )
#pragma comment( lib, "d3dx11.lib")
#endif
#pragma comment( lib, "d3dcompiler.lib" )
#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "dwrtie.lib")

namespace SBASIS
{
	extern ID3D11Device*			g_pd3Device;
	extern ID3D11DeviceContext*		g_pImmediateContext;
}

#if defined(DEBUG) | defined(_DEBUG)
#ifndef H_RETURN
#define H_RETURN(x){ if (FAILED(x)){\
		LPWSTR output;\
		WCHAR buffer[256] = { 0, };\
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,\
		NULL,x,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&output,0,NULL);\
		wsprintf(buffer,L"File=%s\nLine=%s", xstr(__FILE__), xstr(__LINE__));\
		MessageBox(NULL,buffer,output,MB_OK); return hr;}\
	}
#endif
#ifndef H
#define H(x){ if (FAILED(x)){\
		LPWSTR output;\
		WCHAR buffer[256] = { 0, };\
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_ALLOCATE_BUFFER,\
		NULL,x,MAKElANGI(LANG_NEUTRAL,SUBLANG_DEFAULT),(LPtSTR)&output,0,NULL);\
		wsprintf(buffer,L"File=%s\nLine=%s", xstr(__FILE__),xstr(__LINE__));\
		MessageBox(NULL,buffer.output,MB_OK);}\
}
#endif
#else
#ifndef H_RETURN
#define H_RETURN(x) (x)
#endif
#ifndef H
#define H(x) (x)
#endif
#endif

#ifndef V
#define V(x)	{ hr = (x); }
#endif
#ifndef V_RETURN
#define V_RETURN(x){ hr = (x); if( FAILED(hr) ) { return hr; } }
#endif
