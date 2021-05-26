#include "GameScene0.h"

#include "Camera.h"
#include "InGameMenu.h"
#include "Player.h"

void GameScene0::OnStart()
{
	AddObjectToScene(DBG_NEW Player(1000));
	AddObjectToScene(DBG_NEW InGameMenu());
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