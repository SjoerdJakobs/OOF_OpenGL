#pragma once

#include "renderer.h"

class Texture final
{
private:
	unsigned int	m_RendererID;
	std::string		m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width;
	int m_Height;
	int m_BPP;

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	int GetWidth()	const { return m_Width; }
	int GetHeight()	const { return m_Height; }
};
