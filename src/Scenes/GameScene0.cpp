#include "GameScene0.h"
#include "Player.h"

void GameScene0::OnStart()
{
	AddObjectToScene(new Player(1000));
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
