#include "SceneManager.h"

#include "Program.h"
#include "Scene.h"

SceneManager::SceneManager()
{
	m_AllScenes = std::vector<Scene*>();
}

SceneManager::~SceneManager()
{
	for (Scene* scene : m_AllScenes)
	{
		delete scene;
	}
	m_AllScenes.clear();
	m_pCurrentScene = nullptr;
}

void SceneManager::AddScene(Scene* newScene)
{
	m_AllScenes.push_back(newScene);
}

void SceneManager::SwitchToScene(SceneNames sceneName)
{
	m_pCurrentScene->Stop();
	for (Scene* scene : m_AllScenes)
	{
		if (scene->m_SceneName == sceneName)
		{
			m_pCurrentScene = scene;
			break;
		}
	}

	Program::GetInstance()->SetShouldCleanUpGroups(true);
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

void SceneManager::CleanUp()
{
	for (unsigned int i = 0; i < m_AllScenes.size(); i++)
	{
		m_AllScenes[i]->Stop();
		delete m_AllScenes[i];
	}
	m_AllScenes.clear();
}

void SceneManager::Start()
{
	if (m_pCurrentScene == nullptr)
	{
		if (!m_AllScenes.empty())
		{
			m_pCurrentScene = m_AllScenes.front();
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
	for (Scene* scene : m_AllScenes)
	{
		if (scene->m_SceneName == sceneName)
		{
			m_pCurrentScene = scene;
			m_pCurrentScene->Start();
			break;
		}
	}
}