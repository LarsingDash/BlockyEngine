//
// Created by hmkam on 04/12/2024.
//

#ifndef AUDIOMODULE_HPP
#define AUDIOMODULE_HPP
#include <map>
#include <string>
// #include <Audio.hpp>//todo: Audio.hpp
#include <components/audio/Audio.hpp>
#include <moduleManager/ModuleWrapper.hpp>

class AudioModule : public ModuleWrapper {
public:
	AudioModule();
	~AudioModule() override = default;

	void Update(float delta) override {};

	void AddAudio(const Audio& audio);
	void RemoveAudio(const Audio& audio);

	void PlayAudio(const std::string& tag, int loops);
	void StopAudio(const std::string& tag);

private:
	std::map<std::string, AudioFragment> _audioPaths;
};

#endif //AUDIOMODULE_HPP
