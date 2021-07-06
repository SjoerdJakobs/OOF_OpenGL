#pragma once
#include "glm/glm.hpp"
class HandyMaths
{
public:
	//****************************
	//dont even ask i have probably forgotten how this works by the moment you ask me, but here is a video about it:
	//https://www.youtube.com/watch?v=p8u_k2LIZyo
	float Q_rsqrt(float number)
	{
		long i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *(long*)&y;
		//this number has changed compared to th original code cus wikipedia said it was better and i decided to just take their word for it >_>
		//https://en.wikipedia.org/wiki/Fast_inverse_square_root#:~:text=The%20inverse%20square%20root%20of%20a%20floating%20point%20number%20is,every%20second%20to%20simulate%20lighting.
		i = 0x5F375A86 - (i >> 1);
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y));

		return y;
	}
	//****************************

	static float Lerp(float a, float b, float f)
	{
		return (a * (1.0f - f)) + (b * f);
	}

	static float GetDistance(glm::vec2 vector1, glm::vec2 vector2)
	{
		return(sqrtf(powf(fabsf(vector1.x - vector2.x), 2) + powf(fabsf(vector1.y - vector2.y), 2)));
	}
};
