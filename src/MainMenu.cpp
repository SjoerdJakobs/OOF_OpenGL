#include "MainMenu.h"
#include "SceneManager.h"
#include "imgui/imgui.h"

void MainMenu::Start()
{
	m_WindowFlags |= ImGuiWindowFlags_NoTitleBar;
	m_WindowFlags |= ImGuiWindowFlags_NoScrollbar;
	m_WindowFlags |= ImGuiWindowFlags_NoMove;
	m_WindowFlags |= ImGuiWindowFlags_NoResize;
	m_WindowFlags |= ImGuiWindowFlags_NoCollapse;
	m_WindowFlags |= ImGuiWindowFlags_NoNav;
	m_WindowFlags |= ImGuiWindowFlags_NoBackground;
	m_WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void MainMenu::Awake()
{
}

void MainMenu::Sleep()
{
}

void MainMenu::Input(float deltaTime)
{
}

//Todo: change menu system.
/**
 * there has to be a better way to make multiple buttons but right now i just want a working MainMenu
 */
void MainMenu::ImGuiRender(float deltaTime)
{
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.05f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.05f, 0.7f, 0.7f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.05f, 0.8f, 0.8f));
	ImGui::PushFont(m_pMenuFont);

	/*
	 * this all probably does not need its own hidden window for each button but this was the easiest solution
	 */
	ImGui::SetNextWindowPos(ImVec2(m_StartButtonXPos, m_StartButtonYPos), ImGuiCond_Once);
	ImGui::Begin("InvisibleWindow0", nullptr, m_WindowFlags);
	if (ImGui::Button("START", ImVec2(m_StartButtonWidth, m_StartButtonHeight)))
	{
		m_pProgram->GetSceneManager()->SwitchToScene(SceneNames::Scene1);
	}
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(m_HowToPlayButtonXPos, m_HowToPlayButtonYPos), ImGuiCond_Once);

	ImGui::Begin("InvisibleWindow1", nullptr, m_WindowFlags);
	if (ImGui::Button("HOW TO PLAY", ImVec2(m_HowToPlayButtonWidth, m_HowToPlayButtonHeight)))
	{
		std::cout << "Use WASD or the arrow keys for movement." << std::endl;
		std::cout << "pressing shift will make you sprint." << std::endl;
		std::cout << "Coins give you points!." << std::endl;
		std::cout << "EVERYTHING ELSE WILL DAMAGE YOU IF IT TOUCHES YOU" << std::endl;
		std::cout << "try to get as many points as possible until you die" << std::endl;
		m_pProgram->GetSceneManager()->SwitchToScene(SceneNames::HowToPlay);
	}
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(m_OptionsButtonXPos, m_OptionsButtonYPos), ImGuiCond_Once);
	ImGui::Begin("InvisibleWindow2", nullptr, m_WindowFlags);
	if (ImGui::Button("OPTIONS", ImVec2(m_OptionsButtonWidth, m_OptionsButtonHeight)))
	{
		//m_pProgram->GetSceneManager()->SwitchToScene(SceneNames::Options);
		//m_pProgram->GetSceneManager()->SwitchToScene(SceneNames::ObjectTestScene);
	}
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(m_ExitButtonXPos, m_ExitButtonYPos), ImGuiCond_Once);
	ImGui::Begin("InvisibleWindow3", nullptr, m_WindowFlags);
	if (ImGui::Button("EXIT", ImVec2(m_ExitButtonWidth, m_ExitButtonHeight)))
	{
		m_pProgram->SetRunProgram(false);
	}
	ImGui::End();

	ImGui::PopStyleColor(3);
	ImGui::PopFont();

	//ImGui::ShowDemoWindow(nullptr);
}

void MainMenu::OnDestroy()
{
}

MainMenu::MainMenu() :
	StandardObject(true, false, false, false, true, true,
		1000, 1000, 1000, 1000)
{
}

MainMenu::~MainMenu()
{
	//std::cout << "mainmenu destroyed\n";
}