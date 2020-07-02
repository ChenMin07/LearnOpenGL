#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "vendor/ImGUI/imgui.h"
#include "vendor/ImGUI/imgui_impl_opengl3.h"
#include "vendor/ImGUI/imgui_impl_glfw.h"

#include <cmath>

#include "tests/TestClearColor.h"
#include "tests/Test.h"
#include "tests/TestTexture2D.h"


int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1000, 750, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	GLCall(glfwSwapInterval(1));
	glewInit();

	std::cout << glGetString(GL_VERSION) << std::endl;
	{

		Renderer renderer;
		const char* glsl_version = "#version 130";
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init(glsl_version);
		ImGui_ImplGlfw_InitForOpenGL(window, true);

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;
		
		testMenu->RegisterTest<test::TestClearColor>("clearColor");
		testMenu->RegisterTest<test::TestTexture2D>("Texture2D ");

		float r = 0;
		float incre = 0.05f;

		while (!glfwWindowShouldClose(window))
		{
			if(currentTest == testMenu)
				renderer.Clear();											//这个清除是用与整个循环的刷新

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest)
			{
				currentTest->OnUpdate(0);		
				currentTest->OnRender();								//这个清除是用与该按钮之后的刷新
				ImGui::Begin("test");

				if (currentTest != testMenu && ImGui::Button("<<"))		//currentTest不指向menu则说明它指向一个text的对象，此时如点击按钮
				{
					delete currentTest;									//析构该test对象，然后将currentTest指向menu
					currentTest = testMenu;
				}

				currentTest->OnImGuiRender();							//这个是指向对象的Gui界面
				ImGui::End();
			}

			ImGui::Render();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);									//不能放在DrawArray之前，不然无法显示

			glfwPollEvents();

			if (r > 1)
				incre = -0.05f;
			if (r < 0)
				incre = 0.05f;
			r += incre;
		}

		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}
