#pragma once
#include "StandardObject.h"

class Player;
class Rectangle;
class Camera;

class LevelManager final : public StandardObject
{
public:
	LevelManager();

private:
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void OnDestroy() override;
	void Update(float deltaTime) override;
	void Render(float deltaTime) override;

	void SpawnObjects();
	void MoveGround();
	void ContainPlayer() const;
	void UpdateObstacles(float deltaTime);

	Rectangle* m_GroundRectangles[2] = {};

	
	/* should all these things be managed in this place? not really
	 * do i have time to fix this right now? not really
	 * Todo: make pickup and obstacle classes
	 */
	Rectangle* m_CoinRectangles[8] = {};
	Rectangle* m_BombRectangles[8] = {};
	Rectangle* m_ExplosionRectangles[8] = {};
	Camera*	   m_pCamera;
	Player*    m_pPlayer = nullptr;//to remove warning

public:
	~LevelManager() override;
	void GivePlayerPointer(Player* p_player);
protected:
};

