#pragma once
class VertexBuffer final
{
private:
	unsigned int m_RenderID;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};
