#include "BattlefieldScene.h"
#include "Collision.h"
#include <Graphics.h>
#include <Input.h>
#include <fstream>

void BattlefieldScene::Initialize()
{
	// Battlefield
	world.Initialize(L"../../../data/DX2D/resource/Background.bmp");
	camera.Initialize({ 0, 0, (LONG)Graphics::GetScreenWidth(), (LONG)Graphics::GetScreenHeight() }, { 0, 0, 400, 200}, { 220, 0 });

	// UI
	seedbank.Initialize(L"../../../data/DX2D/resource/SeedBank.bmp", 446, 87, 1, 1, &background, { 10, 0 });
	shovelbank.Initialize(L"../../../data/DX2D/resource/ShovelBank.bmp", 70, 72, 1, 1, &background, { 456, 0 });
	pointcard.Initialize(L"../../../data/DX2D/resource/Point.bmp", 65, 25, 11, 3, &background, { 16, 60 });

	// PlantsCard
	SFCard.Initialize(L"../../../data/DX2D/resource/SunFlowerCard.bmp", 50, 70, 2, 1, &background, { 90, 8 });
	SFCard.texture.SetFrame(0);
	WNCard.Initialize(L"../../../data/DX2D/resource/WallNutCard.bmp", 50, 70, 2, 1, &background, { 142, 8 });
	WNCard.texture.SetFrame(0);
	PSCard.Initialize(L"../../../data/DX2D/resource/PeaShooterCard.bmp", 50, 70, 2, 1, &background, { 194, 8 });
	PSCard.texture.SetFrame(0);

	// Plant
	SFReleaser.Initialize(36, 31, {}, L"../../../data/DX2D/resource/SunFlower.bmp", 8, 1);
	WNReleaser.Initialize(36, 30, {}, L"../../../data/DX2D/resource/WallNut.bmp", 5, 1);
	PSReleaser.Initialize(36, 30, {}, L"../../../data/DX2D/resource/PeaShooter.bmp", 13, 1);
	//PSReleaser.InitializeTest({});

	// Zombie
	enemyReleaser.Initialize({}, {});
	spawnPoint.push_back({ 900, 160 });
	spawnPoint.push_back({ 900, 250 });
	spawnPoint.push_back({ 900, 360 });
	spawnPoint.push_back({ 900, 450 });
	spawnPoint.push_back({ 900, 550 });

	// SunLight
	sunlightReleaser.Initialize({}, {});
	for (int i = 0; i < 50; i++)
	{
		float randPos = rand() % 701 + 50;
		spawnPointSun.push_back({ randPos, -100 });
	}

	// cursor
	std::wstring imagePath[3] = {	L"../../../data/DX2D/resource/SunFlowerCard.bmp",
									L"../../../data/DX2D/resource/WallNutCard.bmp",
									L"../../../data/DX2D/resource/PeaShooterCard.bmp" };
}
void BattlefieldScene::Update(float delta)
{
	if (Mouse::LBIsDown())
	{
		playerSpawnPoint.x = Mouse::GetPosX();
		playerSpawnPoint.y = Mouse::GetPosY();

		// XÃà
		if (playerSpawnPoint.x >= 36 && playerSpawnPoint.x <= 115)
		{
			playerSpawnPoint.x = 45;
		}
		else if (playerSpawnPoint.x >= 116 && playerSpawnPoint.x <= 195)
		{
			playerSpawnPoint.x = 125;
		}
		else if (playerSpawnPoint.x >= 196 && playerSpawnPoint.x <= 275)
		{
			playerSpawnPoint.x = 205;
		}
		// YÃà
		if (playerSpawnPoint.y >= 81 && playerSpawnPoint.y <= 180)
		{
			playerSpawnPoint.y = 110;
		}
		else if (playerSpawnPoint.y >= 181 && playerSpawnPoint.y <= 280)
		{
			playerSpawnPoint.y = 210;
		}
		else if (playerSpawnPoint.y >= 281 && playerSpawnPoint.y <= 380)
		{
			playerSpawnPoint.y = 310;
		}
		else if (playerSpawnPoint.y >= 381 && playerSpawnPoint.y <= 480)
		{
			playerSpawnPoint.y = 410;
		}
		else if (playerSpawnPoint.y >= 481 && playerSpawnPoint.y <= 580)
		{
			playerSpawnPoint.y = 510;
		}

		if (bSFCard && SFCard.pressed)
		{
			if (sunPoint >= 2)
			{
				SpawnPlayer(sunflowerList, 36, 31, spawnedSunFlower, currentSunFlower, 1, playerSpawnPoint,
							L"../../../data/DX2D/resource/SunFlower.bmp", 8, 1);
				sunPoint -= 2;
				SFCard.pressed = false;
			}
		}
		else if (bWNCard && WNCard.pressed)
		{
			if (sunPoint >= 2)
			{
				SpawnPlayer(wallnutList, 36, 30, spawnedWallNut, currentWallNut, 1, playerSpawnPoint,
							L"../../../data/DX2D/resource/WallNut.bmp", 5, 1);
				sunPoint -= 2;
				WNCard.pressed = false;
			}
		}
		else if (bPSCard && PSCard.pressed)
		{
			if (sunPoint >= 4)
			{
				SpawnPlayer(playerList, 36, 30, spawnedPlayer, currentPlayer, 1, playerSpawnPoint,
							L"../../../data/DX2D/resource/PeaShooter.bmp", 13, 1);
				sunPoint -= 4;
				PSCard.pressed = false;

				//SpawnPlayerTest(1);
				//sunPoint -= 4;
				//PSCard.pressed = false;

				//if (sunPoint <= 0)
				//{
				//	sunPoint = 0;
				//}
			}
		}
	}

	SpawnEntities(delta);
	SpawnSunEntities(delta);
	UpdateElements(delta);

	seedbank.Update();
	shovelbank.Update();
	pointcard.Update();
	pointcard.texture.SetFrame(sunPoint);

	CardSet();

	CheckSightCollision();
	CheckHitCollision();
	
	//if (Mouse::LBIsDown())
	//{
	//	float x = Mouse::GetPosX();
	//	float y = Mouse::GetPosY();
	//	bool debug = true;
	//}
}
void BattlefieldScene::UpdateElements(float delta)
{
	seedbank.texture.SetDestRect({ 5.0f, 0.0f, 451.0f, 87.0f });
	shovelbank.texture.SetDestRect({ 451.0f, 0.0f, 521.0f, 72.0f });

	// Plant
	std::vector<Plants*>::iterator ivSunFlower;
	for (ivSunFlower = sunflowerList.begin(); ivSunFlower != sunflowerList.end(); ivSunFlower++)
	{
		if ((*ivSunFlower) == nullptr) continue;
		(*ivSunFlower)->Update({ 10, 0 }, delta, 0, 7, {}, {});
	}

	std::vector<Plants*>::iterator ivWallNut;
	for (ivWallNut = wallnutList.begin(); ivWallNut != wallnutList.end(); ivWallNut++)
	{
		if ((*ivWallNut) == nullptr) continue;
		(*ivWallNut)->Update({ 10, 0 }, delta, 0, 4, {}, {});
	}

	std::vector<Plants*>::iterator ivPlayer;
	for (ivPlayer = playerList.begin(); ivPlayer != playerList.end(); ivPlayer++)
	{
		if ((*ivPlayer) == nullptr) continue;
		(*ivPlayer)->Update({ 10, 0 }, delta, 0, 8, 9, 12);
	}

	// Zombie
	std::vector<Enemy*>::iterator it;
	for (it = enemyList.begin(); it != enemyList.end(); it++)
	{
		if ((*it) == nullptr) continue;
		(*it)->Update({ 10, 0 }, delta);
	}

	// SunLight
	std::vector<SunLight*>::iterator viSunlight;
	for (viSunlight = vSunlight.begin(); viSunlight != vSunlight.end(); viSunlight++)
	{
		if ((*viSunlight) == nullptr) continue;
		(*viSunlight)->Update({ 0, 20 }, delta);
	}

	cursor.texture.SetDestRect({
		Mouse::GetPosX() - cursor.texture.GetWidth() / 2,
		Mouse::GetPosY() - cursor.texture.GetHeight() / 2,
		Mouse::GetPosX() + cursor.texture.GetWidth() / 2,
		Mouse::GetPosY() + cursor.texture.GetHeight() / 2 });

	RECT cursorRect = {
		cursor.texture.GetDestRect().left - cursor.texture.GetWidth() / 2,
		cursor.texture.GetDestRect().top - cursor.texture.GetHeight() / 2,
		cursor.texture.GetWidth(),
		cursor.texture.GetHeight()
	};

	SFCard.UpdateCard(cursorRect);
	WNCard.UpdateCard(cursorRect);
	PSCard.UpdateCard(cursorRect);
}
void BattlefieldScene::Render(float delta)
{
	world.Render(camera.GetScope());
	seedbank.Render();
	shovelbank.Render();
	pointcard.Render();
	SFCard.RenderCard();
	WNCard.RenderCard();
	PSCard.RenderCard();

	// Plant
	std::vector<Plants*>::iterator ivSunFlower;
	for (ivSunFlower = sunflowerList.begin(); ivSunFlower != sunflowerList.end(); ivSunFlower++)
	{
		if ((*ivSunFlower) == nullptr) continue;
		else (*ivSunFlower)->Render(delta);
	}

	std::vector<Plants*>::iterator ivWallNut;
	for (ivWallNut = wallnutList.begin(); ivWallNut != wallnutList.end(); ivWallNut++)
	{
		if ((*ivWallNut) == nullptr) continue;
		else (*ivWallNut)->Render(delta);
	}

	std::vector<Plants*>::iterator ivPlayer;
	for (ivPlayer = playerList.begin(); ivPlayer != playerList.end(); ivPlayer++)
	{
		if ((*ivPlayer) == nullptr) continue;
		else (*ivPlayer)->Render(delta);
	}

	// Zombie
	std::vector<Enemy*>::iterator it;
	for (it = enemyList.begin(); it != enemyList.end(); it++)
	{
		if ((*it) == nullptr) continue;
		else (*it)->Render(delta);
	}

	// SunLight
	std::vector<SunLight*>::iterator viSunlight;
	for (viSunlight = vSunlight.begin(); viSunlight != vSunlight.end(); viSunlight++)
	{
		if ((*viSunlight) == nullptr) continue;
		else (*viSunlight)->Render();
	}
}

///////////////////////////////////////////////////////

void BattlefieldScene::SpawnPlayer(std::vector<Plants*> &list,
									float width, float height,
									int spawned, int current, int nPlayer,
									Vector2D spawnPoint, std::wstring imagePath,
									UINT NumFrame, UINT Line)
{
	for (int iPlayer = 0; iPlayer < nPlayer; iPlayer++)
	{
		Plants* ptrPlayer = new Plants;
		ptrPlayer->Initialize(width, height, spawnPoint, imagePath, NumFrame, Line);
		list.push_back(ptrPlayer);
	}
	spawned += nPlayer;
	current += nPlayer;
}
void BattlefieldScene::SpawnPlayerTest(int nPlayer)
{
	for (int iPlayer = 0; iPlayer < nPlayer; iPlayer++)
	{
		Plants* ptrPlayer = new Plants;
		ptrPlayer->InitializeTest(playerSpawnPoint);
		playerList.push_back(ptrPlayer);
	}
	spawnedPlayer += nPlayer;
	currentPlayer += nPlayer;
}
void BattlefieldScene::SpawnEntities(float delta)
{
	startSpawnTimer += delta;
	if (startSpawnTimer > 5)
	{
		spawnTimer += delta;
		if (spawnTimer >= spawnAt)
		{
			spawnTimer -= spawnAt;
			if (spawnedEnemy < maxEnemy)
			{
				SpawnEnemy(1);
			}
		}
	}
}
void BattlefieldScene::SpawnEnemy(int nEnemy)
{
	for (int iEnemy = 0; iEnemy < nEnemy; iEnemy++)
	{
		Enemy* ptrEnemy = new Enemy;
		int spawnIndex = rand() % spawnPoint.size();
		ptrEnemy->Initialize(spawnPoint[spawnIndex], { 0, 0, 120, 220 });
		enemyList.push_back(ptrEnemy);
	}
	spawnedEnemy += nEnemy;
	currentEnemy += nEnemy;
}

void BattlefieldScene::SpawnSunEntities(float delta)
{
	spawnSunTimer += delta;
	if (spawnSunTimer >= spawnSunAt)
	{
		spawnSunTimer -= spawnSunAt;
		if (spawnedSunlight < maxSunlight)
		{
			SpawnSunlight(1);
		}
	}
}

void BattlefieldScene::SpawnSunlight(int nSunlight)
{
	for (int iSunlight = 0; iSunlight < nSunlight; iSunlight++)
	{
		SunLight* ptrSunlight = new SunLight;
		int spawnIndex = rand() % spawnPointSun.size();
		ptrSunlight->Initialize(spawnPointSun[spawnIndex], { 0, 0, 28, 30 });
		vSunlight.push_back(ptrSunlight);
	}
	spawnedSunlight += nSunlight;
	currentSunlight += nSunlight;
}
void BattlefieldScene::CardSet()
{
	// CardSetting
	if (sunPoint >= 2 && !SFCard.pressed)
	{
		bSFCard = true;
		SFCard.texture.SetFrame(1);
	}
	else SFCard.texture.SetFrame(0);
	
	if (sunPoint >= 2 && !WNCard.pressed)
	{ 
		bWNCard = true;
		WNCard.texture.SetFrame(1);
	}
	else WNCard.texture.SetFrame(0);

	if (sunPoint >= 4 && !PSCard.pressed)
	{
		bPSCard = true;
		PSCard.texture.SetFrame(1);
	}
	//else WNCard.texture.SetFrame(0);

	else if (PSCard.pressed) PSCard.texture.SetFrame(0);
}

void BattlefieldScene::CheckSightCollision()
{
	std::vector<Enemy*>::iterator viEnemy;
	for (viEnemy = enemyList.begin(); viEnemy != enemyList.end(); viEnemy++)
	{
		if ((*viEnemy) == nullptr) continue;

		std::vector<Plants*>::iterator viPlayer;
		for (viPlayer = playerList.begin(); viPlayer != playerList.end(); viPlayer)
		{
			if ((*viPlayer) == nullptr) continue;
			if (Collision::RectToRect((*viEnemy)->GetHitBox(), (*viPlayer)->GetSightRange()))
				(*viPlayer)->FoundTarget((*viEnemy)->GetPosition());
			else  (*viEnemy)->LostTarget();
		}
	}
}

void BattlefieldScene::CheckHitCollision()
{
	std::vector<Enemy*>::iterator it;
	for (it = enemyList.begin(); it != enemyList.end(); it++)
	{
		if ((*it) == nullptr) continue;
		if (Collision::RectToRect((*it)->GetAttackRect(), player.GetHitBox()))
		{
			player.GetHit((*it)->GetMeleeDamage());
		}
		//if (Collision::RectToRect(player.GetAttackRect(), (*it)->GetHitBox()))
		//{
		//	player.HitEnemy();
		//	if ((*it)->GetHit(player.GetMeleeDamage()))
		//	{
		//		currentEnemy--;

		//		delete (*it);
		//		(*it) = nullptr;
		//	};
		//}
	}
	// sunpoint
	if (Mouse::LBIsDown())
	{
		mousePoint2.x = Mouse::GetPosX();
		mousePoint2.y = Mouse::GetPosY();

		std::vector<SunLight*>::iterator viSunlight;
		for (viSunlight = vSunlight.begin(); viSunlight != vSunlight.end(); viSunlight++)
		{
			if ((*viSunlight) == nullptr) continue;
			if (Collision::RectToPoint((*viSunlight)->GetHitBox(), mousePoint2))
			{
				currentSunlight--;
				sunPoint++;
				delete (*viSunlight);
				(*viSunlight) = nullptr;

			}
		}
	}
}