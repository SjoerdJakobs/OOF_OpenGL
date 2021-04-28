#pragma once
#include <memory>

#include "VertexBuffer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "string"

class Rectangle
{
public:
	Rectangle(float xSize, float ySize, glm::vec2 pos);
	Rectangle(float xSize, float ySize, float xPos, float yPos);
	Rectangle(float xSize, float ySize, glm::vec2 pos, float& color);
	Rectangle(float xSize, float ySize, float xPos, float yPos, float& color);
	Rectangle(float xSize, float ySize, glm::vec2 pos, std::string texturePath);
	Rectangle(float xSize, float ySize, float xPos, float yPos, std::string texturePath);
	~Rectangle();
	
	void Draw();
	void DrawWithColor();
	void DrawWithTexture();

private:

	bool		m_UseColor;
	float		m_XSize;
	float		m_YSize;
	glm::vec2	m_Pos;
	
	std::unique_ptr<VertexArray>	m_VAO;
	std::unique_ptr<VertexBuffer>	m_VertexBuffer;
	std::unique_ptr<IndexBuffer>	m_IndexBuffer;
	std::unique_ptr<Shader>			m_Shader;
	std::unique_ptr<Texture>		m_Texture;

	void Construct();

public:

	void SetPos(float xPos, float yPos)
	{
		m_Pos.x = xPos;
		m_Pos.y = yPos;
	}

	void SetPos(glm::vec2 pos)
	{
		m_Pos = pos;
	}

	glm::vec2 GetPos() const { return m_Pos; }

	void SetXPos(float xPos)
	{
		m_Pos.x = xPos;
	}

	float GetXPos() const { return m_Pos.x; }

	void SetYPos(float yPos)
	{
		m_Pos.y = yPos;
	}

	float GetYPos() const { return m_Pos.y; }
};

