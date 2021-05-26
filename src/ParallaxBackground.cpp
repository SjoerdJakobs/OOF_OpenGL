#include "ParallaxBackground.h"
#include "Program.h"
#include "Camera.h"
#include "Rectangle.h"

ParallaxBackground::ParallaxBackground() : StandardObject(false, true, false, true, true, false, true, 900, 900, 900, 900)
{
	m_pCamera = &Camera::instance();
	SpawnLayers();
	m_LastCameraPos = m_pCamera->GetCameraPos();
}

void ParallaxBackground::SpawnLayers()
{
	int n = 0;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			m_Layer1Rectangles[n] = DBG_NEW Rectangle(1536.0f, 1536.0f, -768.0f + 1536.0f * static_cast<float>(i), -768.0f + 1536.0f * static_cast<float>(j), "res/textures/backgroundSpace1.png", 9);
			n++;
		}
	}

	m_Layer2Rectangles[0] = DBG_NEW Rectangle(500.0f, 500.0f, -768.0f , -768.0f , "res/textures/jupiter-transparent.png", 8);
	m_Layer2Rectangles[1] = DBG_NEW Rectangle(480.0f*0.7, 360.0f*0.7, -768.0f + 1536.0f, -768.0f , "res/textures/mars.png", 8);
	m_Layer2Rectangles[2] = DBG_NEW Rectangle(400.0f, 400.0f, -768.0f , -768.0f + 1536.0f , "res/textures/mercury-transparent.png", 8);
	m_Layer2Rectangles[3] = DBG_NEW Rectangle(450.0f, 450.0f, -768.0f + 1536.0f , -768.0f + 1536.0f , "res/textures/venus-transparent.png", 8);

	
	m_Layer3Rectangles[0] = DBG_NEW Rectangle(1314.0f*0.3f, 870.0f*0.3f, -0, -768.0f + 1536.0f, "res/textures/transparent-star-background-2.png", 7);
	m_Layer3Rectangles[1] = DBG_NEW Rectangle(1314.0f*0.7f, 870.0f*0.6f, -768.0f, -768.0f + 1536.0f, "res/textures/transparent-star-background-2.png", 7);
	m_Layer3Rectangles[2] = DBG_NEW Rectangle(1314.0f, 870.0f, -768.0f + 1236.0f, -200.0f, "res/textures/transparent-star-background-2.png", 7);
	m_Layer3Rectangles[3] = DBG_NEW Rectangle(1314.0f*0.5f, 870.0f*0.5f, -700, 900, "res/textures/transparent-star-background-2.png", 7);
		
}

void ParallaxBackground::MoveLayers(float deltaTime)
{
	const glm::vec2 moveAmount = m_pCamera->GetCameraPos() - m_LastCameraPos;
	m_LastCameraPos = m_pCamera->GetCameraPos();
	MoveLayer1(moveAmount, deltaTime);
	MoveLayer2(moveAmount, deltaTime);
	MoveLayer3(moveAmount, deltaTime);
}

void ParallaxBackground::MoveLayer1(glm::vec2 moveAmount, float deltaTime)
{
	const glm::vec2 calculatedAmount = glm::vec2(moveAmount * m_Layer1SpeedMod + glm::vec2(1, 0) * (m_Layer2BaseSpeed * deltaTime));

	for (auto& layer1Rectangle : m_Layer1Rectangles)
	{
		layer1Rectangle->AddToPos(calculatedAmount);

		if (layer1Rectangle->GetXPos() - m_pCamera->GetCameraPos().x < -800)
		{
			layer1Rectangle->AddToXPos(1536.0f * 2);
		}
		else if (layer1Rectangle->GetXPos() - m_pCamera->GetCameraPos().x > 2100)
		{
			layer1Rectangle->AddToXPos(-1536.0f * 2);
		}

		if (layer1Rectangle->GetYPos() - m_pCamera->GetCameraPos().y < -800)
		{
			layer1Rectangle->AddToYPos(1536.0f * 2);
		}
		else if (layer1Rectangle->GetYPos() - m_pCamera->GetCameraPos().y > 2100)
		{
			layer1Rectangle->AddToYPos(-1536.0f * 2);
		}
	}
}

void ParallaxBackground::MoveLayer2(glm::vec2 moveAmount, float deltaTime)
{
	const glm::vec2 calculatedAmount = glm::vec2(moveAmount * m_Layer2SpeedMod) + glm::vec2(1,1) * (m_Layer2BaseSpeed*deltaTime);

	for (auto& layer2Rectangle : m_Layer2Rectangles)
	{
		layer2Rectangle->AddToPos(-calculatedAmount);

		if (layer2Rectangle->GetXPos() - m_pCamera->GetCameraPos().x < -800)
		{
			layer2Rectangle->AddToXPos(1536.0f * 2);
		}
		else if (layer2Rectangle->GetXPos() - m_pCamera->GetCameraPos().x > 2100)
		{
			layer2Rectangle->AddToXPos(-1536.0f * 2);
		}

		if (layer2Rectangle->GetYPos() - m_pCamera->GetCameraPos().y < -800)
		{
			layer2Rectangle->AddToYPos(1536.0f * 2);
		}
		else if (layer2Rectangle->GetYPos() - m_pCamera->GetCameraPos().y > 2100)
		{
			layer2Rectangle->AddToYPos(-1536.0f * 2);
		}
	}
}

void ParallaxBackground::MoveLayer3(glm::vec2 moveAmount, float deltaTime)
{
	const glm::vec2 calculatedAmount = glm::vec2(moveAmount * m_Layer3SpeedMod) + glm::vec2(1, 1) * (m_Layer3BaseSpeed * deltaTime);

	for (auto& layer3Rectangle : m_Layer3Rectangles)
	{
		layer3Rectangle->AddToPos(-calculatedAmount);

		if (layer3Rectangle->GetXPos() - m_pCamera->GetCameraPos().x < -800)
		{
			layer3Rectangle->AddToXPos(1536.0f * 2);
		}
		else if (layer3Rectangle->GetXPos() - m_pCamera->GetCameraPos().x > 2100)
		{
			layer3Rectangle->AddToXPos(-1536.0f * 2);
		}

		if (layer3Rectangle->GetYPos() - m_pCamera->GetCameraPos().y < -800)
		{
			layer3Rectangle->AddToYPos(1536.0f * 2);
		}
		else if (layer3Rectangle->GetYPos() - m_pCamera->GetCameraPos().y > 2100)
		{
			layer3Rectangle->AddToYPos(-1536.0f * 2);
		}
	}
}

void ParallaxBackground::Start()
{
}

void ParallaxBackground::Awake()
{
}

void ParallaxBackground::Sleep()
{
}

void ParallaxBackground::OnDestroy()
{
	for (int i = 0; i < 4; ++i)
	{
		m_Layer1Rectangles[i]->CleanUp();
		delete m_Layer1Rectangles[i];
	}
}

void ParallaxBackground::Update(float deltaTime)
{
	MoveLayers(deltaTime);
}

void ParallaxBackground::Render(float deltaTime)
{
	for (int i = 0; i < 4; ++i)
	{
		m_Layer1Rectangles[i]->DrawWithTexture();
	}
	for (int i = 0; i < 4; ++i)
	{
		m_Layer3Rectangles[i]->DrawWithTexture();
	}
	//Todo: make layer 2 layer 3
	for (int i = 0; i < 4; ++i)
	{
		m_Layer2Rectangles[i]->DrawWithTexture();
	}
}

void ParallaxBackground::ImGuiRender(float deltaTime)
{
	ImGui::Begin("MainMenu");

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);                   // Create a m_pWindow called "Hello, world!" and append into it.
		
	for (int i = 0; i < 1; ++i)
	{
		ImGui::Text("background1 x %.2f", static_cast<float>( m_Layer1Rectangles[i]->GetXPos()-(m_pCamera->GetCameraPos().x)));
		ImGui::Text("background2 x %.2f", static_cast<float>(m_pCamera->GetCameraPos().x - m_Layer1Rectangles[i]->GetXPos()));
		ImGui::Text("background y %.2f", static_cast<float>(m_Layer1Rectangles[i]->GetXPos()));
		ImGui::Text("background y %.2f", static_cast<float>(m_Layer1Rectangles[i]->GetYPos()));
		
	}

	ImGui::End();
}

ParallaxBackground::~ParallaxBackground()
{
}
