#pragma once

#include <algorithm>
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
		return(sqrtf(GetDistanceSquared(vector1, vector2)));
	}
	static float GetDistanceSquared(glm::vec2 vector1, glm::vec2 vector2)
	{
		return(powf(fabsf(vector1.x - vector2.x), 2) + powf(fabsf(vector1.y - vector2.y), 2));
	}

	static float minimum_distance(glm::vec2 v, glm::vec2 w, glm::vec2 p) {
		// Return minimum distance between line segment vw and point p
		const float l2 = GetDistanceSquared(v, w);  // i.e. |w-v|^2 -  avoid a sqrt
		if (l2 == 0.0) return GetDistance(p, v);   // v == w case
		// Consider the line extending the segment, parameterized as v + t (w - v).
		// We find projection of point p onto the line.
		// It falls where t = [(p-v) . (w-v)] / |w-v|^2
		// We clamp t from [0,1] to handle points outside the segment vw.
		const float t = std::clamp(dot(p - v, w - v) / l2, 0.0f, 1.0f);
		const glm::vec2 projection = v + t * (w - v);  // Projection falls on the segment
		return distance(p, projection);
	}

	//ty for the comprehensive explanation joshua: https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment?page=1&tab=votes#tab-top
	//and poulbourke: http://paulbourke.net/geometry/pointlineplane/
	//not working atm sadly :(
	/*
	static float GetShortestDistanceFromFiniteLine(glm::vec2 lineStartA, glm::vec2 lineEndB, glm::vec2 pointC)
	{
		glm::vec2 CA = pointC - lineStartA;
		glm::vec2 BA = lineEndB - lineStartA;
		float dot = glm::dot(CA, BA);
		float lengthSquared = BA.x * BA.x + BA.y * BA.y;
		float param{ -1 };
		if (lengthSquared != 0)
		{
			param = dot / lengthSquared;
		}
		glm::vec2 xy;

		if (param < 0)//closest point is the start of the line
		{
			xy = lineStartA;
		}
		else if (param > 1)//closest point is the end of the line
		{
			xy = lineEndB;
		}
		else//closest point is inbetween the start and the end of the line
		{
			xy = lineStartA + param * lineEndB;
		}

		return GetDistance(pointC,xy);
	}*/

	static float AngleBetweenVectors(glm::vec2 v1, glm::vec2 v2) {
		//Vector2.Dot(v1,v2) / (Vector2.Dot())
		double dot = v1.x * v2.x + v1.y * v2.y;
		double det = v1.x * v2.y + v1.y * v2.x;
		return atan2(det, dot);
	}

	static float LookAtVectorInRadians(glm::vec2 looking, glm::vec2 at) {
		// +1.5707963268 because north is 0 degrees in this case instead of east
		return AngleBetweenVectors(glm::vec2(1, 0), glm::vec2(at.x - looking.x, at.y - looking.y));
	}
};
