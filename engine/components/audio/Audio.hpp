//
// Created by hmkam on 04/12/2024.
//

#ifndef AUDIO_HPP
#define AUDIO_HPP
#include <cstdint>
#include <string>
#include <components/Component.hpp>

class AudioModule;

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

	std::string path;
	uint8_t volume;
	bool isLooping;
};

#endif //AUDIO_HPP
