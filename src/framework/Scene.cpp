#include "Scene.h"
#include "StandardObject.h"

void Scene::AddObjectToScene(StandardObject* p_obj)
{
	p_obj->m_IsInAScene = true;
	m_pObjectsToBeAddedToScene.push_back(p_obj);
	m_ObjectsNeedToBeAddedToScene = true;
}

void Scene::RemoveObjectFromScene(StandardObject* p_obj)
{
	m_ObjectsNeedToBeRemovedFromScene = true;
	m_pObjectsToBeRemovedFromScene.push_back(p_obj);
}

void Scene::UpdateAddObjects()
{
	m_pStandardObjectsInScene.insert(m_pStandardObjectsInScene.end(), m_pObjectsToBeAddedToScene.begin(), m_pObjectsToBeAddedToScene.end());
	m_pObjectsToBeAddedToScene.clear();
	m_ObjectsNeedToBeAddedToScene = false;
}

void Scene::UpdateRemoveObjects()
{
	for (StandardObject* p_obj : m_pObjectsToBeRemovedFromScene)
	{
		m_pStandardObjectsInScene.remove(p_obj);
	}
	m_pObjectsToBeRemovedFromScene.clear();
	m_ObjectsNeedToBeRemovedFromScene = false;
}

void Scene::Start()
{
	this->OnStart();
}

void Scene::Stop()
{
	OnStop();
	for (StandardObject* obj : m_pStandardObjectsInScene)
	{
		if (!obj->IsPersistentObject())
		{
			obj->m_IsInAScene = false;
			obj->Destroy();
		}
	}
	m_pStandardObjectsInScene.clear();
}

void Scene::OnStart()
{
}

void Scene::OnStop()
{
}