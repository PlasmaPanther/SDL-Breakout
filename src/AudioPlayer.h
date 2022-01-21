#pragma once
#include <SDL_mixer.h>
#include <map>
#include <string>

class AudioPlayer
{
public:
	AudioPlayer();
	~AudioPlayer();

	void PlayMusic(std::string filename, int loops);
	void PauseMusic();
	void ResumeMusic();

	void PlaySFX(std::string filename, int loops, int channel);

	static void SetVolume(int channel, int Volume);

	void FreeMusic();
	void FreeSFX();

private:
	Mix_Music* GetMusic(std::string filename);
	Mix_Chunk* GetSFX(std::string filename);

	std::map<std::string, Mix_Music*> m_MusicMap;
	std::map<std::string, Mix_Chunk*> m_SFX_Map;

};

