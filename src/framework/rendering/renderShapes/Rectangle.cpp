#include "Rectangle.h"

#include "Camera.h"
#include "VertexBufferLayout.h"
#include "glm/gtc/matrix_transform.hpp"

Rectangle::Rectangle(float xSize, float ySize, glm::vec2 pos):m_XSize(xSize),m_YSize(ySize),m_Pos(pos),m_TexturePath("res/textures/NoTexture.jpg"), m_TextureSlot(0),m_Color{0,0,0,0}
{
	
	ConstructWithColor();
}

Rectangle::Rectangle(float xSize, float ySize, float xPos, float yPos) : m_XSize(xSize), m_YSize(ySize), m_Pos(glm::vec2(xPos, yPos)), m_TexturePath("res/textures/NoTexture.jpg"), m_TextureSlot(0),m_Color { 0, 0, 0, 0 }
{
	ConstructWithColor();
}

Rectangle::Rectangle(float xSize, float ySize, glm::vec2 pos, float color[4]) :m_XSize(xSize), m_YSize(ySize), m_Pos(pos), m_TexturePath("res/textures/NoTexture.jpg"), m_TextureSlot(0),m_Color{color[0],color[1],color[2],color[3]}
{
	ConstructWithColor();
}

Rectangle::Rectangle(float xSize, float ySize, float xPos, float yPos, float color[4]) : m_XSize(xSize), m_YSize(ySize), m_Pos(glm::vec2(xPos, yPos)), m_TexturePath("res/textures/NoTexture.jpg"), m_TextureSlot(0), m_Color{ color[0],color[1],color[2],color[3] }
{
	ConstructWithColor();
}

Rectangle::Rectangle(float xSize, float ySize, glm::vec2 pos, std::string texturePath, int textureSlot) : m_XSize(xSize), m_YSize(ySize), m_Pos(pos), m_TexturePath(texturePath), m_TextureSlot(textureSlot)
{
	ConstructWithTexture();
}

Rectangle::Rectangle(float xSize, float ySize, float xPos, float yPos, std::string texturePath, int textureSlot) : m_XSize(xSize), m_YSize(ySize), m_Pos(glm::vec2(xPos, yPos)), m_TexturePath(texturePath), m_TextureSlot(textureSlot)
{
	ConstructWithTexture();
}

Rectangle::Rectangle(float xSize, float ySize, glm::vec2 pos, std::string texturePath, int textureSlot, float xStart, float xEnd, float yStart, float yEnd) : m_XSize(xSize), m_YSize(ySize), m_Pos(pos), m_TexturePath(texturePath), m_TextureSlot(textureSlot)
{
	ConstructWithTexture(xStart,xEnd,yStart,yEnd);
}

Rectangle::Rectangle(float xSize, float ySize, float xPos, float yPos, std::string texturePath, int textureSlot, float xStart, float xEnd, float yStart, float yEnd) : m_XSize(xSize), m_YSize(ySize), m_Pos(glm::vec2(xPos, yPos)), m_TexturePath(texturePath), m_TextureSlot(textureSlot)
{
	ConstructWithTexture(xStart, xEnd, yStart, yEnd);
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
	
	m_Texture->Bind(m_TextureSlot);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Pos.x, m_Pos.y, 0));	
	renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader, model);	
}

void Rectangle::DrawWithSpritesheetTextureAnimation(float xStart, float xEnd, float yStart, float yEnd)
{
	Renderer renderer;
	float positions[] =
	{
		-m_XSize / 2, -m_YSize / 2, xStart, yStart,	//0.0f, 0.0f,
		m_XSize / 2, -m_YSize / 2, xEnd, yStart,	//1.0f, 0.0f,
		m_XSize / 2, m_YSize / 2, xEnd, yEnd,		//1.0f, 1.0f,
		-m_XSize / 2, m_YSize / 2, xStart, yEnd	    //0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};

	VertexArray VAO = VertexArray();
	//create VertexBuffer
	VertexBuffer VBuffer = VertexBuffer(positions, 16 * sizeof(float));
	//create VertexBufferLayout
	VertexBufferLayout layout;

	//set layout
	//a vertex exists out of 2 floats, hence the 2
	layout.Push<float>(2);
	//a tex coord exists out of 2 floats, hence the 2
	layout.Push<float>(2);

	//add VertexBuffer with its layout to VertexArray
	VAO.AddBuffer(VBuffer, layout);
	//m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

	m_Texture->Bind(m_TextureSlot);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Pos.x, m_Pos.y, 0));
	renderer.Draw(VAO, *m_IndexBuffer, *m_Shader, model);
}

void Rectangle::ConstructWithTexture(float xStart, float xEnd , float yStart , float yEnd)
{
	const unsigned int xSize{ 1 };
	const unsigned int ySize{ 1 };

	float positions[] =
	{
		-m_XSize / 2, -m_YSize / 2, xStart, yStart,	//0.0f, 0.0f,
		m_XSize  / 2, -m_YSize / 2, xEnd, yStart,	//1.0f, 0.0f,
		m_XSize  / 2, m_YSize  / 2, xEnd, yEnd,		//1.0f, 1.0f,
		-m_XSize / 2, m_YSize  / 2, xStart, yEnd	//0.0f, 1.0f
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

	m_Shader = std::make_unique<Shader>("res/shaders/BasicTexture.shader");
	m_Shader->Bind();
	m_Texture = std::make_unique<Texture>(m_TexturePath);
	m_Shader->SetUniform1i("u_Texture", m_TextureSlot);
}


void Rectangle::ConstructWithColor()
{
	const unsigned int xSize{ 1 };
	const unsigned int ySize{ 1 };
	float positions[] =
	{
		-m_XSize / 2, -m_YSize / 2,
		m_XSize / 2, -m_YSize / 2, 
		m_XSize / 2, m_YSize / 2, 
		-m_XSize / 2, m_YSize / 2
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};

	m_VAO = std::make_unique<VertexArray>();
	//create VertexBuffer
	m_VertexBuffer = std::make_unique<VertexBuffer>(positions, xSize * ySize * 8 * sizeof(float));
	//create VertexBufferLayout
	VertexBufferLayout layout;

	//set layout
	//a vertex exists out of 2 floats, hence the 2
	layout.Push<float>(2);

	//add VertexBuffer with its layout to VertexArray
	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, xSize * ySize * 6);

	m_Shader = std::make_unique<Shader>("res/shaders/BasicColor.shader");
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
}


