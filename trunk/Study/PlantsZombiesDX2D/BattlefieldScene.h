#pragma once
#include "Scene.h"
#include "Texture.h"
#include "Plants.h"
#include "Enemy.h"
#include "SunLight.h"
#include "World.h"
#include "Object.h"
#include "UI.h"
#include "Button.h"
#include "Camera.h"
#include <vector>

class BattlefieldScene : public Scene
{
private:
	Camera	camera;
	Object	background;
	UI		seedbank;
	UI		shovelbank;
	UI		pointcard;
	Button	SFCard;
	bool	bSFCard = false;
	Button	WNCard;
	bool	bWNCard = false;
	Button	PSCard;
	bool	bPSCard = false;
	Object	cursor;

	int		sunPoint = 0;

	World	world;
	Plants	player;

	// Plant
	std::vector<Vector2D> plantSpawnPoint;

	// PeaShooter
	Plants PSReleaser;
	int	currentPlayer = 0;
	int spawnedPlayer = 0;
	const int maxPlayer = 20;
	Vector2D playerSpawnPoint;
	std::vector<Plants*> playerList;

	// WallNut
	Plants WNReleaser;
	int currentWallNut = 0;
	int spawnedWallNut = 0;
	const int maxWallNut = 20;
	Vector2D wallnutSpawnPoint;
	std::vector<Plants*> wallnutList;

	// SunFlower
	Plants SFReleaser;
	int currentSunFlower = 0;
	int spawnedSunFlower = 0;
	const int maxSunFlower = 20;
	Vector2D sunFlowerSpawnPoint;
	std::vector<Plants*> sunflowerList;

	// Zombie
	int	currentEnemy = 0;
	int spawnedEnemy = 0;
	float startSpawnTimer = 0.0f;
	float spawnTimer = 0.0f;
	const float spawnAt = 3.0f; // 햇살 스폰 간격
	const int maxEnemy = 30;
	std::vector<Vector2D> spawnPoint;
	std::vector<Enemy*> enemyList;
	Enemy enemyReleaser;

	// SunLight
	int	currentSunlight = 0;
	int spawnedSunlight = 0;
	float spawnSunTimer = 0.0f;
	const float spawnSunAt = 1.0f; // 햇살 스폰 간격
	const int maxSunlight = 30;
	std::vector<Vector2D> spawnPointSun;
	std::vector<SunLight*> vSunlight;
	SunLight sunlightReleaser;
	Vector2D mousePoint;
	POINT	mousePoint2;
public:
	virtual void Initialize() override;
	virtual void Update(float delta) override;
	virtual void Render(float delta) override;


private:
	void UpdateElements(float delta);

	void CheckSightCollision();
	void CheckHitCollision();
	// std::vector<Plants*> list,
	void SpawnPlayer(std::vector<Plants*> &list,
					float width, float height,
					int spawned, int current, int nPlayer,
					Vector2D spawnPoint, std::wstring imagePath,
					UINT NumFrame, UINT Line);
	void SpawnPlayerTest(int nPlayer);
	void SpawnEntities(float delta);
	void SpawnEnemy(int nEnemy);

	void SpawnSunEntities(float delta);
	void SpawnSunlight(int nSunlight);

	void CardSet();
};

