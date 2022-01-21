#include "AudioPlayer.h"
#include <SDL.h>

AudioPlayer::AudioPlayer() {

	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		printf("Audio could not initialize %s\n", SDL_GetError());
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		printf("Mixer could not initialize %s\n", Mix_GetError());
	}
}

AudioPlayer::~AudioPlayer() {

	for (auto& music : m_MusicMap) {
		if (music.second) {
			Mix_FreeMusic(music.second);
			music.second = nullptr;
			printf("Music closed\n");
		}
	}
	m_MusicMap.clear();
	

	for (auto& sfx : m_SFX_Map) {
		if (sfx.second) {
			Mix_FreeChunk(sfx.second);
			sfx.second = nullptr;
			printf("sfx closed\n");
		}
	}
	m_SFX_Map.clear();

	Mix_Quit();
}

Mix_Music* AudioPlayer::GetMusic(std::string filename) {
	std::string basepath = "Resources/Sounds/" + filename;

	Mix_Music* Music = nullptr;

	if (m_MusicMap[basepath] == nullptr) {
		m_MusicMap[basepath] = Music = Mix_LoadMUS(basepath.c_str());

		if (m_MusicMap[basepath] == nullptr) {
			printf("Could not load file %s\n", Mix_GetError());
		}
	}

	return m_MusicMap[basepath];
}

Mix_Chunk* AudioPlayer::GetSFX(std::string filename) {
	std::string basepath = "Resources/Sounds/" + filename;

	Mix_Chunk* SFX = nullptr;

	if (m_SFX_Map[basepath] == nullptr) {
		m_SFX_Map[basepath] = SFX =  Mix_LoadWAV(basepath.c_str());

		if (m_SFX_Map[basepath] == nullptr) {
			printf("Could not load file %s\n", Mix_GetError());
		}
	}

	return m_SFX_Map[basepath];
}

void AudioPlayer::PlayMusic(std::string file, int loops)
{
	Mix_PlayMusic(this->GetMusic(file), loops);
}

void AudioPlayer::PauseMusic() {
	if (Mix_PlayingMusic != 0) {
		Mix_PauseMusic();
	}
}

void AudioPlayer::ResumeMusic() {
	if (Mix_PausedMusic() != 0) {
		Mix_ResumeMusic();
	}
}

void AudioPlayer::PlaySFX(std::string file, int loops, int channel)
{
	Mix_PlayChannel(channel, this->GetSFX(file), loops);
}

void AudioPlayer::SetVolume(int channel, int Volume) {
	Mix_Volume(channel, Volume);
}

void AudioPlayer::FreeMusic() {
	if (!m_MusicMap.empty()) { //check to see if the map is empty
		Mix_FreeMusic(m_MusicMap.crbegin()->second);
		m_MusicMap.rbegin()->second = nullptr;

		m_MusicMap.erase(m_MusicMap.crbegin()->first);
		printf("music freed\n");
	}
}

void AudioPlayer::FreeSFX() {
	if (!m_SFX_Map.empty()) {
		Mix_FreeChunk(m_SFX_Map.crbegin()->second);
		m_SFX_Map.rbegin()->second = nullptr;

		m_SFX_Map.erase(m_SFX_Map.crbegin()->first);
		printf("sfx freed\n");
	}
}