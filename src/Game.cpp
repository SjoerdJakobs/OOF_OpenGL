#include "Game.h"

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
		m_pInstance = DBG_NEW Game();
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
	AddScene(static_cast<Scene*>(DBG_NEW MainMenuScene()));
	AddScene(static_cast<Scene*>(DBG_NEW GameScene0()));
}

void Game::AddToProgramLoopBegin()
{
}

void Game::OnProgramEnd()
{
	
}
