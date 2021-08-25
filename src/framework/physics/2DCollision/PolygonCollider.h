#pragma once
#include "Collider2D.h"
#include <vector>
/************************************************************************************************************************************
/
/
/
/
/
/
/
/
/
/
/												not finished, WIP
/
/
/
/
/
/
/
/
/
*/
struct PolygonCollider : Collider2D
{
	PolygonCollider(std::vector<glm::vec2> vertices) : m_vertices(vertices)
	{
	}

	std::vector<glm::vec2> m_vertices;

	//virtual glm::vec2 support(glm::vec2 direction) override
	//{
	//    float furthestDistance = -INFINITY;
	//    glm::vec2 furthestVertex{};

	//    for (glm::vec2 v : m_vertices) {
	//        float distance = glm::dot(v, direction);
	//        if (distance > furthestDistance) {
	//            furthestDistance = distance;
	//            furthestVertex = v;
	//        }
	//    }
	//    return furthestVertex;
	//}
};