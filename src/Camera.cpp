#include "Camera.h"

#include "HandyMaths.h"

Camera::Camera(int priority) :StandardObject(priority),
m_Proj(glm::ortho(0.0f, static_cast<float>(m_pProgram->GetScreenWidth()), 0.0f, static_cast<float>(m_pProgram->GetScreenHeight()), -1.0f, 1.0f))
{
	Start();
}

void Camera::Start()
{
}

void Camera::Awake()
{
}

void Camera::Sleep()
{
}

void Camera::OnDestroy()
{
}

void Camera::Input(float deltaTime)
{
}

void Camera::Update(float deltaTime)
{
	if (m_ScreenShakeDuration > 0)
	{
		if (deltaTime > 0)
		{
			m_ScreenShakeDuration -= deltaTime;
			m_CameraPos.x += rand() % 10 + -5;
			m_CameraPos.y += rand() % 10 + -5;
		}
	}

	m_CurrentDistance = HandyMaths::GetDistance(m_TargetPos, m_CameraPos);
	m_LerpRenewTickCounter += deltaTime;

	if (m_LerpRenewTickCounter >= m_LerpRenewTickInterfall)
	{
		m_LerpRenewTickCounter = 0;
		m_LastCameraPos = m_CameraPos;
		m_LerpValue = 0;
	}
	if (m_CurrentDistance > m_MaxDistance)
	{
		m_LerpSpeed = m_MaxLerpSpeed;
	}
	else
	{
		m_LerpSpeed = m_MaxLerpSpeed * (m_CurrentDistance / m_MaxDistance);
		if (m_LerpSpeed < m_MinLerpSpeed)
		{
			m_LerpSpeed = m_MinLerpSpeed;
		}
	}
	m_LerpValue += m_LerpSpeed * deltaTime;
	m_CameraPos.x = HandyMaths::Lerp(m_LastCameraPos.x, m_TargetPos.x, m_LerpValue);
	m_CameraPos.y = HandyMaths::Lerp(m_LastCameraPos.y, m_TargetPos.y, m_LerpValue);

	m_View = glm::translate(glm::mat4(1.0f), glm::vec3(-m_CameraPos.x, -m_CameraPos.y, 0));
}

void Camera::ImGuiRender(float deltaTime)
{
}

void Camera::ScreenShake(float duration)
{
	m_ScreenShakeDuration = duration;
}