#include "StandardObject.h"
#include "Program.h"
#include "scene.h"
#include "SceneManager.h"
#include "Collider2D.h"

StandardObject::StandardObject() :
	m_pProgram(Program::GetInstance()), m_UsesInput(true), m_UsesUpdate(true), m_UsesFixedUpdate(true), m_UsesRenderer(true),
	m_UsesImGui(true), m_InputPriority(1000), m_UpdatePriority(1000),
	m_RenderPriority(1000), m_ImGuiPriority(1000), m_ShouldBeActive(true), m_IsActiveState(true), m_Id(reinterpret_cast<unsigned int>(this))
{
	//Start();
	m_pProgram->AddToObjectsList(this);
	AddToLists();
}

StandardObject::StandardObject(int priority) :
	m_pProgram(Program::GetInstance()), m_UsesInput(true), m_UsesUpdate(true), m_UsesFixedUpdate(true), m_UsesRenderer(true),
	m_UsesImGui(true), m_InputPriority(priority), m_UpdatePriority(priority),
	m_RenderPriority(priority), m_ImGuiPriority(priority), m_ShouldBeActive(true), m_IsActiveState(true), m_Id(reinterpret_cast<unsigned int>(this))
{
	//Start();
	m_pProgram->AddToObjectsList(this);
	AddToLists();
}
StandardObject::StandardObject
(bool usesInput, bool usesUpdate, bool usesFixedUpdate, bool usesRenderer, bool usesImGui , bool startsActivated = true,
	int inputPriority = 1000, int updatePriority = 1000, int renderPriority = 1000, int imGuiPriority = 1000) :
	m_pProgram(Program::GetInstance()), m_UsesInput(usesInput), m_UsesUpdate(usesUpdate), m_UsesFixedUpdate(usesFixedUpdate),
	m_UsesRenderer(usesRenderer), m_UsesImGui(usesImGui), m_InputPriority(inputPriority),
	m_UpdatePriority(updatePriority), m_RenderPriority(renderPriority), m_ImGuiPriority(imGuiPriority), m_ShouldBeActive(startsActivated),
	m_IsActiveState(startsActivated), m_Id(reinterpret_cast<unsigned int>(this))
{
	//Start();
	m_pProgram->AddToObjectsList(this);
	if (m_ShouldBeActive) {
		AddToLists();
	}
}

void StandardObject::Destroy()
{
	m_ShouldDestruct = true;
	m_UsesInput = false;
	m_UsesUpdate = false;
	m_UsesFixedUpdate = false;
	m_UsesRenderer = false;
	m_UsesImGui = false;
	m_pProgram->RemoveFromAllLists();
	m_pProgram->RemoveFromObjectsList();
	if (m_IsInAScene)
	{
		m_pProgram->GetSceneManager()->m_pCurrentScene->RemoveObjectFromScene(this);
	}
	m_pProgram = nullptr;
}

void StandardObject::Activate()
{
	Activate(true, true, true, true, false);
}

void StandardObject::Activate(bool usesInput, bool usesUpdate, bool usesRenderer, bool usesImGui,
	 int inputPriority, int updatePriority, int renderPriority, int imGuiPriority)
{
	m_InputPriority = inputPriority;
	m_UpdatePriority = updatePriority;
	m_RenderPriority = renderPriority;
	m_ImGuiPriority = imGuiPriority;
	m_UsesInput = usesInput;
	m_UsesUpdate = usesUpdate;
	m_UsesFixedUpdate = false;
	m_UsesRenderer = usesRenderer;
	m_UsesImGui = usesImGui;
	AddToLists();
}

void StandardObject::DeActivate()
{
	m_UsesInput = false;
	m_UsesUpdate = false;
	m_UsesFixedUpdate = false;
	m_UsesRenderer = false;
	m_UsesImGui = false;
	m_pProgram->RemoveFromAllLists();
}

StandardObject::~StandardObject()
{
}

void StandardObject::Input(float deltaTime)
{
}

void StandardObject::Update(float deltaTime)
{
}

void StandardObject::Render(float deltaTime)
{
}

void StandardObject::ImGuiRender(float deltaTime)
{
}

void StandardObject::OnCollision(Collider2D* other)
{

}

void StandardObject::AddToLists()
{
	if (m_UsesInput && m_UsesUpdate && m_UsesFixedUpdate && m_UsesRenderer && m_UsesImGui)
	{
		m_pProgram->AddToAllLists(this);
		return;
	}

	if (m_UsesInput)
	{
		m_pProgram->AddToList(this, LoopType::input);
	}

	if (m_UsesFixedUpdate)
	{
		m_pProgram->AddToList(this, LoopType::fixedUpdate);
	}

	if (m_UsesUpdate)
	{
		m_pProgram->AddToList(this, LoopType::update);
	}

	if (m_UsesRenderer)
	{
		m_pProgram->AddToList(this, LoopType::render);
	}

	if (m_UsesImGui)
	{
		m_pProgram->AddToList(this, LoopType::imGuiRender);
	}
}

void StandardObject::RemoveFromLists()
{
	if (!m_UsesInput && !m_UsesUpdate && !m_UsesFixedUpdate && !m_UsesRenderer && !m_UsesImGui)
	{
		m_pProgram->RemoveFromAllLists();
		return;
	}
	if (!m_UsesInput)
	{
		m_pProgram->RemoveFromList(LoopType::input);
	}
	if (!m_UsesUpdate)
	{
		m_pProgram->RemoveFromList(LoopType::update);
	}
	if (!m_UsesFixedUpdate)
	{
		m_pProgram->RemoveFromList(LoopType::fixedUpdate);
	}
	if (!m_UsesRenderer)
	{
		m_pProgram->RemoveFromList(LoopType::render);
	}
	if (!m_UsesImGui)
	{
		m_pProgram->RemoveFromList(LoopType::imGuiRender);
	}
}