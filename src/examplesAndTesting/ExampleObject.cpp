#include "ExampleObject.h"

#include <iostream>

void ExampleObject::Start()
{
	std::cout << "example object start called"<<std::endl;
	m_DeathPoint = GetUpdatePriority();
}

void ExampleObject::Awake()
{
}

void ExampleObject::Sleep()
{
}

void ExampleObject::Destroy()
{
	StandardObject::Destroy();
}

void ExampleObject::Input(double deltaTime)
{
	m_Counter++;
	std::cout << "priorityNr " << m_DeathPoint<< " and counter: "<< m_Counter<< std::endl;
	if(m_Counter >= 10)
	{
		Destroy();
	}
}

void ExampleObject::Update(double deltaTime)
{
}

void ExampleObject::Render(double deltaTime)
{
}

void ExampleObject::ImGuiRender(double deltaTime)
{
}

void ExampleObject::DebugRender(double deltaTime)
{
}
