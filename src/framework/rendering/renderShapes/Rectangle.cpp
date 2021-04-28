#include "Rectangle.h"

#include "VertexBufferLayout.h"
#include "glm/gtc/matrix_transform.hpp"

Rectangle::Rectangle(float xSize, float ySize, glm::vec2 pos):m_XSize(xSize),m_YSize(ySize),m_Pos(pos)
{
	Construct();
}

Rectangle::Rectangle(float xSize, float ySize, float xPos, float yPos) : m_XSize(xSize), m_YSize(ySize), m_Pos(glm::vec2(xPos, yPos))
{
	Construct();	
}

Rectangle::Rectangle(float xSize, float ySize, glm::vec2 pos, float& color) :m_XSize(xSize), m_YSize(ySize), m_Pos(pos)
{
	Construct();	
}

Rectangle::Rectangle(float xSize, float ySize, float xPos, float yPos, float& color) : m_XSize(xSize), m_YSize(ySize), m_Pos(glm::vec2(xPos, yPos))
{
	Construct();
}

Rectangle::Rectangle(float xSize, float ySize, glm::vec2 pos, std::string texturePath) : m_XSize(xSize), m_YSize(ySize), m_Pos(pos), m_Texture(std::make_unique<Texture>(texturePath))
{
	Construct();
}

Rectangle::Rectangle(float xSize, float ySize, float xPos, float yPos, std::string texturePath) : m_XSize(xSize), m_YSize(ySize), m_Pos(glm::vec2(xPos, yPos)), m_Texture(std::make_unique<Texture>(texturePath))
{
	Construct();
}


Rectangle::~Rectangle()
{
	
}

void Rectangle::Draw()
{
	Renderer renderer;
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Pos.x,m_Pos.y,0));
	renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader, model);
}

void Rectangle::DrawWithColor()
{
	Renderer renderer;
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Pos.x, m_Pos.y, 0));
	renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader, model);	
}

void Rectangle::DrawWithTexture()
{
	Renderer renderer;
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Pos.x, m_Pos.y, 0));
	renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader, model);	
}

void Rectangle::Construct()
{
	const unsigned int xSize{ 1 };
	const unsigned int ySize{ 1 };

	float positions[] =
	{
		-m_XSize / 2, -m_YSize / 2, 0.0f, 0.0f,
		m_XSize  / 2, -m_YSize / 2, 1.0f, 0.0f,
		m_XSize  / 2, m_YSize  / 2, 1.0f, 1.0f,
		-m_XSize / 2, m_YSize  / 2, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};
	
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
	m_Shader->SetUniform1i("u_Texture", 0);
}


