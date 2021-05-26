#pragma once
#include "StandardObject.h"

class Rectangle;
class Camera;

class ParallaxBackground final :
    public StandardObject
{
	const float m_Layer1BaseSpeed{ 0.0f };
	const float m_Layer1SpeedMod{ 0.3f };
	const float m_Layer2BaseSpeed{ 0.1f };
	const float m_Layer2SpeedMod{ 0.6f };
	const float m_Layer3BaseSpeed{ 0.2f };
	const float m_Layer3SpeedMod{ 1.0f };

	Rectangle* m_Layer1Rectangles[3] = {};
	Rectangle* m_Layer2Rectangles[3] = {};
	Rectangle* m_Layer3Rectangles[3] = {};

	Camera * m_pCamera;

	void SpawnLayers();
	void MoveLayers();

protected:
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void OnDestroy() override;
	void Update(float deltaTime) override;
	void Render(float deltaTime) override;
public:
	~ParallaxBackground() override;
};

