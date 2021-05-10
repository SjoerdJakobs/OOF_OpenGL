#include "Game.h"

#include "Player.h"
#include "Rectangle.h"

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
	std::cout << "CHILD PROGRAM CALLS PROGRAM_START" << std::endl;
	Program::ProgramStart();

}
//
//void Game::func()
//{
//	//std::cout << GetTimeScale();
//	for (int i = 0; i < 1000; ++i)
//	{
//		ExampleObject* obj2 = new ExampleObject((rand() % 2000) + 1000);
//	}
//	ExampleObject* obj = new ExampleObject(1000);
//}

void Game::AtProgramStart()
{
	std::cout << "CHILD PROGRAM AT_PROGRAM_START" << std::endl;
	
	m_Player = new Player(1000);
	//func();
}

void Game::AddToProgramLoopBegin()
{
	//std::cout << "CHILD PROGRAM ADD_TO_PROGRAM_LoopBegin" << std::endl;
}

