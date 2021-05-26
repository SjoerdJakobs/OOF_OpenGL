#pragma once
// debug_new.cpp
// compile by using: cl /EHsc /W4 /D_DEBUG /MDd debug_new.cpp
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <vector>
#include <list>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "Enums.h"
#include "Renderer.h"
#include "Shader.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

//#define ASSERT(x) if(!(x)) __debugbreak();

class Scene;
class StandardObject;
class ExampleObject;
class PriorityGroup;
class SceneManager;

class Program
{
public:
	//http ://www.yolinux.com/TUTORIALS/C++Singleton.html
	static Program* GetInstance();
	static bool Exists();
	void ProgramStart();
	virtual ~Program();

protected:
	static Program* m_pInstance;

	Program();
	virtual void AddToProgramLoopBegin() = 0;
	virtual void AtProgramStart() = 0;
	virtual void OnProgramEnd() = 0;
	void AddScene(Scene* newScene) const;

	int m_UpdateVectorsResizeStep = 50;

	GLsizei m_ScreenWidth = 1280;
	GLsizei m_ScreenHeight = 800;

	GLFWwindow*   m_pWindow;
	SceneManager* m_pSceneManager;

private:

	void CleanUp();

	void Run();
	void AddStandardObjectsMarkedForAdding();
	void AddToPrioritygroup(LoopType type, unsigned int priorityNr, std::list<StandardObject*> objectsForInsert);

	const float m_MaxElapsedSeconds{ 0.1f };
	const float m_FixedTimeStep{ 1.0f / 60.0f };

	bool m_RunProgram{ false };
	std::atomic<bool> atomic_RunProgram = m_RunProgram;
	bool m_IsPaused{ false };
	std::atomic<bool> atomic_IsPaused = m_IsPaused;
	bool m_IsTruePaused{ false };
	std::atomic<bool> atomic_IsTruePaused = m_IsTruePaused;

	std::vector<StandardObject*> m_Objects;
	std::list <StandardObject*> m_pObjectsToBeAdded;
	bool m_ShouldAddToObjectList{ false };
	bool m_ShouldRemoveFromObjectList{ false };

	int m_ObjectListResizeThreshold{ 50 };

	float m_FixedTimeStepTimer{ 0.0f };
	float m_DeltaTime{ 0.0f };
	float m_UnscaledDeltaTime{ 0.0f };
	float m_TimeScale{ 1.0f };
	std::atomic<float> atomic_TimeScale = m_TimeScale;

	//all objects that use the input loop placed in priority groups to allow execution orders
	std::vector<PriorityGroup*> m_pInputObjectGroups;
	std::list <StandardObject*> m_pInputObjectsToBeAdded;
	bool m_ShouldAddToInputList{ false };
	bool m_ShouldRemoveFromInputList{ false };

	//all objects that use the update loop placed in priority groups to allow execution orders
	std::vector<PriorityGroup*> m_pUpdateObjectGroups;
	std::list <StandardObject*> m_pUpdateObjectsToBeAdded;
	bool m_ShouldAddToUpdateList{ false };
	bool m_ShouldRemoveFromUpdateList{ false };

	//all objects that use the fixed update loop placed in priority groups to allow execution orders
	std::vector<PriorityGroup*> m_pFixedUpdateObjectGroups;
	std::list <StandardObject*> m_pFixedUpdateObjectsToBeAdded;
	bool m_ShouldAddToFixedUpdateList{ false };
	bool m_ShouldRemoveFromFixedUpdateList{ false };

	//all objects that use the render loop placed in priority groups to allow execution orders
	std::vector<PriorityGroup*> m_pRenderObjectGroups;
	std::list <StandardObject*> m_pRenderObjectsToBeAdded;
	bool m_ShouldAddToRenderList{ false };
	bool m_ShouldRemoveFromRenderList{ false };

	//all objects that use the render loop placed in priority groups to allow execution orders
	std::vector<PriorityGroup*> m_pImGuiRenderObjectGroups;
	std::list <StandardObject*> m_pImGuiRenderObjectsToBeAdded;
	bool m_ShouldAddToImGuiRenderList{ false };
	bool m_ShouldRemoveFromImGuiRenderList{ false };

	void RemoveStandardObjectsMarkedForRemove();

public:

	GLFWwindow* GetGLFWwindow() const { return m_pWindow; }

	SceneManager* GetSceneManager() const { return m_pSceneManager; }

	int GetScreenWidth() const { return  m_ScreenWidth; }
	int GetScreenHeight() const { return  m_ScreenHeight; }

	bool GetRunProgram() const { return m_RunProgram; }
	bool IsPaused()		const { return m_IsPaused; }
	bool IsTruePaused()	const { return m_IsTruePaused; }

	void SetRunProgram(bool b) { m_RunProgram = b; atomic_RunProgram = b; }
	void SetPaused(bool b) { m_IsPaused = b; atomic_IsPaused = b; }
	void SetTruePaused(bool b) { m_IsTruePaused = b; atomic_IsTruePaused = b; }

	float GetDeltaTime() const { return m_DeltaTime; }
	float GetTimeScale() const { return m_TimeScale; }
	float GetUnscaledDeltaTime() const { return m_UnscaledDeltaTime; }

	void SetTimeScale(float f) { m_TimeScale = f; atomic_TimeScale = f; }

	void AddToObjectsList(StandardObject* p_obj);
	void RemoveFromObjectsList();

	void AddToList(StandardObject* p_obj, LoopType type);
	void AddToAllLists(StandardObject* p_obj);
	void RemoveFromList(LoopType type);
	void RemoveFromAllLists();
};
