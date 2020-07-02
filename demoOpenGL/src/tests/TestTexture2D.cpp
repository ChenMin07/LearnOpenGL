#include "TestTexture2D.h"
#include "Renderer.h"

#include "vendor/ImGUI/imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test {
	test::TestTexture2D::TestTexture2D()	
	{
		float position[] =
		{
			-0.5f,   0.5f,  0.0f, 0.0f,  1.0f,  //left up
			 0.5f,   0.5f,  0.0f, 1.0f,  1.0f,  //right up
			 0.5f,  -0.5f,	0.0f, 1.0f,  0.0f,  //right bottom
			-0.5f,  -0.5f,	0.0f, 0.0f,  0.0f   //left bottom
		};

		unsigned int indices[] = 
		{
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(position, sizeof(position));
		m_IBO = std::make_unique<IndexBuffer>(indices, 6);

		//因为vao会储存layout的相应的信息，所以可以不用考虑作用域的问题
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_Projection = glm::ortho(-0.0f, 4.0f, -0.0f, 4.0f, -1.0f, 1.0f);

		m_Shader = std::make_unique<Shader>("res/shader/vertexShader.vs", "res/shader/fragmentShader.fs");
		m_Shader->UseProgram();


		m_Texture = std::make_unique<Texture>("res/image/0.png");
		m_Shader->SetUniform1i("u_Texture", 0);
		m_Texture->Bind(0);		//这个0和下面的这个0是对应的

		m_VBO->UnBind();
		m_IBO->UnBind();
		m_VAO->UnBind();
		m_Shader->UnUseProgram();

	}

	test::TestTexture2D::~TestTexture2D()
	{
	}

	void test::TestTexture2D::OnRender()
	{	
		Renderer renderer;
		renderer.Clear();

		{
			glm::mat4 viewA = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Projection * viewA;
			m_Shader->UseProgram();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
		{
			glm::mat4 viewB = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Projection * viewB;
			m_Shader->UseProgram();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
	}

	void test::TestTexture2D::OnImGuiRender()
	{
		{

			ImGui::SliderFloat3("translationA", &m_TranslationA.x, 0.0f, 4.0f);       
			ImGui::SliderFloat3("translationB", &m_TranslationB.x, 0.0f, 4.0f);    
			m_TranslationB.z = m_TranslationA.z = 1.0f;								//因为没有深度，所以直接置为1.0f
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		}
	}
}