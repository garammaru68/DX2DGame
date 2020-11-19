#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10math.h>
#include <dxgi.h>
#include <d3dcompiler.h> // d3dcompile
#include <wrl.h> // windows runtime c++ template library(wrl)

using namespace Microsoft::WRL;

#pragma comment (lib, "d3d11.lib")
#if defined(_DEBUG)
#pragma comment (lib, "d3dx10d.lib")
#pragma comment (lib, "d3dx11d.lib")
#else
#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "d3dx11.lib")
#endif

#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

class MDxHelper
{
};

