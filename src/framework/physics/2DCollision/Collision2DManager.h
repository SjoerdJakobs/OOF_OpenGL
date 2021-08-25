#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include "StandardObject.h"
#include "Collider2D.h"
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
class Collision2DManager final : public StandardObject
{
public:
	static Collision2DManager& instance()
	{
		static Collision2DManager* p_instance = new Collision2DManager(1000);
		return *p_instance;
	}

private:
	// Private Constructor
	Collision2DManager(int priority);
	Collision2DManager(Collision2DManager const&) {}            // copy constructor is private
	Collision2DManager& operator=(Collision2DManager const&) {} // assignment operator is private

	std::vector<Collider2D*> m_p2DColliders;
	std::list <Collider2D*> m_p2DCollidersToBeAdded;

	bool m_ShouldAddToCollidersList{ false };
	bool m_ShouldRemoveFromCollidersList{ false };

	// Inherited via StandardObject
	virtual void Start() override;

	virtual void Awake() override;

	virtual void Update(float deltaTime) override;

	virtual void Render(float deltaTime) override;

	virtual void Sleep() override;

	virtual void OnDestroy() override;

	void OnCollision(Collider2D other);
};
