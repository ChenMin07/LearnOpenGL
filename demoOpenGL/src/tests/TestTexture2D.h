#pragma once
#include "Test.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include <memory>

namespace test {
	class TestTexture2D:public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnRender() override;
		void OnImGuiRender() override;

	private:	
		//这里使用指针是因为这些对象可能需要初始化参数，但是这些参数在构造函数里面，所以在进入构造函数的主体之前先不构造这些对象
		//还有一个要考虑的问题是作用域的问题，假如是构造函数内进行创建对象，在离开构造函数后就会被析构掉

		
		std::vector<std::unique_ptr<VertexArray >> m_VAOs;
		std::vector<std::unique_ptr<VertexBuffer>> m_VBOs;
		std::vector<std::unique_ptr<IndexBuffer >> m_IBOs;
		std::vector<std::unique_ptr<Shader >> m_Shaders;

		std::vector<std::unique_ptr<Texture>> m_Textures;

		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;

		glm::mat4 m_Projection;
	};
}
