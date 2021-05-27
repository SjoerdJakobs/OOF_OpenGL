#include "PickupManager.h"

#include "Camera.h"
#include "Player.h"
#include "Rectangle.h"
#include "SpriteSheetFramePicker.h"
#include "HandyMaths.h"

void PickupManager::Start()
{
	SpawnObjects();
}

void PickupManager::Awake()
{
}

void PickupManager::Sleep()
{
}

void PickupManager::OnDestroy()
{
	for (int i = 0; i < m_CoinAmount; ++i)
	{
		delete m_CoinRectangles[i];
	}
	for (int i = 0; i < m_BombAmount; ++i)
	{
		delete m_BombRectangles[i];
		delete m_ExplosionRectangles[i];
	}
}

void PickupManager::Update(float deltaTime)
{
	UpdateObstacles(deltaTime);
}

void PickupManager::Render(float deltaTime)
{
	for (auto& coinRectangle : m_CoinRectangles)
	{
		SpriteSheetFramePicker picker;
		picker.PickFrameHorizontalDownUp(6, 8,m_FrameCountCoins, coinRectangle);
	}
	for (auto& bombRectangle : m_BombRectangles)
	{
		bombRectangle->DrawWithTexture();
	}
	for (int i = 0; i < m_BombAmount; ++i)
	{
		if (m_BombIsExploding[i])
		{
			SpriteSheetFramePicker picker;
			picker.PickFrameHorizontalDownUp(5, 5, m_FrameCountExplosion[i], m_ExplosionRectangles[i]);			
		}
	}
}

void PickupManager::UpdateObstacles(float deltaTime)
{
	m_CoinFrameTimer += deltaTime;
	if (m_CoinFrameTimer >= m_TimeUntilNextCoinFrame)
	{
		m_CoinFrameTimer -= m_TimeUntilNextCoinFrame;
		m_FrameCountCoins--;
	}

	if (m_FrameCountCoins > m_EndFrameCoins)
	{
		m_FrameCountCoins = m_EndFrameCoins;
	}
	else if (m_FrameCountCoins < m_BeginFrameCoins)
	{
		m_FrameCountCoins = m_EndFrameCoins;
	}
	
	for (int i = 0; i < m_BombAmount; ++i)
	{
		if(m_BombIsExploding[i])
		{
			m_ExplosionFrameTimers[i] += deltaTime;
			if (m_ExplosionFrameTimers[i] >= m_TimeUntilNextExplosionFrame)
			{
				m_ExplosionFrameTimers[i] -= m_TimeUntilNextExplosionFrame;
				m_FrameCountExplosion[i]--;
			}

			if (m_FrameCountExplosion[i] > m_EndFrameExplosion)
			{
				m_FrameCountExplosion[i] = m_EndFrameExplosion;
			}
			else if (m_FrameCountExplosion[i] < m_BeginFrameExplosion)
			{
				m_FrameCountExplosion[i] = m_EndFrameExplosion;
				m_BombIsExploding[i] = false;
				m_ExplosionFrameTimers[i] = 0;
				m_FrameCountExplosion[i] = 0;
				m_ExplosionRectangles[i]->AddToXPos(-3000);
			}
		}
	}

	
	for (int i = 0; i < m_CoinAmount; ++i)
	{
		if (HandyMaths::GetDistance(m_pPlayer->GetPlayerPos(), m_CoinRectangles[i]->GetPos()) < 50)
		{
			m_pPlayer->SetScore((m_pPlayer->GetScore() + 1));
			//m_pCamera->ScreenShake(0.3f);
			m_CoinRectangles[i]->SetXPos((rand() % 740) + -370);
			m_CoinRectangles[i]->SetYPos((rand() % 3000) + (1000 + m_pPlayer->GetPlayerPos().y));
		}
		else if (m_pPlayer->GetPlayerPos().y - m_CoinRectangles[i]->GetYPos() > 2000)
		{
			m_CoinRectangles[i]->SetXPos((rand() % 740) + -370);
			m_CoinRectangles[i]->SetYPos((rand() % 3000) + (1000 + m_pPlayer->GetPlayerPos().y));
		}
	}
	for (int i = 0; i < m_BombAmount; ++i)
	{
		if (HandyMaths::GetDistance(m_pPlayer->GetPlayerPos(), m_BombRectangles[i]->GetPos()) < 50)
		{
			m_pCamera->ScreenShake(0.3f);
			m_BombIsExploding[i] = true;
			m_ExplosionRectangles[i]->SetPos(m_BombRectangles[i]->GetPos());
			m_FrameCountExplosion[i] = 24;
			m_BombRectangles[i]->SetXPos((rand() % 740) + -370);
			m_BombRectangles[i]->SetYPos((rand() % 3000) + (1000 + m_pPlayer->GetPlayerPos().y));
		}
		else if (m_pPlayer->GetPlayerPos().y - m_CoinRectangles[i]->GetYPos() > 2000)
		{
			m_BombRectangles[i]->SetXPos((rand() % 740) + -370);
			m_BombRectangles[i]->SetYPos((rand() % 3000) + (1000 + m_pPlayer->GetPlayerPos().y));
		}
	}
}

void PickupManager::SpawnObjects()
{
	for (int i = 0; i < 8; ++i)
	{
		m_CoinRectangles[i] = DBG_NEW Rectangle(63, 63, 300, 0 + 130 * i, "res/textures/coins2.png", 5);
	}
	for (int i = 0; i < 8; ++i)
	{
		m_BombRectangles[i] = DBG_NEW Rectangle(50, 57, -300, 0+130*i, "res/textures/bomb.png", 4);
	}
	for (int i = 0; i < 8; ++i)
	{
		m_ExplosionRectangles[i] = DBG_NEW Rectangle(129, 125, -3000, 0, "res/textures/explosion2.png", 3);
	}
}

PickupManager::PickupManager(): StandardObject(false, true, false, true, false, false, true,
		920, 920, 920, 920)
{
	m_pCamera = &Camera::instance();
}

PickupManager::~PickupManager() = default;

void PickupManager::GivePlayerPointer(Player* p_player)
{
	m_pPlayer = p_player;
}
