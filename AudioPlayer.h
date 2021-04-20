#pragma once

#include <SDL_mixer.h>
#include <SDL.h>
class AudioPlayer
{
private:
	Mix_Music* sound = nullptr;

	AudioPlayer() {}
	AudioPlayer(const AudioPlayer&) = delete;
	AudioPlayer& operator=(const AudioPlayer&) = delete;

public:
	enum class AudioErrorType { ERR_INIT_AUDIO, ERR_OPEN_AUDIO, ERR_LOAD_AUDIO };
		
	~AudioPlayer();

	// Returns the ONLY instance of AudioPlayer that can exist to handle SDL music player
	static AudioPlayer& getInstance() {
		static AudioPlayer audioInst;
		return audioInst;
	}

	// Initializes SDL methods
	void init(int sampleRate, int channels, int chunkSize);

	// Loads SDL Mixer with the audio to play
	void loadAudio(const char* filename);

	// Plays the audio previously loaded into SDL Mixer
	void playAudio(int loops = 1);

	// Pauses the audio
	void pauseAudio();

	// Resumes the audio
	void resumeAudio();
};

