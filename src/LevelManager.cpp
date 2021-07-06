#include "LevelManager.h"
#include "Camera.h"
#include "Player.h"
#include "Rectangle.h"

LevelManager::LevelManager()
	: StandardObject(false, true, false, true, false,  true,
		910, 910, 910, 910)
{
	m_pCamera = &Camera::instance();
}

void LevelManager::Start()
{
	SpawnObjects();
}

void LevelManager::Awake()
{
}

void LevelManager::Sleep()
{
}

void LevelManager::OnDestroy()
{
	for (int i = 0; i < 2; ++i)
	{
		delete m_GroundRectangles[i];
	}
}

LevelManager::~LevelManager()
{
}

void LevelManager::Update(float deltaTime)
{
	MoveGround();
	ContainPlayer();
}

void LevelManager::Render(float deltaTime)
{
	for (int i = 0; i < 2; ++i)
	{
		m_GroundRectangles[i]->DrawWithTexture();
	}
}

void LevelManager::SpawnObjects()
{
	for (int i = 0; i < 2; ++i)
	{
		m_GroundRectangles[i] = new Rectangle(795.0f, 1000.0f, 0, 400.0f + 1000.0f * static_cast<float>(i), "res/textures/ground.png", 0);
	}
}

void LevelManager::MoveGround()
{
	for (auto& groundRectangle : m_GroundRectangles)
	{
		if (groundRectangle->GetYPos() - m_pCamera->GetCameraPos().y < -700)
		{
			groundRectangle->AddToYPos(1000.0f * 2);
		}
		else if (groundRectangle->GetYPos() - m_pCamera->GetCameraPos().y > 1400 && m_pPlayer->GetPlayerPos().y > 500)
		{
			groundRectangle->AddToYPos(-1000.0f * 2);
		}
	}
}

//this will be replaced with actual collision eventually, for now this will do the job and hopefully no one sees its all fake
void LevelManager::ContainPlayer() const
{
	if (m_pPlayer->GetPlayerPos().x > 370)
	{
		m_pPlayer->SetPlayerPos(glm::vec2(370, m_pPlayer->GetPlayerPos().y));
	}
	else if (m_pPlayer->GetPlayerPos().x < -370)
	{
		m_pPlayer->SetPlayerPos(glm::vec2(-370, m_pPlayer->GetPlayerPos().y));
	}
	if (m_pPlayer->GetPlayerPos().y < -45)
	{
		m_pPlayer->SetPlayerPos(glm::vec2(m_pPlayer->GetPlayerPos().x, -45));
	}
}

void LevelManager::GivePlayerPointer(Player* p_player)
{
	m_pPlayer = p_player;
}