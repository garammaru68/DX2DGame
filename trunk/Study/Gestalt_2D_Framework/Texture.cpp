#include "Texture.h"
#include <tchar.h>

#pragma comment (lib, "DirectXTex.lib")
//using namespace DirectX;

Texture::~Texture()
{
	if (pTexture) pTexture->Release();
}
DirectX::ScratchImage Texture::LoadTextureFromFile(std::wstring filePath)
{
	HRESULT hr;
	std::wstring path = filePath;
	DirectX::ScratchImage texture;
	WCHAR extension[_MAX_EXT];
	_wsplitpath_s(filePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, extension, _MAX_EXT);

	if (_wcsicmp(extension, L".dds") == 0)
	{
		hr = LoadFromDDSFile( filePath.c_str(), 
			DirectX::DDS_FLAGS_NONE, 
			nullptr, texture);
	}
	else if (_wcsicmp(extension, L".tga") == 0)
	{
		hr = LoadFromTGAFile( filePath.c_str(), 
			nullptr, texture);
	}
	else
	{
		hr = LoadFromWICFile(filePath.c_str(), 
			DirectX::WIC_FLAGS_NONE,
			nullptr, texture);
	}

	return texture;
}

bool Texture::LoadTexture(ID3D11Device* pDevice, std::wstring filePath)
{
	DirectX::ScratchImage texture = LoadTextureFromFile(filePath);

	DirectX::TexMetadata metadata = texture.GetMetadata();
	imageWidth = metadata.width;
	imageHeight = metadata.height;
	rtDest = { 0, 0, (float)imageWidth, (float)imageHeight };
	rtSrc = { 0, 0, (float)imageWidth, (float)imageHeight };

	HRESULT hr;
	if (FAILED( hr = CreateShaderResourceView(
		pDevice,
		texture.GetImages(),
		1,
		metadata,
		&pTexture)))
	{
		MessageBox(nullptr, L"Failed To Load Texture", L"ERROR", MB_OK);
		PostQuitMessage(0);
	};
	return true;
}

bool Texture::LoadSprite(UINT width, UINT height, UINT NumFrame, UINT Line)
{
	for (UINT iLine = 0u; iLine < Line; iLine++)
	{
		for (UINT iFrame = 0u; iFrame < NumFrame; iFrame++)
		{
			RECT rt = { iFrame * width, iLine * height, iFrame * width + width, iLine * height + height };
			frameList.push_back(rt);
		}
	}
	return true;
}

void Texture::SetFrame(UINT index)
{
	assert( index >= 0 && index < frameList.size());

	//if (index <= 0 || index >= frameList.size()) return;

	RECT tmp = frameList[index];
	rtSrc = { (float)tmp.left, (float)tmp.top, (float)tmp.right, (float)tmp.bottom };
}

UINT Texture::GetSingleWidth(UINT index)
{
	if (frameList.size() == 0u) return imageWidth;
	else return frameList[index].right - frameList[index].left;
}

UINT Texture::GetSingleHeight(UINT index)
{
	if (frameList.size() == 0u) return imageHeight;
	else return frameList[index].bottom - frameList[index].top;
}