//
// Created by hmkam on 04/12/2024.
//

#include "Audio.hpp"

#include <iostream>
#include <moduleManager/ModuleManager.hpp>
#include <utility>
#include <logging/BLogger.hpp>

#include "moduleManager/modules/audio/AudioModule.hpp"

Audio::Audio(GameObject& gameObject, const char* tag, AudioFragment fragment) : Component(gameObject, tag),
	_fragment(std::move(fragment)) {}

Audio::Audio(GameObject& gameObject, const char* tag, std::string path, uint8_t volume, bool isLooping):
	Component(gameObject, tag), _fragment(std::move(path), volume, isLooping) {}

//todo:
// Audio::Audio(GameObject& gameObject, const char* tag, std::string fileLocation): Component(gameObject, tag),
// 	_fileLocation(std::move(fileLocation)) {}

void Audio::Play() {
	BLOCKY_ENGINE_DEBUG("Play: " + tag + " " + _fragment.path);
}

void Audio::Stop() {
	BLOCKY_ENGINE_DEBUG("Stop: " + tag + " " + _fragment.path);
}

void Audio::Start() {
	ModuleManager::getInstance()
		.getModule<AudioModule>().AddAudio(*this);
}

void Audio::End() {
	ModuleManager::getInstance()
		.getModule<AudioModule>().RemoveAudio(*this);
}
