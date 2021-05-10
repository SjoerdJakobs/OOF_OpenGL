#pragma once
#include <list>
#include <vector>

class StandardObject;

class Scene
{
private:
	bool m_ObjectsNeedToBeAddedToScene{ false };
	std::vector<StandardObject*> m_pStandardObjectsInScene;
	std::list<StandardObject*> m_pObjectsToBeAddedToScene;
	
public:
	
	bool GetIfObjectsNeedToBeAdded() { return m_ObjectsNeedToBeAddedToScene; }
	
	void AddObjectToScene(StandardObject* obj);
	void UpdateObjectContainers();

	virtual void Start();
	virtual void Stop();
};

