#include "TestTexture2D.h"

#include "RendererOld.h"
#include "imgui/imgui.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace tests
{
	TestTexture2D::TestTexture2D()
	:m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	m_TranslationA(0, 0, 0), m_TranslationB(500, 200, 0)
	{
		const unsigned int xSize{ 1 };
		const unsigned int ySize{ 1 };
		float boxSize{ 400.0f };
		
		float positions[] =
		{
			-boxSize / 2, -boxSize / 2,0.0f, 0.0f,
			boxSize / 2, -boxSize / 2, 1.0f,  0.0f,
			boxSize / 2, boxSize / 2, 1.0f, 1.0f,
			-boxSize / 2, boxSize / 2, 0.0f,  1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,
		};

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		m_VAO = std::make_unique<VertexArray>();

		//create VertexBuffer
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, xSize * ySize * 16 * sizeof(float));
		//create VertexBufferLayout
		VertexBufferLayout layout;

		//set layout
		//a vertex exists out of 2 floats, hence the 2
		layout.Push<float>(2);
		//a tex coord exists out of 2 floats, hence the 2
		layout.Push<float>(2);

		//add VertexBuffer with its layout to VertexArray
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, xSize * ySize * 6);
				
		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Texture = std::make_unique<Texture>("res/textures/LogoOpenGL.png");
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D()
	{
		
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
		
	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		RendererOld renderer;

		m_Texture->Bind();


		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		glm::mat4 mvp = m_Proj * m_View * model;	//hah pvm cus opengl
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);



		glm::mat4 model2 = glm::translate(glm::mat4(1.0f), m_TranslationB);
		glm::mat4 mvp2 = m_Proj * m_View * model2;	//hah pvm cus opengl
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp2);
		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::Begin("Debug");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);                   // Create a m_pWindow called "Hello, world!" and append into it.
		ImGui::SliderFloat3("positionA", &m_TranslationA.x, 0, 1280);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat3("positionB", &m_TranslationB.x, 0, 1280);            // Edit 1 float using a slider from 0.0f to 1.0f

		ImGui::End();
		
	}
}