#pragma once
#include "Program.h"
#include "StandardObject.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera : public StandardObject
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

	
	glm::vec2 m_PlayerPos{ 100,100 };
	glm::vec2 m_LastPlayerPos{ 100,100 };
	
	glm::vec2 m_CameraPos{ 0,0 };
	glm::vec2 m_LastCameraPos{ 0,0 };

	glm::mat4 m_View;
	glm::mat4 m_Proj;
	
	float Lerp(float a, float b, float f);
	float GetDistance(glm::vec2 v1, glm::vec2 v2);
public:
	
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void Destroy() override;
	void Input(double deltaTime) override;
	void Update(double deltaTime) override;
	void ImGuiRender(double deltaTime) override;

	glm::mat4 GetCameraView() const { return m_View; }
	glm::mat4 GetCameraProj() const { return m_Proj; }
};
