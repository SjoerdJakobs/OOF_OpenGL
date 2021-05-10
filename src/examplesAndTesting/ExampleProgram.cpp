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
		m_pInstance = new ExampleProgram();
	}
}

void ExampleProgram::ProgramStart()
{
	std::cout << "CHILD PROGRAM CALLS PROGRAM_START"<<std::endl;
	Program::ProgramStart();

}

void ExampleProgram::func()
{
	//std::cout << GetTimeScale();
	for (int i = 0; i < 1000; ++i)
	{
		ExampleObject* obj2 = new ExampleObject((rand() % 2000) + 1000);
	}
	ExampleObject* obj = new ExampleObject(1000);
}

void ExampleProgram::AtProgramStart()
{
	std::cout << "CHILD PROGRAM AT_PROGRAM_START" << std::endl;
	func();
}

void ExampleProgram::AddToProgramLoopBegin()
{
	std::cout << "CHILD PROGRAM ADD_TO_PROGRAM_LoopBegin" << std::endl;
}