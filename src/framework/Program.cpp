#include "Program.h"
#include "StandardObject.h"
#include "PriorityGroup.h"
#include "Test.h"
#include "TestClearColor.h"


bool ShouldDestructStandardObject(StandardObject* object)
{
	if (object->GetShouldDestruct())
	{
		delete object;
		return true;
	}
	return false;
}

bool ShouldRemoveStandardObjectFromLoop(StandardObject* object)
{
	return true;
	/*switch (type)
	{
	case input:
		return object->GetUsesInput();
		break;
	case update:
		return object->GetUsesInput();
		break;
	case fixedUpdate:
		return object->GetUsesUpdate();
		break;
	case render:
		return object->GetUsesRenderer();
		break;
	case imGuiRender:
		return object->GetUsesImGui();
		break;
	case debugRender:
		return object->GetUsesDebugRenderer();
		break;
	default:;
	}*/
}

Program::Program()
{
	
}

Program::~Program()
{
}

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
	//ScreenWidth = width;
	//ScreenHeight = height;

	/* update any perspective matrices used here */
}

void Program::Run()
{
	GLFWwindow* window;

	glfwSetErrorCallback(glfw_error_callback);
	/* Initialize the library */
	if (!glfwInit())
	{
		ASSERT(false);
		m_runProgram = false;
	}
	
	const char* glsl_version = "#version 460";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS);

	float InitialScreenWidth = 1280.0f;
	float InitialScreenHeight = 800.0f;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(static_cast<int>(InitialScreenWidth), static_cast<int>(InitialScreenHeight), "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		ASSERT(false);
		m_runProgram = false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);//vsync

	glfwSetWindowSizeCallback(window, glfw_window_size_callback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR, glewInit() != GLEW_OK" << std::endl;
	}
	else
	{
		std::cout << glGetString(GL_VERSION) << std::endl;
	}
	
	{
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		Renderer renderer;

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiWindowFlags_NoMove;					// Prevent window movement
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
				
		//tests::Test* current;
		//tests::TestClearColor test;

		io.ConfigFlags |= ImGuiWindowFlags_NoMove;

		// Set start time
		std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
		while (!glfwWindowShouldClose(window)&&m_runProgram)
		{
			// Get current time
			std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
			// Calculate elapsed time
			m_unscaledDeltaTime = std::chrono::duration<float>(t2 - t1).count();
			// Update current time
			t1 = t2;
			// Prevent jumps in time caused by break points
			m_unscaledDeltaTime = std::min(m_unscaledDeltaTime, m_MaxElapsedSeconds);
			m_deltaTime = m_unscaledDeltaTime * m_timeScale;

			//m_fixedTimeStepTimer += m_unscaledDeltaTime;
			//if (m_fixedTimeStepTimer >= m_fixedTimeStep)
			//{
			//	//fixed update
			//	m_fixedTimeStepTimer -= m_fixedTimeStep;
			//}
			//std::cout << m_deltaTime << std::endl;

			glViewport(0, 0, ScreenWidth, ScreenHeight);
			renderer.Clear();

			if (!IsTruePaused())
			{
				for (PriorityGroup* group : m_pInputObjectGroups)
				{
					for (StandardObject* object : group->standardObjects) {
						if(!IsPaused() || object->IsPauseImmune())
						{
							object->Input(m_unscaledDeltaTime);
						}
					}
				}
			}

			if (!IsTruePaused())
			{
				for (PriorityGroup* group : m_pUpdateObjectGroups)
				{
					for (StandardObject* object : group->standardObjects) {
						if (!IsPaused() || object->IsPauseImmune())
						{
							object->ImGuiRender(m_unscaledDeltaTime);
						}
					}
				}
			}

			if (!IsTruePaused())
			{
				for (PriorityGroup* group : m_pRenderObjectGroups)
				{
					for (StandardObject* object : group->standardObjects) {
						if (!IsPaused() || object->IsPauseImmune())
						{
							object->ImGuiRender(m_unscaledDeltaTime);
						}
					}
				}
			}
			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			/* Poll for and process events */
			GLCall(glfwPollEvents());


			if (!IsTruePaused())
			{
				for (PriorityGroup* group : m_pImGuiRenderObjectGroups)
				{
					for (StandardObject* object : group->standardObjects) {
						if (!IsPaused() || object->IsPauseImmune())
						{
							object->ImGuiRender(m_unscaledDeltaTime);
						}
					}
				}
			}

			if(m_shouldRemoveFromInputList)
			{
				for (PriorityGroup* group : m_pInputObjectGroups)
				{
					//std::remove_if(group->standardObjects.begin(), group->standardObjects.end(), ShouldRemoveStandardObjectFromLoop);
				}
			}
			
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			//activate and deactivate objects
			for (StandardObject* bo : m_objects) {
				if (bo->IsShouldBeActive() && !bo->IsActiveState()) {
					bo->AddToLists();
					bo->SetActiveState(true);
					bo->Awake();
				}
				else if (!bo->IsShouldBeActive() && bo->IsActiveState()) {
					bo->RemoveFromLists();
					bo->SetActiveState(false);
					bo->Sleep();
				}
			}
			
			//std::remove_if(m_objects.begin(), m_objects.end(), ShouldDestructStandardObject);
			//destroy objects that need to be destroyed
			//std::remove_if(m_objects.begin(), m_objects.end(), ShouldDestructStandardObject);
			
			/* Swap front and back buffers */
			GLCall(glfwSwapBuffers(window));

			if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
				glfwSetWindowShouldClose(window, 1);
			}
		}
	}
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);	
}

void Program::Start()
{
	if(!m_runProgram)
	{
		m_runProgram = true;
		
		
		Run();
	}
}

void Program::CleanUp()
{
	
}

void Program::AddToList(StandardObject* p_obj, LoopType type)
{
	switch (type)
	{
	case LoopType::input:
		m_shouldAddToInputList = true;
		m_pInputObjectsToBeAdded.push_back(p_obj);
		break;
	case LoopType::update:
		m_shouldAddToUpdateList = true;
		m_pUpdateObjectsToBeAdded.push_back(p_obj);
		break;
	case LoopType::fixedUpdate:
		m_shouldAddToFixedUpdateList = true;
		m_pFixedUpdateObjectsToBeAdded.push_back(p_obj);
		break;
	case LoopType::render:
		m_shouldAddToRenderList = true;
		m_pRenderObjectsToBeAdded.push_back(p_obj);
		break;
	case LoopType::imGuiRender:
		m_shouldAddToImGuiRenderList = true;
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
}

void Program::RemoveFromList(StandardObject* p_obj, LoopType type)
{
	switch (type)
	{
	case LoopType::input:
		m_shouldRemoveFromInputList = true;
		//m_pInputObjectsToBeRemoved.push_back(p_obj);
		break;
	case LoopType::update:
		m_shouldRemoveFromUpdateList = true;
		//m_pUpdateObjectsToBeRemoved.push_back(p_obj);
		break;
	case LoopType::fixedUpdate:
		m_shouldRemoveFromFixedUpdateList = true;
		//m_pFixedUpdateObjectsToBeRemoved.push_back(p_obj);
		break;
	case LoopType::render:
		m_shouldRemoveFromRenderList = true;
		//m_pRenderObjectsToBeRemoved.push_back(p_obj);
		break;
	case LoopType::imGuiRender:
		m_shouldRemoveFromImGuiRenderList = true;
		//m_pImGuiRenderObjectsToBeRemoved.push_back(p_obj);
		break;
	default:
		ASSERT(false);
	}
}

void Program::RemoveFromAllLists(StandardObject* p_obj)
{
	RemoveFromList(p_obj, LoopType::input);
	RemoveFromList(p_obj, LoopType::update);
	//RemoveFromList(p_obj, LoopType::fixedUpdate);
	RemoveFromList(p_obj, LoopType::render);
	RemoveFromList(p_obj, LoopType::imGuiRender);
}

