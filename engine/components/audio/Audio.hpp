//
// Created by hmkam on 04/12/2024.
//

#ifndef AUDIO_HPP
#define AUDIO_HPP
#include <cstdint>
#include <string>
#include <components/Component.hpp>
#include <utility>

class AudioModule;

struct AudioFragment {
	AudioFragment(std::string path, uint8_t volume, bool isLooping) : path(std::move(path)), volume(volume),
	                                                                  isLooping(isLooping) {}

	std::string path;
	uint8_t volume;
	bool isLooping;
};

class Audio : public Component {
public:
	Audio(GameObject& gameObject, const char* tag, AudioFragment fragment);
	Audio(GameObject& gameObject, const char* tag, std::string path, uint8_t volume, bool isLooping);
	~Audio() override = default;

	void Start() override;
	void Update(float delta) override {};
	void End() override;

private:
	friend AudioModule;
	void Play();
	void Stop();

	AudioFragment _fragment;
};

#endif //AUDIO_HPP
