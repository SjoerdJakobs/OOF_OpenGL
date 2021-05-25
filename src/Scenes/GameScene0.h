#pragma once
#include "Scene.h"

class Player;

class GameScene0 final : public Scene
{
protected:
	void OnStart() override;
	void OnStop() override;
public:
	GameScene0();
	~GameScene0() override;
};
