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
	void OnDestroy() override;
	void Input(float deltaTime) override;
	void Update(float deltaTime) override;
	void Render(float deltaTime) override;
	void ImGuiRender(float deltaTime) override;
	void DebugRender(float deltaTime) override;
};

