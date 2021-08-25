#include "ObjectsStressTestScene.h"

#include "AllocationMetrics.h"
#include "ExampleObject.h"

void ObjectsStressTestScene::OnStart()
{
	PrintMemoryUsage("before ObjectsStressTestScene start");
	for (int i = 0; i < 1000; ++i)
	{
		AddObjectToScene(static_cast<StandardObject*>(new ExampleObject((rand() % 2000) + 1000)));
	}

	PrintMemoryUsage("after ObjectsStressTestScene start");
}

void ObjectsStressTestScene::OnStop()
{
}

ObjectsStressTestScene::ObjectsStressTestScene()
{
	m_SceneName = SceneNames::ObjectTestScene;
}

ObjectsStressTestScene::~ObjectsStressTestScene()
{
	PrintMemoryUsage("on ObjectsStressTestScene destructor");
}