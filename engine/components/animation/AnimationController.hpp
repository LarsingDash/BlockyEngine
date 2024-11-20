//
// Created by 11896 on 19/11/2024.
//

#ifndef BLOCKYENGINE_ENGINE_COMPONENTS_ANIMATION_ANIMATIONCONTROLLER_HPP_
#define BLOCKYENGINE_ENGINE_COMPONENTS_ANIMATION_ANIMATIONCONTROLLER_HPP_

#include <string>
#include <string>
#include <unordered_map>
#include "components/renderables/AnimationRenderable.hpp"


class AnimationController : public Component {
	public:
		struct Animation {
			int startFrame;
			int endFrame;
			bool looping;
		};

		AnimationController(GameObject& gameObject, const char* tag, AnimationRenderable& renderable);

		void Start() override;
		void Update(float delta) override;
		void End() override;

		void SetFrameDuration(float duration);
		void AddAnimation(const std::string& animationName, int startFrame, int endFrame, bool looping);
		void PlayAnimation(const std::string& animationName);
		void StopAnimation();

	private:
		AnimationRenderable& renderable;
		float frameTimer = 0.0f;
		float frameDuration = 0.1f;

		int currentFrame = 0;
		bool isAnimating = false;
		std::string currentAnimationName;

		std::unordered_map<std::string, Animation> animations;

		void UpdateSourceRect();
};

#endif //BLOCKYENGINE_ENGINE_COMPONENTS_ANIMATION_ANIMATIONCONTROLLER_HPP_
