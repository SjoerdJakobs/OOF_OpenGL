#include "Collider2D.h"
#include "Collision2DManager.h"
#include "StandardObject.h"

void Collider2D::OnCollide(Collider2D* other)
{
	if (ownerObject != nullptr)
	{
		ownerObject->OnCollision(other);
	}
}