#include "GameScene0.h"

#include "Camera.h"
#include "InGameMenu.h"
#include "LevelManager.h"
#include "ParallaxBackground.h"
#include "Player.h"

void GameScene0::OnStart()
{
	Player* p_newPlayer = DBG_NEW Player(1000);
	AddObjectToScene(p_newPlayer);
	AddObjectToScene(DBG_NEW InGameMenu());
	AddObjectToScene(DBG_NEW ParallaxBackground());

	LevelManager* p_newLevelManager = DBG_NEW LevelManager();
	AddObjectToScene(p_newLevelManager);
	p_newLevelManager->GivePlayerPointer(p_newPlayer);
}

void GameScene0::OnStop()
{
	
}

GameScene0::GameScene0()
{
	m_SceneName = SceneNames::Scene1;
}

GameScene0::~GameScene0()
{
}