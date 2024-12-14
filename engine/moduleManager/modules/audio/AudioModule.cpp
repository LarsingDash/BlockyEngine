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

void AudioModule::RemoveAudio(const Audio& audio) {
	auto it = _audioPaths.find(audio.tag);
	if (it == _audioPaths.end()) {
		return;
	}

	it->second.numberOfInstances--;

	if (it->second.numberOfInstances <= 0) {
		// stop playing looping audio if all instances are removed, otherwise previous scene audio will keep playing
		if (!it->second.isLooping) { return; }
		for (auto itt : it->second.playingChannel) {
			StopAudio(audio.tag);
		}

		_audioPaths.erase(it);
	}
}

// to be able to stop looping audio don't call Play on the same tag with looping and non looping audio
void AudioModule::PlayAudio(const std::string& tag, int loops) {
	for (auto& [_tag, fragment] : _audioPaths) {
		if (tag != _tag) { continue; }
		if (fragment.isLooping) {
			loops = -1;
		}
		else {
			// to allow to stop non looping preemptively only the last started audio can be stopped.
			// see StopAudio() for more details
			fragment.playingChannel.clear();
		}
		fragment.playingChannel.push_back(Mix_PlayChannel(NO_CHANNEL_SPECIFIED, fragment.audioChunk, loops));
		return;
	}
}

// will only stop last started PlayAudio instance with this (unique)tag.
// when stop is called when not playing the sound, a random channel is stopped,
//	non looping audio chunk can only be stopped 1 time every PlayAudio.
// for looping audio of a (unique)tag can all be stopped FILO 1 instance per time
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
