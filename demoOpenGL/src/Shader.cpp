#include "Shader.h"
#include "Renderer.h"

Shader::Shader(const std::string& vspath, const std::string& fspath)
{
	std::string vsCode, fsCode;
	GetShaderSource(vspath, vsCode);
	GetShaderSource(fspath, fsCode);

	CreateProgram(vsCode, fsCode);
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

void Shader::GetShaderSource(const std::string& filePath, std::string& shaderCode)
{
	std::ifstream stream(filePath);
	if (!stream)
		std::cout << "wrong" << std::endl;
	std::stringstream ss;
	ss << stream.rdbuf();
	shaderCode = ss.str();
}

unsigned int Shader::ComplileShader(unsigned int type, const std::string& source)
{
	GLCall( unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall( glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

    //get error log
	int result;
	GLCall( glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int lenth;
		GLCall( glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenth));
		char* message = (char*)alloca(lenth * sizeof(char));
		GLCall(glGetShaderInfoLog(id, lenth, &lenth, message));
		std::cout << (type == GL_VERTEX_SHADER ? "vertex shader compiled error" : "fragment shader compiled error") <<
			std::endl;
		std::cout << message << std::endl;

	}

	return id;
}

unsigned int Shader::CreateProgram(const std::string& vsCode, const std::string& fsCode)
{
	unsigned int vs = ComplileShader(GL_VERTEX_SHADER, vsCode);
	unsigned int fs = ComplileShader(GL_FRAGMENT_SHADER, fsCode);
	m_program = glCreateProgram();
	GLCall(glAttachShader(m_program, vs));
	GLCall(glAttachShader(m_program, fs));
	GLCall(glLinkProgram(m_program));
	GLCall(glValidateProgram(m_program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return m_program;
}

void Shader::UseProgram() const
{
	GLCall( glUseProgram(m_program));
}

void Shader::UnUseProgram() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& uniformName, float v1, float v2, float v3, float v4)
{
	GLCall(glUniform4f(GetUniformLocation(uniformName), v1, v2, v3, v4));
}

void Shader::SetUniformMat4f(const std::string& uniformName,const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniform1f(const std::string& uniformName, float v1)
{
	GLCall(glUniform1f(GetUniformLocation(uniformName), v1));
}

void Shader::SetUniform1i(const std::string& uniformName, int v1)
{
	GLCall(glUniform1i(GetUniformLocation(uniformName), v1));
}

int Shader::GetUniformLocation(const std::string& uniformName)
{
	if (m_uniformLocationCache.find(uniformName) != m_uniformLocationCache.end())
		return m_uniformLocationCache[uniformName];


	GLCall( int location = glGetUniformLocation(m_program, uniformName.c_str()));		//注意，没有使用该变量也会无法找到，尽管定义了
	if (location == -1)
		std::cout << "warning !!! " << uniformName << " doesn't exist\n";
	else
		m_uniformLocationCache[uniformName] = location;
	return location;
}
