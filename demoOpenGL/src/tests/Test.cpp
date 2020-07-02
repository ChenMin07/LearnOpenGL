#include "Test.h"

#include "vendor/ImGUI/imgui.h"

namespace test {

	TestMenu::TestMenu(Test*& currentTestPtr)
		:m_CurrentTest(currentTestPtr)
	{
	}

	TestMenu::~TestMenu()
	{

	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& t : m_Tests)
		{
			if (ImGui::Button(t.first.c_str()))		//��currentָ��һ��������Ķ���
				m_CurrentTest = t.second();

		}
	}

}
