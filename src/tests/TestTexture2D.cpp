#include "TestTexture2D.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace tests
{
	TestTexture2D::TestTexture2D()
	: m_TranslationA(0, 0, 0), m_TranslationB(500, 200, 0)
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


		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_VAO = std::make_unique<VertexArray>();
		
		//create VertexArray
		VertexArray va;
		//create VertexBuffer
		VertexBuffer vb(positions, xSize * ySize * 16 * sizeof(float));
		//create VertexBufferLayout
		VertexBufferLayout layout;

		//set layout
		//a vertex exists out of 2 floats, hence the 2
		layout.Push<float>(2);
		//a tex coord exists out of 2 floats, hence the 2
		layout.Push<float>(2);

		//add VertexBuffer with its layout to VertexArray
		m_VAO->AddBuffer(vb, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>();

		IndexBuffer ib(indices, xSize * ySize * 6);
		
		m_Shader->Bind();

		Texture texture("res/textures/LogoOpenGL.png");
		texture.Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

		va.UnBind();
		vb.Unbind();
		ib.Unbind();
		m_Shader->UnBind();
		
	}

	TestTexture2D::~TestTexture2D()
	{
		
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
		
	}

	void TestTexture2D::OnRender()
	{
		/*GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT))
			shader.Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = proj * view * model;	//hah pvm cus opengl
			shader.SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(va, ib, shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = proj * view * model;	//hah pvm cus opengl
			shader.SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(va, ib, shader);
		}*/
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::Begin("Debug");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);                   // Create a window called "Hello, world!" and append into it.
		ImGui::SliderFloat3("positionA", &m_TranslationA.x, 0, 1280);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat3("positionB", &m_TranslationB.x, 0, 1280);            // Edit 1 float using a slider from 0.0f to 1.0f

		ImGui::End();
		
	}
}