#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "TestClearColor.h"
#include "exampleProgram.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>

//dont even ask i have probably forgot how this works by the moment you ask me, but here is a video about it:
//https://www.youtube.com/watch?v=p8u_k2LIZyo
inline float Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;
	//this number has changed compared to th original code cus wikipedia said it was better and i decided to just take their word for it >_>
	//https://en.wikipedia.org/wiki/Fast_inverse_square_root#:~:text=The%20inverse%20square%20root%20of%20a%20floating%20point%20number%20is,every%20second%20to%20simulate%20lighting.
	i = 0x5F375A86 - (i >> 1);
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));

	return y;
}

int ScreenWidth = 1280;
int ScreenHeight = 800;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
	ScreenWidth = width;
	ScreenHeight = height;

	/* update any perspective matrices used here */
}

int main(void)
{
	//ExampleProgram* pr = new ExampleProgram();
	//pr->Start();
	
	GLFWwindow* window;

	glfwSetErrorCallback(glfw_error_callback);
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	const char* glsl_version = "#version 460";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS);

	float InitialScreenWidth = 1280;
	float InitialScreenHeight = 800;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(InitialScreenWidth, InitialScreenHeight, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
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

		tests::Test* currentTest = nullptr;
		tests::TestMenu* testMenu = new tests::TestMenu(currentTest);
		currentTest = testMenu;
		tests::TestClearColor test;

		io.ConfigFlags |= ImGuiWindowFlags_NoMove;
		
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			glViewport(0, 0, ScreenWidth, ScreenHeight);
			renderer.Clear();

			test.OnUpdate(0.0f);
			test.OnRender();

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			
			/* Poll for and process events */
			GLCall(glfwPollEvents());

			if(currentTest)
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if(currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}
			test.OnImGuiRender();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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