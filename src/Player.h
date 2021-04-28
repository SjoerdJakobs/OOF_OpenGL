#pragma once
#include "Rectangle.h"
#include "StandardObject.h"

class Player : public StandardObject
{
private:

	Rectangle m_Rectangle{ 100, 100, 0, 0,"res/textures/LogoOpenGL.png"};
	
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
};

