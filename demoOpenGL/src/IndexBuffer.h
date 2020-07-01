#pragma once
#include <GL/glew.h>
class IndexBuffer
{
private:
	unsigned int ibo;
	unsigned int m_count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;
	inline unsigned int GetCount() const { return m_count; }
};