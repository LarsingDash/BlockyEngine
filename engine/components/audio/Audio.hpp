//
// Created by hmkam on 04/12/2024.
//

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <components/Component.hpp>

enum audio_type {
	MUSIC,
	SOUND_EFFECT
};

class Audio : public Component {
	public:
		Audio(GameObject* gameObject, const char* tag, std::string path, bool isLooping = false,
		      audio_type type = SOUND_EFFECT);
		~Audio() override = default;

		void Start() override;
		void Update(float delta) override {};
		void End() override;

		void Play(int loops = 0) const;
		void Stop() const;

		[[nodiscard]] inline const std::string& GetPath() const { return _path; }
		[[nodiscard]] inline bool GetIsLooping() const { return _isLooping; }
		[[nodiscard]] inline audio_type GetType() const { return _type; }

	private:
		Component* _clone(const GameObject& parent) override;

		std::string _path;
		bool _isLooping;
		audio_type _type;
};

#endif //AUDIO_HPP
