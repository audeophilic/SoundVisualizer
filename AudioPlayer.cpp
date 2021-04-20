#include "AudioPlayer.h"
AudioPlayer::~AudioPlayer() {
	if (sound) Mix_FreeMusic(sound);
	Mix_Quit();
}

void AudioPlayer::init(int sampleRate, int channels, int chunkSize ) {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) throw AudioErrorType::ERR_INIT_AUDIO;
	if (Mix_OpenAudio(sampleRate, MIX_DEFAULT_FORMAT, channels, chunkSize) < 0)
		throw AudioErrorType::ERR_OPEN_AUDIO;
}

void AudioPlayer::loadAudio(const char* filename) {
	sound = Mix_LoadMUS(filename);
	if (!sound) throw AudioErrorType::ERR_LOAD_AUDIO;
}

void AudioPlayer::playAudio(int loops) {
	Mix_PlayMusic(sound, loops);
}

void AudioPlayer::pauseAudio() {
	Mix_PauseMusic();
}

void AudioPlayer::resumeAudio() {
	Mix_ResumeMusic();
}