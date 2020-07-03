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
		//����ʹ��ָ������Ϊ��Щ���������Ҫ��ʼ��������������Щ�����ڹ��캯�����棬�����ڽ��빹�캯��������֮ǰ�Ȳ�������Щ����
		//����һ��Ҫ���ǵ�����������������⣬�����ǹ��캯���ڽ��д����������뿪���캯����ͻᱻ������

		
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
