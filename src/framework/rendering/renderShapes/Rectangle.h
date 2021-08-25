#pragma once
#include "VertexBuffer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "string"

class Rectangle final
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
	void CleanUp();

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
	float		m_XScale{ 1 };
	float		m_YScale{ 1 };
	float		m_Rotation{0};
	glm::vec2	m_Pos;
	float m_Color[4];

	VertexArray* m_pVAO;
	VertexBuffer* m_pVertexBuffer;
	IndexBuffer* m_pIndexBuffer;
	Shader* m_pShader;
	Texture* m_pTexture;
	VertexBufferLayout* m_pLayout;

	void ConstructWithTexture(float xStart = 0.0f, float xEnd = 1.0f, float yStart = 0.0f, float yEnd = 1.0f);
	void ConstructWithColor();

public:

	void SetRotationDegrees(float degrees)
	{
		m_Rotation = glm::radians(degrees);
	}
	void SetRotationRadians(float radians)
	{
		m_Rotation = radians;
	}

	void AddToRotationDegrees(float degrees)
	{
		m_Rotation += glm::radians(degrees);
	}
	void AddToRotationRadians(float radians)
	{
		m_Rotation += radians;
	}

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

	void SetScale(float x, float y)
	{
		m_XScale = x;
		m_YScale = y;
	}
};
