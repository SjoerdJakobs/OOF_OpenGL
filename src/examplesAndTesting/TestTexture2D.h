#pragma once
#include "Test.h"

#include <memory>

#include "VertexBuffer.h"
#include "Texture.h"

namespace tests
{
	class TestTexture2D final : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;

		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;


		glm::mat4 m_Proj;
		glm::mat4 m_View;
	};
}
