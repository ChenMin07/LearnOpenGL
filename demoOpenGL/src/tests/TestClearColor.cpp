#include "TestClearColor.h"
#include "Renderer.h"

#include "vendor/ImGUI/imgui.h"

namespace test
{

	TestClearColor::TestClearColor()
		:m_ClearColor{ 0.2f, 0.3f, 0.3f, 1.0f }
	{
	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{

	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("color edit", m_ClearColor);
	}

	void TestClearColor::OnRender()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	}

}

