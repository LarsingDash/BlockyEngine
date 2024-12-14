//
// Created by hmkam on 04/12/2024.
//

#include "Audio.hpp"

#include <moduleManager/ModuleManager.hpp>
#include "moduleManager/modules/audio/AudioModule.hpp"

Audio::Audio(GameObject* gameObject, const char* tag, std::string path, uint8_t volume, bool isLooping) :
	Component(gameObject, tag), _path(std::move(path)), _volume(volume), _isLooping(isLooping) {}

// to be able to stop looping audio don't call Play on the same tag with looping and non looping audio
void Audio::Play(int loops) const {
	ModuleManager::GetInstance().GetModule<AudioModule>().PlayAudio(tag, loops);
}

// will only stop last started PlayAudio instance with this Audio.(unique)tag.
// when stop is called when not playing the sound, a random channel is stopped,
//	non looping audio chunk can only be stopped 1 time every PlayAudio.
// for looping audio of a (unique)tag can all be stopped FILO 1 instance per time
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
