#include "Program.h"

#include "AllocationMetrics.h"
#include "StandardObject.h"
#include "PriorityGroup.h"
#include "SceneManager.h"
#include "SoundManager.h"

bool ShouldDestructStandardObject(StandardObject* object)
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

bool ShouldRemoveGroupFromLoop(const PriorityGroup* group)
{
	if (group->m_StandardObjects.empty())
	{
		delete group;
		return true;
	}
	return false;
}

Program* Program::m_pInstance = nullptr;

Program* Program::GetInstance()
{
	if (m_pInstance == nullptr)
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

static void glfw_window_size_callback(GLFWwindow * m_pWindow, int width, int height) {
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
		GL_CALL(glEnable(GL_BLEND));
		GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		const Renderer renderer;

		m_pSceneManager = new SceneManager();

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		//todo: make a system to manage fonts
		io.FontDefault = io.Fonts->AddFontFromFileTTF("res/fonts/Open_Sans/OpenSans-Regular.ttf", 18);//font 0
		io.Fonts->AddFontFromFileTTF("res/fonts/Orbitron/Orbitron-Bold.ttf", 56);//font 1

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		this->AtProgramStart();
		m_pSceneManager->Start();

		m_pSoundManager = &SoundManager::instance();
		m_pSoundManager->StartBackgroundMusic1();

		// Set start time
		std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
		while (!glfwWindowShouldClose(m_pWindow) && m_RunProgram)
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
			GL_CALL(glClearColor(0, 0, 0, 1));

			/* Poll for and process events */
			GL_CALL(glfwPollEvents());

			this->AddToProgramLoopBegin();

			if (!IsTruePaused())
			{
				for (PriorityGroup* p_group : m_pInputObjectGroups)
				{
					for (StandardObject* p_obj : p_group->m_StandardObjects) {
						if (!IsPaused() || p_obj->IsPauseImmune())
						{
							p_obj->Input(m_DeltaTime);
						}
					}
				}
			}

			if (!IsTruePaused())
			{
				for (PriorityGroup* p_group : m_pUpdateObjectGroups)
				{
					for (StandardObject* p_obj : p_group->m_StandardObjects) {
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
					for (StandardObject* p_obj : p_group->m_StandardObjects) {
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
					for (StandardObject* p_obj : p_group->m_StandardObjects) {
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

			CheckStandardObjectsMarkedForAdding();
			RemoveStandardObjectsMarkedForRemove();
			
			if(m_ShouldCleanGroups)
			{
				PrintMemoryUsage("before group cleanup");
				CleanupEmptyGroups();
				PrintMemoryUsage("after group cleanup");
			}
			m_pSceneManager->UpdateScene();


			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			GL_CALL(glfwSwapBuffers(m_pWindow));

			/*if (GLFW_PRESS == glfwGetKey(m_pWindow, GLFW_KEY_I)) {
				std::cout << "Use WASD or the arrow keys for movement and shift for sprint. \n Pickup the coins and evade enemies and bombs" << std::endl;
			}*/
			if (GLFW_PRESS == glfwGetKey(m_pWindow, GLFW_KEY_I)) {
				std::cout << std::endl;
				std::cout << "Use WASD or the arrow keys for movement." << std::endl;
				std::cout << "pressing shift will make you sprint." << std::endl;
				std::cout << "Coins give you points!." << std::endl;
				std::cout << "EVERYTHING ELSE WILL DAMAGE YOU IF IT TOUCHES YOU" << std::endl;
				std::cout << "try to get as many points as possible until you die" << std::endl;
				PrintMemoryUsage();
			}
			if (GLFW_PRESS == glfwGetKey(m_pWindow, GLFW_KEY_M))
			{
				m_pSceneManager->SwitchToScene(SceneNames::MainMenu);
			}

			////***************************************************
			////Sound
			////***************************************************
			//if (GLFW_PRESS == glfwGetKey(m_pWindow, GLFW_KEY_1)) {

			//	result = system->playSound(sound1, 0, false, &channel);
			//}
			//if (GLFW_PRESS == glfwGetKey(m_pWindow, GLFW_KEY_2)) {

			//	result = system->playSound(sound2, 0, false, &channel);
			//}
			//if (GLFW_PRESS == glfwGetKey(m_pWindow, GLFW_KEY_3)) {

			//	result = system->playSound(sound3, 0, false, &channel);
			//}

			//result = system->update();

			////***************************************************
			////Sound
			////***************************************************

			/*if (GLFW_PRESS == glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE)) {
				glfwSetWindowShouldClose(m_pWindow, 1);
			}*/
		}
	}


	CleanUp();
	//exit(EXIT_SUCCESS);
}

void Program::CleanupEmptyGroups()
{
	m_pInputObjectGroups.erase(std::remove_if(m_pInputObjectGroups.begin(), m_pInputObjectGroups.end(), ShouldRemoveGroupFromLoop), m_pInputObjectGroups.end());
	m_pInputObjectGroups.shrink_to_fit();


	m_pUpdateObjectGroups.erase(std::remove_if(m_pUpdateObjectGroups.begin(), m_pUpdateObjectGroups.end(), ShouldRemoveGroupFromLoop), m_pUpdateObjectGroups.end());
	m_pUpdateObjectGroups.shrink_to_fit();


	m_pFixedUpdateObjectGroups.erase(std::remove_if(m_pFixedUpdateObjectGroups.begin(), m_pFixedUpdateObjectGroups.end(), ShouldRemoveGroupFromLoop), m_pFixedUpdateObjectGroups.end());
	m_pFixedUpdateObjectGroups.shrink_to_fit();


	m_pRenderObjectGroups.erase(std::remove_if(m_pRenderObjectGroups.begin(), m_pRenderObjectGroups.end(), ShouldRemoveGroupFromLoop), m_pRenderObjectGroups.end());
	m_pRenderObjectGroups.shrink_to_fit();


	m_pImGuiRenderObjectGroups.erase(std::remove_if(m_pImGuiRenderObjectGroups.begin(), m_pImGuiRenderObjectGroups.end(), ShouldRemoveGroupFromLoop), m_pImGuiRenderObjectGroups.end());
	m_pImGuiRenderObjectGroups.shrink_to_fit();
	
	m_ShouldCleanGroups = false;
}

void Program::CleanUp()
{
	m_pSceneManager->CleanUp();
	delete m_pSceneManager;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_pWindow);
	glfwTerminate();

	for (PriorityGroup* p_group : m_pInputObjectGroups)
	{
		delete p_group;
	}
	m_pInputObjectGroups.clear();
	m_pInputObjectsToBeAdded.clear();

	for (PriorityGroup* p_group : m_pUpdateObjectGroups)
	{
		delete p_group;
	}
	m_pUpdateObjectGroups.clear();
	m_pUpdateObjectsToBeAdded.clear();

	for (PriorityGroup* p_group : m_pFixedUpdateObjectGroups)
	{
		delete p_group;
	}
	m_pFixedUpdateObjectGroups.clear();
	m_pFixedUpdateObjectsToBeAdded.clear();

	for (PriorityGroup* p_group : m_pRenderObjectGroups)
	{
		delete p_group;
	}
	m_pRenderObjectGroups.clear();
	m_pRenderObjectsToBeAdded.clear();

	for (PriorityGroup* p_group : m_pImGuiRenderObjectGroups)
	{
		delete p_group;
	}
	m_pImGuiRenderObjectGroups.clear();
	m_pImGuiRenderObjectsToBeAdded.clear();

	for (StandardObject* p_objects : m_Objects)
	{
		delete p_objects;
	}
	m_Objects.clear();
}

//Todo: template the repeated code here or make a function which can be used by all looptypes
void Program::CheckStandardObjectsMarkedForAdding()
{
	if (m_ShouldAddToObjectList)
	{
		if (static_cast<int>(m_Objects.capacity()) - (static_cast<int>(m_Objects.size()) + static_cast<int>(m_pObjectsToBeAdded.size())) < 0)
		{
			m_Objects.reserve(m_Objects.size() + m_pObjectsToBeAdded.size() + m_ObjectListResizeThreshold);
		}
		m_Objects.insert(m_Objects.end(), m_pObjectsToBeAdded.begin(), m_pObjectsToBeAdded.end());
		for (StandardObject* p_object : m_pObjectsToBeAdded)
		{
			p_object->Start();
		}
		m_pObjectsToBeAdded.clear();
		m_ShouldAddToObjectList = false;
	}

	if (m_ShouldAddToInputList)			{	AddStandardObjectsMarkedForAdding(m_pInputObjectsToBeAdded,		m_pInputObjectGroups,      m_ShouldAddToInputList);	}

	if (m_ShouldAddToUpdateList)		{	AddStandardObjectsMarkedForAdding(m_pUpdateObjectsToBeAdded,		m_pUpdateObjectGroups,	  m_ShouldAddToUpdateList);	}

	if (m_ShouldAddToFixedUpdateList)	{	/*AddStandardObjectsMarkedForAdding(m_pFixedUpdateObjectsToBeAdded, LoopType::fixedUpdate, m_ShouldAddToFixedUpdateList);*/	}

	if (m_ShouldAddToRenderList)		{	AddStandardObjectsMarkedForAdding(m_pRenderObjectsToBeAdded,		m_pRenderObjectGroups,	  m_ShouldAddToRenderList);	}

	if (m_ShouldAddToImGuiRenderList)	{	AddStandardObjectsMarkedForAdding(m_pImGuiRenderObjectsToBeAdded,	m_pImGuiRenderObjectGroups,m_ShouldAddToImGuiRenderList);}
}

void Program::AddStandardObjectsMarkedForAdding(std::list<StandardObject*>& p_ObjectsToBeAdded, std::vector<PriorityGroup*>& p_ObjectGroupsToBeAddedTo, bool& ShouldAddToListBool)
{
	//sort list with lambda
	p_ObjectsToBeAdded.sort([](const StandardObject* p_obj1, const StandardObject* p_obj2)
			{
				return p_obj1->GetRenderPriority() < p_obj2->GetRenderPriority();
			});

	unsigned int lastPriorityNr = p_ObjectsToBeAdded.front()->GetRenderPriority();
	std::list<StandardObject*>::iterator i = p_ObjectsToBeAdded.begin();
	std::list<StandardObject*>objectsForInsert = std::list<StandardObject*>();
	const int listSize = p_ObjectsToBeAdded.size();
	for (int i = 0; i < listSize; ++i)
	{
		StandardObject* currentObj = p_ObjectsToBeAdded.front();
		if (currentObj->GetRenderPriority() > lastPriorityNr)
		{
			AddToPrioritygroup(p_ObjectGroupsToBeAddedTo, lastPriorityNr, objectsForInsert);
			lastPriorityNr = currentObj->GetRenderPriority();
			objectsForInsert.clear();
		}
		objectsForInsert.push_back(currentObj);
		p_ObjectsToBeAdded.pop_front();
	}
	AddToPrioritygroup(p_ObjectGroupsToBeAddedTo, lastPriorityNr, objectsForInsert);
	objectsForInsert.clear();
	ShouldAddToListBool = false;
	p_ObjectsToBeAdded.clear();
}

//Todo: template the repeated code here or make a function which can be used by all looptypes
void Program::AddToPrioritygroup(std::vector<PriorityGroup*>& p_ObjectGroups, unsigned int priorityNr, std::list<StandardObject*>& objectsForInsert)
{
	for (PriorityGroup* group : p_ObjectGroups)
	{
		if (group->PriorityNr == priorityNr)
		{
			group->m_StandardObjects.insert(group->m_StandardObjects.end(), objectsForInsert.begin(), objectsForInsert.end());
			objectsForInsert.clear();
			return;
		}
	}
	p_ObjectGroups.push_back(new PriorityGroup(priorityNr));
	p_ObjectGroups.back()->m_StandardObjects.insert(p_ObjectGroups.back()->m_StandardObjects.end(), objectsForInsert.begin(), objectsForInsert.end());

	std::sort(p_ObjectGroups.begin(), p_ObjectGroups.end(), [](PriorityGroup* p_priorityGroup1, PriorityGroup* p_priorityGroup2)
		{
			return p_priorityGroup1->PriorityNr < p_priorityGroup2->PriorityNr;
		});
	objectsForInsert.clear();
}

//Todo: template the repeated code here or make a function which can be used by all looptypes
void Program::RemoveStandardObjectsMarkedForRemove()
{
	if (m_ShouldRemoveFromInputList)
	{
		for (PriorityGroup* group : m_pInputObjectGroups)
		{
			//std::remove_if(group->m_StandardObjects.begin(), group->m_StandardObjects.end(), ShouldRemoveStandardObjectFromLoop);
			group->m_StandardObjects.erase(
				std::remove_if(group->m_StandardObjects.begin(), group->m_StandardObjects.end(), ShouldRemoveStandardObjectFromInputLoop),
				group->m_StandardObjects.end());
			
			if (group->m_StandardObjects.capacity() >= group->m_StandardObjects.size() + m_ObjectListResizeThreshold)
			{
				group->m_StandardObjects.shrink_to_fit();
			}
		}
		m_ShouldRemoveFromInputList = false;
	}

	if (m_ShouldRemoveFromUpdateList)
	{
		for (PriorityGroup* group : m_pUpdateObjectGroups)
		{
			//std::remove_if(group->m_StandardObjects.begin(), group->m_StandardObjects.end(), ShouldRemoveStandardObjectFromLoop);
			group->m_StandardObjects.erase(
				std::remove_if(group->m_StandardObjects.begin(), group->m_StandardObjects.end(), ShouldRemoveStandardObjectFromUpdateLoop),
				group->m_StandardObjects.end());
			if (group->m_StandardObjects.capacity() >= group->m_StandardObjects.size() + m_ObjectListResizeThreshold)
			{
				group->m_StandardObjects.shrink_to_fit();
			}
		}
		m_ShouldRemoveFromUpdateList = false;
	}

	if (m_ShouldRemoveFromFixedUpdateList)
	{
		for (PriorityGroup* group : m_pFixedUpdateObjectGroups)
		{
			//std::remove_if(group->m_StandardObjects.begin(), group->m_StandardObjects.end(), ShouldRemoveStandardObjectFromLoop);
			group->m_StandardObjects.erase(
				std::remove_if(group->m_StandardObjects.begin(), group->m_StandardObjects.end(), ShouldRemoveStandardObjectFromFixedUpdateLoop),
				group->m_StandardObjects.end());
			if (group->m_StandardObjects.capacity() >= group->m_StandardObjects.size() + m_ObjectListResizeThreshold)
			{
				group->m_StandardObjects.shrink_to_fit();
			}
		}
		m_ShouldRemoveFromFixedUpdateList = false;
	}

	if (m_ShouldRemoveFromRenderList)
	{
		for (PriorityGroup* group : m_pRenderObjectGroups)
		{
			//std::remove_if(group->m_StandardObjects.begin(), group->m_StandardObjects.end(), ShouldRemoveStandardObjectFromLoop);
			group->m_StandardObjects.erase(
				std::remove_if(group->m_StandardObjects.begin(), group->m_StandardObjects.end(), ShouldRemoveStandardObjectFromRenderLoop),
				group->m_StandardObjects.end());
			if (group->m_StandardObjects.capacity() >= group->m_StandardObjects.size() + m_ObjectListResizeThreshold)
			{
				group->m_StandardObjects.shrink_to_fit();
			}
		}
		m_ShouldRemoveFromRenderList = false;
	}

	if (m_ShouldRemoveFromImGuiRenderList)
	{
		for (PriorityGroup* group : m_pImGuiRenderObjectGroups)
		{
			//std::remove_if(group->m_StandardObjects.begin(), group->m_StandardObjects.end(), ShouldRemoveStandardObjectFromLoop);
			group->m_StandardObjects.erase(
				std::remove_if(group->m_StandardObjects.begin(), group->m_StandardObjects.end(), ShouldRemoveStandardObjectFromImGuiLoop),
				group->m_StandardObjects.end());
			if (group->m_StandardObjects.capacity() >= group->m_StandardObjects.size() + m_ObjectListResizeThreshold)
			{
			}
			group->m_StandardObjects.shrink_to_fit();
		}
		m_ShouldRemoveFromImGuiRenderList = false;
	}

	if (m_ShouldRemoveFromObjectList)
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
	if (!m_RunProgram)
	{
		m_RunProgram = true;
		Run();
	}
}

void Program::AddScene(Scene * newScene) const
{
	m_pSceneManager->AddScene(newScene);
}

void Program::AddToObjectsList(StandardObject * p_obj)
{
	m_ShouldAddToObjectList = true;
	m_pObjectsToBeAdded.push_back(p_obj);
}

void Program::RemoveFromObjectsList()
{
	m_ShouldRemoveFromObjectList = true;
}

void Program::AddToList(StandardObject * p_obj, LoopType type)
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
	}
}

void Program::AddToAllLists(StandardObject * p_obj)
{
	AddToList(p_obj, LoopType::input);
	AddToList(p_obj, LoopType::update);
	//AddToList(p_obj, LoopType::fixedUpdate);
	AddToList(p_obj, LoopType::render);
	AddToList(p_obj, LoopType::imGuiRender);
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