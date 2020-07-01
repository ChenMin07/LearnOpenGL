#include "Renderer.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, int line)
{
	GLenum error;
	while (error = glGetError() != GL_NO_ERROR)
	{
		std::cout << "[OpenGL Error: " << error << "]\n" <<
			"\n" << "line: " << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
	//shader.UseProgram();
	vao.Bind();
	ibo.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::Clear() const
{
	GLCall( glClear(GL_COLOR_BUFFER_BIT) );
	GLCall( glClearColor(0.1f, 0.3f, 0.3f, 1.0f) );
}
