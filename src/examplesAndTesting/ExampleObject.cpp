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

void ExampleObject::OnDestroy()
{
	
}

void ExampleObject::Input(float deltaTime)
{
	m_Counter++;
	std::cout << "priorityNr " << m_DeathPoint<< " and counter: "<< m_Counter<< std::endl;
	if(m_Counter >= 10)
	{
		Destroy();
	}
}

void ExampleObject::Update(float deltaTime)
{
}

void ExampleObject::Render(float deltaTime)
{
}

void ExampleObject::ImGuiRender(float deltaTime)
{
}

void ExampleObject::DebugRender(float deltaTime)
{
}
