#include "InGameMenu.h"
#include "SceneManager.h"

void InGameMenu::Start()
{
	m_WindowFlags |= ImGuiWindowFlags_NoTitleBar;
	m_WindowFlags |= ImGuiWindowFlags_NoScrollbar;
	m_WindowFlags |= ImGuiWindowFlags_NoMove;
	m_WindowFlags |= ImGuiWindowFlags_NoResize;
	m_WindowFlags |= ImGuiWindowFlags_NoCollapse;
	m_WindowFlags |= ImGuiWindowFlags_NoNav;
	//m_WindowFlags |= ImGuiWindowFlags_NoBackground;
	m_WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void InGameMenu::Awake()
{
}

void InGameMenu::Sleep()
{
}

void InGameMenu::Input(float deltaTime)
{
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_ESCAPE)) {
		if (!m_HasPressedESC)
		{
			m_ShowMenu = !m_ShowMenu;
			if (m_ShowMenu)
			{
				m_TimeScaleWhenPaused = m_pProgram->GetTimeScale();
				m_pProgram->SetTimeScale(0.0f);
			}
			else
			{
				m_pProgram->SetTimeScale(m_TimeScaleWhenPaused);
			}
			m_HasPressedESC = true;
		}
	}
	else
	{
		m_HasPressedESC = false;
	}
}

void InGameMenu::ImGuiRender(float deltaTime)
{

	if (m_ShowMenu)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.05f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.05f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.05f, 0.8f, 0.8f));

		ImGui::PushFont(m_pMenuFont);

		ImGui::SetNextWindowPos(ImVec2(m_ResumeButtonXPos, m_ResumeButtonYPos), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(m_MenuWidth, m_MenuHeight), ImGuiCond_Once);

		ImGui::Begin("InGameMenuWindow", nullptr, m_WindowFlags);

		if (ImGui::Button("RESUME", ImVec2(m_ResumeButtonWidth, m_ResumeButtonHeight)))
		{
			m_ShowMenu = !m_ShowMenu;
			m_pProgram->SetTimeScale(m_TimeScaleWhenPaused);
		}

		if (ImGui::Button("MAIN MENU", ImVec2(m_QuitButtonWidth, m_QuitButtonHeight)))
		{
			m_ShowMenu = !m_ShowMenu;
			m_pProgram->SetTimeScale(m_TimeScaleWhenPaused);
			m_pProgram->GetSceneManager()->SwitchToScene(SceneNames::MainMenu);
		}

		if (ImGui::Button("OPTIONS", ImVec2(m_OptionsButtonWidth, m_OptionsButtonHeight)))
		{
			//m_pProgram->GetSceneManager()->SwitchToScene(SceneNames::Options);
		}

		if (ImGui::Button("EXIT", ImVec2(m_ExitButtonWidth, m_ExitButtonHeight)))
		{
			m_pProgram->SetRunProgram(false);
		}

		ImGui::End();

		ImGui::PopStyleColor(3);
		ImGui::PopFont();
	}
}

void InGameMenu::OnDestroy()
{
	//std::cout << "InGameMenu destroyed" << std::endl;
}

InGameMenu::InGameMenu() :StandardObject(true, false, false, false, true, true,
		1000, 1000, 1000, 1000),
	m_ShowMenu(false), m_HasPressedESC(false)
{
}

InGameMenu::~InGameMenu()
{

}