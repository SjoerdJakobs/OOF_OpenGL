#include "Collision2DManager.h"

Collision2DManager::Collision2DManager(int priority)
{
}

void Collision2DManager::Start()
{
}

void Collision2DManager::Awake()
{
}

void Collision2DManager::Update(float deltaTime)
{
	if (m_ShouldAddToCollidersList)
	{
		if (static_cast<int>(m_p2DColliders.capacity()) - (static_cast<int>(m_p2DColliders.size()) + static_cast<int>(m_p2DCollidersToBeAdded.size())) < 0)
		{
			m_p2DColliders.reserve(m_p2DColliders.size() + m_p2DCollidersToBeAdded.size() + 10);
		}
		m_p2DColliders.insert(m_p2DColliders.end(), m_p2DCollidersToBeAdded.begin(), m_p2DCollidersToBeAdded.end());
		for (Collider2D* p_Colliders : m_p2DCollidersToBeAdded)
		{
			//p_Colliders
		}
		m_p2DCollidersToBeAdded.clear();
		m_ShouldAddToCollidersList = false;
	}
}

void Collision2DManager::Render(float deltaTime)
{
}

void Collision2DManager::Sleep()
{
}

void Collision2DManager::OnDestroy()
{
}

void Collision2DManager::OnCollision(Collider2D other)
{
}