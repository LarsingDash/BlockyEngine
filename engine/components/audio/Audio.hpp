//
// Created by hmkam on 04/12/2024.
//

#ifndef AUDIO_HPP
#define AUDIO_HPP
#include <cstdint>
#include <string>
#include <components/Component.hpp>
#include <SDL2_mixer/i686-w64-mingw32/include/SDL2/SDL_mixer.h> //todo: SDL_mixer.h

class AudioModule;

struct AudioFragment {
	AudioFragment(std::string path, uint8_t volume, bool isLooping) : path(std::move(path)), volume(volume),
	                                                                  isLooping(isLooping) {}

	AudioFragment(const AudioFragment&) = default;

	std::string path;
	Mix_Chunk* audioChunk{};
	int playingChannel{};
	uint8_t volume;
	bool isLooping;
	uint8_t numberOfInstances{};
};

class Audio : public Component {
public:
	Audio(GameObject* gameObject, const char* tag, std::string path, uint8_t volume, bool isLooping);
	~Audio() override = default;

	void Start() override;
	void Update(float delta) override {};
	void End() override;

	void Play(int loops = 0) const;
	void Stop() const; // NOLINT(*-use-nodiscard)

private:
	friend AudioModule;
	Component* _clone(const GameObject& parent) override;

	AudioFragment _fragment;
};

#endif //AUDIO_HPP
