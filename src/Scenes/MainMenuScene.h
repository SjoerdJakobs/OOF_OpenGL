#pragma once
#include "Scene.h"

class MainMenu;

class MainMenuScene final : public Scene
{
private:
	void OnStart() override;
	void OnStop() override;
public:

	MainMenuScene();
	~MainMenuScene() override;
};