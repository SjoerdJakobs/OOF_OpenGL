#include "StandardObject.h"


StandardObject::StandardObject() :
	m_usesInput(true), m_usesUpdate(true), m_usesFixedUpdate(true), m_usesRenderer(true), m_usesDebugRenderer(true),
	m_usesImGui(true), m_inputPriority(1000), m_updatePriority(1000), m_renderPriority(1000),
	m_imGuiPriority(1000), m_shouldBeActive(true), m_isActiveState(true)
{
	Start();
	Awake();	
}

StandardObject::StandardObject(int priority) :
	m_usesInput(true), m_usesUpdate(true), m_usesFixedUpdate(true), m_usesRenderer(true), m_usesDebugRenderer(true),
	m_usesImGui(true), m_inputPriority(priority), m_updatePriority(priority), m_renderPriority(priority),
	m_imGuiPriority(priority), m_shouldBeActive(true), m_isActiveState(true)
{
	Start();
	Awake();	
}

StandardObject::StandardObject
(	bool usesInput, bool usesUpdate,bool usesFixedUpdate, bool usesRenderer, bool usesImGui,bool usesDebugRenderer, bool startsActivated = true,
	int inputPriority = 1000, int updatePriority = 1000, int renderPriority = 1000, int imGuiPriority = 1000):
m_usesInput(usesInput),m_usesUpdate(usesUpdate), m_usesFixedUpdate(usesFixedUpdate),m_usesRenderer(usesRenderer),m_usesDebugRenderer(usesDebugRenderer),
m_usesImGui(usesImGui),m_inputPriority(inputPriority),m_updatePriority(updatePriority),m_renderPriority(renderPriority),
m_imGuiPriority(imGuiPriority), m_shouldBeActive(startsActivated),m_isActiveState(startsActivated)
{
	Start();
	if (m_shouldBeActive) {
		Awake();
	}
}

StandardObject::~StandardObject()
{
}

void StandardObject::Start()
{
}

void StandardObject::Destroy()
{
}

void StandardObject::Input(double deltaTime)
{
}

void StandardObject::Update(double deltaTime)
{
}

void StandardObject::Render(double deltaTime)
{
}

void StandardObject::ImGuiRender(double deltaTime)
{
}

void StandardObject::DebugRender(double deltaTime)
{
}

void StandardObject::AddToLists()
{
	/*
	if (m_usesInput && m_usesUpdate && m_usesFixedUpdate && m_usesRenderer && m_usesImGui && m_usesDebugRenderer)
	{
		m_program->AddToAllLists(this);
		return;
	}
	if (m_usesInput)
	{
		m_program->AddToList(this, LoopType::input);
	}
	if (m_usesFixedUpdate)
	{
		m_program->AddToList(this, LoopType::fixedUpdate);
	}
	if (m_usesUpdate)
	{
		m_program->AddToList(this, LoopType::update);
	}
	if (m_usesRenderer)
	{
		m_program->AddToList(this, LoopType::render);
	}
	if (m_usesImGui)
	{
		m_program->AddToList(this, LoopType::imGuiRender);
	}
	if (m_usesDebugRenderer)
	{
		m_program->AddToList(this, LoopType::debugRender);
	}*/
}

void StandardObject::RemoveFromLists()
{
	/*if (!m_usesInput && !m_usesUpdate && !m_usesFixedUpdate && !m_usesRenderer && !m_usesImGui && !m_usesDebugRenderer)
	{
		m_program->RemoveFromAllLists(this);
		return;
	}
	if(!m_usesInput)
	{
		m_program->RemoveFromList(this, LoopType::input);
	}
	if (!m_usesUpdate)
	{
		m_program->RemoveFromList(this, LoopType::update);
	}
	if (!m_usesFixedUpdate)
	{
		m_program->RemoveFromList(this, LoopType::fixedUpdate);
	}
	if (!m_usesRenderer)
	{
		m_program->RemoveFromList(this,LoopType::render);
	}
	if (!m_usesImGui)
	{
		m_program->RemoveFromList(this, LoopType::imGuiRender);
	}
	if (!m_usesDebugRenderer)
	{
		m_program->RemoveFromList(this, LoopType::debugRender);
	}*/
}

void StandardObject::Awake()
{
	AddToLists();
}

void StandardObject::Sleep()
{
	RemoveFromLists();
}
