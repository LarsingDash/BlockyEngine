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

void AudioModule::PlayAudio(const std::string& tag) {
	for (auto& audio : _audioList) {
		for (auto& [_tag, fragment] : audio.get()._audioPaths) {
			if (_tag == tag) {
				audio.get().Play(tag);
				return;
			}
		}
	}
}

void AudioModule::StopAudio(const std::string& tag) {
	for (auto& audio : _audioList) {
		for (auto& [_tag, fragment] : audio.get()._audioPaths) {
			if (_tag == tag) {
				audio.get().Stop(tag);
				return;
			}
		}
	}
}
