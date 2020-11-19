#include "MBitmap.h"
bool	MBitmap::Frame()
{
	return true;
}
bool	MBitmap::Render()
{
	return true;
}
bool	MBitmap::Init()
{
	return true;
}
bool	MBitmap::LoadDIB(HDC hScreenDC, T_STR szLoadFileName)
{
	HANDLE hFile = CreateFile(szLoadFileName.c_str(),
		GENERIC_READ,
		0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	DWORD dwRead, dwDataSize;
	ReadFile(hFile, &m_bitFileHeader, sizeof(BITMAPFILEHEADER),
			&dwRead, NULL);
	dwDataSize = m_bitFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
	BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(dwDataSize);
	ReadFile(hFile, bitInfo, dwDataSize, &dwRead, NULL);

	m_hBitmap = CreateDIBSection(hScreenDC,
		bitInfo,
		DIB_RGB_COLORS,
		&m_pRaster, NULL, 0);

	DWORD dwMaxSize = m_bitFileHeader.bfSize - m_bitFileHeader.bfOffBits;
	ReadFile(hFile, m_pRaster,
		dwMaxSize, &dwRead, NULL);

	free(bitInfo);
	CloseHandle(hFile);
	return true;
}

bool	MBitmap::Load(HDC hScreenDC, T_STR szLoadFileName)
{
	m_hScreenDC = hScreenDC;
	LoadDIB(hScreenDC, szLoadFileName);

	//m_hBitmap = (HBITMAP)LoadImage(g_hInstance,
	//	szLoadFileName.c_str(),
	//	IMAGE_BITMAP,
	//	0, 0,
	//	LR_DEFAULTSIZE | LR_LOADFROMFILE);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_BmpInfo);
	m_hMemDC = CreateCompatibleDC(m_hScreenDC);
	SelectObject(m_hMemDC, m_hBitmap);
	return true;
}
bool MBitmap::Release()
{
	DeleteObject(m_hBitmap);
	ReleaseDC(g_hWnd, m_hMemDC);
	return true;
}
MBitmap::MBitmap()
{

}
MBitmap::~MBitmap()
{

}