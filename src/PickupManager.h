#pragma once
#include "StandardObject.h"
#include "HandyMaths.h"

class Player;
class Rectangle;
class Camera;
class SoundManager;

const int m_CoinAmount{ 8 };
const int m_BombAmount{ 6 };
const int m_ZombieAmount{ 4 };
const int m_LaserAmount{ 2 };

class PickupManager final : public StandardObject
{
public:

	PickupManager();

private:
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void OnDestroy() override;
	void Update(float deltaTime) override;
	void Render(float deltaTime) override;
	void UpdateObstacles(float deltaTime);
	void SpawnObjects();

	Camera* m_pCamera = nullptr;
	Player* m_pPlayer = nullptr;
	SoundManager* m_pSoundManager = nullptr;

	/* should all these things be managed in this place? not really
	 * do i have time to fix this right now? not really
	 * Todo: make pickup and obstacle classes
	 */
	Rectangle* m_CoinRectangles[m_CoinAmount] = {};

	Rectangle* m_ZombieRectangles[m_ZombieAmount] = {};

	Rectangle* m_BombRectangles[m_BombAmount] = {};
	glm::vec2 m_BombDirections[m_BombAmount] = {};
	Rectangle* m_ExplosionRectangles[m_BombAmount] = {};

	Rectangle* m_LaserRectangles[m_LaserAmount] = {};
	float m_LaserTimeCounter[m_LaserAmount] = {};
	bool m_LaserIsShootingBool[m_LaserAmount] = { false };
	glm::vec2 m_LaserIsShootingTopPos[m_LaserAmount] = {};
	glm::vec2 m_LaserIsShootingBottomPos[m_BombAmount] = {};

	/*
	 * especially here when i need to keep track of the animations, this should be in its own class
	 */
	bool m_BombIsExploding[m_BombAmount]{ false };
	float m_ExplosionFrameTimers[m_BombAmount]{ 0 };
	int m_FrameCountExplosion[m_BombAmount]{ 0 };

	float m_BaseBombMovementSpeed{ 350 };
	float m_CurrentBombMovementSpeed{};
	float m_BombMovementSpeedGrowthPerSecond{ 2 };

	int m_BeginFrameExplosion{ 1 };
	int m_EndFrameExplosion{ 24 };
	float m_TimeUntilNextExplosionFrame{ 0.03f };

	int m_FrameCountCoins{ 0 };
	int m_BeginFrameCoins{ 24 };
	int m_EndFrameCoins{ 48 };
	float m_TimeUntilNextCoinFrame{ 0.1f };
	float m_CoinFrameTimer{ 0.0f };

	int m_MinSecondsForLaser{ 2 };
	int m_MaxSecondsForLaser{ 4 };

public:
	~PickupManager() override;
	void GivePlayerPointer(Player* p_player);
};
