#pragma once
#include "StandardObject.h"
#include "fmod.hpp"
#include <string>
#include <map>
/************************************************************************************************************************************
/
/
/												not finished but in use in the current build, WIP
/
/
*/
class SoundManager final : public StandardObject
{
public:
	static SoundManager& instance()
	{
		static SoundManager* p_instance = new SoundManager(1000);
		return *p_instance;
	}

	void PlaySound(std::string SoundName);
	void LoopSound(std::string SoundName);
	void StopSound(std::string SoundName);
	void AddSound(std::string SoundPath, std::string SoundName, int SoundChannel);

	//temp sound functions
	void PlayExplosion();
	void PlayClick();
	void PlayCoin();
	void StartBackgroundMusic1();
	void StopBackgroundMusic1();
	void StartBackgroundMusic2();
	void StopBackgroundMusic2();

	void Cleanup();
private:

	FMOD::System* m_pSystem;
	FMOD::Sound* m_pExplosion;
	FMOD::Sound* m_pClick;
	FMOD::Sound* m_pCoin;
	FMOD::Sound* m_pBackground1;
	FMOD::Sound* m_pBackground2;
	FMOD::Channel* m_pChannel = 0;
	FMOD_RESULT       result;
	unsigned int      version;
	void* extradriverdata = 0;

	SoundManager(int priority);
	SoundManager(SoundManager const&) {}            // copy constructor is private
	SoundManager& operator=(SoundManager const&) {} // assignment operator is private

	// Inherited via StandardObject
	virtual void Start() override;

	virtual void Awake() override;

	void Update(float deltaTime) override;

	virtual void Sleep() override;

	virtual void OnDestroy() override;
};

struct Sound
{
	int channel;
	std::string soundName;
	std::string soundPath;
};
