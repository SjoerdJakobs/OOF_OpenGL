#pragma once
#include <vector>

#include "Enums.h"
#include "StandardObject.h"

class Scene;

class SceneManager final
{
	std::vector<Scene*>* m_pAllScenes;
	Scene* m_pCurrentScene = nullptr;
	
	SceneManager();
	~SceneManager();
	friend class Program;
	friend void StandardObject::Destroy();

	void UpdateScene()const;
public:
	void Start();
	void Start(SceneNames sceneName);
	void AddScene(Scene* newScene)const;
	void SwitchToScene(const SceneNames sceneName);
	
};

