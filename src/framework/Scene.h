#pragma once
#include <list>
#include <vector>
#include "Enums.h"

class StandardObject;

class Scene
{
private:
	unsigned int m_Id = reinterpret_cast<unsigned int>(this);
	
	bool m_ObjectsNeedToBeAddedToScene{ false };
	bool m_ObjectsNeedToBeRemovedFromScene{ false };
	
	std::list<StandardObject*>	m_pStandardObjectsInScene;
	std::list<StandardObject*>	m_pObjectsToBeAddedToScene;
	std::list<StandardObject*>	m_pObjectsToBeRemovedFromScene;
	
	bool GetIfObjectsNeedToBeAdded() const {	return m_ObjectsNeedToBeAddedToScene; }
	void UpdateAddObjects();
	void UpdateRemoveObjects();
	void Start();
	void Stop();

protected:
	virtual void OnStart();
	virtual void OnStop();
	SceneNames m_SceneName;

public:
	virtual ~Scene() = default;
	friend class SceneManager;	
	void AddObjectToScene(StandardObject* p_obj);
	void RemoveObjectFromScene(StandardObject* p_obj);

};

