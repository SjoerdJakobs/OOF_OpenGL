#pragma once
#include "StandardObject.h"
#include "IDamageable.h"
#include "glm/glm.hpp"

class Rectangle;
class Camera;

constexpr int TestRectangles{ 15 };

class Player final : public StandardObject, IDamageable
{
private:

	Camera* m_pCamera;
	Rectangle* m_Rectangle;
	Rectangle* m_ColRectangle;
	Rectangle* m_Rectangles[TestRectangles*TestRectangles];

	float m_Health;
	float m_HealthRegen;

	float m_MovementSpeed;
	float m_SpecialCooldown;

	int m_MaxSpecialsReady;
	int m_SpecialsReady;

	bool m_IsMoving{false};
	bool m_WasMoving{true};
	int m_Direction{ 1 };
	int m_LastDirection{ 0 };
	int m_FrameCount{ 0 };
	int m_BeginFrame{ 0 };
	int m_EndFrame{ 0 };
	float m_TimeUntilNextFrame{ 0.1f };
	float m_FrameTimer{ 0 };

	glm::vec2 m_PlayerPos{ 0,0 };

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
	void DebugRender(float deltaTime) override;
	void TakeDamage(int damage) override;
	void Heal(int healAmount) override;
};
