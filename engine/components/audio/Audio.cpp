//
// Created by hmkam on 04/12/2024.
//

#include "Audio.hpp"

#include "moduleManager/ModuleManager.hpp"
#include "moduleManager/modules/audio/AudioModule.hpp"

Audio::Audio(GameObject* gameObject,
             const char* tag,
             std::string path,
             bool isLooping,
             audio_type type) : Component(gameObject, tag),
                                _path(std::move(path)),
                                _isLooping(isLooping),
                                _type(type) {}

void Audio::Play(int loops) const {
	ModuleManager::GetInstance().GetModule<AudioModule>().PlayAudio(tag, loops);
}

// Only audio fragment with isLooping = true can be stopped.
// Will only stop last started PlayAudio instance with this (unique)tag, (FILO 1 instance per time).
void Audio::Stop() const {
	ModuleManager::GetInstance().GetModule<AudioModule>().StopAudio(tag);
}

Component* Audio::_clone(const GameObject& parent) {
	auto clone = new Audio(*this);
	return clone;
}

void Audio::Start() {
	ModuleManager::GetInstance().GetModule<AudioModule>().AddAudio(*this);
}

void Audio::End() {
	ModuleManager::GetInstance().GetModule<AudioModule>().RemoveAudio(*this);
}
