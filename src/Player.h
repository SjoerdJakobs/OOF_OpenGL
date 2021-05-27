#pragma once
#include "StandardObject.h"
#include "IDamageable.h"
#include "glm/glm.hpp"
#include "imgui/imgui.h"

class Rectangle;
class Camera;

constexpr int TestRectangles{ 15 };

class Player final : public StandardObject, IDamageable
{
private:

	ImGuiIO& m_rIO = ImGui::GetIO();
	ImFont* m_pMenuFont = m_rIO.Fonts->Fonts[1];
	ImGuiWindowFlags m_WindowFlags = 0;
	Camera* m_pCamera;
	Rectangle* m_pPlayerRectangle;

	void ChooseRightAnimationFrame();

	float m_Health{5};
	float m_HealthRegen{0};

	float m_MovementSpeed{300};
	float m_MovementBoost{300};
	float m_SpecialCooldown{4};
	int m_Score{ 0 };
	int m_MaxSpecialsReady{1};
	int m_SpecialsReady{1};

	bool m_IsMoving{false};
	bool m_WasMoving{true};
	int m_Direction{ 1 };
	int m_LastDirection{ 0 };
	int m_FrameCount{ 0 };
	int m_BeginFrame{ 0 };
	int m_EndFrame{ 0 };
	float m_TimeUntilNextFrame{ 0.08f };
	float m_TimeUntilNextFrameSpeedUp{ 0.05f };
	float m_FrameTimer{ 0 };

	float m_MoveCameraDistanceThreshold{ 100 };//the size of the box in which the player can walk with out moving the camera

	glm::vec2 m_PlayerPos{ 0,0 };
	glm::vec2 m_CameraTarget{ 0,0 };
	glm::vec2 m_CameraTargetOfset{ 0,70 };

public:

	Player(int priority);
	~Player() override;

	void Start() override;
	void Awake() override;
	void Sleep() override;
	void OnDestroy() override;

	void Input(float deltaTime) override;
	void Update(float deltaTime) override;
	void Render(float deltaTime) override;
	void ImGuiRender(float deltaTime) override;
	void TakeDamage(int damage) override;
	void Heal(int healAmount) override;

	int GetScore() { return m_Score; };
	void SetScore(int newScore) { m_Score = newScore; }
	
	glm::vec2 GetPlayerPos() { return m_PlayerPos; }
	void SetPlayerPos(glm::vec2 newPos) { m_PlayerPos = newPos; }
};
