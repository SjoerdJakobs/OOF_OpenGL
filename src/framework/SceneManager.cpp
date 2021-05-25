#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{
	m_pAllScenes = new std::vector<Scene*>();
}

SceneManager::~SceneManager()
{
	for (Scene* scene : *m_pAllScenes)
	{
		delete scene;
	}
	m_pAllScenes->clear();
	m_pAllScenes = nullptr;
	m_pCurrentScene = nullptr;
}

void SceneManager::AddScene(Scene* newScene)const
{
	m_pAllScenes->push_back(newScene);
}

void SceneManager::SwitchToScene(SceneNames sceneName)
{
	m_pCurrentScene->Stop();
	for (Scene* scene : *m_pAllScenes)
	{
		if (scene->m_SceneName == sceneName)
		{
			m_pCurrentScene = scene;
			break;
		}
	}
	m_pCurrentScene->Start();
}

void SceneManager::UpdateScene()const
{
	if (m_pCurrentScene != nullptr)
	{
		if (m_pCurrentScene->m_ObjectsNeedToBeAddedToScene)
		{
			m_pCurrentScene->UpdateAddObjects();
		}
		if (m_pCurrentScene->m_ObjectsNeedToBeRemovedFromScene)
		{
			m_pCurrentScene->UpdateRemoveObjects();
		}
	}
}

void SceneManager::Start()
{
	if (m_pCurrentScene == nullptr)
	{
		if (!m_pAllScenes->empty())
		{
			m_pCurrentScene = m_pAllScenes->front();
			m_pCurrentScene->Start();
		}
	}
	else
	{
		m_pCurrentScene->Start();
	}
}

void SceneManager::Start(SceneNames sceneName)
{
	for (Scene* scene : *m_pAllScenes)
	{
		if (scene->m_SceneName == sceneName)
		{
			m_pCurrentScene = scene;
			m_pCurrentScene->Start();
			break;
		}
	}
}