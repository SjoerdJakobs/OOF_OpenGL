#pragma once
#include <functional>
#include <string>
#include <vector>

namespace tests
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& current);
		virtual ~TestMenu();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() override;
		virtual void OnImGuiRender() override;

	private:
		Test* m_currentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_tests;
		
	};
}
