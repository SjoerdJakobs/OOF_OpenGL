#include "SoundManager.h"

void SoundManager::PlaySound(std::string SoundName)
{
}

void SoundManager::LoopSound(std::string SoundName)
{
}

void SoundManager::StopSound(std::string SoundName)
{
}

void SoundManager::AddSound(std::string SoundPath, std::string SoundName, int SoundChannel)
{
}

void SoundManager::PlayExplosion()
{
	result = m_pSystem->playSound(m_pExplosion, nullptr, false, &m_pChannel);
}

void SoundManager::PlayClick()
{
	result = m_pSystem->playSound(m_pClick, nullptr, false, &m_pChannel);
}

void SoundManager::PlayCoin()
{
	result = m_pSystem->playSound(m_pCoin, nullptr, false, &m_pChannel);
}

void SoundManager::StartBackgroundMusic1()
{
	result = m_pSystem->playSound(m_pBackground1, nullptr, false, &m_pChannel);
}

void SoundManager::StopBackgroundMusic1()
{
}

void SoundManager::StartBackgroundMusic2()
{
}

void SoundManager::StopBackgroundMusic2()
{
}

void SoundManager::Cleanup()
{
	result = m_pExplosion->release();
	result = m_pClick->release();
	result = m_pCoin->release();
	result = m_pBackground1->release();
	result = m_pBackground2->release();
	result = m_pSystem->close();
	result = m_pSystem->release();
}

SoundManager::SoundManager(int priority) :StandardObject(priority)
{
	//Start();
}

void SoundManager::Start()
{
	/*
		Create a System object and initialize
	*/
	result = FMOD::System_Create(&m_pSystem);

	result = m_pSystem->getVersion(&version);

	result = m_pSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);

	result = m_pSystem->createSound("res/sounds/drumloop.wav", FMOD_DEFAULT, 0, &m_pBackground1);

	//result = m_pBackground1->setMode(FMOD_LOOP_OFF);    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
												/* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */
	result = m_pSystem->createSound("res/sounds/coin.wav", FMOD_DEFAULT, 0, &m_pCoin);
	result = m_pSystem->createSound("res/sounds/click.wav", FMOD_DEFAULT, 0, &m_pClick);
	result = m_pSystem->createSound("res/sounds/boom.wav", FMOD_DEFAULT, 0, &m_pExplosion);

	//***************************************************
	//Sound
	//***************************************************
}

void SoundManager::Awake()
{
}

void SoundManager::Update(float deltaTime)
{
	m_pSystem->update();
}

void SoundManager::Sleep()
{
}

void SoundManager::OnDestroy()
{
	Cleanup();
}
