#include "Player.h"

#include "Program.h"
#include "Camera.h"
#include "Rectangle.h"
#include "SpriteSheetFramePicker.h"
#include <GLFW/glfw3.h>

#include "SceneManager.h"

Player::~Player()
{
	std::cout << "player destroyed\n";
}

void Player::TakeDamage(int damage)
{
}

void Player::Heal(int healAmount)
{
}

void Player::Start()
{
	m_Camera = &Camera::instance();
	m_Rectangle = new Rectangle(400, 400, 100, 100, "res/textures/professor_walk_cycle_no_hat.png", 0, 0.555555582f, 0.666666682f, 0, 0.250000000f);
	float col[4]{ 0.7f ,0.55f ,0.24f ,1.0f };
	m_ColRectangle = new Rectangle(400, 400, 100, 100, col);

	for (int i = 0; i < TestRectangles; ++i)
	{
		for (int j = 0; j < TestRectangles; ++j)
		{
			float randNr = (float)rand() / ((float)(RAND_MAX / 1));
			if (randNr < 0.25f)
			{
				m_Rectangles[i][j] = new Rectangle(100.0f, 100.0f, -400.0f + 200.0f * i, -400.0f + 200.0f * j, "res/textures/BlueBlock.png", 1);
			}
			else if (randNr < 0.50f)
			{
				m_Rectangles[i][j] = new Rectangle(100.0f, 100.0f, -400.0f + 200.0f * i, -400.0f + 200.0f * j, "res/textures/GreenBlock.png", 2);
			}
			else if (randNr < 0.75f)
			{
				m_Rectangles[i][j] = new Rectangle(100.0f, 100.0f, -400.0f + 200.0f * i, -400.0f + 200.0f * j, "res/textures/OrangeBlock.png", 3);
			}
			else
			{
				m_Rectangles[i][j] = new Rectangle(100.0f, 100.0f, -400.0f + 200.0f * i, -400.0f + 200.0f * j, "res/textures/PurpleBlock.png", 4);
			}
		}
	}
}

void Player::Awake()
{
}

void Player::Sleep()
{
}

void Player::OnDestroy()
{
	for (int i = 0; i < TestRectangles; ++i)
	{
		for (int j = 0; j < TestRectangles; ++j)
		{
			delete m_Rectangles[i][j];
		}
	}

	delete m_Rectangle;
	delete m_ColRectangle;
}

void Player::Input(float deltaTime)
{
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_D)) {
		m_PlayerPos.x += deltaTime * 500.0f;
	}
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_A)) {
		m_PlayerPos.x += deltaTime * -500.0f;
	}
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_W)) {
		m_PlayerPos.y += deltaTime * 500.0f;
	}
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_S)) {
		m_PlayerPos.y += deltaTime * -500.0f;
	}
	m_Camera->SetTargetPos(m_PlayerPos);
}

void Player::Update(float deltaTime)
{
	m_FrameTimer += deltaTime;
	if (m_FrameTimer >= m_TimeUntilNextFrame)
	{
		m_FrameTimer -= m_TimeUntilNextFrame;
		m_FrameCount++;
		if (m_FrameCount > m_EndFrame)
		{
			m_FrameCount = m_BeginFrame;
		}
	}
}

void Player::Render(float deltaTime)
{
	m_ColRectangle->Draw();
	m_Rectangle->SetXPos(m_PlayerPos.x + (float)m_pProgram->GetScreenWidth() / 2.0f);
	m_Rectangle->SetYPos(m_PlayerPos.y + (float)m_pProgram->GetScreenHeight() / 2.0f);
	SpriteSheetFramePicker picker;
	picker.PickFrame(9, 4, m_FrameCount, m_Rectangle);
	for (int i = 0; i < TestRectangles; ++i)
	{
		for (int j = 0; j < TestRectangles; ++j)
		{
			m_Rectangles[i][j]->DrawWithTexture();
		}
	}
}

void Player::ImGuiRender(float deltaTime)
{
	ImGui::Begin("MainMenu");

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);                   // Create a m_pWindow called "Hello, world!" and append into it.
	if (ImGui::Button("MainMenu"))
	{
		m_pProgram->GetSceneManager()->SwitchToScene(SceneNames::MainMenu);
	}
	int one = 1;
	ImGui::Text("player x %.2f", static_cast<float>(m_PlayerPos.x));
	ImGui::Text("player y %.2f", static_cast<float>(m_PlayerPos.y));

	ImGui::End();
}

void Player::DebugRender(float deltaTime)
{
}