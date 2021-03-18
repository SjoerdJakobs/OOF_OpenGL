#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <vector>
#include <list>

#include <iostream>
#include <fstream>
#include <string>
#include <Test.h>
#include <TestClearColor.h>

#include <chrono>
#include "PriorityGroup.h"
#include "Renderer.h"
#include "Shader.h"
#include "tests/TestClearColor.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define ASSERT(x) if(!(x)) __debugbreak();

enum LoopType
{
	input = 0,
	update = 1,
	fixedUpdate = 2,
	render = 3
};

class StandardObject;

class Program
{
protected:
	Program();
    virtual ~Program();
	GLsizei ScreenWidth = 1280;
	GLsizei ScreenHeight = 800;
	

	//all objects will be in this vector regardless of which loops they use, if you change shit in here directly chances are the program will break
	std::vector<std::shared_ptr<StandardObject>> m_pAllStandardObjects{};

private:
	
	void Run();

	const double m_MaxElapsedSeconds{0.1};
	const double m_fixedTimeStep{ 1.0 / 60.0 };

	bool m_runProgram	{ false };	//normal pause, things can be unaffected by this
	std::atomic<bool> atomic_runProgram = m_runProgram;
	bool m_isPaused		{ false };	//true pause, the whole program is effectively stopped
	std::atomic<bool> atomic_isPaused = m_isPaused;
	bool m_isTruePaused	{ false };
	std::atomic<bool> atomic_isTruePaused = m_isTruePaused;

	double m_fixedTimeStepTimer	{ 0.0 };
	double m_deltaTime			{ 0.0 };
	double m_unscaledDeltaTime	{ 0.0 };
	double m_timeScale			{ 1.0 };
	std::atomic<double> atomic_timeScale = m_timeScale;

	//std::unique_ptr<PriorityGroup> pointer1 = std::make_unique<PriorityGroup>(1);
	//all objects that use the input loop placed in priority groups to allow execution orders	
	std::vector<PriorityGroup*> m_pInputObjectGroups;
	std::list <StandardObject*> m_pInputObjectsToBeAdded;
	std::list <StandardObject*> m_pInputObjectsToBeRemoved;
	bool m_shouldAddToInputList{ false };
	bool m_shouldRemoveFromInputList{ false };


	//all objects that use the update loop placed in priority groups to allow execution orders
	std::vector<PriorityGroup*> m_pUpdateObjectGroups;
	std::list <StandardObject*> m_pUpdateObjectsToBeAdded;
	std::list <StandardObject*> m_pUpdateObjectsToBeRemoved;
	bool m_shouldAddToUpdateList { false };
	bool m_shouldRemoveFromUpdateList { false };


	//all objects that use the fixed update loop placed in priority groups to allow execution orders
	std::vector<PriorityGroup*> m_pFixedUpdateObjectGroups;
	std::list <StandardObject*> m_pFixedUpdateObjectsToBeAdded;
	std::list <StandardObject*> m_pFixedUpdateObjectsToBeRemoved;
	bool m_shouldAddToFixedUpdateList { false };
	bool m_shouldRemoveFromFixedUpdateList { false };


	//all objects that use the render loop placed in priority groups to allow execution orders
	std::vector<PriorityGroup*> m_pRenderObjectGroups;
	std::list <StandardObject*> m_pRenderObjectsToBeAdded;
	std::list <StandardObject*> m_pRenderObjectsToBeRemoved;
	bool m_shouldAddToRenderList { false };
	bool m_shouldRemoveFromRenderList { false };

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

	//inline void SetShouldAddToInputList(bool b)			{ m_shouldAddToInputList = b; }
	//inline void SetShouldRemoveFromInputList(bool b)	{ m_shouldRemoveFromInputList = b; }
	//
	//inline void SetShouldAddToUpdateList(bool b)		{ m_shouldAddToUpdateList = b; }
	//inline void SetShouldRemoveFromUpdateList(bool b)	{ m_shouldRemoveFromUpdateList = b; }

	//inline void SetShouldAddToFixedUpdateList(bool b)	{ m_shouldAddToFixedUpdateList = b; }
	//inline void SetShouldRemoveFromFixedUpdateList(bool b) { m_shouldRemoveFromFixedUpdateList = b; }
	//
	//inline void SetShouldAddToRenderList(bool b)		{ m_shouldAddToRenderList = b; }
	//inline void SetShouldRemoveFromRenderList(bool b)	{ m_shouldRemoveFromRenderList = b; }

	void Start();
	void CleanUp();
	void AddToList(StandardObject* p_obj,LoopType type);
	void AddToAllLists(StandardObject* p_obj);
	void RemoveFromList(StandardObject* p_obj,LoopType type);
	void RemoveFromAllLists(StandardObject* p_obj);
};