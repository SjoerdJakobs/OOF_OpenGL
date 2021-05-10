#pragma once
#include "StandardObject.h"

class SceneManager final : public StandardObject
{
public:
	SceneManager() :StandardObject(true, false, true, false, false, false, false,1000,1000,1000,1000)
	{
		Start();
	}
	~SceneManager();
	
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void Destroy() override;
	void Update(double deltaTime) override;
};

