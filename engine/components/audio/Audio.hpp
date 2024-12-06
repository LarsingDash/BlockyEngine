//
// Created by hmkam on 04/12/2024.
//

#ifndef AUDIO_HPP
#define AUDIO_HPP
#include <cstdint>
#include <string>
#include <components/Component.hpp>
#include <SDL_mixer.h>

class AudioModule;

struct AudioFragment {
	AudioFragment(std::string path, uint8_t volume, bool isLooping) : path(std::move(path)), volume(volume),
	                                                                  isLooping(isLooping) {}

	std::string path;
	Mix_Chunk* audioChunk{};
	int playingChannel{};
	uint8_t volume;
	bool isLooping;
};

class Audio : public Component {
public:
	Audio(GameObject& gameObject, const char* tag, const AudioFragment& fragment);
	Audio(GameObject& gameObject, const char* tag, std::string path, uint8_t volume, bool isLooping);
	~Audio() override = default;

	void Start() override;
	void Update(float delta) override {};
	void End() override;

private:
	friend AudioModule;
	int Play(int loops = 0);
	int Stop() const; // NOLINT(*-use-nodiscard)

	AudioFragment _fragment;
};

#endif //AUDIO_HPP
