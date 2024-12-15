//
// Created by hmkam on 04/12/2024.
//

#include "AudioModule.hpp"

#include <algorithm>
#include <SDL.h>
#include "logging/BLogger.hpp"
#include "components/audio/Audio.hpp"

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
	auto it = _audioPaths.find(audio.tag);
	if (it == _audioPaths.end()) {
		auto fragment = AudioFragment(
			audio.GetPath(),
			audio.GetVolume(),
			audio.GetIsLooping()
		);

		fragment.audioChunk = Mix_LoadWAV(fragment.path.c_str());

		if (nullptr == fragment.audioChunk) {
			std::string error = Mix_GetError();
			BLOCKY_ENGINE_ERROR("Could not AddAudio, error: " + error);
			return;
		}

		Mix_VolumeChunk(fragment.audioChunk, audio.GetVolume() / 2);
		fragment.numberOfInstances = 1;

		_audioPaths.emplace(std::pair(audio.tag, fragment));
	}
	else {
		it->second.numberOfInstances++;
	}
}

// Will stop audio where isLooping = true and all instances of audio.tag are removed, other audio will keep playing.
void AudioModule::RemoveAudio(const Audio& audio) {
	auto it = _audioPaths.find(audio.tag);
	if (it == _audioPaths.end()) {
		return;
	}

	it->second.numberOfInstances--;

	if (it->second.numberOfInstances <= 0) {
		for (auto itt : it->second.playingChannel) {
			StopAudio(audio.tag);
		}

		_audioPaths.erase(it);
	}
}

void AudioModule::PlayAudio(const std::string& tag, int loops) {
	for (auto& [_tag, fragment] : _audioPaths) {
		if (tag != _tag) { continue; }
		if (fragment.isLooping) {
			loops = -1;
			fragment.playingChannel.push_back(Mix_PlayChannel(NO_CHANNEL_SPECIFIED, fragment.audioChunk, loops));
		}
		else {
			Mix_PlayChannel(NO_CHANNEL_SPECIFIED, fragment.audioChunk, loops);
		}
		return;
	}
}

// Only audio fragment with isLooping = true can be stopped.
// Will only stop last started PlayAudio instance with this (unique)tag, (FILO 1 instance per time).
void AudioModule::StopAudio(const std::string& tag) {
	for (auto& [_tag, fragment] : _audioPaths) {
		if (tag != _tag) { continue; }

		if (fragment.playingChannel.empty()) {
			return;
		}

		Mix_HaltChannel(fragment.playingChannel.back());
		fragment.playingChannel.pop_back();
		return;
	}
}
