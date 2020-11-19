#include "MSpriteMgr.h"
bool MSpriteMgr::Load(const TCHAR* pszLoad)
{
	TCHAR pBuffer[256] = { 0 };
	TCHAR pTemp[256] = { 0 };

	int iNumSprite = 0;
	FILE* fp_src;
	_wfopen_s(&fp_src, pszLoad, _T("rt"));
	if (fp_src == NULL) return false;

	_fgetts(pBuffer, _countof(pBuffer), fp_src);
	_stscanf_s(pBuffer, _T("%s%d%s"), pTemp, _countof(pTemp), &iNumSprite);

	for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
	{
		int iNumFrame = 0;
		_fgetts(pBuffer, _countof(pBuffer), fp_src);
		_stscanf_s(pBuffer, _T("%s %d"), pTemp, _countof(pTemp), &iNumFrame);
		MSprite* pSprite = new MSprite;

		RECT rt;
		for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
		{
			_fgetts(pBuffer, _countof(pBuffer), fp_src);
			_stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, _countof(pTemp),
				&rt.left, &rt.top, &rt.right, &rt.bottom);
			pSprite->m_rtList.push_back(rt);
		}
		m_Map.insert(make_pair(++m_iIndex, pSprite));
	}
	fclose(fp_src);
	return true;
}
MSprite* MSpriteMgr::GetPtr(int iIndex)
{
	MItor iter = m_Map.find(iIndex);
	if (iter != m_Map.end())
	{
		return iter->second;
	}
	return nullptr;
}
bool MSpriteMgr::Release()
{
	MSprite* pData = nullptr;
	for (MItor iter = m_Map.begin(); iter != m_Map.end(); iter++)
	{
		pData = iter->second;
		pData->Release();
		SAFE_DEL(pData);
	}
	m_Map.clear();
	return true;
}

MSpriteMgr::MSpriteMgr()
{

}
MSpriteMgr::~MSpriteMgr()
{
	Release();
}
