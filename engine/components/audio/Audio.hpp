//
// Created by hmkam on 04/12/2024.
//

#ifndef AUDIO_HPP
#define AUDIO_HPP
#include <cstdint>
#include <map>
#include <string>
#include <components/Component.hpp>

class AudioModule;

struct AudioFragment {
	std::string path;
	uint8_t volume;
	bool isLooping;
};

class Audio : Component {
public:
	Audio(GameObject& gameObject, const char* tag);
	~Audio() override = default;

	void Start() override;
	void Update(float delta) override {};
	void End() override;

	std::map<std::string, AudioFragment> _audioPaths;
	// AudioFragment audioPaths;

private:
	friend AudioModule;
	void Play(const std::string& tag);
	void Stop(const std::string& tag);
};

#endif //AUDIO_HPP
