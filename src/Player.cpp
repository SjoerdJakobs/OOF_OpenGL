#include "Player.h"

#include "Program.h"
#include "Camera.h"
#include "Rectangle.h"
#include "SpriteSheetFramePicker.h"
#include <GLFW/glfw3.h>

#include "SceneManager.h"

Player::Player(int priority) :StandardObject(priority)
{
	
}

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
	m_pCamera = &Camera::instance();
	m_Rectangle = DBG_NEW Rectangle(200, 200, 100, 100, "res/textures/professor_walk_cycle_no_hat.png", 0, 0.555555582f, 0.666666682f, 0, 0.250000000f);
	float col[4]{ 0.7f ,0.55f ,0.24f ,1.0f };
	m_ColRectangle = DBG_NEW Rectangle(400, 400, 100, 100, col);
	m_FrameCount = m_BeginFrame;
	for (int i = 0; i < TestRectangles; ++i)
	{
		for (int j = 0; j < TestRectangles; ++j)
		{
			float randNr = (float)rand() / ((float)(RAND_MAX / 1));
			if (randNr < 0.25f)
			{
				m_Rectangles[i * TestRectangles + j] = DBG_NEW Rectangle(100.0f, 100.0f, -400.0f + 200.0f * i, -400.0f + 200.0f * j, "res/textures/BlueBlock.png", 1);
			}
			else if (randNr < 0.50f)
			{
				m_Rectangles[i * TestRectangles + j] = DBG_NEW Rectangle(100.0f, 100.0f, -400.0f + 200.0f * i, -400.0f + 200.0f * j, "res/textures/GreenBlock.png", 2);
			}
			else if (randNr < 0.75f)
			{
				m_Rectangles[i * TestRectangles + j] = DBG_NEW Rectangle(100.0f, 100.0f, -400.0f + 200.0f * i, -400.0f + 200.0f * j, "res/textures/OrangeBlock.png", 3);
			}
			else
			{
				m_Rectangles[i * TestRectangles + j] = DBG_NEW Rectangle(100.0f, 100.0f, -400.0f + 200.0f * i, -400.0f + 200.0f * j, "res/textures/PurpleBlock.png", 4);
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
			m_Rectangles[i * TestRectangles + j]->CleanUp();
			delete m_Rectangles[i *TestRectangles + j];
		}
	}
	
	//delete[] m_Rectangles;
	
	m_Rectangle->CleanUp();
	delete m_Rectangle;
	m_ColRectangle->CleanUp();
	delete m_ColRectangle;

}

void Player::Input(float deltaTime)
{
	m_IsMoving = false;
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_W)) {
		m_PlayerPos.y += deltaTime * 500.0f;
		m_Direction = 1;
		m_IsMoving = true;
	}
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_D)) {
		m_PlayerPos.x += deltaTime * 500.0f;
		m_Direction = 2;
		m_IsMoving = true;
	}
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_S)) {
		m_PlayerPos.y += deltaTime * -500.0f;
		m_Direction = 3;
		m_IsMoving = true;
	}
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_A)) {
		m_PlayerPos.x += deltaTime * -500.0f;
		m_Direction = 4;
		m_IsMoving = true;
	}
	m_pCamera->SetTargetPos(m_PlayerPos);
}

void Player::Update(float deltaTime)
{
	if (m_Direction != m_LastDirection || m_IsMoving != m_WasMoving)
	{
		if (m_IsMoving)
		{
			m_WasMoving = m_IsMoving;
			m_LastDirection = m_Direction;
			if (m_Direction == 1)
			{
				m_BeginFrame = 28;
				m_EndFrame = 35;
			}
			else if (m_Direction == 2)
			{
				m_BeginFrame = 1;
				m_EndFrame = 8;
			}
			else if (m_Direction == 3)
			{
				m_BeginFrame = 10;
				m_EndFrame = 17;
			}
			else if (m_Direction == 4)
			{
				m_BeginFrame = 19;
				m_EndFrame = 26;
			}
		}else
		{
			m_WasMoving = m_IsMoving;
			m_LastDirection = m_Direction;
			if (m_Direction == 1)
			{
				m_BeginFrame = 27;
				m_EndFrame = 27;
			}
			else if (m_Direction == 2)
			{
				m_BeginFrame = 0;
				m_EndFrame = 0;
			}
			else if (m_Direction == 3)
			{
				m_BeginFrame = 9;
				m_EndFrame = 9;
			}
			else if (m_Direction == 4)
			{
				m_BeginFrame = 18;
				m_EndFrame = 18;
			}
		}
	}
	
	m_FrameTimer += deltaTime;
	if (m_FrameTimer >= m_TimeUntilNextFrame)
	{
		m_FrameTimer -= m_TimeUntilNextFrame;
		m_FrameCount++;
	}

	if (m_FrameCount > m_EndFrame)
	{
		m_FrameCount = m_BeginFrame;
	}
	else if (m_FrameCount < m_BeginFrame)
	{
		m_FrameCount = m_BeginFrame;
	}
}

void Player::Render(float deltaTime)
{
	m_ColRectangle->Draw();
	m_Rectangle->SetXPos(m_PlayerPos.x + (float)m_pProgram->GetScreenWidth() / 2.0f);
	m_Rectangle->SetYPos(m_PlayerPos.y + (float)m_pProgram->GetScreenHeight() / 2.0f);
	SpriteSheetFramePicker picker;
	picker.PickFrameHorizontal(9, 4, m_FrameCount, m_Rectangle);
	for (int i = 0; i < TestRectangles; ++i)
	{
		for (int j = 0; j < TestRectangles; ++j)
		{
			m_Rectangles[i * TestRectangles + j]->DrawWithTexture();
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