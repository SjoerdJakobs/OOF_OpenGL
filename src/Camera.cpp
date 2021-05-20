#include "Camera.h"

Camera::Camera(int priority) :StandardObject(priority),
m_Proj(glm::ortho(0.0f, static_cast<float>(m_pProgram->GetScreenWidth()), 0.0f, static_cast<float>(m_pProgram->GetScreenHeight()), -1.0f, 1.0f))
{
	Start();
}

float Camera::Lerp(float a, float b, float f)
{
	return (a * (1.0f - f)) + (b * f);
}

float Camera::GetDistance(glm::vec2 v1, glm::vec2 v2)
{
	return(sqrtf(powf(fabsf(v1.x - v2.x), 2) + powf(fabsf(v1.y - v2.y), 2)));
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
	m_CurrentDistance = GetDistance(m_TargetPos, m_CameraPos);
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
	m_CameraPos.x = Lerp(m_LastCameraPos.x, m_TargetPos.x, m_LerpValue);
	m_CameraPos.y = Lerp(m_LastCameraPos.y, m_TargetPos.y, m_LerpValue);

	m_View = glm::translate(glm::mat4(1.0f), glm::vec3(-m_CameraPos.x, -m_CameraPos.y, 0));
}

void Camera::ImGuiRender(float deltaTime)
{
}
