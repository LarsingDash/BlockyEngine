//
// Created by hmkam on 04/12/2024.
//

#include "Audio.hpp"

#include <moduleManager/ModuleManager.hpp>
#include <logging/BLogger.hpp>
#include "moduleManager/modules/audio/AudioModule.hpp"
#include <SDL.h>

constexpr int NO_CHANNEL_SPECIFIED = -1;

Audio::Audio(GameObject& gameObject, const char* tag, const AudioFragment& fragment) : Audio(
	gameObject, tag, fragment.path, fragment.volume, fragment.isLooping) {}

Audio::Audio(GameObject& gameObject, const char* tag, std::string path, uint8_t volume, bool isLooping):
	Component(gameObject, tag), _fragment(std::move(path), volume, isLooping) {
	constexpr int flags = MIX_INIT_MP3;

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		BLOCKY_ENGINE_ERROR("Failed to init SDL\n");
		return;
	}

	if (flags != Mix_Init(flags)) {
		std::string error = Mix_GetError();
		BLOCKY_ENGINE_ERROR("Could not initialize mixer: " + error);
		return;
	}

	if (-1 == Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640)) {
		std::string error = Mix_GetError();
		BLOCKY_ENGINE_ERROR("Could not Mix_OpenAudio: " + error);
		return;
	}

	_fragment.audioChunk = Mix_LoadWAV(_fragment.path.c_str());
	if (nullptr == _fragment.audioChunk) {
		std::string error = Mix_GetError();
		BLOCKY_ENGINE_ERROR("Could not Mix_LoadWAV: " + error);
		return;
	}
}

// If `loops` is greater than zero, loop the sound that many times. If `loops` is -1, loop "infinitely" (~65000 times).
// which channel was used to play the sound, or -1 if sound could not be played.
int Audio::Play(int loops) {
	BLOCKY_ENGINE_DEBUG("Play: " + tag + " " + _fragment.path + " loops: " + std::to_string(loops));

	_fragment.playingChannel = Mix_PlayChannel(NO_CHANNEL_SPECIFIED, _fragment.audioChunk, loops);
	return _fragment.playingChannel;
}

// return 0 on success, or -1 on error.
int Audio::Stop() const {
	BLOCKY_ENGINE_DEBUG("Stop: " + tag + " " + _fragment.path);

	if (_fragment.playingChannel == NO_CHANNEL_SPECIFIED) {
		return -1;
	}

	return Mix_HaltChannel(_fragment.playingChannel);
}

void Audio::Start() {
	ModuleManager::getInstance().getModule<AudioModule>().AddAudio(*this);
}

void Audio::End() {
	ModuleManager::getInstance().getModule<AudioModule>().RemoveAudio(*this);
}
