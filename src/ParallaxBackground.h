#pragma once
#include "StandardObject.h"
#include "glm/glm.hpp"

class Rectangle;
class Camera;

class ParallaxBackground final :
    public StandardObject
{
	const float m_Layer1BaseSpeed{ 1.0f };
	const float m_Layer1SpeedMod{ 0.3f };
	const float m_Layer2BaseSpeed{ 15.0f };
	const float m_Layer2SpeedMod{ 1.2f };
	const float m_Layer3BaseSpeed{ 5.0f };
	const float m_Layer3SpeedMod{ 0.8f };

	Rectangle* m_Layer1Rectangles[4] = {};
	Rectangle* m_Layer2Rectangles[4] = {};
	Rectangle* m_Layer3Rectangles[4] = {};

	Camera * m_pCamera;
	glm::vec2 m_LastCameraPos;

public:
	ParallaxBackground();
	~ParallaxBackground() override;
private:
	void SpawnLayers();
	void MoveLayers(float deltaTime);
	void MoveLayer1(glm::vec2 moveAmount, float deltaTime);
	void MoveLayer2(glm::vec2 moveAmount, float deltaTime);
	void MoveLayer3(glm::vec2 moveAmount, float deltaTime);
protected:
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void OnDestroy() override;
	void Update(float deltaTime) override;
	void Render(float deltaTime) override;
	void ImGuiRender(float deltaTime) override;
};

