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


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1000, 750, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	GLCall(glfwSwapInterval(1));
	glewInit();

	//float position[] =
	//{
	//	-0.5f,   0.5f,  0.0f, 0.0f,  1.0f,  //left up
	//	 0.5f,   0.5f,  0.0f, 1.0f,  1.0f,  //right up
	//	 0.5f,  -0.5f,	0.0f, 1.0f,  0.0f,  //right bottom
	//	-0.5f,  -0.5f,	0.0f, 0.0f,  0.0f   //left bottom
	//};

	//unsigned int indices[] = 
	//{
	//	0, 1, 2,
	//	2, 3, 0
	//};

	//GLCall(glEnable(GL_BLEND));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
//		VertexArray vao;
//		VertexBuffer vbo(position, sizeof(position));
//		IndexBuffer ibo(indices, 6);
//
//		VertexBufferLayout layout;
//		layout.Push<float>(3);
//		layout.Push<float>(2);
//		vao.AddBuffer(vbo, layout);
//
//		glm::mat4 projection = glm::ortho(-0.0f, 4.0f, -0.0f, 4.0f, -1.0f, 1.0f);
////		glm::mat4 mvp = projection;
//
//		//glm::mat4 projection = glm::mat4(glm::vec4(2.0f, 0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 2.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 0.0f), glm::vec4(0.3f, 0.2f, 0.0f, 1.0f));
//		Shader shader("res/shader/vertexShader.vs", "res/shader/fragmentShader.fs");
//		shader.UseProgram();
//
//
//		Texture texture("res/image/0.png");
//		shader.SetUniform1i("u_Texture", 0);
//		texture.Bind(0);		//这个0和下面的这个0是对应的
//
//		vbo.UnBind();
//		ibo.UnBind();
//		vao.UnBind();
//		shader.UnUseProgram();

		Renderer renderer;

		test::TestClearColor clearColor;

		ImGui::CreateContext();
		
		const char* glsl_version = "#version 130";

		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		
		while (!glfwWindowShouldClose(window))
		{
			
			//renderer.Clear();
			clearColor.OnRender();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			//shader.UseProgram();
			//{
			//	glm::mat4 viewA = glm::translate(glm::mat4(1.0f), translationA);
			//	glm::mat4 mvp = projection * viewA;
			//	shader.UseProgram();
			//	shader.SetUniformMat4f("u_MVP", mvp);
			//	renderer.Draw(vao, ibo, shader);
			//}
			//{
			//	glm::mat4 viewB = glm::translate(glm::mat4(1.0f), translationB);
			//	glm::mat4 mvp = projection * viewB;
			//	shader.UseProgram();
			//	shader.SetUniformMat4f("u_MVP", mvp);
			//	renderer.Draw(vao, ibo, shader);
			//}


			//{

			//	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
			//	ImGui::SliderFloat3("translationA", &translationA.x, 0.0f, 4.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			//	ImGui::SliderFloat3("translationB", &translationB.x, 0.0f, 4.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//	ImGui::End();

			//}

			// Rendering
			clearColor.OnImGuiRender();

			ImGui::Render();
			int display_w, display_h;
			glfwGetFramebufferSize(window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


			glfwSwapBuffers(window);		//不能放在DrawArray之前，不然无法显示

			//if (r > 1)
			//	increment = -0.05f;
			//if (r < 0)
			//	increment = 0.05f;
			//r += increment;
			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}
