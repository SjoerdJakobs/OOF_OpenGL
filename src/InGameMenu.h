#pragma once
#include "Program.h"
#include "StandardObject.h"
#include "imgui/imgui.h"

class InGameMenu final : public StandardObject
{
private:

	bool m_ShowMenu;
	bool m_HasPressedESC;
	float m_TimeScaleWhenPaused = 0;

	ImGuiIO& m_rIO = ImGui::GetIO();
	ImFont* m_pMenuFont = m_rIO.Fonts->Fonts[1];
	ImGuiWindowFlags m_WindowFlags = 0;

	//Todo: make menu adapt to screen size after this project, because the screen size is decided beforehand all these values will be const for now.
	const int m_WindowWidth = m_pProgram->GetScreenWidth();
	const int m_WindowHeight = m_pProgram->GetScreenHeight();

	const int m_ButtonDistancePos = 15;

	const std::string m_ResumeButtonLabel = "RESUME";
	const float m_ResumeButtonWidth = 300.0f;
	const float m_ResumeButtonHalfWidth = m_ResumeButtonWidth / 2.0f;
	const float m_ResumeButtonHeight = 100.0f;
	const float m_ResumeButtonHalfHeight = m_ResumeButtonHeight / 2.0f;
	const float m_ResumeButtonXPos = m_WindowWidth / 2.0f - m_ResumeButtonHalfWidth;
	const float m_ResumeButtonYPos = m_WindowHeight / 2.0f - 250.0f;

	const std::string m_QuitButtonLabel = "MAIN MENU";
	const float m_QuitButtonWidth = 300.0f;
	const float m_QuitButtonHalfWidth = m_QuitButtonWidth / 2.0f;
	const float m_QuitButtonHeight = 100.0f;
	const float m_QuitButtonHalfHeight = m_QuitButtonHeight / 2.0f;
	const float m_QuitButtonXPos = m_WindowWidth / 2.0f - m_QuitButtonHalfWidth;
	const float m_QuitButtonYPos = m_ResumeButtonYPos + m_ResumeButtonHeight + m_ButtonDistancePos;

	const std::string m_OptionsButtonLabel = "OPTIONS";
	const float m_OptionsButtonWidth = 300.0f;
	const float m_OptionsButtonHalfWidth = m_OptionsButtonWidth / 2.0f;
	const float m_OptionsButtonHeight = 100.0f;
	const float m_OptionsButtonHalfHeight = m_OptionsButtonHeight / 2.0f;
	const float m_OptionsButtonXPos = m_WindowWidth / 2.0f - m_OptionsButtonHalfWidth;
	const float m_OptionsButtonYPos = m_QuitButtonYPos + m_QuitButtonHeight + m_ButtonDistancePos;

	const std::string m_ExitButtonLabel = "EXIT";
	const float m_ExitButtonWidth = 300.0f;
	const float m_ExitButtonHalfWidth = m_ExitButtonWidth / 2.0f;
	const float m_ExitButtonHeight = 100.0f;
	const float m_ExitButtonHalfHeight = m_ExitButtonHeight / 2.0f;
	const float m_ExitButtonXPos = m_WindowWidth / 2.0f - m_ExitButtonHalfWidth;
	const float m_ExitButtonYPos = m_OptionsButtonYPos + m_OptionsButtonHeight + m_ButtonDistancePos;

	const float m_MenuWidth = m_QuitButtonWidth + m_ButtonDistancePos;
	const float m_MenuHeight = m_ResumeButtonHeight + m_QuitButtonHeight + m_OptionsButtonHeight + m_ExitButtonHeight + m_ButtonDistancePos * 2 - 3;

protected:
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void Input(float deltaTime) override;
	void ImGuiRender(float deltaTime) override;
	void OnDestroy() override;
public:
	InGameMenu();
	~InGameMenu() override;
};
