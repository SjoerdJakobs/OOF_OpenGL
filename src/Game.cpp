#include "Game.h"

#include "ObjectsStressTestScene.h"
#include "GameScene0.h"
#include "MainMenuScene.h"
#include "SceneManager.h"


Game::Game() :Program()
{
}

Game::~Game()
{
}

void Game::CreateInstance()
{
	if (m_pInstance)
	{
		std::cout << "Singleton has already been created" << std::endl;
	}
	else
	{
		m_pInstance = new Game();
	}
}

void Game::DeleteInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
	else
	{
		std::cout << "Singleton has already been deleted" << std::endl;
	}
}

void Game::AtProgramStart()
{
	AddScene(static_cast<Scene*>(new MainMenuScene()));
	AddScene(static_cast<Scene*>(new ObjectsStressTestScene()));
	AddScene(static_cast<Scene*>(new GameScene0()));
}

void Game::AddToProgramLoopBegin()
{
}

void Game::OnProgramEnd()
{
}