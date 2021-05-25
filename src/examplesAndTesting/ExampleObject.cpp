#include "ExampleObject.h"

#include <iostream>

ExampleObject::~ExampleObject()
{
	
}

void ExampleObject::Start()
{
	m_DeathPoint = ( static_cast<float>(rand() % 600) + 300.0f)/100.0f;
	//std::cout << m_DeathPoint <<std::endl;
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
	m_Counter += deltaTime;
	//std::cout << "deathpoint " << m_DeathPoint<< " and counter: "<< m_Counter<< std::endl;
	if(m_Counter >= m_DeathPoint)
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
