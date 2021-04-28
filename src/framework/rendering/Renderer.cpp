#include "Renderer.h"
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

Renderer::Renderer() : m_Camera(Camera::instance())
{
	
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, glm::mat4 model) const
{
	glm::mat4 mvp = m_Camera.GetCameraProj() * m_Camera.GetCameraView() * model;
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, glm::vec3 position) const
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 mvp = m_Camera.GetCameraProj() * m_Camera.GetCameraView() * model;
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	GLCall(glClearColor(1.0f, 0.545f, 0.321f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
