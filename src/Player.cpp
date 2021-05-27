#include "Player.h"

#include "Program.h"
#include "Camera.h"
#include "Rectangle.h"
#include "SpriteSheetFramePicker.h"
#include <GLFW/glfw3.h>

#include "SceneManager.h"

Player::Player(int priority) : StandardObject(priority), m_pCamera(nullptr), m_pPlayerRectangle(nullptr)
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
	m_pPlayerRectangle = DBG_NEW Rectangle(100, 100, m_PlayerPos.x, m_PlayerPos.y, "res/textures/professor_walk_cycle_no_hat.png", 0);
	m_FrameCount = m_BeginFrame;

	m_WindowFlags |= ImGuiWindowFlags_NoTitleBar;
	m_WindowFlags |= ImGuiWindowFlags_NoScrollbar;
	m_WindowFlags |= ImGuiWindowFlags_NoMove;
	m_WindowFlags |= ImGuiWindowFlags_NoResize;
	m_WindowFlags |= ImGuiWindowFlags_NoCollapse;
	m_WindowFlags |= ImGuiWindowFlags_NoNav;
	m_WindowFlags |= ImGuiWindowFlags_NoBackground;
	m_WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void Player::Awake()
{
}

void Player::Sleep()
{
}

void Player::OnDestroy()
{
	m_pPlayerRectangle->CleanUp();
	delete m_pPlayerRectangle;
}

void Player::Input(float deltaTime)
{
	m_IsMoving = false;
	m_MovementBoost = 0;
	m_TimeUntilNextFrameSpeedUp = 0;
	
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_LEFT_SHIFT) || GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_RIGHT_SHIFT)) {
		m_MovementBoost = 300;
		m_TimeUntilNextFrameSpeedUp = 0.05f;
	}
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_W)|| GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_UP)) {
		m_PlayerPos.y += deltaTime * (m_MovementSpeed+m_MovementBoost);
		m_Direction = 1;
		m_IsMoving = true;
	}
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_D) || GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_RIGHT)) {
		m_PlayerPos.x += deltaTime * (m_MovementSpeed + m_MovementBoost);
		m_Direction = 2;
		m_IsMoving = true;
	}
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_S) || GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_DOWN)) {
		m_PlayerPos.y += deltaTime * -(m_MovementSpeed + m_MovementBoost);
		m_Direction = 3;
		m_IsMoving = true;
	}
	if (GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_A) || GLFW_PRESS == glfwGetKey(m_pProgram->GetGLFWwindow(), GLFW_KEY_LEFT)) {
		m_PlayerPos.x += deltaTime * -(m_MovementSpeed + m_MovementBoost);
		m_Direction = 4;
		m_IsMoving = true;
	}
}

void Player::Update(float deltaTime)
{
	if ((m_Direction != m_LastDirection && deltaTime > 0) || (m_IsMoving != m_WasMoving&&deltaTime > 0))
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
	if (m_FrameTimer >= m_TimeUntilNextFrame - m_TimeUntilNextFrameSpeedUp)
	{
		m_FrameTimer -= m_TimeUntilNextFrame - m_TimeUntilNextFrameSpeedUp;
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


	if (m_CameraTarget.x - m_PlayerPos.x < -m_MoveCameraDistanceThreshold)
	{
		m_CameraTarget.x = m_PlayerPos.x - m_MoveCameraDistanceThreshold;
	}
	else if (m_CameraTarget.x - m_PlayerPos.x > m_MoveCameraDistanceThreshold)
	{
		m_CameraTarget.x = m_PlayerPos.x + m_MoveCameraDistanceThreshold;
	}

	if (m_CameraTarget.y - m_PlayerPos.y < -m_MoveCameraDistanceThreshold)
	{
		m_CameraTarget.y = m_PlayerPos.y - m_MoveCameraDistanceThreshold;
	}
	else if (m_CameraTarget.y - m_PlayerPos.y > m_MoveCameraDistanceThreshold)
	{
		m_CameraTarget.y = m_PlayerPos.y + m_MoveCameraDistanceThreshold;
	}

	m_pCamera->SetTargetPos(m_CameraTarget+m_CameraTargetOfset);
	
}

void Player::Render(float deltaTime)
{
	m_pPlayerRectangle->SetXPos(m_PlayerPos.x);// + (float)m_pProgram->GetScreenWidth() / 2.0f);
	m_pPlayerRectangle->SetYPos(m_PlayerPos.y);// + (float)m_pProgram->GetScreenHeight() / 2.0f);
	SpriteSheetFramePicker picker;
	picker.PickFrameHorizontalDownUp(9, 4, m_FrameCount, m_pPlayerRectangle);
	
}

void Player::ImGuiRender(float deltaTime)
{
	ImGui::PushFont(m_pMenuFont);
	ImGui::SetNextWindowPos(ImVec2(920, 20), ImGuiCond_Once);
	ImGui::Begin("scoreText",nullptr,m_WindowFlags);
	ImGui::Text("Score: %.0f", static_cast<float>(m_Score));
	ImGui::End();
	ImGui::PopFont();

}