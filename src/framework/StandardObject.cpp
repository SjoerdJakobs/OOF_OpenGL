#include "StandardObject.h"
#include "Program.h"


StandardObject::StandardObject() :
	m_Program(Program::GetInstance()), m_UsesInput(true), m_UsesUpdate(true), m_UsesFixedUpdate(true), m_UsesRenderer(true),
	m_UsesDebugRenderer(true), m_UsesImGui(true), m_InputPriority(1000), m_UpdatePriority(1000),
	m_RenderPriority(1000), m_ImGuiPriority(1000), m_ShouldBeActive(true), m_IsActiveState(true)
{
	std::cout << "standardobject" << std::endl;
	//Start();
	
	m_Program->AddToObjectsList(this);
	AddToLists();
}

StandardObject::StandardObject(int priority) :
	m_Program(Program::GetInstance()), m_UsesInput(true), m_UsesUpdate(true), m_UsesFixedUpdate(true), m_UsesRenderer(true),
	m_UsesDebugRenderer(true), m_UsesImGui(true), m_InputPriority(priority), m_UpdatePriority(priority),
	m_RenderPriority(priority), m_ImGuiPriority(priority), m_ShouldBeActive(true), m_IsActiveState(true)
{
	//Start();
	m_Program->AddToObjectsList(this);
	AddToLists();
}

StandardObject::StandardObject
(	bool usesInput, bool usesUpdate,bool usesFixedUpdate, bool usesRenderer, bool usesImGui,bool usesDebugRenderer, bool startsActivated = true,
	int inputPriority = 1000, int updatePriority = 1000, int renderPriority = 1000, int imGuiPriority = 1000):
m_Program(Program::GetInstance()),m_UsesInput(usesInput), m_UsesUpdate(usesUpdate),m_UsesFixedUpdate(usesFixedUpdate),
m_UsesRenderer(usesRenderer),m_UsesDebugRenderer(usesDebugRenderer),m_UsesImGui(usesImGui),m_InputPriority(inputPriority),
m_UpdatePriority(updatePriority),m_RenderPriority(renderPriority), m_ImGuiPriority(imGuiPriority),m_ShouldBeActive(startsActivated),
m_IsActiveState(startsActivated)
{
	//Start();
	m_Program->AddToObjectsList(this);
	if (m_ShouldBeActive) {
		AddToLists();
	}
}

StandardObject::~StandardObject()
{
}

void StandardObject::Start()
{
	ASSERT(true, "baseclass start should not be called");
}

void StandardObject::Destroy()
{
	m_ShouldDestruct = true;
	m_UsesInput = false;
	m_UsesUpdate = false;
	m_UsesFixedUpdate = false;
	m_UsesRenderer = false;
	m_UsesImGui = false;
	m_UsesDebugRenderer = false;
	m_Program->RemoveFromAllLists();
	m_Program->RemoveFromObjectsList();
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
	
	if (m_UsesInput && m_UsesUpdate && m_UsesFixedUpdate && m_UsesRenderer && m_UsesImGui && m_UsesDebugRenderer)
	{
		m_Program->AddToAllLists(this);
		return;
	}
	
	if (m_UsesInput)
	{
		m_Program->AddToList(this, LoopType::input);
	}
	
	if (m_UsesFixedUpdate)
	{
		m_Program->AddToList(this, LoopType::fixedUpdate);
	}
	
	if (m_UsesUpdate)
	{
		m_Program->AddToList(this, LoopType::update);
	}
	
	if (m_UsesRenderer)
	{
		m_Program->AddToList(this, LoopType::render);
	}
	
	if (m_UsesImGui)
	{
		m_Program->AddToList(this, LoopType::imGuiRender);
	}
	
	if (m_UsesDebugRenderer)
	{
		m_Program->AddToList(this, LoopType::debugRender);
	}
}

void StandardObject::RemoveFromLists()
{
	if (!m_UsesInput && !m_UsesUpdate && !m_UsesFixedUpdate && !m_UsesRenderer && !m_UsesImGui && !m_UsesDebugRenderer)
	{
		m_Program->RemoveFromAllLists();
		return;
	}
	if(!m_UsesInput)
	{
		m_Program->RemoveFromList( LoopType::input);
	}
	if (!m_UsesUpdate)
	{
		m_Program->RemoveFromList( LoopType::update);
	}
	if (!m_UsesFixedUpdate)
	{
		m_Program->RemoveFromList(LoopType::fixedUpdate);
	}
	if (!m_UsesRenderer)
	{
		m_Program->RemoveFromList(LoopType::render);
	}
	if (!m_UsesImGui)
	{
		m_Program->RemoveFromList( LoopType::imGuiRender);
	}
	if (!m_UsesDebugRenderer)
	{
		m_Program->RemoveFromList(LoopType::debugRender);
	}
}

void StandardObject::Awake()
{
}

void StandardObject::Sleep()
{
}
