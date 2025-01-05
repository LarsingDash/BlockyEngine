//
// Created by hmkam on 04/12/2024.
//

#ifndef AUDIOMODULE_HPP
#define AUDIOMODULE_HPP
#include <map>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <components/audio/Audio.hpp>
#include <moduleManager/ModuleWrapper.hpp>

constexpr int NO_CHANNEL_SPECIFIED = -1;

struct AudioFragment {
	AudioFragment(std::string path, bool isLooping, audio_type type) : path(std::move(path)),
	                                                                   isLooping(isLooping), type(type) {}

	std::string path;
	bool isLooping;
	audio_type type;
	Mix_Chunk* audioChunk{};
	std::vector<int> playingChannel{};
	uint8_t numberOfInstances{};
};

class AudioModule : public ModuleWrapper {
	public:
		AudioModule();
		~AudioModule() override = default;

		void Update(float delta) override {};

		void AddAudio(const Audio& audio);
		void RemoveAudio(const Audio& audio);
		void SetVolume(audio_type type, int volume);

		void PlayAudio(const std::string& tag, int loops);
		void StopAudio(const std::string& tag);

	private:
		std::map<std::string, AudioFragment> _audioPaths{};
		std::map<audio_type, uint8_t> _audioVolume;

		static void _setVolume(Mix_Chunk* audioChunk, int volume);
};

#endif //AUDIOMODULE_HPP
