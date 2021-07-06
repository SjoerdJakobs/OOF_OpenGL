#include "GameScene0.h"


#include "AllocationMetrics.h"
#include "Camera.h"
#include "InGameMenu.h"
#include "LevelManager.h"
#include "ParallaxBackground.h"
#include "Player.h"
#include "PickupManager.h"

void GameScene0::OnStart()
{
	PrintMemoryUsage("before gamescene start");
	Player* p_newPlayer = new Player(1000);
	AddObjectToScene(p_newPlayer);
	AddObjectToScene(new InGameMenu());
	AddObjectToScene(new ParallaxBackground());
	
	LevelManager* p_newLevelManager = new LevelManager();
	AddObjectToScene(p_newLevelManager);
	p_newLevelManager->GivePlayerPointer(p_newPlayer);
	
	PickupManager* p_newPickupManager = new PickupManager();
	AddObjectToScene(p_newPickupManager);
	p_newPickupManager->GivePlayerPointer(p_newPlayer);
	PrintMemoryUsage("after gamescene start");
}

void GameScene0::OnStop()
{
	PrintMemoryUsage("on gamescene stop");
}

GameScene0::GameScene0()
{
	m_SceneName = SceneNames::Scene1;
}

GameScene0::~GameScene0()
{
	PrintMemoryUsage("on gamescene destructor");
}