#pragma once

#include "Subsystem.h"

#include <irrKlang.h>

class AudioSubsystem : public Subsystem
{
private:
	irrklang::ISoundEngine* soundEngine;
	std::unordered_map<std::string, irrklang::ISoundSource*> sounds;

	void PlayMusic(const std::string& title);
	void PlaySFX(const std::string& title);
	void StopAllAudio();
public:
	AudioSubsystem();
	
	void AddSound(const std::string& title, const std::string& pathFile, float volume = 1);
	void OnNotify(Event event) override;
	void Close() override;
};

