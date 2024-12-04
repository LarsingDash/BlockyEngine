//
// Created by hmkam on 04/12/2024.
//

#ifndef AUDIOMODULE_HPP
#define AUDIOMODULE_HPP
#include <string>
#include <vector>
#include <moduleManager/ModuleWrapper.hpp>

class Audio;

class AudioModule : public ModuleWrapper {
public:
	AudioModule() = default;
	~AudioModule() override = default;

	void Update(float delta) override {};

	void AddAudio(Audio& audio);
	void RemoveAudio(const Audio& audio);

	void PlayAudio(const std::string& tag);
	void StopAudio(const std::string& tag);

private:
	std::vector<std::reference_wrapper<Audio>> _audioList;
};

#endif //AUDIOMODULE_HPP
