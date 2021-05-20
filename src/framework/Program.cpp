#include "Program.h"
#include "StandardObject.h"
#include "PriorityGroup.h"
#include "SceneManager.h"


bool ShouldDestructStandardObject(StandardObject * object)
{
	if (object->GetShouldDestruct())
	{
		object->OnDestroy();
		delete object;
		return true;
	}
	return false;
}

bool ShouldRemoveStandardObjectFromInputLoop(const StandardObject* object)
{
	return !object->GetUsesInput();
}
bool ShouldRemoveStandardObjectFromUpdateLoop(const StandardObject* object)
{
	return !object->GetUsesUpdate();
}
bool ShouldRemoveStandardObjectFromFixedUpdateLoop(const StandardObject* object)
{
	return !object->GetUsesFixedUpdate();
}
bool ShouldRemoveStandardObjectFromRenderLoop(const StandardObject* object)
{
	return !object->GetUsesRenderer();
}
bool ShouldRemoveStandardObjectFromImGuiLoop(const StandardObject* object)
{
	return !object->GetUsesImGui();
}
bool ShouldRemoveStandardObjectFromDebugRenderLoop(const StandardObject* object)
{
	return !object->GetUsesRenderer();
}

Program::~Program() = default;

Program* Program::m_pInstance = 0;

Program* Program::GetInstance()
{
	if (m_pInstance == 0)
	{
		std::cout << "Class has not been created" << std::endl;
	}
	return m_pInstance;
}

bool Program::Exists()
{
	return (m_pInstance != nullptr);
}

Program::Program() = default;


static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void glfw_window_size_callback(GLFWwindow* m_pWindow, int width, int height) {
	//m_ScreenWidth = width;
	//m_ScreenHeight = height;
	/* update any perspective matrices used here */
}

void Program::Run()
{
	

	glfwSetErrorCallback(glfw_error_callback);
	/* Initialize the library */
	if (!glfwInit())
	{
		ASSERT(false);
		m_RunProgram = false;
	}
	
	const char* glsl_version = "#version 460";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS);
	const float InitialScreenWidth = static_cast<float>(m_ScreenWidth);
	const float InitialScreenHeight = static_cast<float>(m_ScreenHeight);

	/* Create a windowed mode m_pWindow and its OpenGL context */
	m_pWindow = glfwCreateWindow(static_cast<int>(InitialScreenWidth), static_cast<int>(InitialScreenHeight), "Hello World", NULL, NULL);
	if (!m_pWindow)
	{
		glfwTerminate();
		ASSERT(false);
		m_RunProgram = false;
	}

	/* Make the m_pWindow's context current */
	glfwMakeContextCurrent(m_pWindow);

	glfwSwapInterval(1);//vsync

	glfwSetWindowSizeCallback(m_pWindow, glfw_window_size_callback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR, glewInit() != GLEW_OK" << std::endl;
	}
	else
	{
		std::cout << glGetString(GL_VERSION) << std::endl;
	}
	
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		Renderer renderer;

		m_pSceneManager = new SceneManager();
		
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiWindowFlags_NoMove;				// Prevent m_pWindow movement
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
				
		io.ConfigFlags |= ImGuiWindowFlags_NoMove;

		this->AtProgramStart();
		
		// Set start time
		std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
		while (!glfwWindowShouldClose(m_pWindow)&&m_RunProgram)
		{
			// Get current time
			std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
			// Calculate elapsed time
			m_UnscaledDeltaTime = std::chrono::duration<float>(t2 - t1).count();
			// Update current time
			t1 = t2;
			// Prevent jumps in time caused by break points
			m_UnscaledDeltaTime = std::min(m_UnscaledDeltaTime, m_MaxElapsedSeconds);
			m_DeltaTime = m_UnscaledDeltaTime * m_TimeScale;

			//m_FixedTimeStepTimer += m_UnscaledDeltaTime;
			//if (m_FixedTimeStepTimer >= m_FixedTimeStep)
			//{
			//	//fixed update
			//	m_FixedTimeStepTimer -= m_FixedTimeStep;
			//}
			//std::cout << m_DeltaTime << std::endl;

			glViewport(0, 0, m_ScreenWidth, m_ScreenHeight);
			renderer.Clear();
			GLCall(glClearColor(0, 0, 0, 1));
			

			/* Poll for and process events */
			GLCall(glfwPollEvents());

			this->AddToProgramLoopBegin();

			if (!IsTruePaused())
			{
				for (PriorityGroup* p_group : m_pInputObjectGroups)
				{
					for (StandardObject* p_obj : p_group->standardObjects) {
						if(!IsPaused() || p_obj->IsPauseImmune())
						{
							p_obj->Input(m_UnscaledDeltaTime);
						}
					}
				}
			}

			if (!IsTruePaused())
			{
				for (PriorityGroup* p_group : m_pUpdateObjectGroups)
				{
					for (StandardObject* p_obj : p_group->standardObjects) {
						if (!IsPaused() || p_obj->IsPauseImmune())
						{
							p_obj->Update(m_DeltaTime);
						}
					}
				}
			}

			if (!IsTruePaused())
			{
				for (PriorityGroup* p_group : m_pRenderObjectGroups)
				{
					for (StandardObject* p_obj : p_group->standardObjects) {
						if (!IsPaused() || p_obj->IsPauseImmune())
						{
							p_obj->Render(m_DeltaTime);
						}
					}
				}
			}

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (!IsTruePaused())
			{
				for (PriorityGroup* p_group : m_pImGuiRenderObjectGroups)
				{
					for (StandardObject* p_obj : p_group->standardObjects) {
						if (!IsPaused() || p_obj->IsPauseImmune())
						{
							p_obj->ImGuiRender(m_UnscaledDeltaTime);
						}
					}
				}
			}

			//activate and deactivate objects
			for (StandardObject* p_obj : m_Objects) {
				if (p_obj->IsShouldBeActive() && !p_obj->IsActiveState()) {
					p_obj->AddToLists();
					p_obj->SetActiveState(true);
					p_obj->Awake();
				}
				else if (!p_obj->IsShouldBeActive() && p_obj->IsActiveState()) {
					p_obj->RemoveFromLists();
					p_obj->SetActiveState(false);
					p_obj->Sleep();
				}
			}

			AddStandardObjectsMarkedForAdding();
			RemoveStandardObjectsMarkedForRemove();
			m_pSceneManager->UpdateScene();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			GLCall(glfwSwapBuffers(m_pWindow));

			if (GLFW_PRESS == glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE)) {
				glfwSetWindowShouldClose(m_pWindow, 1);
			}
		}
	}

	delete m_pSceneManager;
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
	exit(EXIT_SUCCESS);	
}

void Program::AddStandardObjectsMarkedForAdding()
{
	if(m_ShouldAddToObjectList)
	{
		if(static_cast<int>(m_Objects.capacity())-(static_cast<int>(m_Objects.size())+ static_cast<int>(m_pObjectsToBeAdded.size()))<0)
		{
			m_Objects.reserve(m_Objects.size() + m_pObjectsToBeAdded.size() + m_ObjectListResizeThreshold);
		}
		m_Objects.insert(m_Objects.end(), m_pObjectsToBeAdded.begin(), m_pObjectsToBeAdded.end());
		m_pObjectsToBeAdded.clear();
		m_ShouldAddToObjectList = false;
	}
	
	if (m_ShouldAddToInputList)
	{
		//sort list with lambda
		m_pInputObjectsToBeAdded.sort([](StandardObject* p_obj1, StandardObject* p_obj2)
			{
				return p_obj1->GetInputPriority() < p_obj2->GetInputPriority();
			});
		
		unsigned int lastPriorityNr = m_pInputObjectsToBeAdded.front()->GetInputPriority();
		std::list<StandardObject*>::iterator i = m_pInputObjectsToBeAdded.begin();
		std::list<StandardObject*>objectsForInsert = std::list<StandardObject*>();
		const int listSize = m_pInputObjectsToBeAdded.size();
		for (int i = 0; i < listSize; ++i)
		{
			StandardObject* currentObj = m_pInputObjectsToBeAdded.front();
			if (currentObj->GetInputPriority() > lastPriorityNr)
			{
				AddToPrioritygroup(LoopType::input, lastPriorityNr, objectsForInsert);
				lastPriorityNr = currentObj->GetInputPriority();
				objectsForInsert.clear();
			}
			objectsForInsert.push_back(currentObj);
			m_pInputObjectsToBeAdded.pop_front();
		}
		AddToPrioritygroup(LoopType::input, lastPriorityNr, objectsForInsert);
		objectsForInsert.clear();
		m_ShouldAddToInputList = false;
		m_pInputObjectsToBeAdded.clear();
	}

	
	if (m_ShouldAddToUpdateList)
	{
		//sort list with lambda
		m_pUpdateObjectsToBeAdded.sort([](const StandardObject* p_obj1,const StandardObject* p_obj2)
			{
				return p_obj1->GetUpdatePriority() < p_obj2->GetUpdatePriority();
			});

		unsigned int lastPriorityNr = m_pUpdateObjectsToBeAdded.front()->GetUpdatePriority();
		std::list<StandardObject*>::iterator i = m_pUpdateObjectsToBeAdded.begin();
		std::list<StandardObject*>objectsForInsert = std::list<StandardObject*>();
		const int listSize = m_pUpdateObjectsToBeAdded.size();
		for (int i = 0; i < listSize; ++i)
		{
			StandardObject* currentObj = m_pUpdateObjectsToBeAdded.front();
			if (currentObj->GetUpdatePriority() > lastPriorityNr)
			{
				AddToPrioritygroup(LoopType::update, lastPriorityNr, objectsForInsert);
				lastPriorityNr = currentObj->GetInputPriority();
				objectsForInsert.clear();
			}
			objectsForInsert.push_back(currentObj);
			m_pUpdateObjectsToBeAdded.pop_front();
		}
		AddToPrioritygroup(LoopType::update, lastPriorityNr, objectsForInsert);
		objectsForInsert.clear();
		m_ShouldAddToUpdateList = false;
		m_pUpdateObjectsToBeAdded.clear();
	}

	if (m_ShouldAddToFixedUpdateList)
	{
		//sort list with lambda
		m_pFixedUpdateObjectsToBeAdded.sort([](const StandardObject* p_obj1, const StandardObject* p_obj2)
			{
				return p_obj1->GetFixedUpdatePriority() < p_obj2->GetFixedUpdatePriority();
			});

		unsigned int lastPriorityNr = m_pFixedUpdateObjectsToBeAdded.front()->GetUpdatePriority();
		std::list<StandardObject*>::iterator i = m_pFixedUpdateObjectsToBeAdded.begin();
		std::list<StandardObject*>objectsForInsert = std::list<StandardObject*>();
		const int listSize = m_pFixedUpdateObjectsToBeAdded.size();
		for (int i = 0; i < listSize; ++i)
		{
			StandardObject* currentObj = m_pFixedUpdateObjectsToBeAdded.front();
			if (currentObj->GetFixedUpdatePriority() > lastPriorityNr)
			{
				AddToPrioritygroup(LoopType::fixedUpdate, lastPriorityNr, objectsForInsert);
				lastPriorityNr = currentObj->GetInputPriority();
				objectsForInsert.clear();
			}
			objectsForInsert.push_back(currentObj);
			m_pFixedUpdateObjectsToBeAdded.pop_front();
		}
		AddToPrioritygroup(LoopType::fixedUpdate, lastPriorityNr, objectsForInsert);
		objectsForInsert.clear();
		m_ShouldAddToFixedUpdateList = false;
		m_pFixedUpdateObjectsToBeAdded.clear();
	}

	if (m_ShouldAddToRenderList)
	{
		//sort list with lambda
		m_pRenderObjectsToBeAdded.sort([](const StandardObject* p_obj1, const StandardObject* p_obj2)
			{
				return p_obj1->GetRenderPriority() < p_obj2->GetRenderPriority();
			});

		unsigned int lastPriorityNr = m_pRenderObjectsToBeAdded.front()->GetRenderPriority();
		std::list<StandardObject*>::iterator i = m_pRenderObjectsToBeAdded.begin();
		std::list<StandardObject*>objectsForInsert = std::list<StandardObject*>();
		const int listSize = m_pRenderObjectsToBeAdded.size();
		for (int i = 0; i < listSize; ++i)
		{
			StandardObject* currentObj = m_pRenderObjectsToBeAdded.front();
			if (currentObj->GetRenderPriority() > lastPriorityNr)
			{
				AddToPrioritygroup(LoopType::render, lastPriorityNr, objectsForInsert);
				lastPriorityNr = currentObj->GetRenderPriority();
				objectsForInsert.clear();
			}
			objectsForInsert.push_back(currentObj);
			m_pRenderObjectsToBeAdded.pop_front();
		}
		AddToPrioritygroup(LoopType::render, lastPriorityNr, objectsForInsert);
		objectsForInsert.clear();
		m_ShouldAddToRenderList = false;
		m_pRenderObjectsToBeAdded.clear();
	}

	if (m_ShouldAddToImGuiRenderList)
	{
		//sort list with lambda
		m_pImGuiRenderObjectsToBeAdded.sort([](const StandardObject* p_obj1, const StandardObject* p_obj2)
			{
				return p_obj1->GetImGuiPriority() < p_obj2->GetImGuiPriority();
			});

		unsigned int lastPriorityNr = m_pImGuiRenderObjectsToBeAdded.front()->GetUpdatePriority();
		std::list<StandardObject*>::iterator i = m_pImGuiRenderObjectsToBeAdded.begin();
		std::list<StandardObject*>objectsForInsert = std::list<StandardObject*>();
		const int listSize = m_pImGuiRenderObjectsToBeAdded.size();
		for (int i = 0; i < listSize; ++i)
		{
			StandardObject* currentObj = m_pImGuiRenderObjectsToBeAdded.front();
			if (currentObj->GetRenderPriority() > lastPriorityNr)
			{
				AddToPrioritygroup(LoopType::imGuiRender, lastPriorityNr, objectsForInsert);
				lastPriorityNr = currentObj->GetImGuiPriority();
				objectsForInsert.clear();
			}
			objectsForInsert.push_back(currentObj);
			m_pImGuiRenderObjectsToBeAdded.pop_front();
		}
		AddToPrioritygroup(LoopType::imGuiRender, lastPriorityNr, objectsForInsert);
		objectsForInsert.clear();
		m_ShouldAddToImGuiRenderList = false;
		m_pImGuiRenderObjectsToBeAdded.clear();
	}
	
}

void Program::AddToPrioritygroup(LoopType type, unsigned int priorityNr, std::list<StandardObject*>objectsForInsert)
{
	switch (type) {
	case LoopType::input:
		for (PriorityGroup* group : m_pInputObjectGroups)
		{
			if (group->PriorityNr == priorityNr)
			{
				group->standardObjects.insert(group->standardObjects.end(), objectsForInsert.begin(), objectsForInsert.end());
				objectsForInsert.clear();
				return;
			}
		}
		m_pInputObjectGroups.push_back(new PriorityGroup(priorityNr));
		m_pInputObjectGroups.back()->standardObjects.insert(m_pInputObjectGroups.back()->standardObjects.end(), objectsForInsert.begin(), objectsForInsert.end());

		std::sort(m_pInputObjectGroups.begin(), m_pInputObjectGroups.end(), [](PriorityGroup* p_priorityGroup1, PriorityGroup* p_priorityGroup2)
			{
				return p_priorityGroup1->PriorityNr < p_priorityGroup2->PriorityNr;
			});
		objectsForInsert.clear();
		break;
	case LoopType::update:
		for (PriorityGroup* group : m_pUpdateObjectGroups)
		{
			if (group->PriorityNr == priorityNr)
			{
				group->standardObjects.insert(group->standardObjects.end(), objectsForInsert.begin(), objectsForInsert.end());
				return;
			}
		}
		m_pUpdateObjectGroups.push_back(new PriorityGroup(priorityNr));
		m_pUpdateObjectGroups.back()->standardObjects.insert(m_pUpdateObjectGroups.back()->standardObjects.end(), objectsForInsert.begin(), objectsForInsert.end());
		std::sort(m_pUpdateObjectGroups.begin(), m_pUpdateObjectGroups.end(), [](PriorityGroup* p_priorityGroup1, PriorityGroup* p_priorityGroup2)
			{
				return p_priorityGroup1->PriorityNr < p_priorityGroup2->PriorityNr;
			});
		objectsForInsert.clear();
		break;
	case LoopType::fixedUpdate:
		for (PriorityGroup* group : m_pFixedUpdateObjectGroups)
		{
			if (group->PriorityNr == priorityNr)
			{
				group->standardObjects.insert(group->standardObjects.end(), objectsForInsert.begin(), objectsForInsert.end());
				return;
			}
		}
		m_pFixedUpdateObjectGroups.push_back(new PriorityGroup(priorityNr));
		m_pFixedUpdateObjectGroups.back()->standardObjects.insert(m_pFixedUpdateObjectGroups.back()->standardObjects.end(), objectsForInsert.begin(), objectsForInsert.end());
		std::sort(m_pFixedUpdateObjectGroups.begin(), m_pFixedUpdateObjectGroups.end(), [](PriorityGroup* p_priorityGroup1, PriorityGroup* p_priorityGroup2)
			{
				return p_priorityGroup1->PriorityNr < p_priorityGroup2->PriorityNr;
			});
		objectsForInsert.clear();
		break;
	case LoopType::render:
		for (PriorityGroup* group : m_pRenderObjectGroups)
		{
			if (group->PriorityNr == priorityNr)
			{
				group->standardObjects.insert(group->standardObjects.end(), objectsForInsert.begin(), objectsForInsert.end());
				return;
			}
		}
		m_pRenderObjectGroups.push_back(new PriorityGroup(priorityNr));
		m_pRenderObjectGroups.back()->standardObjects.insert(m_pRenderObjectGroups.back()->standardObjects.end(), objectsForInsert.begin(), objectsForInsert.end());
		std::sort(m_pRenderObjectGroups.begin(), m_pRenderObjectGroups.end(), [](PriorityGroup* p_priorityGroup1, PriorityGroup* p_priorityGroup2)
			{
				return p_priorityGroup1->PriorityNr < p_priorityGroup2->PriorityNr;
			});
		objectsForInsert.clear();
		break;
	case LoopType::imGuiRender:
		for (PriorityGroup* group : m_pImGuiRenderObjectGroups)
		{
			if (group->PriorityNr == priorityNr)
			{
				group->standardObjects.insert(group->standardObjects.end(), objectsForInsert.begin(), objectsForInsert.end());
				return;
			}
		}
		m_pImGuiRenderObjectGroups.push_back(new PriorityGroup(priorityNr));
		m_pImGuiRenderObjectGroups.back()->standardObjects.insert(m_pImGuiRenderObjectGroups.back()->standardObjects.end(), objectsForInsert.begin(), objectsForInsert.end());
		std::sort(m_pImGuiRenderObjectGroups.begin(), m_pImGuiRenderObjectGroups.end(), [](PriorityGroup* p_priorityGroup1, PriorityGroup* p_priorityGroup2)
			{
				return p_priorityGroup1->PriorityNr < p_priorityGroup2->PriorityNr;
			});
		objectsForInsert.clear();
		break;
	case LoopType::debugRender:
		//TODO: implement debug rendering
		//currentGroup = m_pDebugRenderObjectGroups;
		break;
	}
}


void Program::RemoveStandardObjectsMarkedForRemove()
{
	if (m_ShouldRemoveFromInputList)
	{
		for (PriorityGroup* group : m_pInputObjectGroups)
		{
			//std::remove_if(group->standardObjects.begin(), group->standardObjects.end(), ShouldRemoveStandardObjectFromLoop);
			group->standardObjects.erase(
				std::remove_if(group->standardObjects.begin(), group->standardObjects.end(), ShouldRemoveStandardObjectFromInputLoop),
				group->standardObjects.end());
			if (group->standardObjects.capacity() >= group->standardObjects.size() + m_ObjectListResizeThreshold)
			{
				group->standardObjects.shrink_to_fit();
			}
		}
		m_ShouldRemoveFromInputList = false;
	}

	if (m_ShouldRemoveFromUpdateList)
	{
		for (PriorityGroup* group : m_pUpdateObjectGroups)
		{
			//std::remove_if(group->standardObjects.begin(), group->standardObjects.end(), ShouldRemoveStandardObjectFromLoop);
			group->standardObjects.erase(
				std::remove_if(group->standardObjects.begin(), group->standardObjects.end(), ShouldRemoveStandardObjectFromUpdateLoop),
				group->standardObjects.end());
			if (group->standardObjects.capacity() >= group->standardObjects.size() + m_ObjectListResizeThreshold)
			{
				group->standardObjects.shrink_to_fit();
			}
		}
		m_ShouldRemoveFromUpdateList = false;
	}

	if (m_ShouldRemoveFromFixedUpdateList)
	{
		for (PriorityGroup* group : m_pFixedUpdateObjectGroups)
		{
			//std::remove_if(group->standardObjects.begin(), group->standardObjects.end(), ShouldRemoveStandardObjectFromLoop);
			group->standardObjects.erase(
				std::remove_if(group->standardObjects.begin(), group->standardObjects.end(), ShouldRemoveStandardObjectFromFixedUpdateLoop),
				group->standardObjects.end());
			if (group->standardObjects.capacity() >= group->standardObjects.size() + m_ObjectListResizeThreshold)
			{
				group->standardObjects.shrink_to_fit();
			}
		}
		m_ShouldRemoveFromFixedUpdateList = false;
	}

	if (m_ShouldRemoveFromRenderList)
	{
		for (PriorityGroup* group : m_pRenderObjectGroups)
		{
			//std::remove_if(group->standardObjects.begin(), group->standardObjects.end(), ShouldRemoveStandardObjectFromLoop);
			group->standardObjects.erase(
				std::remove_if(group->standardObjects.begin(), group->standardObjects.end(), ShouldRemoveStandardObjectFromRenderLoop),
				group->standardObjects.end());
			if (group->standardObjects.capacity() >= group->standardObjects.size() + m_ObjectListResizeThreshold)
			{
				group->standardObjects.shrink_to_fit();
			}
		}
		m_ShouldRemoveFromRenderList = false;
	}

	if (m_ShouldRemoveFromImGuiRenderList)
	{
		for (PriorityGroup* group : m_pImGuiRenderObjectGroups)
		{
			//std::remove_if(group->standardObjects.begin(), group->standardObjects.end(), ShouldRemoveStandardObjectFromLoop);
			group->standardObjects.erase(
				std::remove_if(group->standardObjects.begin(), group->standardObjects.end(), ShouldRemoveStandardObjectFromImGuiLoop),
				group->standardObjects.end());
			if (group->standardObjects.capacity() >= group->standardObjects.size() + m_ObjectListResizeThreshold)
			{
			}
				group->standardObjects.shrink_to_fit();
		}
		m_ShouldRemoveFromImGuiRenderList = false;
	}

	if(m_ShouldRemoveFromObjectList)
	{
		m_Objects.erase(
			std::remove_if(m_Objects.begin(), m_Objects.end(), ShouldDestructStandardObject),
			m_Objects.end());
		
		if (m_Objects.capacity() >= m_Objects.size() + m_ObjectListResizeThreshold)
		{
		}
			m_Objects.shrink_to_fit();

		m_ShouldRemoveFromObjectList = false;
	}
}

void Program::ProgramStart()
{
	if(!m_RunProgram)
	{
		m_RunProgram = true;		
		Run();
	}
}

void Program::AtProgramStart()
{
}

void Program::AddToProgramLoopBegin()
{
}

void Program::AddScene(Scene* newScene) const
{
	m_pSceneManager->AddScene(newScene);
}

void Program::CleanUp()
{
	
}

void Program::AddToObjectsList(StandardObject* p_obj)
{		

	m_ShouldAddToObjectList = true;
	m_pObjectsToBeAdded.push_back(p_obj);		
}

void Program::RemoveFromObjectsList()
{
	m_ShouldRemoveFromObjectList = true;
}

void Program::AddToList(StandardObject* p_obj, LoopType type)
{
	switch (type)
	{
	case LoopType::input:
		m_ShouldAddToInputList = true;
		m_pInputObjectsToBeAdded.push_back(p_obj);
		break;
	case LoopType::update:
		m_ShouldAddToUpdateList = true;
		m_pUpdateObjectsToBeAdded.push_back(p_obj);
		break;
	case LoopType::fixedUpdate:
		m_ShouldAddToFixedUpdateList = true;
		m_pFixedUpdateObjectsToBeAdded.push_back(p_obj);
		break;
	case LoopType::render:
		m_ShouldAddToRenderList = true;
		m_pRenderObjectsToBeAdded.push_back(p_obj);
		break;
	case LoopType::imGuiRender:
		m_ShouldAddToImGuiRenderList = true;
		m_pImGuiRenderObjectsToBeAdded.push_back(p_obj);
		break;
	case LoopType::debugRender:

		break;
	default:
		ASSERT(false);
	}
}

void Program::AddToAllLists(StandardObject* p_obj)
{
	AddToList(p_obj, LoopType::input);
	AddToList(p_obj, LoopType::update);
	//AddToList(p_obj, LoopType::fixedUpdate);
	AddToList(p_obj, LoopType::render);
	AddToList(p_obj, LoopType::imGuiRender);
	//AddToList(p_obj, LoopType::debugRender);
}

void Program::RemoveFromList(const LoopType type)
{
	switch (type)
	{
	case LoopType::input:
		m_ShouldRemoveFromInputList = true;
		break;
	case LoopType::update:
		m_ShouldRemoveFromUpdateList = true;
		break;
	case LoopType::fixedUpdate:
		m_ShouldRemoveFromFixedUpdateList = true;
		break;
	case LoopType::render:
		m_ShouldRemoveFromRenderList = true;
		break;
	case LoopType::imGuiRender:
		m_ShouldRemoveFromImGuiRenderList = true;
		break;
	default:
		ASSERT(false);
	}
}

void Program::RemoveFromAllLists()
{
	RemoveFromList(LoopType::input);
	RemoveFromList(LoopType::update);
	//RemoveFromList(p_obj, LoopType::fixedUpdate);
	RemoveFromList(LoopType::render);
	RemoveFromList(LoopType::imGuiRender);
}