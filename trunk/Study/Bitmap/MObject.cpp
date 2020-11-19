#include "MObject.h"
void	MObject::SetRect(RECT rtSrc, RECT rtDesk)
{
	m_rtSrc = rtSrc;
	m_rtDesk = rtDesk;
}
bool	MObject::Load(HDC hScreenDC, T_STR szFileName)
{
	m_Bitmap.Load(hScreenDC, szFileName);
	m_rtSrc.left = 0;
	m_rtSrc.top = 0;
	m_rtSrc.right = m_Bitmap.m_BmpInfo.bmWidth;
	m_rtSrc.bottom = m_Bitmap.m_BmpInfo.bmHeight;
	m_rtDesk.left = 0;
	m_rtDesk.top = 0;
	m_rtDesk.right = g_rtClient.right - g_rtClient.left;
	m_rtDesk.bottom = g_rtClient.bottom - g_rtClient.top;
	return true;
}
bool	MObject::Render()
{
	BitBlt( m_Bitmap.m_hScreenDC,
			m_rtDesk.left,
			m_rtDesk.top,
			m_rtDesk.right,
			m_rtDesk.bottom,
			m_Bitmap.m_hMemDC,
			m_rtSrc.left,
			m_rtSrc.top,
			SRCCOPY);
	return true;
};
bool	MObject::Release()
{
	return m_Bitmap.Release();
}
MObject::MObject()
{

}
MObject::~MObject()
{

}
