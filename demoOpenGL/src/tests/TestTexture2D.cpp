#include "TestTexture2D.h"
#include "Renderer.h"
#include <array>
#include "vendor/ImGUI/imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct Vec2
{
	float x, y;
};
struct Vec3
{
	float x, y, z;
};
struct Vec4
{
	float x, y, z, w;
};

struct Vertex 
{
	Vec3 position;
	Vec2 texCoord;
	float texindex;
};

static std::array<Vertex, 4> CreateQuad(Vec3 leftUp, float texIndex)
{
	Vertex v0 = { leftUp, {0.0f, 1.0f} , texIndex};
	Vertex v1 = { {leftUp.x + 1.0f, leftUp.y} , {1.0f, 1.0f}, texIndex };
	Vertex v2 = { {leftUp.x + 1.0f, leftUp.y - 1.0f}, {1.0f, 0.0f}, texIndex };
	Vertex v3 = { {leftUp.x, leftUp.y - 1.0f }, {0.0f, 0.0f}, texIndex };

	return { v0, v1, v2, v3 };
}

namespace test {
	test::TestTexture2D::TestTexture2D()	
	{
		m_PositionA = { -0.5f, 0.5f, 0.0f };
		m_PositionB = {  0.5f, 1.5f, 0.0f };

		unsigned int indices[] = 
		{
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


		m_VAOs.push_back( std::make_unique<VertexArray>());
		m_VBOs.push_back( std::make_unique<VertexBuffer>(nullptr, sizeof(float) * 6 * 8));
		m_IBOs.push_back( std::make_unique<IndexBuffer>(indices, 12));

		
		VertexBufferLayout layout;	//因为vao会储存layout的相应的信息，所以可以不用考虑作用域的问题
		layout.Push<float>(3);		//position
		layout.Push<float>(2);		//texCoord
		layout.Push<float>(1);
		m_VAOs[0]->AddBuffer(*m_VBOs[0], layout);

		m_Shaders.push_back(std::make_unique<Shader>("res/shader/vertexShader.vs", "res/shader/fragmentShader.fs"));
		m_Shaders[0]->UseProgram();


		m_Textures.push_back(std::make_unique<Texture>("res/image/0.png"));
		m_Textures.push_back(std::make_unique<Texture>("res/image/1.png"));
		m_Textures[0]->Bind(0);		//这个0和下面的这个0是对应的
		m_Textures[1]->Bind(1);		//这个1和下面的这个1是对应的
		m_Shaders[0]->SetUniform1i("u_Textures", 0);
		m_Shaders[0]->SetUniform1i("u_Textures", 1);

		//m_VBOs[0]->UnBind();
		//m_IBOs[0]->UnBind();
		//m_VAOs[0]->UnBind();
		//m_Shaders[0]->UnUseProgram();

		m_Projection = glm::ortho(-0.0f, 4.0f, -0.0f, 4.0f, -1.0f, 1.0f);
		m_TranslationA = glm::vec3(1.0f, 1.0f, 0.0f);
	}

	test::TestTexture2D::~TestTexture2D()
	{
	}

	void test::TestTexture2D::OnRender()
	{	
		Renderer renderer;
		renderer.Clear();

		m_VAOs[0]->Bind();
		m_Shaders[0]->UseProgram();
		
		{
			glm::mat4 viewA = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Projection * viewA;
			m_Shaders[0]->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAOs[0], *m_IBOs[0], *m_Shaders[0]);
		}
	}

	void test::TestTexture2D::OnImGuiRender()
	{
		{
			//ImGui::SliderFloat3("translationA", &m_TranslationA.x, 0.0f, 4.0f);       
			//ImGui::SliderFloat3("translationB", &m_TranslationB.x, 0.0f, 4.0f);    
			ImGui::SliderFloat2("positionA", &m_PositionA.x, 0.0f, 4.0f);
			ImGui::SliderFloat2("positionB", &m_PositionB.x, 0.0f, 4.0f);

			m_TranslationB.z = m_TranslationA.z = 1.0f;								//因为没有深度，所以直接置为1.0f
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		}
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
		//float position[] =
		//{
		//	//position			    //texCoord	 //texIndex
		//	-0.5f,  0.5f,  0.0f,	0.0f, 1.0f,   0.0f,		//left up
		//	 0.5f,  0.5f,  0.0f,	1.0f, 1.0f,   0.0f,		//right up
		//	 0.5f, -0.5f,  0.0f,	1.0f, 0.0f,   0.0f,		//right bottom
		//	-0.5f, -0.5f,  0.0f,	0.0f, 0.0f,   0.0f,		//left bottom

		//	 0.5f,  1.5f,  0.0f,	0.0f, 1.0f,   1.0f,		//left up
		//	 1.5f,  1.5f,  0.0f,	1.0f, 1.0f,   1.0f,		//right up
		//	 1.5f,  0.5f,  0.0f,	1.0f, 0.0f,   1.0f,		//right bottom
		//	 0.5f,  0.5f,  0.0f,	0.0f, 0.0f,   1.0f		//left bottom
		//};
		
		auto quad0 = CreateQuad({ m_PositionA.x,  m_PositionA.y,  0.0f }, 0.0f);
		auto quad1 = CreateQuad({ m_PositionB.x,  m_PositionB.y,  0.0f }, 1.0f);

		Vertex vertices[8];
		memcpy(vertices, quad0.data(), sizeof(Vertex) * quad0.size());
		memcpy(vertices + quad0.size(), quad1.data(), sizeof(Vertex) * quad1.size());

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	}

}