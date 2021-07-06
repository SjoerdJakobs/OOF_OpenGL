#pragma once
#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

/**
 * this is only still here for testing purposes
 */

#define ASSERT(x) if(!(x)) __debugbreak();
#define GL_CALL(x) GLClearError();\
    x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class RendererOld
{
public:
	RendererOld();

	static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, glm::mat4 model);
	void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, glm::vec3 position);

	void Clear() const;
};
