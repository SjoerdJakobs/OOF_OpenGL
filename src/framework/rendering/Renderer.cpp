#include "Renderer.h"
#include "Camera.h"
#include "Game.h"

//void GLClearError()
//{
//	while (glGetError() != GL_NO_ERROR);
//}
//
//bool GLLogCall(const char* function, const char* file, int line)
//{
//	while (GLenum error = glGetError())
//	{
//		std::cout << "[OpenGl Error] dec : " << error << " | hex : 0x.." << std::hex << error << std::dec << "\n| function : " << function << "\n| file : " << file << "\n| line : " << line << std::endl;
//		return(false);
//	}
//	return(true);
//}

Renderer::Renderer() : m_Camera(Camera::instance())
{
	m_Proj = m_Camera.GetCameraProj();
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GL_CALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, glm::mat4 model) const
{
	const glm::mat4 mvp = m_Proj * m_Camera.GetCameraView() * model;
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	va.Bind();
	ib.Bind();
	GL_CALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader, glm::vec3 position) const
{
	const glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
	const glm::mat4 mvp = m_Proj * m_Camera.GetCameraView() * model;
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	va.Bind();
	ib.Bind();
	GL_CALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	GL_CALL(glClearColor(0.278f, 0.376f, 0.619f, 1.0f));
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}