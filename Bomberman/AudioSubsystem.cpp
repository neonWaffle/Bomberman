#include "AudioSubsystem.h"

void AudioSubsystem::PlayMusic(const std::string& title)
{
	soundEngine->play2D(sounds[title], true);
}

void AudioSubsystem::PlaySFX(const std::string& title)
{
	soundEngine->play2D(sounds[title], false);
}

void AudioSubsystem::StopAllAudio()
{
	soundEngine->stopAllSounds();
}

AudioSubsystem::AudioSubsystem()
{
	soundEngine = irrklang::createIrrKlangDevice();
}

void AudioSubsystem::AddSound(const std::string& title, const std::string& pathFile, float volume)
{
	auto sound = soundEngine->addSoundSourceFromFile(pathFile.c_str());
	sound->setDefaultVolume(volume);
	sounds.insert(std::make_pair(title, sound));
}

void AudioSubsystem::OnNotify(Event event)
{
	switch (event)
	{
	case Event::OPEN_MAIN_MENU:
		StopAllAudio();
		PlayMusic("mainMenuSong");
		break;
	case Event::START_GAME:
		StopAllAudio();
		PlayMusic("matchSong");
		break;
	case Event::PLAYER_DIED:
		StopAllAudio();
		PlayMusic("gameOverSong");
		break;
	case Event::BOMB_EXPLODED:
		PlaySFX("explosionSFX");
		break;
	case Event::OPEN_EDITOR:
		StopAllAudio();
		PlaySFX("tilemapEditorSong");
		break;
	}
}

void AudioSubsystem::Close()
{
	StopAllAudio();
}
