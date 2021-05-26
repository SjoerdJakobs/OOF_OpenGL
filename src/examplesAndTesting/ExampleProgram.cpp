#include "ExampleProgram.h"
#include "ExampleObject.h"

ExampleProgram::ExampleProgram():Program()
{
}

ExampleProgram::~ExampleProgram()
{
}

void ExampleProgram::CreateInstance()
{
	if (m_pInstance)
	{
		std::cout << "Singleton has already been created" << std::endl;
	}
	else
	{
		m_pInstance = DBG_NEW ExampleProgram();
	}
}


void ExampleProgram::func()
{
	std::cout << "start \n";
	for (int i = 0; i < 2000000; ++i)
	{
		//DBG_NEW ExampleObject((rand() % 2000) + 1000);
		DBG_NEW ExampleObject(1000);
	}
	std::cout << "stop \n";
}

void ExampleProgram::AtProgramStart()
{
	//std::cout << "CHILD PROGRAM AT_PROGRAM_START" << std::endl;
	func();
}

void ExampleProgram::AddToProgramLoopBegin()
{
	//std::cout << "CHILD PROGRAM ADD_TO_PROGRAM_LoopBegin" << std::endl;
}

void ExampleProgram::OnProgramEnd()
{
}
