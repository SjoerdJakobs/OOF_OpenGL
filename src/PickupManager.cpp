#include "PickupManager.h"

#include "Camera.h"
#include "Player.h"
#include "Rectangle.h"
#include "SpriteSheetFramePicker.h"
#include "SoundManager.h"

void PickupManager::Start()
{
	SpawnObjects();
	m_pSoundManager = &SoundManager::instance();
	m_CurrentBombMovementSpeed = m_BaseBombMovementSpeed;
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
		picker.PickFrameHorizontalDownUp(6, 8, m_FrameCountCoins, coinRectangle);
	}
	for (auto& bombRectangle : m_BombRectangles)
	{
		bombRectangle->DrawWithTexture();
	}
	for (auto& zombieRectangle : m_ZombieRectangles)
	{
		zombieRectangle->DrawWithTexture();
	}
	for (auto& laserRectangle : m_LaserRectangles)
	{
		laserRectangle->DrawWithTexture();
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
		if (m_BombIsExploding[i])
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
			m_pSoundManager->PlayCoin();
			m_pPlayer->SetScore((m_pPlayer->GetScore() + 1));
			//m_pCamera->ScreenShake(0.3f);
			m_CoinRectangles[i]->SetXPos((rand() % 740) + -370.0f);
			m_CoinRectangles[i]->SetYPos((rand() % 3000) + (1000 + m_pPlayer->GetPlayerPos().y));
		}
		else if (m_pPlayer->GetPlayerPos().y - m_CoinRectangles[i]->GetYPos() > 2000)
		{
			m_CoinRectangles[i]->SetXPos((rand() % 740) + -370.0f);
			m_CoinRectangles[i]->SetYPos((rand() % 3000) + (1000 + m_pPlayer->GetPlayerPos().y));
		}
	}









	//way to much magic numbers, this will be fixed when it will be moved too its own class
	m_CurrentBombMovementSpeed += m_BombMovementSpeedGrowthPerSecond * deltaTime;
	for (int i = 0; i < m_BombAmount; ++i)
	{
		m_BombRectangles[i]->AddToPos(m_BombDirections[i] * (m_CurrentBombMovementSpeed * deltaTime));
		if (HandyMaths::GetDistance(m_pPlayer->GetPlayerPos(), m_BombRectangles[i]->GetPos()) < 50)
		{
			m_pSoundManager->PlayExplosion();
			m_pCamera->ScreenShake(0.5f);
			m_BombIsExploding[i] = true;
			m_ExplosionRectangles[i]->SetPos(m_BombRectangles[i]->GetPos());
			m_FrameCountExplosion[i] = 24;
			m_BombRectangles[i]->SetXPos((rand() % 740) + -370.0f);
			m_BombRectangles[i]->SetYPos((rand() % 1000) + (500 + m_pPlayer->GetPlayerPos().y));
			m_BombDirections[i] = normalize(glm::vec2(m_pPlayer->GetPlayerPos() - m_BombRectangles[i]->GetPos()));
			m_pPlayer->TakeDamage(5);
		}
		else if (m_pPlayer->GetPlayerPos().y - m_BombRectangles[i]->GetYPos() > 1500)
		{
			m_BombRectangles[i]->SetXPos((rand() % 740) + -370.0f);
			m_BombRectangles[i]->SetYPos((rand() % 1000) + (500 + m_pPlayer->GetPlayerPos().y));
			m_BombDirections[i] = normalize(glm::vec2(m_pPlayer->GetPlayerPos() - m_BombRectangles[i]->GetPos()));
		}
		else if (m_BombRectangles[i]->GetPos().x > 370 || m_BombRectangles[i]->GetPos().x < -370 || m_BombRectangles[i]->GetPos().y < -100)
		{
			m_pSoundManager->PlayExplosion();
			m_pCamera->ScreenShake(0.3f);
			m_BombIsExploding[i] = true;
			m_ExplosionRectangles[i]->SetPos(m_BombRectangles[i]->GetPos());
			m_FrameCountExplosion[i] = 24;
			m_BombRectangles[i]->SetXPos((rand() % 740) + -370.0f);
			m_BombRectangles[i]->SetYPos((rand() % 1000) + (500 + m_pPlayer->GetPlayerPos().y));
			m_BombDirections[i] = normalize(glm::vec2(m_pPlayer->GetPlayerPos() - m_BombRectangles[i]->GetPos()));
		}
	}

	for (int i = 0; i < m_ZombieAmount; ++i)
	{
		m_ZombieRectangles[i]->AddToPos(normalize(glm::vec2(m_pPlayer->GetPlayerPos() - m_ZombieRectangles[i]->GetPos())) * (110 * deltaTime));
		m_ZombieRectangles[i]->SetRotationRadians(HandyMaths::LookAtVectorInRadians(m_ZombieRectangles[i]->GetPos(), m_pPlayer->GetPlayerPos()));
		if (HandyMaths::GetDistance(m_pPlayer->GetPlayerPos(), m_ZombieRectangles[i]->GetPos()) < 50)
		{
			//m_pSoundManager->PlayExplosion();
			m_pPlayer->TakeDamage(1);
			m_pCamera->ScreenShake(0.3f);
		}
		else if (m_pPlayer->GetPlayerPos().y - m_ZombieRectangles[i]->GetYPos() > 1500)
		{
			m_ZombieRectangles[i]->SetXPos((rand() % 740) + -370.0f);
			m_ZombieRectangles[i]->SetYPos((rand() % 3000) + (1000 + m_pPlayer->GetPlayerPos().y));
		}
	}

	for (int i = 0; i < m_LaserAmount; ++i)
	{
		m_LaserTimeCounter[i] -= deltaTime;
		if (m_LaserTimeCounter[i] < 0.0f && !m_LaserIsShootingBool[i])
		{
			m_LaserIsShootingBool[i] = true;
			m_LaserTimeCounter[i] = 2.0f;
			m_LaserRectangles[i]->SetScale(1.0f, 0.1f);
			m_LaserIsShootingTopPos[i].x = ((rand() % 2000) + -1000.0f);
			m_LaserIsShootingTopPos[i].y = m_pCamera->GetCameraPos().y + 5000;
			m_LaserIsShootingBottomPos[i].x = ((rand() % 2000) + -1000.0f);
			m_LaserIsShootingBottomPos[i].y = m_pCamera->GetCameraPos().y - 5000;
			m_LaserRectangles[i]->SetYPos(m_pCamera->GetCameraPos().y);
		}
		else if (m_LaserIsShootingBool[i])
		{
			if ((m_LaserTimeCounter[i] <= -2.0))
			{
				m_LaserTimeCounter[i] = (rand() % (m_MaxSecondsForLaser - m_MinSecondsForLaser + 1) + m_MinSecondsForLaser);
				m_LaserIsShootingBool[i] = false;
				m_LaserRectangles[i]->SetXPos(10000);
			}
			else if (m_LaserTimeCounter[i] <= 0.0)
			{
				m_LaserRectangles[i]->SetScale(1.0f, 1.0f);
				if (HandyMaths::minimum_distance(m_LaserIsShootingBottomPos[i], m_LaserIsShootingTopPos[i], m_pPlayer->GetPlayerPos()) < 35)
				{
					//m_pSoundManager->PlayExplosion();
					m_pPlayer->TakeDamage(1);
					m_pCamera->ScreenShake(0.1f);
				}
			}
			else
			{
				m_LaserIsShootingTopPos[i].y = m_pCamera->GetCameraPos().y + 5000;
				m_LaserIsShootingBottomPos[i].y = m_pCamera->GetCameraPos().y - 5000;
				m_LaserRectangles[i]->SetYPos(m_pCamera->GetCameraPos().y);
			}

			if (m_LaserIsShootingBool[i])
			{
				if (m_LaserIsShootingTopPos[i].x > m_LaserIsShootingBottomPos[i].x)
				{
					m_LaserRectangles[i]->SetXPos(m_LaserIsShootingBottomPos[i].x + ((m_LaserIsShootingTopPos[i].x - m_LaserIsShootingBottomPos[i].x) / 2));
				}
				else
				{
					m_LaserRectangles[i]->SetXPos(m_LaserIsShootingTopPos[i].x + ((m_LaserIsShootingBottomPos[i].x - m_LaserIsShootingTopPos[i].x) / 2));
				}
			}
			m_LaserRectangles[i]->SetRotationRadians(HandyMaths::LookAtVectorInRadians(m_LaserRectangles[i]->GetPos(), m_LaserIsShootingTopPos[i]));
		}
	}
}

void PickupManager::SpawnObjects()
{
	for (int i = 0; i < m_CoinAmount; ++i)
	{
		m_CoinRectangles[i] = new Rectangle(63, 63, 300, 0.0f + 130.0f * static_cast<float>(i), "res/textures/coins2.png", 5);
	}
	for (int i = 0; i < m_BombAmount; ++i)
	{
		m_BombRectangles[i] = new Rectangle(50, 57, -300, 0.0f + 130.0f * static_cast<float>(i), "res/textures/bomb.png", 4);
		m_ExplosionRectangles[i] = new Rectangle(129, 125, -3000, 0, "res/textures/explosion2.png", 3);
		m_BombDirections[i] = normalize(glm::vec2(m_pPlayer->GetPlayerPos() - m_BombRectangles[i]->GetPos()));
	}
	for (int i = 0; i < m_ZombieAmount; i++)
	{
		m_ZombieRectangles[i] = new Rectangle(64, 66, -300, 1500.0f + 170.0f * static_cast<float>(i), "res/textures/zombie.png", 6);
	}
	for (int i = 0; i < m_LaserAmount; i++)
	{
		m_LaserRectangles[i] = new Rectangle(7000, 100, -30000, 0, "res/textures/redLaser.png", 7);
		m_LaserTimeCounter[i] = (rand() % (m_MaxSecondsForLaser - m_MinSecondsForLaser + 1) + m_MinSecondsForLaser);
	}
}

PickupManager::PickupManager() : StandardObject(false, true, false, true, false, true,
	920, 920, 1020, 920)
{
	m_pCamera = &Camera::instance();
}

PickupManager::~PickupManager() = default;

void PickupManager::GivePlayerPointer(Player * p_player)
{
	m_pPlayer = p_player;
}