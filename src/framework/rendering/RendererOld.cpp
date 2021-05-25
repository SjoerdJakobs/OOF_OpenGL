#include "RendererOld.h"
#include <iostream>
#include "Camera.h"
#include "Game.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGl Error] dec : " << error << " | hex : 0x.." << std::hex << error << std::dec << "\n| function : " << function << "\n| file : " << file << "\n| line : " << line << std::endl;
		return(false);
	}
	return(true);
}

RendererOld::RendererOld()
{
}

void RendererOld::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GL_CALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void RendererOld::Clear() const
{
	GL_CALL(glClearColor(1.0f, 0.545f, 0.321f, 0.1f));
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}