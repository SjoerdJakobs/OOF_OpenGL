#include "Rectangle.h"

#include "Camera.h"
#include "VertexBufferLayout.h"
#include "glm/gtc/matrix_transform.hpp"

Rectangle::Rectangle(float xSize, float ySize, glm::vec2 pos) :m_XSize(xSize), m_YSize(ySize), m_Pos(pos), m_TexturePath("res/textures/NoTexture.jpg"), m_TextureSlot(0), m_Color{ 0,0,0,0 }
{
	ConstructWithColor();
}

Rectangle::Rectangle(float xSize, float ySize, float xPos, float yPos) : m_XSize(xSize), m_YSize(ySize), m_Pos(glm::vec2(xPos, yPos)), m_TexturePath("res/textures/NoTexture.jpg"), m_TextureSlot(0), m_Color{ 0, 0, 0, 0 }
{
	ConstructWithColor();
}

Rectangle::Rectangle(float xSize, float ySize, glm::vec2 pos, float color[4]) : m_XSize(xSize), m_YSize(ySize), m_Pos(pos), m_TexturePath("res/textures/NoTexture.jpg"), m_TextureSlot(0), m_Color{ color[0],color[1],color[2],color[3] }
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
	ConstructWithTexture(xStart, xEnd, yStart, yEnd);
}

Rectangle::Rectangle(float xSize, float ySize, float xPos, float yPos, std::string texturePath, int textureSlot, float xStart, float xEnd, float yStart, float yEnd) : m_XSize(xSize), m_YSize(ySize), m_Pos(glm::vec2(xPos, yPos)), m_TexturePath(texturePath), m_TextureSlot(textureSlot)
{
	ConstructWithTexture(xStart, xEnd, yStart, yEnd);
}

Rectangle::~Rectangle()
{
}

void Rectangle::CleanUp()
{
	if (m_pVAO != nullptr)
	{
		m_pVAO->UnBind();
		delete m_pVAO;
	}

	if (m_pVertexBuffer != nullptr)
	{
		m_pVertexBuffer->UnBind();
		delete m_pVertexBuffer;
	}

	if (m_pIndexBuffer != nullptr)
	{
		m_pIndexBuffer->UnBind();
		delete m_pIndexBuffer;
	}

	if (m_pShader != nullptr)
	{
		m_pShader->UnBind();
		delete m_pShader;
	}

	if (m_pTexture != nullptr)
	{
		m_pTexture->UnBind();
		delete m_pTexture;
	}
}

void Rectangle::Draw() const
{
	Renderer renderer;
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Pos.x, m_Pos.y, 0));

	model = glm::rotate(model, m_Rotation, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(m_XScale, m_YScale, 1));
	
	renderer.Draw(*m_pVAO, *m_pIndexBuffer, *m_pShader, model);
}

void Rectangle::DrawWithColor()
{
	Renderer renderer;
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Pos.x, m_Pos.y, 0));
	model = glm::rotate(model, m_Rotation, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(m_XScale, m_YScale, 1));
	renderer.Draw(*m_pVAO, *m_pIndexBuffer, *m_pShader, model);
}

void Rectangle::DrawWithTexture()
{
	Renderer renderer;

	m_pTexture->Bind(m_TextureSlot);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Pos.x, m_Pos.y, 0));
	model = glm::rotate(model, m_Rotation, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(m_XScale, m_YScale, 1));
	renderer.Draw(*m_pVAO, *m_pIndexBuffer, *m_pShader, model);
}

void Rectangle::DrawWithSpritesheetTextureAnimation(float xStart, float xEnd, float yStart, float yEnd)
{
	Renderer renderer;
	float positions[] =
	{
		-m_XSize / 2, -m_YSize / 2, xStart, yStart,	//0.0f, 0.0f,
		m_XSize  / 2, -m_YSize / 2, xEnd, yStart,	//1.0f, 0.0f,
		m_XSize  / 2, m_YSize  / 2, xEnd, yEnd,		//1.0f, 1.0f,
		-m_XSize / 2, m_YSize  / 2, xStart, yEnd	//0.0f, 1.0f
	};
	
	VertexArray VAO = VertexArray();
	//create VertexBuffer
	VertexBuffer VBuffer = VertexBuffer(positions, 16 * sizeof(float));

	//add VertexBuffer with its layout to VertexArray
	VAO.AddBuffer(VBuffer, *m_pLayout);
	//m_pIndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

	m_pTexture->Bind(m_TextureSlot);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(m_Pos.x, m_Pos.y, 0));
	model = glm::rotate(model, m_Rotation, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(m_XScale, m_YScale, 1));
	renderer.Draw(VAO, *m_pIndexBuffer, *m_pShader, model);
}

void Rectangle::ConstructWithTexture(float xStart, float xEnd, float yStart, float yEnd)
{
	const unsigned int xSize{ 1 };
	const unsigned int ySize{ 1 };

	float positions[] =
	{
		-m_XSize / 2, -m_YSize / 2, xStart, yStart,	//0.0f, 0.0f,
		m_XSize  / 2, -m_YSize / 2, xEnd,   yStart,	//1.0f, 0.0f,
		m_XSize  / 2, m_YSize  / 2, xEnd,   yEnd,	//1.0f, 1.0f,
		-m_XSize / 2, m_YSize  / 2, xStart, yEnd	//0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};

	m_pVAO = new VertexArray();
	//create VertexBuffer
	m_pVertexBuffer = new VertexBuffer(positions, xSize * ySize * 16 * sizeof(float));

	//set layout
	m_pLayout = new VertexBufferLayout;
	//a vertex exists out of 2 floats, hence the 2
	m_pLayout->Push<float>(2);
	//a tex coord exists out of 2 floats, hence the 2
	m_pLayout->Push<float>(2);

	//add VertexBuffer with its layout to VertexArray
	m_pVAO->AddBuffer(*m_pVertexBuffer, *m_pLayout);
	m_pIndexBuffer = new IndexBuffer(indices, xSize * ySize * 6);

	m_pShader = new Shader("res/shaders/BasicTexture.shader");
	m_pShader->Bind();
	m_pTexture = new Texture(m_TexturePath);
	m_pShader->SetUniform1i("u_Texture", m_TextureSlot);
}

void Rectangle::ConstructWithColor()
{
	m_pTexture = nullptr;
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

	m_pVAO = new VertexArray();
	//create VertexBuffer
	m_pVertexBuffer = new VertexBuffer(positions, xSize * ySize * 8 * sizeof(float));
	//create VertexBufferLayout
	VertexBufferLayout layout;

	//set layout
	//a vertex exists out of 2 floats, hence the 2
	layout.Push<float>(2);

	//add VertexBuffer with its layout to VertexArray
	m_pVAO->AddBuffer(*m_pVertexBuffer, layout);
	m_pIndexBuffer = new IndexBuffer(indices, xSize * ySize * 6);

	m_pShader = new Shader("res/shaders/BasicColor.shader");
	m_pShader->Bind();
	m_pShader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
}