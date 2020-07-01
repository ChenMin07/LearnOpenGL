#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "GL/glew.h"

#include <glm/glm.hpp>

class Shader
{
private:
	unsigned int m_program;
	std::unordered_map<std::string, int> m_uniformLocationCache;
public:
	Shader(const std::string& vspath, const std::string& fspath);
	~Shader();

private:
	void GetShaderSource(const std::string& filePath, std::string& shaderCode);
	unsigned int ComplileShader(unsigned int type, const std::string& source);
	unsigned int CreateProgram(const std::string& vsCode, const std::string& fsCode);
	int GetUniformLocation(const std::string& uniformName);

public:
	void UseProgram() const;
	void UnUseProgram() const;
	
	void SetUniform4f(const std::string& uniformName, float v1, float v2, float v3, float v4);
	void SetUniformMat4f(const std::string& uniformName, const glm::mat4& matrix);
	void SetUniform1f(const std::string& uniformName, float v1);
	void SetUniform1i(const std::string& uniformName, int v1);
};

