#pragma once
#include "IDamageable.h"
#include "StandardObject.h"
#include "glm/glm.hpp"

class Rectangle;
class Camera;

constexpr int TestRectangles{10};

class Player final : public StandardObject , IDamageable
{
private:

	Camera* m_Camera;
	Rectangle* m_Rectangle;
	Rectangle* m_ColRectangle;
	Rectangle* m_Rectangles[TestRectangles][TestRectangles];
	
	float m_Health;
	float m_HealthRegen;

	float m_MovementSpeed;

	float m_SpecialCooldown;

	int m_MaxSpecialsReady;
	int m_SpecialsReady;

	int m_FrameCount{0};
	int m_BeginFrame {0};
	int m_EndFrame{8};
	float m_TimeUntilNextFrame{0.1f};
	float m_FrameTimer{0};

	glm::vec2 m_PlayerPos{ 0,0 };

public:

	Player(int priority) :StandardObject(priority)
	{
		Start();
	}
	~Player();
	
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void Destroy() override;
	void Input (double deltaTime) override;
	void Update(double deltaTime) override;
	void Render(double deltaTime) override;
	void ImGuiRender(double deltaTime) override;
	void DebugRender(double deltaTime) override;
	void TakeDamage(int damage) override;
	void Heal(int healAmount) override;
};

