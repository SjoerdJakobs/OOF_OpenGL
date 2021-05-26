#include "MainMenuScene.h"
#include "MainMenu.h"

void MainMenuScene::OnStart()
{
	AddObjectToScene(static_cast<StandardObject*>(DBG_NEW MainMenu()));
}

void MainMenuScene::OnStop()
{
}

MainMenuScene::MainMenuScene()
{
	m_SceneName = SceneNames::MainMenu;
}

MainMenuScene::~MainMenuScene()
{
}