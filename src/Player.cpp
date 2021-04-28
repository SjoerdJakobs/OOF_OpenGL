#include "Player.h"

void Player::Start()
{
	
}

void Player::Awake()
{
}

void Player::Sleep()
{
}

void Player::Destroy()
{
	StandardObject::Destroy();
}

void Player::Input(double deltaTime)
{
	m_Rectangle.DrawWithTexture();	
}

void Player::Update(double deltaTime)
{
	m_Rectangle.DrawWithTexture();
}

void Player::Render(double deltaTime)
{
	m_Rectangle.DrawWithTexture();
}

void Player::ImGuiRender(double deltaTime)
{
}

void Player::DebugRender(double deltaTime)
{
}
