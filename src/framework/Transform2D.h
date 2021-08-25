#pragma once
#include "glm/glm.hpp"

struct Transform2D final
{
	Transform2D();
	~Transform2D();
	glm::vec2 position{};
	glm::vec2 scale{};
	float rotation = 0;
};
