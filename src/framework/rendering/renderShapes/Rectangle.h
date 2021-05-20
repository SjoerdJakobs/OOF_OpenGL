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
	Rectangle(float xSize, float ySize, glm::vec2 pos, float color[4]);
	Rectangle(float xSize, float ySize, float xPos, float yPos, float color[4]);
	Rectangle(float xSize, float ySize, glm::vec2 pos, std::string texturePath, int textureSlot);
	Rectangle(float xSize, float ySize, float xPos, float yPos, std::string texturePath, int textureSlot);
	Rectangle(float xSize, float ySize, glm::vec2 pos, std::string texturePath, int textureSlot, float xStart, float xEnd, float yStart, float yEnd);
	Rectangle(float xSize, float ySize, float xPos, float yPos, std::string texturePath, int textureSlot, float xStart, float xEnd, float yStart, float yEnd);
	
	~Rectangle();
	
	void Draw() const;
	void DrawWithColor();
	void DrawWithTexture();
	void DrawWithSpritesheetTexture();
	void DrawWithSpritesheetTextureAnimation(float xStart = 0.0f, float xEnd = 1.0f, float yStart = 0.0f, float yEnd = 1.0f);

private:
	
	std::string m_TexturePath;
	int			m_TextureSlot;
	float		m_XSize;
	float		m_YSize;
	glm::vec2	m_Pos;
	float m_Color[4];
	
	std::unique_ptr<VertexArray>	m_VAO;
	std::unique_ptr<VertexBuffer>	m_VertexBuffer;
	std::unique_ptr<IndexBuffer>	m_IndexBuffer;
	std::unique_ptr<Shader>			m_Shader;
	std::unique_ptr<Texture>		m_Texture;

	void ConstructWithTexture(float xStart = 0.0f, float xEnd = 1.0f, float yStart = 0.0f, float yEnd = 1.0f);
	void ConstructWithColor();

public:

	void AddToXPos(float xPos)
	{
		m_Pos.x += xPos;
	}
	
	void AddToYPos(float yPos)
	{
		m_Pos.y += yPos;
	}
	
	void AddToPos(float xPos, float yPos)
	{
		m_Pos.x += xPos;
		m_Pos.y += yPos;
	}

	void AddToPos(glm::vec2 pos)
	{
		m_Pos += pos;
	}
	
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

