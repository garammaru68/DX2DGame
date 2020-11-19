#pragma once
#include <DirectXTex.h>
#include <DirectXTex.inl>
#include <vector>
#include <string>

struct RECT_F
{
	FLOAT left;
	FLOAT top;
	FLOAT right;
	FLOAT bottom;
};

class Texture
{
private:
	ID3D11ShaderResourceView* pTexture;
	std::vector<RECT> frameList;
	UINT currentFrame = 0u;

	RECT_F rtDest;
	RECT_F rtSrc;

	UINT imageWidth = 0u;
	UINT imageHeight = 0u;

public:
	Texture() = default;
	~Texture();

	Texture(const Texture&) = delete;
	Texture& operator =(const Texture&) = delete;

private:
	static DirectX::ScratchImage LoadTextureFromFile(std::wstring fileName);

public:
	bool LoadTexture(ID3D11Device* pDevice, std::wstring filePath);
	bool LoadSprite(UINT width, UINT height, UINT NumFrame, UINT line);

	ID3D11ShaderResourceView* GetSRV() { return pTexture; }
	void SetFrame(UINT index);
	void SetDestRect(RECT_F rt) { rtDest = rt; }
	void SetSrcRect(RECT_F rt) { rtSrc = rt; }

	RECT_F GetDestRect() { return rtDest; }
	RECT_F GetSrcRect() { return rtSrc; }

	UINT GetMaxFrame() { return frameList.size(); }
	UINT GetWidth() { return imageWidth; }
	UINT GetHeight() { return imageHeight; }
	UINT GetSingleWidth(UINT index = 0);
	UINT GetSingleHeight(UINT index = 0);
};