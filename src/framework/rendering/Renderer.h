#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GL_CALL(x) GLClearError();\
    x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

class Camera;
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
private:
	Camera& m_Camera;
	glm::mat4 m_Proj;
public:
	Renderer();

	static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, glm::mat4 model) const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, glm::vec3 position) const;

	void Clear() const;
};
