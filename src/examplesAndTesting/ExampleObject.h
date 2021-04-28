#pragma once
#include "StandardObject.h"
class ExampleObject : public StandardObject
{
private:
	int m_Counter{ 0 };
	int m_DeathPoint{ 0 };
public:
	ExampleObject(int priority) :StandardObject(priority)
	{
		Start();
	}
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void Destroy() override;
	void Input(double deltaTime) override;
	void Update(double deltaTime) override;
	void Render(double deltaTime) override;
	void ImGuiRender(double deltaTime) override;
	void DebugRender(double deltaTime) override;
};

