#include "Test.h"
#include "imgui/imgui.h"

namespace tests
{
	TestMenu::TestMenu(Test*& current) :m_currentTest(current)
	{
	}

	TestMenu::~TestMenu()
	{
	}

	void TestMenu::OnUpdate(float deltaTime)
	{
	}

	void TestMenu::OnRender()
	{
	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_tests)
		{
			if(ImGui::Button(test.first.c_str()))
			{
				m_currentTest = test.second();
			}
		}
	}
}
