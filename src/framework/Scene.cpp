#include "Scene.h"
#include "StandardObject.h"

void Scene::AddObjectToScene(StandardObject* p_obj)
{
	m_pObjectsToBeAddedToScene.push_back(p_obj);
}

void Scene::UpdateObjectContainers()
{
	m_pStandardObjectsInScene.insert(m_pStandardObjectsInScene.end(), m_pObjectsToBeAddedToScene.begin(), m_pObjectsToBeAddedToScene.end());
	m_pStandardObjectsInScene.clear();
	m_ObjectsNeedToBeAddedToScene = false;
}

void Scene::Stop()
{
	for (StandardObject* obj : m_pStandardObjectsInScene)
	{
		if(!obj->IsPersistentObject())
		{
			obj->Destroy();
		}
		m_pStandardObjectsInScene.clear();
	}
}
