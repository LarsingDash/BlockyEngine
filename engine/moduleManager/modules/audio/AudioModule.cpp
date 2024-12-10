//
// Created by hmkam on 04/12/2024.
//

#include "AudioModule.hpp"

#include <algorithm>
#include <SDL.h>
#include <logging/BLogger.hpp>

#include "components/audio/Audio.hpp" //todo: audio.hpp
constexpr int NO_CHANNEL_SPECIFIED = -1;

AudioModule::AudioModule() {
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
}

void AudioModule::AddAudio(const Audio& audio) {
	BLOCKY_ENGINE_DEBUG("AddAudio: " + audio.tag + " " + audio._fragment.path);
	auto it = _audioPaths.find(audio.tag);
	if (it == _audioPaths.end()) {
		_audioPaths.emplace(std::pair<std::string, AudioFragment>(audio.tag, audio._fragment));
		_audioPaths.at(audio.tag).audioChunk = Mix_LoadWAV(audio._fragment.path.c_str());

		_audioPaths.at(audio.tag).numberOfInstances = 1;

		if (nullptr == _audioPaths.at(audio.tag).audioChunk) {
			std::string error = Mix_GetError();
			BLOCKY_ENGINE_ERROR("Could not AddAudio, error: " + error);
			return;
		}
	}
	else {
		it->second.numberOfInstances++;
	}
}

void AudioModule::RemoveAudio(const Audio& audio) {
	BLOCKY_ENGINE_DEBUG("RemoveAudio: " + audio.tag + " " + audio._fragment.path);
	auto it = _audioPaths.find(audio.tag);
	if (it == _audioPaths.end()) {
		return;
	}

	it->second.numberOfInstances--;

	if (it->second.numberOfInstances <= 0) {
		_audioPaths.erase(it);
	}
}

void AudioModule::PlayAudio(const std::string& tag, int loops) {
	for (auto& [_tag,fragment] : _audioPaths) {
		if (tag != _tag) { continue; }
		if (fragment.isLooping) { loops = -1; }

		fragment.playingChannel = Mix_PlayChannel(NO_CHANNEL_SPECIFIED, fragment.audioChunk, loops);
		return;
	}
}

// when using stop, specify unique tag, so when stop is called right (only)instance of tag is stopped.
// when stop is called when not playing the sound, a random channel is stopped.
void AudioModule::StopAudio(const std::string& tag) {
	for (auto& [_tag, fragment] : _audioPaths) {
		if (tag != _tag) { continue; }

		if (fragment.playingChannel == NO_CHANNEL_SPECIFIED) {
			return;
		}

		Mix_HaltChannel(fragment.playingChannel);
		fragment.playingChannel = NO_CHANNEL_SPECIFIED;
		return;
	}
}
