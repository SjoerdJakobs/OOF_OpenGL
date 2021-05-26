#pragma once
#include "StandardObject.h"
class LevelManager final : public StandardObject
{
protected:
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void OnDestroy() override;
	void Update(float deltaTime) override;
	void Render(float deltaTime) override;
public:
	~LevelManager() override;
protected:
};

