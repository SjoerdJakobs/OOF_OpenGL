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
struct CircleCollider : Collider2D
{
public:
    glm::vec2  centre;
    float radius;
    CircleCollider(glm::vec2 pos, float radius);

    glm::vec2 support(glm::vec2 direction)
    {
        //return centre + radius * direction.normalized();
    }
};