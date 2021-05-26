#pragma once
#include <vector>
#include "Enums.h"
#include "StandardObject.h"

class Scene;

class SceneManager final
{
	std::vector<Scene*> m_AllScenes;
	Scene* m_pCurrentScene = nullptr;

	SceneManager();
	~SceneManager();
	friend class Program;
	friend void StandardObject::Destroy();

	void UpdateScene()const;
public:
	void CleanUp();
	void Start();
	void Start(SceneNames sceneName);
	void AddScene(Scene* newScene);
	void SwitchToScene(SceneNames sceneName);
};
