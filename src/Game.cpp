#include "Game.h"

#include "GameScene0.h"
#include "MainMenuScene.h"
#include "Rectangle.h"
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

void Game::ProgramStart()
{
	Program::ProgramStart();
}

void Game::AtProgramStart()
{
	AddScene(static_cast<Scene*>(new MainMenuScene()));
	AddScene(static_cast<Scene*>(new GameScene0()));
	m_pSceneManager->Start();
}

void Game::AddToProgramLoopBegin()
{

}

