//
// Created by hmkam on 04/12/2024.
//

#include "Audio.hpp"

#include <moduleManager/ModuleManager.hpp>
#include <logging/BLogger.hpp>
#include "moduleManager/modules/audio/AudioModule.hpp"
#include <SDL.h>

constexpr int NO_CHANNEL_SPECIFIED = -1;

Audio::Audio(GameObject& gameObject, const char* tag, std::string path, uint8_t volume, bool isLooping):
	Component(gameObject, tag), _fragment(std::move(path), volume, isLooping) {}

void Audio::Play(int loops) const {
	BLOCKY_ENGINE_DEBUG("Play: " + tag + " loops: " + std::to_string(loops));

	ModuleManager::getInstance().getModule<AudioModule>().PlayAudio(tag, loops);
}

void Audio::Stop() const {
	BLOCKY_ENGINE_DEBUG("Stop: " + tag);

	ModuleManager::getInstance().getModule<AudioModule>().StopAudio(tag);
}

void Audio::Start() {
	ModuleManager::getInstance().getModule<AudioModule>().AddAudio(*this);
}

void Audio::End() {
	ModuleManager::getInstance().getModule<AudioModule>().RemoveAudio(*this);
}
