#include "Sample.h"

void Sample::SetLifeCounter()
{
	if (m_fHeroLifeTime > 3.0f)
	{
		I_SoundMgr.GetPtr(3)->PlayEffect();
		m_iLifeCounter--;
		m_fHeroLifeTime = 0.0f;
	}
}
MNpcObj*	Sample::AddNpc()
{
	MNpcObj* npc = new MNpcObj;
	if (npc->Load(m_hScreenDC, L"../../../data/Apopup_normal.bmp"))
	{
		RECT rtSrc, rtDest;
		rtSrc.left = 0;
		rtSrc.top = 0;
		rtDest.left = rand() % 800;
		rtDest.top = 0;
		rtDest.right = 196;
		rtDest.bottom = 124;
		npc->SetRect(rtSrc, rtDest);
	}
	return npc;
}
bool	Sample::Init()
{
	I_SoundMgr.Load(L"../../../data/sound/OnlyLove.mp3");
	I_SoundMgr.Load(L"../../../data/sound/gunShot.mp3");
	I_SoundMgr.Load(L"../../../data/sound/gun1.wav");
	m_BackGround.Load(m_hScreenDC, L"../../../data/KGCABK.bmp");
	if (m_Hero.Load(m_hScreenDC, L"../../../data/bitmap1.bmp"))
	{
		m_Hero.SetMaskBitmap(m_hScreenDC, L"../../../data/bitmap1mask.bmp");

		RECT rtSrc, rtDest;
		rtSrc.left		= 133;
		rtSrc.top		= 1;
		rtDest.left		= g_rtClient.right / 2;
		rtDest.top		= g_rtClient.bottom / 2;
		rtDest.right	= 42;
		rtDest.bottom	= 60;
		m_Hero.SetRect(rtSrc, rtDest);
	}
	if (m_Projectile.Load(m_hScreenDC, L"../../../data/bitmap1.bmp"))
	{
		RECT rtSrc, rtDest;
		rtSrc.left		= 276;
		rtSrc.top		= 1;
		rtDest.left		= m_Hero.m_fPosX;
		rtDest.top		= m_Hero.m_fPosY;
		rtDest.right	= 8;
		rtDest.bottom	= 24;
		m_Projectile.SetRect(rtSrc, rtDest);
	}
	for (int iNpc = 0; iNpc < 1; iNpc++)
	{
		m_NpcList.push_back(AddNpc());
	}

	return true;
}
bool	Sample::Frame()
{
	m_Hero.Frame();
	m_Projectile.Frame();
	if (g_InputMap.bAttack == KEY_PUSH)
	{
		MProjectile item;
		item.fLifeTime	= 2.0f;
		item.rtDest		= m_Projectile.m_rtDest;
		item.SetPos(m_Hero.m_fPosX, m_Hero.m_fPosY);
		m_ProjectileList.insert(m_ProjectileList.end(), item);
		I_SoundMgr.GetPtr(2)->PlayEffect();
	}
	list<MProjectile>::iterator iter;
	for (iter = m_ProjectileList.begin(); iter != m_ProjectileList.end();)
	{
		(*iter).fLifeTime	-= g_fSecondPerFrame;
		(*iter).pos.y		-= g_fSecondPerFrame * 500.0f;
		(*iter).SetPos((*iter).pos.x, (*iter).pos.y);

		if ((*iter).fLifeTime < 0.0f)
		{
			iter = m_ProjectileList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	m_fNpcTime += g_fSecondPerFrame;
	if (m_fNpcTime > 1.0f)
	{
		m_NpcList.push_back(AddNpc());
		m_fNpcTime -= 1.0f;
	}

	for (MNpcObj* npc : m_NpcList)
	{
		if (npc->m_bDead == true) continue;
		npc->Frame();

		list<MProjectile>::iterator iter;
		for (iter = m_ProjectileList.begin(); iter != m_ProjectileList.end(); iter++)
		{
			if (MCollision::SphereInSphere(npc->m_Sphere, (*iter).m_Sphere))
			{
				npc->m_bDead = true;
				break;
			}
		}
		if (MCollision::RectInRect(npc->m_rtCollision, m_Hero.m_rtCollision))
		{
			SetLifeCounter();
			break;
		}
		if (MCollision::SphereInPt(npc->m_Sphere, g_MousePos))
		{
			npc->SetPos(0, 0);
		}
	}
	if (m_iLifeCounter <= 0)
	{
		m_bExit = true;
	}
	m_fHeroLifeTime += g_fSecondPerFrame;

	return true;
}
bool	Sample::Render()
{
	m_BackGround.Render(m_hOffScreenDC);
	m_Hero.Render(m_hOffScreenDC);
	list<MProjectile>::iterator iter;
	for (iter = m_ProjectileList.begin(); iter != m_ProjectileList.end(); iter++)
	{
		m_Projectile.SetPos((*iter).pos.x, (*iter).pos.y);
		m_Projectile.DrawColorKey(m_hOffScreenDC);
	}
	for (MNpcObj* npc : m_NpcList)
	{
		if (npc->m_bDead == true) continue;
		npc->Render(m_hOffScreenDC);
	}

	HFONT hOldFont = (HFONT)SelectObject(m_hOffScreenDC, m_hGameFont);
	T_STR strBuffer	= L"LIFE :";
	strBuffer += std::to_wstring(m_iLifeCounter);
	SetTextColor(m_hOffScreenDC, RGB(255, 0, 0));
	SetBkColor(m_hOffScreenDC, RGB(0, 0, 255));
	SetBkMode(m_hOffScreenDC, TRANSPARENT);
	RECT rt = g_rtClient;
	rt.left = 400;
	DrawText(m_hOffScreenDC,
		strBuffer.c_str(),
		-1,
		&rt,
		DT_LEFT | DT_VCENTER);
	SelectObject(m_hOffScreenDC, hOldFont);
	return true;
}
bool	Sample::Release()
{
	m_BackGround.Release();
	m_Hero.Release();
	m_Projectile.Release();
	for (MNpcObj* npc : m_NpcList)
	{
		npc->Release();
		delete npc;
	}
	m_NpcList.clear();
	return true;
}

Sample::Sample()
{
	m_fNpcTime		= 0.0f;
	m_fHeroLifeTime = 0.0f;
	m_iLifeCounter	= 3;
}
Sample::~Sample()
{

}
MWINGAME;