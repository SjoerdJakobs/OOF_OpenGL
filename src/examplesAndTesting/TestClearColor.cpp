#include "TestClearColor.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace tests
{
	TestClearColor::TestClearColor()
		:m_ClearColor{ 0.62f,0.87f,0.34f,1.0f }
	{
		
	}

	TestClearColor::~TestClearColor()
	{
		
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{
		
	}

	void TestClearColor::OnRender()
	{
		GL_CALL(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT))
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("clear color", m_ClearColor);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}