#pragma once
#include "Scene.h"

class ObjectsStressTestScene final : public Scene
{
private:
	void OnStart() override;
	void OnStop() override;
public:

	ObjectsStressTestScene();
	~ObjectsStressTestScene() override;
};

