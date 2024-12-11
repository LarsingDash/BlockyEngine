//
// Created by hmkam on 04/12/2024.
//

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <components/Component.hpp>

class Audio : public Component {
	public:
		Audio(GameObject* gameObject, const char* tag, std::string path, uint8_t volume, bool isLooping);
		~Audio() override = default;

		void Start() override;
		void Update(float delta) override {};
		void End() override;

		void Play(int loops = 0) const;
		void Stop() const;
		
		[[nodiscard]] inline const std::string& GetPath() const { return _path; }
		[[nodiscard]] inline uint8_t GetVolume() const { return _volume; }
		[[nodiscard]] inline bool GetIsLooping() const { return _isLooping; }

	private:
		Component* _clone(const GameObject& parent) override;

		std::string _path;
		uint8_t _volume;
		bool _isLooping;
};

#endif //AUDIO_HPP
