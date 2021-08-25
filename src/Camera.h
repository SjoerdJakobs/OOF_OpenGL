#pragma once
#include "Program.h"
#include "StandardObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera final : public StandardObject
{
public:
	static Camera& instance()
	{
		static Camera* p_instance = new Camera(1000);
		return *p_instance;
	}

private:
	// Private Constructor
	Camera(int priority);
	Camera(Camera const&) {}            // copy constructor is private
	Camera& operator=(Camera const&) {} // assignment operator is private

	float m_LerpValue{ 0 };
	float m_LerpSpeed{ 1.0f };
	float m_MaxLerpSpeed{ 9.0f };
	float m_MinLerpSpeed{ 2.5f };
	float m_LerpRenewTickInterfall{ 0 };
	float m_LerpRenewTickCounter{ 0.0666666f };
	float m_MaxDistance{ 500 };
	float m_CurrentDistance{ 0 };

	float m_ScreenShakeDuration{ 0 };

	glm::vec2 m_TargetPos{ 0,0 };
	glm::vec2 m_LastTargetPos{ 0,0 };

	glm::vec2 m_CameraPos{ 0,0 };
	glm::vec2 m_LastCameraPos{ 0,0 };

	glm::mat4 m_View{};
	glm::mat4 m_Proj{};

public:

	void SetTargetPos(glm::vec2 pos) { m_TargetPos = pos + glm::vec2(-m_pProgram->GetScreenWidth() / 2, -m_pProgram->GetScreenHeight() / 2); }

	void Start() override;
	void Awake() override;
	void Sleep() override;
	void OnDestroy() override;
	void Input(float deltaTime) override;
	void Update(float deltaTime) override;
	void ImGuiRender(float deltaTime) override;
	void ScreenShake(float duration);

	glm::vec2 GetCameraPos() const { return m_CameraPos; }

	glm::mat4 GetCameraView() const { return m_View; }
	glm::mat4 GetCameraProj() const { return m_Proj; }
};
