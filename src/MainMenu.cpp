#include "MainMenu.h"


#include "Program.h"
#include "SceneManager.h"
#include "imgui/imgui.h"

void MainMenu::Start()
{
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

void MainMenu::ImGuiRender(float deltaTime)
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_MenuBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoNav;
	window_flags |= ImGuiWindowFlags_NoBackground;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	

	ImGui::SetNextWindowPos(ImVec2(200, 100), ImGuiCond_FirstUseEver);
	ImGui::Begin("Invisible window##InvisibleWindow",nullptr ,
		ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::Button("Hello!");
	ImGui::End();

	ImGui::ShowDemoWindow(NULL);
	
	ImGui::Begin("MainMenu");

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);                   // Create a m_pWindow called "Hello, world!" and append into it.
	if (ImGui::Button("play"))
	{
		m_pProgram->GetSceneManager()->SwitchToScene(SceneNames::Scene1);
	}
	
	ImGui::End();
}

void MainMenu::OnDestroy()
{
	
}

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}
