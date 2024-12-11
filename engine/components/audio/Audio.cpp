//
// Created by hmkam on 04/12/2024.
//

#include "Audio.hpp"

#include <moduleManager/ModuleManager.hpp>
#include "moduleManager/modules/audio/AudioModule.hpp"

Audio::Audio(GameObject* gameObject, const char* tag, std::string path, uint8_t volume, bool isLooping) :
		Component(gameObject, tag), _path(std::move(path)), _volume(volume), _isLooping(isLooping) {}

void Audio::Play(int loops) const {
	ModuleManager::GetInstance().GetModule<AudioModule>().PlayAudio(tag, loops);
}

// will only stop last instance with this (unique)tag.
// when stop is called when not playing the sound, a random channel is stopped,
//	only audio that is started after this one has finished may stop playing.
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
