//
// Created by hmkam on 04/12/2024.
//

#include "Audio.hpp"

#include <iostream>
#include <moduleManager/ModuleManager.hpp>

#include "moduleManager/modules/audio/AudioModule.hpp"

Audio::Audio(GameObject& gameObject, const char* tag): Component(gameObject, tag) {}

void Audio::Play(const std::string& tag) {
	std::cout << "Play: " << tag << "\n";
}

void Audio::Stop(const std::string& tag) {
	std::cout << "Stop: " << tag << "\n";
}

void Audio::Start() {
	ModuleManager::getInstance()
		.getModule<AudioModule>().AddAudio(*this);
}

void Audio::End() {
	ModuleManager::getInstance()
		.getModule<AudioModule>().RemoveAudio(*this);
}
