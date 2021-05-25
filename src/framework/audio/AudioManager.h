#pragma once
#include <glm/glm.hpp>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	float DBToVolume(float dB)
	{
		return powf(10.0f, 0.05f * dB);
	}

	float VolumeToDB(float volume)
	{
		return 20.0f * log10f(volume);
	}
};

