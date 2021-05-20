#pragma once
#include "StandardObject.h"

class MainMenu final : public StandardObject
{
protected:
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void Input(float deltaTime) override;
	void ImGuiRender(float deltaTime) override;
	void OnDestroy() override;
public:
	MainMenu();
	~MainMenu() override;
};

