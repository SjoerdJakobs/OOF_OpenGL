#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <vector>
#include <list>

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "Renderer.h"
#include "Shader.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define ASSERT(x) if(!(x)) __debugbreak();

enum class LoopType
{
	input = 0,
	update = 1,
	fixedUpdate = 2,
	render = 3,
	imGuiRender = 4,
	debugRender = 5
};

class StandardObject;
class PriorityGroup;

bool ShouldDestructStandardObject(const StandardObject* object);
bool ShouldRemoveStandardObjectFromLoop(StandardObject* object);

class Program
{
protected:
	Program();
    virtual ~Program();
	
	GLsizei ScreenWidth = 1280;
	GLsizei ScreenHeight = 800;

private:
	static Program* instance;
	//threadsave singleton from https://refactoring.guru/design-patterns/singleton/cpp/example#example-1 ?
	
	void Run();

	const double m_MaxElapsedSeconds{0.1};
	const double m_fixedTimeStep{ 1.0 / 60.0 };

	bool m_runProgram	{ false };	//normal pause, things can be unaffected by this
	std::atomic<bool> atomic_runProgram = m_runProgram;
	bool m_isPaused		{ false };	//true pause, the whole program is effectively stopped
	std::atomic<bool> atomic_isPaused = m_isPaused;
	bool m_isTruePaused	{ false };
	std::atomic<bool> atomic_isTruePaused = m_isTruePaused;


	std::vector<StandardObject*> m_objects{};

	double m_fixedTimeStepTimer	{ 0.0 };
	double m_deltaTime			{ 0.0 };
	double m_unscaledDeltaTime	{ 0.0 };
	double m_timeScale			{ 1.0 };
	std::atomic<double> atomic_timeScale = m_timeScale;

	
	//all objects that use the input loop placed in priority groups to allow execution orders	
	std::vector<PriorityGroup*> m_pInputObjectGroups;
	std::list <StandardObject*> m_pInputObjectsToBeAdded;
	bool m_shouldAddToInputList{ false };
	bool m_shouldRemoveFromInputList{ false };


	//all objects that use the update loop placed in priority groups to allow execution orders
	std::vector<PriorityGroup*> m_pUpdateObjectGroups;
	std::list <StandardObject*> m_pUpdateObjectsToBeAdded;
	bool m_shouldAddToUpdateList { false };
	bool m_shouldRemoveFromUpdateList { false };


	//all objects that use the fixed update loop placed in priority groups to allow execution orders
	std::vector<PriorityGroup*> m_pFixedUpdateObjectGroups;
	std::list <StandardObject*> m_pFixedUpdateObjectsToBeAdded;
	bool m_shouldAddToFixedUpdateList { false };
	bool m_shouldRemoveFromFixedUpdateList { false };


	//all objects that use the render loop placed in priority groups to allow execution orders
	std::vector<PriorityGroup*> m_pRenderObjectGroups;
	std::list <StandardObject*> m_pRenderObjectsToBeAdded;
	bool m_shouldAddToRenderList { false };
	bool m_shouldRemoveFromRenderList { false };

	//all objects that use the render loop placed in priority groups to allow execution orders
	std::vector<PriorityGroup*> m_pImGuiRenderObjectGroups;
	std::list <StandardObject*> m_pImGuiRenderObjectsToBeAdded;
	bool m_shouldAddToImGuiRenderList{ false };
	bool m_shouldRemoveFromImGuiRenderList{ false };

public:

	
	inline bool GetRunProgram() const { return m_runProgram; }
	inline bool IsPaused()		const { return m_isPaused; }
	inline bool IsTruePaused()	const { return m_isTruePaused; }
	
	inline void SetRunProgram	(bool b){ m_runProgram = b; atomic_runProgram = b; }
	inline void SetPaused		(bool b){ m_isPaused = b; atomic_isPaused = b; }
	inline void SetTruePaused	(bool b){ m_isTruePaused = b; atomic_isTruePaused = b; }
	
	inline double GetDeltaTime() const { return m_deltaTime; }
	inline double GetTimeScale() const { return m_timeScale; }
	inline double GetUnscaledDeltaTime() const { return m_unscaledDeltaTime; }
	
	inline void SetTimeScale(float f) { m_timeScale = f; atomic_timeScale = f; }

	void Start();
	void CleanUp();
	void AddToList(StandardObject* p_obj,LoopType type);
	void AddToAllLists(StandardObject* p_obj);
	void RemoveFromList(StandardObject* p_obj,LoopType type);
	void RemoveFromAllLists(StandardObject* p_obj);
};

static Program* p_Instance;
static Program* GetInstance()
{
	return p_Instance;
}