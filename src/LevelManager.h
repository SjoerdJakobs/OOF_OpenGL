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

	Rectangle* m_GroundRectangles[2] = {};

	Camera* m_pCamera = nullptr;
	Player* m_pPlayer = nullptr;

public:
	~LevelManager() override;
	void GivePlayerPointer(Player* p_player);
protected:
};
