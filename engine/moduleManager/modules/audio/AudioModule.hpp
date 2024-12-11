//
// Created by hmkam on 04/12/2024.
//

#ifndef AUDIOMODULE_HPP
#define AUDIOMODULE_HPP
#include <map>
#include <SDL_mixer.h>
#include <string>
#include <components/audio/Audio.hpp>
#include <moduleManager/ModuleWrapper.hpp>

struct AudioFragment {
	AudioFragment(std::string path, uint8_t volume, bool isLooping) : path(std::move(path)), volume(volume),
	                                                                  isLooping(isLooping) {}

	std::string path;
	uint8_t volume;
	bool isLooping;
	Mix_Chunk* audioChunk{};
	int playingChannel{};
	uint8_t numberOfInstances{};
};

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
