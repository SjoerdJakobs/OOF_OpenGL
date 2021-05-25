#pragma once
#include <string>


#include "Program.h"
#include "StandardObject.h"
#include "imgui/imgui.h"

class MainMenu final : public StandardObject
{
private:
	ImGuiIO& m_rIO = ImGui::GetIO();
	ImFont* m_pMenuFont = m_rIO.Fonts->Fonts[1];
	ImGuiWindowFlags m_WindowFlags = 0;

	//Todo: make menu adapt to screen size after this project, because the screen size is decided beforehand all these values will be const for now.
	const int m_WindowWidth = m_pProgram->GetScreenWidth();
	const int m_WindowHeight = m_pProgram->GetScreenHeight();

	const int m_ButtonDistanceYPos = 40;
	
	const std::string m_StartButtonLabel = "START";
	const float m_StartButtonWidth = 300.0f;
	const float m_StartButtonHalfWidth = m_StartButtonWidth / 2.0f;
	const float m_StartButtonHeight = 100.0f;
	const float m_StartButtonHalfHeight = m_StartButtonHeight / 2.0f;
	const float m_StartButtonXPos = m_WindowWidth / 2.0f - m_StartButtonHalfWidth;
	const float m_StartButtonYPos = m_WindowHeight / 2.0f - 250.0f;

	const std::string m_HowToPlayButtonLabel = "HOW TO PLAY";
	const float m_HowToPlayButtonWidth = 450.0f;
	const float m_HowToPlayButtonHalfWidth = m_HowToPlayButtonWidth / 2.0f;
	const float m_HowToPlayButtonHeight = 100.0f;
	const float m_HowToPlayButtonHalfHeight = m_HowToPlayButtonHeight / 2.0f;
	const float m_HowToPlayButtonXPos = m_WindowWidth / 2.0f - m_HowToPlayButtonHalfWidth;
	const float m_HowToPlayButtonYPos = m_StartButtonYPos+m_StartButtonHeight+m_ButtonDistanceYPos;

	const std::string m_OptionsButtonLabel = "OPTIONS";
	const float m_OptionsButtonWidth = 300.0f;
	const float m_OptionsButtonHalfWidth = m_OptionsButtonWidth / 2.0f;
	const float m_OptionsButtonHeight = 100.0f;
	const float m_OptionsButtonHalfHeight = m_OptionsButtonHeight / 2.0f;
	const float m_OptionsButtonXPos = m_WindowWidth / 2.0f - m_OptionsButtonHalfWidth;
	const float m_OptionsButtonYPos = m_HowToPlayButtonYPos + m_HowToPlayButtonHeight + m_ButtonDistanceYPos;
	
	const std::string m_ExitButtonLabel = "EXIT";
	const float m_ExitButtonWidth = 300.0f;
	const float m_ExitButtonHalfWidth = m_ExitButtonWidth / 2.0f;
	const float m_ExitButtonHeight = 100.0f;
	const float m_ExitButtonHalfHeight = m_ExitButtonHeight / 2.0f;
	const float m_ExitButtonXPos = m_WindowWidth / 2.0f - m_ExitButtonHalfWidth;
	const float m_ExitButtonYPos = m_OptionsButtonYPos + m_OptionsButtonHeight + m_ButtonDistanceYPos;
	
protected:
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void Input(float deltaTime) override;
	void ImGuiRender(float deltaTime) override;
	void OnDestroy() override;
public:
	MainMenu();
	~MainMenu() override;
};
