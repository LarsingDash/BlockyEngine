//
// Created by hmkam on 04/12/2024.
//

#include "AudioModule.hpp"

#include <algorithm>

#include "components/audio/Audio.hpp"

void AudioModule::AddAudio(Audio& audio) {
	_audioList.emplace_back(audio);
}

void AudioModule::RemoveAudio(const Audio& audio) {
	auto it = std::find_if(_audioList.begin(), _audioList.end(),
	                       [&audio](const std::reference_wrapper<Audio>& other) {
		                       return &audio == &other.get();
	                       });

	if (it != _audioList.end()) {
		_audioList.erase(it);
	}
}

void AudioModule::PlayAudio(const std::string& tag) const {
	for (auto& audio : _audioList) {
		if (tag == audio.get().tag) {
			audio.get().Play();
			return;
		}
	}
}

void AudioModule::StopAudio(const std::string& tag) const {
	for (auto& audio : _audioList) {
		if (tag == audio.get().tag) {
			audio.get().Stop();
			return;
		}
	}
}
