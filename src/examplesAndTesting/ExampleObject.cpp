#include "ExampleObject.h"

#include <iostream>

ExampleObject::ExampleObject(int priority): StandardObject(priority), m_pBigNr0(nullptr), m_pBigNr1(nullptr),
                                            m_pBigNr2(nullptr),
                                            m_pBigNr3(nullptr),
                                            m_pBigNr4(nullptr),
                                            m_pBigNr5(nullptr),
                                            m_pBigNr6(nullptr),
                                            m_pBigNr7(nullptr),
                                            m_pBigNr8(nullptr),
                                            m_pBigNr9(nullptr)
{
}

ExampleObject::~ExampleObject()
{
	
}

void ExampleObject::Start()
{
	m_pBigNr0 = new _LONGDOUBLE{ 10000000.0 };
	m_pBigNr1 = new _LONGDOUBLE{ 10000000.0 };
	m_pBigNr2 = new _LONGDOUBLE{ 10000000.0 };
	m_pBigNr3 = new _LONGDOUBLE{ 10000000.0 };
	m_pBigNr4 = new _LONGDOUBLE{ 10000000.0 };
	m_pBigNr5 = new _LONGDOUBLE{ 10000000.0 };
	m_pBigNr6 = new _LONGDOUBLE{ 10000000.0 };
	m_pBigNr7 = new _LONGDOUBLE{ 10000000.0 };
	m_pBigNr8 = new _LONGDOUBLE{ 10000000.0 };
	m_pBigNr9 = new _LONGDOUBLE{ 10000000.0 };
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
	delete(m_pBigNr0);
	delete(m_pBigNr1);
	delete(m_pBigNr2);
	delete(m_pBigNr3);
	delete(m_pBigNr4);
	delete(m_pBigNr5);
	delete(m_pBigNr6);
	delete(m_pBigNr7);
	delete(m_pBigNr8);
	delete(m_pBigNr9);
}

void ExampleObject::Input(float deltaTime)
{
	//m_Counter += deltaTime;
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