#pragma once
#include <vector>
#include <string>
#include <functional>

namespace test{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {};

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

	};

	class TestMenu: public Test
	{
	public:
		TestMenu(Test*& currentTestPtr);
		~TestMenu();

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string name)
		{
			std::cout << "Register test" << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() ->Test* {return new T(); }));	//通过这里来创建相应的派生对象
		}

	private:
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
		Test* & m_CurrentTest;
	};

}
