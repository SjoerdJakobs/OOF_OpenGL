#pragma once
#include "CollisionEnums.h"
#include "glm/glm.hpp"
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
class Collision2DManager;

class StandardObject;

class Collider2D
{
protected:
	Collision2DManager* m_pProgram;
	ColliderType2D m_Type;
	StandardObject* ownerObject = nullptr;
	glm::vec2 pos;

	//probably should make this a callback thingy
	virtual void OnCollide(Collider2D* other);
public:

};

